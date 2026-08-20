// DPI-C 内存后端实现 (DUT 自己的物理内存)。
// 直接持有 pmem_words[] 数组, 与单周期 riscv32e-npc/csrc/dpic.cpp 同构。
// 不引用 ref_difftest_memcpy, 不依赖 NEMU pmem —— DUT 内存是独立真相。
// 由 vsrc/dpic_mem.v 经 DPI-C 调用 dpic_mem_read / dpic_mem_write。

#include "dpic_mem.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// ── DUT 物理内存本体 (仿真进程的普通数组, 字节/字寻址) ──────────────────
// 容量 128 MiB, 与 NEMU CONFIG_MSIZE 同量级, 故 amtest 等大镜像也能直接跑。
static const size_t DPI_PMEM_MAX_WORDS = (128u * 1024u * 1024u) / 4u;
static uint32_t pmem_words[DPI_PMEM_MAX_WORDS] = {0};
static size_t   pmem_words_size = 0;  // 实际已初始化字数 (用于越界检查)

// ── 地址映射: 物理地址 -> 数组下标 ─────────────────────────────────────
// 与 NEMU ref.c 的 guest_to_host 严格一致: pmem + paddr - CONFIG_MBASE,
// 不做任何低位地址折回 (NEMU 侧也无折回逻辑)。传入的 addr 必须是物理地址。
static uint32_t dpi_addr_to_index(uint32_t addr)
{
  return (addr - DPI_PMEM_BASE) >> 2;
}

// ── 镜像加载 / 初始化 (main 在仿真前调用) ─────────────────────────────
bool dpi_load_image(const char *path)
{
  FILE *fp = fopen(path, "r");
  if (fp == nullptr) { perror("dpi_load_image fopen"); return false; }

  // 简单 hex 解析: 每行 "addr: word" 或 "@addr word ...", 这里只支持
  // abstract-machine tools/bin2readmemh.py 产出的 "@addr data data ..." 格式。
  // 注: 与单周期保持一致, 足以支撑 amtest/cpu-tests。
  uint32_t cur = 0;
  char line[512];
  while (fgets(line, sizeof(line), fp))
  {
    char *tok = strtok(line, " \t\r\n");
    while (tok != nullptr)
    {
      if (tok[0] == '#' || tok[0] == '@')
      {
        if (tok[0] == '@')
        {
          // "@<字地址>" -> 转字节地址
          uint32_t waddr = (uint32_t)strtoul(tok + 1, nullptr, 16);
          cur = waddr << 2;
        }
        break;  // 注释行 / 地址行跳过剩余 token
      }
      uint32_t v = (uint32_t)strtoul(tok, nullptr, 16);
      uint32_t idx = dpi_addr_to_index(cur);
      if (idx < DPI_PMEM_MAX_WORDS)
      {
        pmem_words[idx] = v;
        if (idx + 1 > pmem_words_size) pmem_words_size = idx + 1;
      }
      cur += 4;
      tok = strtok(nullptr, " \t\r\n");
    }
  }
  fclose(fp);
  printf("[dpic_mem] loaded image %s, %zu words\n", path, pmem_words_size);
  return true;
}

// raw .bin: 线性布局, 字节 0 落在 MEM_BASE (0x80000000)。
// 逐字节填入 pmem_words[] —— 与 NEMU ref.c 的
//   memcpy(guest_to_host(MEM_BASE), buf, rd)
// 完全等价 (guest_to_host 返回字节指针, 逐字节落盘),
// 避免任何 uint32 重组带来的字节序/对齐歧义。
void dpi_load_bin(const uint8_t *buf, size_t len)
{
  if (buf == nullptr || len == 0) return;
  uint8_t *base = reinterpret_cast<uint8_t *>(pmem_words);
  size_t n = len;
  if (n > DPI_PMEM_MAX_WORDS * sizeof(uint32_t))
    n = DPI_PMEM_MAX_WORDS * sizeof(uint32_t);
  for (size_t i = 0; i < n; i++) base[i] = buf[i];
  pmem_words_size = (n + 3) / sizeof(uint32_t);
}

void dpi_init_pmem(size_t bytes)
{
  size_t words = (bytes == 0) ? 1 : (bytes / 4);
  if (words > DPI_PMEM_MAX_WORDS) words = DPI_PMEM_MAX_WORDS;
  pmem_words_size = words;
  for (size_t i = 0; i < pmem_words_size; i++) pmem_words[i] = 0;
}

// ── DUT 内存拷出 (给 difftest 初始化 REF 用, 方向 DUT -> NEMU) ──────────
// 逐字节拷出, 与 dpi_load_bin 对称。
void dpi_pmem_copy_out(void *dst, size_t bytes)
{
  if (dst == nullptr || bytes == 0) return;
  size_t n = bytes;
  size_t maxn = pmem_words_size * sizeof(uint32_t);
  if (n > maxn) n = maxn;
  memcpy(dst, pmem_words, n);
}

// ── DPI-C 入口 (被 dpic_mem.v 调用) ──────────────────────────────────────
extern "C" {

void dpic_mem_read(unsigned long long addr, unsigned int *rdata)
{
  if (rdata == nullptr) return;
  uint32_t idx = dpi_addr_to_index((uint32_t)addr);
  if (idx >= pmem_words_size)
  {
    *rdata = 0;
    return;
  }
  // 返回对齐字的 4 字节, 由 LSU 用 addr[1:0] 选字节 (小端: 低字节在低地址)
  *rdata = pmem_words[idx];
}

void dpic_mem_write(unsigned long long addr, unsigned int wdata, unsigned char wmask)
{
  uint32_t idx = dpi_addr_to_index((uint32_t)addr);
  if (idx >= DPI_PMEM_MAX_WORDS) return;

  uint32_t old = pmem_words[idx];
  uint8_t *p = (uint8_t *)&old;
  if (wmask & 0x1) p[0] = uint8_t(wdata >> 0);
  if (wmask & 0x2) p[1] = uint8_t(wdata >> 8);
  if (wmask & 0x4) p[2] = uint8_t(wdata >> 16);
  if (wmask & 0x8) p[3] = uint8_t(wdata >> 24);
  pmem_words[idx] = old;

  if (idx + 1 > pmem_words_size) pmem_words_size = idx + 1;
}

} // extern "C"
