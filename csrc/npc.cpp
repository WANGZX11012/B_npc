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
static uint64_t g_cycles = 0;   // 跑了多少个时钟周期 (仿真器侧自己数)
static uint64_t g_t0_us  = 0;   // 第一个周期时的墙钟 (us)




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
  fflush(stdout);  //stdout 有缓冲
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
  if (g_cycles == 0) g_t0_us = (uint64_t)rtc_time_us();   // 起点
  g_cycles++;
  
  top->clk = 1; top->eval(); TRACE_DUMP(tick++);
  top->clk = 0; top->eval(); TRACE_DUMP(tick++);
}

void npc_exec_inst(void) //走完一条指令 500是一条指令的上限时钟周期
{
  // run cycles until state returns to FET (1) or halt
  int cnt = 0;
  // 执行一次时钟周期后 再看条件 这样来推进时钟
  do 
  {
    npc_cycle(); //一次时钟周期 刷新电路状态
  } 
  while (!top->inst_retire && !top->halt && !top->aborted && ++cnt < 500);
}


bool     npc_halted(void) { return top->halt || top->aborted; } //停下 两种原因都会导致拉高
uint32_t npc_pc(void)     { return top->pc; }
uint32_t npc_retire_inst(void) { return top->retire_inst_dbg; }
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

void npc_finish(void)
{
  if (g_cycles)
  {
    uint64_t dt = (uint64_t)rtc_time_us() - g_t0_us;      // 墙钟 (us)
    uint64_t rate = dt ? (g_cycles * 1000000ull / dt) : 0;
    printf("[mtime] cycles=%llu  host=%llu us  rate=%llu Hz\n",
           (unsigned long long)g_cycles,
           (unsigned long long)dt,
           (unsigned long long)rate);
  }
  TRACE_CLOSE();
}


} // extern "C"
