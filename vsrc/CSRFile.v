// CSRFile: 机器模式 CSR 寄存器堆 (mstatus/mepc/mcause/mtvec/mcycle/...)
// trap 时按 RISC-V 特权规范自动更新 mstatus 位域, 写操作只在 WB 拍(at_state_wb)生效

`include "npc_defs.vh"
module CSRFile#(
    parameter ADDR_WIDTH = 12
) (
    //不需要读使能
    input           clk,
    input           rst,
    input           at_state_wb,   // 控制CSR写入时机 来自ctrl模块         

    input           csr_wen,
    input           ecall_trap,   // ecall 异常 (mcause=11)
    input           ebreak_trap,  // ebreak 断点异常 (mcause=3)
    input           mret_exec,    // mret 指令执行，恢复 mstatus
    input           irq_trap,     // interupt request 定时器中断 
    
    input  [31:0]   ecall_pc,      // ecall 时的 PC，保存到 mepc
    input  [31:0]   csr_wdata,
    input  [11:0]   csr_idx,
    input           csr_s_w,      // 1=csrrs 置位写(与原值 OR), 0=csrrw 直写

    output [31:0]   csr_mtvec, // 出事了去哪里 输出mtvec值 
    output [31:0]   csr_mepc,  // 出事前的pc 方便回来 输出的mepc值，供mret/IFU使用
    output [31:0]   csr_data,
    output          mstatus_mie // 是否开启中断 通过软件iset 函数 写1或0 
                                // mstatus.MIE, 供 core 判定 irq_taken
    

);
    reg [31:0] csr_read;
    reg [63:0] mcycle;
    reg [31:0] mvendroid, marchid;
    reg [31:0] mcause, mepc, mstatus, mtvec;

    initial 
    begin
        mvendroid = 32'h79737978;//ysyx
        marchid = 32'h18D08CF;//我的学号
    end

	always @(posedge clk)//mcycle 自增逻辑
	begin
	   if(rst)
	       mcycle <= 64'b0;
	   else
	       mcycle <= mcycle + 64'b1;
	end

    //模仿intr.c的 isa_raise_intr
    always @(posedge clk) 
    begin
        if(rst) 
        begin
            mcause <= 0;
            mepc <= 0;
            mstatus <= 32'h1800; //初始化  MIE是0 默认没中断 必须让软件代码来把MIE变为1 才有中断
            mtvec <= 0; //由am注册的cte init 的内联汇编 csrrw来写入
        end   

        else 
        begin
            if(ecall_trap && at_state_wb)
            begin
                mcause <= `MCAUSE_ECALL;       // M-mode ecall
                mepc <= ecall_pc;
                mstatus[7] <= mstatus[3];       // MPIE <- MIE 把当前中断使能状态存档
                mstatus[3] <= 1'b0;             // MIE  <- 0（关中断） 强制关 防止嵌套
                mstatus[12:11] <= 2'b11;        // MPP  <- M-mode（RISC-V 规范：trap 时保存当前特权级）
            end
            else if(ebreak_trap && at_state_wb)
            begin
                mcause <= `MCAUSE_BREAK;        // Breakpoint
                mepc <= ecall_pc;
                mstatus[7] <= mstatus[3];       // MPIE <- MIE
                mstatus[3] <= 1'b0;             // MIE  <- 0
                mstatus[12:11] <= 2'b11;        // MPP  <- M-mode
            end
            else if(mret_exec && at_state_wb)
            begin
                mstatus[3]   <= mstatus[7];     // MIE  <- MPIE（恢复中断）
                mstatus[7]   <= 1'b1;           // MPIE <- 1 规范
                mstatus[12:11] <= 2'b00;        // MPP  <- 0（最低特权级）
            end
            else if (irq_trap && at_state_wb)
            begin
                mcause <= `MCAUSE_MTIMER;   // 机器模式定时器中断 (bit31=1)
                mepc   <= ecall_pc;          // 中断在指令边界响应: core 传入的是 npc_noirq
                mstatus[7] <= mstatus[3];    // MPIE <- MIE
                mstatus[3] <= 1'b0;          // MIE  <- 0 (关中断, 天然不嵌套)
                mstatus[12:11] <= 2'b11;     // MPP  <- M-mode
            end
            else if (csr_wen && at_state_wb) //写值CSR指令
            begin
            /* verilator lint_off CASEINCOMPLETE  */ 
            case (csr_idx)
                12'h341: mepc    <= csr_s_w ? (csr_wdata |  mepc ) : csr_wdata;  // mepc
                12'h342: mcause  <= csr_s_w ? (csr_wdata |  mcause ) : csr_wdata;  // mcause
                12'h300: mstatus <= csr_s_w ? (csr_wdata |  mstatus ) : csr_wdata;  // mstatus
                12'h305: mtvec   <= csr_s_w ? (csr_wdata |  mtvec ) : csr_wdata;  // mtvec
                default: ;
            endcase
        end
        end
    
    end

   always @(*) //随时读 
   begin
    case (csr_idx)
        12'hB00: csr_read = mcycle[31:0];
        12'hB80: csr_read = mcycle[63:32];
        12'hf11: csr_read = mvendroid;
        12'hf12: csr_read = marchid;
        12'h341: csr_read = mepc;
        12'h342: csr_read = mcause;
        12'h300: csr_read = mstatus;
        12'h305: csr_read = mtvec;
        default: csr_read = 32'b0;
    endcase

   end

    assign csr_data = csr_read;
    assign csr_mtvec = mtvec;
    assign csr_mepc  = mepc;    //不需要+4 am的traps已经做了
    assign mstatus_mie = mstatus[3];   // 把 MIE 位引出去 是否启用中断


endmodule

