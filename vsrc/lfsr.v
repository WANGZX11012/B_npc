// 8-bit LFSR 伪随机数
// feedback: bit7 ^ bit5 ^ bit4 ^ bit3  (maximal length = 255)

module lfsr #(
  parameter [7:0] SEED = 8'h5A            // initial value (must be non-zero)
) (
  input  wire         clk,
  input  wire         rst,
  input  wire         en,                  // advance to next value
  output wire [7:0]   val                  // current random value (1..255)
);

  reg [7:0] state;

  always @(posedge clk)
  begin
    if (rst)
      state <= SEED;
    else if (en)
      state <= {state[6:0],                // left shift by 1
                state[7] ^ state[5] ^ state[4] ^ state[3]};  // feedback
  end

  assign val = state;

endmodule
