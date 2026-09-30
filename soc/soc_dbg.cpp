#include "soc_tb.h"              // 声明/定义的交叉检查
#include "VysyxSoCFull__Dpi.h"   // verilator 生成的导出声明
#include "VysyxSoCFull.h"

#include "verilated_dpi.h"       // svGetScopeFromName / svSetScope
#include <cstdio>                // printf / fprintf
#include <cstdlib>               // abort

uint32_t cpu_pc(VysyxSoCFull *)             { return npc_dbg_pc();      }
uint32_t cpu_ir_pc(VysyxSoCFull *)          { return npc_dbg_inst_pc(); }
bool     cpu_retire(VysyxSoCFull *)         { return npc_dbg_retire();  }
bool     cpu_inst_retire(VysyxSoCFull *)    { return npc_dbg_inst_retire();  }
bool     cpu_access_fault(VysyxSoCFull *)   { return npc_dbg_access_fault() != 0; }
uint32_t cpu_fault_addr(VysyxSoCFull *)     { return (uint32_t)npc_dbg_fault_addr(); }


void     cpu_get_gprs(VysyxSoCFull *, uint32_t *g) 
{
  g[0] = 0;
  for (int i = 1; i < 32; i++) g[i] = npc_dbg_gpr(i);
}

void cpu_dbg_init(void)
{
  svScope sc = svGetScopeFromName("TOP.ysyxSoCFull.asic.cpu.cpu.u_core");
  if (sc == nullptr) {
    fprintf(stderr, "[dbg] DPI scope 找不到: TOP.ysyxSoCFull.asic.cpu.cpu.u_core\n");
    abort();
  }
  svSetScope(sc);                     // 之后就一直是这个 scope(thread-local)
  printf("[dbg] DPI scope 已设置\n");
}
