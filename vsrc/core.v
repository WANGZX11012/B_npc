`include "npc_defs.vh"

module core (
  input  wire         clk,
  input  wire         reset,
  output wire [31:0]  pc,
  output wire         halt      // ebreak 时拉高
);

  assign halt = (IR == 32'h00100073);

  // ── 总线 ──
  wire [31:0] pc4;
  wire [31:0] ifu_raddr, ifu_rdata;
  wire        ifu_reqValid, ifu_respValid, ifu_done;
  wire [31:0] lsu_addr, lsu_wdata, lsu_rdata, mem_rdata;
  wire        lsu_reqValid, lsu_wen, lsu_respValid, lsu_done;
  wire [3:0]  lsu_wmask;
  wire [4:0]  rs1, rs2, rd;
  wire        rd_en;
  wire [31:0] imm, csr_data, r_data1, r_data2, alu_result, wb_data;
  wire [3:0]  alu_op;
  wire        alu_src2_imm, alu_en, alu_src1_pc;
  wire [11:0] csr_idx;
  wire        csr_wen, csr_s_w;
  wire [31:0] csr_mtvec, csr_mepc;
  wire [2:0]  wb_sel, npc_sel;
  wire        mem_re, mem_we;
  wire [1:0]  mem_width;
  wire        mem_signed;
  wire [2:0]  branch_type;
  wire        idu_invalid, branch_taken;
  wire [2:0]  ctrl_state;
  wire        ctrl_ir_we, ctrl_pc_we, ctrl_reg_we, ctrl_fetch_req, ctrl_mem_req;
  wire        _unused_rs1_en, _unused_rs2_en, _unused_r_a0;

  // ── IFU ──
  IFU u_ifu (
    .clk(clk), .reset(reset),
    .pc_we(ctrl_pc_we), .fetch_req(ctrl_fetch_req),
    .alu_result(alu_result), .npc_sel(npc_sel),
    .branch_taken(branch_taken),
    .csr_mtvec(csr_mtvec), .csr_mepc(csr_mepc),
    .pc(pc), .pc4(pc4),
    .ifu_raddr(ifu_raddr), .ifu_reqValid(ifu_reqValid),
    .ifu_rdata(ifu_rdata), .ifu_respValid(ifu_respValid),
    .ifu_done(ifu_done)
  );

  // ── 指令内存 ──
  inst_mem u_imem (
    .clk(clk), .addr(ifu_raddr), .reqValid(ifu_reqValid),
    .rdata(ifu_rdata), .respValid(ifu_respValid)
  );

  // ── 控制器 ──
  ctrl u_ctrl (
    .clk(clk), .rst(reset),
    .idu_mem_re(mem_re), .idu_mem_we(mem_we),
    .ifu_done(ifu_done), .lsu_done(lsu_done),
    .state(ctrl_state),
    .ir_we(ctrl_ir_we), .pc_we(ctrl_pc_we), .reg_we(ctrl_reg_we),
    .fetch_req(ctrl_fetch_req), .mem_req(ctrl_mem_req)
  );

  // ── IR ──
  reg [31:0] IR;
  always @(posedge clk)
    if (ctrl_ir_we) IR <= ifu_rdata;

  // ── ALU 结果锁存 ──
  reg [31:0] alu_out;
  always @(posedge clk)
    if (ctrl_state == `NPC_EXE) alu_out <= alu_result;

  // ── LSU（访存控制器） ──
  LSU u_lsu (
    .clk(clk),
    .mem_req(ctrl_mem_req),
    .mem_re(mem_re), .mem_we(mem_we),
    .mem_width(mem_width), .mem_signed(mem_signed),
    .wdata_in(r_data2), .addr_in(alu_out),
    .lsu_reqValid(lsu_reqValid), .lsu_addr(lsu_addr),
    .lsu_wen(lsu_wen), .lsu_wdata(lsu_wdata), .lsu_wmask(lsu_wmask),
    .lsu_rdata(lsu_rdata), .lsu_respValid(lsu_respValid),
    .lsu_done(lsu_done),
    .rdata(mem_rdata)
  );

  // ── 数据内存（SimpleBus 从设备） ──
  data_mem u_dmem (
    .clk(clk), .reqValid(lsu_reqValid),
    .addr(lsu_addr), .wen(lsu_wen),
    .wdata(lsu_wdata), .wmask(lsu_wmask),
    .rdata(lsu_rdata), .respValid(lsu_respValid)
  );

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
    .clk(clk), .reset(reset),
    .csr_wen(csr_wen), .csr_s_w(csr_s_w),
    .ecall_trap(npc_sel == `NPC_ECALL),
    .ebreak_trap(IR == 32'h00100073),
    .mret_exec(npc_sel == `NPC_MRET),
    .ecall_pc(pc), .csr_wdata(r_data1), .csr_idx(csr_idx),
    .csr_mtvec(csr_mtvec), .csr_mepc(csr_mepc), .csr_data(csr_data)
  );

endmodule
