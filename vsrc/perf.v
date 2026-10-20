module perf (
    input clk, input rst, input halt,

    // ── 相位通道: 每通道一对 ──
    input ifu_done, input at_ifu,
    input lsu_done, input at_lsu,

    // ── 指令类别: 门 retire + 各类判定(retire 拍有效) ──
    input retire,
    input is_alu, is_lui, is_load, is_store, is_branch, is_jump, is_csr, is_sys
);
    // ══ ① 相位通道: 每通道一行 ══
    wire [31:0] ifu_ev, ifu_cyc, lsu_ev, lsu_cyc;
    perf_counter u_ifu (.clk(clk), .rst(rst), .ev(ifu_done), .ph(at_ifu),
                        .cnt_ev(ifu_ev), .cnt_cyc(ifu_cyc));
    perf_counter u_lsu (.clk(clk), .rst(rst), .ev(lsu_done), .ph(at_lsu),
                        .cnt_ev(lsu_ev), .cnt_cyc(lsu_cyc));

    // ══ ② 指令类别直方图: 门 = retire, 每类一行 ══
    reg [31:0] c_alu, c_lui, c_load, c_store, c_br, c_jmp, c_csr, c_sys;
    always @(posedge clk) 
    begin
        if (rst) begin
            c_alu<=0; c_lui<=0; c_load<=0; c_store<=0;
            c_br<=0;  c_jmp<=0; c_csr<=0;  c_sys<=0;
        end 
        else if (retire) 
        begin          // ★ 每条指令只 +1 一次
            if (is_alu)    c_alu   <= c_alu   + 32'd1;
            if (is_lui)    c_lui   <= c_lui   + 32'd1;
            if (is_load)   c_load  <= c_load  + 32'd1;
            if (is_store)  c_store <= c_store + 32'd1;
            if (is_branch) c_br    <= c_br    + 32'd1;
            if (is_jump)   c_jmp   <= c_jmp   + 32'd1;
            if (is_csr)    c_csr   <= c_csr   + 32'd1;
            if (is_sys)    c_sys   <= c_sys   + 32'd1;
        end
    end

    reg [31:0] gap;   // 距上次退休的拍数
    reg [31:0] cyc_alu, cyc_lui, cyc_load, cyc_store, cyc_br, cyc_jmp, cyc_csr, cyc_sys;
    always @(posedge clk) 
    begin
        if (rst) 
        begin 
            gap<=0; cyc_alu<=0; cyc_lui<=0; cyc_load<=0; cyc_store<=0;

            cyc_br<=0;  cyc_jmp<=0; cyc_csr<=0;  cyc_sys<=0; 
        end
        else if (retire) 
        begin
            gap <= 0;
            if (is_alu)    cyc_alu   <= cyc_alu   + gap + 32'd1;
            if (is_lui)    cyc_lui   <= cyc_lui   + gap + 32'd1;
            if (is_load)   cyc_load  <= cyc_load  + gap + 32'd1;
            if (is_store)  cyc_store <= cyc_store + gap + 32'd1;
            if (is_branch) cyc_br    <= cyc_br    + gap + 32'd1;
            if (is_jump)   cyc_jmp   <= cyc_jmp   + gap + 32'd1;
            if (is_csr)    cyc_csr   <= cyc_csr   + gap + 32'd1;
            if (is_sys)    cyc_sys   <= cyc_sys   + gap + 32'd1;
        end 
        else gap <= gap + 32'd1;
    end


    // ══ ③ 停机打印一次 ══
    reg halt_r;
    wire [31:0] total_insts;
    assign  total_insts = c_alu + c_lui + c_load + c_store + c_br + c_jmp + c_csr + c_sys; 
    wire [31:0] total_cycs;
    assign total_cycs = cyc_alu + cyc_lui + cyc_load + cyc_store + cyc_br + cyc_jmp + cyc_csr + cyc_sys;



    // ══ ④ AMAT 统计 (讲义「统计AMAT」) ══
    //   全部用 64 位算, 避免 *100 溢出(60M 指令时 ifu_cyc 可达 3e8)
    wire [31:0] hits    = total_insts - ifu_ev;
    wire [63:0] amat100 = ({32'd0, ifu_cyc} * 64'd100) / {32'd0, total_insts};   // AMAT × 100
    wire [63:0] mr1000  = ({32'd0, ifu_ev}  * 64'd1000) / {32'd0, total_insts};  // miss_rate × 1000
    wire [63:0] mlat100 = (ifu_ev == 32'd0) ? 64'd100 :
                          ({32'd0, (ifu_cyc - hits)} * 64'd100) / {32'd0, ifu_ev}; // miss_lat × 100
    wire [63:0] dmat100 = (lsu_ev == 32'd0) ? 64'd0 :
                          ({32'd0, lsu_cyc} * 64'd100) / {32'd0, lsu_ev};          // data AMAT × 100





    always @(posedge clk) 
    begin
        halt_r <= halt;                     // ★ 非阻塞
        if (halt && !halt_r) 
        begin
            $display("[perf] ifu  ev=%0d cyc=%0d", ifu_ev, ifu_cyc);
            $display("[perf] lsu  ev=%0d cyc=%0d", lsu_ev, lsu_cyc);
            $display("[perf] alu insts: %0d  cycles: %0d cpi is %0d", c_alu, cyc_alu, cyc_alu/c_alu);
            $display("[perf] lui insts: %0d  cycles: %0d cpi is %0d", c_lui, cyc_lui, cyc_lui/c_lui);
            $display("[perf] load insts: %0d  cycles: %0d cpi is %0d", c_load, cyc_load, cyc_load/c_load);
            $display("[perf] store insts: %0d  cycles: %0d cpi is %0d", c_store, cyc_store, cyc_store/c_store);
            $display("[perf] branch insts: %0d  cycles: %0d cpi is %0d", c_br, cyc_br, cyc_br/c_br);
            $display("[perf] jmp insts: %0d  cycles: %0d cpi is %0d", c_jmp, cyc_jmp, cyc_jmp/c_jmp);
            $display("[perf] csr insts: %0d  cycles: %0d cpi is %0d", c_csr, cyc_csr, cyc_csr/c_csr);
            $display("[perf] sys insts: %0d  cycles: %0d cpi is %0d", c_sys, cyc_sys, cyc_sys/c_sys);

            $display("[perf] Total insts: %0d",
                     total_insts);
            $display("[perf] Total cycles: %0d",
                     total_cycs);
            $display("[perf] Total cpi: %0d", total_cycs/total_insts);

            $display("[perf] ---------- AMAT ----------");
            $display("[perf] AMAT          : %0d.%02d cyc", amat100/100, amat100%100);
            $display("[perf]   hit_time    : 1.00 cyc");
            $display("[perf]   miss_rate   : %0d.%01d%%", mr1000/10, mr1000%10);
            $display("[perf]   miss_latency: %0d.%02d cyc", mlat100/100, mlat100%100);
            $display("[perf]   miss_penalty: %0d.%02d cyc", (mlat100-100)/100, (mlat100-100)%100);
            $display("[perf] data AMAT     : %0d.%02d cyc", dmat100/100, dmat100%100);




        end
    end



endmodule
