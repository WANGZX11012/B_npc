// ============================================================================
// NPC (多周期) DiffTest 模块
//
// 职责: 加载 REF (NEMU 编译的 .so), 每条指令完成后比对 PC + GPR.
//
// 与单周期的差异 (多周期适配):
//   1. 内存同步: DPI_MEM 模式下 DUT 物理内存在 C++ 侧的 pmem_words[] (见 dpic_mem.cpp),
//      是独立真相. 先把 .bin 载进 DUT, 再用 dpi_pmem_copy_out 把 DUT 内存同步给 REF,
//      这样比对的是"两份独立内存", 而非 DUT 借用 REF 内存(那等于自己比自己).
//   2. 检查时机: 多周期一条指令跨多个周期, 必须等一条指令执行完
//      (ctrl 状态回到 FET) 才调用 difftest_step.
//   3. MMIO skip: 多周期没有 DPI-C 访存, 改为读 RTL 暴露的 mmio_dbg.
//
// 寄存器传递格式 (与 NEMU ref.c 约定一致): 35 个 uint32_t
//   [0]=pc, [1..32]=gpr[0..31], [33]=mcycle_lo, [34]=mcycle_hi
// 注意: 不做 CSR 的 difftest! mcycle 字段保留仅因 ref.c 的 regcpy 固定
//       访问 r[33]/r[34], 若不保留会越界. 我们始终填 0, 不读取/比对.
// ============================================================================

#include "difftest.h"
#include "npc.h"
#include "dpic_mem.h"   // dpic_mem_read/dpic_mem_write 的声明(后端实现已迁到 dpic_mem.cpp)

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <dlfcn.h>

#include <difftest-def.h>  // DIFFTEST_TO_REF, DIFFTEST_TO_DUT

// ── 寄存器传递格式 (与 NEMU ref.c 约定一致) ─────────────────────────────
// 这块内存就是 NEMU regcpy 里 uint32_t r[35] 扁平数组的"带名字视图":
//   RefCPUState         等价于  uint32_t r[35]
//   .pc                 等价于  r[0]   (IDX_PC)
//   .gpr[0..31]         等价于  r[1..32] (IDX_GPR+0..31)
//   .mcycle_lo          等价于  r[33]  (IDX_MCYCLE_LO)
//   .mcycle_hi          等价于  r[34]  (IDX_MCYCLE_HI)
// 全是 uint32, 无 padding, 布局逐字节一致; regcpy 把它强转成 (uint32_t*)访问。
struct RefCPUState {
  uint32_t pc;          // 等价于 r[0]
  uint32_t gpr[32];     // 等价于 r[1..32]
  uint32_t mcycle_lo;   // 等价于 r[33], 不做 CSR difftest, 恒 0 (仅为对齐 ref.c 布局)
  uint32_t mcycle_hi;   // 等价于 r[34], 不做 CSR difftest, 恒 0
};

// ── 全局状态 ────────────────────────────────────────────────────────────
static RefCPUState ref_cpu = {};
static bool diff_failed = false;
static void *ref_handle = nullptr;

// ── REF 导出函数的函数指针 ──────────────────────────────────────────────
// 注意: 不再加 static, 供 dpic_mem.cpp 通过 extern 引用同一个 NEMU memcpy 指针。
void (*ref_difftest_memcpy)(uint32_t addr, void *buf, size_t n, bool direction) = nullptr;
static void (*ref_difftest_regcpy)(void *dut, bool direction) = nullptr;
static void (*ref_difftest_exec)(uint64_t n) = nullptr;
static void (*ref_difftest_raise_intr)(uint64_t NO) = nullptr;

// ── 物理内存基址 (与 NEMU 的 CONFIG_MBASE 一致) ─────────────────────────
static const uint32_t MEM_BASE = 0x80000000u;

#ifndef ENABLE_DIFFTEST
#define ENABLE_DIFFTEST 0
#endif

// ============================================================================
// load_image_bin — 把 .bin 镜像载入 DUT 物理内存 (pmem_words[]), 并(若开 difftest)同步 REF
// 本函数无条件可用: DPI_MEM 模式下 DUT 物理内存在 C++ 侧 pmem_words[],
// 必须有镜像来源, 不能依赖 difftest 开关。
// ============================================================================
static void load_image_bin(const char *img_path)
{
  if (img_path == nullptr || img_path[0] == '\0') return;

  FILE *fp = fopen(img_path, "rb");
  if (fp == nullptr) {
    std::fprintf(stderr, "difftest: cannot open image %s\n", img_path);
    abort();
  }

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  if (size <= 0) { fclose(fp); return; }

  uint8_t *buf = new uint8_t[size];
  size_t rd = fread(buf, 1, size, fp);
  fclose(fp);

  if (rd > 0) {
    // ① 先把镜像载进 DUT 自己的 pmem_words[] (DUT 内存真相, 无条件执行)
    dpi_load_bin(buf, (size_t)rd);
#if ENABLE_DIFFTEST
    // ② 再把 DUT 内存拷出, 同步给 REF (NEMU pmem). 方向: DUT -> REF
    uint8_t *out = new uint8_t[rd];
    dpi_pmem_copy_out(out, (size_t)rd);
    ref_difftest_memcpy(MEM_BASE, out, rd, DIFFTEST_TO_REF);
    delete[] out;
#endif
  }
  delete[] buf;
}

#if ENABLE_DIFFTEST

// ============================================================================
// load_ref_so — 动态加载 REF 共享库, 解析所有 API 符号
// (dpic_mem_read/dpic_mem_write 已迁至 csrc/dpic_mem.cpp, 复用本文件解析的
//  ref_difftest_memcpy 指针, 通过 extern 共享, 不在此重复定义)
// ============================================================================
static void load_ref_so(const char *ref_so_path)
{
  ref_handle = dlopen(ref_so_path, RTLD_LAZY | RTLD_LOCAL);
  //把 NEMU 编译成的共享库动态加载进当前 Vtop 进程。

  if (ref_handle == nullptr)
  {
    std::fprintf(stderr, "Failed to open %s: %s\n", ref_so_path, dlerror());
    abort();
  }

  //从 so 里取出 5 个导出函数地址,赋给你全局的函数指针变量(ref_difftest_exec 等)。
  //之后 C++ 侧调 ref_difftest_exec(1) 就是直接跳进 NEMU 的 difftest_exec 函数体执行。 前面有声明
  ref_difftest_memcpy      = reinterpret_cast< void (*)(uint32_t, void*, size_t, bool) > (dlsym(ref_handle, "difftest_memcpy"));
  //在nemu的ref.c里，把.bin文件放到nemu的pmem 保证执行是一样的程序

  ref_difftest_regcpy      = reinterpret_cast< void (*)(void*, bool) > (dlsym(ref_handle, "difftest_regcpy"));
  //有两个方向 to ref是把npc写进，nemu 让nemu跟上状态（init和访问mmio需要用到） 每条指令执行后是把正确答案存到r数组交给npc比较

  ref_difftest_exec        = reinterpret_cast< void (*)(uint64_t) > (dlsym(ref_handle, "difftest_exec"));
  //指令执行传入cpu pc 驿马后写回 更新gpr

  ref_difftest_raise_intr  = reinterpret_cast< void (*)(uint64_t) > (dlsym(ref_handle, "difftest_raise_intr"));
  //暂时没用

  auto ref_difftest_init   = reinterpret_cast< void (*)(int) > (dlsym(ref_handle, "difftest_init"));//因为只用一次 没必要全局变量

  assert(ref_difftest_memcpy     != nullptr);//检查是否传入
  assert(ref_difftest_regcpy     != nullptr);
  assert(ref_difftest_exec       != nullptr);
  assert(ref_difftest_raise_intr != nullptr);
  assert(ref_difftest_init       != nullptr);

  ref_difftest_init(1234);
}

// ============================================================================
// checkregs — 逐寄存器比对 REF 和 DUT
// ============================================================================
static void checkregs(const RefCPUState &ref, uint32_t dut_pc, uint32_t dut_inst, const uint32_t *dut_gpr)
{
  // ebreak (nemu_trap): 程序终止, DUT PC 停在原地, REF PC 已 +4,
  // 两边对终止指令的 PC 语义允许不同, 跳过 PC 比对
  bool is_ebreak = (dut_inst == 0x00100073);

  // PC 比对
  if (!is_ebreak && ref.pc != dut_pc) 
  {
    std::fprintf(stderr,
      "pc is different after executing instruction 0x%08x at pc = 0x%08x, right = 0x%08x, wrong = 0x%08x, diff = 0x%08x\n",
      dut_inst, dut_pc, ref.pc, dut_pc, ref.pc ^ dut_pc);
    diff_failed = true;
    return;
  }

  // 跳过 csrr mcycle/mcycleh 的 GPR 比对（mcycle 值不一致，不比对）
  uint32_t csr_addr = (dut_inst >> 20) & 0xFFF;
  int skip_rd = -1;
  if (csr_addr == 0xB00 || csr_addr == 0xB80) {
    skip_rd = (dut_inst >> 7) & 0x1F;
  }

  // 32 个 GPR 比对
  for (int i = 0; i < 32; i++) 
  {
    if (i == skip_rd) continue;
    if (ref.gpr[i] != dut_gpr[i])
    {
      std::fprintf(stderr,
    "x%d is different after executing instruction 0x%08x at pc = 0x%08x, right = 0x%08x, wrong = 0x%08x, diff = 0x%08x\n",
        i, dut_inst, dut_pc, ref.gpr[i], dut_gpr[i], ref.gpr[i] ^ dut_gpr[i]);
      diff_failed = true;
      return;
    }
  }
}

// ============================================================================
// difftest_init — 初始化 DiffTest (NPC 主程序启动时调用一次)
// ============================================================================
void difftest_init(uint32_t dut_pc, const char *img_path)
{
  ref_cpu = {};
  diff_failed = false;

  // ① 加载 REF .so, 解析 API 符号, 调用 ref_difftest_init()
  load_ref_so("./build/ref.so");

  // ② 内存同步: :把 .bin 字节拷给 NEMU 的 pmem,让 REF 内存和 NPC 的 inst_mem 内容一致。
  load_image_bin(img_path);

  // ③ 寄存器同步: 把 NPC 复位后的初始 PC 和 32 个 GPR 通过 regcpy(→REF) 同步给 NEMU。
  //这一步保证 REF 和 DUT 站在同一起跑线:PC 都是 0x80000000,GPR 都是 0。
  //   dut_init.pc = dut_pc;     等价于  r[0]     = dut_pc;   (NEMU 读 r[0]→cpu.pc)
  //   npc_get_gprs(dut_init.gpr);等价于  r[1..32] = gpr[0..31]; (NEMU 读 r[1..32]→cpu.gpr[])
  RefCPUState dut_init = {};
  dut_init.pc = dut_pc;
  npc_get_gprs(dut_init.gpr);
  ref_difftest_regcpy(&dut_init, DIFFTEST_TO_REF);
}

// ============================================================================
// difftest_step — 每条指令完成后调用一次: REF 执行 1 条, 然后比对
// ============================================================================
bool difftest_step(uint32_t dut_pc, uint32_t dut_inst, const uint32_t *dut_gpr)
{
  if (diff_failed) return false;  // 已经失败, 不再继续

  // MMIO 指令: 跳过 REF 执行, 直接同步 DUT → REF (RTL 的 mmio_dbg 指示)
  if (npc_get_mmio())
  {
    RefCPUState dut_state = {};   // 不做 CSR difftest, mcycle 恒 0
    //   dut_state.pc = dut_pc;              等价于  r[0]     = dut_pc;
    //   dut_state.gpr[i] = dut_gpr[i];     等价于  r[1..32] = dut_gpr[0..31];
    // NEMU 把 r[0..32] 读进 cpu.pc/cpu.gpr, 让 REF 寄存器跟上 DUT (单向同步, 不比对)
    dut_state.pc = dut_pc;
    for (int i = 0; i < 32; i++) dut_state.gpr[i] = dut_gpr[i];
    ref_difftest_regcpy(&dut_state, DIFFTEST_TO_REF);
    return true;
  }

  // ① REF 执行一条指令
  ref_difftest_exec(1);

  // ② 读回 REF 的寄存器: NEMU 把 cpu.pc/cpu.gpr 写进 r[0..32]
  //   ref_cpu.pc        等价于  r[0]     (NEMU 写回的 PC)
  //   ref_cpu.gpr[i]    等价于  r[1..32] (NEMU 写回的 GPR)
  // 随后 checkregs 按结构体成员读 ref_cpu.pc / ref_cpu.gpr[i] 与 DUT 比对
  ref_difftest_regcpy(&ref_cpu, DIFFTEST_TO_DUT);

  // ③ 逐寄存器比对
  checkregs(ref_cpu, dut_pc, dut_inst, dut_gpr);

  return !diff_failed;
}
#else

// 没启用 difftest 时, 仍需把镜像载进 DUT 自己的 pmem_words[] (dpic 内存真相)
void difftest_init(uint32_t dut_pc, const char *img_path)
{
  (void)dut_pc;
  load_image_bin(img_path);
}

bool difftest_step(uint32_t dut_pc, uint32_t dut_inst, const uint32_t *dut_gpr)
{
  (void)dut_pc; (void)dut_inst; (void)dut_gpr;
  return true; // always succeed when difftest disabled
}

#endif
