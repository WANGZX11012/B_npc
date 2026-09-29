// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Implementation of DPI export functions.
//
#include "VysyxSoCFull.h"
#include "VysyxSoCFull__Syms.h"
#include "verilated_dpi.h"


int VysyxSoCFull::npc_dbg_pc() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VysyxSoCFull___024root::npc_dbg_pc\n"); );
    // Locals
    IData/*31:0*/ npc_dbg_pc__Vfuncrtn__Vcvt;
    npc_dbg_pc__Vfuncrtn__Vcvt = 0;
    // Body
    static int __Vfuncnum = -1;
    if (VL_UNLIKELY(__Vfuncnum == -1)) {
        __Vfuncnum = Verilated::exportFuncNum("npc_dbg_pc");
    }
    const VerilatedScope* const __Vscopep = Verilated::dpiScope();
    VysyxSoCFull__Vcb_npc_dbg_pc_t __Vcb = reinterpret_cast<VysyxSoCFull__Vcb_npc_dbg_pc_t>(VerilatedScope::exportFind(__Vscopep, __Vfuncnum));
    (*__Vcb)((VysyxSoCFull__Syms*)(__Vscopep->symsp()), npc_dbg_pc__Vfuncrtn__Vcvt);
    int npc_dbg_pc__Vfuncrtn;
    npc_dbg_pc__Vfuncrtn = npc_dbg_pc__Vfuncrtn__Vcvt;
    return npc_dbg_pc__Vfuncrtn;
}

int VysyxSoCFull::npc_dbg_inst_pc() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VysyxSoCFull___024root::npc_dbg_inst_pc\n"); );
    // Locals
    IData/*31:0*/ npc_dbg_inst_pc__Vfuncrtn__Vcvt;
    npc_dbg_inst_pc__Vfuncrtn__Vcvt = 0;
    // Body
    static int __Vfuncnum = -1;
    if (VL_UNLIKELY(__Vfuncnum == -1)) {
        __Vfuncnum = Verilated::exportFuncNum("npc_dbg_inst_pc");
    }
    const VerilatedScope* const __Vscopep = Verilated::dpiScope();
    VysyxSoCFull__Vcb_npc_dbg_inst_pc_t __Vcb = reinterpret_cast<VysyxSoCFull__Vcb_npc_dbg_inst_pc_t>(VerilatedScope::exportFind(__Vscopep, __Vfuncnum));
    (*__Vcb)((VysyxSoCFull__Syms*)(__Vscopep->symsp()), npc_dbg_inst_pc__Vfuncrtn__Vcvt);
    int npc_dbg_inst_pc__Vfuncrtn;
    npc_dbg_inst_pc__Vfuncrtn = npc_dbg_inst_pc__Vfuncrtn__Vcvt;
    return npc_dbg_inst_pc__Vfuncrtn;
}

int VysyxSoCFull::npc_dbg_retire() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VysyxSoCFull___024root::npc_dbg_retire\n"); );
    // Locals
    IData/*31:0*/ npc_dbg_retire__Vfuncrtn__Vcvt;
    npc_dbg_retire__Vfuncrtn__Vcvt = 0;
    // Body
    static int __Vfuncnum = -1;
    if (VL_UNLIKELY(__Vfuncnum == -1)) {
        __Vfuncnum = Verilated::exportFuncNum("npc_dbg_retire");
    }
    const VerilatedScope* const __Vscopep = Verilated::dpiScope();
    VysyxSoCFull__Vcb_npc_dbg_retire_t __Vcb = reinterpret_cast<VysyxSoCFull__Vcb_npc_dbg_retire_t>(VerilatedScope::exportFind(__Vscopep, __Vfuncnum));
    (*__Vcb)((VysyxSoCFull__Syms*)(__Vscopep->symsp()), npc_dbg_retire__Vfuncrtn__Vcvt);
    int npc_dbg_retire__Vfuncrtn;
    npc_dbg_retire__Vfuncrtn = npc_dbg_retire__Vfuncrtn__Vcvt;
    return npc_dbg_retire__Vfuncrtn;
}

int VysyxSoCFull::npc_dbg_gpr(int i) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VysyxSoCFull___024root::npc_dbg_gpr\n"); );
    // Locals
    IData/*31:0*/ i__Vcvt;
    i__Vcvt = 0;
    IData/*31:0*/ npc_dbg_gpr__Vfuncrtn__Vcvt;
    npc_dbg_gpr__Vfuncrtn__Vcvt = 0;
    // Body
    static int __Vfuncnum = -1;
    if (VL_UNLIKELY(__Vfuncnum == -1)) {
        __Vfuncnum = Verilated::exportFuncNum("npc_dbg_gpr");
    }
    const VerilatedScope* const __Vscopep = Verilated::dpiScope();
    VysyxSoCFull__Vcb_npc_dbg_gpr_t __Vcb = reinterpret_cast<VysyxSoCFull__Vcb_npc_dbg_gpr_t>(VerilatedScope::exportFind(__Vscopep, __Vfuncnum));
    i__Vcvt = (i);
    (*__Vcb)((VysyxSoCFull__Syms*)(__Vscopep->symsp()), i__Vcvt, npc_dbg_gpr__Vfuncrtn__Vcvt);
    int npc_dbg_gpr__Vfuncrtn;
    npc_dbg_gpr__Vfuncrtn = npc_dbg_gpr__Vfuncrtn__Vcvt;
    return npc_dbg_gpr__Vfuncrtn;
}

int VysyxSoCFull::npc_dbg_inst_retire() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VysyxSoCFull___024root::npc_dbg_inst_retire\n"); );
    // Locals
    IData/*31:0*/ npc_dbg_inst_retire__Vfuncrtn__Vcvt;
    npc_dbg_inst_retire__Vfuncrtn__Vcvt = 0;
    // Body
    static int __Vfuncnum = -1;
    if (VL_UNLIKELY(__Vfuncnum == -1)) {
        __Vfuncnum = Verilated::exportFuncNum("npc_dbg_inst_retire");
    }
    const VerilatedScope* const __Vscopep = Verilated::dpiScope();
    VysyxSoCFull__Vcb_npc_dbg_inst_retire_t __Vcb = reinterpret_cast<VysyxSoCFull__Vcb_npc_dbg_inst_retire_t>(VerilatedScope::exportFind(__Vscopep, __Vfuncnum));
    (*__Vcb)((VysyxSoCFull__Syms*)(__Vscopep->symsp()), npc_dbg_inst_retire__Vfuncrtn__Vcvt);
    int npc_dbg_inst_retire__Vfuncrtn;
    npc_dbg_inst_retire__Vfuncrtn = npc_dbg_inst_retire__Vfuncrtn__Vcvt;
    return npc_dbg_inst_retire__Vfuncrtn;
}
