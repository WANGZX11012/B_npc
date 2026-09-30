#ifndef SOC_TB_H
#define SOC_TB_H

#include "VysyxSoCFull.h"     // VysyxSoCFull 类型
#include <cstdint>

/* ── 扮演 SoC 的存储器 (实现在 soc_mem.cpp) ── */
void     load_mrom(const char *path);    // 把 .bin 灌进 MROM 镜像
extern volatile int mrom_count;          // MROM 被访问次数
extern int          ebreak_triggered;    // 取到 ebreak 就置 1
extern uint32_t     ebreak_addr;         // ebreak 所在的取指地址

/* ── 读 CPU 内部信号 (实现在 soc_dbg.cpp) ── */
uint32_t cpu_pc(VysyxSoCFull *top);                    // 退休后的 PC
uint32_t cpu_ir_pc(VysyxSoCFull *top);                 // 这条指令自己的 PC
bool     cpu_retire(VysyxSoCFull *top);                // 这一拍要退休一条指令 本拍进行写回等操作
bool     cpu_inst_retire(VysyxSoCFull *top);           // 干净状态标志
void     cpu_get_gprs(VysyxSoCFull *top, uint32_t *gpr);
void     cpu_dbg_init(void);                           // 设 DPI scope, 必须在 new 之后、调用 cpu_* 之前
bool     cpu_access_fault(VysyxSoCFull *top);           // 是否发生过总线错误(粘住)
uint32_t cpu_fault_addr(VysyxSoCFull *top);             // 第一次出错的地址



#endif
