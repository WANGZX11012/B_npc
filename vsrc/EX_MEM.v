`include "npc_defs.vh"

// EX_MEM — EX/MEM 流水寄存器
//   干什么: 一条指令在 EX 段算完之后、WB 段写回之前, 它的结果需要一个地方举着。
//           因为访存要等总线好几拍, 地址必须全程稳定, 组合信号做不到。
//   为什么独立成模块: EXU 是纯组合(无 clk)放不了寄存器, 历史上这段状态
//           只能寄生在 core.v 里(alu_result_r / ex_done_r), 成了孤儿。现在给它归宿,
//           core 回归纯互连。
//   三段对称性: IFU 管 IF 段(hold_*), 本模块管 EX~WB 段, LSU 管 MEM 段(busy/res_rdy)。
module EX_MEM (

  // Clock & Reset
  input         clk,
  input         rst,

  // 输入: 上游握手(ID/EX 侧)
  input         in_valid,        // ← IFU.out_valid : 上游手上有指令
  input  [31:0] result_in,       // ← EXU.alu_result: EX 段组合算出的结果

  // 输入: 下游握手(WB 侧)
  input         out_ready,       // ← retire        : WB 段把这条指令的结果收走了

  // 输出: 数据
  output [31:0] exm_result,      // → LSU.addr_in / WBU.alu_result (跨拍稳定)

  // 输出: 状态
  output        exm_done,        // → mem_req / retire 判决: EX 段已算完, 结果可交
  output        exm_stage_fire   // → ex_stage_fire : 本拍正在把结果锁进来
);

  reg        busy_r;             // 我占着一条指令(覆盖 EX → MEM → WB 全程)
  reg        done_r;             // EX 段已算完, 结果锁好, 可以往外交
  reg [31:0] result_r;           // 举着的那个结果

  assign exm_result     = result_r;
  assign exm_done       = done_r;
  assign exm_stage_fire = busy_r && !done_r;   // 占着但还没算完 = 本拍在干活

  always @(posedge clk)
  begin
    if (rst)
    begin
      busy_r   <= 1'b0;
      done_r   <= 1'b0;
      result_r <= 32'b0;
    end
    else if (!busy_r && in_valid)
    begin
      busy_r   <= 1'b1;                 // 接手: 上游有指令且我空着 → 占住
    end
    else if (busy_r && !done_r)
    begin
      result_r <= result_in;            // 干活: 把 EXU 的结果锁下来
      done_r   <= 1'b1;                 //       从此 result_r 稳定, 不再变化
    end
    else if (out_ready)
    begin
      busy_r   <= 1'b0;                 // 交班: WB 段真把结果收走了才松手
      done_r   <= 1'b0;                 //       访存时 retire 要等 lsu_res_valid,
    end                                 //       所以地址会一直举到总线返回
  end

endmodule
