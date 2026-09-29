#ifndef SOC_DIFFTEST_H
#define SOC_DIFFTEST_H

#include "VysyxSoCFull.h"
#include <cstdint>

// 初始化: dlopen ref.so → 把镜像写进 REF 内存 → 用 DUT 的 PC/GPR 同步 REF
// 必须在 reset_circuit() 之后调用(那时 PC 才是复位值)
void difftest_init(VysyxSoCFull *top, const char *img_path);

// 每退休一条指令调一次; 返回 false 表示不一致, 仿真应停止
bool difftest_step(uint32_t dut_pc, const uint32_t *dut_gpr);
// 到此刻为止是否一直一致 (没开 difftest 时恒 true)
bool         difftest_ok(void);
#endif
