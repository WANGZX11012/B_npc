// 数据内存：128KB，字节寻址。SimpleBus 从设备。
// reqValid 当拍 → respValid 下一拍拉高 + rdata 有效
module data_mem (
  input  wire         clk,
  input  wire         reqValid,
  input  wire [31:0]  addr,
  input  wire         wen,
  input  wire [31:0]  wdata,
  input  wire [3:0]   wmask,
  output reg  [31:0]  rdata,
  output reg          respValid
);

  reg [7:0] mem [0:(128*1024)-1]; //单个字节的单位

  wire [16:0] byte_off = addr[16:0];
  wire [14:0] word_off = byte_off[16:2];

  // 组合读：给地址 → 立刻出数据（LSU 自己锁存时机由 respValid 控制）
  wire [31:0] word_aligned = {
    mem[{word_off, 2'b11}],
    mem[{word_off, 2'b10}],
    mem[{word_off, 2'b01}],
    mem[{word_off, 2'b00}]
  };

  always @(posedge clk) begin
    // 同步写
    if (reqValid && wen) begin
      if (wmask[0]) mem[{word_off, 2'b00}] <= wdata[ 7: 0];
      if (wmask[1]) mem[{word_off, 2'b01}] <= wdata[15: 8];
      if (wmask[2]) mem[{word_off, 2'b10}] <= wdata[23:16];
      if (wmask[3]) mem[{word_off, 2'b11}] <= wdata[31:24];
    end
    // 读数据：reqValid 当拍采样 → respValid 下一拍 + rdata 有效
    rdata     <= reqValid ? word_aligned : 32'h0;
    respValid <= reqValid;
  end

endmodule
