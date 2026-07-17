#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <cstdio>
#include <unistd.h>

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);

  Vtop *top = new Vtop;

  // 波形
  Verilated::traceEverOn(true);
  VerilatedVcdC *tfp = new VerilatedVcdC;
  top->trace(tfp, 99);
  tfp->open("build/sim.vcd");

  // 复位
  top->clk = 0; top->reset = 1; top->eval(); tfp->dump(0);
  top->clk = 1; top->eval(); tfp->dump(1);
  top->clk = 0; top->reset = 0; top->eval(); tfp->dump(2);

  uint64_t tick = 3;
  while (!top->halt && tick < 400) 
  {
    top->clk = 1; top->eval(); tfp->dump(tick++);
    top->clk = 0; top->eval(); tfp->dump(tick++);
  }

  printf("[SIM] %s at tick %lu, pc=0x%08x\n",
         top->halt ? "Halted" : "Timeout", tick, top->pc);

  tfp->close();
  exit(0);  // Verilator $readmemh + delete 有清理 bug，跳过析构
}

