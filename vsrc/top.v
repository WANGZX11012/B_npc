module top (
  input  wire         clk,
  input  wire         reset,
  output wire         halt,
  output wire [31:0]  pc
);

  core u_core (
    .clk   (clk),
    .reset (reset),
    .pc    (pc),
    .halt  (halt)
  );

endmodule
