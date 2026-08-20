module top (
  input  wire         clk,
  input  wire         rst,
  output wire         halt,
  output wire         aborted,        // 非法指令/异常终止(对齐 NEMU_ABORT)
  output wire [31:0]  pc,
  output wire [31:0]  ir_dbg,        // IR for monitor
  output wire [2:0]   state_dbg,      // ctrl_state for monitor
  output wire         stall_ifu,      // IFU LFSR stall
  output wire         mmio_dbg       // 本条指令是否访问外设(difftest)
);

  core u_core (
    .clk       (clk),
    .rst     (rst),
    .pc        (pc),
    .halt      (halt),
    .aborted   (aborted),
    .ir_dbg    (ir_dbg),
    .state_dbg (state_dbg),
    .mmio_dbg  (mmio_dbg)
  );

endmodule
