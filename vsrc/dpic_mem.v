// DPI-C 内存:AXI4-Lite 从设备, 自身不存数据, 读/写都通过 DPI-C 转发到 NEMU pmem。
// 两个实例(i_mem / d_mem)各例化一个, 总线接入方式完全一致, 物理内存真相只在 NEMU pmem 一处。
// 这样 NPC 取指/访存不受 Verilog 数组容量限制, amtest 这种大镜像也能直接跑。
//

import "DPI-C" function void dpic_mem_read (input  longint unsigned addr, output int unsigned rdata);
import "DPI-C" function void dpic_mem_write(input  longint unsigned addr, input  int unsigned wdata, input  byte unsigned wmask);

module dpic_mem #(
`ifdef DATA_MEM_DELAY
  parameter DELAY = `DATA_MEM_DELAY                     // from menuconfig
`else
  parameter DELAY = 1                                   // default: SRAM speed
`endif
)(
  // Clock
  input  wire         clk,

  // AXI4-Lite AR (read address)
  input  wire [31:0]  araddr,
  input  wire         arvalid,
  output wire         arready,

  // AXI4-Lite R (read data)
  output reg  [31:0]  rdata,
  output reg  [1:0]   rresp,
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


  reg [15:0] cnt;
  reg        rd_delay;
  reg        wr_delay;
  wire busy = rd_delay || wr_delay; //只要有一个delay 就是busy


  initial
  begin
    rvalid   = 1'b0;
    bvalid   = 1'b0;
    aw_recv  = 1'b0;
    rd_delay = 1'b0;
    wr_delay = 1'b0;
  end

  // ready 由组合条件驱动(纯 AXI slave 靠 ready 握手自然反压, 不接外部 stall):
  //   - arready: 无挂起读响应且未在写事务中时接收 AR
  //   - awready: 无挂起写响应且未在写事务中时接收 AW
  //   - wready : AW 已收后, 等 W
  assign arready = !aw_recv && !rvalid && !busy;
  assign awready = !aw_recv && !bvalid && !busy;
  assign wready  = aw_recv;//收到地址了

  always @(posedge clk)
  begin
    if (rvalid && rready) rvalid <= 1'b0;   // 清上一次未被取走的读响应
    if (bvalid && bready) bvalid <= 1'b0;   // 清上一次未被取走的写响应

    // 读: AR 握手当拍即调 DPI 读 NEMU pmem(4 字节对齐, 由 LSU 用 addr[1:0] 选字节), 锁存后下一拍 rvalid
    if (arvalid && arready)
    begin
      // 地址零扩展为 64 位(DPIC 协议要求 longint unsigned), 高位补 0 不丢信息
      dpic_mem_read({32'b0, araddr}, rdata);
      rd_delay <= 1'b1;
      cnt <= DELAY;
    end
    else if(rd_delay)
    begin
        if(cnt == 1)
        begin
            rvalid <= 1'b1; //延迟结束才返回read valid
            rd_delay <= 1'b0;
        end
        else    cnt <= cnt - 1;
    end


    // 写地址: AW 握手时锁存地址/掩码, 置 aw_recv 等 W
    if (awvalid && awready)
    begin
      aw_addr_latch <= awaddr;
      w_mask_latch <= wmask;
      aw_recv      <= 1'b1;
    end

    // 写提交: AW 与 W 都到, 调 DPI 写回 pmem, 置 B 响应。
    // 直接用当拍 wdata (master 在 wvalid&&wready 时保证 wdata 有效且稳定),
    // 不依赖延迟锁存, 避免 AW/W 同拍到达时取到旧 w_data_latch。
    if (aw_recv && wvalid && wready)
    begin
      // 地址零扩展 64 位; wmask 零扩展 8 位(C 侧只取低 4 位, 高位补 0 无影响)
      dpic_mem_write({32'b0, aw_addr_latch}, wdata, {4'b0, w_mask_latch});
      aw_recv <= 1'b0;
      wr_delay <= 1'b1;
      cnt <= DELAY;
    end
    else if(wr_delay)
    begin
        if(cnt == 1)
        begin
            bvalid  <= 1'b1;
            wr_delay <= 1'b0;
        end
        else cnt <= cnt - 1;
    end


  end

endmodule
