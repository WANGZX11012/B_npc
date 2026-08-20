`include "npc_defs.vh"

module core (
  input  wire         clk,
  input  wire         rst,
  output wire [31:0]  pc,
  output wire         halt,       // ebreak 时拉高
  output wire         aborted,    // 非法指令/异常终止(对齐 NEMU_ABORT)
  output wire [31:0]  ir_dbg,     // IR for monitor
  output wire [2:0]   state_dbg,  // ctrl_state for monitor
  output wire         mmio_dbg    // 本条指令是否访问了外设(供 difftest 跳过比对)
);

  assign halt = (IR == 32'h00100073);

  // ═══════════════ IFU 私有请求接口 ═══════════════
  wire [31:0] pc4;
  wire [31:0] inst;
  wire        ifu_done;
  wire        ifu_req_valid;
  wire [31:0] ifu_req_addr;
  wire        ifu_handshake_done;    // arbiter → IFU
  wire [31:0] ifu_resp_rdata;

  // ═══════════════ LSU 私有请求接口 ═══════════════
  wire        lsu_req_valid;
  wire [31:0] lsu_req_addr;
  wire [31:0] lsu_req_wdata;
  wire [3:0]  lsu_req_wmask;
  wire        lsu_handshake_done;    // arbiter → LSU
  wire [31:0] lsu_resp_rdata;
  wire        lsu_done;
  wire [31:0] mem_rdata;

  // ═══════════════ arbiter → 唯一 axi_lite_master ═══════════════
  wire        m_req_valid;
  wire        m_req_we;
  wire [31:0] m_req_addr;
  wire [31:0] m_req_wdata;
  wire [3:0]  m_req_wstrb;
  wire        m_done;
  wire [31:0] m_resp_rdata;

  // ═══════════════ 合并后的 AXI4-Lite 五通道 ═══════════════
  wire [31:0] m_araddr, m_awaddr, m_wdata, m_rdata;
  wire        m_arvalid, m_arready, m_rvalid, m_rready;
  wire [1:0]  m_rresp;
  wire        m_awvalid, m_awready, m_wvalid, m_wready;
  wire [3:0]  m_wmask;
  wire [1:0]  m_bresp;
  wire        m_bvalid, m_bready;

  // ═══════════════ LFSR 随机停顿 ═══════════════
  wire [7:0]  lfsr_val;
  wire        bus_stall;

  // ═══════════════ IDU → 各模块 ═══════════════
  wire [4:0]  rs1, rs2, rd;
  wire        rd_en;
  wire [31:0] imm;
  wire [3:0]  alu_op;
  wire        alu_src2_imm, alu_en, alu_src1_pc;
  wire [2:0]  wb_sel, npc_sel;
  wire        mem_re, mem_we;
  wire [1:0]  mem_width;
  wire        mem_signed;
  wire [2:0]  branch_type;
  wire        idu_invalid;

  // ═══════════════ 寄存器堆 / EXU / WBU ═══════════════
  wire [31:0] r_data1, r_data2, alu_result, wb_data;
  wire        branch_taken;

  // ═══════════════ CSR ═══════════════
  wire [31:0] csr_data, csr_mtvec, csr_mepc;
  wire [11:0] csr_idx;
  wire        csr_wen, csr_s_w;

  // ═══════════════ ctrl 信号 ═══════════════
  wire [2:0]  ctrl_state;
  wire        ctrl_ir_we, ctrl_pc_we, ctrl_reg_we, ctrl_fetch_req, ctrl_mem_req;
  wire        ctrl_abort;

  // ═══════════════ 未用端口 ═══════════════
  wire        _unused_rs1_en, _unused_rs2_en, _unused_r_a0;

  // ── IFU ── 私有请求接口接 arbiter
  IFU u_ifu (
    .clk(clk), .rst(rst),
    .pc_we(ctrl_pc_we), .fetch_req(ctrl_fetch_req),
    .alu_result(alu_result), .npc_sel(npc_sel),
    .branch_taken(branch_taken),
    .csr_mtvec(csr_mtvec), .csr_mepc(csr_mepc),
    .req_valid(ifu_req_valid),
    .req_addr(ifu_req_addr),
    .handshake_done(ifu_handshake_done),
    .resp_rdata(ifu_resp_rdata),
    .pc(pc), .pc4(pc4), .inst(inst),
    .ifu_done(ifu_done)
  );

 // ── LSU（访存控制器：私有请求 → arbiter）──
  LSU u_lsu (
    .clk(clk), .rst(rst),
    .mem_req(ctrl_mem_req),
    .mem_re(mem_re), .mem_we(mem_we),
    .mem_width(mem_width), .mem_signed(mem_signed),
    .wdata_in(r_data2), .addr_in(alu_out),
    .rdata_in(lsu_resp_rdata),
    .handshake_done(lsu_handshake_done),
    .req_valid(lsu_req_valid),
    .req_addr(lsu_req_addr),
    .req_wdata(lsu_req_wdata),
    .req_wmask(lsu_req_wmask),
    .lsu_done(lsu_done),
    .rdata_out(mem_rdata)
  );


  // ── 仲裁器：IFU/LSU 两个 master 合并成一路（IFU 固定优先）──
  arbiter u_arb (
    .clk(clk), .rst(rst),
    .ifu_req_valid(ifu_req_valid), .ifu_req_addr(ifu_req_addr),
    .ifu_done(ifu_handshake_done), .ifu_resp_rdata(ifu_resp_rdata),
    .lsu_req_valid(lsu_req_valid), .lsu_req_we(mem_we),
    .lsu_req_addr(lsu_req_addr), .lsu_req_wdata(lsu_req_wdata),
    .lsu_req_wstrb(lsu_req_wmask),
    .lsu_done(lsu_handshake_done), .lsu_resp_rdata(lsu_resp_rdata),
    .m_req_valid(m_req_valid), .m_req_we(m_req_we),
    .m_req_addr(m_req_addr), .m_req_wdata(m_req_wdata),
    .m_req_wstrb(m_req_wstrb),
    .m_done(m_done), .m_resp_rdata(m_resp_rdata)
  );

  // ── 唯一的 AXI4-Lite 协议适配层（IFU 读 / LSU 读写 共用）──
  axi_lite_master u_master (
    .clk(clk), .rst(rst),
    .req_valid(m_req_valid), .req_we(m_req_we),
    .req_addr(m_req_addr), .req_wdata(m_req_wdata), .req_wstrb(m_req_wstrb),
    .stall(bus_stall),
    .done(m_done), .resp_rdata(m_resp_rdata),
    // AR
    .araddr(m_araddr), .arvalid(m_arvalid), .arready(m_arready),
    // R
    .rdata(m_rdata), .rvalid(m_rvalid), .rresp(m_rresp), .rready(m_rready),
    // AW
    .awaddr(m_awaddr), .awvalid(m_awvalid), .awready(m_awready),
    // W
    .wdata(m_wdata), .wvalid(m_wvalid), .wmask(m_wmask), .wready(m_wready),
    // B
    .bresp(m_bresp), .bvalid(m_bvalid), .bready(m_bready)
  );

  // ── LFSR:每拍推进, 按阈值产生随机总线停顿 ──
  // lfsr 输出 1~255(不含 0), 阈值 16 → 约 1/16 概率停一拍
  lfsr u_lfsr (
    .clk (clk),
    .rst (rst),
    .en  (1'b1),
    .val (lfsr_val)
  );
  assign bus_stall = (lfsr_val < 8'd16); //小于16就stall




  // ── 控制器 ──
  ctrl u_ctrl (
    .clk(clk), .rst(rst),
    .idu_mem_re(mem_re), .idu_mem_we(mem_we),
    .idu_invalid(idu_invalid),
    .ifu_done(ifu_done), .lsu_done(lsu_done),
    .state(ctrl_state),
    .ir_we(ctrl_ir_we), .pc_we(ctrl_pc_we), .reg_we(ctrl_reg_we),
    .fetch_req(ctrl_fetch_req), .mem_req(ctrl_mem_req),
    .aborted(ctrl_abort)
  );



  // ── IR ──
  reg [31:0] IR;
  reg [31:0] ir_pc;          // 锁存当前指令的 PC, 供 ecall/mret 作为 mepc 基准
  always @(posedge clk)
  begin
    if (ctrl_ir_we) IR    <= inst;
    if (ctrl_ir_we) ir_pc <= pc;   // pc 此时为刚取到的指令地址(FET 阶段未前进)
  end

  // ── ALU 结果锁存 ──
  reg [31:0] alu_out;
  always @(posedge clk)
    if (ctrl_state == `NPC_EXE) alu_out <= alu_result;


  // ── 外设段判断：0xa00000xx 是 RTC 外设段 ──
  wire rtc_sel = (m_araddr[31:8] == 24'ha00000);

  // ── RTC 从设备（墙钟只读）──
  wire        rtc_arready, rtc_rvalid;
  wire [31:0] rtc_rdata;
  wire [1:0]  rtc_rresp;
  rtc u_rtc (
    .clk    (clk),
    .araddr (m_araddr),
    .arvalid(m_arvalid && rtc_sel),
    .arready(rtc_arready),
    .rdata  (rtc_rdata),
    .rresp  (rtc_rresp),
    .rvalid (rtc_rvalid),
    .rready (m_rready)
  );

  // ── UART 段判断：0xa00003f0 ~ 0xa00003ff（串口 0xa00003f8）──
  wire uart_sel = (m_araddr[31:4] == 28'ha00003f) || (m_awaddr[31:4] == 28'ha00003f);

  // ── UART 从设备（串口，写打印 / 读返回 0）──
  wire        uart_arready, uart_rvalid;
  wire [31:0] uart_rdata;
  wire [1:0]  uart_rresp;
  wire        uart_awready, uart_wready, uart_bvalid;
  wire [1:0]  uart_bresp;
  uart u_uart (
    .clk    (clk),
    .araddr (m_araddr), .arvalid(m_arvalid && uart_sel), .arready(uart_arready),
    .rdata  (uart_rdata), .rresp(uart_rresp), .rvalid(uart_rvalid), .rready(m_rready),
    .awaddr (m_awaddr),
    .awvalid(m_awvalid && uart_sel),
    .awready(uart_awready),
    .wdata  (m_wdata),
    .wmask  (m_wmask),
    .wvalid (m_wvalid && uart_sel),
    .wready (uart_wready),
    .bresp  (uart_bresp),
    .bvalid (uart_bvalid),
    .bready (m_bready)
  );

  // ── 统一内存（取指 + 访存共用同一个 pmem 从设备）──
  wire        dmem_arready, dmem_rvalid, dmem_awready, dmem_wready, dmem_bvalid;
  wire [31:0] dmem_rdata;
  wire [1:0]  dmem_rresp, dmem_bresp;
`ifdef DPI_MEM
  // DPI 模式: 取指/访存经 DPI-C 读写 NEMU pmem, 只保留一个实例。
  // pmem 段 = 0x80000000~0x87FFFFFF (128MB), IFU 取指地址与 LSU 访存地址都落在此段,
  // 故都路由到同一个 dpic_mem。
  // mmio(uart/rtc) 在 0xa00000xx, 不在此范围, 由 uart_sel/rtc_sel 单独路由。
  wire pmem_sel = (m_araddr[31:24] >= 8'h80) && (m_araddr[31:24] <= 8'h87);
  dpic_mem u_mem (
    .clk(clk),
    .araddr(m_araddr), .arvalid(m_arvalid && pmem_sel), .arready(dmem_arready),
    .rdata(dmem_rdata), .rresp(dmem_rresp), .rvalid(dmem_rvalid), .rready(m_rready),
    .awaddr(m_awaddr), .awvalid(m_awvalid && pmem_sel), .awready(dmem_awready),
    .wdata(m_wdata), .wmask(m_wmask), .wvalid(m_wvalid && pmem_sel), .wready(dmem_wready),
    .bresp(dmem_bresp), .bvalid(dmem_bvalid), .bready(m_bready)
  );
`else
  // 非 DPI 模式: 用一块 data_mem(读写)同时服务取指与访存, inst_mem 已并入。
  data_mem u_mem (                  // delay from menuconfig
    .clk(clk),
    .araddr(m_araddr), .arvalid(m_arvalid && !rtc_sel && !uart_sel), .arready(dmem_arready),
    .rdata(dmem_rdata), .rresp(dmem_rresp), .rvalid(dmem_rvalid), .rready(m_rready),
    .awaddr(m_awaddr), .awvalid(m_awvalid && !uart_sel), .awready(dmem_awready),
    .wdata(m_wdata), .wmask(m_wmask), .wvalid(m_wvalid && !uart_sel), .wready(dmem_wready),
    .bresp(dmem_bresp), .bvalid(dmem_bvalid), .bready(m_bready)
  );
`endif

  // ── 返回给 axi_lite_master 的信号按段多选 ──
  // 读:rtc/uart mmio 段走各自设备, 其余(pmem)走统一内存
  assign m_arready = uart_sel ? uart_arready : (rtc_sel ? rtc_arready : dmem_arready);
  assign m_rvalid  = uart_sel ? uart_rvalid  : (rtc_sel ? rtc_rvalid  : dmem_rvalid);
  assign m_rdata   = uart_sel ? uart_rdata   : (rtc_sel ? rtc_rdata   : dmem_rdata);
  assign m_rresp   = uart_sel ? uart_rresp   : (rtc_sel ? rtc_rresp   : dmem_rresp);
  assign m_awready = uart_sel ? uart_awready : dmem_awready;
  assign m_wready  = uart_sel ? uart_wready  : dmem_wready;
  assign m_bresp   = uart_sel ? uart_bresp   : dmem_bresp;
  assign m_bvalid  = uart_sel ? uart_bvalid  : dmem_bvalid;

  // ── IDU ──
  IDU u_idu (
    .inst(IR),
    .rs1(rs1), .rs2(rs2), .rd(rd),
    .rs1_en(_unused_rs1_en), .rs2_en(_unused_rs2_en), .rd_en(rd_en),
    .imm(imm),
    .alu_op(alu_op), .alu_src2_imm(alu_src2_imm),
    .alu_en(alu_en), .alu_src1_pc(alu_src1_pc),
    .wb_sel(wb_sel), .npc_sel(npc_sel),
    .mem_re(mem_re), .mem_we(mem_we),
    .mem_width(mem_width), .mem_signed(mem_signed),
    .branch_type(branch_type), .invalid(idu_invalid),
    .csr_idx(csr_idx), .csr_wen(csr_wen), .csr_s_w(csr_s_w)
  );




  // ── 寄存器堆 ──
  RegisterFile #(.ADDR_WIDTH(5), .DATA_WIDTH(32)) u_regfile (
    .clk(clk),
    .w_data(wb_data), .w_addr(rd),
    .r_addr1(rs1), .r_addr2(rs2),
    .wen(rd_en && ctrl_reg_we),
    .r_data1(r_data1), .r_data2(r_data2), .r_a0(_unused_r_a0)
  );

  // ── EXU ──
  EXU u_exu (
    .rs1_data(r_data1), .rs2_data(r_data2),
    .imm(imm), .alu_en(alu_en), .alu_op(alu_op),
    .alu_src2_imm(alu_src2_imm), .alu_src1_pc(alu_src1_pc),
    .pc(pc), .branch_type(branch_type),
    .alu_result(alu_result), .branch_taken(branch_taken)
  );

  // ── WBU ──
  WBU u_wbu (
    .wb_sel(wb_sel), .pc4(pc4),
    .alu_result(alu_out), .mem_data(mem_rdata),
    .csr_data(csr_data), .imm(imm),
    .wb_data(wb_data)
  );

  // ── CSRFile ──
  CSRFile #(.ADDR_WIDTH(12)) u_CSRFile (
    .clk(clk), .rst(rst),
    .csr_wen(csr_wen), .csr_s_w(csr_s_w),
    .ecall_trap(npc_sel == `NPC_ECALL),
    .ebreak_trap(IR == 32'h00100073),
    .mret_exec(npc_sel == `NPC_MRET),
    .ecall_pc(ir_pc), .csr_wdata(r_data1), .csr_idx(csr_idx),
    .csr_mtvec(csr_mtvec), .csr_mepc(csr_mepc), .csr_data(csr_data)
  );

  assign ir_dbg    = IR;
  assign state_dbg = ctrl_state;
  assign aborted   = ctrl_abort;   // 非法指令/异常终止

  // ── MMIO 检测:供 difftest 跳过外设访问的比对 ──
  // 一条指令访问 rtc/uart 外设时(rtc_sel 或 uart_sel), 标记本条指令为 MMIO。
  // EXE 阶段清零, MEM 阶段采样, 指令完成后 C++ 侧读取。
  reg mmio_flag;
  always @(posedge clk)
  begin
    if (rst)         mmio_flag <= 1'b0;
    else if (ctrl_state == `NPC_EXE) mmio_flag <= 1'b0;
    else if (ctrl_state == `NPC_MEM) mmio_flag <= (rtc_sel || uart_sel);
  end
  assign mmio_dbg = mmio_flag;

endmodule
