#include "soc_difftest.h"
#include "soc_tb.h"                 // cpu_pc / cpu_get_gprs
#include <difftest-def.h>           // DIFFTEST_TO_REF / DIFFTEST_TO_DUT (来自 nemu/include)

#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>

#ifndef ENABLE_DIFFTEST
#define ENABLE_DIFFTEST 0
#endif

#if ENABLE_DIFFTEST

/* 寄存器传递格式: 与 NEMU ref.c 约定的 35 个 uint32_t 一致
 *   [0]=pc  [1..32]=gpr[0..31]  [33]=mcycle_lo  [34]=mcycle_hi
 * 不做 CSR 比对: mcycle 两位恒 0, 保留只为对齐布局(ref.c 固定访问 r[33]/r[34]) */
struct RefCPUState {
  uint32_t pc;
  uint32_t gpr[32];
  uint32_t mcycle_lo;
  uint32_t mcycle_hi;
};

/* SoC 上程序所在的地址 —— 镜像要写进 REF 的这个位置 */
static const uint32_t SOC_IMG_BASE = 0x20000000u;

static RefCPUState ref_cpu = {};
static bool        diff_failed = false;
static void       *ref_handle  = nullptr;

static void (*ref_difftest_memcpy)(uint32_t, void*, size_t, bool) = nullptr;
static void (*ref_difftest_regcpy)(void*, bool) = nullptr;
static void (*ref_difftest_exec)(uint64_t) = nullptr;
static void (*ref_difftest_raise_intr)(uint64_t) = nullptr;

/* ── ① 加载 REF 共享库, 解析 4 个 API 符号 ── */
static void load_ref_so(const char *path)
{
  ref_handle = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
  if (ref_handle == nullptr) {
    fprintf(stderr, "difftest: dlopen %s 失败: %s\n", path, dlerror());
    abort();
  }

  ref_difftest_memcpy     = reinterpret_cast<void(*)(uint32_t,void*,size_t,bool)>(dlsym(ref_handle, "difftest_memcpy"));
  ref_difftest_regcpy     = reinterpret_cast<void(*)(void*,bool)>(dlsym(ref_handle, "difftest_regcpy"));
  ref_difftest_exec       = reinterpret_cast<void(*)(uint64_t)>(dlsym(ref_handle, "difftest_exec"));
  ref_difftest_raise_intr = reinterpret_cast<void(*)(uint64_t)>(dlsym(ref_handle, "difftest_raise_intr"));
  auto ref_init           = reinterpret_cast<void(*)(int)>(dlsym(ref_handle, "difftest_init"));

  if (!ref_difftest_memcpy || !ref_difftest_regcpy ||
      !ref_difftest_exec   || !ref_difftest_raise_intr || !ref_init) {
    fprintf(stderr, "difftest: %s 里缺少 difftest_* 符号\n", path);
    abort();
  }

  ref_init(1234);   // NEMU 侧初始化(端口参数, 无实际作用)
}

/* ── ② 初始化: 同步内存 + 同步寄存器 ── */
void difftest_init(VysyxSoCFull *top, const char *img_path)
{
  ref_cpu = {};
  diff_failed = false;

  // ① 加载 ref.so
  load_ref_so("./build/ref.so");  //mk 拷贝nemu镜像的操作 

  // ② 内存: 把 .bin 原样写进 REF 的 MROM 地址
  //    (SoC 的 DUT 内存在 RTL 里, 没有 C++ 侧快照可拷, 只能喂镜像本身)
  FILE *fp = fopen(img_path, "rb");
  if (fp == nullptr) { fprintf(stderr, "difftest: 打不开镜像 %s\n", img_path); abort(); }
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  uint8_t *buf = new uint8_t[size];
  size_t rd = fread(buf, 1, size, fp);
  fclose(fp);
  ref_difftest_memcpy(SOC_IMG_BASE, buf, rd, DIFFTEST_TO_REF);
  delete[] buf;

  // ③ 寄存器: 让 REF 和 DUT 站在同一起跑线
  RefCPUState dut_init = {};
  dut_init.pc = cpu_pc(top);
  cpu_get_gprs(top, dut_init.gpr);
  ref_difftest_regcpy(&dut_init, DIFFTEST_TO_REF);
}

static void checkregs(const RefCPUState &ref, uint32_t dut_pc, const uint32_t *dut_gpr)
{
  if (ref.pc != dut_pc) 
  {
    fprintf(stderr,
      "PC 不同: at pc = 0x%08x, REF = 0x%08x, DUT = 0x%08x, diff = 0x%08x\n",
      dut_pc, ref.pc, dut_pc, ref.pc ^ dut_pc);
    diff_failed = true;
    return;
  }

  for (int i = 0; i < 32; i++) 
  {
    if (ref.gpr[i] != dut_gpr[i]) 
    {
      fprintf(stderr,
        "REG x%02d 不同: at pc = 0x%08x, REF = 0x%08x, DUT = 0x%08x, diff = 0x%08x\n",
        i, dut_pc, ref.gpr[i], dut_gpr[i], ref.gpr[i] ^ dut_gpr[i]);
      diff_failed = true;
      return;
    }
  }
}

bool difftest_step(uint32_t dut_pc, const uint32_t *dut_gpr)
{
  if (diff_failed) return false;                   // ① 已经失败就别再比了

  ref_difftest_exec(1);                            // ② ★ REF 执行一条
  ref_difftest_regcpy(&ref_cpu, DIFFTEST_TO_DUT);  // ③ 读回 REF 的 pc/gpr
  checkregs(ref_cpu, dut_pc, dut_gpr);             // ④ 比对

  return !diff_failed;
}

bool          difftest_ok(void)   { return !diff_failed; }

#else   /* 没开 difftest */

void difftest_init(VysyxSoCFull *top, const char *img_path) 
{ 
    (void)top; (void)img_path; 
}
bool difftest_step(uint32_t dut_pc, const uint32_t *dut_gpr) 
{
  (void)dut_pc; (void)dut_gpr; return true;
}
bool          difftest_ok(void)   { return true; } // 没开就恒true
#endif
