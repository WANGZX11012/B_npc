// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtop__pch.h"
#include "Vtop.h"
#include "Vtop___024root.h"
#include "Vtop___024unit.h"

void Vtop___024root____Vdpiexp_top__DOT__u_core__DOT__npc_dbg_gpr_TOP(Vtop__Syms* __restrict vlSymsp, IData/*31:0*/ i, IData/*31:0*/ &npc_dbg_gpr__Vfuncrtn);
void Vtop___024root____Vdpiexp_top__DOT__u_core__DOT__npc_dbg_inst_pc_TOP(Vtop__Syms* __restrict vlSymsp, IData/*31:0*/ &npc_dbg_inst_pc__Vfuncrtn);
void Vtop___024root____Vdpiexp_top__DOT__u_core__DOT__npc_dbg_pc_TOP(Vtop__Syms* __restrict vlSymsp, IData/*31:0*/ &npc_dbg_pc__Vfuncrtn);
void Vtop___024root____Vdpiexp_top__DOT__u_core__DOT__npc_dbg_retire_TOP(Vtop__Syms* __restrict vlSymsp, IData/*31:0*/ &npc_dbg_retire__Vfuncrtn);

// FUNCTIONS
Vtop__Syms::~Vtop__Syms()
{
}

Vtop__Syms::Vtop__Syms(VerilatedContext* contextp, const char* namep, Vtop* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
    , TOP____024unit{this, Verilated::catName(namep, "$unit")}
{
    // Check resources
    Verilated::stackCheck(528);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    TOP.__PVT____024unit = &TOP____024unit;
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    TOP____024unit.__Vconfigure(true);
    // Setup scopes
    __Vscope_top__u_core.configure(this, name(), "top.u_core", "u_core", "<null>", -12, VerilatedScope::SCOPE_OTHER);
    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
        __Vscope_top__u_core.exportInsert(__Vfinal, "npc_dbg_gpr", (void*)(&Vtop___024root____Vdpiexp_top__DOT__u_core__DOT__npc_dbg_gpr_TOP));
        __Vscope_top__u_core.exportInsert(__Vfinal, "npc_dbg_inst_pc", (void*)(&Vtop___024root____Vdpiexp_top__DOT__u_core__DOT__npc_dbg_inst_pc_TOP));
        __Vscope_top__u_core.exportInsert(__Vfinal, "npc_dbg_pc", (void*)(&Vtop___024root____Vdpiexp_top__DOT__u_core__DOT__npc_dbg_pc_TOP));
        __Vscope_top__u_core.exportInsert(__Vfinal, "npc_dbg_retire", (void*)(&Vtop___024root____Vdpiexp_top__DOT__u_core__DOT__npc_dbg_retire_TOP));
    }
}
