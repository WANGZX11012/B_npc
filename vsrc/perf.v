// ============================================================================
// perf — 性能计数器 (仿真专用; 由 core.v 用 `ifdef PERF_ENABLE 控制例化)
//
// 统计口径 (三条铁律, 别混):
//   ① 相位通道 ifu/lsu: ev = 事件次数, cyc = 处于该相位的周期数
//      ★ 有 ICACHE 后 ifu_ev 是 "ICACHE→内存" 的事务数 = miss 次数, 不是取指次数
//   ② 指令分类: 门 = retire; cyc = 从上次 retire 到本次的全部拍 (gap+1)
//      ★ 分类 cyc 互相重叠(都含取指), 不能相加当占比; 只有 ① 能当 Amdahl 的 f
//   ③ 自校验: retire_cnt / total_insts / total_cycs / cycles 必须两两对上
// ============================================================================
module perf (
    input clk, input rst, input halt,

    input ifu_done, input at_ifu,
    input lsu_done, input at_lsu,

    input retire,
    input is_alu, is_lui, is_load, is_store, is_branch, is_jump, is_csr, is_sys
);

    // ══ 停机冻结: halt 拉起那一拍仍计数, 之后停止 (躲开 cpu-exec 的 100 拍尾巴) ══
    reg halt_r;
    always @(posedge clk)
    begin
        if (rst) halt_r <= 1'b0;
        else     halt_r <= halt;
    end
    wire en = !halt_r;

    // ══ 64 位安全运算 (分母 0 一律返回 0, 永不除零) ══
    function [63:0] udiv;
        input [63:0] a; input [63:0] b;
        begin udiv = (b == 64'd0) ? 64'd0 : (a / b); end
    endfunction
    function [63:0] umod;
        input [63:0] a; input [63:0] b;
        begin umod = (b == 64'd0) ? 64'd0 : (a % b); end
    endfunction
    function [63:0] upct;            // a/b × 100  (取两位小数用)
        input [63:0] a; input [63:0] b;
        begin upct = (b == 64'd0) ? 64'd0 : (a * 64'd100) / b; end
    endfunction

    // ══ ① 相位通道 ══
    wire [63:0] ifu_ev, ifu_cyc, lsu_ev, lsu_cyc;
    perf_counter u_ifu (.clk(clk), .rst(rst),
                        .ev(ifu_done && en), .ph(at_ifu && en),
                        .cnt_ev(ifu_ev), .cnt_cyc(ifu_cyc));
    perf_counter u_lsu (.clk(clk), .rst(rst),
                        .ev(lsu_done && en), .ph(at_lsu && en),
                        .cnt_ev(lsu_ev), .cnt_cyc(lsu_cyc));

    // ══ ② 指令分类 + 归因周期 (全 64 位, 一个 always 里统一门控) ══
    reg [63:0] c_alu,   c_lui,   c_load,   c_store,   c_br,   c_jmp,   c_csr,   c_sys;
    reg [63:0] cyc_alu, cyc_lui, cyc_load, cyc_store, cyc_br, cyc_jmp, cyc_csr, cyc_sys;
    reg [63:0] gap;          // 距上次 retire 的拍数
    reg [63:0] retire_cnt;   // 自校验 1: retire 拍数
    reg [63:0] cycles;       // 自校验 2: 总周期

    always @(posedge clk)
    begin
        if (rst)
        begin
            gap <= 64'd0; cycles <= 64'd0; retire_cnt <= 64'd0;
            c_alu <= 64'd0; c_lui <= 64'd0; c_load <= 64'd0; c_store <= 64'd0;
            c_br  <= 64'd0; c_jmp <= 64'd0; c_csr  <= 64'd0; c_sys   <= 64'd0;
            cyc_alu <= 64'd0; cyc_lui <= 64'd0; cyc_load <= 64'd0; cyc_store <= 64'd0;
            cyc_br  <= 64'd0; cyc_jmp <= 64'd0; cyc_csr  <= 64'd0; cyc_sys   <= 64'd0;
        end
        else if (en)
        begin
            cycles <= cycles + 64'd1;

            if (retire)
            begin
                retire_cnt <= retire_cnt + 64'd1;
                gap <= 64'd0;
                if (is_alu)    begin c_alu   <= c_alu   + 64'd1; cyc_alu   <= cyc_alu   + gap + 64'd1; end
                if (is_lui)    begin c_lui   <= c_lui   + 64'd1; cyc_lui   <= cyc_lui   + gap + 64'd1; end
                if (is_load)   begin c_load  <= c_load  + 64'd1; cyc_load  <= cyc_load  + gap + 64'd1; end
                if (is_store)  begin c_store <= c_store + 64'd1; cyc_store <= cyc_store + gap + 64'd1; end
                if (is_branch) begin c_br    <= c_br    + 64'd1; cyc_br    <= cyc_br    + gap + 64'd1; end
                if (is_jump)   begin c_jmp   <= c_jmp   + 64'd1; cyc_jmp   <= cyc_jmp   + gap + 64'd1; end
                if (is_csr)    begin c_csr   <= c_csr   + 64'd1; cyc_csr   <= cyc_csr   + gap + 64'd1; end
                if (is_sys)    begin c_sys   <= c_sys   + 64'd1; cyc_sys   <= cyc_sys   + gap + 64'd1; end
            end
            else gap <= gap + 64'd1;
        end
    end

    wire [63:0] total_insts = c_alu + c_lui + c_load + c_store + c_br + c_jmp + c_csr + c_sys;
    wire [63:0] total_cycs  = cyc_alu + cyc_lui + cyc_load + cyc_store
                            + cyc_br + cyc_jmp + cyc_csr + cyc_sys;

    // ══ ③ AMAT (统一 64 位, 除零/下溢全保护) ══
    //   HIT_TIME: ICACHE 命中时的取指周期数. 若 IFU 命中实际要 2 拍, 改这里
    localparam [63:0] HIT_TIME = 64'd1;

    wire [63:0] fetch_n = total_insts;                                   // 取指次数(1 次/指令)
    wire [63:0] miss_n  = ifu_ev;                                        // ICACHE miss 次数
    wire [63:0] hit_n   = (fetch_n > miss_n) ? (fetch_n - miss_n) : 64'd0;   // 防下溢

    wire [63:0] fetch_cyc = ifu_cyc;
    wire [63:0] hit_cyc   = hit_n * HIT_TIME;
    wire [63:0] miss_cyc  = (fetch_cyc > hit_cyc) ? (fetch_cyc - hit_cyc) : 64'd0;

    wire [63:0] amat100 = udiv(fetch_cyc * 64'd100, fetch_n);            // AMAT × 100
    wire [63:0] mr1000  = udiv(miss_n  * 64'd1000, fetch_n);             // miss_rate × 1000
    wire [63:0] mlat100 = udiv(miss_cyc * 64'd100,  miss_n);             // miss_time × 100
    wire [63:0] mpen100 = (mlat100 > HIT_TIME * 64'd100)
                        ? (mlat100 - HIT_TIME * 64'd100) : 64'd0;        // 防下溢
    wire [63:0] dmat100 = udiv(lsu_cyc * 64'd100, lsu_ev);               // 每次访存平均周期 ×100
    wire [63:0] dmpi100 = udiv(lsu_ev  * 64'd100, total_insts);          // 每条指令访存次数 ×100
    wire [63:0] ipc1000 = udiv(total_insts * 64'd1000, total_cycs);      // IPC × 1000

    // ══ ④ 停机打印一次 ══
    always @(posedge clk)
    begin
        if (halt && !halt_r)
        begin
            $display("[perf] ==================== PERF ====================");
            $display("[perf] ifu  ev=%0d (ICACHE miss)  cyc=%0d", ifu_ev, ifu_cyc);
            $display("[perf] lsu  ev=%0d (访存次数)     cyc=%0d", lsu_ev, lsu_cyc);

            $display("[perf] alu   insts=%0d cycles=%0d cpi=%0d.%02d",
                     c_alu,   cyc_alu,   udiv(cyc_alu,   c_alu),   upct(umod(cyc_alu,   c_alu),   c_alu));
            $display("[perf] lui   insts=%0d cycles=%0d cpi=%0d.%02d",
                     c_lui,   cyc_lui,   udiv(cyc_lui,   c_lui),   upct(umod(cyc_lui,   c_lui),   c_lui));
            $display("[perf] load  insts=%0d cycles=%0d cpi=%0d.%02d",
                     c_load,  cyc_load,  udiv(cyc_load,  c_load),  upct(umod(cyc_load,  c_load),  c_load));
            $display("[perf] store insts=%0d cycles=%0d cpi=%0d.%02d",
                     c_store, cyc_store, udiv(cyc_store, c_store), upct(umod(cyc_store, c_store), c_store));
            $display("[perf] br    insts=%0d cycles=%0d cpi=%0d.%02d",
                     c_br,    cyc_br,    udiv(cyc_br,    c_br),    upct(umod(cyc_br,    c_br),    c_br));
            $display("[perf] jmp   insts=%0d cycles=%0d cpi=%0d.%02d",
                     c_jmp,   cyc_jmp,   udiv(cyc_jmp,   c_jmp),   upct(umod(cyc_jmp,   c_jmp),   c_jmp));
            $display("[perf] csr   insts=%0d cycles=%0d cpi=%0d.%02d",
                     c_csr,   cyc_csr,   udiv(cyc_csr,   c_csr),   upct(umod(cyc_csr,   c_csr),   c_csr));
            $display("[perf] sys   insts=%0d cycles=%0d cpi=%0d.%02d",
                     c_sys,   cyc_sys,   udiv(cyc_sys,   c_sys),   upct(umod(cyc_sys,   c_sys),   c_sys));

            $display("[perf] Total insts : %0d", total_insts);
            $display("[perf] Total cycles: %0d", total_cycs);
            $display("[perf] Total cpi   : %0d.%02d",
                     udiv(total_cycs, total_insts), upct(umod(total_cycs, total_insts), total_insts));
            $display("[perf] IPC         : %0d.%03d",
                     udiv(ipc1000, 64'd1000), umod(ipc1000, 64'd1000));

            $display("[perf] ------ AMAT -----");
            $display("[perf] fetch_n=%0d  hit_n=%0d  miss_n=%0d", fetch_n, hit_n, miss_n);
            $display("[perf] AMAT       : %0d.%02d cyc", udiv(amat100,64'd100), umod(amat100,64'd100));
            $display("[perf] hit_time   : 1.00 cyc (HIT_TIME 参数, 需实测确认)");
            $display("[perf] miss_rate  : %0d.%01d%%", udiv(mr1000,64'd10), umod(mr1000,64'd10));
            $display("[perf] miss_time  : %0d.%02d cyc", udiv(mlat100,64'd100), umod(mlat100,64'd100));
            $display("[perf] miss_penalty:%0d.%02d cyc", udiv(mpen100,64'd100), umod(mpen100,64'd100));
            $display("[perf] data AMAT  : %0d.%02d cyc (每次访存)",
                     udiv(dmat100,64'd100), umod(dmat100,64'd100));
            $display("[perf] mem_per_inst: %0d.%02d",
                     udiv(dmpi100,64'd100), umod(dmpi100,64'd100));

            $display("[perf] ------ selfcheck -----");
            $display("[perf] retire=%0d sum_insts=%0d |diff|=%0d",
                     retire_cnt, total_insts,
                     (retire_cnt > total_insts) ? (retire_cnt - total_insts)
                                                : (total_insts - retire_cnt));
            $display("[perf] cycles=%0d sum_cycs=%0d  |diff|=%0d",
                     cycles, total_cycs,
                     (cycles > total_cycs) ? (cycles - total_cycs)
                                           : (total_cycs - cycles));
            $display("[perf] fetch_n=%0d hit+miss=%0d",
                     fetch_n, hit_n + miss_n);
        end
    end

endmodule
