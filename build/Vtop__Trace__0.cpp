// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[0U]))) {
        bufp->chgIData(oldp+0,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mvendroid),32);
        bufp->chgIData(oldp+1,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__marchid),32);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgIData(oldp+2,(((IData)(4U) + vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg)),32);
        bufp->chgIData(oldp+3,(vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__resp_rdata),32);
        bufp->chgBit(oldp+4,(vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__handshake_done));
        bufp->chgBit(oldp+5,((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state))));
        bufp->chgIData(oldp+6,(vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg),32);
        bufp->chgBit(oldp+7,(((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state)) 
                              & ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_re) 
                                 | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_we)))));
        bufp->chgIData(oldp+8,(vlSelfRef.top__DOT__u_core__DOT__alu_out),32);
        bufp->chgCData(oldp+9,((0x0000000fU & ((0U 
                                                == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                                                ? ((IData)(1U) 
                                                   << 
                                                   (3U 
                                                    & vlSelfRef.top__DOT__u_core__DOT__alu_out))
                                                : (
                                                   (1U 
                                                    == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                                                    ? 
                                                   ((2U 
                                                     & vlSelfRef.top__DOT__u_core__DOT__alu_out)
                                                     ? 0x0cU
                                                     : 3U)
                                                    : 0x0fU)))),4);
        bufp->chgBit(oldp+10,(((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)) 
                               & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_done))));
        bufp->chgIData(oldp+11,(((0U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                                  ? ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_signed)
                                      ? (((- (IData)(
                                                     (1U 
                                                      & (vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2 
                                                         >> 7U)))) 
                                          << 8U) | 
                                         (0x000000ffU 
                                          & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2))
                                      : (0x000000ffU 
                                         & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2))
                                  : ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                                      ? ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_signed)
                                          ? (((- (IData)(
                                                         (1U 
                                                          & (vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_3 
                                                             >> 0x0000000fU)))) 
                                              << 0x00000010U) 
                                             | (0x0000ffffU 
                                                & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_3))
                                          : (0x0000ffffU 
                                             & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_3))
                                      : vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__resp_rdata))),32);
        bufp->chgBit(oldp+12,(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_valid_r));
        bufp->chgBit(oldp+13,(((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)) 
                               & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_we))));
        bufp->chgIData(oldp+14,(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr),32);
        bufp->chgCData(oldp+15,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)
                                  ? 0U : (0x0000000fU 
                                          & ((0U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                                              ? ((IData)(1U) 
                                                 << 
                                                 (3U 
                                                  & vlSelfRef.top__DOT__u_core__DOT__alu_out))
                                              : ((1U 
                                                  == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                                                  ? 
                                                 ((2U 
                                                   & vlSelfRef.top__DOT__u_core__DOT__alu_out)
                                                   ? 0x0cU
                                                   : 3U)
                                                  : 0x0fU))))),4);
        bufp->chgBit(oldp+16,(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_done));
        bufp->chgBit(oldp+17,((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state))));
        bufp->chgBit(oldp+18,(((0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                >> 4U)) 
                               || ((0x00a00000U == 
                                    (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                     >> 8U)) || (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_arready)))));
        bufp->chgBit(oldp+19,(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rvalid));
        bufp->chgBit(oldp+20,(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rready));
        bufp->chgCData(oldp+21,(((0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                  >> 4U))
                                  ? 0U : ((0x00a00000U 
                                           == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                               >> 8U))
                                           ? (IData)(vlSelfRef.top__DOT__u_core__DOT__rtc_rresp)
                                           : 0U))),2);
        bufp->chgBit(oldp+22,((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state))));
        bufp->chgBit(oldp+23,(((0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                >> 4U)) 
                               || (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_awready))));
        bufp->chgBit(oldp+24,((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state))));
        bufp->chgBit(oldp+25,(((0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                >> 4U)) 
                               || (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv))));
        bufp->chgBit(oldp+26,(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__bvalid));
        bufp->chgBit(oldp+27,(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__bready));
        bufp->chgCData(oldp+28,(vlSelfRef.top__DOT__u_core__DOT__u_lfsr__DOT__state),8);
        bufp->chgBit(oldp+29,((0x10U > (IData)(vlSelfRef.top__DOT__u_core__DOT__u_lfsr__DOT__state))));
        bufp->chgCData(oldp+30,((0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                >> 0x0000000fU))),5);
        bufp->chgCData(oldp+31,((0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                >> 0x00000014U))),5);
        bufp->chgCData(oldp+32,((0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                >> 7U))),5);
        bufp->chgBit(oldp+33,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11) 
                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh) 
                                  | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_6) 
                                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                                           | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_9))))))));
        bufp->chgIData(oldp+34,(vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__imm),32);
        bufp->chgCData(oldp+35,(vlSelfRef.top__DOT__u_core__DOT__alu_op),4);
        bufp->chgBit(oldp+36,(vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm));
        bufp->chgBit(oldp+37,(vlSelfRef.top__DOT__u_core__DOT__alu_en));
        bufp->chgBit(oldp+38,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc) 
                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal) 
                                  | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                                                 | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu))))))))));
        bufp->chgCData(oldp+39,((((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add) 
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
                                           ? 1U : (
                                                   ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw) 
                                                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lbu) 
                                                       | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh) 
                                                          | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_6))))
                                                    ? 2U
                                                    : 
                                                   ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lui)
                                                     ? 3U
                                                     : 
                                                    ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_4)
                                                      ? 4U
                                                      : 0U)))))),3);
        bufp->chgCData(oldp+40,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel),3);
        bufp->chgBit(oldp+41,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_re));
        bufp->chgBit(oldp+42,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_we));
        bufp->chgCData(oldp+43,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width),2);
        bufp->chgBit(oldp+44,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_signed));
        bufp->chgCData(oldp+45,(vlSelfRef.top__DOT__u_core__DOT__branch_type),3);
        bufp->chgBit(oldp+46,((1U & ((~ ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11) 
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
                                     | (IData)(((0x02000013U 
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
                                                          >> 0x0000000cU))))))))));
        bufp->chgIData(oldp+47,(vlSelfRef.top__DOT__u_core__DOT__wb_data),32);
        bufp->chgIData(oldp+48,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_data),32);
        bufp->chgIData(oldp+49,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec),32);
        bufp->chgIData(oldp+50,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mepc),32);
        bufp->chgSData(oldp+51,((vlSelfRef.top__DOT__u_core__DOT__IR 
                                 >> 0x00000014U)),12);
        bufp->chgBit(oldp+52,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wen));
        bufp->chgBit(oldp+53,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs));
        bufp->chgCData(oldp+54,(vlSelfRef.top__DOT__u_core__DOT__ctrl_state),3);
        bufp->chgBit(oldp+55,(vlSelfRef.top__DOT__u_core__DOT__ctrl_ir_we));
        bufp->chgBit(oldp+56,((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state))));
        bufp->chgBit(oldp+57,((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state))));
        bufp->chgIData(oldp+58,(vlSelfRef.top__DOT__u_core__DOT__IR),32);
        bufp->chgIData(oldp+59,(vlSelfRef.top__DOT__u_core__DOT__ir_pc),32);
        bufp->chgBit(oldp+60,((0x00a00000U == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                               >> 8U))));
        bufp->chgBit(oldp+61,(vlSelfRef.top__DOT__u_core__DOT__rtc_rvalid));
        bufp->chgIData(oldp+62,(vlSelfRef.top__DOT__u_core__DOT__rtc_rdata),32);
        bufp->chgCData(oldp+63,(vlSelfRef.top__DOT__u_core__DOT__rtc_rresp),2);
        bufp->chgBit(oldp+64,((0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                               >> 4U))));
        bufp->chgBit(oldp+65,(vlSelfRef.top__DOT__u_core__DOT__uart_rvalid));
        bufp->chgBit(oldp+66,(vlSelfRef.top__DOT__u_core__DOT__uart_bvalid));
        bufp->chgBit(oldp+67,(vlSelfRef.top__DOT__u_core__DOT__dmem_arready));
        bufp->chgBit(oldp+68,(vlSelfRef.top__DOT__u_core__DOT__dmem_rvalid));
        bufp->chgBit(oldp+69,(vlSelfRef.top__DOT__u_core__DOT__dmem_awready));
        bufp->chgBit(oldp+70,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv));
        bufp->chgBit(oldp+71,(vlSelfRef.top__DOT__u_core__DOT__dmem_bvalid));
        bufp->chgIData(oldp+72,(vlSelfRef.top__DOT__u_core__DOT__dmem_rdata),32);
        bufp->chgBit(oldp+73,(vlSelfRef.top__DOT__u_core__DOT__pmem_sel));
        bufp->chgBit(oldp+74,(vlSelfRef.top__DOT__u_core__DOT__mmio_flag));
        bufp->chgBit(oldp+75,((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))));
        bufp->chgBit(oldp+76,((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))));
        bufp->chgQData(oldp+77,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcycle),64);
        bufp->chgIData(oldp+79,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcause),32);
        bufp->chgIData(oldp+80,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus),32);
        bufp->chgBit(oldp+81,(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu));
        bufp->chgCData(oldp+82,(vlSelfRef.top__DOT__u_core__DOT__u_ctrl__DOT__next_state),3);
        bufp->chgBit(oldp+83,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_addi) 
                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jalr) 
                                  | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add) 
                                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw) 
                                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lbu) 
                                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sw) 
                                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sb) 
                                                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xor) 
                                                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sub) 
                                                       | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xori) 
                                                          | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_or) 
                                                             | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ori) 
                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_10) 
                                                                   | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                                                                      | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                                                         | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                                                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                                                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_8) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_2) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lb) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh) 
                                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                                                                                | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_9))))))))))))))))))))))))));
        bufp->chgBit(oldp+84,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add) 
                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_1) 
                                  | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sub) 
                                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xor) 
                                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_or) 
                                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                                                 | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                                    | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                                       | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                                          | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu) 
                                                             | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                                                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh) 
                                                                   | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                                                                      | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sll) 
                                                                         | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sra) 
                                                                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_and) 
                                                                               | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srl))))))))))))))))))));
        bufp->chgCData(oldp+85,((0x0000007fU & vlSelfRef.top__DOT__u_core__DOT__IR)),7);
        bufp->chgCData(oldp+86,((7U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                       >> 0x0000000cU))),3);
        bufp->chgCData(oldp+87,((vlSelfRef.top__DOT__u_core__DOT__IR 
                                 >> 0x00000019U)),7);
        bufp->chgCData(oldp+88,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type),3);
        bufp->chgBit(oldp+89,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal));
        bufp->chgBit(oldp+90,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jalr));
        bufp->chgBit(oldp+91,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne));
        bufp->chgBit(oldp+92,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq));
        bufp->chgBit(oldp+93,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge));
        bufp->chgBit(oldp+94,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu));
        bufp->chgBit(oldp+95,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt));
        bufp->chgBit(oldp+96,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu));
        bufp->chgBit(oldp+97,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lui));
        bufp->chgBit(oldp+98,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lbu));
        bufp->chgBit(oldp+99,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw));
        bufp->chgBit(oldp+100,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lb));
        bufp->chgBit(oldp+101,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh));
        bufp->chgBit(oldp+102,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lhu));
        bufp->chgBit(oldp+103,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ebreak));
        bufp->chgBit(oldp+104,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrw));
        bufp->chgBit(oldp+105,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ecall));
        bufp->chgBit(oldp+106,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_mret));
        bufp->chgBit(oldp+107,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_fence));
        bufp->chgBit(oldp+108,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sb));
        bufp->chgBit(oldp+109,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sw));
        bufp->chgBit(oldp+110,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh));
        bufp->chgBit(oldp+111,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc));
        bufp->chgBit(oldp+112,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_or));
        bufp->chgBit(oldp+113,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ori));
        bufp->chgBit(oldp+114,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xor));
        bufp->chgBit(oldp+115,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xori));
        bufp->chgBit(oldp+116,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add));
        bufp->chgBit(oldp+117,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_addi));
        bufp->chgBit(oldp+118,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sub));
        bufp->chgBit(oldp+119,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slti));
        bufp->chgBit(oldp+120,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltiu));
        bufp->chgBit(oldp+121,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_and));
        bufp->chgBit(oldp+122,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_andi));
        bufp->chgBit(oldp+123,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sra));
        bufp->chgBit(oldp+124,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srai));
        bufp->chgBit(oldp+125,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srl));
        bufp->chgBit(oldp+126,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sll));
        bufp->chgBit(oldp+127,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slli));
        bufp->chgBit(oldp+128,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srli));
        bufp->chgBit(oldp+129,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu));
        bufp->chgBit(oldp+130,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt));
        bufp->chgBit(oldp+131,((IData)(((0x02000013U 
                                         == (0x0200007fU 
                                             & vlSelfRef.top__DOT__u_core__DOT__IR)) 
                                        & ((1U == (7U 
                                                   & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                      >> 0x0000000cU))) 
                                           | (5U == 
                                              (7U & 
                                               (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                >> 0x0000000cU))))))));
        bufp->chgIData(oldp+132,((((- (IData)((vlSelfRef.top__DOT__u_core__DOT__IR 
                                               >> 0x0000001fU))) 
                                   << 0x0000000cU) 
                                  | (vlSelfRef.top__DOT__u_core__DOT__IR 
                                     >> 0x00000014U))),32);
        bufp->chgIData(oldp+133,((((- (IData)((vlSelfRef.top__DOT__u_core__DOT__IR 
                                               >> 0x0000001fU))) 
                                   << 0x0000000cU) 
                                  | ((0x00000fe0U & 
                                      (vlSelfRef.top__DOT__u_core__DOT__IR 
                                       >> 0x00000014U)) 
                                     | (0x0000001fU 
                                        & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                           >> 7U))))),32);
        bufp->chgIData(oldp+134,((0xfffff000U & vlSelfRef.top__DOT__u_core__DOT__IR)),32);
        bufp->chgIData(oldp+135,((((- (IData)((vlSelfRef.top__DOT__u_core__DOT__IR 
                                               >> 0x0000001fU))) 
                                   << 0x0000000dU) 
                                  | ((((2U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                              >> 0x0000001eU)) 
                                       | (1U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                >> 7U))) 
                                      << 0x0000000bU) 
                                     | ((0x000007e0U 
                                         & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                            >> 0x00000014U)) 
                                        | (0x0000001eU 
                                           & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                              >> 7U)))))),32);
        bufp->chgIData(oldp+136,(((((0x00000ffeU & 
                                     ((- (IData)((vlSelfRef.top__DOT__u_core__DOT__IR 
                                                  >> 0x0000001fU))) 
                                      << 1U)) | (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                 >> 0x0000001fU)) 
                                   << 0x00000014U) 
                                  | ((((0x000001feU 
                                        & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                           >> 0x0000000bU)) 
                                       | (1U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                >> 0x00000014U))) 
                                      << 0x0000000bU) 
                                     | (0x000007feU 
                                        & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                           >> 0x00000014U))))),32);
        bufp->chgCData(oldp+137,((3U & vlSelfRef.top__DOT__u_core__DOT__alu_out)),2);
        bufp->chgCData(oldp+138,((0x000000ffU & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2)),8);
        bufp->chgSData(oldp+139,((0x0000ffffU & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_3)),16);
        bufp->chgCData(oldp+140,(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state),3);
        bufp->chgCData(oldp+141,(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__next_state),3);
        bufp->chgBit(oldp+142,(((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
                                & (IData)(vlSelfRef.top__DOT__u_core__DOT__pmem_sel))));
        bufp->chgBit(oldp+143,(vlSelfRef.top__DOT__u_core__DOT____Vcellinp__u_mem__awvalid));
        bufp->chgBit(oldp+144,(((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
                                & (IData)(vlSelfRef.top__DOT__u_core__DOT__pmem_sel))));
        bufp->chgIData(oldp+145,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_addr_latch),32);
        bufp->chgCData(oldp+146,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__w_mask_latch),4);
        bufp->chgSData(oldp+147,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__cnt),16);
        bufp->chgBit(oldp+148,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__rd_delay));
        bufp->chgBit(oldp+149,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__wr_delay));
        bufp->chgBit(oldp+150,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__busy));
        bufp->chgBit(oldp+151,(((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state)) 
                                & ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11) 
                                   | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh) 
                                      | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_6) 
                                         | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                                               | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_9)))))))));
        bufp->chgIData(oldp+152,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0]),32);
        bufp->chgIData(oldp+153,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[1]),32);
        bufp->chgIData(oldp+154,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[2]),32);
        bufp->chgIData(oldp+155,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[3]),32);
        bufp->chgIData(oldp+156,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[4]),32);
        bufp->chgIData(oldp+157,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[5]),32);
        bufp->chgIData(oldp+158,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[6]),32);
        bufp->chgIData(oldp+159,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[7]),32);
        bufp->chgIData(oldp+160,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[8]),32);
        bufp->chgIData(oldp+161,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[9]),32);
        bufp->chgIData(oldp+162,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[10]),32);
        bufp->chgIData(oldp+163,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[11]),32);
        bufp->chgIData(oldp+164,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[12]),32);
        bufp->chgIData(oldp+165,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[13]),32);
        bufp->chgIData(oldp+166,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[14]),32);
        bufp->chgIData(oldp+167,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[15]),32);
        bufp->chgIData(oldp+168,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[16]),32);
        bufp->chgIData(oldp+169,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[17]),32);
        bufp->chgIData(oldp+170,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[18]),32);
        bufp->chgIData(oldp+171,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[19]),32);
        bufp->chgIData(oldp+172,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[20]),32);
        bufp->chgIData(oldp+173,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[21]),32);
        bufp->chgIData(oldp+174,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[22]),32);
        bufp->chgIData(oldp+175,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[23]),32);
        bufp->chgIData(oldp+176,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[24]),32);
        bufp->chgIData(oldp+177,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[25]),32);
        bufp->chgIData(oldp+178,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[26]),32);
        bufp->chgIData(oldp+179,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[27]),32);
        bufp->chgIData(oldp+180,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[28]),32);
        bufp->chgIData(oldp+181,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[29]),32);
        bufp->chgIData(oldp+182,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[30]),32);
        bufp->chgIData(oldp+183,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[31]),32);
        bufp->chgBit(oldp+184,(vlSelfRef.top__DOT__u_core__DOT____Vcellinp__u_rtc__arvalid));
        bufp->chgQData(oldp+185,(vlSelfRef.top__DOT__u_core__DOT__u_rtc__DOT__now_us),64);
        bufp->chgBit(oldp+187,(((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
                                & (0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                   >> 4U)))));
        bufp->chgBit(oldp+188,(((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
                                & (0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                   >> 4U)))));
        bufp->chgBit(oldp+189,(((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
                                & (0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                   >> 4U)))));
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[2U]))) {
        bufp->chgIData(oldp+190,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read
                                 [0x0aU]),32);
        bufp->chgIData(oldp+191,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0]),32);
        bufp->chgIData(oldp+192,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[1]),32);
        bufp->chgIData(oldp+193,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[2]),32);
        bufp->chgIData(oldp+194,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[3]),32);
        bufp->chgIData(oldp+195,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[4]),32);
        bufp->chgIData(oldp+196,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[5]),32);
        bufp->chgIData(oldp+197,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[6]),32);
        bufp->chgIData(oldp+198,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[7]),32);
        bufp->chgIData(oldp+199,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[8]),32);
        bufp->chgIData(oldp+200,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[9]),32);
        bufp->chgIData(oldp+201,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[10]),32);
        bufp->chgIData(oldp+202,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[11]),32);
        bufp->chgIData(oldp+203,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[12]),32);
        bufp->chgIData(oldp+204,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[13]),32);
        bufp->chgIData(oldp+205,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[14]),32);
        bufp->chgIData(oldp+206,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[15]),32);
        bufp->chgIData(oldp+207,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[16]),32);
        bufp->chgIData(oldp+208,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[17]),32);
        bufp->chgIData(oldp+209,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[18]),32);
        bufp->chgIData(oldp+210,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[19]),32);
        bufp->chgIData(oldp+211,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[20]),32);
        bufp->chgIData(oldp+212,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[21]),32);
        bufp->chgIData(oldp+213,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[22]),32);
        bufp->chgIData(oldp+214,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[23]),32);
        bufp->chgIData(oldp+215,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[24]),32);
        bufp->chgIData(oldp+216,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[25]),32);
        bufp->chgIData(oldp+217,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[26]),32);
        bufp->chgIData(oldp+218,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[27]),32);
        bufp->chgIData(oldp+219,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[28]),32);
        bufp->chgIData(oldp+220,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[29]),32);
        bufp->chgIData(oldp+221,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[30]),32);
        bufp->chgIData(oldp+222,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[31]),32);
        bufp->chgIData(oldp+223,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__i),32);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[3U]))) {
        bufp->chgIData(oldp+224,(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_wdata),32);
        bufp->chgIData(oldp+225,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata),32);
        bufp->chgIData(oldp+226,(vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data),32);
        bufp->chgIData(oldp+227,(vlSelfRef.top__DOT__u_core__DOT__alu_result),32);
    }
    bufp->chgBit(oldp+228,(vlSelfRef.clk));
    bufp->chgBit(oldp+229,(vlSelfRef.rst));
    bufp->chgBit(oldp+230,(vlSelfRef.halt));
    bufp->chgBit(oldp+231,(vlSelfRef.aborted));
    bufp->chgIData(oldp+232,(vlSelfRef.pc),32);
    bufp->chgIData(oldp+233,(vlSelfRef.ir_dbg),32);
    bufp->chgCData(oldp+234,(vlSelfRef.state_dbg),3);
    bufp->chgBit(oldp+235,(vlSelfRef.stall_ifu));
    bufp->chgBit(oldp+236,(vlSelfRef.mmio_dbg));
    bufp->chgIData(oldp+237,(((0U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                               ? ((vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data 
                                   << 0x00000018U) 
                                  | ((0x00ff0000U & 
                                      (vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data 
                                       << 0x00000010U)) 
                                     | ((0x0000ff00U 
                                         & (vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data 
                                            << 8U)) 
                                        | (0x000000ffU 
                                           & vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data))))
                               : ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                                   ? ((vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data 
                                       << 0x00000010U) 
                                      | (0x0000ffffU 
                                         & vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data))
                                   : vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data))),32);
    bufp->chgBit(oldp+238,(((6U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
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
                                             : ((5U 
                                                 == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type)) 
                                                & (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
                                                   < vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)))))))));
    bufp->chgIData(oldp+239,((((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc) 
                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal) 
                                  | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                              | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                                                 | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu))))))))
                               ? vlSelfRef.pc : vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata)),32);
    bufp->chgIData(oldp+240,(((IData)(vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm)
                               ? vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__imm
                               : vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)),32);
    bufp->chgIData(oldp+241,(((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
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
                                               : ((3U 
                                                   == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                                   ? 
                                                  (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
                                                   >= vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                                                   : 
                                                  ((4U 
                                                    == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                                    ? 
                                                   VL_LTS_III(32, vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata, vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                                                    : 
                                                   ((5U 
                                                     == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type)) 
                                                    & (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
                                                       < vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data))))))))
                                   ? vlSelfRef.top__DOT__u_core__DOT__alu_result
                                   : ((2U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
                                       ? vlSelfRef.top__DOT__u_core__DOT__alu_result
                                       : ((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
                                           ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec
                                           : ((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
                                               ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mepc
                                               : ((IData)(4U) 
                                                  + vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg))))))),32);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
}
