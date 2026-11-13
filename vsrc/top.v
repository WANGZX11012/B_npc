module top (
  input  wire         clk,
  input  wire         rst,
  output wire         halt,
  output wire         aborted,
  output wire [31:0]  pc,
  output wire [2:0]   state_dbg,
  output wire         inst_retire,
  output wire [31:0]  retire_inst_dbg,
  output wire         mmio_dbg
);

`ifdef CORE_PIPE
  core_pipe u_core (
`else
  core u_core (
`endif
    .clk            (clk),
    .rst            (rst),
    .pc             (pc),
    .halt           (halt),
    .aborted        (aborted),
    .state_dbg      (state_dbg),
    .inst_retire    (inst_retire),
    .retire_inst_dbg(retire_inst_dbg),
    .mmio_dbg       (mmio_dbg)
  );

endmodule
