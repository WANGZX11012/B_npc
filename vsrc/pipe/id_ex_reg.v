// id_ex_reg — ID/EX 段寄存器
//   结构和 if_id_reg 完全一样, 只是字段多。
//   存的是「ID 段译码出的控制信号 + 从 RF 读出的操作数值」。
module id_ex_reg (
  input  wire        clk,
  input  wire        rst,

// ID 段（IDU 控制信号 + RegisterFile 操作数）
  input  wire        id_valid,
  input  wire [31:0] id_pc,
  input  wire [31:0] id_inst,         //来自if id寄存器 传输 ID 段正在译码的指令
  input  wire [31:0] id_rs1_data,     // RF 读口 1 的值(将来是转发后的值)
  input  wire [31:0] id_rs2_data,     // RF 读口 2 的值
  input  wire [31:0] id_imm,
  input  wire [4:0]  id_rd,
  input  wire        id_rd_en,
  input  wire [3:0]  id_alu_op,
  input  wire        id_alu_en,
  input  wire        id_alu_src2_imm,
  input  wire        id_alu_src1_pc,
  input  wire [2:0]  id_npc_sel,
  input  wire [2:0]  id_branch_type,
  input  wire        id_mem_re,
  input  wire        id_mem_we,
  input  wire [1:0]  id_mem_width,
  input  wire        id_mem_signed,
  input  wire [2:0]  id_wb_sel,
  input  wire [11:0] id_csr_idx,
  input  wire        id_csr_wen,
  input  wire        id_csr_s_w,
  input  wire        id_fence_i,
  input  wire        id_invalid,
  output wire        id_ready,

  // ── 下游: EXU ──
  output reg         ex_valid,
  output reg  [31:0] ex_pc,
  output reg  [31:0] ex_inst,  // 继续传递inst
  output reg  [31:0] ex_rs1_data,
  output reg  [31:0] ex_rs2_data,
  output reg  [31:0] ex_imm,
  output reg  [4:0]  ex_rd,
  output reg         ex_rd_en,
  output reg  [3:0]  ex_alu_op,
  output reg         ex_alu_en,
  output reg         ex_alu_src2_imm,
  output reg         ex_alu_src1_pc,
  output reg  [2:0]  ex_npc_sel,
  output reg  [2:0]  ex_branch_type,
  output reg         ex_mem_re,
  output reg         ex_mem_we,
  output reg  [1:0]  ex_mem_width,
  output reg         ex_mem_signed,
  output reg  [2:0]  ex_wb_sel,
  output reg  [11:0] ex_csr_idx,
  output reg         ex_csr_wen,
  output reg         ex_csr_s_w,
  output reg         ex_fence_i,
  output reg         ex_invalid,
  input  wire        ex_ready,

  // ── 控制 ──
  input  wire        flush,
  input  wire        stall 
);

  assign id_ready = (!ex_valid || ex_ready) && !stall;   // 阻止取指令

  always @(posedge clk)
  begin
    if (rst || flush || stall) // stall的时候输出气泡
    begin
      ex_valid        <= 1'b0;
      ex_pc           <= 32'b0;
      ex_inst         <= 32'b0;
      ex_rs1_data     <= 32'b0;
      ex_rs2_data     <= 32'b0;
      ex_imm          <= 32'b0;
      ex_rd           <= 5'b0;
      ex_rd_en        <= 1'b0;
      ex_alu_op       <= 4'b0;
      ex_alu_en       <= 1'b0;
      ex_alu_src2_imm <= 1'b0;
      ex_alu_src1_pc  <= 1'b0;
      ex_npc_sel      <= 3'b0;
      ex_branch_type  <= 3'b0;
      ex_mem_re       <= 1'b0;
      ex_mem_we       <= 1'b0;
      ex_mem_width    <= 2'b0;
      ex_mem_signed   <= 1'b0;
      ex_wb_sel       <= 3'b0;
      ex_csr_idx      <= 12'b0;
      ex_csr_wen      <= 1'b0;
      ex_csr_s_w      <= 1'b0;
      ex_fence_i      <= 1'b0;
      ex_invalid      <= 1'b0;
    end
    else if (id_ready && !stall)
    begin
      ex_valid        <= id_valid;
      ex_pc           <= id_pc;
      ex_inst         <= id_inst;
      ex_rs1_data     <= id_rs1_data;
      ex_rs2_data     <= id_rs2_data;
      ex_imm          <= id_imm;
      ex_rd           <= id_rd;
      ex_rd_en        <= id_rd_en;
      ex_alu_op       <= id_alu_op;
      ex_alu_en       <= id_alu_en;
      ex_alu_src2_imm <= id_alu_src2_imm;
      ex_alu_src1_pc  <= id_alu_src1_pc;
      ex_npc_sel      <= id_npc_sel;
      ex_branch_type  <= id_branch_type;
      ex_mem_re       <= id_mem_re;
      ex_mem_we       <= id_mem_we;
      ex_mem_width    <= id_mem_width;
      ex_mem_signed   <= id_mem_signed;
      ex_wb_sel       <= id_wb_sel;
      ex_csr_idx      <= id_csr_idx;
      ex_csr_wen      <= id_csr_wen;
      ex_csr_s_w      <= id_csr_s_w;
      ex_fence_i      <= id_fence_i;
      ex_invalid      <= id_invalid;
    end
  end

endmodule
