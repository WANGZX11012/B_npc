// 数据内存：128KB 字节寻址。AXI4-Lite 从设备（读+写，带可配置延迟）

module pmem #(
`ifdef DATA_MEM_DELAY
  parameter DELAY = `DATA_MEM_DELAY                     // from menuconfig
`else
  parameter DELAY = 1                                   // default: SRAM speed
`endif
) (

  // Clock
  input  wire         clk,

  // AXI4-Lite AR (read address)
  input  wire [31:0]  araddr,
  input  wire         arvalid,
  output wire         arready,

  // AXI4-Lite R (read data)
  output reg  [31:0]  rdata,
  output wire [1:0]   rresp,
  output reg          rvalid,
  input  wire         rready,

  // AXI4-Lite AW (write address)
  input  wire [31:0]  awaddr,
  input  wire         awvalid,
  output wire         awready,

  // AXI4-Lite W (write data)
  input  wire [31:0]  wdata,
  input  wire [3:0]   wmask,
  input  wire         wvalid,
  output wire         wready,

  // AXI4-Lite B (write response)
  output wire [1:0]   bresp,
  output reg          bvalid,
  input  wire         bready
);

  reg [7:0] mem [0:(128*1024)-1]; 

  // ── 程序数据初始化：加载 build/img.hex（与 inst_mem 同一个镜像）──
  // AM 的 .bin 是 代码+数据 的连续镜像，bin2readmemh.py 每行一个 32-bit word，
  // 从 @00000000 开始；而 CPU 地址 0x8000_0000 经 araddr[16:2]/awaddr[16:2]
  // 索引 word，两者天然对齐：img_mem[w] ⇔ 0x8000_0000 + w*4。
  // 没有这段，.data 段（如函数指针表）在 data_mem 里全是 0，间接调用会崩溃。


  reg [31:0] img_mem [0:32767];//通过readmem填进来 再通过for循环放到
  integer    i;
  initial
  begin
    $readmemh("build/img.hex", img_mem);
    for (i = 0; i < 32768; i = i + 1)
    begin
      mem[{i[14:0], 2'b00}] = img_mem[i][ 7: 0];
      mem[{i[14:0], 2'b01}] = img_mem[i][15: 8];
      mem[{i[14:0], 2'b10}] = img_mem[i][23:16];
      mem[{i[14:0], 2'b11}] = img_mem[i][31:24];
    end
    // [临时调试] 验证 img_mem 加载 + mem 拷贝
    $display("DBG img_mem[5206]=%08x img_mem[0]=%08x", img_mem[5206], img_mem[0]);
    $display("DBG mem[20824..7]=%02x%02x%02x%02x (期待 13050000)", mem[20824], mem[20825], mem[20826], mem[20827]);
  end

  localparam [1:0] S_IDLE = 2'd0, S_RD = 2'd1, S_WR = 2'd2;
  reg [1:0]  state;
  reg [15:0] cnt;
  reg [31:0] rdata_lat;
  reg [14:0] aw_word_lat;
  reg        aw_recv;          // AW 已收，等待 W

  wire [14:0] ar_word = araddr[16:2];//截断得到真实地址
  wire [14:0] aw_word = awaddr[16:2];
  wire [31:0] ar_data = {mem[{ar_word, 2'b11}], mem[{ar_word, 2'b10}],
                         mem[{ar_word, 2'b01}], mem[{ar_word, 2'b00}]};

  // IDLE 且无挂起响应时才接收 AR/AW；AW 收到后才能收 W
  assign arready = (state == S_IDLE) && !aw_recv && !rvalid;
  assign awready = (state == S_IDLE) && !aw_recv && !bvalid;
  assign wready  = aw_recv;
  assign rresp   = 2'b00;       // OKAY
  assign bresp   = 2'b00;       // OKAY

  initial state = S_IDLE;

  always @(posedge clk)
  begin
    case (state)
      S_IDLE: begin
        if (rvalid && rready) rvalid <= 1'b0;   // 上一次读数据 被取走了 清楚valid信号应对下一次
        if (bvalid && bready) bvalid <= 1'b0;   
        if (awvalid && awready) 
        begin
          aw_recv     <= 1'b1;                   // 写地址已经收到 等待写入数据
          aw_word_lat <= aw_word;
        end
        else if (arvalid && arready) 
        begin
          rdata_lat <= ar_data;                  // 锁存读数据
          cnt       <= 16'd1;
          state     <= S_RD;
        end
      end

      S_RD: begin
        if (cnt == DELAY) 
        begin
          rvalid <= 1'b1;                        // 延迟到，返回读数据 下一个周期才会更新
          rdata  <= rdata_lat;
          state  <= S_IDLE;                       // 回 IDLE 等 rready 握手
        end
        else cnt <= cnt + 1;
      end

      S_WR: begin
        if (cnt == DELAY) begin
          bvalid <= 1'b1;                        // 延迟到，返回写响应
          state  <= S_IDLE;                       // 回 IDLE 等 bready 握手
        end
        else cnt <= cnt + 1;
      end

      default: state <= S_IDLE;
    endcase

    // W 握手：收到写数据 → 执行写 + 进延迟
    if (aw_recv && wvalid && wready)
    begin
      if (wmask[0]) mem[{aw_word_lat, 2'b00}] <= wdata[ 7: 0];
      if (wmask[1]) mem[{aw_word_lat, 2'b01}] <= wdata[15: 8];
      if (wmask[2]) mem[{aw_word_lat, 2'b10}] <= wdata[23:16];
      if (wmask[3]) mem[{aw_word_lat, 2'b11}] <= wdata[31:24];
      aw_recv <= 1'b0;
      cnt     <= 16'd1;
      state   <= S_WR;
    end
  end

endmodule
