`include "npc_defs.vh"
// ── 复位向量: 平台相关 ──
//   单跑: 程序在主存, 链接在 0x8000_0000
//   SoC : 从 MROM 启动, MROM 在 0x2000_0000
//   现在升级flash 放在0x3000_0000
`ifdef YSYXSOC
  `define RESET_PC 32'h2000_0000
`else
  `define RESET_PC 32'h8000_0000
`endif

module IFU (

  // Clock & Reset
  input               clk,
  input               rst,

   // ── 输入: 级间握手 ──
  input               out_ready,                       // 下游本拍能收(逆流反压)

  // pc_we 决定 pc_reg 何时推进, 从而决定 pc 端口的语义。两套核接法不同:
  //   core.v      (多周期): .pc_we(retire)                   → 退休才写, pc = 当前指令 PC
  //   core_pipe.v (流水线): .pc_we(if_valid && if_id_ready)  → 交付即写, pc = 推测取指 PC
  //   故 pc 是"架构 PC"还是"推测 PC"由外部决定, 本模块不作假设。
  input               pc_we,

  // ── 输入: EXU / CSR (next-PC 计算) ──
  input  [31:0]       alu_result,                      // 跳转/分支目标
  input  [2:0]        npc_sel,                         // NPC_JALR/JAL/BR/...
  input               branch_taken,                    // 分支条件成立
  input  [31:0]       csr_mtvec,                       // 异常入口
  input  [31:0]       csr_mepc,                        // mret 返回地址
  input               irq_taken,                       // 顶层判定: 拉高则强制跳 mtvec, 覆盖本条指令意图
  input               access_fault,                    // 总线错误

  // ── 取指请求/响应: 上游可为 AXI 桥或仿真桩, 此处只看握手 ──
  output              req_valid,                       // 请求(电平保持到应答)
  output [31:0]       req_addr,                        // = pc_reg
  input               handshake_done,                  // 应答脉冲(单拍)
  input  [31:0]       resp_rdata,                      // 返回的 32 位指令字

  // ── 输出: 交付给下游段寄存器 ──
  output              out_valid,                       // 本拍交付是否有效(= hold_valid)
  output [31:0]       out_pc,                          // 本拍交付的那条指令自己的 PC

  // ── 输出: 给顶层核 ──
  //   三类 PC 名字相近但归属不同, 请勿混用:
  //     ① pc     = pc_reg 的 Q 端, "下一个取指地址"(取指态)
  //     ② out_pc = 正交付的那条指令的地址(指令态), 随指令走, 供 mepc / 精确异常用
  //     ③ pc4    = out_pc + 4, 参照物是本条指令, 不是 pc 端口
  //   注: 握手当拍 cur_pc 取自 pc_reg, 故 pc4 数值上等于 pc+4; 差别在参照物, 不在数值。
  //   npc_normal 的 "normal" 指"未经 fault/irq 劫持", 不是"顺序+4": 跳转目标也在其中。
  output [31:0]       pc,
  output [31:0]       pc4,
  output [31:0]       inst,                            // 本拍交付的指令编码(bypass 或 hold)
  output [31:0]       npc_normal


);

  // ── 保持寄存器: 接住总线返回的取指结果 ──
  //   handshake_done 是单拍脉冲, 不锁存就丢; 锁住后一直举着, 直到 fire 松手。
  //   hold_valid=0 不是"没有指令", 而是"回到可发请求的初态": 同一拍就在发起取指。
  reg        hold_valid;
  reg [31:0] hold_inst;
  reg [31:0] hold_pc;

  // 取/交互斥: 手上有货(hold_valid=1)就不再发请求。
  //   单槽保持寄存器使"接住"与"交付"必占两个时钟周期 → 每 2 周期进一条指令(IPC≈0.5)。
  //   接真实 AXI/icache 后 hold_valid=0 会持续到握手回来, 那时才是真正的访存等待。
  assign  req_valid = !rst && !hold_valid;
  assign  req_addr = pc;


  // 中断劫持: irq_taken 时无视本条指令的意图, 强制跳 mtvec
  wire [31:0] next_pc;
  assign next_pc = access_fault ? 32'b0 :(irq_taken ? csr_mtvec :  npc_normal); //fault跳0

  // ── PC register ──
  reg [31:0] pc_reg;   // 取指 PC(推测)
  initial pc_reg = `RESET_PC; 

  always @(posedge clk)
  begin
    if (rst)
      pc_reg <= `RESET_PC;
    else if (pc_we || access_fault)  // 总线故障时不等退休, 自己抢占写 PC
      pc_reg <= next_pc;
  end

  // ── 输出选择: 握手当拍走 bypass, 其余时间来自保持寄存器 ──
  //   因为握手done后一拍 才会到hold inst寄存器 所以当握手done的时候 要取到正确的值 就必须直接从输入的resp data拉进来
  //   非阻塞赋值下 IR 会读到 hold_inst 更新前的旧值(晚一拍)。
  wire [31:0] cur_inst = handshake_done ? resp_rdata : hold_inst;
  wire [31:0] cur_pc   = handshake_done ? pc_reg     : hold_pc;

  assign pc   = pc_reg;
  assign pc4  = cur_pc + 32'd4;   // 本指令 PC+4
  assign inst = cur_inst;

  // ── next PC ──
  //  npc_normal = 指令本身决定的下一条 PC (跳转目标 / mtvec / mepc / pc4)
  //   中断的 mepc 必须用它, 不能用 pc4: 被打断的若是 jal / taken branch,
  //   本来要去的是跳转目标; 笼统写 pc4 会把跳转吞掉(静默跑飞)。
  assign  npc_normal =  (npc_sel == `NPC_JALR)               ? {alu_result[31:1], 1'b0} :
                        (npc_sel == `NPC_BR && branch_taken) ? alu_result :
                        (npc_sel == `NPC_JAL)                ? alu_result :
                        (npc_sel == `NPC_ECALL)              ? csr_mtvec :
                        (npc_sel == `NPC_MRET)               ? csr_mepc  : // cte.c 软件里面+4 返回地址
                        pc4;

  // ── 级间握手: 保持 / 松手 ──
  wire       fire = hold_valid && out_ready;   // 本拍下游把指令取走了

  always @(posedge clk)
  begin
    if (rst)
    begin
      hold_valid <= 1'b0;
      hold_inst  <= 32'b0;
      hold_pc    <= `RESET_PC;   // 复位向量: 避免复位后波形里 X 传染到 out_pc
    end
    else if (handshake_done)
    begin
      hold_valid <= 1'b1;      // 总线返回: 接住
      hold_inst  <= resp_rdata;
      hold_pc    <= pc_reg;    // 取指时的 PC, 就是这条指令的 PC
    end
    else if (fire)
    begin
      hold_valid <= 1'b0;      // 下游取走: 松手
    end
  end

  assign out_valid = hold_valid;   // 我手里有一条指令 还没被取走
  assign out_pc    = cur_pc;      // 这条指令自己的 PC




endmodule
