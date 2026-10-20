`ifndef ICACHE_INDEX_BITS
  `define ICACHE_INDEX_BITS 4     // 没传宏时的兜底
`endif

module icache #(
  parameter OFFSET_WIDTH = 2,                        // 块大小 4B, 暂不支持改
  parameter INDEX_WIDTH  = `ICACHE_INDEX_BITS        // ← menuconfig 控制块数
)
(
  input  wire        clk,
  input  wire        rst,
  input  wire        halt,

  input  wire        ifu_req_valid,
  input  wire [31:0] ifu_req_addr,
  output wire        ifu_done,
  output wire [31:0] ifu_rdata,

  output wire        mem_req_valid,
  output wire [31:0] mem_req_addr,
  input  wire        mem_done,
  input  wire [31:0] mem_rdata
);

  // ── 派生参数: 全部自动算, 改上面两个数就行 ──
  localparam NUM_BLOCKS = 1 << INDEX_WIDTH;              // 16
  localparam TAG_WIDTH  = 32 - INDEX_WIDTH - OFFSET_WIDTH; // 26

  localparam S_IDLE = 1'b0;
  localparam S_WAIT = 1'b1;
  reg state;

  reg [INDEX_WIDTH-1:0] miss_idx;
  reg [TAG_WIDTH-1:0]   miss_tag;
  reg [31:0]            miss_addr;   // 上一轮的结论: 整地址锁存更干净

  // ── 地址切分: 用参数化的位选, 不写魔数 ──
  wire [INDEX_WIDTH-1:0] idx   = ifu_req_addr[OFFSET_WIDTH +: INDEX_WIDTH];
  wire [TAG_WIDTH-1:0]   tag_w = ifu_req_addr[31 -: TAG_WIDTH];
  // 等价于 addr[5:2] 和 addr[31:6], 但跟着参数走

  reg [31:0]          data  [NUM_BLOCKS];
  reg [TAG_WIDTH-1:0] tag   [NUM_BLOCKS];
  reg                 valid [NUM_BLOCKS];

  wire hit = valid[idx] && (tag[idx] == tag_w);

  integer i;
  always @(posedge clk) 
  begin
    if (rst) 
    begin
        state <= S_IDLE;
        for (i = 0; i < NUM_BLOCKS; i = i + 1)
            valid[i] <= 1'b0;
    end 
    else 
    begin
      case (state)
        S_IDLE: if (ifu_req_valid && !hit) 
        begin
            state     <= S_WAIT;
            miss_idx  <= idx;
            miss_tag  <= tag_w;
            miss_addr <= ifu_req_addr;
        end
        S_WAIT: if (mem_done) 
        begin
            state           <= S_IDLE;
            valid[miss_idx] <= 1'b1;
            tag [miss_idx]  <= miss_tag;
            data[miss_idx]  <= mem_rdata;
        end
        default: state <= S_IDLE;
      endcase
    end
  end

  assign mem_req_valid = (state == S_IDLE) ? (ifu_req_valid && !hit) : 1'b1;
  assign mem_req_addr  = (state == S_IDLE) ? ifu_req_addr : miss_addr;

  assign ifu_done  = ((state == S_IDLE) && ifu_req_valid && hit)
                   || ((state == S_WAIT) && mem_done);
  assign ifu_rdata = (state == S_WAIT) ? mem_rdata : data[idx];

  // ── 统计部分不变 ──
  reg [31:0] hit_cnt, miss_cnt;
  reg        halt_r;

  always @(posedge clk) 
  begin
    if (rst) 
    begin
      hit_cnt  <= 32'd0;
      miss_cnt <= 32'd0;
      halt_r   <= 1'b0;
    end 
    else 
    begin
      halt_r <= halt;
      if (state == S_IDLE && ifu_req_valid && hit)
        hit_cnt <= hit_cnt + 32'd1;
      if (state == S_WAIT && mem_done)
        miss_cnt <= miss_cnt + 32'd1;
      `ifdef PRINT_ICACHE
      if (halt && !halt_r && (hit_cnt + miss_cnt) != 0)
        $display("[icache %0d blocks x %0dB] hit=%0d  miss=%0d  hit_rate=%0d.%01d%%",
          NUM_BLOCKS, (1 << OFFSET_WIDTH),
          hit_cnt, miss_cnt,
          (hit_cnt * 100)  / (hit_cnt + miss_cnt),
          ((hit_cnt * 1000) / (hit_cnt + miss_cnt)) % 10);
      `endif
    end
  end

endmodule