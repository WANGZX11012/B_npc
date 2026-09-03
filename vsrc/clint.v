// CLINT — 时钟中断控制器 设备有写数据的部分
// AXI4-Lite 接口
//   mtime[63:0] 每周期 +1（64 位避免 32 位溢出）。
//   偏移 +0 (0xa0000050) = mtime[31:0]  低 32 位 只读
//   偏移 +4 (0xa0000054) = mtime[63:32] 高 32 位 只读
//   mtimecmp 时钟中断比较寄存器：低32位 0xa0000058 高32位 0xa000005c 读写

//   软件分两次读低/高 32 位组合成 64 位 uptime，再按时钟频率换算成真实时间。




module clint (
  input  wire        clk,
  input  wire        rst,
  // AR（读地址）
  input  wire [31:0] araddr,
  input  wire        arvalid,
  output wire        arready,
  // R（读数据）
  output reg  [31:0] rdata,
  output reg  [1:0]  rresp,
  output reg         rvalid,
  input  wire        rready,
   // AW（写地址）
  input  wire [31:0] awaddr,           
  input  wire        awvalid,           
  output wire        awready,           
  // W（写数据）
  input  wire [31:0] wdata,            
  input  wire        wvalid,            
  output wire        wready,            
  // B（写响应）
  output wire [1:0]  bresp,             
  output reg         bvalid,            
  input  wire        bready,            

  // 中断输出
  output wire        mtip       // 比较结果: mtime >= mtimecmp 时拉高
);

  assign arready = 1'b1;       // 读地址立即可收
  assign awready = 1'b1;       // 写地址立即可收
  assign wready  = 1'b1;       // 写数据立即可收
  assign bresp   = 2'b00;      // 恒 OKAY（同 uart）

  // ── mtime：64 位自由计数器，每周期 +1 ──
  reg [63:0] mtime;
  always @(posedge clk)
  begin
    if(rst)
      mtime <= 64'b0;
    else
      mtime <= mtime + 64'b1;
  end

    // mtimecmp 比较寄存器: 初始/复位为最大值, 保证初态"永不触发"
  reg [63:0] mtimecmp;
  initial mtimecmp = 64'hffff_ffff_ffff_ffff;

  // AW 握手拍是协议保证 awaddr 有效的最后一拍, 在此登记"这次写哪个半区"
  reg aw_half;              // 0=低 32 位(0xa0000058), 1=高 32 位(0xa000005c)
  always @(posedge clk)
  begin
    if (rst)
      aw_half <= 1'b0;
    else if (awvalid && awready)
      aw_half <= awaddr[2];
  end

  // mtimecmp 写入: 复位回到最大值(initial 不响应复位, 必须显式写)
  always @(posedge clk)
  begin
    if (rst)
      mtimecmp <= 64'hffff_ffff_ffff_ffff;
    else if (wvalid && wready)
    begin
      if (aw_half)
        mtimecmp[63:32] <= wdata;
      else
        mtimecmp[31:0]  <= wdata;
    end
  end

  // B 通道应答: 只管 bvalid, 不再碰 mtimecmp(避免双驱动)
  always @(posedge clk)
  begin
    if (rst)
      bvalid <= 1'b0;
    else if (wvalid && wready)
      bvalid <= 1'b1;
    else if (bvalid && bready)
      bvalid <= 1'b0;          // 握手完成, 撤销应答
  end


  always @(posedge clk)
  begin
    rresp <= 2'b00;            // OKAY
    if (rst)
    begin
      rvalid <= 1'b0;          // AMBA: 复位期间所有 VALID 必须为低
    end
    else if (arvalid && arready)
    begin
      case (araddr[3:2])
        2'b00:   rdata <= mtime[31:0];      // +0x00 mtime 低 32 位
        2'b01:   rdata <= mtime[63:32];     // +0x04 mtime 高 32 位
        2'b10:   rdata <= mtimecmp[31:0];   // +0x08 mtimecmp 低 32 位
        default: rdata <= mtimecmp[63:32];  // +0x0c mtimecmp 高 32 位
      endcase
      rvalid <= 1'b1;
    end
    else if (rvalid && rready)
    begin
      rvalid <= 1'b0;          // master 取走，撤销
    end
  end


  reg mtip_temp;
  always @(posedge clk)
  begin
    if (rst)
      mtip_temp <= 1'b0;
    else
      mtip_temp <= (mtime >= mtimecmp);
  end

  assign mtip = mtip_temp;   // 打一拍, 防止比较器毛刺




endmodule
