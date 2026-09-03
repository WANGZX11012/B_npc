`include "npc_defs.vh"

// LSU — 访存控制器：AXI4-Lite 主设备（读+写，复用 axi_lite_master）

module LSU (

  // // Clock & Reset
  // input  wire         clk,
  // input  wire         rst,

  // 输入: IDU / ctrl
  input  wire         mem_req,                        // ctrl: MEM 拍
  input  wire         mem_re,                         // load
  input  wire         mem_we,                         // store
  input  wire [1:0]   mem_width,                      // BYTE / HALF / WORD
  input  wire         mem_signed,                     // load sign-extend

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
  output wire         lsu_done,                       // transaction complete
  output wire [31:0]  rdata_out                       // read data (sign-extended)

);

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

  assign req_wmask = wmask_gen;

  // ── store 数据摆位（复制到各字节通道，由 wmask 决定实际写入）──
  wire [31:0] wdata_gen = (mem_width == `MEM_BYTE) ? {4{wdata_in[7:0]}} :
                          (mem_width == `MEM_HALF) ? {2{wdata_in[15:0]}} :
                          wdata_in;
                      
  assign  req_wdata = wdata_gen;

  // ── load 选字节 + 符号扩展 ──
  // ── load 选字节 + 符号扩展 ──
  wire [7:0]  lb = rdata_in[{addr_in[1:0], 3'b0} +: 8];    // 按 addr 选出目标字节 
                      // 以{addr_in[1:0], 3'b0}为base 向上取8位
  wire [15:0] lh = rdata_in[{addr_in[1],   4'b0} +: 16];   // 按 addr[1] 选出目标半字


  assign rdata_out = (mem_width == `MEM_BYTE) ? (mem_signed ? {{24{lb[7]}},  lb} : {24'b0, lb}) :
                     (mem_width == `MEM_HALF) ? (mem_signed ? {{16{lh[15]}}, lh} : {16'b0, lh}) :
                     rdata_in;

    // ── 请求有效 ──
  assign req_valid = mem_req && (mem_re || mem_we); //后面的判断有点多余？
  assign req_addr = addr_in;
  assign lsu_done = handshake_done;

endmodule
