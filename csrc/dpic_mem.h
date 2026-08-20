#ifndef NPC_DPIX_MEM_H
#define NPC_DPIX_MEM_H

#include <cstdint>
#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

// DPI-C 内存后端: DUT 自己的物理内存真相, 由 C++ 持有的数组实现。
// 与单周期 riscv32e-npc/csrc/dpic.cpp 的 pmem_words[] 同构 —— DUT 内存独立,
// 不依赖 NEMU pmem, 也不经过 difftest 的 ref_difftest_memcpy。
// 这样将来做"内存比对"时, DUT 内存(本数组)和 REF 内存(NEMU pmem)是两份独立真相, 比对才有意义。
//
// 地址按 4 字节对齐读写(字寻址), 非对齐的字地址由 LSU 用 addr[1:0] 选字节。

// DUT 物理内存基址 (与 NEMU CONFIG_MBASE 一致, 仅用于地址映射, 不依赖 NEMU)
#define DPI_PMEM_BASE 0x80000000u

// 由镜像加载填充 DUT 内存 (main 在仿真前调用)
bool dpi_load_image(const char *path);
// 直接把 raw .bin 线性字节 (从 MEM_BASE 起) 填进 DUT pmem_words[]。
// difftest 启动时先调它把镜像载进 DUT, 再用 dpi_pmem_copy_out 同步给 REF。
void dpi_load_bin(const uint8_t *buf, size_t len);
// 无镜像时的兜底初始化
void dpi_init_pmem(size_t bytes);
// 把 DUT 内存当前内容拷出, 供 difftest 初始化 REF 用 (方向: DUT -> NEMU)
void dpi_pmem_copy_out(void *dst, size_t bytes);

// 从 DUT pmem 读 4 字节 (被 vsrc/dpic_mem.v 经 DPI-C 调用)
void dpic_mem_read(unsigned long long addr, unsigned int *rdata);

// 写 4 字节回 DUT pmem (被 vsrc/dpic_mem.v 经 DPI-C 调用, 按 wmask 合并字节)
void dpic_mem_write(unsigned long long addr, unsigned int wdata, unsigned char wmask);

#ifdef __cplusplus
}
#endif

#endif
