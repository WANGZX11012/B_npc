// C++ wrapper around Verilator Vtop — exposes C functions

#include "npc.h"
#include "Vtop.h"
#include "Vtop___024root.h"
#include "verilated.h"

#if TRACE_ENABLE
#include "verilated_vcd_c.h"
#define TRACE_DUMP(t)   do { if (tfp) tfp->dump(t); } while (0)
#define TRACE_CLOSE()   do { if (tfp) { tfp->close(); tfp = nullptr; } } while (0)
#else
#define TRACE_DUMP(t)   do {} while (0)
#define TRACE_CLOSE()   do {} while (0)
#endif

#include <cstdio>
#include <cstring>
#include <ctime>

static Vtop *top = nullptr;

#if TRACE_ENABLE
static VerilatedVcdC *tfp = nullptr;
static uint64_t tick = 0;
#endif

static uint64_t rtc_boot_us = 0;

extern "C" {

long long rtc_time_us()
{
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  uint64_t now = (uint64_t)ts.tv_sec * 1000000ull + ts.tv_nsec / 1000;
  if(rtc_boot_us == 0)  rtc_boot_us = now;
  return (long long)(now - rtc_boot_us);
}

// DPI-C: 串口输出。Verilog uart.v 写 0xa00003f8 时调这里，逐字节打印到终端
void uart_putchar(unsigned char c)
{
  putchar(c);
  fflush(stdout);
}

void npc_init(int argc, char *argv[]) 
{
  Verilated::commandArgs(argc, argv);
  top = new Vtop;

  // optional waveform
  #if TRACE_ENABLE

  for (int i = 1; i < argc; i++) 
  {
    if (strcmp(argv[i], "--wave") == 0 || strcmp(argv[i], "-w") == 0) 
    {
      Verilated::traceEverOn(true);
      tfp = new VerilatedVcdC;
      top->trace(tfp, 99);
      tfp->open("build/sim.vcd");
    }
  }

  #endif
}

void npc_reset(void) 
{
  top->clk = 0; top->rst = 1; top->eval();

  TRACE_DUMP(tick++); TRACE_DUMP(tick++); TRACE_DUMP(tick++);
  
  top->clk = 1; top->eval();  // posedge with rst=1, so sync-reset registers actually reset
  
  TRACE_DUMP(tick++);
  
  top->rst = 0; top->clk = 0; top->eval();
  
  TRACE_DUMP(tick++);  // show clk=0 rst=0 before first npc_cycle posedge
}

void npc_cycle(void) 
{
  top->clk = 1; top->eval(); TRACE_DUMP(tick++);
  top->clk = 0; top->eval(); TRACE_DUMP(tick++);
}

void npc_exec_inst(void) //走完一条指令 500是一条指令的上限时钟周期
{
  // run cycles until state returns to FET (1) or halt
  int cnt = 0;
  uint8_t prev = top->state_dbg; //prev 不准确 应该是当前的状态
  do 
  {
    npc_cycle(); //一次时钟周期 刷新电路状态
    prev = top->state_dbg;
  } 
  while (prev != 1 && !top->halt && !top->aborted && ++cnt < 500);
}

void npc_cont(void) {
  int cnt = 0;
  while (!top->halt && cnt++ < 10000)
    npc_cycle();
}

bool     npc_halted(void) { return top->halt || top->aborted; } //停下 两种原因都会导致拉高
uint32_t npc_pc(void)     { return top->pc; }
uint32_t npc_ir(void)     { return top->ir_dbg; }
uint8_t  npc_state(void)  { return top->state_dbg; }
bool     npc_aborted(void) { return top->aborted; }

// difftest 需要:读寄存器堆 / mcycle / mmio 标志(挖 Verilator rootp 层次)
void npc_get_gprs(uint32_t *gpr)
{
  if (top == nullptr || gpr == nullptr) return;
  gpr[0] = 0;  // x0 恒为 0
  for (int i = 1; i < 32; i++)
  {
    gpr[i] = top->rootp->top__DOT__u_core__DOT__u_regfile__DOT__rf[i];
  }
}

bool npc_get_mmio(void) { return top->mmio_dbg; }

void npc_finish(void) { TRACE_CLOSE(); }

} // extern "C"
