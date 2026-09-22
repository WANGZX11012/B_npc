`ifdef YSYXSOC
// ysyx_26020047 — 一生一芯 CPU 在 ysyxSoC 上的顶层封装
//   端口严格对齐 ysyxSoC/spec/cpu-interface.md:
//     clock / reset / io_interrupt / io_master_*
//   io_slave_* 规范文档未列, 但 SoC 生成的 Verilog 会连它(见 ysyxSoC/build/ysyxSoCFull.v),
//   所以必须存在; 本 CPU 不作从设备, 29 根输出恒 0 打桩。
//   整份文件只在 +define+YSYXSOC 时参与编译, 单跑模式不产生任何模块。
module ysyx_26020047 (

  // Clock & Reset(SoC 命名: clock/reset, 不是 clk/rst)
  input         clock,
  input         reset,

  // 外部中断(SoC 侧当前恒 0; MEIP 未实现, 暂不接入)
  input         io_interrupt,

  // ── AXI4 Master: 写地址通道 AW ──
  input         io_master_awready,
  output        io_master_awvalid,
  output [3:0]  io_master_awid,
  output [31:0] io_master_awaddr,
  output [7:0]  io_master_awlen,
  output [2:0]  io_master_awsize,
  output [1:0]  io_master_awburst,

  // ── AXI4 Master: 写数据通道 W ──
  input         io_master_wready,
  output        io_master_wvalid,
  output [31:0] io_master_wdata,
  output [3:0]  io_master_wstrb,
  output        io_master_wlast,

  // ── AXI4 Master: 写响应通道 B ──
  input         io_master_bvalid,
  input  [3:0]  io_master_bid,
  input  [1:0]  io_master_bresp,
  output        io_master_bready,

  // ── AXI4 Master: 读地址通道 AR ──
  input         io_master_arready,
  output        io_master_arvalid,
  output [3:0]  io_master_arid,
  output [31:0] io_master_araddr,
  output [7:0]  io_master_arlen,
  output [2:0]  io_master_arsize,
  output [1:0]  io_master_arburst,

  // ── AXI4 Master: 读数据通道 R ──
  input         io_master_rvalid,
  input  [3:0]  io_master_rid,
  input  [31:0] io_master_rdata,
  input  [1:0]  io_master_rresp,
  input         io_master_rlast,
  output        io_master_rready,

  // ── AXI4 Slave: 本 CPU 不作从设备, 恒不响应 ──
  // 方向与 master 侧相反: 本侧是 slave, 所以 valid 是输入、ready 是输出
  output        io_slave_awready,
  input         io_slave_awvalid,
  input  [3:0]  io_slave_awid,
  input  [31:0] io_slave_awaddr,
  input  [7:0]  io_slave_awlen,
  input  [2:0]  io_slave_awsize,
  input  [1:0]  io_slave_awburst,

  output        io_slave_wready,
  input         io_slave_wvalid,
  input  [31:0] io_slave_wdata,
  input  [3:0]  io_slave_wstrb,
  input         io_slave_wlast,

  input         io_slave_bready,
  output        io_slave_bvalid,
  output [3:0]  io_slave_bid,
  output [1:0]  io_slave_bresp,

  output        io_slave_arready,
  input         io_slave_arvalid,
  input  [3:0]  io_slave_arid,
  input  [31:0] io_slave_araddr,
  input  [7:0]  io_slave_arlen,
  input  [2:0]  io_slave_arsize,
  input  [1:0]  io_slave_arburst,

  input         io_slave_rready,
  output        io_slave_rvalid,
  output [3:0]  io_slave_rid,
  output [31:0] io_slave_rdata,
  output [1:0]  io_slave_rresp,
  output        io_slave_rlast

);

  // ── 调试观测线: 端口列表必须与 SoC 严格一致(多一个少一个都不行),
  //    故 pc/halt 等不引出, 先接在内部线上, 以后由 tb 层次化探针读 ──
  wire [31:0] dbg_pc;
  wire        dbg_halt;
  wire        dbg_aborted;
  wire [31:0] dbg_ir;
  wire [2:0]  dbg_state;
  wire        dbg_retire;
  wire        dbg_mmio;

  // ── 唯一的处理器实例(SoC 模式: core 内部 xbar/从设备已按 ifdef 旁路) ──
  core u_core (
    .clk         (clock),
    .rst         (reset),

    // AXI4 Master
    .io_master_arid    (io_master_arid),
    .io_master_araddr  (io_master_araddr),
    .io_master_arlen   (io_master_arlen),
    .io_master_arsize  (io_master_arsize),
    .io_master_arburst (io_master_arburst),
    .io_master_arvalid (io_master_arvalid),
    .io_master_arready (io_master_arready),

    .io_master_rid     (io_master_rid),
    .io_master_rdata   (io_master_rdata),
    .io_master_rresp   (io_master_rresp),
    .io_master_rlast   (io_master_rlast),
    .io_master_rvalid  (io_master_rvalid),
    .io_master_rready  (io_master_rready),

    .io_master_awid    (io_master_awid),
    .io_master_awaddr  (io_master_awaddr),
    .io_master_awlen   (io_master_awlen),
    .io_master_awsize  (io_master_awsize),
    .io_master_awburst (io_master_awburst),
    .io_master_awvalid (io_master_awvalid),
    .io_master_awready (io_master_awready),

    .io_master_wdata   (io_master_wdata),
    .io_master_wstrb   (io_master_wstrb),
    .io_master_wlast   (io_master_wlast),
    .io_master_wvalid  (io_master_wvalid),
    .io_master_wready  (io_master_wready),

    .io_master_bid     (io_master_bid),
    .io_master_bresp   (io_master_bresp),
    .io_master_bvalid  (io_master_bvalid),
    .io_master_bready  (io_master_bready),

    // 调试观测(不引出)
    .pc          (dbg_pc),
    .halt        (dbg_halt),
    .aborted     (dbg_aborted),
    .ir_dbg      (dbg_ir),
    .state_dbg   (dbg_state),
    .inst_retire (dbg_retire),
    .mmio_dbg    (dbg_mmio)
  );

  // ── AXI4 Slave: 恒不响应(SoC 侧无主设备访问本 CPU) ──
  //    只驱动本侧的 11 根输出; 18 根输入不接(悬空即"永远收不到请求")
  assign io_slave_awready = 1'b0;
  assign io_slave_wready  = 1'b0;
  assign io_slave_bvalid  = 1'b0;
  assign io_slave_bid     = 4'd0;
  assign io_slave_bresp   = 2'd0;

  assign io_slave_arready = 1'b0;
  assign io_slave_rvalid  = 1'b0;
  assign io_slave_rid     = 4'd0;
  assign io_slave_rdata   = 32'd0;
  assign io_slave_rresp   = 2'd0;
  assign io_slave_rlast   = 1'b0;

endmodule
`endif
