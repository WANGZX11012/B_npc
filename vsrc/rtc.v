import "DPI-C" function longint rtc_time_us();

//相当于slave

module rtc (
    input               clk,
    //AR
    input [31:0]        araddr,
    input               arvalid,
    output              arready,
    //R
    output reg [31:0]   rdata,
    output reg [1:0]    rresp,
    output reg          rvalid,
    input               rready
);

    assign  arready = 1'b1;

    // 关键: rtc_time_us() 是无输入 DPI-C 调用,不能放在 wire 连续赋值里
    // (Verilator 会当常量只求值一次)。必须放进时钟沿内,每个周期采样。
    reg [63:0] now_us;

    always@(posedge clk)
    begin
        now_us <= rtc_time_us();   // 每周期都调用 DPI-C,拿到最新墙钟
        if(arvalid && arready)//ar done
        begin
            rdata  <= (araddr[3:2] == 2'b11) ? now_us[63:32] : now_us[31:0];
            rresp  <= 2'b00;            // OKAY
            rvalid <= 1'b1;
        end
        else if(rready && rvalid)
            rvalid <= 0; //取走清零
    end

    
endmodule

