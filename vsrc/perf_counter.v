// 一个相位通道: 事件脉冲→次数, 相位电平→周期
module perf_counter (
    input             clk,
    input             rst,
    input             ev,        // 本拍发生一次的事件(脉冲)
    input             ph,        // 本拍处于该相位(电平)
    output reg [31:0] cnt_ev,
    output reg [31:0] cnt_cyc
);
    always @(posedge clk) 
    begin
        if (rst) 
        begin
            cnt_ev  <= 32'b0;
            cnt_cyc <= 32'b0;
        end 
        else 
        begin
            if (ev) cnt_ev  <= cnt_ev  + 32'b1;
            if (ph) cnt_cyc <= cnt_cyc + 32'b1;
        end
    end
endmodule