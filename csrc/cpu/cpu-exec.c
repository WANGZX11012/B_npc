#include "npc.h"
#include "difftest.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_INST_TO_PRINT 10

static uint64_t g_nr_inst    = 0;
static bool     g_print_step = false;

#ifndef ENABLE_DIFFTEST
#define ENABLE_DIFFTEST 0
#endif

#if ITRACE_ENABLE
static FILE *g_itrace_fp     = NULL;
static int   g_itrace_inited = 0;

static inline void itrace_write(uint32_t pc, uint32_t inst)
{
  if (!g_itrace_inited)
  {
    g_itrace_inited = 1;
    g_itrace_fp = fopen("build/itrace.bin", "wb");
    if (!g_itrace_fp) { perror("itrace fopen"); exit(1); }
  }
  fwrite(&pc, sizeof(pc), 1, g_itrace_fp);
}
#else
  #define itrace_write(pc, inst) ((void)0)
#endif

static void print_inst(uint32_t pc, uint32_t inst)
{
  uint8_t code[4] = { (uint8_t)(inst >>  0), (uint8_t)(inst >>  8),
                      (uint8_t)(inst >> 16), (uint8_t)(inst >> 24) };
  char asm_str[128];
  disassemble(asm_str, sizeof(asm_str), pc, code, 4);
  printf("0x%08x: %02x %02x %02x %02x\t%s\n",
         pc, code[0], code[1], code[2], code[3], asm_str);
}

// 执行一条指令: exec + 计数 + itrace + 打印 + difftest
// 返回 0 正常, -1 mismatch
static int exec_once(void)
{
  uint32_t before_pc = npc_pc();
  npc_exec_inst();
  uint32_t after_pc  = npc_pc();
  uint32_t inst      = npc_retire_inst();

  bool pc_advanced = (after_pc != before_pc);
  bool is_halt     = npc_halted() && !npc_aborted();

  if (pc_advanced)
  {
    itrace_write(before_pc, inst);
    g_nr_inst++;
    if (g_print_step)
      print_inst(before_pc, inst);          // ← 只打真正退休的指令
  }

  // ebreak 不产生 retire, 且 halt 是 "IFU 手里拿着 ebreak" 的组合信号:
  //   - ebreak 自己那步: pc 不动  -> 打 before_pc
  //   - ebreak 被 IFU 提前预取: 上一条 pc 前进 -> 打 after_pc
  if (is_halt && g_print_step)
    print_inst(pc_advanced ? after_pc : before_pc, 0x00100073);


#if ENABLE_DIFFTEST
  if (after_pc != before_pc || inst == 0x00100073)
  {
    uint32_t dut_gpr[32];
    npc_get_gprs(dut_gpr);
    if (!difftest_step(after_pc, inst, dut_gpr))
    {
      printf("npc: DIFFTEST MISMATCH at pc = 0x%08x, abort\n", after_pc);
      return -1;
    }
  }
#endif
  return 0;
}

// n < 0: 跑到停机; n > 0: 跑 n 条
static void execute(int64_t n)
{
  while (n != 0 && !npc_halted())
  {
    if (exec_once() < 0) return;
    if (n > 0) n--;
  }
}

void cpu_exec(int64_t n)
{
  // c 传 -1, 必须加 n > 0, 否则 -1 <= 10 会误开打印
  g_print_step = (n > 0 && n <= MAX_INST_TO_PRINT);

  execute(n);

  if (!npc_halted()) return;

  if (npc_aborted())
  {
    printf("npc: HIT BAD TRAP (illegal instruction) at pc = 0x%08x, inst = 0x%08x, total_inst = %lu\n",
           npc_pc(), npc_retire_inst(), g_nr_inst);
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

  for (int i = 0; i < 100; i++) npc_cycle();
}
