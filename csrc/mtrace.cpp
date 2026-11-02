// mtrace.cpp — 记录每条 load/store 的地址与属性
// 记录格式: 8 字节 [addr:32][flags:32]
//   flags bit0     = is_write
//   flags bit[3:1] = size (0=byte, 1=half, 2=word)
#include <cstdio>
#include <cstdint>

static FILE *g_fp = nullptr;
static unsigned long long g_n = 0;

extern "C" {

void mtrace_open(const char *path)
{
  if (path == nullptr) return;
  g_fp = fopen(path, "wb");
  if (g_fp == nullptr) { perror("mtrace_open"); return; }
  static char buf[1 << 20];
  setvbuf(g_fp, buf, _IOFBF, sizeof(buf));
  printf("[mtrace] logging to %s\n", path);
}

void mtrace_close(void)
{
  if (g_fp) {
    fclose(g_fp);
    g_fp = nullptr;
    printf("[mtrace] %llu records\n", g_n);
  }
}

void mtrace_log(int addr, int val, int is_write, int size)
{
  (void)val;
  if (g_fp == nullptr) return;
  uint32_t rec[2];
  rec[0] = (uint32_t)addr;
  rec[1] = ((uint32_t)is_write & 1u) | (((uint32_t)size & 7u) << 1);
  fwrite(rec, sizeof(rec), 1, g_fp);
  g_n++;
}

} // extern "C"
