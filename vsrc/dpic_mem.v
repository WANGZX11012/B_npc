// DPI-C 内存:AXI4-Lite 从设备, 自身不存数据, 读/写都通过 DPI-C 转发到 NEMU pmem。
// 两个实例(i_mem / d_mem)各例化一个, 总线接入方式完全一致, 物理内存真相只在 NEMU pmem 一处。
// 这样 NPC 取指/访存不受 Verilog 数组容量限制, amtest 这种大镜像也能直接跑。
//

import "DPI-C" function void dpic_mem_read (input  longint unsigned addr, output int unsigned rdata);
import "DPI-C" function void dpic_mem_write(input  longint unsigned addr, input  int unsigned wdata, input  byte unsigned wmask);

// 正在加突发传输
module dpic_mem #(
`ifdef DATA_MEM_DELAY
  parameter DELAY = `DATA_MEM_DELAY,   // 设备服务时间 k 的组成部分
`else
  parameter DELAY = 1,
`endif
  parameter R     = 1                  // ★ 频率比 r: 设备 1 拍 → CPU 视角 R 拍
)(
  // Clock
  input  wire         clk,

  // AXI4-Lite AR (read address)
  input  wire [31:0]  araddr,
  input  wire         arvalid,
  output wire         arready,
  input  wire [7:0]   arlen,

  // AXI4-Lite R (read data)
  output reg  [31:0]  rdata,
  output reg  [1:0]   rresp,
  output reg          rvalid,
  input  wire         rready,
  output reg          rlast,      // 本次突发最后一拍; arlen=0 时恒 1

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

  assign rresp = 2'b00;   // OKAY
  assign bresp = 2'b00;   // OKAY

  // 写事务的两段锁存:AW 先到锁地址/掩码, 置 aw_recv 等 W;
  // W 到时直接提交(用当拍 wdata, 不延迟锁存, 见下方说明)。
  // 注意: 不能用 w_data_latch 延迟锁存再提交 —— 当 AW/W 同拍到达时,
  // 非阻塞赋值的 w_data_latch 当拍未更新, 提交会用到旧值(0), 导致 store 写错数据。
  // master 在 wready=1 期间保证 wdata 稳定, 故提交时直接用 wdata 即可。
  reg        aw_recv;
  reg [31:0] aw_addr_latch;
  reg [3:0]  w_mask_latch;

    // ══════════ 写通道: 写响应延迟 ══════════
  reg [15:0] cnt;
  reg        wr_delay;

  // ══════════ 读通道: 4 状态机 ══════════
  localparam R_IDLE  = 2'd0,   // 等 AR 握手
             R_DELAY = 2'd1,   // 等 (DELAY+1)*R 拍
             R_DATA  = 2'd2,   // rvalid=1, 等 rready
             R_NEXT  = 2'd3;   // 换下一个数据(这一拍不举牌)

  reg [1:0]  rd_state;
  reg [15:0] rd_cnt;
  reg [7:0]  rd_len;      // 本次突发拍数-1
  reg [7:0]  rd_beat;     // 已完成第几拍
  reg [31:0] rd_base;     // 本次突发首地址

  initial
  begin
    rvalid   = 1'b0;
    rlast    = 1'b0;
    bvalid   = 1'b0;
    aw_recv  = 1'b0;
    wr_delay = 1'b0;
    rd_state = R_IDLE;
  end

  // ready: 读在 R_IDLE 且无写事务时才收 AR; 写在读空闲且无挂起响应时收 AW
  assign arready = !aw_recv && !rvalid && (rd_state == R_IDLE) && !wr_delay;  //正在等写响应，不能开新事务
  assign awready = !aw_recv && !bvalid && (rd_state == R_IDLE) && !wr_delay;
  assign wready  = aw_recv; // 它不回答“我能不能开始一次新事务”（那是 awready 的事）。

  // ── 写通道: 独立 always ──
  always @(posedge clk)
  begin
    if (bvalid && bready) bvalid <= 1'b0;

    if (awvalid && awready)
    begin
      aw_addr_latch <= awaddr;
      w_mask_latch  <= wmask;
      aw_recv       <= 1'b1;
    end

    if (aw_recv && wvalid && wready)
    begin
      dpic_mem_write({32'b0, aw_addr_latch}, wdata, {4'b0, w_mask_latch});
      aw_recv  <= 1'b0;
      wr_delay <= 1'b1;
      cnt      <= ((DELAY + 2) * R) - 2;
    end
    else if (wr_delay)
    begin
      if (cnt == 1) begin bvalid <= 1'b1; wr_delay <= 1'b0; end
      else cnt <= cnt - 1;
    end
  end

  // ── 读通道: 状态机 ──
  always @(posedge clk)
  begin
    case (rd_state)
      // 等 AR; 握手当拍锁参数、读首字、起延迟
      R_IDLE:
        if (arvalid && arready)
        begin
          dpic_mem_read({32'b0, araddr}, rdata); // 读第一个字
          rd_len   <= arlen;      // 要发几个
          rd_base  <= araddr;
          rd_beat  <= 8'd0;     // 发送数据个数
          rd_cnt   <= ((DELAY + 1) * R) - 1;
          rd_state <= R_DELAY;
        end

      // 倒计时结束 → 举牌
      R_DELAY:
        if (rd_cnt == 1)
        begin
          rvalid   <= 1'b1;
          rlast    <= (rd_len == 8'd0);
          rd_state <= R_DATA;
        end
        else rd_cnt <= rd_cnt - 1;

      // 举牌等客户取; 交接这一拍不动 rdata
      R_DATA:
        if (rready)
        begin
          rvalid <= 1'b0;  // 拿走数据就清理
          if (rd_beat == rd_len)    // 全拿走了
          begin
            rlast    <= 1'b0;   // rlast的清零
            rd_state <= R_IDLE;
          end
          else
            rd_state <= R_NEXT;
        end

      // 取下一个货(这一拍不举牌, 所以可以安全改 rdata)
      R_NEXT:
        begin
          dpic_mem_read({32'b0, rd_base + ({24'd0, rd_beat} << 2) + 32'd4}, rdata);  // 已经是第二个了
          rd_beat  <= rd_beat + 8'd1;
          rlast    <= ((rd_beat + 8'd1) == rd_len);
          rvalid   <= 1'b1;
          rd_state <= R_DATA;
        end

      default: rd_state <= R_IDLE;
    endcase
  end


endmodule
