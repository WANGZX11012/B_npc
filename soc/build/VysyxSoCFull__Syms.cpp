// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "VysyxSoCFull__pch.h"
#include "VysyxSoCFull.h"
#include "VysyxSoCFull___024root.h"
#include "VysyxSoCFull___024unit.h"

void VysyxSoCFull___024root____Vdpiexp_ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__u_core__DOT__npc_dbg_gpr_TOP(VysyxSoCFull__Syms* __restrict vlSymsp, IData/*31:0*/ i, IData/*31:0*/ &npc_dbg_gpr__Vfuncrtn);
void VysyxSoCFull___024root____Vdpiexp_ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__u_core__DOT__npc_dbg_inst_pc_TOP(VysyxSoCFull__Syms* __restrict vlSymsp, IData/*31:0*/ &npc_dbg_inst_pc__Vfuncrtn);
void VysyxSoCFull___024root____Vdpiexp_ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__u_core__DOT__npc_dbg_inst_retire_TOP(VysyxSoCFull__Syms* __restrict vlSymsp, IData/*31:0*/ &npc_dbg_inst_retire__Vfuncrtn);
void VysyxSoCFull___024root____Vdpiexp_ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__u_core__DOT__npc_dbg_pc_TOP(VysyxSoCFull__Syms* __restrict vlSymsp, IData/*31:0*/ &npc_dbg_pc__Vfuncrtn);
void VysyxSoCFull___024root____Vdpiexp_ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__u_core__DOT__npc_dbg_retire_TOP(VysyxSoCFull__Syms* __restrict vlSymsp, IData/*31:0*/ &npc_dbg_retire__Vfuncrtn);

// FUNCTIONS
VysyxSoCFull__Syms::~VysyxSoCFull__Syms()
{
}

VysyxSoCFull__Syms::VysyxSoCFull__Syms(VerilatedContext* contextp, const char* namep, VysyxSoCFull* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
    , TOP____024unit{this, Verilated::catName(namep, "$unit")}
{
    // Check resources
    Verilated::stackCheck(966);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    TOP.__PVT____024unit = &TOP____024unit;
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    TOP____024unit.__Vconfigure(true);
    // Setup scopes
    __Vscope_ysyxSoCFull__asic__axi42apb.configure(this, name(), "ysyxSoCFull.asic.axi42apb", "axi42apb", "<null>", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_ysyxSoCFull__asic__axi4frag.configure(this, name(), "ysyxSoCFull.asic.axi4frag", "axi4frag", "<null>", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_ysyxSoCFull__asic__axi4xbar_1.configure(this, name(), "ysyxSoCFull.asic.axi4xbar_1", "axi4xbar_1", "<null>", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_ysyxSoCFull__asic__axi4yank.configure(this, name(), "ysyxSoCFull.asic.axi4yank", "axi4yank", "<null>", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_ysyxSoCFull__asic__axi4yank__unnamedblk1.configure(this, name(), "ysyxSoCFull.asic.axi4yank.unnamedblk1", "unnamedblk1", "<null>", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_ysyxSoCFull__asic__cpu__cpu__u_core.configure(this, name(), "ysyxSoCFull.asic.cpu.cpu.u_core", "u_core", "<null>", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_ysyxSoCFull__asic__lmrom.configure(this, name(), "ysyxSoCFull.asic.lmrom", "lmrom", "<null>", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_ysyxSoCFull__flash.configure(this, name(), "ysyxSoCFull.flash", "flash", "<null>", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_ysyxSoCFull__flash__flash_cmd_i.configure(this, name(), "ysyxSoCFull.flash.flash_cmd_i", "flash_cmd_i", "<null>", -9, VerilatedScope::SCOPE_OTHER);
    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
        __Vscope_ysyxSoCFull__asic__cpu__cpu__u_core.exportInsert(__Vfinal, "npc_dbg_gpr", (void*)(&VysyxSoCFull___024root____Vdpiexp_ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__u_core__DOT__npc_dbg_gpr_TOP));
        __Vscope_ysyxSoCFull__asic__cpu__cpu__u_core.exportInsert(__Vfinal, "npc_dbg_inst_pc", (void*)(&VysyxSoCFull___024root____Vdpiexp_ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__u_core__DOT__npc_dbg_inst_pc_TOP));
        __Vscope_ysyxSoCFull__asic__cpu__cpu__u_core.exportInsert(__Vfinal, "npc_dbg_inst_retire", (void*)(&VysyxSoCFull___024root____Vdpiexp_ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__u_core__DOT__npc_dbg_inst_retire_TOP));
        __Vscope_ysyxSoCFull__asic__cpu__cpu__u_core.exportInsert(__Vfinal, "npc_dbg_pc", (void*)(&VysyxSoCFull___024root____Vdpiexp_ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__u_core__DOT__npc_dbg_pc_TOP));
        __Vscope_ysyxSoCFull__asic__cpu__cpu__u_core.exportInsert(__Vfinal, "npc_dbg_retire", (void*)(&VysyxSoCFull___024root____Vdpiexp_ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__u_core__DOT__npc_dbg_retire_TOP));
    }
}
