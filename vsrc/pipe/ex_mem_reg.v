`include "npc_defs.vh"

// ex_mem_reg — EX/MEM 段寄存器（流水线版）
//   与旧的 EX_MEM.v 的根本区别:
//     旧: busy_r / done_r 三步式, 一条指令占住 3 拍以上, 直到 WB 收走
//     新: valid 单步式, 每拍都能换一条新指令
module ex_mem_reg (
  input  wire        clk,
  input  wire        rst,

  // ── 上游: EX 段 ──
    input  wire        ex_valid,
    input  wire [31:0] ex_pc,
    input  wire [31:0] ex_inst,         // 本指令编码
    input  wire [31:0] ex_alu_result,   // EXU 的结果; 访存时是地址
    input  wire [31:0] ex_rs1_data,     // CSR 写数据
    input  wire [31:0] ex_rs2_data,     // store 的写数据
    input  wire [31:0] ex_imm,          // WBU 的 WB_IMM(lui) 要用
    input  wire [4:0]  ex_rd,
    input  wire        ex_rd_en,
    input  wire        ex_mem_re,
    input  wire        ex_mem_we,
    input  wire [1:0]  ex_mem_width,
    input  wire        ex_mem_signed,
    input  wire [2:0]  ex_wb_sel,
    input  wire [11:0] ex_csr_idx,
    input  wire        ex_csr_wen,
    input  wire        ex_csr_s_w,
    input  wire        ex_invalid,
    output wire        ex_ready,    
    // ── 下游: MEM 段 ──
    output reg         mem_valid,
    output reg  [31:0] mem_pc,
    output reg  [31:0] mem_inst,        // 本指令编码
    output reg  [31:0] mem_alu_result,
    output reg  [31:0] mem_rs2_data,
    output reg  [31:0] mem_rs1_data,
    output reg  [31:0] mem_imm,
    output reg  [4:0]  mem_rd,
    output reg         mem_rd_en,
    output reg         mem_re,
    output reg         mem_we,
    output reg  [1:0]  mem_width,
    output reg         mem_signed,
    output reg  [2:0]  mem_wb_sel,
    output reg  [11:0] mem_csr_idx,
    output reg         mem_csr_wen,
    output reg         mem_csr_s_w,
    output reg         mem_invalid,
    input  wire        mem_ready,       // 由 core 选: 访存看 lsu_in_ready, 非访存看 memwb_ready

  // ── 控制 ──
  input  wire        flush            // 分支不用它, 先接 0
);

    assign ex_ready = !mem_valid || mem_ready;

    always @(posedge clk)
    begin
        if (rst || flush)
        begin
          mem_valid      <= 1'b0;
          mem_pc         <= 32'b0;
          mem_inst       <= 32'b0;      // 冲刷时清气泡
          mem_alu_result <= 32'b0;
          mem_rs2_data   <= 32'b0;
          mem_rs1_data   <= 32'b0;
          mem_imm        <= 32'b0;
          mem_rd         <= 5'b0;
          mem_rd_en      <= 1'b0;
          mem_re         <= 1'b0;
          mem_we         <= 1'b0;
          mem_width      <= 2'b0;
          mem_signed     <= 1'b0;
          mem_wb_sel     <= 3'b0;
          mem_csr_idx    <= 12'b0;
          mem_csr_wen    <= 1'b0;
          mem_csr_s_w    <= 1'b0;
          mem_invalid    <= 1'b0;
        end
        else if (ex_ready)
        begin
          mem_valid      <= ex_valid;
          mem_pc         <= ex_pc;
          mem_inst       <= ex_inst;    // 与 valid 同拍
          mem_alu_result <= ex_alu_result;
          mem_rs2_data   <= ex_rs2_data;
          mem_rs1_data   <= ex_rs1_data;
          mem_imm        <= ex_imm;
          mem_rd         <= ex_rd;
          mem_rd_en      <= ex_rd_en;
          mem_re         <= ex_mem_re;
          mem_we         <= ex_mem_we;
          mem_width      <= ex_mem_width;
          mem_signed     <= ex_mem_signed;
          mem_wb_sel     <= ex_wb_sel;
          mem_csr_idx    <= ex_csr_idx;
          mem_csr_wen    <= ex_csr_wen;
          mem_csr_s_w    <= ex_csr_s_w;
          mem_invalid    <= ex_invalid;
        end
    end

endmodule
