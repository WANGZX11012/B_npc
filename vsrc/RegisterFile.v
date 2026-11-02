module RegisterFile #(
  parameter ADDR_WIDTH = 5,     // 端口位宽, 由 RV32 编码决定, 不动
  parameter DEPTH_LOG2 = 4,     // 存储深度 log2: 4=16 项(RV32E), 5=32 项(RV32I)
  parameter DATA_WIDTH = 32
) 
 (//二读一写寄存器堆 必须有clk
  input clk,
  input [DATA_WIDTH-1:0] w_data,
  input [ADDR_WIDTH-1:0] w_addr,

  input [ADDR_WIDTH-1:0] r_addr1,
  input [ADDR_WIDTH-1:0] r_addr2,

  input wen,

  output [DATA_WIDTH-1:0]r_data1,
  output [DATA_WIDTH-1:0]r_data2,

  output [DATA_WIDTH-1:0]r_a0

);
  localparam DEPTH = (1 << DEPTH_LOG2);

  reg [DATA_WIDTH-1:0] rf [DEPTH-1:0];  // 16个寄存器了 rv32e

  integer i;
  initial
  begin
    for (i = 0; i < DEPTH; i = i + 1)
      rf[i] = {DATA_WIDTH{1'b0}};
  end

  // 地址低位截断到实际深度: RV32E 下 x16~x31 不存在, 编译器不会产生
  wire [DEPTH_LOG2-1:0] w_idx  = w_addr[DEPTH_LOG2-1:0];
  wire [DEPTH_LOG2-1:0] r1_idx = r_addr1[DEPTH_LOG2-1:0];
  wire [DEPTH_LOG2-1:0] r2_idx = r_addr2[DEPTH_LOG2-1:0];

  always @(posedge clk)
  begin
    rf[0] <= {DATA_WIDTH{1'b0}};
    if (wen && w_addr != 0)
      rf[w_idx] <= w_data;
  end

  assign r_data1 = (r_addr1 == 0) ? 0 : rf[r1_idx];
  assign r_data2 = (r_addr2 == 0) ? 0 : rf[r2_idx];


  assign r_a0    = rf[10]; //到时候传给DPIC 来判断good trap bad trap


endmodule
