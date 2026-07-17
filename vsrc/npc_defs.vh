`ifndef NPC_DEFS_VH
`define NPC_DEFS_VH

// 关闭 linter 误报（不影响语法检查）
/* verilator lint_off UNUSED */
/* verilator lint_off UNDRIVEN */

// 访存宽度编码（IDU/LSU 共用，避免到处写魔法数）
`define MEM_BYTE 2'b00
`define MEM_HALF 2'b01
`define MEM_WORD 2'b10

// 写回来源编码（IDU/WBU 共用）
`define WB_ALU 3'b000
`define WB_PC4 3'b001
`define WB_MEM 3'b010
`define WB_IMM 3'b011
`define WB_CSR 3'b100

// ALU 操作编码（IDU/EXU 共用）
`define ALU_ADD  4'b0000
`define ALU_SUB  4'b0001
`define ALU_AND  4'b0010
`define ALU_OR   4'b0011
`define ALU_XOR  4'b0100
`define ALU_SLT  4'b0101
`define ALU_SLTU 4'b0110
`define ALU_SLL  4'b0111
`define ALU_SRL  4'b1000
`define ALU_SRA  4'b1001

// Next-PC / 跳转选择编码
`define NPC_PC4   3'b000
`define NPC_JALR  3'b001
`define NPC_JAL   3'b010
`define NPC_BR    3'b011
`define NPC_ECALL 3'b100
`define NPC_MRET  3'b101 

// 多周期状态编码（ctrl.v / core.v 共用）
`define NPC_IDLE  3'd0
`define NPC_FET   3'd1
`define NPC_DEC   3'd2
`define NPC_EXE   3'd3
`define NPC_MEM   3'd4
`define NPC_WB    3'd5

// 分支类型编码
`define BR_NONE 3'b000
`define BR_BEQ  3'b110
`define BR_BNE  3'b001
`define BR_BGE  3'b010
`define BR_BGEU 3'b011
`define BR_BLT  3'b100
`define BR_BLTU 3'b101
// `BR_BEQ` already defined above; duplicate removed

`endif
