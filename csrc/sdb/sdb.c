#include "npc.h"
#include "sdb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static char *rl_gets(void)
{
  static char *line_read = NULL;
  if (line_read) { free(line_read); line_read = NULL; }
  line_read = readline("(npc) ");
  if (line_read && *line_read) add_history(line_read);
  return line_read;
}



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
  uint32_t gpr[32];
  npc_get_gprs(gpr);
  for (int i = 0; i < 16; i++)
  {
    printf("x%-2d = 0x%08x%s", i, gpr[i], (i % 4 == 3) ? "\n" : "   ");
  }
  return 0;
}


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

  char *line;
  while ((line = rl_gets()) != NULL)
  {
    int len = (int)strlen(line);
    while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r' ||
                       line[len-1] == '\t' || line[len-1] == ' '))
      line[--len] = '\0';

    char *str_end = line + len;
    char *cmd = strtok(line, " \t\n");
    if (!cmd) continue;

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
  }
}
