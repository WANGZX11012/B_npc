// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((~ (IData)(vlSelfRef.clk)) 
                                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)) 
                                                      << 1U) 
                                                     | ((IData)(vlSelfRef.clk) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vtop___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

extern const VlUnpacked<CData/*7:0*/, 512> Vtop__ConstPool__TABLE_hd03dc8c3_0;
void Vtop___024unit____Vdpiimwrap_uart_putchar_TOP____024unit(CData/*7:0*/ c);
void Vtop___024unit____Vdpiimwrap_dpic_mem_read_TOP____024unit(QData/*63:0*/ addr, IData/*31:0*/ &rdata);
void Vtop___024unit____Vdpiimwrap_dpic_mem_write_TOP____024unit(QData/*63:0*/ addr, IData/*31:0*/ wdata, CData/*7:0*/ wmask);
void Vtop___024unit____Vdpiimwrap_rtc_time_us_TOP____024unit(QData/*63:0*/ &rtc_time_us__Vfuncrtn);
extern const VlUnpacked<CData/*2:0*/, 128> Vtop__ConstPool__TABLE_h540c7ad9_0;
extern const VlUnpacked<CData/*2:0*/, 64> Vtop__ConstPool__TABLE_hf13ebc3c_0;
extern const VlUnpacked<CData/*2:0*/, 2048> Vtop__ConstPool__TABLE_h8b11fe7c_0;
extern const VlUnpacked<CData/*2:0*/, 256> Vtop__ConstPool__TABLE_h9af52e12_0;

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    QData/*63:0*/ __Vfunc_rtc_time_us__0__Vfuncout;
    __Vfunc_rtc_time_us__0__Vfuncout = 0;
    IData/*31:0*/ __Vtask_dpic_mem_read__2__rdata;
    __Vtask_dpic_mem_read__2__rdata = 0;
    SData/*8:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_core__DOT__u_arb__DOT__m_valid_r;
    __Vdly__top__DOT__u_core__DOT__u_arb__DOT__m_valid_r = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_core__DOT__rtc_rvalid;
    __Vdly__top__DOT__u_core__DOT__rtc_rvalid = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_core__DOT__uart_rvalid;
    __Vdly__top__DOT__u_core__DOT__uart_rvalid = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_core__DOT__uart_bvalid;
    __Vdly__top__DOT__u_core__DOT__uart_bvalid = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_core__DOT__u_mem__DOT__rd_delay;
    __Vdly__top__DOT__u_core__DOT__u_mem__DOT__rd_delay = 0;
    SData/*15:0*/ __Vdly__top__DOT__u_core__DOT__u_mem__DOT__cnt;
    __Vdly__top__DOT__u_core__DOT__u_mem__DOT__cnt = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_core__DOT__u_mem__DOT__aw_recv;
    __Vdly__top__DOT__u_core__DOT__u_mem__DOT__aw_recv = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_core__DOT__u_mem__DOT__wr_delay;
    __Vdly__top__DOT__u_core__DOT__u_mem__DOT__wr_delay = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mcause;
    __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mcause = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mepc;
    __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mepc = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus;
    __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec;
    __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf__v1;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf__v1 = 0;
    CData/*4:0*/ __VdlyDim0__top__DOT__u_core__DOT__u_regfile__DOT__rf__v1;
    __VdlyDim0__top__DOT__u_core__DOT__u_regfile__DOT__rf__v1 = 0;
    CData/*0:0*/ __VdlySet__top__DOT__u_core__DOT__u_regfile__DOT__rf__v1;
    __VdlySet__top__DOT__u_core__DOT__u_regfile__DOT__rf__v1 = 0;
    // Body
    __Vdly__top__DOT__u_core__DOT__rtc_rvalid = vlSelfRef.top__DOT__u_core__DOT__rtc_rvalid;
    __Vdly__top__DOT__u_core__DOT__u_arb__DOT__m_valid_r 
        = vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_valid_r;
    __Vdly__top__DOT__u_core__DOT__uart_rvalid = vlSelfRef.top__DOT__u_core__DOT__uart_rvalid;
    __Vdly__top__DOT__u_core__DOT__uart_bvalid = vlSelfRef.top__DOT__u_core__DOT__uart_bvalid;
    __Vdly__top__DOT__u_core__DOT__u_mem__DOT__cnt 
        = vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__cnt;
    __Vdly__top__DOT__u_core__DOT__u_mem__DOT__rd_delay 
        = vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__rd_delay;
    __Vdly__top__DOT__u_core__DOT__u_mem__DOT__wr_delay 
        = vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__wr_delay;
    __Vdly__top__DOT__u_core__DOT__u_mem__DOT__aw_recv 
        = vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv;
    __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mcause 
        = vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcause;
    __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
        = vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus;
    __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec 
        = vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec;
    __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mepc 
        = vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mepc;
    __VdlySet__top__DOT__u_core__DOT__u_regfile__DOT__rf__v1 = 0U;
    __Vtableidx2 = (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_lfsr__DOT__state) 
                     << 1U) | (IData)(vlSelfRef.rst));
    vlSelfRef.top__DOT__u_core__DOT__u_lfsr__DOT__state 
        = Vtop__ConstPool__TABLE_hd03dc8c3_0[__Vtableidx2];
    if (((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
         & (0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                            >> 4U)))) {
        __Vdly__top__DOT__u_core__DOT__uart_rvalid = 1U;
    } else if (((IData)(vlSelfRef.top__DOT__u_core__DOT__uart_rvalid) 
                & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rready))) {
        __Vdly__top__DOT__u_core__DOT__uart_rvalid = 0U;
    }
    if (vlSelfRef.top__DOT__u_core__DOT____Vcellinp__u_rtc__arvalid) {
        __Vdly__top__DOT__u_core__DOT__rtc_rvalid = 1U;
    } else if (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rready) 
                & (IData)(vlSelfRef.top__DOT__u_core__DOT__rtc_rvalid))) {
        __Vdly__top__DOT__u_core__DOT__rtc_rvalid = 0U;
    }
    vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcycle 
        = ((IData)(vlSelfRef.rst) ? 0ULL : (1ULL + vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcycle));
    if (((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
         & (0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                            >> 4U)))) {
        Vtop___024unit____Vdpiimwrap_uart_putchar_TOP____024unit(
                                                                 (0x000000ffU 
                                                                  & vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_wdata));
        __Vdly__top__DOT__u_core__DOT__uart_bvalid = 1U;
    } else if (((IData)(vlSelfRef.top__DOT__u_core__DOT__uart_bvalid) 
                & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__bready))) {
        __Vdly__top__DOT__u_core__DOT__uart_bvalid = 0U;
    }
    if (((IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_rvalid) 
         & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rready))) {
        vlSelfRef.top__DOT__u_core__DOT__dmem_rvalid = 0U;
    }
    if (((IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_bvalid) 
         & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__bready))) {
        vlSelfRef.top__DOT__u_core__DOT__dmem_bvalid = 0U;
    }
    if ((((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
          & (IData)(vlSelfRef.top__DOT__u_core__DOT__pmem_sel)) 
         & (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_arready))) {
        Vtop___024unit____Vdpiimwrap_dpic_mem_read_TOP____024unit((QData)((IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr)), __Vtask_dpic_mem_read__2__rdata);
        vlSelfRef.top__DOT__u_core__DOT__dmem_rdata 
            = __Vtask_dpic_mem_read__2__rdata;
        __Vdly__top__DOT__u_core__DOT__u_mem__DOT__rd_delay = 1U;
        __Vdly__top__DOT__u_core__DOT__u_mem__DOT__cnt = 1U;
    } else if (vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__rd_delay) {
        if ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__cnt))) {
            vlSelfRef.top__DOT__u_core__DOT__dmem_rvalid = 1U;
            __Vdly__top__DOT__u_core__DOT__u_mem__DOT__rd_delay = 0U;
        } else {
            __Vdly__top__DOT__u_core__DOT__u_mem__DOT__cnt 
                = (0x0000ffffU & ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__cnt) 
                                  - (IData)(1U)));
        }
    }
    if (((IData)(vlSelfRef.top__DOT__u_core__DOT____Vcellinp__u_mem__awvalid) 
         & (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_awready))) {
        __Vdly__top__DOT__u_core__DOT__u_mem__DOT__aw_recv = 1U;
    }
    if ((((IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv) 
          & (4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state))) 
         & (IData)(vlSelfRef.top__DOT__u_core__DOT__pmem_sel))) {
        Vtop___024unit____Vdpiimwrap_dpic_mem_write_TOP____024unit((QData)((IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_addr_latch)), vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_wdata, (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__w_mask_latch));
        __Vdly__top__DOT__u_core__DOT__u_mem__DOT__aw_recv = 0U;
        __Vdly__top__DOT__u_core__DOT__u_mem__DOT__wr_delay = 1U;
        __Vdly__top__DOT__u_core__DOT__u_mem__DOT__cnt = 1U;
    } else if (vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__wr_delay) {
        if ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__cnt))) {
            vlSelfRef.top__DOT__u_core__DOT__dmem_bvalid = 1U;
            __Vdly__top__DOT__u_core__DOT__u_mem__DOT__wr_delay = 0U;
        } else {
            __Vdly__top__DOT__u_core__DOT__u_mem__DOT__cnt 
                = (0x0000ffffU & ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__cnt) 
                                  - (IData)(1U)));
        }
    }
    if (((IData)(vlSelfRef.top__DOT__u_core__DOT____Vcellinp__u_mem__awvalid) 
         & (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_awready))) {
        vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_addr_latch 
            = vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr;
        vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__w_mask_latch 
            = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)
                ? 0U : (0x0000000fU & ((0U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                                        ? ((IData)(1U) 
                                           << (3U & vlSelfRef.top__DOT__u_core__DOT__alu_out))
                                        : ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                                            ? ((2U 
                                                & vlSelfRef.top__DOT__u_core__DOT__alu_out)
                                                ? 0x0cU
                                                : 3U)
                                            : 0x0fU))));
    }
    if (vlSelfRef.top__DOT__u_core__DOT____Vcellinp__u_rtc__arvalid) {
        vlSelfRef.top__DOT__u_core__DOT__rtc_rresp = 0U;
        vlSelfRef.top__DOT__u_core__DOT__rtc_rdata 
            = ((3U == (3U & (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                             >> 2U))) ? (IData)((vlSelfRef.top__DOT__u_core__DOT__u_rtc__DOT__now_us 
                                                 >> 0x20U))
                : (IData)(vlSelfRef.top__DOT__u_core__DOT__u_rtc__DOT__now_us));
    }
    if ((((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state)) 
          & ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11) 
             | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh) 
                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_6) 
                   | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                      | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                         | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_9))))))) 
         & (0U != (0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                  >> 7U))))) {
        __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf__v1 
            = vlSelfRef.top__DOT__u_core__DOT__wb_data;
        __VdlyDim0__top__DOT__u_core__DOT__u_regfile__DOT__rf__v1 
            = (0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                              >> 7U));
        __VdlySet__top__DOT__u_core__DOT__u_regfile__DOT__rf__v1 = 1U;
    }
    vlSelfRef.top__DOT__u_core__DOT__rtc_rvalid = __Vdly__top__DOT__u_core__DOT__rtc_rvalid;
    vlSelfRef.top__DOT__u_core__DOT__uart_rvalid = __Vdly__top__DOT__u_core__DOT__uart_rvalid;
    vlSelfRef.top__DOT__u_core__DOT__uart_bvalid = __Vdly__top__DOT__u_core__DOT__uart_bvalid;
    vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__cnt 
        = __Vdly__top__DOT__u_core__DOT__u_mem__DOT__cnt;
    vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__rd_delay 
        = __Vdly__top__DOT__u_core__DOT__u_mem__DOT__rd_delay;
    vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__wr_delay 
        = __Vdly__top__DOT__u_core__DOT__u_mem__DOT__wr_delay;
    vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv 
        = __Vdly__top__DOT__u_core__DOT__u_mem__DOT__aw_recv;
    if (vlSelfRef.rst) {
        __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mcause = 0U;
        vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcause 
            = __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mcause;
        __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus = 0x00001800U;
        vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
            = __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus;
        __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec = 0U;
        vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec 
            = __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec;
        __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mepc = 0U;
    } else {
        if ((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))) {
            __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mcause = 0x0000000bU;
            __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
                = ((0xffffff7fU & __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus) 
                   | (0x00000080U & (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
                                     << 4U)));
            __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
                = (0xfffffff7U & __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus);
            __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
                = (0x00001800U | __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus);
            __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mepc 
                = vlSelfRef.top__DOT__u_core__DOT__ir_pc;
        } else if (vlSelfRef.halt) {
            __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mcause = 3U;
            __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
                = ((0xffffff7fU & __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus) 
                   | (0x00000080U & (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
                                     << 4U)));
            __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
                = (0xfffffff7U & __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus);
            __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
                = (0x00001800U | __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus);
            __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mepc 
                = vlSelfRef.top__DOT__u_core__DOT__ir_pc;
        } else {
            if ((5U != (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))) {
                if (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wen) {
                    if ((0x0341U != (vlSelfRef.top__DOT__u_core__DOT__IR 
                                     >> 0x00000014U))) {
                        if ((0x0342U == (vlSelfRef.top__DOT__u_core__DOT__IR 
                                         >> 0x00000014U))) {
                            __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mcause 
                                = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs)
                                    ? (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
                                       | vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcause)
                                    : vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata);
                        }
                    }
                    if ((0x0341U == (vlSelfRef.top__DOT__u_core__DOT__IR 
                                     >> 0x00000014U))) {
                        __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mepc 
                            = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs)
                                ? (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
                                   | vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mepc)
                                : vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata);
                    }
                }
            }
            if ((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))) {
                __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
                    = ((0xfffffff7U & __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus) 
                       | (8U & (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
                                >> 4U)));
                __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
                    = (0x00000080U | __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus);
                __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
                    = (0xffffe7ffU & __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus);
            } else if (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wen) {
                if ((0x0341U != (vlSelfRef.top__DOT__u_core__DOT__IR 
                                 >> 0x00000014U))) {
                    if ((0x0342U != (vlSelfRef.top__DOT__u_core__DOT__IR 
                                     >> 0x00000014U))) {
                        if ((0x0300U == (vlSelfRef.top__DOT__u_core__DOT__IR 
                                         >> 0x00000014U))) {
                            __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
                                = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs)
                                    ? (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
                                       | vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus)
                                    : vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata);
                        }
                    }
                }
            }
        }
        vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcause 
            = __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mcause;
        vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus 
            = __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus;
        if ((4U != (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))) {
            if ((1U & (~ (IData)(vlSelfRef.halt)))) {
                if ((5U != (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))) {
                    if (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wen) {
                        if ((0x0341U != (vlSelfRef.top__DOT__u_core__DOT__IR 
                                         >> 0x00000014U))) {
                            if ((0x0342U != (vlSelfRef.top__DOT__u_core__DOT__IR 
                                             >> 0x00000014U))) {
                                if ((0x0300U != (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                 >> 0x00000014U))) {
                                    if ((0x0305U == 
                                         (vlSelfRef.top__DOT__u_core__DOT__IR 
                                          >> 0x00000014U))) {
                                        __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec 
                                            = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs)
                                                ? (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
                                                   | vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec)
                                                : vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec 
            = __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec;
    }
    vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mepc 
        = __Vdly__top__DOT__u_core__DOT__u_CSRFile__DOT__mepc;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0U] = 0U;
    if (__VdlySet__top__DOT__u_core__DOT__u_regfile__DOT__rf__v1) {
        vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[__VdlyDim0__top__DOT__u_core__DOT__u_regfile__DOT__rf__v1] 
            = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf__v1;
    }
    vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__busy 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__rd_delay) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__wr_delay));
    if (vlSelfRef.top__DOT__u_core__DOT__ctrl_ir_we) {
        vlSelfRef.top__DOT__u_core__DOT__ir_pc = vlSelfRef.pc;
        vlSelfRef.top__DOT__u_core__DOT__IR = vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__resp_rdata;
    }
    if (vlSelfRef.rst) {
        vlSelfRef.top__DOT__u_core__DOT__mmio_flag = 0U;
        vlSelfRef.mmio_dbg = vlSelfRef.top__DOT__u_core__DOT__mmio_flag;
        vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg = 0x80000000U;
        vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state = 0U;
    } else {
        if ((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state))) {
            vlSelfRef.top__DOT__u_core__DOT__mmio_flag = 0U;
        } else if ((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state))) {
            vlSelfRef.top__DOT__u_core__DOT__mmio_flag 
                = ((0x00a00000U == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                    >> 8U)) | (0x0a00003fU 
                                               == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                   >> 4U)));
        }
        vlSelfRef.mmio_dbg = vlSelfRef.top__DOT__u_core__DOT__mmio_flag;
        if ((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state))) {
            vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg 
                = vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__next_pc;
        }
        vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state 
            = vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__next_state;
    }
    Vtop___024unit____Vdpiimwrap_rtc_time_us_TOP____024unit(__Vfunc_rtc_time_us__0__Vfuncout);
    vlSelfRef.top__DOT__u_core__DOT__u_rtc__DOT__now_us 
        = __Vfunc_rtc_time_us__0__Vfuncout;
    vlSelfRef.top__DOT__u_core__DOT__dmem_arready = 
        (1U & ((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv)) 
               & ((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_rvalid)) 
                  & (~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__busy)))));
    vlSelfRef.top__DOT__u_core__DOT__dmem_awready = 
        (1U & ((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv)) 
               & ((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_bvalid)) 
                  & (~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__busy)))));
    vlSelfRef.pc = vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg;
    vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rready 
        = ((0x10U <= (IData)(vlSelfRef.top__DOT__u_core__DOT__u_lfsr__DOT__state)) 
           & (2U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)));
    vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__bready 
        = ((0x10U <= (IData)(vlSelfRef.top__DOT__u_core__DOT__u_lfsr__DOT__state)) 
           & (5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)));
    if ((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state))) {
        vlSelfRef.top__DOT__u_core__DOT__alu_out = vlSelfRef.top__DOT__u_core__DOT__alu_result;
    }
    if (vlSelfRef.rst) {
        vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu = 0U;
        __Vdly__top__DOT__u_core__DOT__u_arb__DOT__m_valid_r = 0U;
        vlSelfRef.top__DOT__u_core__DOT__ctrl_state = 0U;
    } else {
        if (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_valid_r) {
            if (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_done) {
                __Vdly__top__DOT__u_core__DOT__u_arb__DOT__m_valid_r = 0U;
            }
        } else if (((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state)) 
                    | ((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state)) 
                       & ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_re) 
                          | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_we))))) {
            vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu 
                = (1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state));
            __Vdly__top__DOT__u_core__DOT__u_arb__DOT__m_valid_r = 1U;
        }
        vlSelfRef.top__DOT__u_core__DOT__ctrl_state 
            = vlSelfRef.top__DOT__u_core__DOT__u_ctrl__DOT__next_state;
    }
    vlSelfRef.halt = (0x00100073U == vlSelfRef.top__DOT__u_core__DOT__IR);
    vlSelfRef.ir_dbg = vlSelfRef.top__DOT__u_core__DOT__IR;
    vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 0U;
    vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
    vlSelfRef.top__DOT__u_core__DOT__alu_en = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ebreak = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_fence = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_data 
        = ((((0x0b00U == (vlSelfRef.top__DOT__u_core__DOT__IR 
                          >> 0x00000014U)) | (0x0b80U 
                                              == (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000014U))) 
            | (((0x0f11U == (vlSelfRef.top__DOT__u_core__DOT__IR 
                             >> 0x00000014U)) | (0x0f12U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000014U))) 
               | ((0x0341U == (vlSelfRef.top__DOT__u_core__DOT__IR 
                               >> 0x00000014U)) | (
                                                   (0x0342U 
                                                    == 
                                                    (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                     >> 0x00000014U)) 
                                                   | ((0x0300U 
                                                       == 
                                                       (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                        >> 0x00000014U)) 
                                                      | (0x0305U 
                                                         == 
                                                         (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                          >> 0x00000014U)))))))
            ? ((0x0b00U == (vlSelfRef.top__DOT__u_core__DOT__IR 
                            >> 0x00000014U)) ? (IData)(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcycle)
                : ((0x0b80U == (vlSelfRef.top__DOT__u_core__DOT__IR 
                                >> 0x00000014U)) ? (IData)(
                                                           (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcycle 
                                                            >> 0x00000020U))
                    : ((0x0f11U == (vlSelfRef.top__DOT__u_core__DOT__IR 
                                    >> 0x00000014U))
                        ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mvendroid
                        : ((0x0f12U == (vlSelfRef.top__DOT__u_core__DOT__IR 
                                        >> 0x00000014U))
                            ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__marchid
                            : ((0x0341U == (vlSelfRef.top__DOT__u_core__DOT__IR 
                                            >> 0x00000014U))
                                ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mepc
                                : ((0x0342U == (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                >> 0x00000014U))
                                    ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcause
                                    : ((0x0300U == 
                                        (vlSelfRef.top__DOT__u_core__DOT__IR 
                                         >> 0x00000014U))
                                        ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus
                                        : vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec)))))))
            : 0U);
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ecall = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_mret = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu = 0U;
    vlSelfRef.__Vtableidx4 = (0x0000007fU & vlSelfRef.top__DOT__u_core__DOT__IR);
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type 
        = Vtop__ConstPool__TABLE_h540c7ad9_0[vlSelfRef.__Vtableidx4];
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srli = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srai = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srl = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sra = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sll = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_andi = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slli = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_and = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ori = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_or = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lui = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xor = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xori = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_addi = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sub = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltiu = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slti = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrw = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jalr = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal = 0U;
    if ((0x00000040U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
        if ((0x00000020U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
            if ((0x00000010U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 0U;
                vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
                vlSelfRef.top__DOT__u_core__DOT__alu_en = 0U;
                if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                            if ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                if ((0x00100073U == vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ebreak = 1U;
                                }
                                if ((0x00100073U != vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                    if ((0x00000073U 
                                         == vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                        vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ecall = 1U;
                                    }
                                    if ((0x00000073U 
                                         != vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                        if ((0x30200073U 
                                             == vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_mret = 1U;
                                        }
                                    }
                                }
                                if ((2U == (7U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000000cU)))) {
                                    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs = 1U;
                                }
                                if ((2U != (7U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000000cU)))) {
                                    if ((1U == (7U 
                                                & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                   >> 0x0000000cU)))) {
                                        vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrw = 1U;
                                    }
                                }
                            }
                        }
                    }
                }
            } else if ((8U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm 
                    = ((1U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                              >> 2U)) && ((1U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                 >> 1U)) 
                                          && (1U & vlSelfRef.top__DOT__u_core__DOT__IR)));
                vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
                vlSelfRef.top__DOT__u_core__DOT__alu_en 
                    = ((1U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                              >> 2U)) && ((1U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                 >> 1U)) 
                                          && (1U & vlSelfRef.top__DOT__u_core__DOT__IR)));
            } else if ((4U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                    if ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                        if ((0U == (7U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                          >> 0x0000000cU)))) {
                            vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 1U;
                            vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
                            vlSelfRef.top__DOT__u_core__DOT__alu_en = 1U;
                        }
                    } else {
                        vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 0U;
                        vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
                        vlSelfRef.top__DOT__u_core__DOT__alu_en = 0U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 0U;
                    vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
                    vlSelfRef.top__DOT__u_core__DOT__alu_en = 0U;
                }
            } else if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                if ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                    if ((0x00004000U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                        vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 1U;
                        vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
                        vlSelfRef.top__DOT__u_core__DOT__alu_en = 1U;
                    } else if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                         >> 0x0000000dU)))) {
                        vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 1U;
                        vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
                        vlSelfRef.top__DOT__u_core__DOT__alu_en = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 0U;
                    vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
                    vlSelfRef.top__DOT__u_core__DOT__alu_en = 0U;
                }
            } else {
                vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 0U;
                vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
                vlSelfRef.top__DOT__u_core__DOT__alu_en = 0U;
            }
            if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                          >> 4U)))) {
                if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                            if ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                              >> 0x0000000eU)))) {
                                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000000dU)))) {
                                        if ((0x00001000U 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne = 1U;
                                        }
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq = 1U;
                                        }
                                    }
                                }
                                if ((0x00004000U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000000dU)))) {
                                        if ((0x00001000U 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge = 1U;
                                        }
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt = 1U;
                                        }
                                    }
                                    if ((0x00002000U 
                                         & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                        if ((0x00001000U 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu = 1U;
                                        }
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu = 1U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if ((4U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                        if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                            if ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                if ((0U == (7U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000000cU)))) {
                                    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jalr = 1U;
                                }
                            }
                        }
                    }
                }
                if ((8U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                    if ((4U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                        if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                            if ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal = 1U;
                            }
                        }
                    }
                }
            }
        } else {
            vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 0U;
            vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
            vlSelfRef.top__DOT__u_core__DOT__alu_en = 0U;
        }
    } else if ((0x00000020U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
        if ((0x00000010U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
            if ((8U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 0U;
                vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
            } else if ((4U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 0U;
                vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
            } else if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                if ((1U & (~ vlSelfRef.top__DOT__u_core__DOT__IR))) {
                    vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 0U;
                }
                vlSelfRef.top__DOT__u_core__DOT__alu_op 
                    = ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)
                        ? ((0x00004000U & vlSelfRef.top__DOT__u_core__DOT__IR)
                            ? ((0x00002000U & vlSelfRef.top__DOT__u_core__DOT__IR)
                                ? ((0x00001000U & vlSelfRef.top__DOT__u_core__DOT__IR)
                                    ? 2U : 3U) : ((0x00001000U 
                                                   & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                   ? 
                                                  ((0x20U 
                                                    == 
                                                    (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                     >> 0x00000019U))
                                                    ? 9U
                                                    : 8U)
                                                   : 4U))
                            : ((0x00002000U & vlSelfRef.top__DOT__u_core__DOT__IR)
                                ? ((0x00001000U & vlSelfRef.top__DOT__u_core__DOT__IR)
                                    ? 6U : 5U) : ((0x00001000U 
                                                   & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                   ? 7U
                                                   : 
                                                  ((0x20U 
                                                    == 
                                                    (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                     >> 0x00000019U))
                                                    ? 1U
                                                    : 0U))))
                        : 0U);
            } else {
                vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 0U;
                vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
            }
            vlSelfRef.top__DOT__u_core__DOT__alu_en 
                = ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                             >> 3U))) && ((1U & (~ 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 2U))) 
                                          && ((1U & 
                                               (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                >> 1U)) 
                                              && (1U 
                                                  & vlSelfRef.top__DOT__u_core__DOT__IR))));
        } else {
            vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm 
                = ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                             >> 3U))) && ((1U & (~ 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 2U))) 
                                          && ((1U & 
                                               (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                >> 1U)) 
                                              && (1U 
                                                  & vlSelfRef.top__DOT__u_core__DOT__IR))));
            vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
            vlSelfRef.top__DOT__u_core__DOT__alu_en 
                = ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                             >> 3U))) && ((1U & (~ 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 2U))) 
                                          && ((1U & 
                                               (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                >> 1U)) 
                                              && (1U 
                                                  & vlSelfRef.top__DOT__u_core__DOT__IR))));
        }
    } else if ((0x00000010U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
        vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm 
            = ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                         >> 3U))) && ((4U & vlSelfRef.top__DOT__u_core__DOT__IR)
                                       ? ((1U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                 >> 1U)) 
                                          && (1U & vlSelfRef.top__DOT__u_core__DOT__IR))
                                       : ((1U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                 >> 1U)) 
                                          && (1U & vlSelfRef.top__DOT__u_core__DOT__IR))));
        vlSelfRef.top__DOT__u_core__DOT__alu_op = (
                                                   (8U 
                                                    & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                    ? 0U
                                                    : 
                                                   ((4U 
                                                     & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                     ? 0U
                                                     : 
                                                    ((2U 
                                                      & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                      ? 
                                                     ((1U 
                                                       & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                       ? 
                                                      ((0x00004000U 
                                                        & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                        ? 
                                                       ((0x00002000U 
                                                         & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                         ? 
                                                        ((0x00001000U 
                                                          & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                          ? 2U
                                                          : 3U)
                                                         : 
                                                        ((0x00001000U 
                                                          & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                          ? 
                                                         ((0x20U 
                                                           == 
                                                           (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                            >> 0x00000019U))
                                                           ? 9U
                                                           : 8U)
                                                          : 4U))
                                                        : 
                                                       ((0x00002000U 
                                                         & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                         ? 
                                                        ((0x00001000U 
                                                          & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                          ? 6U
                                                          : 5U)
                                                         : 
                                                        ((0x00001000U 
                                                          & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                          ? 7U
                                                          : 0U)))
                                                       : 0U)
                                                      : 0U)));
        vlSelfRef.top__DOT__u_core__DOT__alu_en = (
                                                   (1U 
                                                    & (~ 
                                                       (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                        >> 3U))) 
                                                   && ((4U 
                                                        & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                        ? 
                                                       ((1U 
                                                         & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                            >> 1U)) 
                                                        && (1U 
                                                            & vlSelfRef.top__DOT__u_core__DOT__IR))
                                                        : 
                                                       ((1U 
                                                         & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                            >> 1U)) 
                                                        && (1U 
                                                            & vlSelfRef.top__DOT__u_core__DOT__IR))));
    } else {
        vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm 
            = ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                         >> 3U))) && ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                >> 2U))) 
                                      && ((1U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                 >> 1U)) 
                                          && (1U & vlSelfRef.top__DOT__u_core__DOT__IR))));
        vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
        vlSelfRef.top__DOT__u_core__DOT__alu_en = (
                                                   (1U 
                                                    & (~ 
                                                       (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                        >> 3U))) 
                                                   && ((1U 
                                                        & (~ 
                                                           (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                            >> 2U))) 
                                                       && ((1U 
                                                            & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                               >> 1U)) 
                                                           && (1U 
                                                               & vlSelfRef.top__DOT__u_core__DOT__IR))));
    }
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sb = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sw = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lhu = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lbu = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lb = 0U;
    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                  >> 6U)))) {
        if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                      >> 5U)))) {
            if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                          >> 4U)))) {
                if ((8U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                    if ((4U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                        if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                            if ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_fence = 1U;
                            }
                        }
                    }
                }
                if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                            if ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                if ((0x00004000U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000000dU)))) {
                                        if ((0x00001000U 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lhu = 1U;
                                        }
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lbu = 1U;
                                        }
                                    }
                                }
                                if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                              >> 0x0000000eU)))) {
                                    if ((0x00002000U 
                                         & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw = 1U;
                                        }
                                    }
                                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000000dU)))) {
                                        if ((0x00001000U 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh = 1U;
                                        }
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lb = 1U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if ((0x00000010U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                            if ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                if ((0x00004000U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000000dU)))) {
                                        if ((0x00001000U 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            if ((0U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000019U))) {
                                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srli = 1U;
                                            }
                                            if ((0x20U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000019U))) {
                                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srai = 1U;
                                            }
                                        }
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xori = 1U;
                                        }
                                    }
                                    if ((0x00002000U 
                                         & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                        if ((0x00001000U 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_andi = 1U;
                                        }
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ori = 1U;
                                        }
                                    }
                                }
                                if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                              >> 0x0000000eU)))) {
                                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000000dU)))) {
                                        if ((0x00001000U 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            if ((0U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000019U))) {
                                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slli = 1U;
                                            }
                                        }
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_addi = 1U;
                                        }
                                    }
                                    if ((0x00002000U 
                                         & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                        if ((0x00001000U 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltiu = 1U;
                                        }
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slti = 1U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if ((4U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                        if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                            if ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc = 1U;
                            }
                        }
                    }
                }
            }
        }
        if ((0x00000020U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
            if ((0x00000010U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                            if ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                              >> 0x0000000eU)))) {
                                    if ((0x00002000U 
                                         & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            if ((0U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000019U))) {
                                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt = 1U;
                                            }
                                        }
                                        if ((0x00001000U 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            if ((0U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000019U))) {
                                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu = 1U;
                                            }
                                        }
                                    }
                                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000000dU)))) {
                                        if ((0x00001000U 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            if ((0U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000019U))) {
                                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sll = 1U;
                                            }
                                        }
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            if ((0U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000019U))) {
                                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add = 1U;
                                            }
                                            if ((0x20U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000019U))) {
                                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sub = 1U;
                                            }
                                        }
                                    }
                                }
                                if ((0x00004000U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000000dU)))) {
                                        if ((0x00001000U 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            if ((0U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000019U))) {
                                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srl = 1U;
                                            }
                                            if ((0x20U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000019U))) {
                                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sra = 1U;
                                            }
                                        }
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            if ((0U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000019U))) {
                                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xor = 1U;
                                            }
                                        }
                                    }
                                    if ((0x00002000U 
                                         & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                        if ((0x00001000U 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                            if ((0U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000019U))) {
                                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_and = 1U;
                                            }
                                        }
                                        if ((1U & (~ 
                                                   (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                    >> 0x0000000cU)))) {
                                            if ((0U 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x00000019U))) {
                                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_or = 1U;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if ((4U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                        if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                            if ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lui = 1U;
                            }
                        }
                    }
                }
            }
            if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                          >> 4U)))) {
                if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.top__DOT__u_core__DOT__IR 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                            if ((1U & vlSelfRef.top__DOT__u_core__DOT__IR)) {
                                if ((0U != (7U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000000cU)))) {
                                    if ((2U != (7U 
                                                & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                   >> 0x0000000cU)))) {
                                        if ((1U == 
                                             (7U & 
                                              (vlSelfRef.top__DOT__u_core__DOT__IR 
                                               >> 0x0000000cU)))) {
                                            vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh = 1U;
                                        }
                                    }
                                    if ((2U == (7U 
                                                & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                   >> 0x0000000cU)))) {
                                        vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sw = 1U;
                                    }
                                }
                                if ((0U == (7U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000000cU)))) {
                                    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sb = 1U;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_valid_r 
        = __Vdly__top__DOT__u_core__DOT__u_arb__DOT__m_valid_r;
    vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__imm 
        = ((0U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type))
            ? (((- (IData)((vlSelfRef.top__DOT__u_core__DOT__IR 
                            >> 0x0000001fU))) << 0x0000000cU) 
               | (vlSelfRef.top__DOT__u_core__DOT__IR 
                  >> 0x00000014U)) : ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type))
                                       ? (((- (IData)(
                                                      (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                       >> 0x0000001fU))) 
                                           << 0x0000000cU) 
                                          | ((0x00000fe0U 
                                              & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                 >> 0x00000014U)) 
                                             | (0x0000001fU 
                                                & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                   >> 7U))))
                                       : ((2U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type))
                                           ? (0xfffff000U 
                                              & vlSelfRef.top__DOT__u_core__DOT__IR)
                                           : ((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type))
                                               ? ((
                                                   (- (IData)(
                                                              (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                               >> 0x0000001fU))) 
                                                   << 0x0000000dU) 
                                                  | ((((2U 
                                                        & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                           >> 0x0000001eU)) 
                                                       | (1U 
                                                          & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                             >> 7U))) 
                                                      << 0x0000000bU) 
                                                     | ((0x000007e0U 
                                                         & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                            >> 0x00000014U)) 
                                                        | (0x0000001eU 
                                                           & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                              >> 7U)))))
                                               : ((4U 
                                                   == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type))
                                                   ? 
                                                  ((((0x00000ffeU 
                                                      & ((- (IData)(
                                                                    (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                                     >> 0x0000001fU))) 
                                                         << 1U)) 
                                                     | (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                        >> 0x0000001fU)) 
                                                    << 0x00000014U) 
                                                   | ((((0x000001feU 
                                                         & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                            >> 0x0000000bU)) 
                                                        | (1U 
                                                           & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                              >> 0x00000014U))) 
                                                       << 0x0000000bU) 
                                                      | (0x000007feU 
                                                         & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                            >> 0x00000014U))))
                                                   : 0U)))));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_7 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_and) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slli));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_10 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slti) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltiu));
    vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wen 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrw) 
           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs) 
              & (0U != (0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                       >> 0x0000000fU)))));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_4 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrw));
    vlSelfRef.__Vtableidx5 = ((((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu) 
                                << 5U) | (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                           << 4U) | 
                                          ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                           << 3U))) 
                              | (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                  << 2U) | (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                             << 1U) 
                                            | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq))));
    vlSelfRef.top__DOT__u_core__DOT__branch_type = 
        Vtop__ConstPool__TABLE_hf13ebc3c_0[vlSelfRef.__Vtableidx5];
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_8 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_3 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jalr));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_1 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sb) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sw));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_2 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lhu));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_signed 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lb) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_6 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lb) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lhu));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_0 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lb) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lbu));
    vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)
            ? vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg
            : vlSelfRef.top__DOT__u_core__DOT__alu_out);
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_9 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sra) 
           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srai) 
              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sll) 
                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srli) 
                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_andi) 
                       | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srl) 
                          | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_7) 
                             | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_4))))))));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jalr)
            ? 1U : (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                              | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_8)))))
                     ? 3U : ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal)
                              ? 2U : ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ecall)
                                       ? 4U : ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_mret)
                                                ? 5U
                                                : 0U)))));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_addi) 
           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_3) 
              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add) 
                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lui) 
                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lbu) 
                       | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw) 
                          | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc) 
                             | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xor) 
                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sub) 
                                   | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xori) 
                                      | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_or) 
                                         | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ori) 
                                            | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_10)))))))))))));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_we 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_1) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_re 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_0) 
           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw) 
              | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_2)));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width 
        = (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sb) 
            | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_0))
            ? 0U : (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw) 
                     | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sw))
                     ? 2U : (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_2) 
                              | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh))
                              ? 1U : 2U)));
    vlSelfRef.top__DOT__u_core__DOT____Vcellinp__u_rtc__arvalid 
        = ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
           & (0x00a00000U == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                              >> 8U)));
    vlSelfRef.top__DOT__u_core__DOT__pmem_sel = ((0x80U 
                                                  <= 
                                                  (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                   >> 0x00000018U)) 
                                                 & (0x87U 
                                                    >= 
                                                    (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                     >> 0x00000018U)));
    if ((0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                         >> 4U))) {
        vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__bvalid 
            = vlSelfRef.top__DOT__u_core__DOT__uart_bvalid;
        vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rvalid 
            = vlSelfRef.top__DOT__u_core__DOT__uart_rvalid;
        vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__resp_rdata = 0U;
    } else {
        vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__bvalid 
            = vlSelfRef.top__DOT__u_core__DOT__dmem_bvalid;
        if ((0x00a00000U == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                             >> 8U))) {
            vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rvalid 
                = vlSelfRef.top__DOT__u_core__DOT__rtc_rvalid;
            vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__resp_rdata 
                = vlSelfRef.top__DOT__u_core__DOT__rtc_rdata;
        } else {
            vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rvalid 
                = vlSelfRef.top__DOT__u_core__DOT__dmem_rvalid;
            vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__resp_rdata 
                = vlSelfRef.top__DOT__u_core__DOT__dmem_rdata;
        }
    }
    vlSelfRef.aborted = (6U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state));
    vlSelfRef.state_dbg = vlSelfRef.top__DOT__u_core__DOT__ctrl_state;
    vlSelfRef.top__DOT__u_core__DOT____Vcellinp__u_mem__awvalid 
        = ((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
           & (IData)(vlSelfRef.top__DOT__u_core__DOT__pmem_sel));
    vlSelfRef.__Vtableidx1 = (((((((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)) 
                                   & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_we)) 
                                  << 5U) | (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_valid_r) 
                                             << 4U) 
                                            | (((0x0a00003fU 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                  >> 4U)) 
                                                || ((0x00a00000U 
                                                     == 
                                                     (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                      >> 8U)) 
                                                    || (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_arready))) 
                                               << 3U))) 
                                | (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rvalid) 
                                    << 2U) | ((((0x0a00003fU 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                  >> 4U)) 
                                                || (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_awready)) 
                                               << 1U) 
                                              | ((0x0a00003fU 
                                                  == 
                                                  (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                   >> 4U)) 
                                                 || (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv))))) 
                               << 5U) | (((0x10U > (IData)(vlSelfRef.top__DOT__u_core__DOT__u_lfsr__DOT__state)) 
                                          << 4U) | 
                                         (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__bvalid) 
                                           << 3U) | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state))));
    vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__next_state 
        = Vtop__ConstPool__TABLE_h8b11fe7c_0[vlSelfRef.__Vtableidx1];
    vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_done 
        = (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rready) 
            & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rvalid)) 
           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__bvalid) 
              & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__bready)));
    vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2 
        = (vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__resp_rdata 
           >> (0x00000018U & (vlSelfRef.top__DOT__u_core__DOT__alu_out 
                              << 3U)));
    vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_3 
        = (vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__resp_rdata 
           >> (0x00000010U & (vlSelfRef.top__DOT__u_core__DOT__alu_out 
                              << 3U)));
    vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__handshake_done 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_done) 
           & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu));
    vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_imm 
        = vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__imm;
    vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_csr_data 
        = vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_data;
    vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_mem_data 
        = ((0U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
            ? ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_signed)
                ? (((- (IData)((1U & (vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2 
                                      >> 7U)))) << 8U) 
                   | (0x000000ffU & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2))
                : (0x000000ffU & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2))
            : ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                ? ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_signed)
                    ? (((- (IData)((1U & (vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_3 
                                          >> 0x0000000fU)))) 
                        << 0x00000010U) | (0x0000ffffU 
                                           & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_3))
                    : (0x0000ffffU & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_3))
                : vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__resp_rdata));
    vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_alu_result 
        = vlSelfRef.top__DOT__u_core__DOT__alu_out;
    vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_pc4 
        = ((IData)(4U) + vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg);
    vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_wb_sel 
        = (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add) 
            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_addi) 
               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc) 
                  | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xor) 
                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sub) 
                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xori) 
                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_or) 
                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slti) 
                                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltiu) 
                                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                                       | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ori) 
                                          | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                                             | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sra) 
                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srai) 
                                                   | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sll) 
                                                      | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srli) 
                                                         | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_andi) 
                                                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srl) 
                                                               | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_7)))))))))))))))))))
            ? 0U : ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_3)
                     ? 1U : (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw) 
                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lbu) 
                                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh) 
                                    | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_6))))
                              ? 2U : ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lui)
                                       ? 3U : ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_4)
                                                ? 4U
                                                : 0U)))));
    vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__Vfuncout 
        = ((4U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_wb_sel))
            ? ((2U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_wb_sel))
                ? 0U : ((1U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_wb_sel))
                         ? 0U : vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_csr_data))
            : ((2U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_wb_sel))
                ? ((1U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_wb_sel))
                    ? vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_imm
                    : vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_mem_data)
                : ((1U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_wb_sel))
                    ? vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_pc4
                    : vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_alu_result)));
    vlSelfRef.top__DOT__u_core__DOT__wb_data = vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__Vfuncout;
    vlSelfRef.top__DOT__u_core__DOT__ctrl_ir_we = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__handshake_done) 
                                                   & (1U 
                                                      == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state)));
    vlSelfRef.__Vtableidx3 = ((((((IData)(vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__handshake_done) 
                                  << 3U) | (4U & ((
                                                   (~ 
                                                    ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11) 
                                                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_1) 
                                                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ebreak) 
                                                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh) 
                                                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                                                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                                                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                                                       | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                                                          | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                                                                             | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_2) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lb) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srai) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sll) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sra) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srl) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srli) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_and) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_andi) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slli) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrw) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ecall) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_fence) 
                                                                                | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_mret)))))))))))))))))))))))))))) 
                                                   | (IData)(
                                                             ((0x02000013U 
                                                               == 
                                                               (0x0200007fU 
                                                                & vlSelfRef.top__DOT__u_core__DOT__IR)) 
                                                              & ((1U 
                                                                  == 
                                                                  (7U 
                                                                   & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                                      >> 0x0000000cU))) 
                                                                 | (5U 
                                                                    == 
                                                                    (7U 
                                                                     & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                                        >> 0x0000000cU))))))) 
                                                  << 2U))) 
                                | (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_we) 
                                    << 1U) | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_re))) 
                               << 4U) | ((((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)) 
                                           & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_done)) 
                                          << 3U) | (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state)));
    vlSelfRef.top__DOT__u_core__DOT__u_ctrl__DOT__next_state 
        = Vtop__ConstPool__TABLE_h9af52e12_0[vlSelfRef.__Vtableidx3];
}

void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__1\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v1;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v1 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v2;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v2 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v3;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v3 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v4;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v4 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v5;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v5 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v6;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v6 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v7;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v7 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v8;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v8 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v9;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v9 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v10;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v10 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v11;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v11 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v12;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v12 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v13;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v13 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v14;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v14 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v15;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v15 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v16;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v16 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v17;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v17 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v18;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v18 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v19;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v19 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v20;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v20 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v21;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v21 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v22;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v22 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v23;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v23 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v24;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v24 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v25;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v25 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v26;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v26 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v27;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v27 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v28;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v28 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v29;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v29 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v30;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v30 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v31;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v31 = 0;
    // Body
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__i = 0x00000020U;
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v1 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [1U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v2 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [2U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v3 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [3U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v4 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [4U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v5 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [5U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v6 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [6U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v7 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [7U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v8 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [8U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v9 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [9U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v10 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x0aU];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v11 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x0bU];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v12 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x0cU];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v13 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x0dU];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v14 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x0eU];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v15 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x0fU];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v16 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x10U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v17 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x11U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v18 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x12U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v19 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x13U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v20 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x14U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v21 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x15U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v22 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x16U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v23 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x17U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v24 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x18U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v25 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x19U];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v26 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x1aU];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v27 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x1bU];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v28 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x1cU];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v29 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x1dU];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v30 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x1eU];
    __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v31 
        = vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
        [0x1fU];
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[1U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v1;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[2U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v2;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[3U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v3;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[4U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v4;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[5U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v5;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[6U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v6;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[7U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v7;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[8U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v8;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[9U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v9;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x0aU] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v10;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x0bU] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v11;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x0cU] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v12;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x0dU] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v13;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x0eU] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v14;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x0fU] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v15;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x10U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v16;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x11U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v17;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x12U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v18;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x13U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v19;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x14U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v20;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x15U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v21;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x16U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v22;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x17U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v23;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x18U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v24;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x19U] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v25;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x1aU] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v26;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x1bU] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v27;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x1cU] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v28;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x1dU] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v29;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x1eU] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v30;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0x1fU] 
        = __VdlyVal__top__DOT__u_core__DOT__u_regfile__DOT__rf_read__v31;
}

void Vtop___024root___nba_comb__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
        = ((0U == (0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                  >> 0x0000000fU)))
            ? 0U : vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read
           [(0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                            >> 0x0000000fU))]);
    vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data 
        = ((0U == (0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                  >> 0x00000014U)))
            ? 0U : vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read
           [(0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                            >> 0x00000014U))]);
    vlSelfRef.top__DOT__u_core__DOT__alu_result = ((IData)(vlSelfRef.top__DOT__u_core__DOT__alu_en)
                                                    ? 
                                                   ([&]() {
                vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b 
                    = ((IData)(vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm)
                        ? vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__imm
                        : vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data);
                vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__a 
                    = (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc) 
                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal) 
                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                       | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                                          | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu))))))))
                        ? vlSelfRef.pc : vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata);
                vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op 
                    = vlSelfRef.top__DOT__u_core__DOT__alu_op;
                vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__Vfuncout 
                    = ((8U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op))
                        ? ((4U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op))
                            ? 0U : ((2U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op))
                                     ? 0U : ((1U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op))
                                              ? VL_SHIFTRS_III(32,32,5, vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__a, 
                                                               (0x0000001fU 
                                                                & vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b))
                                              : (vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__a 
                                                 >> 
                                                 (0x0000001fU 
                                                  & vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b)))))
                        : ((4U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op))
                            ? ((2U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op))
                                ? ((1U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op))
                                    ? (vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__a 
                                       << (0x0000001fU 
                                           & vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b))
                                    : ((vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__a 
                                        < vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b)
                                        ? 1U : 0U))
                                : ((1U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op))
                                    ? (VL_LTS_III(32, vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__a, vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b)
                                        ? 1U : 0U) : 
                                   (vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__a 
                                    ^ vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b)))
                            : ((2U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op))
                                ? ((1U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op))
                                    ? (vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__a 
                                       | vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b)
                                    : (vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__a 
                                       & vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b))
                                : ((1U & (IData)(vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op))
                                    ? (vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__a 
                                       - vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b)
                                    : (vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__a 
                                       + vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b)))));
            }(), vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__Vfuncout)
                                                    : 0U);
    vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_wdata 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)
            ? 0U : ((0U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                     ? ((vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data 
                         << 0x00000018U) | ((0x00ff0000U 
                                             & (vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data 
                                                << 0x00000010U)) 
                                            | ((0x0000ff00U 
                                                & (vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data 
                                                   << 8U)) 
                                               | (0x000000ffU 
                                                  & vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data))))
                     : ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                         ? ((vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data 
                             << 0x00000010U) | (0x0000ffffU 
                                                & vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data))
                         : vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)));
    vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__next_pc 
        = ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
            ? (0xfffffffeU & vlSelfRef.top__DOT__u_core__DOT__alu_result)
            : (((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel)) 
                & ((6U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                    ? (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
                       == vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                    : ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                        ? (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
                           != vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                        : ((2U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                            ? VL_GTES_III(32, vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata, vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                            : ((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                ? (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
                                   >= vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                                : ((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                    ? VL_LTS_III(32, vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata, vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                                    : ((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type)) 
                                       & (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
                                          < vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data))))))))
                ? vlSelfRef.top__DOT__u_core__DOT__alu_result
                : ((2U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
                    ? vlSelfRef.top__DOT__u_core__DOT__alu_result
                    : ((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
                        ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec
                        : ((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
                            ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mepc
                            : ((IData)(4U) + vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg))))));
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__1(vlSelf);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[3U] = 1U;
    }
}

void Vtop___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_triggers__act(vlSelf);
    Vtop___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vtop___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtop___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        Vtop___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("vsrc/top.v", 1, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("vsrc/top.v", 1, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vtop___024root___eval_phase__act(vlSelf));
    } while (Vtop___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
}
#endif  // VL_DEBUG
