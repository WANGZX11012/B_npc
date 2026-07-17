// 指令内存：128KB，字寻址。SimpleBus 从设备接口。
// 同步读：reqValid 当拍 → respValid 下一拍拉高 + rdata 有效
module inst_mem (
  input  wire         clk,
  input  wire [31:0]  addr,
  input  wire         reqValid,
  output reg  [31:0]  rdata,
  output reg          respValid
);

  wire [14:0] word_idx = addr[16:2];
  reg [31:0] mem [0:32767];

  always @(posedge clk) 
  begin
    rdata     <= mem[word_idx];
    respValid <= reqValid;     // 请求当拍 → 下一拍拉高
  end

  initial $readmemh("csrc/test.hex", mem);

endmodule
