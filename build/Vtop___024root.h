// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"
class Vtop___024unit;


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:
    // CELLS
    Vtop___024unit* __PVT____024unit;

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst,0,0);
        VL_OUT8(halt,0,0);
        VL_OUT8(aborted,0,0);
        VL_OUT8(state_dbg,2,0);
        VL_OUT8(stall_ifu,0,0);
        VL_OUT8(mmio_dbg,0,0);
        CData/*0:0*/ top__DOT__u_core__DOT__ifu_done;
        CData/*0:0*/ top__DOT__u_core__DOT__mst_done;
        CData/*0:0*/ top__DOT__u_core__DOT__mst_rvalid;
        CData/*0:0*/ top__DOT__u_core__DOT__mst_bvalid;
        CData/*3:0*/ top__DOT__u_core__DOT__idu_alu_op;
        CData/*0:0*/ top__DOT__u_core__DOT__idu_alu_en;
        CData/*0:0*/ top__DOT__u_core__DOT__idu_alu_src2_imm;
        CData/*0:0*/ top__DOT__u_core__DOT__idu_mem_re;
        CData/*0:0*/ top__DOT__u_core__DOT__idu_mem_we;
        CData/*2:0*/ top__DOT__u_core__DOT__idu_branch_type;
        CData/*0:0*/ top__DOT__u_core__DOT__idu_csr_wen;
        CData/*2:0*/ top__DOT__u_core__DOT__ctrl_state;
        CData/*0:0*/ top__DOT__u_core__DOT__ctrl_ir_we;
        CData/*0:0*/ top__DOT__u_core__DOT__dmem_awvalid;
        CData/*0:0*/ top__DOT__u_core__DOT__clint_arvalid;
        CData/*0:0*/ top__DOT__u_core__DOT__clint_wvalid;
        CData/*0:0*/ top__DOT__u_core__DOT__rtc_rvalid;
        CData/*0:0*/ top__DOT__u_core__DOT__clint_rvalid;
        CData/*0:0*/ top__DOT__u_core__DOT__clint_bvalid;
        CData/*0:0*/ top__DOT__u_core__DOT__uart_rvalid;
        CData/*0:0*/ top__DOT__u_core__DOT__uart_bvalid;
        CData/*0:0*/ top__DOT__u_core__DOT__dmem_arready;
        CData/*0:0*/ top__DOT__u_core__DOT__dmem_rvalid;
        CData/*0:0*/ top__DOT__u_core__DOT__dmem_awready;
        CData/*0:0*/ top__DOT__u_core__DOT__dmem_bvalid;
        CData/*0:0*/ top__DOT__u_core__DOT__mmio_flag_r;
        CData/*7:0*/ top__DOT__u_core__DOT__u_lsu__DOT__lb;
        CData/*0:0*/ top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu;
        CData/*0:0*/ top__DOT__u_core__DOT__u_arb__DOT__m_valid_r;
        CData/*2:0*/ top__DOT__u_core__DOT__u_master__DOT__state;
        CData/*2:0*/ top__DOT__u_core__DOT__u_master__DOT__next_state;
        CData/*0:0*/ top__DOT__u_core__DOT__u_xbar__DOT__ar_clint;
        CData/*0:0*/ top__DOT__u_core__DOT__u_xbar__DOT__ar_mem;
        CData/*2:0*/ top__DOT__u_core__DOT__u_ctrl__DOT__next_state;
        CData/*0:0*/ top__DOT__u_core__DOT__u_clint__DOT__aw_half;
        CData/*0:0*/ top__DOT__u_core__DOT__u_mem__DOT__aw_recv;
        CData/*3:0*/ top__DOT__u_core__DOT__u_mem__DOT__w_mask_latch;
        CData/*0:0*/ top__DOT__u_core__DOT__u_mem__DOT__rd_delay;
        CData/*0:0*/ top__DOT__u_core__DOT__u_mem__DOT__wr_delay;
        CData/*0:0*/ top__DOT__u_core__DOT__u_mem__DOT____VdfgRegularize_ha4eaa22b_0_1;
        CData/*1:0*/ top__DOT__u_core__DOT__u_idu__DOT__mem_width;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__mem_signed;
        CData/*2:0*/ top__DOT__u_core__DOT__u_idu__DOT__npc_sel;
        CData/*2:0*/ top__DOT__u_core__DOT__u_idu__DOT__imm_type;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_jal;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_jalr;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_bne;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_beq;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_bge;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_bgeu;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_blt;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_bltu;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_lui;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_lbu;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_lw;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_lb;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_lh;
    };
    struct {
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_lhu;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_ebreak;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_csrrs;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_csrrw;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_ecall;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_mret;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_fence;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_sb;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_sw;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_sh;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_auipc;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_or;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_ori;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_xor;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_xori;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_add;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_addi;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_sub;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_slti;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_sltiu;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_and;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_andi;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_sra;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_srai;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_srl;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_sll;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_slli;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_srli;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_sltu;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_slt;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_0;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_1;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_2;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_3;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_4;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_6;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_7;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11;
        CData/*3:0*/ __Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op;
        CData/*2:0*/ __Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_wb_sel;
        CData/*7:0*/ __Vtableidx2;
        CData/*6:0*/ __Vtableidx3;
        CData/*5:0*/ __Vtableidx4;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
        SData/*15:0*/ top__DOT__u_core__DOT__u_lsu__DOT__lh;
        SData/*15:0*/ top__DOT__u_core__DOT__u_mem__DOT__cnt;
        SData/*9:0*/ __Vtableidx1;
        VL_OUT(pc,31,0);
        VL_OUT(ir_dbg,31,0);
        IData/*31:0*/ top__DOT__u_core__DOT__ifu_inst;
        IData/*31:0*/ top__DOT__u_core__DOT__arb_req_addr;
        IData/*31:0*/ top__DOT__u_core__DOT__arb_req_wdata;
        IData/*31:0*/ top__DOT__u_core__DOT__idu_imm;
        IData/*31:0*/ top__DOT__u_core__DOT__rf_rdata1;
        IData/*31:0*/ top__DOT__u_core__DOT__exu_alu_result;
        IData/*31:0*/ top__DOT__u_core__DOT__wbu_wb_data;
        IData/*31:0*/ top__DOT__u_core__DOT__IR;
        IData/*31:0*/ top__DOT__u_core__DOT__ir_pc;
        IData/*31:0*/ top__DOT__u_core__DOT__alu_result_r;
        IData/*31:0*/ top__DOT__u_core__DOT__rtc_rdata;
        IData/*31:0*/ top__DOT__u_core__DOT__clint_rdata;
        IData/*31:0*/ top__DOT__u_core__DOT__dmem_rdata;
        IData/*31:0*/ top__DOT__u_core__DOT__u_ifu__DOT__pc_reg;
    };
    struct {
        IData/*31:0*/ top__DOT__u_core__DOT__u_ifu__DOT__next_pc;
        IData/*31:0*/ top__DOT__u_core__DOT__u_mem__DOT__aw_addr_latch;
        IData/*31:0*/ top__DOT__u_core__DOT__u_exu__DOT__rs2_data;
        IData/*31:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__csr_read;
        IData/*31:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__mvendroid;
        IData/*31:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__marchid;
        IData/*31:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__mcause;
        IData/*31:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__mepc;
        IData/*31:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus;
        IData/*31:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec;
        IData/*31:0*/ __Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__Vfuncout;
        IData/*31:0*/ __Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__a;
        IData/*31:0*/ __Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b;
        IData/*31:0*/ __Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__Vfuncout;
        IData/*31:0*/ __Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_pc4;
        IData/*31:0*/ __Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_alu_result;
        IData/*31:0*/ __Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_mem_data;
        IData/*31:0*/ __Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_csr_data;
        IData/*31:0*/ __Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_imm;
        IData/*31:0*/ __VactIterCount;
        QData/*63:0*/ top__DOT__u_core__DOT__u_rtc__DOT__now_us;
        QData/*63:0*/ top__DOT__u_core__DOT__u_clint__DOT__mtime;
        QData/*63:0*/ top__DOT__u_core__DOT__u_clint__DOT__mtimecmp;
        QData/*63:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__mcycle;
        VlUnpacked<IData/*31:0*/, 32> top__DOT__u_core__DOT__u_regfile__DOT__rf;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
