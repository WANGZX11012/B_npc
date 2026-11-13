`include "npc_defs.vh"

// cpu_bus_unit — CPU 侧总线单元 (arbiter + AXI4-Lite master)
//   IFU(取指) / LSU(访存) 两路简单请求仲裁后, 翻译成 AXI 五通道。
//   这是 CPU 核对总线的唯一出口; xbar 与各从设备都在它之外。
//
//   ★ 模块边界就画在 AXI 主口上: 从设备不在此模块内。
//     对外 AXI 端口与 axi_xbar 的 m_* 主口逐根同名(方向相反),
//     将来插 xbar 时只改 core_pipe 顶层接线, 本文件零改动:
//       现在: u_cpu_bus ── AXI ──> dpic_mem
//       将来: u_cpu_bus ── AXI ──> axi_xbar ── mem_* ──> dpic_mem
//                                           └─ uart_/rtc_/clint_
module cpu_bus_unit (
  input  wire        clk,
  input  wire        rst,

  // ── CPU 侧: IFU 取指请求(只读, 可 burst) ──
  input  wire        ifu_req_valid,     // 单拍脉冲(电平已由顶层整形)
  input  wire [31:0] ifu_req_addr,
  input  wire [7:0]  ifu_req_len,       // 当前单字取指恒 0
  output wire        ifu_done,
  output wire [31:0] ifu_rdata,

  // ── CPU 侧: LSU 访存请求(读写, 恒单拍) ──
  input  wire        lsu_req_valid,
  input  wire        lsu_req_we,
  input  wire [31:0] lsu_req_addr,
  input  wire [31:0] lsu_req_wdata,
  input  wire [3:0]  lsu_req_wstrb,
  output wire        lsu_ready,
  output wire [31:0] lsu_rdata,

  // ── AXI 主口 (与 axi_xbar.m_* 对齐) ──
  // AR
  output wire [31:0] araddr,
  output wire [7:0]  arlen,
  output wire        arvalid,
  input  wire        arready,
  // R
  input  wire [31:0] rdata,
  input  wire [1:0]  rresp,
  input  wire        rvalid,
  input  wire        rlast,
  output wire        rready,
  // AW
  output wire [31:0] awaddr,
  output wire        awvalid,
  input  wire        awready,
  // W
  output wire [31:0] wdata,
  output wire [3:0]  wstrb,
  output wire        wvalid,
  input  wire        wready,
  // B
  input  wire [1:0]  bresp,
  input  wire        bvalid,
  output wire        bready
);

  // ── arbiter → master 的简单请求侧: 已收进模块内部, 顶层不再可见 ──
  wire        m_req_valid, m_req_we, m_done;
  wire [31:0] m_req_addr, m_req_wdata, m_rdata;
  wire [3:0]  m_req_wstrb;
  wire [7:0]  m_req_len;

  arbiter_pipe u_arb (
    .clk(clk), .rst(rst),
    .ifu_req_valid(ifu_req_valid), .ifu_req_addr(ifu_req_addr), .ifu_req_len(ifu_req_len),
    .ifu_done(ifu_done), .ifu_rdata(ifu_rdata),
    .lsu_req_valid(lsu_req_valid), .lsu_req_we(lsu_req_we),
    .lsu_req_addr(lsu_req_addr), .lsu_req_wdata(lsu_req_wdata),
    .lsu_req_wstrb(lsu_req_wstrb),
    .lsu_ready(lsu_ready), .lsu_rdata(lsu_rdata),
    .m_req_valid(m_req_valid), .m_req_we(m_req_we),
    .m_req_addr(m_req_addr), .m_req_wdata(m_req_wdata),
    .m_req_wstrb(m_req_wstrb), .m_req_len(m_req_len),
    .m_done(m_done), .m_rdata(m_rdata), .m_rvalid(rvalid)
  );

  ysyx_26020047_axi_master u_master (
    .clk(clk), .rst(rst),
    .req_valid(m_req_valid), .req_we(m_req_we),
    .req_addr(m_req_addr), .req_wdata(m_req_wdata),
    .req_wstrb(m_req_wstrb), .req_len(m_req_len),
    .req_rsize(2'b10),        // 总线恒按 4 字节字传输; 裁剪在 LSU 内做
    .stall(1'b0),             // 无 LFSR 随机停顿
    .done(m_done), .resp_rdata(m_rdata),
    .araddr(araddr), .arvalid(arvalid), .arready(arready), .arlen(arlen),
    .rid(4'd0), .rdata(rdata), .rvalid(rvalid),
    .rresp(rresp), .rlast(rlast), .rready(rready),
    .awaddr(awaddr), .awvalid(awvalid), .awready(awready),
    .wdata(wdata), .wvalid(wvalid), .wstrb(wstrb), .wready(wready),
    .bid(4'd0), .bresp(bresp), .bvalid(bvalid), .bready(bready)
  );

endmodule
