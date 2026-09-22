// stage_dec — 相位译码器(纯组合观测器)
`include "npc_defs.vh"

// 干什么: 把各段上报的"我现在在干什么"翻译成一个 3bit 相位号, 只给 state_dbg / sdb 看。
// 不干什么: 不产生任何控制信号。没有 clk, 没有 reg, 没有 FSM —— 它不能"决定"任何事,
//           只能"描述"当前这一拍机器处在哪个相位。这就是把它从 ctrl 改过来的全部意义:
//           ctrl 当年是拿 state 去驱动 pc_we/reg_we/fetch_req/mem_req 的, 那些腿已全部
//           被各自的模块(IFU/EX_MEM/LSU)接管, 剩下的只有一个"我现在是哪一拍"的问题。
//
// 为什么必须纯组合: 只要它有时序, 就存在"它以为的相位"和"真实的握手状态"对不上的可能
//           (少一拍 / 多一拍), 而这个错位又会反过来被拿去当控制用 —— 分布式握手的前提是
//           **相位是观测结果, 不是原因**。
module stage_dec (

  // Reset(只用于复位期间显示 IDLE, 不产生时序)
  input  wire         rst,

  // 输入: 各段自己上报的相位事实
  input  wire         ifu_out_valid,   // IFU: 我手里攥着一条取回的指令
  input  wire         ex_stage_fire,   // EX_MEM: 本拍正在把 EXU 结果锁进来
  input  wire         mem_active,      // LSU: 访存单已下、结果还没回来
  input  wire         retire,          // WB: 本拍退休
  input  wire         aborted,         // core: 已停机(粘住的 aborted_r)

  // 输出: 当前相位(仅供观测, 禁止任何模块拿去当控制)
  output wire  [2:0]  state
);

  // ── 相位判决: 从最具体的事实往兜底排, 各条件天然互斥 ──
  //   优先级即书写顺序: 停机 > 退休 > 等总线 > 执行 > 译码 > 取指
  //   互斥性说明:
  //     retire 需要 lsu_res_valid, mem_active 需要 !lsu_res_valid → 二者不同时成立
  //     ex_stage_fire 是 busy&&!done, 而 retire/mem_active 都要求 done → 不同时成立
  //     ifu_out_valid 在整条指令期间恒为 1, 所以只能放最后当兜底前的最后一档
  assign state = rst           ? `ST_IDLE :   // 复位期间
                 aborted       ? `ST_ERR  :   // 已停机: 由 core 的 aborted_r 粘住
                 retire        ? `ST_WB   :   // 本拍写回 = 退休拍
                 mem_active    ? `ST_MEM  :   // 访存在途, 等总线
                 ex_stage_fire ? `ST_EXE  :   // 本拍执行(EX_MEM 正在锁结果)
                 ifu_out_valid ? `ST_DEC  :   // 指令已取回, 还没进 EX
                                 `ST_FET;    // 兜底: IFU 手里空 = 正在取指

endmodule
