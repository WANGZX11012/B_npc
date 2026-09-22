`include "npc_defs.vh"

// LSU — 访存控制器：AXI4-Lite 主设备（读+写，复用 axi_lite_master）

module LSU (

  // // Clock & Reset
  input  wire         clk,
  input  wire         rst,

  // 输入: IDU / ctrl
  input  wire         in_valid,                       // 有指令来访存 握手信号
  input  wire         mem_re,                         // load
  input  wire         mem_we,                         // store
  input  wire [1:0]   mem_width,                      // BYTE / HALF / WORD
  input  wire         mem_signed,                     // load sign-extend
  input  wire         out_ready,                      // 下游(写回)能收结果

  // 输入: 数据通路 提供给axi的驱动信号
  output              req_valid,
  output[31:0]        req_addr,
  input [31:0]        wdata_in,                       // r_data2 (store data)
  input [31:0]        rdata_in,
  input [31:0]        addr_in,                        // alu_out  (memory addr)
  input               handshake_done,                 //axi反馈回来的握手完成信号

  output[31:0]        req_wdata,
  output[3:0]         req_wmask,

  // 输出: to ctrl / WBU
  output wire         in_ready,                       // 我能收新访存单(!busy)
  output wire         res_valid,                      // 结果就绪(MEM/WB棒的valid), 供retire判决
  output wire [31:0]  rdata_out                       // read data (sign-extended

);

  // ── busy: "LSU 段被本条指令占用"的自我意识 ──
  //   与 IFU 的 hold_valid 完全对称: IFU 记"我有一条指令", LSU 记"我有一单访存"。
  //   handshake_done 是单拍脉冲(只在总线返回那拍有效), 必须锁进 res_rdy,
  //   否则它和 out_ready(WB 拍)永不同时成立, busy 永远清不掉。
  //   占用周期 = 接单(MEM 首拍) → WB 拍交班, 覆盖整条指令的 MEM~WB。
  reg        busy;                 // 我手里占着一单
  reg        res_rdy;              // 总线已返回, 结果等交班
  reg [31:0] addr_r;               // 请求包: 访存地址
  reg [3:0]  wmask_r;              // 请求包: 写掩码
  reg [31:0] wdata_r;              // 请求包: 写数据(已摆位)
  reg [31:0] rdata_r;              // 结果: 读数据(已符号/零扩展)
  assign in_ready = !busy;         // 手里空着就能收
  assign rdata_out = rdata_r;      // 输出从锁存器出(MEM/WB 接力棒的 data)
  assign res_valid = res_rdy;


  /*  写逻辑  */
  // ── wmask: mem_width + addr_in[1:0] → 字节写掩码 ──
  wire [1:0] off = addr_in[1:0];
  reg  [3:0] wmask_gen;
  always @(*) 
  begin
    case (mem_width)
      `MEM_BYTE: wmask_gen = (4'b0001 << off);            // 00→0001 01→0010 10→0100 11→1000
      `MEM_HALF: wmask_gen = off[1] ? 4'b1100 : 4'b0011;  // 半字按 addr[1] 对齐
      default:   wmask_gen = 4'b1111;                     // MEM_WORD
    endcase
  end
  assign req_wmask = busy ? wmask_r : wmask_gen;   // 接单拍 bypass, 之后用锁存
  // ── store 数据摆位（复制到各字节通道，由 wmask 决定实际写入）──
  wire [31:0] wdata_gen = (mem_width == `MEM_BYTE) ? {4{wdata_in[7:0]}} :
                          (mem_width == `MEM_HALF) ? {2{wdata_in[15:0]}} :
                          wdata_in;
  assign req_wdata = busy ? wdata_r : wdata_gen;

  /*  读逻辑  */
  // ── load 选字节 + 符号扩展 ──
  wire [7:0]  lb = rdata_in[{addr_in[1:0], 3'b0} +: 8];    // 按 addr 选出目标字节 
  // 以{addr_in[1:0], 3'b0}为base 向上取8位
  wire [15:0] lh = rdata_in[{addr_in[1],   4'b0} +: 16];   // 按 addr[1] 选出目标半字
  // 组合最终值: 在总线返回拍用它锁存, 之后不再依赖总线保持 rdata_in
  wire [31:0] rdata_final = (mem_width == `MEM_BYTE) ? (mem_signed ? {{24{lb[7]}},  lb} : {24'b0, lb}) :
                            (mem_width == `MEM_HALF) ? (mem_signed ? {{16{lh[15]}}, lh} : {16'b0, lh}) :
                            rdata_in;

  // ── 级间握手 ──
  // is_access: 本条指令是否真的要访存(load/store)
  //   非访存指令: 本级纯直通, 来了就能走 访存指令  : 持续向总线发请求, 等 handshake_done 才算干完
  wire is_access = mem_re || mem_we;

  assign req_valid = (in_valid && is_access && !busy)   // 接单拍: bypass 直发
                  || (busy && !res_rdy);                // 在途: 自己维持, 不再依赖 in_valid
  assign req_addr  = busy ? addr_r : addr_in;
  /*  信号锁存  */
  always @(posedge clk)
  begin
    if (rst)
    begin
      busy    <= 1'b0;
      res_rdy <= 1'b0;
      addr_r  <= 32'b0;
      wmask_r <= 4'b0;
      wdata_r <= 32'b0;
      rdata_r <= 32'b0;
    end
    else if (!busy && in_valid && is_access)
    begin
      busy    <= 1'b1;             // 接单: 一条访存指令进段
      addr_r  <= addr_in;
      wmask_r <= wmask_gen;
      wdata_r <= wdata_gen;
    end
    else if (busy && handshake_done)
    begin
      res_rdy <= 1'b1;             // 总线返回: 结果就绪, 等下游收
      rdata_r <= rdata_final;
    end
    else if (busy && res_rdy && out_ready)  //res ready锁存 握手完成信号的作用
    begin
      busy    <= 1'b0;             // 交班: 写回段把结果收走
      res_rdy <= 1'b0;
    end
  end  

endmodule
