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

// 装载镜像到 DUT pmem (唯一入口): raw .bin, 字节 0 落在 DPI_PMEM_BASE
//   空路径 → 内置默认程序; 打不开/为空 → 报错 abort
void dpi_load_image(const char *path);

// DUT 内存已装载镜像的字节数 (difftest 同步 REF 用)
size_t dpi_pmem_image_bytes(void);

// 把 DUT 内存拷出, 同步给 REF 用 (方向: DUT -> NEMU)
void dpi_pmem_copy_out(void *dst, size_t bytes);

// ── 内部工具: 只在本文件使用, 不对外暴露 ──
static void dpi_load_bin(const uint8_t *buf, size_t len);
static void dpi_load_default(void);




#ifdef __cplusplus
}
#endif

#endif
