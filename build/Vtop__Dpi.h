// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#ifndef VERILATED_VTOP__DPI_H_
#define VERILATED_VTOP__DPI_H_  // guard

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI EXPORTS
    // DPI export at /home/wang/ysyx-workbench/npc/vsrc/core_dbg.vh:13:16
    extern int npc_dbg_gpr(int i);
    // DPI export at /home/wang/ysyx-workbench/npc/vsrc/core_dbg.vh:11:16
    extern int npc_dbg_inst_pc();
    // DPI export at /home/wang/ysyx-workbench/npc/vsrc/core_dbg.vh:10:16
    extern int npc_dbg_pc();
    // DPI export at /home/wang/ysyx-workbench/npc/vsrc/core_dbg.vh:12:16
    extern int npc_dbg_retire();

    // DPI IMPORTS
    // DPI import at vsrc/dpic_mem.v:6:30
    extern void dpic_mem_read(unsigned long long addr, unsigned int* rdata);
    // DPI import at vsrc/dpic_mem.v:7:30
    extern void dpic_mem_write(unsigned long long addr, unsigned int wdata, unsigned char wmask);
    // DPI import at vsrc/rtc.v:1:33
    extern long long rtc_time_us();
    // DPI import at vsrc/uart.v:4:30
    extern void uart_putchar(unsigned char c);

#ifdef __cplusplus
}
#endif

#endif  // guard
