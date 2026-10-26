// C interface to the Verilator NPC model
#ifndef NPC_H
#define NPC_H
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void  npc_init(int argc, char *argv[]);
void  npc_finish(void);        // close wave, cleanup
void  npc_reset(void);
void  npc_cycle(void);           // one clock cycle (posedge + negedge)
void  npc_exec_inst(void);       // run until next instruction starts

bool     npc_halted(void);
bool     npc_aborted(void);      // 非法指令/异常终止(对齐 NEMU_ABORT)
uint32_t npc_pc(void);
uint32_t npc_retire_inst(void);   // 刚退休指令的编码
uint8_t  npc_state(void);        // ctrl_state

// difftest 支持
void     npc_get_gprs(uint32_t *gpr);
bool     npc_get_mmio(void);

// 反汇编 (disasm.c)
void init_disasm(void);
int  disassemble(char *str, int size, uint32_t pc, const uint8_t *code, int nbyte);



#ifdef __cplusplus
}
#endif

#endif
