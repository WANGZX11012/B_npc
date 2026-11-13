`include "npc_defs.vh"

// mem_wb_reg — MEM/WB 段寄存器
//   WB 段是最后一级：写 RF、写 CSR、判定退休。
//   数据来源: ALU 结果 / 访存数据 / CSR 读值 / 立即数(lui)
module mem_wb_reg (
  input  wire        clk,
  input  wire        rst,

  // ── 上游: MEM 段 ──
  input  wire        mem_valid,
  input  wire [31:0] mem_pc,
  input  wire [31:0] mem_inst,      // 本指令编码
  input  wire [31:0] mem_alu_result,
  // 命名约定: 前缀 mem_ / wb_ 是"级名"(MEM 段输入 / WB 段输出), 后面才是字段语义。
  //   mem_mem_data = mem_(级) + mem_data(访存读回数据, 对应 WBU.mem_data), 两个 mem 含义不同;
  //   与 wb_mem_data 是同一份数据的"寄存前 / 寄存后"两个节点, 不是同一根线。
  //   该数据在 MEM 段才由 LSU 产生, 故 ex_mem_reg 中没有对应字段。
  input  wire [31:0] mem_mem_data,     // ← lsu_rdata_out, 非访存指令为 0
  input  wire [31:0] mem_csr_data,     // ← CSRFile 读口(MEM 段读)
  input  wire [31:0] mem_rs1_data,     // ← CSR 写数据
  input  wire [31:0] mem_imm,          // ← WB_IMM(lui)
  input  wire [2:0]  mem_wb_sel,
  input  wire [4:0]  mem_rd,
  input  wire        mem_rd_en,
  input  wire [11:0] mem_csr_idx,
  input  wire        mem_csr_wen,
  input  wire        mem_csr_s_w,
  input  wire        mem_invalid,
  output wire        mem_ready,

  // ── 下游: WB 段 ──
  output reg         wb_valid,
  output reg  [31:0] wb_pc,
  output reg  [31:0] wb_inst,       // 本指令编码
  output reg  [31:0] wb_alu_result,
  output reg  [31:0] wb_mem_data,
  output reg  [31:0] wb_csr_data,
  output reg  [31:0] wb_rs1_data,
  output reg  [31:0] wb_imm,
  output reg  [2:0]  wb_wb_sel,
  output reg  [4:0]  wb_rd,
  output reg         wb_rd_en,
  output reg  [11:0] wb_csr_idx,
  output reg         wb_csr_wen,
  output reg         wb_csr_s_w,
  output reg         wb_invalid,
  input  wire        wb_ready,         // WB 是最后一级, 接 1'b1  因为不用等下一个设备 直接写入

  // ── 控制 ──
  input  wire        flush,             // 简单流水线接 0
  input  wire        mem_stall
);

  assign mem_ready = (!wb_valid || wb_ready) && !mem_stall;

  always @(posedge clk)
  begin
    if (rst || flush || mem_stall)// 冲刷 以及等待返回数据时清气泡
    begin
      wb_valid      <= 1'b0;
      wb_pc         <= 32'b0;
      wb_inst       <= 32'b0;      
      wb_alu_result <= 32'b0;
      wb_mem_data   <= 32'b0;
      wb_csr_data   <= 32'b0;
      wb_rs1_data   <= 32'b0;
      wb_imm        <= 32'b0;
      wb_wb_sel     <= 3'b0;
      wb_rd         <= 5'b0;
      wb_rd_en      <= 1'b0;
      wb_csr_idx    <= 12'b0;
      wb_csr_wen    <= 1'b0;
      wb_csr_s_w    <= 1'b0;
      wb_invalid    <= 1'b0;
    end
    else if (mem_ready)
    begin
      wb_valid      <= mem_valid;
      wb_pc         <= mem_pc;
      wb_inst       <= mem_inst;    // 与 valid 同拍
      wb_alu_result <= mem_alu_result;
      wb_mem_data   <= mem_mem_data;
      wb_csr_data   <= mem_csr_data;
      wb_rs1_data   <= mem_rs1_data;
      wb_imm        <= mem_imm;
      wb_wb_sel     <= mem_wb_sel;
      wb_rd         <= mem_rd;
      wb_rd_en      <= mem_rd_en;
      wb_csr_idx    <= mem_csr_idx;
      wb_csr_wen    <= mem_csr_wen;
      wb_csr_s_w    <= mem_csr_s_w;
      wb_invalid    <= mem_invalid;
    end
  end

endmodule
