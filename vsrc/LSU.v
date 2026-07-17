`include "npc_defs.vh"

// LSU — 访存控制器：SimpleBus 主设备
// 从 IDU 接收访存请求，转为 SimpleBus 总线协议发给 data_mem
// idle: 发请求 (addr, wen, wdata, wmask)
// wait: 等内存返回 (respValid=1 → 数据有效)

module LSU (
  input  wire         clk,
  input  wire         mem_req,       // ctrl: MEM 状态
  input  wire         mem_re,        // load 使能
  input  wire         mem_we,        // store 使能
  input  wire [1:0]   mem_width,     // BYTE/HALF/WORD
  input  wire         mem_signed,    // load 符号扩展
  input  wire [31:0]  wdata_in,      // 要写的数据 (r_data2)
  input  wire [31:0]  addr_in,       // 访存地址 (alu_out)

  // SimpleBus 主设备接口 → data_mem
  output wire         lsu_reqValid,
  output wire [31:0]  lsu_addr,
  output wire         lsu_wen,
  output wire [31:0]  lsu_wdata,
  output wire [3:0]   lsu_wmask,

  input  wire [31:0]  lsu_rdata,
  input  wire         lsu_respValid,
  output wire         lsu_done,      // 本拍事务完成

  // 读回数据（经符号扩展）→ WBU
  output wire [31:0]  rdata
);

  localparam [0:0] S_IDLE = 0, S_WAIT = 1;
  reg [0:0] bus_state, bus_next;

  always @(posedge clk)
    bus_state <= bus_next;

  wire do_req = mem_req && (mem_re || mem_we);   // MEM 拍 + IDU 说访存

  always @(*) 
  begin
    case (bus_state)
      S_IDLE: bus_next = do_req ? S_WAIT : S_IDLE;       // 有请求才进 wait
      S_WAIT: bus_next = lsu_respValid ? S_IDLE : S_WAIT; // 数据到 → 回 idle
      default: bus_next = S_IDLE;
    endcase
  end

  assign lsu_reqValid = (bus_state == S_IDLE) && do_req;
  assign lsu_addr     = addr_in;
  assign lsu_wen      = mem_we;
  assign lsu_wdata    = wdata_in;

  // wmask：字节/半字/字
  assign lsu_wmask = (mem_width == `MEM_BYTE)  ? 4'b0001 :
                     (mem_width == `MEM_HALF)  ? 4'b0011 :
                     /* MEM_WORD */              4'b1111;

  assign lsu_done = (bus_state == S_WAIT) && lsu_respValid;

  // 读数据符号扩展
  assign rdata = (mem_width == `MEM_BYTE)  ? (mem_signed ? {{24{lsu_rdata[ 7]}}, lsu_rdata[ 7:0]}
                                                          : {24'b0, lsu_rdata[7:0]})
               : (mem_width == `MEM_HALF)  ? (mem_signed ? {{16{lsu_rdata[15]}}, lsu_rdata[15:0]}
                                                          : {16'b0, lsu_rdata[15:0]})
               : /* MEM_WORD */               lsu_rdata;

endmodule
