`include "npc_defs.vh"

// 命名约定: 内部连线一律带"来源模块"前缀, 一眼看出信号从哪来、去哪里
//   ifu_*   IFU        输出
//   lsu_*   LSU        输出
//   arb_*   arbiter    输出
//   mst_*   axi_lite_master 输出 (含 AXI4-Lite 五通道)
//   idu_*   IDU        输出
//   rf_*    RegisterFile 输出
//   exu_*   EXU        输出
//   wbu_*   WBU        输出
//   csr_*   CSRFile    输出
//   ctrl_*  ctrl       输出
//   xbar_*  axi_xbar   输出
//   lfsr_*  lfsr       输出
//   _r 后缀 core 自己的时序锁存(alu_result_r / mmio_flag_r)
module core (

  // Clock & Reset
  input         clk,
  input         rst,

  // 输出: to top / monitor
  output [31:0] pc,          // 当前 PC, IFU 直接驱动
  output        halt,        // ebreak 时拉高
  output        aborted,     // 非法指令/异常终止(对齐 NEMU_ABORT)
  output [31:0] ir_dbg,      // IR for monitor
  output [2:0]  state_dbg,   // ctrl_state for monitor
  output        mmio_dbg     // 本条指令是否访问了外设(供 difftest 跳过比对)
);

  // ═══════════════ IFU ↔ arbiter ═══════════════
  wire [31:0] ifu_pc4;          // IFU → WBU (jal/jalr 写 rd = pc+4)
  wire [31:0] ifu_npc_normal;   // IFU → 第 4 步作中断 mepc (未被中断劫持的 next pc)
  wire [31:0] ifu_inst;         // IFU → IR (FET 拍锁存)
  wire        ifu_done;         // IFU → ctrl (取指完成)
  wire        ifu_req_valid;    // IFU → arbiter (取指请求)
  wire [31:0] ifu_req_addr;     // IFU → arbiter (取指地址)
  wire        arb_ifu_done;     // arbiter → IFU (握手完成)
  wire [31:0] arb_ifu_rdata;    // arbiter → IFU (返回指令)

  // ═══════════════ LSU ↔ arbiter ═══════════════
  wire        lsu_req_valid;    // LSU → arbiter (访存请求)
  wire [31:0] lsu_req_addr;     // LSU → arbiter (访存地址)
  wire [31:0] lsu_req_wdata;    // LSU → arbiter (store 数据)
  wire [3:0]  lsu_req_wmask;    // LSU → arbiter (字节写使能)
  wire        arb_lsu_done;     // arbiter → LSU (握手完成)
  wire [31:0] arb_lsu_rdata;    // arbiter → LSU (返回数据)
  wire        lsu_done;         // LSU → ctrl (访存完成)
  wire [31:0] lsu_rdata;        // LSU → WBU (load 数据, 已符号/零扩展)

  // ═══════════════ arbiter ↔ axi_lite_master ═══════════════
  wire        arb_req_valid;    // arbiter → master (合并后的请求)
  wire        arb_req_we;       // arbiter → master
  wire [31:0] arb_req_addr;     // arbiter → master
  wire [31:0] arb_req_wdata;    // arbiter → master
  wire [3:0]  arb_req_wstrb;    // arbiter → master
  wire        mst_done;         // master → arbiter (传输完成)
  wire [31:0] mst_resp_rdata;   // master → arbiter (读数据)

  // ═══════════════ axi_lite_master → axi_xbar (AXI4-Lite 五通道) ═══════════════
  wire [31:0] mst_araddr, mst_awaddr, mst_wdata, mst_rdata;
  wire        mst_arvalid, mst_arready, mst_rvalid, mst_rready;
  wire [1:0]  mst_rresp;
  wire        mst_awvalid, mst_awready, mst_wvalid, mst_wready;
  wire [3:0]  mst_wmask;
  wire [1:0]  mst_bresp;
  wire        mst_bvalid, mst_bready;

  // ═══════════════ lfsr → axi_lite_master ═══════════════
  wire [7:0]  lfsr_val;         // lfsr → 停顿阈值比较
  wire        lfsr_stall;       // → axi_lite_master.stall (随机总线停顿)

  // ═══════════════ IDU → 各模块 ═══════════════
  wire [4:0]  idu_rs1;          // → RegisterFile.r_addr1
  wire [4:0]  idu_rs2;          // → RegisterFile.r_addr2
  wire [4:0]  idu_rd;           // → RegisterFile.w_addr
  wire        idu_rd_en;        // → RegisterFile.wen (与 ctrl_reg_we 相与)
  wire [31:0] idu_imm;          // → EXU / WBU
  wire [3:0]  idu_alu_op;       // → EXU
  wire        idu_alu_en;       // → EXU
  wire        idu_alu_src2_imm; // → EXU
  wire        idu_alu_src1_pc;  // → EXU
  wire [2:0]  idu_wb_sel;       // → WBU
  wire [2:0]  idu_npc_sel;      // → IFU (next-pc 选择) / CSRFile (ecall/mret 判定)
  wire        idu_mem_re;       // → LSU / ctrl (是否进 MEM 拍)
  wire        idu_mem_we;       // → LSU / ctrl / arbiter
  wire [1:0]  idu_mem_width;    // → LSU
  wire        idu_mem_signed;   // → LSU
  wire [2:0]  idu_branch_type;  // → EXU
  wire        idu_invalid;      // → ctrl (非法指令)
  wire [11:0] idu_csr_idx;      // → CSRFile
  wire        idu_csr_wen;      // → CSRFile
  wire        idu_csr_s_w;      // → CSRFile (置位/原值写)

  // ═══════════════ RegisterFile / EXU / WBU ═══════════════
  wire [31:0] rf_rdata1;        // RegisterFile → EXU / CSRFile.csr_wdata
  wire [31:0] rf_rdata2;        // RegisterFile → LSU.wdata_in
  wire [31:0] exu_alu_result;   // EXU → IFU (跳转目标) / alu_result_r
  wire        exu_branch_taken; // EXU → IFU (分支成立)
  wire [31:0] wbu_wb_data;      // WBU → RegisterFile.w_data

  // ═══════════════ CSRFile → ═══════════════
  wire [31:0] csr_data;         // CSRFile → WBU (csr 读值写回 rd)
  wire [31:0] csr_mtvec;        // CSRFile → IFU (trap 入口)
  wire [31:0] csr_mepc;         // CSRFile → IFU (mret 返回地址)
  wire        csr_mstatus_mie;  // CSRFile → CSRFile → irq_taken 判决
  //  时钟中断相关
  wire        irq_taken;        // 中断响应判决(assign 在 clint 实例之后)
  wire [31:0] trap_pc;          // 存进 mepc: 中断→ifu_npc_normal, 异常→ir_pc

  // ═══════════════ ctrl → 各模块 ═══════════════
  wire        ctrl_at_state_wb; // → CSRFile (CSR 写时机)
  wire [2:0]  ctrl_state;       // → alu_result_r / mmio_flag_r / state_dbg
  wire        ctrl_ir_we;       // → IR / ir_pc 锁存
  wire        ctrl_pc_we;       // → IFU
  wire        ctrl_reg_we;      // → RegisterFile
  wire        ctrl_fetch_req;   // → IFU
  wire        ctrl_mem_req;     // → LSU
  wire        ctrl_abort;       // → aborted

  // ═══════════════ 未用端口(保留连接, 避免 PINMISSING) ═══════════════
  wire        idu_unused_rs1_en;  // IDU → 未用
  wire        idu_unused_rs2_en;  // IDU → 未用
  wire [31:0] rf_unused_r_a0;     // RegisterFile → 未用

  // ── IFU ── 私有请求接口接 arbiter
  IFU u_ifu (
    .clk(clk), .rst(rst),
    .pc_we(ctrl_pc_we), .fetch_req(ctrl_fetch_req),
    .alu_result(exu_alu_result), .npc_sel(idu_npc_sel),
    .branch_taken(exu_branch_taken),
    .csr_mtvec(csr_mtvec), .csr_mepc(csr_mepc),
    .irq_taken(irq_taken),                 // 中断行为 劫持取指
    .req_valid(ifu_req_valid),
    .req_addr(ifu_req_addr),
    .handshake_done(arb_ifu_done),
    .resp_rdata(arb_ifu_rdata),
    .pc(pc), .pc4(ifu_pc4), .inst(ifu_inst),
    .npc_normal(ifu_npc_normal),      // 未被中断劫持的 next-pc, 中断时作 mepc
    .ifu_done(ifu_done)
  );

  // ── LSU（访存控制器：私有请求 → arbiter）──
  LSU u_lsu (
    .mem_req(ctrl_mem_req),
    .mem_re(idu_mem_re), .mem_we(idu_mem_we),
    .mem_width(idu_mem_width), .mem_signed(idu_mem_signed),
    .wdata_in(rf_rdata2), .addr_in(alu_result_r),
    .rdata_in(arb_lsu_rdata),
    .handshake_done(arb_lsu_done),
    .req_valid(lsu_req_valid),
    .req_addr(lsu_req_addr),
    .req_wdata(lsu_req_wdata),
    .req_wmask(lsu_req_wmask),
    .lsu_done(lsu_done),
    .rdata_out(lsu_rdata)
  );

  // ── 仲裁器：IFU/LSU 两个 master 合并成一路（IFU 固定优先）──
  arbiter u_arb (
    .clk(clk), .rst(rst),
    .ifu_req_valid(ifu_req_valid), .ifu_req_addr(ifu_req_addr),
    .ifu_done(arb_ifu_done), .ifu_resp_rdata(arb_ifu_rdata),
    .lsu_req_valid(lsu_req_valid), .lsu_req_we(idu_mem_we),
    .lsu_req_addr(lsu_req_addr), .lsu_req_wdata(lsu_req_wdata),
    .lsu_req_wstrb(lsu_req_wmask),
    .lsu_done(arb_lsu_done), .lsu_resp_rdata(arb_lsu_rdata),
    .m_req_valid(arb_req_valid), .m_req_we(arb_req_we),
    .m_req_addr(arb_req_addr), .m_req_wdata(arb_req_wdata),
    .m_req_wstrb(arb_req_wstrb),
    .m_done(mst_done), .m_resp_rdata(mst_resp_rdata)
  );

  // ── 唯一的 AXI4-Lite 协议适配层（IFU 读 / LSU 读写 共用）──
  axi_lite_master u_master (
    .clk(clk), .rst(rst),
    .req_valid(arb_req_valid), .req_we(arb_req_we),
    .req_addr(arb_req_addr), .req_wdata(arb_req_wdata), .req_wstrb(arb_req_wstrb),
    .stall(lfsr_stall),
    .done(mst_done), .resp_rdata(mst_resp_rdata),
    // AR
    .araddr(mst_araddr), .arvalid(mst_arvalid), .arready(mst_arready),
    // R
    .rdata(mst_rdata), .rvalid(mst_rvalid), .rresp(mst_rresp), .rready(mst_rready),
    // AW
    .awaddr(mst_awaddr), .awvalid(mst_awvalid), .awready(mst_awready),
    // W
    .wdata(mst_wdata), .wvalid(mst_wvalid), .wmask(mst_wmask), .wready(mst_wready),
    // B
    .bresp(mst_bresp), .bvalid(mst_bvalid), .bready(mst_bready)
  );

  // ── axi_xbar：把 axi_lite_master 的单路 AXI 按地址扇出到 {rtc, clint, uart, mem} ──
  // 译码/门控/广播/多选全在 xbar 内部。core 只做两件事:
  //   1) xbar 主口 m_* 直接接上面 axi_lite_master 的输出;
  //   2) 三个从设备的端口改接 xbar 从口。
  // mem 从口(xbar 驱动侧; xbar 端口叫 mem_*, 这里接到 core 的 dmem_* 线)
  wire [31:0] dmem_araddr, dmem_awaddr, dmem_wdata;
  wire [3:0]  dmem_wmask;
  wire        dmem_arvalid, dmem_rready, dmem_awvalid, dmem_wvalid, dmem_bready;
  // uart 从口(xbar 驱动侧)
  wire [31:0] uart_araddr, uart_awaddr, uart_wdata;
  wire [3:0]  uart_wmask;
  wire        uart_arvalid, uart_rready, uart_awvalid, uart_wvalid, uart_bready;
  // rtc 从口(xbar 驱动侧, 只读)
  wire [31:0] rtc_araddr;
  wire        rtc_arvalid;
  // clint 从口(xbar 驱动侧; 含写通道, 路由到 mtimecmp)
  wire [31:0] clint_araddr;
  wire        clint_arvalid;
  wire [31:0] clint_awaddr, clint_wdata;
  wire        clint_awvalid, clint_wvalid;
  wire        clint_bready;
  // MMIO 标记(xbar 判定, 供 difftest 跳过比对)
  wire        xbar_mmio_sel;

  axi_xbar u_xbar (
    // 主口 ← axi_lite_master
    .m_araddr (mst_araddr),  .m_arvalid (mst_arvalid),  .m_arready (mst_arready),
    .m_rdata  (mst_rdata),   .m_rresp   (mst_rresp),    .m_rvalid  (mst_rvalid),  .m_rready (mst_rready),
    .m_awaddr (mst_awaddr),  .m_awvalid (mst_awvalid),  .m_awready (mst_awready),
    .m_wdata  (mst_wdata),   .m_wmask   (mst_wmask),    .m_wvalid  (mst_wvalid),  .m_wready (mst_wready),
    .m_bresp  (mst_bresp),   .m_bvalid  (mst_bvalid),   .m_bready  (mst_bready),
    // 从口 → mem
    .mem_araddr (dmem_araddr),  .mem_arvalid (dmem_arvalid),  .mem_arready (dmem_arready),
    .mem_rdata  (dmem_rdata),   .mem_rresp   (dmem_rresp),    .mem_rvalid  (dmem_rvalid),  .mem_rready (dmem_rready),
    .mem_awaddr (dmem_awaddr),  .mem_awvalid (dmem_awvalid),  .mem_awready (dmem_awready),
    .mem_wdata  (dmem_wdata),   .mem_wmask   (dmem_wmask),    .mem_wvalid  (dmem_wvalid),  .mem_wready (dmem_wready),
    .mem_bresp  (dmem_bresp),   .mem_bvalid  (dmem_bvalid),   .mem_bready  (dmem_bready),
    // 从口 → uart
    .uart_araddr (uart_araddr),  .uart_arvalid (uart_arvalid),  .uart_arready (uart_arready),
    .uart_rdata  (uart_rdata),   .uart_rresp   (uart_rresp),    .uart_rvalid  (uart_rvalid),  .uart_rready (uart_rready),
    .uart_awaddr (uart_awaddr),  .uart_awvalid (uart_awvalid),  .uart_awready (uart_awready),
    .uart_wdata  (uart_wdata),   .uart_wmask   (uart_wmask),    .uart_wvalid  (uart_wvalid),  .uart_wready (uart_wready),
    .uart_bresp  (uart_bresp),   .uart_bvalid  (uart_bvalid),   .uart_bready  (uart_bready),
    // 从口 → rtc（只读）
    .rtc_araddr (rtc_araddr),  .rtc_arvalid (rtc_arvalid),  .rtc_arready (rtc_arready),
    .rtc_rdata  (rtc_rdata),   .rtc_rresp   (rtc_rresp),    .rtc_rvalid  (rtc_rvalid),
    // 从口 → clint（读 mtime/mtimecmp + 写 mtimecmp）
    .clint_araddr (clint_araddr),  .clint_arvalid (clint_arvalid),  .clint_arready (clint_arready),
    .clint_rdata  (clint_rdata),   .clint_rresp   (clint_rresp),    .clint_rvalid  (clint_rvalid),
    .clint_awaddr (clint_awaddr),  .clint_awvalid (clint_awvalid),  .clint_awready (clint_awready),
    .clint_wdata  (clint_wdata),   .clint_wvalid  (clint_wvalid),   .clint_wready  (clint_wready),
    .clint_bresp  (clint_bresp),   .clint_bvalid  (clint_bvalid),   .clint_bready  (clint_bready),
    // MMIO 标记
    .mmio_sel (xbar_mmio_sel)
  );

  // ── LFSR:每拍推进, 按阈值产生随机总线停顿 ──
  // lfsr 输出 1~255(不含 0), 阈值 16 → 约 1/16 概率停一拍
`ifdef HAS_LFSR
  lfsr u_lfsr (
    .clk (clk),
    .rst (rst),
    .en  (1'b1),
    .val (lfsr_val)
  );
  assign lfsr_stall = (lfsr_val < 8'd16); //小于16就stall
`else
  assign lfsr_stall = 1'b0;               // 未开 LFSR: 总线不停顿
`endif

  // ── 控制器 ──
  ctrl u_ctrl (
    .clk(clk), .rst(rst),
    .idu_mem_re(idu_mem_re), .idu_mem_we(idu_mem_we),
    .idu_invalid(idu_invalid),
    .ifu_done(ifu_done), .lsu_done(lsu_done),
    .state(ctrl_state),
    .ir_we(ctrl_ir_we), .pc_we(ctrl_pc_we), .at_state_wb(ctrl_at_state_wb), .reg_we(ctrl_reg_we),
    .fetch_req(ctrl_fetch_req), .mem_req(ctrl_mem_req),
    .aborted(ctrl_abort)
  );

  // ── IR ──
  reg [31:0] IR;
  reg [31:0] ir_pc;          // 锁存当前指令的 PC, 供 ecall/mret 作为 mepc 基准
  always @(posedge clk)
  begin
    if (ctrl_ir_we) IR    <= ifu_inst;
    if (ctrl_ir_we) ir_pc <= pc;   // pc 此时为刚取到的指令地址(FET 阶段未前进)
  end

  // ── ALU 结果锁存 ──
  reg [31:0] alu_result_r;   // EXE 拍锁存 exu_alu_result, 供 MEM 拍访存 / WB 拍写回
  always @(posedge clk)
  begin
    if (ctrl_state == `ST_EXE)
    begin
      alu_result_r <= exu_alu_result;
    end
  end

  // ── RTC 从设备（墙钟只读, AM_TIMER_UPTIME 真实时间来源, 0xa0000048）──
  wire        rtc_arready, rtc_rvalid;
  wire [31:0] rtc_rdata;
  wire [1:0]  rtc_rresp;
  rtc u_rtc (
    .clk    (clk),
    .araddr (rtc_araddr),
    .arvalid(rtc_arvalid),
    .arready(rtc_arready),
    .rdata  (rtc_rdata),
    .rresp  (rtc_rresp),
    .rvalid (rtc_rvalid),
    .rready (mst_rready)   // rtc 的 rready 不走 xbar(xbar 无 rtc_rready 口), 直接连 master
  );

  // ── CLINT 从设备（mtime 只读 + mtimecmp 可写, 0xa0000050~5f）──
  wire        clint_arready, clint_rvalid;
  wire [31:0] clint_rdata;
  wire [1:0]  clint_rresp;
  wire        clint_awready, clint_wready, clint_bvalid;
  wire [1:0]  clint_bresp;
  wire        clint_mtip;   // 定时器中断请求, 第 4 步接 irq_taken 判决
  clint u_clint (
    .clk    (clk),
    .rst    (rst),
    .araddr (clint_araddr),
    .arvalid(clint_arvalid),
    .arready(clint_arready),
    .rdata  (clint_rdata),
    .rresp  (clint_rresp),
    .rvalid (clint_rvalid),
    .rready (mst_rready),  // clint 的 rready 不走 xbar(xbar 无 clint_rready 口), 直接连 master
    // 写通道 → mtimecmp
    .awaddr (clint_awaddr), .awvalid(clint_awvalid), .awready(clint_awready),
    .wdata  (clint_wdata),  .wvalid (clint_wvalid),  .wready (clint_wready),
    .bresp  (clint_bresp),  .bvalid (clint_bvalid),  .bready (clint_bready),
    // 中断
    .mtip   (clint_mtip)
  );
 // ── 中断响应判决 ──
  // 只在 WB 拍响应: 这一拍 reg_we/pc_we/CSR 写同时发生, 是唯一的原子指令边界
  //   ctrl_at_state_wb : (state == 3'd5), 指令边界
  //   csr_mstatus_mie  : mstatus.MIE, 软件 iset() 打开才响应
  //   clint_mtip       : mtime >= mtimecmp, 硬件中断请求
  // 排除 ecall(3'b100) / mret(3'b101), 否则 mepc 会被写坏:
  //   ecall: npc_normal 恰好 = mtvec, mepc 会变成 mtvec, 返回地址丢失
  //   mret : npc_normal 恰好 = mepc,  新 mepc = 旧 mepc, mret 后死循环
  assign irq_taken = ctrl_at_state_wb
                  && csr_mstatus_mie
                  && clint_mtip
                  && (idu_npc_sel != `NPC_ECALL)
                  && (idu_npc_sel != `NPC_MRET)
                  && !idu_csr_wen;  //  CSR 写指令的WB拍不响应中断

  // 异常存自己(软件 +4 跳过); 中断存下一条(软件绝不能 +4)
  assign trap_pc   = irq_taken ? ifu_npc_normal : ir_pc;














  // ── UART 从设备（串口，写打印 / 读返回 0）── 段译码/门控已移到 axi_xbar
  wire        uart_arready, uart_rvalid;
  wire [31:0] uart_rdata;
  wire [1:0]  uart_rresp;
  wire        uart_awready, uart_wready, uart_bvalid;
  wire [1:0]  uart_bresp;
  uart u_uart (
    .clk    (clk),
    .araddr (uart_araddr), .arvalid(uart_arvalid), .arready(uart_arready),
    .rdata  (uart_rdata), .rresp(uart_rresp), .rvalid(uart_rvalid), .rready(uart_rready),
    .awaddr (uart_awaddr),
    .awvalid(uart_awvalid),
    .awready(uart_awready),
    .wdata  (uart_wdata),
    .wmask  (uart_wmask),
    .wvalid (uart_wvalid),
    .wready (uart_wready),
    .bresp  (uart_bresp),
    .bvalid (uart_bvalid),
    .bready (uart_bready)
  );

  // ── 统一内存（取指 + 访存共用同一个 mem 从设备）── 段译码/门控已移到 axi_xbar
  wire        dmem_arready, dmem_rvalid, dmem_awready, dmem_wready, dmem_bvalid;
  wire [31:0] dmem_rdata;
  wire [1:0]  dmem_rresp, dmem_bresp;
`ifdef DPI_MEM
  // DPI 模式: 取指/访存经 DPI-C 读写 NEMU pmem, 只保留一个实例。
  // pmem 段 = 0x80000000~0x87FFFFFF (128MB), 由 xbar 的 mem 从口统一路由。
  dpic_mem u_mem (
    .clk(clk),
    .araddr(dmem_araddr), .arvalid(dmem_arvalid), .arready(dmem_arready),
    .rdata(dmem_rdata), .rresp(dmem_rresp), .rvalid(dmem_rvalid), .rready(dmem_rready),
    .awaddr(dmem_awaddr), .awvalid(dmem_awvalid), .awready(dmem_awready),
    .wdata(dmem_wdata), .wmask(dmem_wmask), .wvalid(dmem_wvalid), .wready(dmem_wready),
    .bresp(dmem_bresp), .bvalid(dmem_bvalid), .bready(dmem_bready)
  );
`else
  // 非 DPI 模式: 用一块 data_mem(读写)同时服务取指与访存, inst_mem 已并入。
  pmem u_pmem (                  // delay from menuconfig
    .clk(clk),
    .araddr(dmem_araddr), .arvalid(dmem_arvalid), .arready(dmem_arready),
    .rdata(dmem_rdata), .rresp(dmem_rresp), .rvalid(dmem_rvalid), .rready(dmem_rready),
    .awaddr(dmem_awaddr), .awvalid(dmem_awvalid), .awready(dmem_awready),
    .wdata(dmem_wdata), .wmask(dmem_wmask), .wvalid(dmem_wvalid), .wready(dmem_wready),
    .bresp(dmem_bresp), .bvalid(dmem_bvalid), .bready(dmem_bready)
  );
`endif

  // 返回给 axi_lite_master 的应答多选（含未命中地址的 DECERR 兜底）已整体移入 axi_xbar。

  // ── IDU ──
  IDU u_idu (
    .inst(IR),
    .rs1(idu_rs1), .rs2(idu_rs2), .rd(idu_rd),
    .rs1_en(idu_unused_rs1_en), .rs2_en(idu_unused_rs2_en), .rd_en(idu_rd_en),
    .imm(idu_imm),
    .alu_op(idu_alu_op), .alu_src2_imm(idu_alu_src2_imm),
    .alu_en(idu_alu_en), .alu_src1_pc(idu_alu_src1_pc),
    .wb_sel(idu_wb_sel), .npc_sel(idu_npc_sel),
    .mem_re(idu_mem_re), .mem_we(idu_mem_we),
    .mem_width(idu_mem_width), .mem_signed(idu_mem_signed),
    .branch_type(idu_branch_type), .invalid(idu_invalid),
    .csr_idx(idu_csr_idx), .csr_wen(idu_csr_wen), .csr_s_w(idu_csr_s_w)
  );

  // ── 寄存器堆 ──
  RegisterFile #(.ADDR_WIDTH(5), .DATA_WIDTH(32)) u_regfile (
    .clk(clk),
    .w_data(wbu_wb_data), .w_addr(idu_rd),
    .r_addr1(idu_rs1), .r_addr2(idu_rs2),
    .wen(idu_rd_en && ctrl_reg_we),
    .r_data1(rf_rdata1), .r_data2(rf_rdata2), .r_a0(rf_unused_r_a0)
  );

  // ── EXU ──
  EXU u_exu (
    .rs1_data(rf_rdata1), .rs2_data(rf_rdata2),
    .imm(idu_imm), .alu_en(idu_alu_en), .alu_op(idu_alu_op),
    .alu_src2_imm(idu_alu_src2_imm), .alu_src1_pc(idu_alu_src1_pc),
    .pc(pc), .branch_type(idu_branch_type),
    .alu_result(exu_alu_result), .branch_taken(exu_branch_taken)
  );

  // ── WBU ──
  WBU u_wbu (
    .wb_sel(idu_wb_sel), .pc4(ifu_pc4),
    .alu_result(alu_result_r), .mem_data(lsu_rdata),
    .csr_data(csr_data), .imm(idu_imm),
    .wb_data(wbu_wb_data)
  );

  // ── CSRFile ──
  CSRFile #(.ADDR_WIDTH(12)) u_CSRFile (
    .clk(clk), .rst(rst), .at_state_wb(ctrl_at_state_wb),
    .csr_wen(idu_csr_wen), .csr_s_w(idu_csr_s_w),
    .ecall_trap(idu_npc_sel == `NPC_ECALL),
    .ebreak_trap(IR == 32'h00100073),
    .mret_exec(idu_npc_sel == `NPC_MRET),
    .irq_trap(irq_taken),                 
    .ecall_pc(trap_pc), .csr_wdata(rf_rdata1), .csr_idx(idu_csr_idx),
    .mstatus_mie(csr_mstatus_mie),     
    .csr_mtvec(csr_mtvec), .csr_mepc(csr_mepc), .csr_data(csr_data)
  );

  // ── 输出打包 ──
  assign halt      = (IR == 32'h00100073);
  assign ir_dbg    = IR;
  assign state_dbg = ctrl_state;
  assign aborted   = ctrl_abort;   // 非法指令/异常终止

  // ── MMIO 检测:供 difftest 跳过外设访问的比对 ──
  // xbar 判定本次访问是否落在 rtc/clint/uart 外设(xbar_mmio_sel), 标记本条指令为 MMIO。
  // EXE 阶段清零, MEM 阶段采样, 指令完成后 C++ 侧读取。
  reg mmio_flag_r;
  always @(posedge clk)
  begin
    if (rst)
    begin
      mmio_flag_r <= 1'b0;
    end
    else if (ctrl_state == `ST_EXE)
    begin
      mmio_flag_r <= 1'b0;
    end
    else if (ctrl_state == `ST_MEM)
    begin
      mmio_flag_r <= xbar_mmio_sel;
    end
  end
  assign mmio_dbg = mmio_flag_r;

endmodule
