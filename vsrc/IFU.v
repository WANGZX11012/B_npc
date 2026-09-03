`include "npc_defs.vh"

module IFU (

  // Clock & Reset
  input               clk,
  input               rst,

  // 输入: ctrl   
  input               pc_we,                           // update PC
  input               fetch_req,                       // ctrl: FETCH state

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
  // 输出: to core / ctrl
  output [31:0]       pc,             // program counter
  output [31:0]       pc4,            // pc + 4
  output [31:0]       inst,           // fetched instruction
  output [31:0]       npc_normal,     //未被劫持的next pc
  output              ifu_done        // instruction valid this cycle

);

  //提供给axi的输入
  assign  req_valid = fetch_req; //不用！stall ，stall只是为了控制axi总线停顿的信号
  assign  req_addr = pc;
  //自己的输出
  assign  ifu_done =  handshake_done;
  assign  inst  = resp_rdata; //返回的指令


  // ── PC register ──
  reg [31:0] pc_reg;
  initial pc_reg = 32'h8000_0000;

  always @(posedge clk)
  begin
    if (rst)
      pc_reg <= 32'h8000_0000;
    else if (pc_we)
      pc_reg <= next_pc;
  end

  assign pc  = pc_reg;
  assign pc4 = pc_reg + 32'd4;

  // ── next PC ──
  //  npc_normal = 指令本身决定的下一条 PC (跳转目标 / mtvec / mepc / pc4)
  //   中断的 mepc 必须用它, 不能用 pc4: 被打断的若是 jal / taken branch,
  //   本来要去的是跳转目标; 笼统写 pc4 会把跳转吞掉(静默跑飞)。
  assign  npc_normal =  (npc_sel == `NPC_JALR)              ? {alu_result[31:1], 1'b0} :
                        (npc_sel == `NPC_BR && branch_taken) ? alu_result :
                        (npc_sel == `NPC_JAL)                ? alu_result :
                        (npc_sel == `NPC_ECALL)              ? csr_mtvec :
                        (npc_sel == `NPC_MRET)               ? csr_mepc  : // cte.c 软件里面+4 返回地址
                        pc4;

  // 中断劫持: irq_taken 时无视本条指令的意图, 强制跳 mtvec
  wire [31:0] next_pc;
  assign next_pc = irq_taken ? csr_mtvec :  npc_normal;



endmodule
