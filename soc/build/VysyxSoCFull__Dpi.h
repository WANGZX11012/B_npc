// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#ifndef VERILATED_VYSYXSOCFULL__DPI_H_
#define VERILATED_VYSYXSOCFULL__DPI_H_  // guard

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI EXPORTS
    // DPI export at ../vsrc/core_dbg.vh:18:16
    extern int npc_dbg_access_fault();
    // DPI export at ../vsrc/core_dbg.vh:19:16
    extern int npc_dbg_fault_addr();
    // DPI export at ../vsrc/core_dbg.vh:16:16
    extern int npc_dbg_gpr(int i);
    // DPI export at ../vsrc/core_dbg.vh:14:16
    extern int npc_dbg_inst_pc();
    // DPI export at ../vsrc/core_dbg.vh:17:16
    extern int npc_dbg_inst_retire();
    // DPI export at ../vsrc/core_dbg.vh:13:16
    extern int npc_dbg_pc();
    // DPI export at ../vsrc/core_dbg.vh:15:16
    extern int npc_dbg_retire();

    // DPI IMPORTS
    // DPI import at ../vsrc/../../ysyxSoC/perip/flash/flash.v:84:30
    extern void flash_read(int addr, int* data);
    // DPI import at build/ysyxSoCFull.v:5402:30
    extern void mrom_read(int raddr, int* rdata);

#ifdef __cplusplus
}
#endif

#endif  // guard
