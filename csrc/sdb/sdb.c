#include "npc.h"
#include "sdb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int is_batch = 0;
void sdb_set_batch(void) { is_batch = 1; }

static int cmd_help(char *args);

// ---- 命令实现: 返回 0 继续主循环, -1 退出 ----

static int cmd_c(char *args)
{
  cpu_exec(-1);
  return 0;
}

static int cmd_si(char *args)
{
  int n = 1;
  if (args != NULL && *args != '\0')
  {
    char *endptr;
    long v = strtol(args, &endptr, 10);
    if (*endptr != '\0' || v <= 0)
    {
      printf("Usage: si [N]  (N > 0)\n");
      return 0;
    }
    n = (int)v;
  }
  cpu_exec(n);
  return 0;
}

static int print_regs(void)
{
  printf("pc=0x%08x  ir=0x%08x  state=%d  halt=%d\n",
         npc_pc(), npc_retire_inst(), npc_state(), npc_halted());
  return 0;
}

static int cmd_r(char *args)    { return print_regs(); }
static int cmd_q(char *args)    { return -1; }

static int cmd_info(char *args)
{
  if (args != NULL && strcmp(args, "r") == 0)
    return print_regs();
  printf("Usage: info r\n");
  return 0;
}

static struct {
  const char *name;
  const char *desc;
  int (*handler)(char *);
} cmd_table[] = {
  { "help", "Display all commands",            cmd_help },
  { "c",    "Continue until halt",             cmd_c    },
  { "si",   "Step N instructions (default 1)", cmd_si   },
  { "info", "info r: print registers",         cmd_info },
  { "r",    "Print registers (alias of info r)", cmd_r  },
  { "q",    "Quit",                            cmd_q    },
};

#define NR_CMD (int)(sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args)
{
  if (args == NULL)
  {
    printf("%-6s %s\n", "Command", "Description");
    for (int i = 0; i < NR_CMD; i++)
      printf("%-6s %s\n", cmd_table[i].name, cmd_table[i].desc);
  }
  else
  {
    for (int i = 0; i < NR_CMD; i++)
      if (strcmp(args, cmd_table[i].name) == 0)
      {
        printf("%-6s %s\n", cmd_table[i].name, cmd_table[i].desc);
        return 0;
      }
    printf("Unknown command '%s'\n", args);
  }
  return 0;
}

void sdb_mainloop(void)
{
  if (is_batch) { cpu_exec(-1); return; }

  char line[256];
  printf("(npc) "); fflush(stdout);

  while (fgets(line, sizeof(line), stdin))
  {
    // 去掉行尾 \r \n 及尾随空白: 否则 "si 10\n" 的 args 是 "10\n",
    // strtol 的 endptr 会停在 '\n' 上而被误判为非法输入
    int len = (int)strlen(line);
    while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r' ||
                       line[len-1] == '\t' || line[len-1] == ' '))
      line[--len] = '\0';

    char *str_end = line + len;        // ← 原来是 line + strlen(line)
    char *cmd = strtok(line, " \t\n");
    
    if (!cmd) { printf("(npc) "); fflush(stdout); continue; }

    // 剩余整串作为 args, 不按空格切, 将来加 p/w 不用改框架
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end)
      args = NULL;
    else
    {
      while (*args == ' ' || *args == '\t') args++;   // 跳过连续空格
      if (*args == '\0') args = NULL;
    }

    int i;
    for (i = 0; i < NR_CMD; i++)
    {
      if (strcmp(cmd, cmd_table[i].name) == 0)
      {
        if (cmd_table[i].handler(args) < 0) return;
        break;
      }
    }
    if (i == NR_CMD) printf("Unknown command '%s'\n", cmd);

    printf("(npc) "); fflush(stdout);
  }
}
