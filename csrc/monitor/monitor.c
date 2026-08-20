#include "npc.h"
#include "sdb/sdb.h"
#include "difftest.h"
#include <stdio.h>
#include <string.h>

#define ANSI_FG_YELLOW  "\033[1;33m"
#define ANSI_FG_GREEN   "\033[1;32m"
#define ANSI_FG_RED     "\033[1;31m"
#define ANSI_BG_RED     "\033[1;41m"
#define ANSI_NONE       "\033[0m"
#define ANSI_FMT(s, fmt)  fmt s ANSI_NONE

static char img_path[256];

static void welcome(void) {
  printf("Trace: " ANSI_FMT("OFF", ANSI_FG_RED) "\n");
  printf("Build time: %s, %s\n", __TIME__, __DATE__);
  printf("Welcome to " ANSI_FMT("riscv32", ANSI_FG_YELLOW ANSI_BG_RED) "-multi-cycle-NPC!\n");
  printf("For help, type \"help\"\n");
}

void init_monitor(int argc, char *argv[]) 
{
  for (int i = 1; i < argc; i++) 
  {
    if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--batch") == 0)
      sdb_set_batch();
    else if (argv[i][0] != '-')
      strncpy(img_path, argv[i], sizeof(img_path) - 1);
  }

  if (img_path[0])
    printf("The image is %s\n", img_path);
  else
    printf("No image is given. Built-in default instructions will be used.\n");

  npc_reset();

#ifndef ENABLE_DIFFTEST
#define ENABLE_DIFFTEST 0
#endif
  // DPI_MEM 模式下 DUT 物理内存在 C++ 侧 pmem_words[], 必须有镜像来源,
  // 故无论是否开 difftest, 都要调 difftest_init 加载镜像(其内部再按需同步 REF)。
  difftest_init(npc_pc(), img_path);
#if ENABLE_DIFFTEST
  printf("DiffTest: " ANSI_FMT("ON", ANSI_FG_GREEN) "\n");
#else
  printf("DiffTest: " ANSI_FMT("OFF", ANSI_FG_RED) "\n");
#endif

  welcome();
}
