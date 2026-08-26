// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_initial__TOP(vlSelf);
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg = 0x80000000U;
    vlSelfRef.top__DOT__u_core__DOT__uart_bvalid = 0U;
    vlSelfRef.top__DOT__u_core__DOT__uart_rvalid = 0U;
    vlSelfRef.top__DOT__u_core__DOT__dmem_rvalid = 0U;
    vlSelfRef.top__DOT__u_core__DOT__dmem_bvalid = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__rd_delay = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__wr_delay = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[1U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[2U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[3U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[4U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[5U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[6U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[7U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[8U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[9U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x0aU] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x0bU] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x0cU] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x0dU] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x0eU] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x0fU] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x10U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x11U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x12U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x13U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x14U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x15U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x16U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x17U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x18U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x19U] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x1aU] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x1bU] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x1cU] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x1dU] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x1eU] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0x1fU] = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mvendroid = 0x79737978U;
    vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__marchid = 0x018d08cfU;
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("vsrc/top.v", 1, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vtop___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vtop___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtop___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__stl\n"); );
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

extern const VlUnpacked<CData/*2:0*/, 128> Vtop__ConstPool__TABLE_h540c7ad9_0;
extern const VlUnpacked<CData/*2:0*/, 64> Vtop__ConstPool__TABLE_hf13ebc3c_0;
extern const VlUnpacked<CData/*2:0*/, 1024> Vtop__ConstPool__TABLE_hbf2ead68_0;
extern const VlUnpacked<CData/*2:0*/, 256> Vtop__ConstPool__TABLE_h9af52e12_0;

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.halt = (0x00100073U == vlSelfRef.top__DOT__u_core__DOT__IR);
    vlSelfRef.aborted = (6U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state));
    vlSelfRef.ir_dbg = vlSelfRef.top__DOT__u_core__DOT__IR;
    vlSelfRef.state_dbg = vlSelfRef.top__DOT__u_core__DOT__ctrl_state;
    vlSelfRef.mmio_dbg = vlSelfRef.top__DOT__u_core__DOT__mmio_flag;
    vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm = 0U;
    vlSelfRef.top__DOT__u_core__DOT__alu_op = 0U;
    vlSelfRef.top__DOT__u_core__DOT__alu_en = 0U;
    vlSelfRef.pc = vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ebreak = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_fence = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT____VdfgRegularize_ha4eaa22b_0_1 
        = (1U & (~ ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__rd_delay) 
                    | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__wr_delay))));
    vlSelfRef.top__DOT__u_core__DOT__r_data1 = ((0U 
                                                 == 
                                                 (0x0000001fU 
                                                  & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                     >> 0x0000000fU)))
                                                 ? 0U
                                                 : 
                                                vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
                                                [(0x0000001fU 
                                                  & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                     >> 0x0000000fU))]);
    vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data 
        = ((0U == (0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                  >> 0x00000014U)))
            ? 0U : vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf
           [(0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                            >> 0x00000014U))]);
    vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_read 
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
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srli = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srai = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srl = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sra = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sll = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_andi = 0U;
    vlSelfRef.__Vtableidx3 = (0x0000007fU & vlSelfRef.top__DOT__u_core__DOT__IR);
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type 
        = Vtop__ConstPool__TABLE_h540c7ad9_0[vlSelfRef.__Vtableidx3];
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slli = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_and = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrw = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltiu = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slti = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ori = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_or = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lui = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xor = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xori = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_addi = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sub = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jalr = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sb = 0U;
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sw = 0U;
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
    vlSelfRef.top__DOT__u_core__DOT__dmem_arready = 
        ((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv)) 
         & ((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_rvalid)) 
            & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT____VdfgRegularize_ha4eaa22b_0_1)));
    vlSelfRef.top__DOT__u_core__DOT__dmem_awready = 
        ((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv)) 
         & ((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_bvalid)) 
            & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT____VdfgRegularize_ha4eaa22b_0_1)));
    vlSelfRef.top__DOT__u_core__DOT__imm = ((0U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type))
                                             ? (((- (IData)(
                                                            (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                             >> 0x0000001fU))) 
                                                 << 0x0000000cU) 
                                                | (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                   >> 0x00000014U))
                                             : ((1U 
                                                 == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type))
                                                 ? 
                                                (((- (IData)(
                                                             (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                              >> 0x0000001fU))) 
                                                  << 0x0000000cU) 
                                                 | ((0x00000fe0U 
                                                     & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                        >> 0x00000014U)) 
                                                    | (0x0000001fU 
                                                       & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                          >> 7U))))
                                                 : 
                                                ((2U 
                                                  == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type))
                                                  ? 
                                                 (0xfffff000U 
                                                  & vlSelfRef.top__DOT__u_core__DOT__IR)
                                                  : 
                                                 ((3U 
                                                   == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type))
                                                   ? 
                                                  (((- (IData)(
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
                                                   : 
                                                  ((4U 
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
    vlSelfRef.top__DOT__u_core__DOT__csr_wen = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrw) 
                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs) 
                                                   & (0U 
                                                      != 
                                                      (0x0000001fU 
                                                       & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                          >> 0x0000000fU)))));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_4 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrw));
    vlSelfRef.__Vtableidx4 = ((((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu) 
                                << 5U) | (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                           << 4U) | 
                                          ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                           << 3U))) 
                              | (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                  << 2U) | (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                             << 1U) 
                                            | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq))));
    vlSelfRef.top__DOT__u_core__DOT__branch_type = 
        Vtop__ConstPool__TABLE_hf13ebc3c_0[vlSelfRef.__Vtableidx4];
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_1 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sb) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sw));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jalr)
            ? 1U : (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                 | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu))))))
                     ? 3U : ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal)
                              ? 2U : ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ecall)
                                       ? 4U : ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_mret)
                                                ? 5U
                                                : 0U)))));
    vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_3 
        = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal) 
           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jalr));
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
    vlSelfRef.top__DOT__u_core__DOT__m_req_addr = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)
                                                    ? vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg
                                                    : vlSelfRef.top__DOT__u_core__DOT__alu_out);
    vlSelfRef.top__DOT__u_core__DOT__rtc_arvalid = 
        ((0x00a00000U == (vlSelfRef.top__DOT__u_core__DOT__m_req_addr 
                          >> 8U)) & (1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)));
    vlSelfRef.top__DOT__u_core__DOT__u_xbar__DOT__ar_mem 
        = ((0x80U <= (vlSelfRef.top__DOT__u_core__DOT__m_req_addr 
                      >> 0x00000018U)) & (0x87U >= 
                                          (vlSelfRef.top__DOT__u_core__DOT__m_req_addr 
                                           >> 0x00000018U)));
    vlSelfRef.top__DOT__u_core__DOT__alu_result = ((IData)(vlSelfRef.top__DOT__u_core__DOT__alu_en)
                                                    ? 
                                                   ([&]() {
                vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b 
                    = ((IData)(vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm)
                        ? vlSelfRef.top__DOT__u_core__DOT__imm
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
                        ? vlSelfRef.pc : vlSelfRef.top__DOT__u_core__DOT__r_data1);
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
    vlSelfRef.top__DOT__u_core__DOT__mem_we = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_1) 
                                               | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh));
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
                                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slti) 
                                               | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltiu))))))))))))));
    vlSelfRef.top__DOT__u_core__DOT__mem_re = ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_0) 
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
    vlSelfRef.top__DOT__u_core__DOT__m_req_wdata = 
        ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)
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
    vlSelfRef.top__DOT__u_core__DOT__dmem_awvalid = 
        ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_xbar__DOT__ar_mem) 
         & (3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)));
    if ((0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__m_req_addr 
                         >> 4U))) {
        vlSelfRef.top__DOT__u_core__DOT__m_bvalid = 
            (1U & (IData)(vlSelfRef.top__DOT__u_core__DOT__uart_bvalid));
        vlSelfRef.top__DOT__u_core__DOT__m_rvalid = 
            (1U & (IData)(vlSelfRef.top__DOT__u_core__DOT__uart_rvalid));
        vlSelfRef.top__DOT__u_core__DOT__inst = 0U;
    } else {
        vlSelfRef.top__DOT__u_core__DOT__m_bvalid = 
            (1U & ((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_xbar__DOT__ar_mem)) 
                   | (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_bvalid)));
        if ((0x00a00000U == (vlSelfRef.top__DOT__u_core__DOT__m_req_addr 
                             >> 8U))) {
            vlSelfRef.top__DOT__u_core__DOT__m_rvalid 
                = (1U & (IData)(vlSelfRef.top__DOT__u_core__DOT__rtc_rvalid));
            vlSelfRef.top__DOT__u_core__DOT__inst = vlSelfRef.top__DOT__u_core__DOT__rtc_rdata;
        } else {
            vlSelfRef.top__DOT__u_core__DOT__m_rvalid 
                = (1U & ((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_xbar__DOT__ar_mem)) 
                         | (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_rvalid)));
            vlSelfRef.top__DOT__u_core__DOT__inst = 
                ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_xbar__DOT__ar_mem)
                  ? vlSelfRef.top__DOT__u_core__DOT__dmem_rdata
                  : 0U);
        }
    }
    vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__next_pc 
        = ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
            ? (0xfffffffeU & vlSelfRef.top__DOT__u_core__DOT__alu_result)
            : (((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel)) 
                & ((6U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                    ? (vlSelfRef.top__DOT__u_core__DOT__r_data1 
                       == vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                    : ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                        ? (vlSelfRef.top__DOT__u_core__DOT__r_data1 
                           != vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                        : ((2U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                            ? VL_GTES_III(32, vlSelfRef.top__DOT__u_core__DOT__r_data1, vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                            : ((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                ? (vlSelfRef.top__DOT__u_core__DOT__r_data1 
                                   >= vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                                : ((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                    ? VL_LTS_III(32, vlSelfRef.top__DOT__u_core__DOT__r_data1, vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                                    : ((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type)) 
                                       & (vlSelfRef.top__DOT__u_core__DOT__r_data1 
                                          < vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data))))))))
                ? vlSelfRef.top__DOT__u_core__DOT__alu_result
                : ((2U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
                    ? vlSelfRef.top__DOT__u_core__DOT__alu_result
                    : ((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
                        ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec
                        : ((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
                            ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mepc
                            : ((IData)(4U) + vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg))))));
    vlSelfRef.__Vtableidx1 = (((((((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)) 
                                   & (IData)(vlSelfRef.top__DOT__u_core__DOT__mem_we)) 
                                  << 4U) | (((IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_valid_r) 
                                             << 3U) 
                                            | (((0x0a00003fU 
                                                 == 
                                                 (vlSelfRef.top__DOT__u_core__DOT__m_req_addr 
                                                  >> 4U)) 
                                                || ((0x00a00000U 
                                                     == 
                                                     (vlSelfRef.top__DOT__u_core__DOT__m_req_addr 
                                                      >> 8U)) 
                                                    || (1U 
                                                        & ((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_xbar__DOT__ar_mem)) 
                                                           | (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_arready))))) 
                                               << 2U))) 
                                | (((IData)(vlSelfRef.top__DOT__u_core__DOT__m_rvalid) 
                                    << 1U) | ((0x0a00003fU 
                                               == (vlSelfRef.top__DOT__u_core__DOT__m_req_addr 
                                                   >> 4U)) 
                                              || (1U 
                                                  & ((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_xbar__DOT__ar_mem)) 
                                                     | (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_awready)))))) 
                               << 5U) | ((((0x0a00003fU 
                                            == (vlSelfRef.top__DOT__u_core__DOT__m_req_addr 
                                                >> 4U)) 
                                           || (1U & 
                                               ((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_xbar__DOT__ar_mem)) 
                                                | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv)))) 
                                          << 4U) | 
                                         (((IData)(vlSelfRef.top__DOT__u_core__DOT__m_bvalid) 
                                           << 3U) | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state))));
    vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__next_state 
        = Vtop__ConstPool__TABLE_hbf2ead68_0[vlSelfRef.__Vtableidx1];
    vlSelfRef.top__DOT__u_core__DOT__m_done = (((2U 
                                                 == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
                                                & (IData)(vlSelfRef.top__DOT__u_core__DOT__m_rvalid)) 
                                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__m_bvalid) 
                                                  & (5U 
                                                     == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state))));
    vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2 
        = (vlSelfRef.top__DOT__u_core__DOT__inst >> 
           (0x00000018U & (vlSelfRef.top__DOT__u_core__DOT__alu_out 
                           << 3U)));
    vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_3 
        = (vlSelfRef.top__DOT__u_core__DOT__inst >> 
           (0x00000010U & (vlSelfRef.top__DOT__u_core__DOT__alu_out 
                           << 3U)));
    vlSelfRef.top__DOT__u_core__DOT__ifu_done = ((IData)(vlSelfRef.top__DOT__u_core__DOT__m_done) 
                                                 & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu));
    vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_imm 
        = vlSelfRef.top__DOT__u_core__DOT__imm;
    vlSelfRef.__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_csr_data 
        = vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_read;
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
                : vlSelfRef.top__DOT__u_core__DOT__inst));
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
    vlSelfRef.top__DOT__u_core__DOT__ctrl_ir_we = ((IData)(vlSelfRef.top__DOT__u_core__DOT__ifu_done) 
                                                   & (1U 
                                                      == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state)));
    vlSelfRef.__Vtableidx2 = ((((((IData)(vlSelfRef.top__DOT__u_core__DOT__ifu_done) 
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
                                | (((IData)(vlSelfRef.top__DOT__u_core__DOT__mem_we) 
                                    << 1U) | (IData)(vlSelfRef.top__DOT__u_core__DOT__mem_re))) 
                               << 4U) | ((((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)) 
                                           & (IData)(vlSelfRef.top__DOT__u_core__DOT__m_done)) 
                                          << 3U) | (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state)));
    vlSelfRef.top__DOT__u_core__DOT__u_ctrl__DOT__next_state 
        = Vtop__ConstPool__TABLE_h9af52e12_0[vlSelfRef.__Vtableidx2];
}

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vtop___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtop___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->halt = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11049222807502041558ull);
    vlSelf->aborted = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4868682049854349875ull);
    vlSelf->pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4211327832146562899ull);
    vlSelf->ir_dbg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15075204503865564024ull);
    vlSelf->state_dbg = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 6042213990076480022ull);
    vlSelf->stall_ifu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17322703457740471759ull);
    vlSelf->mmio_dbg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9554483427072562357ull);
    vlSelf->top__DOT__u_core__DOT__inst = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2417272985412653589ull);
    vlSelf->top__DOT__u_core__DOT__ifu_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1643661922859531240ull);
    vlSelf->top__DOT__u_core__DOT__m_req_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14103835474802955303ull);
    vlSelf->top__DOT__u_core__DOT__m_req_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15172507337633803254ull);
    vlSelf->top__DOT__u_core__DOT__m_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1054445868233723499ull);
    vlSelf->top__DOT__u_core__DOT__m_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11784486716547168036ull);
    vlSelf->top__DOT__u_core__DOT__m_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14104572128603376394ull);
    vlSelf->top__DOT__u_core__DOT__imm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3520739126106933177ull);
    vlSelf->top__DOT__u_core__DOT__alu_op = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 3306366242686482610ull);
    vlSelf->top__DOT__u_core__DOT__alu_src2_imm = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4805873606988371846ull);
    vlSelf->top__DOT__u_core__DOT__alu_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11934238896666575621ull);
    vlSelf->top__DOT__u_core__DOT__mem_re = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12508707161427236381ull);
    vlSelf->top__DOT__u_core__DOT__mem_we = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7925759870939498457ull);
    vlSelf->top__DOT__u_core__DOT__branch_type = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10683641873153630806ull);
    vlSelf->top__DOT__u_core__DOT__r_data1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11555001605828081059ull);
    vlSelf->top__DOT__u_core__DOT__alu_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1155168294279643942ull);
    vlSelf->top__DOT__u_core__DOT__wb_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 652582278752513991ull);
    vlSelf->top__DOT__u_core__DOT__csr_wen = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8977130986363215394ull);
    vlSelf->top__DOT__u_core__DOT__ctrl_state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 18358527596681774975ull);
    vlSelf->top__DOT__u_core__DOT__ctrl_ir_we = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16689648258247375033ull);
    vlSelf->top__DOT__u_core__DOT__dmem_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4042773554843693272ull);
    vlSelf->top__DOT__u_core__DOT__rtc_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10594332709997637517ull);
    vlSelf->top__DOT__u_core__DOT__IR = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7773111407760685233ull);
    vlSelf->top__DOT__u_core__DOT__ir_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8129015921111941437ull);
    vlSelf->top__DOT__u_core__DOT__alu_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5103381572749926900ull);
    vlSelf->top__DOT__u_core__DOT__rtc_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15451904356198807515ull);
    vlSelf->top__DOT__u_core__DOT__rtc_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12750002723409178501ull);
    vlSelf->top__DOT__u_core__DOT__uart_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1372124949468861760ull);
    vlSelf->top__DOT__u_core__DOT__uart_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12508497576293858631ull);
    vlSelf->top__DOT__u_core__DOT__dmem_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6627972348826255339ull);
    vlSelf->top__DOT__u_core__DOT__dmem_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13084471804129813225ull);
    vlSelf->top__DOT__u_core__DOT__dmem_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4656891681854951424ull);
    vlSelf->top__DOT__u_core__DOT__dmem_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3978391184838138206ull);
    vlSelf->top__DOT__u_core__DOT__dmem_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10556181952209269361ull);
    vlSelf->top__DOT__u_core__DOT__mmio_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10489147620269404093ull);
    vlSelf->top__DOT__u_core__DOT__u_ifu__DOT__pc_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2766230339152843059ull);
    vlSelf->top__DOT__u_core__DOT__u_ifu__DOT__next_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16068160163048828511ull);
    vlSelf->top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8352065280734966544ull);
    vlSelf->top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10545329827589676959ull);
    vlSelf->top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8872451939442426854ull);
    vlSelf->top__DOT__u_core__DOT__u_arb__DOT__m_valid_r = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13157573800912678161ull);
    vlSelf->top__DOT__u_core__DOT__u_master__DOT__state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10309067849075006674ull);
    vlSelf->top__DOT__u_core__DOT__u_master__DOT__next_state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 2481012515736338292ull);
    vlSelf->top__DOT__u_core__DOT__u_xbar__DOT__ar_mem = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13974450284649823439ull);
    vlSelf->top__DOT__u_core__DOT__u_ctrl__DOT__next_state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 7429608952928147908ull);
    vlSelf->top__DOT__u_core__DOT__u_rtc__DOT__now_us = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 2426469311810486920ull);
    vlSelf->top__DOT__u_core__DOT__u_mem__DOT__aw_recv = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1699125886008017202ull);
    vlSelf->top__DOT__u_core__DOT__u_mem__DOT__aw_addr_latch = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16652105164904880200ull);
    vlSelf->top__DOT__u_core__DOT__u_mem__DOT__w_mask_latch = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 4873295938291901141ull);
    vlSelf->top__DOT__u_core__DOT__u_mem__DOT__cnt = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 2933639740758538322ull);
    vlSelf->top__DOT__u_core__DOT__u_mem__DOT__rd_delay = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6727002360022129678ull);
    vlSelf->top__DOT__u_core__DOT__u_mem__DOT__wr_delay = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10010015919280449861ull);
    vlSelf->top__DOT__u_core__DOT__u_mem__DOT____VdfgRegularize_ha4eaa22b_0_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17382088051150113432ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__mem_width = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4146500611482369462ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__mem_signed = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6741950106578237665ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__npc_sel = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 8513120433288965746ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__imm_type = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10777651286093629664ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_jal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4700438736010278649ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5911616755744786795ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_bne = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8278628661212228373ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_beq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14625830661895210039ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_bge = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17705827921820764543ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_bgeu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12136690001490381659ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_blt = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13567842607339157131ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_bltu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3587836951906065746ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_lui = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1286915713492780378ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_lbu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7058693003741154891ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_lw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16257821205712055673ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_lb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10559573943346323212ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_lh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8596912780177831878ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_lhu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10803052931109656963ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_ebreak = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7305299295051968556ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_csrrs = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5603489414825002759ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_csrrw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15461868584003935753ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_ecall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5632079755213721530ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_mret = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4477035598323049098ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_fence = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14644650340163894617ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_sb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6805191172132192439ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_sw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12353280736211899847ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_sh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9721683453050455039ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_auipc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6594337490679511688ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_or = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3640421751231576906ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_ori = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 314706135528622858ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_xor = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13749992253058903320ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_xori = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2793481913425343719ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_add = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14232611244542864972ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_addi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10631999269481575860ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_sub = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12194503831034511421ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_slti = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1184252700634015244ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_sltiu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17901600433668539917ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_and = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9700730455498750972ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_andi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12228106381493398129ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_sra = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7737914307449062341ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_srai = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17194209821820535021ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_srl = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9647128041837258244ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_sll = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1861033851532355076ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_slli = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4112893902196594697ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_srli = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11382363868574851059ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_sltu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13425941053769988825ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT__is_slt = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12221280317410100070ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16812701022399024948ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10654905750808330760ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7355725715445529996ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2869773297947823681ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4425963065332469969ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13077037539567635656ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14633227306952317048ull);
    vlSelf->top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14880486202174187874ull);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->top__DOT__u_core__DOT__u_regfile__DOT__rf[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1950181590513781821ull);
    }
    vlSelf->top__DOT__u_core__DOT__u_exu__DOT__rs2_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15722008089695203101ull);
    vlSelf->top__DOT__u_core__DOT__u_CSRFile__DOT__csr_read = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7574565168479766693ull);
    vlSelf->top__DOT__u_core__DOT__u_CSRFile__DOT__mcycle = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8359660978686605147ull);
    vlSelf->top__DOT__u_core__DOT__u_CSRFile__DOT__mvendroid = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 873683739740681106ull);
    vlSelf->top__DOT__u_core__DOT__u_CSRFile__DOT__marchid = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7831898515665494346ull);
    vlSelf->top__DOT__u_core__DOT__u_CSRFile__DOT__mcause = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15229678083653694607ull);
    vlSelf->top__DOT__u_core__DOT__u_CSRFile__DOT__mepc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11902051174586333109ull);
    vlSelf->top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14010047114623299440ull);
    vlSelf->top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7888744288779044881ull);
    vlSelf->__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__Vfuncout = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 974244192275401089ull);
    vlSelf->__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__op = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 11766837536649333501ull);
    vlSelf->__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__a = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6608169846821433962ull);
    vlSelf->__Vfunc_top__DOT__u_core__DOT__u_exu__DOT__alu_func__4__b = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 164592702743752160ull);
    vlSelf->__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__Vfuncout = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11997086689398144301ull);
    vlSelf->__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_wb_sel = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10218818733978071043ull);
    vlSelf->__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_pc4 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18006408626485519218ull);
    vlSelf->__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_alu_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16428679329668508385ull);
    vlSelf->__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_mem_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17796570609836666881ull);
    vlSelf->__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_csr_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 561379556563953815ull);
    vlSelf->__Vfunc_top__DOT__u_core__DOT__u_wbu__DOT__wb_func__5__i_imm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12192883500042294682ull);
    vlSelf->__Vtableidx1 = 0;
    vlSelf->__Vtableidx2 = 0;
    vlSelf->__Vtableidx3 = 0;
    vlSelf->__Vtableidx4 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9526919608049418986ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
