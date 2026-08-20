// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("$rootio", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+230,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+231,0,"halt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+232,0,"aborted",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+233,0,"pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+234,0,"ir_dbg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+235,0,"state_dbg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+236,0,"stall_ifu",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+237,0,"mmio_dbg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("top", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+230,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+231,0,"halt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+232,0,"aborted",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+233,0,"pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+234,0,"ir_dbg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+235,0,"state_dbg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+236,0,"stall_ifu",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+237,0,"mmio_dbg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("u_core", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+230,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+233,0,"pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+231,0,"halt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+232,0,"aborted",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+234,0,"ir_dbg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+235,0,"state_dbg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+237,0,"mmio_dbg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+3,0,"pc4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+4,0,"inst",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+5,0,"ifu_done",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"ifu_req_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+7,0,"ifu_req_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+5,0,"ifu_handshake_done",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"ifu_resp_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+8,0,"lsu_req_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+9,0,"lsu_req_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+238,0,"lsu_req_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"lsu_req_wmask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+11,0,"lsu_handshake_done",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"lsu_resp_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+11,0,"lsu_done",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+12,0,"mem_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+13,0,"m_req_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"m_req_we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"m_req_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+225,0,"m_req_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+16,0,"m_req_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+17,0,"m_done",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"m_resp_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+15,0,"m_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+15,0,"m_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+225,0,"m_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+4,0,"m_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+18,0,"m_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+19,0,"m_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+20,0,"m_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+21,0,"m_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+22,0,"m_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+23,0,"m_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+24,0,"m_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+25,0,"m_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+26,0,"m_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+16,0,"m_wmask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+243,0,"m_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+27,0,"m_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"m_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+29,0,"lfsr_val",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+30,0,"bus_stall",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+31,0,"rs1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+32,0,"rs2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+33,0,"rd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+34,0,"rd_en",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+35,0,"imm",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+36,0,"alu_op",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+37,0,"alu_src2_imm",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+38,0,"alu_en",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+39,0,"alu_src1_pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+40,0,"wb_sel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+41,0,"npc_sel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+42,0,"mem_re",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+43,0,"mem_we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+44,0,"mem_width",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+45,0,"mem_signed",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+46,0,"branch_type",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+47,0,"idu_invalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+226,0,"r_data1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+227,0,"r_data2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+228,0,"alu_result",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+48,0,"wb_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+239,0,"branch_taken",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+49,0,"csr_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+50,0,"csr_mtvec",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+51,0,"csr_mepc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+52,0,"csr_idx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBit(c+53,0,"csr_wen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+54,0,"csr_s_w",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+55,0,"ctrl_state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+56,0,"ctrl_ir_we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+57,0,"ctrl_pc_we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+57,0,"ctrl_reg_we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"ctrl_fetch_req",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+58,0,"ctrl_mem_req",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+232,0,"ctrl_abort",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+59,0,"IR",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+60,0,"ir_pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+9,0,"alu_out",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+61,0,"rtc_sel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+244,0,"rtc_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+62,0,"rtc_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+63,0,"rtc_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+64,0,"rtc_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+65,0,"uart_sel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+244,0,"uart_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+66,0,"uart_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+245,0,"uart_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+243,0,"uart_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+244,0,"uart_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+244,0,"uart_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"uart_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+243,0,"uart_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+68,0,"dmem_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+69,0,"dmem_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+70,0,"dmem_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+71,0,"dmem_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+72,0,"dmem_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+73,0,"dmem_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+243,0,"dmem_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+243,0,"dmem_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+74,0,"pmem_sel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+75,0,"mmio_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("u_CSRFile", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+246,0,"ADDR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+230,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+53,0,"csr_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+76,0,"ecall_trap",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+231,0,"ebreak_trap",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+77,0,"mret_exec",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+60,0,"ecall_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+226,0,"csr_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+52,0,"csr_idx",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBit(c+54,0,"csr_s_w",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+50,0,"csr_mtvec",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+51,0,"csr_mepc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+49,0,"csr_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+49,0,"csr_read",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+78,0,"mcycle",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+1,0,"mvendroid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+2,0,"marchid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+80,0,"mcause",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+51,0,"mepc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+81,0,"mstatus",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+50,0,"mtvec",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_arb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+230,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"ifu_req_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+7,0,"ifu_req_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+5,0,"ifu_done",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"ifu_resp_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+8,0,"lsu_req_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+43,0,"lsu_req_we",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+9,0,"lsu_req_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+238,0,"lsu_req_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"lsu_req_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+11,0,"lsu_done",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"lsu_resp_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+13,0,"m_req_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"m_req_we",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"m_req_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+225,0,"m_req_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+16,0,"m_req_wstrb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+17,0,"m_done",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"m_resp_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+82,0,"sel_is_ifu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+13,0,"m_valid_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("u_ctrl", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+230,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+42,0,"idu_mem_re",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+43,0,"idu_mem_we",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+47,0,"idu_invalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+5,0,"ifu_done",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+11,0,"lsu_done",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+55,0,"state",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+56,0,"ir_we",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+57,0,"pc_we",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+57,0,"reg_we",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"fetch_req",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+58,0,"mem_req",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+232,0,"aborted",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+247,0,"IDLE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+248,0,"FET",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+249,0,"DEC",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+250,0,"EXE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+251,0,"MEM",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+252,0,"WB",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+253,0,"ERR",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+83,0,"next_state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_exu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+226,0,"rs1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+227,0,"rs2_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+35,0,"imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+38,0,"alu_en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+36,0,"alu_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+37,0,"alu_src2_imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+39,0,"alu_src1_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+233,0,"pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+46,0,"branch_type",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+228,0,"alu_result",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+239,0,"branch_taken",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+240,0,"src1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+241,0,"src2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_idu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+59,0,"inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+31,0,"rs1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+32,0,"rs2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+33,0,"rd",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+84,0,"rs1_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+85,0,"rs2_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+34,0,"rd_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+35,0,"imm",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+36,0,"alu_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+38,0,"alu_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+37,0,"alu_src2_imm",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+39,0,"alu_src1_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+42,0,"mem_re",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+43,0,"mem_we",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+44,0,"mem_width",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+45,0,"mem_signed",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+40,0,"wb_sel",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+41,0,"npc_sel",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+46,0,"branch_type",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+47,0,"invalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+52,0,"csr_idx",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBit(c+53,0,"csr_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+54,0,"csr_s_w",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+247,0,"IMM_I",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+248,0,"IMM_S",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+249,0,"IMM_U",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+250,0,"IMM_B",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+251,0,"IMM_J",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+86,0,"opcode",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+87,0,"funct3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+88,0,"funct7",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+89,0,"imm_type",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+90,0,"is_jal",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+91,0,"is_jalr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+92,0,"is_bne",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+93,0,"is_beq",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+94,0,"is_bge",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+95,0,"is_bgeu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+96,0,"is_blt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+97,0,"is_bltu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+98,0,"is_lui",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+99,0,"is_lbu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+100,0,"is_lw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+101,0,"is_lb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+102,0,"is_lh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+103,0,"is_lhu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+104,0,"is_ebreak",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+54,0,"is_csrrs",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+105,0,"is_csrrw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+106,0,"is_ecall",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+107,0,"is_mret",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+108,0,"is_fence",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+109,0,"is_sb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+110,0,"is_sw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+111,0,"is_sh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+112,0,"is_auipc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+113,0,"is_or",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+114,0,"is_ori",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+115,0,"is_xor",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+116,0,"is_xori",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+117,0,"is_add",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+118,0,"is_addi",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+119,0,"is_sub",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+120,0,"is_slti",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+121,0,"is_sltiu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+122,0,"is_and",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+123,0,"is_andi",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+124,0,"is_sra",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+125,0,"is_srai",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+126,0,"is_srl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+127,0,"is_sll",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+128,0,"is_slli",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+129,0,"is_srli",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+130,0,"is_sltu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+131,0,"is_slt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+132,0,"illegal_shift_imm",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+133,0,"imm_i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+134,0,"imm_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+135,0,"imm_u",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+136,0,"imm_b",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+137,0,"imm_j",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_ifu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+230,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+57,0,"pc_we",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"fetch_req",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+228,0,"alu_result",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+41,0,"npc_sel",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+239,0,"branch_taken",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+50,0,"csr_mtvec",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+51,0,"csr_mepc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+6,0,"req_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+7,0,"req_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+5,0,"handshake_done",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"resp_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+233,0,"pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+3,0,"pc4",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+4,0,"inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+5,0,"ifu_done",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+7,0,"pc_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+242,0,"next_pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_lfsr", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+254,0,"SEED",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+230,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+244,0,"en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+29,0,"val",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+29,0,"state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_lsu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+230,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+58,0,"mem_req",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+42,0,"mem_re",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+43,0,"mem_we",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+44,0,"mem_width",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+45,0,"mem_signed",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+8,0,"req_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+9,0,"req_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+227,0,"wdata_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+4,0,"rdata_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+9,0,"addr_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+11,0,"handshake_done",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+238,0,"req_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"req_wmask",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+11,0,"lsu_done",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+12,0,"rdata_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+138,0,"off",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+10,0,"wmask_gen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+238,0,"wdata_gen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+139,0,"lb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+140,0,"lh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_master", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+230,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+13,0,"req_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"req_we",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"req_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+225,0,"req_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+16,0,"req_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+30,0,"stall",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+17,0,"done",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"resp_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+15,0,"araddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+18,0,"arvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+19,0,"arready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+20,0,"rvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+22,0,"rresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+21,0,"rready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"awaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+23,0,"awvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+24,0,"awready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+225,0,"wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+25,0,"wvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+16,0,"wmask",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+26,0,"wready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+243,0,"bresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+27,0,"bvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"bready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+247,0,"IDLE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+248,0,"AR",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+249,0,"R",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+250,0,"AW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+251,0,"W",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+252,0,"B",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+141,0,"state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+142,0,"next_state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_mem", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+255,0,"DELAY",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+143,0,"arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+68,0,"arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+73,0,"rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+243,0,"rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+69,0,"rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+21,0,"rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+144,0,"awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+70,0,"awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+225,0,"wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+16,0,"wmask",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+145,0,"wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+71,0,"wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+243,0,"bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+72,0,"bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+71,0,"aw_recv",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+146,0,"aw_addr_latch",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+147,0,"w_mask_latch",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+148,0,"cnt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+149,0,"rd_delay",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+150,0,"wr_delay",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+151,0,"busy",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("u_regfile", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+256,0,"ADDR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+257,0,"DATA_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+48,0,"w_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+33,0,"w_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+31,0,"r_addr1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+32,0,"r_addr2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+152,0,"wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+226,0,"r_data1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+227,0,"r_data2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+191,0,"r_a0",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("rf", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+153+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("rf_read", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+192+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+224,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_rtc", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+185,0,"arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+244,0,"arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+63,0,"rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+64,0,"rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+62,0,"rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+21,0,"rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+186,0,"now_us",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_uart", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+229,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+188,0,"arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+244,0,"arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+245,0,"rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+243,0,"rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+66,0,"rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+21,0,"rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+189,0,"awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+244,0,"awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+225,0,"wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+16,0,"wmask",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+190,0,"wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+244,0,"wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+243,0,"bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+67,0,"bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("u_wbu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+3,0,"pc4",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+9,0,"alu_result",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+12,0,"mem_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+49,0,"csr_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+35,0,"imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+40,0,"wb_sel",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+48,0,"wb_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vtop___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vtop___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_const_0\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtop___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_const_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullCData(oldp+243,(0U),2);
    bufp->fullBit(oldp+244,(1U));
    bufp->fullIData(oldp+245,(0U),32);
    bufp->fullIData(oldp+246,(0x0000000cU),32);
    bufp->fullCData(oldp+247,(0U),3);
    bufp->fullCData(oldp+248,(1U),3);
    bufp->fullCData(oldp+249,(2U),3);
    bufp->fullCData(oldp+250,(3U),3);
    bufp->fullCData(oldp+251,(4U),3);
    bufp->fullCData(oldp+252,(5U),3);
    bufp->fullCData(oldp+253,(6U),3);
    bufp->fullCData(oldp+254,(0x5aU),8);
    bufp->fullIData(oldp+255,(1U),32);
    bufp->fullIData(oldp+256,(5U),32);
    bufp->fullIData(oldp+257,(0x00000020U),32);
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vtop___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+1,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mvendroid),32);
    bufp->fullIData(oldp+2,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__marchid),32);
    bufp->fullIData(oldp+3,(((IData)(4U) + vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg)),32);
    bufp->fullIData(oldp+4,(vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__resp_rdata),32);
    bufp->fullBit(oldp+5,(vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__handshake_done));
    bufp->fullBit(oldp+6,((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state))));
    bufp->fullIData(oldp+7,(vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg),32);
    bufp->fullBit(oldp+8,(((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state)) 
                           & ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_re) 
                              | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_we)))));
    bufp->fullIData(oldp+9,(vlSelfRef.top__DOT__u_core__DOT__alu_out),32);
    bufp->fullCData(oldp+10,((0x0000000fU & ((0U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
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
                                                  : 0x0fU)))),4);
    bufp->fullBit(oldp+11,(((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)) 
                            & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_done))));
    bufp->fullIData(oldp+12,(((0U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                               ? ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_signed)
                                   ? (((- (IData)((1U 
                                                   & (vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2 
                                                      >> 7U)))) 
                                       << 8U) | (0x000000ffU 
                                                 & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2))
                                   : (0x000000ffU & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2))
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
    bufp->fullBit(oldp+13,(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_valid_r));
    bufp->fullBit(oldp+14,(((~ (IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)) 
                            & (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_we))));
    bufp->fullIData(oldp+15,(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr),32);
    bufp->fullCData(oldp+16,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu)
                               ? 0U : (0x0000000fU 
                                       & ((0U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                                           ? ((IData)(1U) 
                                              << (3U 
                                                  & vlSelfRef.top__DOT__u_core__DOT__alu_out))
                                           : ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                                               ? ((2U 
                                                   & vlSelfRef.top__DOT__u_core__DOT__alu_out)
                                                   ? 0x0cU
                                                   : 3U)
                                               : 0x0fU))))),4);
    bufp->fullBit(oldp+17,(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_done));
    bufp->fullBit(oldp+18,((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state))));
    bufp->fullBit(oldp+19,(((0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                             >> 4U)) 
                            || ((0x00a00000U == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                 >> 8U)) 
                                || (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_arready)))));
    bufp->fullBit(oldp+20,(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rvalid));
    bufp->fullBit(oldp+21,(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__rready));
    bufp->fullCData(oldp+22,(((0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                               >> 4U))
                               ? 0U : ((0x00a00000U 
                                        == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                            >> 8U))
                                        ? (IData)(vlSelfRef.top__DOT__u_core__DOT__rtc_rresp)
                                        : 0U))),2);
    bufp->fullBit(oldp+23,((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state))));
    bufp->fullBit(oldp+24,(((0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                             >> 4U)) 
                            || (IData)(vlSelfRef.top__DOT__u_core__DOT__dmem_awready))));
    bufp->fullBit(oldp+25,((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state))));
    bufp->fullBit(oldp+26,(((0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                             >> 4U)) 
                            || (IData)(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv))));
    bufp->fullBit(oldp+27,(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__bvalid));
    bufp->fullBit(oldp+28,(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__bready));
    bufp->fullCData(oldp+29,(vlSelfRef.top__DOT__u_core__DOT__u_lfsr__DOT__state),8);
    bufp->fullBit(oldp+30,((0x10U > (IData)(vlSelfRef.top__DOT__u_core__DOT__u_lfsr__DOT__state))));
    bufp->fullCData(oldp+31,((0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                             >> 0x0000000fU))),5);
    bufp->fullCData(oldp+32,((0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                             >> 0x00000014U))),5);
    bufp->fullCData(oldp+33,((0x0000001fU & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                             >> 7U))),5);
    bufp->fullBit(oldp+34,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11) 
                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh) 
                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_6) 
                                  | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                                        | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_9))))))));
    bufp->fullIData(oldp+35,(vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__imm),32);
    bufp->fullCData(oldp+36,(vlSelfRef.top__DOT__u_core__DOT__alu_op),4);
    bufp->fullBit(oldp+37,(vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm));
    bufp->fullBit(oldp+38,(vlSelfRef.top__DOT__u_core__DOT__alu_en));
    bufp->fullBit(oldp+39,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc) 
                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal) 
                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                  | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                     | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                        | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                           | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                                              | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu))))))))));
    bufp->fullCData(oldp+40,((((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add) 
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
                                                 ? 2U
                                                 : 
                                                ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lui)
                                                  ? 3U
                                                  : 
                                                 ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_4)
                                                   ? 4U
                                                   : 0U)))))),3);
    bufp->fullCData(oldp+41,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel),3);
    bufp->fullBit(oldp+42,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_re));
    bufp->fullBit(oldp+43,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_we));
    bufp->fullCData(oldp+44,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width),2);
    bufp->fullBit(oldp+45,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_signed));
    bufp->fullCData(oldp+46,(vlSelfRef.top__DOT__u_core__DOT__branch_type),3);
    bufp->fullBit(oldp+47,((1U & ((~ ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11) 
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
                                              == (0x0200007fU 
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
    bufp->fullIData(oldp+48,(vlSelfRef.top__DOT__u_core__DOT__wb_data),32);
    bufp->fullIData(oldp+49,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_data),32);
    bufp->fullIData(oldp+50,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mtvec),32);
    bufp->fullIData(oldp+51,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mepc),32);
    bufp->fullSData(oldp+52,((vlSelfRef.top__DOT__u_core__DOT__IR 
                              >> 0x00000014U)),12);
    bufp->fullBit(oldp+53,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wen));
    bufp->fullBit(oldp+54,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrs));
    bufp->fullCData(oldp+55,(vlSelfRef.top__DOT__u_core__DOT__ctrl_state),3);
    bufp->fullBit(oldp+56,(vlSelfRef.top__DOT__u_core__DOT__ctrl_ir_we));
    bufp->fullBit(oldp+57,((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state))));
    bufp->fullBit(oldp+58,((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state))));
    bufp->fullIData(oldp+59,(vlSelfRef.top__DOT__u_core__DOT__IR),32);
    bufp->fullIData(oldp+60,(vlSelfRef.top__DOT__u_core__DOT__ir_pc),32);
    bufp->fullBit(oldp+61,((0x00a00000U == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                            >> 8U))));
    bufp->fullBit(oldp+62,(vlSelfRef.top__DOT__u_core__DOT__rtc_rvalid));
    bufp->fullIData(oldp+63,(vlSelfRef.top__DOT__u_core__DOT__rtc_rdata),32);
    bufp->fullCData(oldp+64,(vlSelfRef.top__DOT__u_core__DOT__rtc_rresp),2);
    bufp->fullBit(oldp+65,((0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                            >> 4U))));
    bufp->fullBit(oldp+66,(vlSelfRef.top__DOT__u_core__DOT__uart_rvalid));
    bufp->fullBit(oldp+67,(vlSelfRef.top__DOT__u_core__DOT__uart_bvalid));
    bufp->fullBit(oldp+68,(vlSelfRef.top__DOT__u_core__DOT__dmem_arready));
    bufp->fullBit(oldp+69,(vlSelfRef.top__DOT__u_core__DOT__dmem_rvalid));
    bufp->fullBit(oldp+70,(vlSelfRef.top__DOT__u_core__DOT__dmem_awready));
    bufp->fullBit(oldp+71,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_recv));
    bufp->fullBit(oldp+72,(vlSelfRef.top__DOT__u_core__DOT__dmem_bvalid));
    bufp->fullIData(oldp+73,(vlSelfRef.top__DOT__u_core__DOT__dmem_rdata),32);
    bufp->fullBit(oldp+74,(vlSelfRef.top__DOT__u_core__DOT__pmem_sel));
    bufp->fullBit(oldp+75,(vlSelfRef.top__DOT__u_core__DOT__mmio_flag));
    bufp->fullBit(oldp+76,((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))));
    bufp->fullBit(oldp+77,((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))));
    bufp->fullQData(oldp+78,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcycle),64);
    bufp->fullIData(oldp+80,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mcause),32);
    bufp->fullIData(oldp+81,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mstatus),32);
    bufp->fullBit(oldp+82,(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__sel_is_ifu));
    bufp->fullCData(oldp+83,(vlSelfRef.top__DOT__u_core__DOT__u_ctrl__DOT__next_state),3);
    bufp->fullBit(oldp+84,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_addi) 
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
    bufp->fullBit(oldp+85,(((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add) 
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
    bufp->fullCData(oldp+86,((0x0000007fU & vlSelfRef.top__DOT__u_core__DOT__IR)),7);
    bufp->fullCData(oldp+87,((7U & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                    >> 0x0000000cU))),3);
    bufp->fullCData(oldp+88,((vlSelfRef.top__DOT__u_core__DOT__IR 
                              >> 0x00000019U)),7);
    bufp->fullCData(oldp+89,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__imm_type),3);
    bufp->fullBit(oldp+90,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal));
    bufp->fullBit(oldp+91,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jalr));
    bufp->fullBit(oldp+92,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne));
    bufp->fullBit(oldp+93,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq));
    bufp->fullBit(oldp+94,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge));
    bufp->fullBit(oldp+95,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu));
    bufp->fullBit(oldp+96,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt));
    bufp->fullBit(oldp+97,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu));
    bufp->fullBit(oldp+98,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lui));
    bufp->fullBit(oldp+99,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lbu));
    bufp->fullBit(oldp+100,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lw));
    bufp->fullBit(oldp+101,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lb));
    bufp->fullBit(oldp+102,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh));
    bufp->fullBit(oldp+103,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lhu));
    bufp->fullBit(oldp+104,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ebreak));
    bufp->fullBit(oldp+105,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_csrrw));
    bufp->fullBit(oldp+106,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ecall));
    bufp->fullBit(oldp+107,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_mret));
    bufp->fullBit(oldp+108,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_fence));
    bufp->fullBit(oldp+109,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sb));
    bufp->fullBit(oldp+110,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sw));
    bufp->fullBit(oldp+111,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sh));
    bufp->fullBit(oldp+112,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc));
    bufp->fullBit(oldp+113,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_or));
    bufp->fullBit(oldp+114,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_ori));
    bufp->fullBit(oldp+115,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xor));
    bufp->fullBit(oldp+116,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_xori));
    bufp->fullBit(oldp+117,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_add));
    bufp->fullBit(oldp+118,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_addi));
    bufp->fullBit(oldp+119,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sub));
    bufp->fullBit(oldp+120,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slti));
    bufp->fullBit(oldp+121,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltiu));
    bufp->fullBit(oldp+122,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_and));
    bufp->fullBit(oldp+123,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_andi));
    bufp->fullBit(oldp+124,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sra));
    bufp->fullBit(oldp+125,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srai));
    bufp->fullBit(oldp+126,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srl));
    bufp->fullBit(oldp+127,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sll));
    bufp->fullBit(oldp+128,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slli));
    bufp->fullBit(oldp+129,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_srli));
    bufp->fullBit(oldp+130,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu));
    bufp->fullBit(oldp+131,(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt));
    bufp->fullBit(oldp+132,((IData)(((0x02000013U == 
                                      (0x0200007fU 
                                       & vlSelfRef.top__DOT__u_core__DOT__IR)) 
                                     & ((1U == (7U 
                                                & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                   >> 0x0000000cU))) 
                                        | (5U == (7U 
                                                  & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                     >> 0x0000000cU))))))));
    bufp->fullIData(oldp+133,((((- (IData)((vlSelfRef.top__DOT__u_core__DOT__IR 
                                            >> 0x0000001fU))) 
                                << 0x0000000cU) | (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                   >> 0x00000014U))),32);
    bufp->fullIData(oldp+134,((((- (IData)((vlSelfRef.top__DOT__u_core__DOT__IR 
                                            >> 0x0000001fU))) 
                                << 0x0000000cU) | (
                                                   (0x00000fe0U 
                                                    & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                       >> 0x00000014U)) 
                                                   | (0x0000001fU 
                                                      & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                         >> 7U))))),32);
    bufp->fullIData(oldp+135,((0xfffff000U & vlSelfRef.top__DOT__u_core__DOT__IR)),32);
    bufp->fullIData(oldp+136,((((- (IData)((vlSelfRef.top__DOT__u_core__DOT__IR 
                                            >> 0x0000001fU))) 
                                << 0x0000000dU) | (
                                                   (((2U 
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
                                                            >> 7U)))))),32);
    bufp->fullIData(oldp+137,(((((0x00000ffeU & ((- (IData)(
                                                            (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                             >> 0x0000001fU))) 
                                                 << 1U)) 
                                 | (vlSelfRef.top__DOT__u_core__DOT__IR 
                                    >> 0x0000001fU)) 
                                << 0x00000014U) | (
                                                   (((0x000001feU 
                                                      & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                         >> 0x0000000bU)) 
                                                     | (1U 
                                                        & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                           >> 0x00000014U))) 
                                                    << 0x0000000bU) 
                                                   | (0x000007feU 
                                                      & (vlSelfRef.top__DOT__u_core__DOT__IR 
                                                         >> 0x00000014U))))),32);
    bufp->fullCData(oldp+138,((3U & vlSelfRef.top__DOT__u_core__DOT__alu_out)),2);
    bufp->fullCData(oldp+139,((0x000000ffU & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_2)),8);
    bufp->fullSData(oldp+140,((0x0000ffffU & vlSelfRef.top__DOT__u_core__DOT__u_lsu__DOT____VdfgRegularize_hac146698_0_3)),16);
    bufp->fullCData(oldp+141,(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state),3);
    bufp->fullCData(oldp+142,(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__next_state),3);
    bufp->fullBit(oldp+143,(((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
                             & (IData)(vlSelfRef.top__DOT__u_core__DOT__pmem_sel))));
    bufp->fullBit(oldp+144,(vlSelfRef.top__DOT__u_core__DOT____Vcellinp__u_mem__awvalid));
    bufp->fullBit(oldp+145,(((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
                             & (IData)(vlSelfRef.top__DOT__u_core__DOT__pmem_sel))));
    bufp->fullIData(oldp+146,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__aw_addr_latch),32);
    bufp->fullCData(oldp+147,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__w_mask_latch),4);
    bufp->fullSData(oldp+148,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__cnt),16);
    bufp->fullBit(oldp+149,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__rd_delay));
    bufp->fullBit(oldp+150,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__wr_delay));
    bufp->fullBit(oldp+151,(vlSelfRef.top__DOT__u_core__DOT__u_mem__DOT__busy));
    bufp->fullBit(oldp+152,(((5U == (IData)(vlSelfRef.top__DOT__u_core__DOT__ctrl_state)) 
                             & ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_11) 
                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_lh) 
                                   | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_6) 
                                      | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_slt) 
                                         | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_sltu) 
                                            | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT____VdfgRegularize_h52656aab_0_9)))))))));
    bufp->fullIData(oldp+153,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[0]),32);
    bufp->fullIData(oldp+154,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[1]),32);
    bufp->fullIData(oldp+155,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[2]),32);
    bufp->fullIData(oldp+156,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[3]),32);
    bufp->fullIData(oldp+157,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[4]),32);
    bufp->fullIData(oldp+158,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[5]),32);
    bufp->fullIData(oldp+159,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[6]),32);
    bufp->fullIData(oldp+160,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[7]),32);
    bufp->fullIData(oldp+161,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[8]),32);
    bufp->fullIData(oldp+162,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[9]),32);
    bufp->fullIData(oldp+163,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[10]),32);
    bufp->fullIData(oldp+164,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[11]),32);
    bufp->fullIData(oldp+165,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[12]),32);
    bufp->fullIData(oldp+166,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[13]),32);
    bufp->fullIData(oldp+167,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[14]),32);
    bufp->fullIData(oldp+168,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[15]),32);
    bufp->fullIData(oldp+169,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[16]),32);
    bufp->fullIData(oldp+170,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[17]),32);
    bufp->fullIData(oldp+171,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[18]),32);
    bufp->fullIData(oldp+172,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[19]),32);
    bufp->fullIData(oldp+173,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[20]),32);
    bufp->fullIData(oldp+174,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[21]),32);
    bufp->fullIData(oldp+175,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[22]),32);
    bufp->fullIData(oldp+176,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[23]),32);
    bufp->fullIData(oldp+177,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[24]),32);
    bufp->fullIData(oldp+178,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[25]),32);
    bufp->fullIData(oldp+179,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[26]),32);
    bufp->fullIData(oldp+180,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[27]),32);
    bufp->fullIData(oldp+181,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[28]),32);
    bufp->fullIData(oldp+182,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[29]),32);
    bufp->fullIData(oldp+183,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[30]),32);
    bufp->fullIData(oldp+184,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf[31]),32);
    bufp->fullBit(oldp+185,(vlSelfRef.top__DOT__u_core__DOT____Vcellinp__u_rtc__arvalid));
    bufp->fullQData(oldp+186,(vlSelfRef.top__DOT__u_core__DOT__u_rtc__DOT__now_us),64);
    bufp->fullBit(oldp+188,(((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
                             & (0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                >> 4U)))));
    bufp->fullBit(oldp+189,(((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
                             & (0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                >> 4U)))));
    bufp->fullBit(oldp+190,(((4U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_master__DOT__state)) 
                             & (0x0a00003fU == (vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_addr 
                                                >> 4U)))));
    bufp->fullIData(oldp+191,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read
                              [0x0aU]),32);
    bufp->fullIData(oldp+192,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[0]),32);
    bufp->fullIData(oldp+193,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[1]),32);
    bufp->fullIData(oldp+194,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[2]),32);
    bufp->fullIData(oldp+195,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[3]),32);
    bufp->fullIData(oldp+196,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[4]),32);
    bufp->fullIData(oldp+197,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[5]),32);
    bufp->fullIData(oldp+198,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[6]),32);
    bufp->fullIData(oldp+199,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[7]),32);
    bufp->fullIData(oldp+200,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[8]),32);
    bufp->fullIData(oldp+201,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[9]),32);
    bufp->fullIData(oldp+202,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[10]),32);
    bufp->fullIData(oldp+203,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[11]),32);
    bufp->fullIData(oldp+204,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[12]),32);
    bufp->fullIData(oldp+205,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[13]),32);
    bufp->fullIData(oldp+206,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[14]),32);
    bufp->fullIData(oldp+207,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[15]),32);
    bufp->fullIData(oldp+208,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[16]),32);
    bufp->fullIData(oldp+209,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[17]),32);
    bufp->fullIData(oldp+210,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[18]),32);
    bufp->fullIData(oldp+211,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[19]),32);
    bufp->fullIData(oldp+212,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[20]),32);
    bufp->fullIData(oldp+213,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[21]),32);
    bufp->fullIData(oldp+214,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[22]),32);
    bufp->fullIData(oldp+215,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[23]),32);
    bufp->fullIData(oldp+216,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[24]),32);
    bufp->fullIData(oldp+217,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[25]),32);
    bufp->fullIData(oldp+218,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[26]),32);
    bufp->fullIData(oldp+219,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[27]),32);
    bufp->fullIData(oldp+220,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[28]),32);
    bufp->fullIData(oldp+221,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[29]),32);
    bufp->fullIData(oldp+222,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[30]),32);
    bufp->fullIData(oldp+223,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__rf_read[31]),32);
    bufp->fullIData(oldp+224,(vlSelfRef.top__DOT__u_core__DOT__u_regfile__DOT__i),32);
    bufp->fullIData(oldp+225,(vlSelfRef.top__DOT__u_core__DOT__u_arb__DOT__m_req_wdata),32);
    bufp->fullIData(oldp+226,(vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata),32);
    bufp->fullIData(oldp+227,(vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data),32);
    bufp->fullIData(oldp+228,(vlSelfRef.top__DOT__u_core__DOT__alu_result),32);
    bufp->fullBit(oldp+229,(vlSelfRef.clk));
    bufp->fullBit(oldp+230,(vlSelfRef.rst));
    bufp->fullBit(oldp+231,(vlSelfRef.halt));
    bufp->fullBit(oldp+232,(vlSelfRef.aborted));
    bufp->fullIData(oldp+233,(vlSelfRef.pc),32);
    bufp->fullIData(oldp+234,(vlSelfRef.ir_dbg),32);
    bufp->fullCData(oldp+235,(vlSelfRef.state_dbg),3);
    bufp->fullBit(oldp+236,(vlSelfRef.stall_ifu));
    bufp->fullBit(oldp+237,(vlSelfRef.mmio_dbg));
    bufp->fullIData(oldp+238,(((0U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__mem_width))
                                ? ((vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data 
                                    << 0x00000018U) 
                                   | ((0x00ff0000U 
                                       & (vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data 
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
    bufp->fullBit(oldp+239,(((6U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
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
    bufp->fullIData(oldp+240,((((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_auipc) 
                                | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_jal) 
                                   | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bge) 
                                      | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bne) 
                                         | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bgeu) 
                                            | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_blt) 
                                               | ((IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_beq) 
                                                  | (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__is_bltu))))))))
                                ? vlSelfRef.pc : vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata)),32);
    bufp->fullIData(oldp+241,(((IData)(vlSelfRef.top__DOT__u_core__DOT__alu_src2_imm)
                                ? vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__imm
                                : vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)),32);
    bufp->fullIData(oldp+242,(((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
                                ? (0xfffffffeU & vlSelfRef.top__DOT__u_core__DOT__alu_result)
                                : (((3U == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel)) 
                                    & ((6U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                        ? (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
                                           == vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                                        : ((1U == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                            ? (vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata 
                                               != vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                                            : ((2U 
                                                == (IData)(vlSelfRef.top__DOT__u_core__DOT__branch_type))
                                                ? VL_GTES_III(32, vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__csr_wdata, vlSelfRef.top__DOT__u_core__DOT__u_exu__DOT__rs2_data)
                                                : (
                                                   (3U 
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
                                            : ((5U 
                                                == (IData)(vlSelfRef.top__DOT__u_core__DOT__u_idu__DOT__npc_sel))
                                                ? vlSelfRef.top__DOT__u_core__DOT__u_CSRFile__DOT__mepc
                                                : ((IData)(4U) 
                                                   + vlSelfRef.top__DOT__u_core__DOT__u_ifu__DOT__pc_reg))))))),32);
}
