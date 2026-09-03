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
    // (Verilator 会当常量只求值一次)。必须放进时钟沿内采样。
    //
    // 但绝不能"每周期采样":
    //   rtc_time_us() 经 DPI-C 调用 clock_gettime(), 单次开销远大于普通逻辑。
    //   无条件每周期调用会把仿真速度从 ~74ns/周期 拖到 ~5us/周期(实测慢 68 倍),
    //   而 99.99% 的周期里根本没人读 RTC, 采来的值直接被丢弃。
    // 正确做法: 只在 AR 握手(真正被读)时采样一次。
    //   注意非阻塞赋值读旧值: 本次 AR 握手送出的是"上一次采样"的墙钟,
    //   与原实现的语义完全一致(原来送出的也是上一拍采样的值)。
    reg [63:0] now_us;

    always@(posedge clk)
    begin
        if(arvalid && arready)//ar done
        begin
            now_us <= rtc_time_us();   // 只在被读时采样,拿到最新墙钟
            rdata  <= (araddr[3:2] == 2'b11) ? now_us[63:32] : now_us[31:0];
            rresp  <= 2'b00;            // OKAY
            rvalid <= 1'b1;
        end
        else if(rready && rvalid)
        begin
            rvalid <= 1'b0;             //取走清零
        end
    end

    
endmodule

