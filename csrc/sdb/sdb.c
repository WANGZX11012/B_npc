#include "npc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cpu_exec(int64_t n);

static int is_batch = 0;
void sdb_set_batch(void) { is_batch = 1; }

void sdb_mainloop(void) 
{
  if (is_batch) 
  {
    cpu_exec(-1);
    return;
  }

  char line[256];
  printf("(npc) ");
  fflush(stdout);

  while (fgets(line, sizeof(line), stdin)) 
  {
    char *cmd = strtok(line, " \t\n");
    if (!cmd) { printf("(npc) "); fflush(stdout); continue; }

    if (strcmp(cmd, "c") == 0)
      cpu_exec(-1);
    else if (strcmp(cmd, "si") == 0 || strcmp(cmd, "s") == 0) 
    {
      if (!npc_halted()) 
      {
        uint32_t pc = npc_pc();            // 执行前: 这条指令自己的地址
        npc_exec_inst();                    // 执行完, PC 已经前进
        uint32_t inst = npc_retire_inst();  // 刚退休那条的编码(退休拍快照)
        uint8_t  code[4] = { (uint8_t)(inst >>  0), (uint8_t)(inst >>  8),
                             (uint8_t)(inst >> 16), (uint8_t)(inst >> 24) };
        char asm_str[128];
        disassemble(asm_str, sizeof(asm_str), pc, code, 4);
        printf("0x%08x: %02x %02x %02x %02x\t%s\n",
               pc, code[0], code[1], code[2], code[3], asm_str);
      }
    } 

    else if (strcmp(cmd, "r") == 0)
      printf("pc=0x%08x  ir=0x%08x  state=%d  halt=%d\n",
             npc_pc(), npc_retire_inst(), npc_state(), npc_halted());
    else if (strcmp(cmd, "q") == 0)
      break;
    else if (strcmp(cmd, "help") == 0 || strcmp(cmd, "h") == 0)
      printf("Commands: c  si(s)  r  q  help\n");
    else
      printf("Unknown command: %s\n", cmd);

    printf("(npc) "); fflush(stdout);
  }
}
