
module  ysyx_26020047_axi_master(

    input       clk,
    input       rst,

   // ── 简单请求侧（IFU/LSU 喂进来）──
    input           req_valid,      // 持续拉高直到 done（= fetch_req / do_req）
    input           req_we,         // 0=读, 1=写
    input  [31:0]   req_addr,
    input  [31:0]   req_wdata,
    input  [3:0]    req_wstrb,
    input           stall,          // LFSR 随机停顿（无 LFSR 时接 0）

    //完成标志
    output          done,
    output [31:0]   resp_rdata,     //  返回的读数据   
    output          resp_err,       //  出错误       


    /**axilite接口 把master信号翻译成从设备能看得懂的东西**/
    
    //axi4 AR(address read) 读地址给slave
    output  [3:0]    arid,      // 读事务 ID(无乱序请求, 恒 0)
    output  [31:0]   araddr,
    output  [7:0]    arlen,     // 突发拍数-1(恒 0 = 单拍, 不是 0 拍)
    output  [2:0]    arsize,    // 每拍字节数 = 2^arsize(恒 2 = 4 字节)
    output  [1:0]    arburst,   // 突发类型(恒 2'b01 = INCR)
    output           arvalid,
    input            arready,
    //R 从slave取数据 给master , rresp是判断读的数据是否合法的标记 rready表示master空闲 可以接收读的数据
    input   [3:0]    rid,       // 返回 ID 检查与arid相同
    input   [31:0]   rdata,
    input            rvalid,
    input   [1:0]    rresp,
    input            rlast,     // 读最后一拍标志(R 通道唯一的结束标记) 判断突发读是否结束
    output           rready,
    //AW(address write) 写地址给slave
    output  [3:0]    awid,      // 写事务 ID(无乱序请求, 恒 0)
    output  [31:0]   awaddr,
    output  [7:0]    awlen,     // 突发拍数-1(恒 0 = 单拍)
    output  [2:0]    awsize,    // 每拍字节数 = 2^awsize(恒 2 = 4 字节)
    output  [1:0]    awburst,   // 突发类型(恒 2'b01 = INCR)
    output           awvalid,
    input            awready,
    //W master2slave 写什么数据, wstrb 是字节写使能
    output  [31:0]  wdata,
    output          wvalid,
    output  [3:0]   wstrb,      // 字节写使能(原 wmask, 与 cpu-interface.md 对齐)
    output          wlast,      // 写最后一拍标志(单拍恒 1) 发给slave 这是我最后一拍数据
    input           wready,
    //B s2m 写成功的回应 bready是master准备好收bvalid的信号
    input   [3:0]   bid,        // 返回写事务 ID(与 awid 同源恒 0, 无需核对)
    input   [1:0]   bresp,
    input           bvalid,
    output          bready


);

localparam  [2:0]   IDLE = 3'b000, AR = 3'b001, R = 3'b010, AW = 3'b011, W = 3'b100, B = 3'b101;

reg [2:0] state, next_state;

always @(posedge clk) 
begin
    if(rst)
        state <= IDLE;
    else 
    begin
        state <= next_state;
    end    
end

always @(*) 
begin
    case (state)
        IDLE:
            next_state = (req_valid && !stall) ? (req_we ? AW : AR) : IDLE;
        AR:
            next_state = arready ? R : AR;
        R:
            next_state = (rvalid && rlast && !stall) ? IDLE : R;  // 引入rlast检验
        AW:
            next_state = awready ? W : AW;
        W:
            next_state = (wready && wlast)? B : W;   //只有last为高 才能进入B状态
        B:
            next_state = (bvalid && !stall) ? IDLE : B; 

        default:    next_state = IDLE;
    endcase    
end




//AR
// ── AXI4 单拍读的固定字段(与状态机无关, 故用常量 assign) ──
assign arvalid = (state == AR);   // 地址通道有效(AR 状态期间拉高)
assign arid    = 4'd0;
assign arlen   = 8'd0;      // 1 拍
assign arsize  = 3'd2;      // 4 字节
assign arburst = 2'b01;     // INCR
assign araddr = req_addr;   //axi暂时设置读写地址是一个
//R
assign rready = (state == R) && !stall;
assign resp_rdata = rdata;
//AW
assign awvalid = (state == AW); //根据axi协议 valid信号一旦拉高就不能降低
assign awid    = 4'd0;
assign awlen   = 8'd0;      // 1 拍
assign awsize  = 3'd2;      // 4 字节
assign awburst = 2'b01;     // INCR
assign awaddr = req_addr;
//W
assign wdata = req_wdata;
assign wvalid = (state == W);
assign wstrb = req_wstrb; // wmask 写掩码赋值
assign wlast = 1'b1;      // 默认单拍写
//B
assign bready = state == B && !stall;


/** 完成信号 **/
assign done = (rready && rvalid  && rlast)|| (bvalid && bready); //读或写完成 握手完成

wire rd_err = rready && rvalid && rlast && rresp[1]; 
// 报错是在要真正传递数据的时候出现的
// resp高 bit 为 1 就代表错误（见下表），用它一句就能同时覆盖 SLVERR 和 DECERR
// rlast 保证一个事务一个报错 如果是多拍的传输 最后一拍才拉高
wire wr_err = bvalid && bready && bresp[1];
assign resp_err = rd_err || wr_err;
// assign resp_err = done && (req_addr == 32'h10000000);




endmodule










