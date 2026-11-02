#include <cstdio> //<cxxx> 系列的头文件只保证将符号放入 std:: 命名空间
#include <cstdint>
#include <cstdlib>   // std::atoi, std::strtol 等
#include "../include/generated/autoconf.h"  // cache参数 与npc的一致
#include <vector>
#include <cstring>


#ifndef CONFIG_ICACHE_INDEX_BITS
  #define CONFIG_ICACHE_INDEX_BITS 4      // 没跑过 menuconfig 时的兜底
#endif
#ifndef CONFIG_ICACHE_BLOCK_BYTES
  #define CONFIG_ICACHE_BLOCK_BYTES 4     // 同上
#endif


static std::vector<uint32_t> tag;
static std::vector<uint8_t> valid;





// 用给定参数跑一遍 trace, 返回 miss 次数; n_acc 带出访问次数
static long long sim_icache(std::FILE *fp, int off_bits, int idx_bits, int nblk, long long &n_acc, int shift)
{
  tag.assign(nblk, 0);
  valid.assign(nblk, 0);
  std::rewind(fp);                        // ★ 关键: 每次从头读

  long long miss = 0;
  n_acc = 0;

  uint32_t pc;
  while (std::fread(&pc, sizeof(pc), 1, fp) == 1)
  {
    ++n_acc;
    pc += (uint32_t)shift; 
    uint32_t idx = (pc >> off_bits) & (nblk - 1);
    uint32_t tg  = pc >> (off_bits + idx_bits);
    if (!valid[idx] || tag[idx] != tg)
    {
      valid[idx] = 1;
      tag[idx]   = tg;
      ++miss;
    }
  }
  return miss;
}

// 用给定参数跑一遍 mtrace, 返回 miss 次数; n_acc 带出访问次数
// 记录格式: 8 字节 [addr:32][flags:32]
static long long sim_dcache(std::FILE *fp, int off_bits, int idx_bits, int nblk, long long &n_acc)
{
  tag.assign(nblk, 0);
  valid.assign(nblk, 0);
  std::rewind(fp);                    // 每次从头读

  long long miss = 0;
  n_acc = 0;

  uint32_t rec[2];
  while (std::fread(rec, sizeof(rec), 1, fp) == 1)
  {
    uint32_t addr  = rec[0];
    uint32_t flags = rec[1];
    (void)flags;                      // bit0=is_write, 现在等价 write-allocate

    ++n_acc;
    uint32_t idx = (addr >> off_bits) & (nblk - 1);
    uint32_t tg  = addr >> (off_bits + idx_bits);

    if (!valid[idx] || tag[idx] != tg)
    {
      valid[idx] = 1;
      tag[idx]   = tg;
      ++miss;
    }
  }
  return miss;
}




int main(int argc, char **argv)
{
  if (argc < 2) { std::fprintf(stderr, "usage: %s <trace.bin>\n", argv[0]); return 1; }

  // 两条 trace 的路径, 对称命名; 谁用谁 fopen
  const char *ifu_path = argv[1];                  // itrace: 4 字节/条
  const char *lsu_path = std::getenv("LSU_TRACE"); // mtrace: 8 字节/条
  if (lsu_path == nullptr) lsu_path = "build/mtrace.bin";
 
 // 默认参数: 与 RTL 同源 (autoconf.h), 后面可由命令行覆盖
  int IDX_BITS = CONFIG_ICACHE_INDEX_BITS;
  int NBLK     = 1 << IDX_BITS;
  int OFF_BITS = 0;
  while ((1 << OFF_BITS) < CONFIG_ICACHE_BLOCK_BYTES) ++OFF_BITS;   // 4B→2, 16B→4

  int BLK      = 1 << OFF_BITS;

    // ── 扫描模式: ./cachesim <trace> --sweep ──
  if (argc > 2 && std::strcmp(argv[2], "--sweep") == 0)
  {
    std::FILE *f = std::fopen(ifu_path, "rb");
    if (!f) { std::fprintf(stderr, "[sweep] 打不开 %s\n", ifu_path); return 1; }

    const int BLKS[]  = {4, 8, 16, 32, 64};       // 块大小(字节)
    const int NBLKS[] = {4, 8 , 16, 32, 64, 256, 1024};    // 块数

    std::printf("%-5s %-7s %-8s %12s %9s\n",
                "blk", "blocks", "size", "miss", "miss%"); //打印表头

    for (int b : BLKS)
      for (int nb : NBLKS)
      {
        int ob = 0; while ((1 << ob) < b)  ++ob;   // 字节数 → 偏移位宽
        int ib = 0; while ((1 << ib) < nb) ++ib;   // 块数   → 索引位宽
        if (ob + ib >= 32) continue;               // 防止 pc >> 32

        long long n = 0;
        long long miss = sim_icache(f, ob, ib, nb, n, 0);


        std::printf("%-5d %-7d %-8d %12lld %8.4f%%\n",
                    b, nb, b * nb, miss,
                    n ? 100.0 * miss / (double)n : 0.0);
      }

    std::fclose(f);
    return 0;
  }

    // ── 命令行覆盖: ./cachesim <trace> [blk_bytes] [blocks] ──
  if (argc > 2)
  {
    int b = std::atoi(argv[2]);
    if (b < 4 || (b & (b - 1))) { std::fprintf(stderr, "blk 必须是 >=4 的 2 的幂\n"); return 1; }
    OFF_BITS = 0;
    while ((1 << OFF_BITS) < b) ++OFF_BITS;   // ★ 用命令行传入的 b
    BLK = 1 << OFF_BITS;
  }
  if (argc > 3)
  {
    int nb = std::atoi(argv[3]);
    if (nb < 1 || (nb & (nb - 1))) { std::fprintf(stderr, "blocks 必须是 2 的幂\n"); return 1; }
    NBLK = nb;
    IDX_BITS = 0;
    while ((1 << IDX_BITS) < NBLK) ++IDX_BITS;
  }


  int SHIFT = 0;
  if (argc > 4)
    SHIFT = std::atoi(argv[4]);


  tag.assign(NBLK, 0);     // 将 tag 重置为 NBLK 个元素，全部赋值为 0
  valid.assign(NBLK, 0);   


  //   打印相关
#if defined(CONFIG_ITRACE)
  {
    std::FILE *f = std::fopen(ifu_path, "rb");
    if (!f) {
      std::fprintf(stderr, "[icache] 打不开 %s, 先跑一次开了 ITRACE 的仿真\n", ifu_path);
    } else {
      long long n = 0;
      long long miss = sim_icache(f, OFF_BITS, IDX_BITS, NBLK, n, SHIFT);
      std::fclose(f);
      std::printf("[icache] blk=%dB blocks=%d shift=%d\n", BLK, NBLK, SHIFT);
      std::printf("  access=%lld  miss=%lld  hit_rate=%.2f%%  miss_rate=%.2f%%\n",
                  n, miss,
                  n ? 100.0 * (n - miss) / n : 0.0,
                  n ? 100.0 * miss / n : 0.0);
    }
  }
#endif

#if defined(CONFIG_MTRACE)
  {
    std::FILE *f2 = std::fopen(lsu_path, "rb");
    if (!f2) {
      std::fprintf(stderr, "[dcache] 打不开 %s, 先跑一次开了 MTRACE 的仿真\n", lsu_path);
    } else {
      long long n = 0;
      long long miss = sim_dcache(f2, OFF_BITS, IDX_BITS, NBLK, n);
      std::fclose(f2);
      std::printf("[dcache] blk=%dB blocks=%d\n", BLK, NBLK);
      std::printf("  access=%lld  miss=%lld  hit_rate=%.2f%%  miss_rate=%.2f%%\n",
                  n, miss,
                  n ? 100.0 * (n - miss) / n : 0.0,
                  n ? 100.0 * miss / n : 0.0);
    }
  }
#endif

  return 0;
}
