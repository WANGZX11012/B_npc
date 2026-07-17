`include "npc_defs.vh"

// IFU – 取指单元：PC + SimpleBus 主设备接口
// idle: 发读请求 (ifu_reqValid=1, ifu_raddr=pc)
// wait: 等内存返回数据 (ifu_respValid=1 → 指令有效)

module IFU (
  input  wire         clk,
  input  wire         reset,
  input  wire         pc_we,
  input  wire         fetch_req,       // ctrl: 需要取指（FETCH 状态）
  input  wire [31:0]  alu_result,
  input  wire [2:0]   npc_sel,
  input  wire         branch_taken,
  input  wire [31:0]  csr_mtvec,
  input  wire [31:0]  csr_mepc,
  output wire [31:0]  pc,
  output wire [31:0]  pc4,

  // SimpleBus 读接口
  input  wire [31:0]  ifu_rdata,
  input  wire         ifu_respValid,
  output wire [31:0]  ifu_raddr,
  output wire         ifu_reqValid,
  output wire         ifu_done         // 本拍拿到有效指令
);

  localparam [0:0] S_IDLE = 0, S_WAIT = 1;

  reg [0:0] bus_state, bus_next;

  always @(posedge clk) begin
    if (reset) bus_state <= S_IDLE;
    else       bus_state <= bus_next;
  end

  always @(*) begin
    case (bus_state)
      S_IDLE: bus_next = fetch_req  ? S_WAIT : S_IDLE;      // ctrl 说取指才发请求
      S_WAIT: bus_next = ifu_respValid ? S_IDLE : S_WAIT;   // 数据到 → 回 idle
      default: bus_next = S_IDLE;
    endcase
  end

  assign ifu_reqValid = (bus_state == S_IDLE) && fetch_req;
  assign ifu_raddr    = pc;
  assign ifu_done     = (bus_state == S_WAIT) && ifu_respValid;  // WAIT 拍且数据有效

  // ── PC 寄存器 ──
  reg [31:0] pc_reg;
  initial pc_reg = 32'h8000_0000;

  always @(posedge clk) begin
    if (reset)
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
