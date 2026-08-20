#include "npc.h"
#include "difftest.h"
#include <stdio.h>

static uint64_t g_nr_inst = 0;

#ifndef ENABLE_DIFFTEST
#define ENABLE_DIFFTEST 0
#endif

void cpu_exec(int64_t n) 
{
  if (n < 0) //小于0就是无限执行？
  {
    while (!npc_halted())
    {
      uint32_t before_pc = npc_pc();
      npc_exec_inst();
      uint32_t after_pc  = npc_pc();
      uint32_t inst      = npc_ir();   // 执行完的指令 (FET 还没覆盖 IR)

      if (after_pc != before_pc || inst == 0x00100073) //加上ebreak的计数
      {  // PC changed → 一条指令执行完
        g_nr_inst++;
      }

#if ENABLE_DIFFTEST
      // 一条指令真正执行完(PC 已更新)后才做 difftest 比对
      // ERR 状态(abort)下 PC 不动, DUT/REF 都没前进, 跳过比对
      if (after_pc != before_pc || inst == 0x00100073)
      {
        uint32_t dut_gpr[32];
        npc_get_gprs(dut_gpr);
        if (!difftest_step(after_pc, inst, dut_gpr))
        {
          printf("npc: DIFFTEST MISMATCH at pc = 0x%08x, abort\n", after_pc);
          return;
        }
      }
#endif
    }

    // 退出原因区分, 对齐 NEMU 的 trap 语义:
    //   abort  -> BAD TRAP (非法指令/异常终止)
    //   halt(ebreak) 且 a0==0 -> GOOD TRAP
    //   halt(ebreak) 且 a0!=0 -> 测试失败 (BAD TRAP)
    // a0 = GPR[10], 由 nemu_trap(code) 写入; code==0 才算成功
    if (npc_aborted())
    {
      printf("npc: HIT BAD TRAP (illegal instruction) at pc = 0x%08x, inst = 0x%08x, total_inst = %lu\n",
             npc_pc(), npc_ir(), g_nr_inst);
    }
    else
    {
      uint32_t gpr[32];
      npc_get_gprs(gpr);
      uint32_t a0 = gpr[10];
      if (a0 == 0)
        printf("npc: HIT GOOD TRAP at pc = 0x%08x, total_inst = %lu\n",
               npc_pc(), g_nr_inst);
      else
        printf("npc: HIT BAD TRAP (a0 = %u != 0, test failed) at pc = 0x%08x, total_inst = %lu\n",
               a0, npc_pc(), g_nr_inst);
    }
  } 
  else 
  {
    for (int64_t i = 0; i < n && !npc_halted(); i++)
      npc_exec_inst();
  }
}
