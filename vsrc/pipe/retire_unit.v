`include "npc_defs.vh"

// retire_unit — 退休观测单元
//   WB 段是流水线的终点, 这里把「本拍有没有一条指令真正退休」换算成
//   给 monitor / 顶层端口的四样东西:
//     pc               架构 PC(只在退休时 +4, 气泡不计)
//     inst_retire      退休事件(打一拍给 C++ 的 npc_exec_inst 循环)
//     retire_inst_dbg  退休指令快照(IR 下一拍就被覆盖, 必须当场拍照)
//     halt             ebreak 到 WB 后锁存, 保持到复位
//
//   ★ C++ 侧 g_nr_inst 按「pc 变了」计数, 所以气泡天然不被计入;
//     气泡占的时钟由 npc_cycle() 吃掉, 只让 cycles 增加。
//     这就是为什么 pc 必须由 retire 门控, 不能跟着取指 PC 走。
module retire_unit (
  input  wire        clk,
  input  wire        rst,

  // ── ← WB 段 ──
  input  wire        wb_valid,
  input  wire [31:0] wb_inst,
  input  wire [31:0] wb_pc,

  // ── → top / monitor ──
  output wire [31:0] pc,
  output wire        halt,
  output wire [31:0] retire_inst_dbg,
  output reg         inst_retire
);

  localparam [31:0] EBREAK_INST   = 32'h00100073;
  localparam [31:0] ARCH_RESET_PC = 32'h8000_0000;

  wire        wb_ebreak = wb_valid && (wb_inst == EBREAK_INST);
  wire        retire    = wb_valid && !wb_ebreak && !halt_r;

  reg  [31:0] arch_pc;
  reg  [31:0] retire_inst_r;
  reg         halt_r;

  assign pc              = arch_pc;
  assign halt            = halt_r;
  assign retire_inst_dbg = retire_inst_r;

  // 退休事件打一拍输出给 monitor
  always @(posedge clk)
    inst_retire <= retire;              // ebreak 不算退休

  always @(posedge clk)
    if (rst)          arch_pc <= ARCH_RESET_PC;
    else if (retire)  arch_pc <= wb_pc + 32'd4;   // 退休才前进

  always @(posedge clk)
    if (rst)          retire_inst_r <= 32'b0;
    else if (retire)  retire_inst_r <= wb_inst;

  always @(posedge clk)
    if (rst)            halt_r <= 1'b0;
    else if (wb_ebreak) halt_r <= 1'b1;   // 锁存到复位, 不会只闪一拍

endmodule
