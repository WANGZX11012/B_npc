// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Implementation of DPI export functions.
//
// Verilator compiles this file in when DPI functions are used.
// If you have multiple Verilated designs with the same DPI exported
// function names, you will get multiple definition link errors from here.
// This is an unfortunate result of the DPI specification.
// To solve this, either
//    1. Call VysyxSoCFull::{export_function} instead,
//       and do not even bother to compile this file
// or 2. Compile all __Dpi.cpp files in the same compiler run,
//       and #ifdefs already inserted here will sort everything out.

#include "VysyxSoCFull__Dpi.h"
#include "VysyxSoCFull.h"

#ifndef VL_DPIDECL_npc_dbg_access_fault_
#define VL_DPIDECL_npc_dbg_access_fault_
int npc_dbg_access_fault() {
    // DPI export at ../vsrc/core_dbg.vh:18:16
    return VysyxSoCFull::npc_dbg_access_fault();
}
#endif

#ifndef VL_DPIDECL_npc_dbg_fault_addr_
#define VL_DPIDECL_npc_dbg_fault_addr_
int npc_dbg_fault_addr() {
    // DPI export at ../vsrc/core_dbg.vh:19:16
    return VysyxSoCFull::npc_dbg_fault_addr();
}
#endif

#ifndef VL_DPIDECL_npc_dbg_gpr_
#define VL_DPIDECL_npc_dbg_gpr_
int npc_dbg_gpr(int i) {
    // DPI export at ../vsrc/core_dbg.vh:16:16
    return VysyxSoCFull::npc_dbg_gpr(i);
}
#endif

#ifndef VL_DPIDECL_npc_dbg_inst_pc_
#define VL_DPIDECL_npc_dbg_inst_pc_
int npc_dbg_inst_pc() {
    // DPI export at ../vsrc/core_dbg.vh:14:16
    return VysyxSoCFull::npc_dbg_inst_pc();
}
#endif

#ifndef VL_DPIDECL_npc_dbg_inst_retire_
#define VL_DPIDECL_npc_dbg_inst_retire_
int npc_dbg_inst_retire() {
    // DPI export at ../vsrc/core_dbg.vh:17:16
    return VysyxSoCFull::npc_dbg_inst_retire();
}
#endif

#ifndef VL_DPIDECL_npc_dbg_pc_
#define VL_DPIDECL_npc_dbg_pc_
int npc_dbg_pc() {
    // DPI export at ../vsrc/core_dbg.vh:13:16
    return VysyxSoCFull::npc_dbg_pc();
}
#endif

#ifndef VL_DPIDECL_npc_dbg_retire_
#define VL_DPIDECL_npc_dbg_retire_
int npc_dbg_retire() {
    // DPI export at ../vsrc/core_dbg.vh:15:16
    return VysyxSoCFull::npc_dbg_retire();
}
#endif

