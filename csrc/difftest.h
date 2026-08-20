#ifndef NPC_DIFFTEST_H
#define NPC_DIFFTEST_H

#include <cstdint>

// 初始化 difftest: 加载 REF .so, 用 bin 镜像同步 REF 内存, 同步寄存器
void difftest_init(uint32_t dut_pc, const char *img_path);

// 每条指令完成后调用一次: REF 执行 1 条, 然后比对寄存器
// 返回 true 表示比对通过, false 表示 mismatch
bool difftest_step(uint32_t dut_pc, uint32_t dut_inst, const uint32_t *dut_gpr);

#endif
