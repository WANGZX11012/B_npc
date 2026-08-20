// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

extern "C" void dpic_mem_read(unsigned long long addr, unsigned int* rdata);

void Vtop___024unit____Vdpiimwrap_dpic_mem_read_TOP____024unit(QData/*63:0*/ addr, IData/*31:0*/ &rdata) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop___024unit____Vdpiimwrap_dpic_mem_read_TOP____024unit\n"); );
    // Body
    unsigned long long addr__Vcvt;
    addr__Vcvt = addr;
    unsigned int rdata__Vcvt;
    dpic_mem_read(addr__Vcvt, &rdata__Vcvt);
    rdata = (rdata__Vcvt);
}

extern "C" void dpic_mem_write(unsigned long long addr, unsigned int wdata, unsigned char wmask);

void Vtop___024unit____Vdpiimwrap_dpic_mem_write_TOP____024unit(QData/*63:0*/ addr, IData/*31:0*/ wdata, CData/*7:0*/ wmask) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop___024unit____Vdpiimwrap_dpic_mem_write_TOP____024unit\n"); );
    // Body
    unsigned long long addr__Vcvt;
    addr__Vcvt = addr;
    unsigned int wdata__Vcvt;
    wdata__Vcvt = wdata;
    unsigned char wmask__Vcvt;
    wmask__Vcvt = wmask;
    dpic_mem_write(addr__Vcvt, wdata__Vcvt, wmask__Vcvt);
}

extern "C" long long rtc_time_us();

void Vtop___024unit____Vdpiimwrap_rtc_time_us_TOP____024unit(QData/*63:0*/ &rtc_time_us__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop___024unit____Vdpiimwrap_rtc_time_us_TOP____024unit\n"); );
    // Body
    long long rtc_time_us__Vfuncrtn__Vcvt;
    rtc_time_us__Vfuncrtn__Vcvt = rtc_time_us();
    rtc_time_us__Vfuncrtn = (rtc_time_us__Vfuncrtn__Vcvt);
}

extern "C" void uart_putchar(unsigned char c);

void Vtop___024unit____Vdpiimwrap_uart_putchar_TOP____024unit(CData/*7:0*/ c) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop___024unit____Vdpiimwrap_uart_putchar_TOP____024unit\n"); );
    // Body
    unsigned char c__Vcvt;
    c__Vcvt = c;
    uart_putchar(c__Vcvt);
}
