`ifndef ICACHE_INDEX_BITS
  `define ICACHE_INDEX_BITS 4     // 没传宏时的兜底 16个
`endif

`ifndef ICACHE_BLOCK_BYTES
  `define ICACHE_BLOCK_BYTES 4     // 没传宏时的兜底 32位每块
`endif

module icache #(
  // 块大小要经过处理
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

    // ── 派生参数 ──
  localparam BLK_BYTES    = `ICACHE_BLOCK_BYTES;         // 4/8/16/32
  localparam WORDS = BLK_BYTES / 4;      // 每块几个字: 4B→1, 8B→2, 16B→4 也就是能放几个指令
  localparam OFFSET_WIDTH = $clog2(BLK_BYTES);           // 4→2, 16→4
  
  localparam NUM_BLOCKS   = 1 << INDEX_WIDTH;
  localparam TAG_WIDTH    = 32 - INDEX_WIDTH - OFFSET_WIDTH;
  // 状态机
  localparam S_IDLE = 1'b0;
  localparam S_WAIT = 1'b1;
  reg state;

  reg [INDEX_WIDTH-1:0] miss_idx;
  reg [TAG_WIDTH-1:0]   miss_tag;
  reg [31:0]            miss_addr;
  reg [31:0]            miss_word_idx;

  // ── 地址切分: 用参数化的位选, 不写魔数 ──
  wire [INDEX_WIDTH-1:0] idx   = ifu_req_addr[OFFSET_WIDTH +: INDEX_WIDTH];
  wire [TAG_WIDTH-1:0]   tag_w = ifu_req_addr[31 -: TAG_WIDTH];
  // 等价于 addr[5:2] 和 addr[31:6], 但跟着参数走

  // 请求地址落在块内的第几个字 (WORDS=1 时恒为 0) 多字传输中使用 表示第几个字
  wire [31:0] word_idx = (ifu_req_addr >> 2) & (WORDS - 1);
  // data 展平成一维: data[块号*WORDS + 块内字号]
  reg [31:0]          data  [0: NUM_BLOCKS*WORDS - 1];
  reg [TAG_WIDTH-1:0] tag   [NUM_BLOCKS];
  reg                 valid [NUM_BLOCKS];
  // hit判断
  wire hit = valid[idx] && (tag[idx] == tag_w);
  wire [31:0] hit_word = data[idx*WORDS + word_idx];

  reg [31:0] refill_w_off;            // 已经填到块内第几个字
  // 块首地址: 把块内偏移位清零
  wire [31:0] blk_base = {ifu_req_addr[31:OFFSET_WIDTH], {OFFSET_WIDTH{1'b0}}};  

  // ── 参数检查: ICACHE_BLOCK_BYTES 必须是 >=4 的 2 的幂 (4/8/16/32/64) ──
  initial begin
    if (`ICACHE_BLOCK_BYTES < 4 || (`ICACHE_BLOCK_BYTES & (`ICACHE_BLOCK_BYTES - 1)) != 0)
      $fatal(1, "[icache] ICACHE_BLOCK_BYTES=%0d 非法, 必须是 4/8/16/32/64", `ICACHE_BLOCK_BYTES);
  end

  integer i;
  always @(posedge clk) 
  begin
    if (rst) 
    begin
      state <= S_IDLE;
      refill_w_off <= 32'b0;
      miss_idx   <= 0;
      miss_tag   <= 0;
      miss_addr  <= 32'b0;
      miss_word_idx <= 32'b0; 
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
          miss_addr <= blk_base;
          miss_word_idx <= word_idx;
          refill_w_off <= 32'b0;
        end
        S_WAIT: 
        if (mem_done) 
        begin
           // ① 本拍读回的字, 落进块内 refill_w 号槽位
          data[miss_idx*WORDS + refill_w_off] <= mem_rdata;
          // ② 整块填完了吗?
          if (refill_w_off == WORDS - 1)
          begin
              state           <= S_IDLE;
              valid[miss_idx] <= 1'b1;
              tag  [miss_idx] <= miss_tag;
          end
          else
              refill_w_off <= refill_w_off + 32'd1;
        end
        default: state <= S_IDLE;
      endcase
    end
  end

  assign mem_req_valid = (state == S_IDLE) ? (ifu_req_valid && !hit) : 1'b1;
  assign mem_req_addr  = (state == S_IDLE) ? blk_base
                                           : (miss_addr + (refill_w_off << 2));

  wire refill_done = (state == S_WAIT) && mem_done &&
                     (refill_w_off == WORDS - 1) && ifu_req_valid;   // 如果传输大于4B（好几个指令） 就要所有传输完才done
  assign ifu_done  = ((state == S_IDLE) && ifu_req_valid && hit) || refill_done;


  wire [31:0] refill_word = data[miss_idx*WORDS + miss_word_idx];
   // 最后一个字还停在 mem_rdata 上(data 是非阻塞赋值), 直接旁路总线数据
  assign ifu_rdata = refill_done ? ((miss_word_idx == WORDS - 1) ? mem_rdata : refill_word)
                                 : hit_word;      // hit 路径才用 hit_word


`ifdef PRINT_ICACHE
  // ── 统计 (仅仿真/调试, 综合时连同寄存器一起消失) ──
  reg [63:0] hit_cnt, miss_cnt;
  reg        halt_r;

  always @(posedge clk)
  begin
    if (rst)
    begin
      hit_cnt  <= 64'd0;
      miss_cnt <= 64'd0;
      halt_r   <= 1'b0;
    end
    else
    begin
      halt_r <= halt;

      if (state == S_IDLE && ifu_req_valid && hit)
        hit_cnt  <= hit_cnt  + 64'd1;
      if (state == S_WAIT && mem_done && (refill_w_off == WORDS - 1))
        miss_cnt <= miss_cnt + 64'd1;

      if (halt && !halt_r && (hit_cnt + miss_cnt) != 0)
        $display("[icache %0d blocks x %0dB] hit=%0d  miss=%0d  hit_rate=%0d.%01d%%",
          NUM_BLOCKS, (1 << OFFSET_WIDTH),
          hit_cnt, miss_cnt,
          (hit_cnt * 64'd1000) / (hit_cnt + miss_cnt) / 10,     // 91
          (hit_cnt * 64'd1000) / (hit_cnt + miss_cnt) % 10);    // .5
    end
  end
`endif


endmodule