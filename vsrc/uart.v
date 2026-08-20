// UART — 串口（MMIO 0xa00003f8），AXI4-Lite 从设备（AR + R + AW + W + B）
// 写 1 字节 → DPI-C 调 C++ putch 打印到 stdout; 读返回 0（amtest 只写不读）

import "DPI-C" function void uart_putchar(byte unsigned c);

module uart (
  input  wire        clk,
  // AR（读地址）
  input  wire [31:0] araddr,
  input  wire        arvalid,
  output wire        arready,
  // R（读数据）
  output wire [31:0] rdata,
  output wire [1:0]  rresp,
  output reg         rvalid,
  input  wire        rready,
  // AW
  input  wire [31:0] awaddr,
  input  wire        awvalid,
  output wire        awready,
  // W
  input  wire [31:0] wdata,
  input  wire [3:0]  wmask,
  input  wire        wvalid,
  output wire        wready,
  // B
  output wire [1:0]  bresp,
  output reg         bvalid,
  input  wire        bready
);

  assign awready = 1'b1;
  assign wready  = 1'b1;
  assign bresp   = 2'b00;          // OKAY
  assign arready = 1'b1;           // 读立即收
  assign rdata   = 32'b0;          // UART 接收数据寄存器, amtest 不读
  assign rresp   = 2'b00;          // OKAY

  initial begin
    bvalid = 1'b0;
    rvalid = 1'b0;
  end

  always @(posedge clk)
  begin
    if (arvalid && arready)
      rvalid <= 1'b1;
    else if (rvalid && rready)
      rvalid <= 1'b0;

    if (wvalid && wready)
    begin
      uart_putchar(wdata[7:0]);   // 锁存一拍，写 1 字节打印 1 字符
      bvalid <= 1'b1;
    end
    else if (bvalid && bready)
      bvalid <= 1'b0;             // master 取走，撤销
  end

endmodule
