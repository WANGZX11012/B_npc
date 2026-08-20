#include "npc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cpu_exec(int64_t n);

static int is_batch = 0;
void sdb_set_batch(void) { is_batch = 1; }

void sdb_mainloop(void) {
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
    else if (strcmp(cmd, "si") == 0 || strcmp(cmd, "s") == 0) {
      if (!npc_halted()) {
        npc_exec_inst();
        printf("pc=0x%08x  ir=0x%08x  state=%d\n",
               npc_pc(), npc_ir(), npc_state());
      }
    } else if (strcmp(cmd, "r") == 0)
      printf("pc=0x%08x  ir=0x%08x  state=%d  halt=%d\n",
             npc_pc(), npc_ir(), npc_state(), npc_halted());
    else if (strcmp(cmd, "q") == 0)
      break;
    else if (strcmp(cmd, "help") == 0 || strcmp(cmd, "h") == 0)
      printf("Commands: c  si(s)  r  q  help\n");
    else
      printf("Unknown command: %s\n", cmd);

    printf("(npc) "); fflush(stdout);
  }
}
