`include "npc_defs.vh"

module IFU (

  // Clock & Reset
  input  wire         clk,
  input  wire         rst,

  // 输入: ctrl
  input  wire         pc_we,                           // update PC
  input  wire         fetch_req,                       // ctrl: FETCH state

  // 输入: EXU / CSR (next-PC calc)
  input  wire [31:0]  alu_result,                      // jump/branch target
  input  wire [2:0]   npc_sel,                         // NPC_JALR/JAL/BR/...
  input  wire         branch_taken,                    // branch condition met
  input  wire [31:0]  csr_mtvec,                       // exception entry
  input  wire [31:0]  csr_mepc,                        // mret return addr


  //提供给axi转化的信号 简单请求
  output              req_valid,
  output [31:0]       req_addr,
  input               handshake_done, //握手完成信号
  input  [31:0]       resp_rdata,             
  // 输出: to core / ctrl
  output wire [31:0]  pc,                              // program counter
  output wire [31:0]  pc4,                             // pc + 4
  output wire [31:0]  inst,                            // fetched instruction
  output wire         ifu_done                         // instruction valid this cycle

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

  wire [31:0] next_pc;
  assign next_pc = (npc_sel == `NPC_JALR)               ? {alu_result[31:1], 1'b0} :
                   (npc_sel == `NPC_BR && branch_taken)  ? alu_result :
                   (npc_sel == `NPC_JAL)                 ? alu_result :
                   (npc_sel == `NPC_ECALL)               ? csr_mtvec :
                   (npc_sel == `NPC_MRET)                ? csr_mepc  :
                   pc4;


endmodule
