module arbiter_pipe (
    input   wire        clk,
    input   wire        rst, 
    // ──   . IFU 侧: 实际来自 icache 的 mem_* (只读, 带 burst) ──
    input   wire        ifu_req_valid,    // icache.mem_req_valid: miss 时只给一拍脉冲
    input   wire [31:0] ifu_req_addr,     // 块首地址 (burst 期间需保持稳定)
    input   wire [7:0]  ifu_req_len,      // icache.mem_req_len = WORDS-1, 默认 3 (4 拍)
    output  wire        ifu_ready,        // ★ 专属: 参与 if_id_ready, 冻住前端
    output  wire        ifu_done,         // → icache.mem_done: 整个 refill 事务结束
    output  wire [31:0] ifu_rdata,        // → icache.mem_rdata
    output  wire        ifu_rvalid,       // ★ burst: 每拍数据有效(门控后给 icache.mem_rvalid)  
    // ──   . LSU 侧: 来自 lsu_pipe (读写, 恒单拍) ──
    input   wire        lsu_req_valid,
    input   wire        lsu_req_we,       // 1=store, 0=load
    input   wire [31:0] lsu_req_addr,
    input   wire [31:0] lsu_req_wdata,    // 已按字节摆位
    input   wire [3:0]  lsu_req_wstrb,    // 字节写使能
    output  wire        lsu_ready,        // ★ 专属: 参与 mem_ready, 冻住 MEM 段
    output  wire        lsu_done,         // → lsu_pipe.handshake_done
    output  wire [31:0] lsu_rdata,        // → lsu_pipe.rdata_in 
    // ──   . 合并后 → axi_lite_master 的简单请求侧 ──
    output  wire        m_req_valid,      // 电平: 保持拉高直到 m_done (见 master 第 8 行注释)
    output  wire        m_req_we,
    output  wire [31:0] m_req_addr,
    output  wire [31:0] m_req_wdata,
    output  wire [3:0]  m_req_wstrb,
    output  wire [7:0]  m_req_len,        // 仅 IFU 侧透传, LSU 恒 0
    input   wire        m_done,           // master.done: 事务完成(读=rlast 那拍, 写=bvalid)
    input   wire [31:0] m_rdata,          // master.resp_rdata
    input   wire        m_rvalid          // ★ master 的 AXI R 通道 rvalid (core.v 里叫 mst_rvalid)
);


reg is_sel_ifu;
reg m_req_valid_r;  // 锁存请求
reg ifu_pending_r;  // 已发起 但是尚未响应的请求

always @(posedge clk)
begin
    if (rst)
        ifu_pending_r <= 1'b0;
    else if (ifu_req_valid)
        ifu_pending_r <= 1'b1;        // 置起优先: 完成拍若又来新 miss, 不能丢
    else if (m_done && m_req_valid_r && is_sel_ifu)
        ifu_pending_r <= 1'b0;        // 整笔 refill 完成才清
end



always @(posedge clk) 
begin
    if(rst)
    begin
        is_sel_ifu <= 1'b0;
        m_req_valid_r <= 1'b0;
    end
    else if (m_req_valid_r)             // 交易进行中: 不接新单
    begin
        if (m_done)
            m_req_valid_r <= 1'b0;     // done 才释放总线
        // is_sel_ifu 保持不动: 整个 burst 不许换主
    end
    else 
    begin
        if(ifu_req_valid || lsu_req_valid || ifu_pending_r) // 竞争mem 还要reqvalid 因为那一拍pending还没来
        begin
            is_sel_ifu <= !lsu_req_valid; // lsu优先
            m_req_valid_r <= 1'b1; // 第二拍拉高req
        end    
    end

end

wire lsu_finished = m_done && m_req_valid_r && !is_sel_ifu; // lsu 取数据完成
wire ifu_finished = m_done && m_req_valid_r && is_sel_ifu;

assign lsu_ready = !lsu_req_valid || lsu_finished;
  // IFU 有单未服务(含排队中 + burst 进行中) → 冻住前端
assign ifu_ready = !ifu_pending_r;

assign m_req_we    = is_sel_ifu ? 1'b0   : lsu_req_we;
assign m_req_addr  = is_sel_ifu ? ifu_req_addr  : lsu_req_addr;
assign m_req_wdata = is_sel_ifu ? 32'b0  : lsu_req_wdata;
assign m_req_wstrb = is_sel_ifu ? 4'b0   : lsu_req_wstrb;
assign m_req_len   = is_sel_ifu ? ifu_req_len : 8'd0;  // LSU 不 burst
assign m_req_valid = m_req_valid_r;

assign ifu_done = ifu_finished;
assign lsu_done = lsu_finished;
assign ifu_rdata = is_sel_ifu && m_req_valid_r ? m_rdata : 32'b0;
assign lsu_rdata = !is_sel_ifu && m_req_valid_r ? m_rdata : 32'b0;

assign ifu_rvalid = m_rvalid && m_req_valid_r && is_sel_ifu; // 三顶门控

endmodule
