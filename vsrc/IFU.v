`include "npc_defs.vh"
// ── 复位向量: 平台相关 ──
//   单跑: 程序在主存, 链接在 0x8000_0000
//   SoC : 从 MROM 启动, MROM 在 0x2000_0000
`ifdef YSYXSOC
  `define RESET_PC 32'h2000_0000
`else
  `define RESET_PC 32'h8000_0000
`endif

module IFU (

  // Clock & Reset
  input               clk,
  input               rst,

    // 输入: 级间握手(下游给的"能收"信号)
  input               out_ready,                       // 下游能收(过渡期 = ctrl 处于 WB 拍)
 
  input               pc_we,                           // update PC
  // 输入: EXU / CSR (next-PC calc)
  input  [31:0]       alu_result,                      // jump/branch target
  input  [2:0]        npc_sel,                         // NPC_JALR/JAL/BR/...
  input               branch_taken,                    // branch condition met
  input  [31:0]       csr_mtvec,                       // exception entry
  input  [31:0]       csr_mepc,                        // mret return addr
  input               irq_taken,                       // 中断响应: WB拍&MIE&mtip 三者成立时拉高, 强制跳 mtvec

  //提供给axi转化的信号 简单请求
  output              req_valid,
  output [31:0]       req_addr,
  input               handshake_done, //握手完成信号
  input  [31:0]       resp_rdata,             


  output              out_valid,                       // 我手里有一条取回的指令
  output [31:0]       out_pc,                          // 这条指令自己的 PC


  // 输出: to core / ctrl
  output [31:0]       pc,             // program counter
  output [31:0]       pc4,            // pc + 4
  output [31:0]       inst,           // fetched instruction
  output [31:0]       npc_normal     //未被劫持的next pc

);

  // ── 保持寄存器: 接住总线返回的取指结果 ──
  // handshake_done 是单拍脉冲, 不锁存就丢了; 锁住后一直保持到下游接收(out_ready)
  reg        hold_valid;
  reg [31:0] hold_inst;
  reg [31:0] hold_pc;

  //提供给axi的输入
  assign  req_valid = !rst && !hold_valid;   // 脱离ctrl控制 自己发请求 手里空了就去取
  assign  req_addr = pc;

  // 中断劫持: irq_taken 时无视本条指令的意图, 强制跳 mtvec
  wire [31:0] next_pc;
  assign next_pc = irq_taken ? csr_mtvec :  npc_normal;

  // ── PC register ──
  reg [31:0] pc_reg;
  initial pc_reg = `RESET_PC; 

  always @(posedge clk)
  begin
    if (rst)
      pc_reg <= `RESET_PC;
    else if (pc_we)
      pc_reg <= next_pc;
  end

  // ── 输出选择: 握手当拍走 bypass, 其余时间来自保持寄存器 ──
  //   因为握手done后一拍 才会到hold inst寄存器 所以当握手done的时候 要取到正确的值 就必须直接从输入的resp data拉进来
  //   非阻塞赋值下 IR 会读到 hold_inst 更新前的旧值(晚一拍)。
  wire [31:0] cur_inst = handshake_done ? resp_rdata : hold_inst;
  wire [31:0] cur_pc   = handshake_done ? pc_reg     : hold_pc;

  assign pc   = pc_reg;
  assign pc4  = cur_pc + 32'd4;   // pc+4 属于"这条指令", 不是"当前 PC"
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

  assign out_valid = hold_valid;   // 我手里有一条指令
  assign out_pc    = cur_pc;      // 这条指令自己的 PC




endmodule
