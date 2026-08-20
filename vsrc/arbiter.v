module arbiter (
  input  wire         clk,
  input  wire         rst,

  // ── IFU 私有请求（只读）──
  input  wire         ifu_req_valid,
  input  wire [31:0]  ifu_req_addr,
  output wire         ifu_done,
  output wire [31:0]  ifu_resp_rdata,

  // ── LSU 私有请求（读写）──
  input  wire         lsu_req_valid,
  input  wire         lsu_req_we,        // 接 ctrl 的 mem_we
  input  wire [31:0]  lsu_req_addr,
  input  wire [31:0]  lsu_req_wdata,
  input  wire [3:0]   lsu_req_wstrb,
  output wire         lsu_done,
  output wire [31:0]  lsu_resp_rdata,

  // ── 合并后的单请求 → axi_lite_master ──
  output wire         m_req_valid,
  output wire         m_req_we,
  output wire [31:0]  m_req_addr,
  output wire [31:0]  m_req_wdata,
  output wire [3:0]   m_req_wstrb,
  input  wire         m_done,
  input  wire [31:0]  m_resp_rdata
);

  // ── 归属锁存：空闲时来了新请求，锁存这单是谁的（IFU 固定优先）──
  reg        sel_is_ifu;
  reg        m_valid_r;

  always @(posedge clk)
  begin
    if (rst)
    begin
      sel_is_ifu <= 1'b0;
      m_valid_r  <= 1'b0;
    end
    else if (m_valid_r)                    // 交易进行中
    begin
      if (m_done)                          // 完成，释放总线
        m_valid_r <= 1'b0;
      // sel_is_ifu 保持不动，保证转发不中途切换
    end
    else if (ifu_req_valid || lsu_req_valid)  // 空闲，新请求来了
    begin
      sel_is_ifu <= ifu_req_valid;         // IFU 优先：ifu 有请求就选 ifu
      m_valid_r  <= 1'b1;                  // 下一拍才转发，让 sel 先稳定
    end
  end

  // ── 转发：用锁存的 sel，保证整个交易期间 payload 稳定 ──
  assign m_req_valid = m_valid_r;
  assign m_req_we    = sel_is_ifu ? 1'b0    : lsu_req_we;
  assign m_req_addr  = sel_is_ifu ? ifu_req_addr : lsu_req_addr;
  assign m_req_wdata = sel_is_ifu ? 32'b0   : lsu_req_wdata;
  assign m_req_wstrb = sel_is_ifu ? 4'b0    : lsu_req_wstrb;

  // ── 响应路由：done/rdata 只给归属方 ──
  assign ifu_done       = m_done &&  sel_is_ifu;
  assign lsu_done       = m_done && !sel_is_ifu;
  assign ifu_resp_rdata = m_resp_rdata;   // 输家 done=0 不会采，直接都接即可
  assign lsu_resp_rdata = m_resp_rdata;

endmodule
