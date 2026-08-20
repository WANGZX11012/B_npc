module  axi_lite_master(

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


    /**axilite接口 把master信号翻译成从设备能看得懂的东西**/
    
    //axi4-lite AR(address read) 读地址给slave
    output  [31:0]   araddr,    output  arvalid,    input arready,
    //R 从slave取数据 给master , rresp是判断读的数据是否合法的标记 rready表示master空闲 可以接收读的数据
    input   [31:0]  rdata,  input   rvalid, input   [1:0]   rresp,  output rready,
    //AW
    output  [31:0]  awaddr, output  awvalid,    input awready,
    //W master2slave 写什么数据 多个wmask 写的字节选择
    output  [31:0]  wdata,  output  wvalid, output  [3:0] wmask,  input   wready,
    //B s2m 写成功的回应 bready是master准备好收bvalid的信号
    input   [1:0]   bresp,  input   bvalid, output  bready

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
            next_state = (rvalid && !stall) ? IDLE : R; 
        AW:
            next_state = awready ? W : AW;
        W:
            next_state = wready ? B : W;
        B:
            next_state = (bvalid && !stall) ? IDLE : B; 

        default:    next_state = IDLE;
    endcase    
end


assign wmask = req_wstrb; //wmask 写掩码赋值

//AR
assign araddr = req_addr;   //axi暂时设置读写地址是一个
assign arvalid = (state == AR);
//R
assign rready = (state == R) && !stall;
//AW
assign awaddr = req_addr;
assign awvalid = (state == AW); //根据axi协议 valid信号一旦拉高就不能降低
//W
assign wdata = req_wdata;
assign wvalid = state == W;
//B
assign bready = state == B && !stall;


/** 完成信号 **/
assign done = rready && rvalid || bvalid && bready; //读或写完成 握手完成
assign resp_rdata = rdata;



endmodule










