// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(reset,0,0);
        VL_OUT8(halt,0,0);
        CData/*0:0*/ top__DOT__u_core__DOT__ifu_respValid;
        CData/*0:0*/ top__DOT__u_core__DOT__ifu_done;
        CData/*0:0*/ top__DOT__u_core__DOT__lsu_reqValid;
        CData/*0:0*/ top__DOT__u_core__DOT__lsu_wen;
        CData/*0:0*/ top__DOT__u_core__DOT__lsu_respValid;
        CData/*3:0*/ top__DOT__u_core__DOT__lsu_wmask;
        CData/*3:0*/ top__DOT__u_core__DOT__alu_op;
        CData/*0:0*/ top__DOT__u_core__DOT__alu_src2_imm;
        CData/*0:0*/ top__DOT__u_core__DOT__alu_en;
        CData/*0:0*/ top__DOT__u_core__DOT__csr_wen;
        CData/*2:0*/ top__DOT__u_core__DOT__npc_sel;
        CData/*0:0*/ top__DOT__u_core__DOT__mem_re;
        CData/*1:0*/ top__DOT__u_core__DOT__mem_width;
        CData/*0:0*/ top__DOT__u_core__DOT__mem_signed;
        CData/*2:0*/ top__DOT__u_core__DOT__branch_type;
        CData/*2:0*/ top__DOT__u_core__DOT__ctrl_state;
        CData/*0:0*/ top__DOT__u_core__DOT__ctrl_ir_we;
        CData/*0:0*/ top__DOT__u_core__DOT__u_ifu__DOT__bus_state;
        CData/*0:0*/ top__DOT__u_core__DOT__u_ifu__DOT__bus_next;
        CData/*2:0*/ top__DOT__u_core__DOT__u_ctrl__DOT__next_state;
        CData/*0:0*/ top__DOT__u_core__DOT__u_lsu__DOT__bus_state;
        CData/*0:0*/ top__DOT__u_core__DOT__u_lsu__DOT__bus_next;
        CData/*0:0*/ top__DOT__u_core__DOT__u_lsu__DOT__do_req;
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
    };
    struct {
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_srl;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_sll;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_slli;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_srli;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_sltu;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT__is_slt;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_1;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_2;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_3;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_4;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_6;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_7;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_8;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_9;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_10;
        CData/*0:0*/ top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11;
        CData/*3:0*/ __Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__0__op;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
        VL_OUT(pc,31,0);
        IData/*31:0*/ top__DOT__u_core__DOT__ifu_rdata;
        IData/*31:0*/ top__DOT__u_core__DOT__lsu_wdata;
        IData/*31:0*/ top__DOT__u_core__DOT__lsu_rdata;
        IData/*31:0*/ top__DOT__u_core__DOT__imm;
        IData/*31:0*/ top__DOT__u_core__DOT__csr_data;
        IData/*31:0*/ top__DOT__u_core__DOT__r_data1;
        IData/*31:0*/ top__DOT__u_core__DOT__alu_result;
        IData/*31:0*/ top__DOT__u_core__DOT__wb_data;
        IData/*31:0*/ top__DOT__u_core__DOT__IR;
        IData/*31:0*/ top__DOT__u_core__DOT__alu_out;
        IData/*31:0*/ top__DOT__u_core__DOT__u_ifu__DOT__pc_reg;
        IData/*31:0*/ top__DOT__u_core__DOT__u_ifu__DOT__next_pc;
        IData/*31:0*/ top__DOT__u_core__DOT__u_regfile__DOT__i;
        IData/*31:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__mvendroid;
        IData/*31:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__marchid;
        IData/*31:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__mcause;
        IData/*31:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__mepc;
        IData/*31:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus;
        IData/*31:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec;
        IData/*31:0*/ __Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__0__Vfuncout;
        IData/*31:0*/ __Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__0__a;
        IData/*31:0*/ __Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__0__b;
        IData/*31:0*/ __VactIterCount;
        QData/*63:0*/ top__DOT__u_core__DOT__u_CSRFile__DOT__mcycle;
        VlUnpacked<IData/*31:0*/, 32768> top__DOT__u_core__DOT__u_imem__DOT__mem;
        VlUnpacked<CData/*7:0*/, 131072> top__DOT__u_core__DOT__u_dmem__DOT__mem;
        VlUnpacked<IData/*31:0*/, 32> top__DOT__u_core__DOT__u_regfile__DOT__rf;
        VlUnpacked<IData/*31:0*/, 32> top__DOT__u_core__DOT__u_regfile__DOT__rf_read;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
        VlUnpacked<CData/*0:0*/, 4> __Vm_traceActivity;
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
