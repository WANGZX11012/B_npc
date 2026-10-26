// npc/csrc/disasm.c —— 静态链接 capstone, 运行时不依赖 .so
#include <capstone/capstone.h>
#include <stdio.h>
#include "npc.h"

static csh handle;
static int disasm_ready = 0;

void init_disasm(void)
{
  if (cs_open(CS_ARCH_RISCV, CS_MODE_RISCV32, &handle) != CS_ERR_OK)
  {
    fprintf(stderr, "[disasm] cs_open(riscv32) failed\n");
    return;
  }
  disasm_ready = 1;
}

int disassemble(char *str, int size, uint32_t pc, const uint8_t *code, int nbyte)
{
  if (!disasm_ready)
  {
    snprintf(str, size, "unknown");
    return -1;
  }

  cs_insn *insn = NULL;
  size_t count = cs_disasm(handle, code, (size_t)nbyte, pc, 0, &insn);
  if (count < 1)
  {
    snprintf(str, size, "unknown");
    return -1;
  }

  int ret = snprintf(str, size, "%s", insn->mnemonic);
  if (ret > 0 && ret < size && insn->op_str[0] != '\0')
    snprintf(str + ret, size - ret, "\t%s", insn->op_str);

  cs_free(insn, count);
  return 0;
}
