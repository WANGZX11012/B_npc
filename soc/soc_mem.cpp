#include "soc_tb.h"

#include <cassert>          // 桩函数里用的 assert
#include <cstdio>
#include <cstdlib>          //abort
#include <cstdint>          // uint32_t / uint8_t

static const uint32_t MROM_BASE = 0x20000000u;
static size_t mrom_size = 0;
static  uint8_t mrom_img[4096];

// ── flash: 仿真模型经 DPI 来取数据, 这里扮演真实的 flash 芯片内容 ──
static uint8_t flash_img[16 * 1024 * 1024];   // 16MB 足够; 别开 256MB, 静态数组太大
static size_t  flash_size = 0;

volatile int mrom_count       = 0;   // ← 原来 static, 现在 main 要打印它
int          ebreak_triggered = 0;   
uint32_t     ebreak_addr      = 0;

extern "C" void flash_read(int addr, int *data)
{
  uint32_t off = (uint32_t)addr;              // 已经是内部偏移, 不减基址!
  if (off + 4 > flash_size) { *data = 0; return; }
  uint32_t w = (uint32_t)flash_img[off]
             | ((uint32_t)flash_img[off + 1] <<  8)
             | ((uint32_t)flash_img[off + 2] << 16)
             | ((uint32_t)flash_img[off + 3] << 24);
  
  if (w == 0x00100073u) { ebreak_triggered = 1; }   //
  *data = (int)w;
}

extern "C" void mrom_read (int addr, int *data) 
{ 
  mrom_count++;  
  // printf("[ifetch] 0x%08x\n", (uint32_t)addr);  //打印当前指令   
  
  if (mrom_count == 1) printf("Soc visit mrom (first)\n");
    uint32_t off = (uint32_t(addr) - MROM_BASE) & ~3u;
  if (mrom_size < 4 || off > mrom_size - 4) 
  {
    *data = 0;                                  // 给确定值, 避免 CPU 吃到 X
    return;
  }
  // 小端拼 32 位: 低地址 = 低位字节 (RISC-V 是小端)
  uint32_t w = (uint32_t)mrom_img[off]
             | ((uint32_t)mrom_img[off + 1] <<  8)
             | ((uint32_t)mrom_img[off + 2] << 16)
             | ((uint32_t)mrom_img[off + 3] << 24);
  *data = (int)w;

  static uint32_t last_addr = 0xFFFFFFFFu;
  if ((uint32_t)addr != last_addr) 
  {
    last_addr = (uint32_t)addr;
    // printf("[mrom] 0x%08x\n", (uint32_t)addr);
   
  }

  if((uint32_t)w == 0x00100073u)
  {
    ebreak_triggered = 1;
    ebreak_addr = (uint32_t)addr;
  }
}

void load_mrom(const char *path)
{
  FILE *fp = fopen(path, "rb");
  if(fp == nullptr)
  {
    printf("open file fail [mrom]\n");
    abort(); //core dump退出
  }
  // ★ 先看文件真实大小
  fseek(fp, 0, SEEK_END);
  long fsz = ftell(fp);
  rewind(fp);
  if (fsz > (long)sizeof(mrom_img))
    fprintf(stderr, "[mrom] ★ 镜像 %ld 字节 > MROM 的 4KB, 会被截断 %ld 字节!\n",
            fsz, fsz - (long)sizeof(mrom_img));     
  mrom_size = fread(mrom_img, 1, sizeof(mrom_img), fp);// 读到哪 每次几个字节 最多读几次(4096) 从哪里读
  //读入文件
  fclose(fp);
  printf("[mrom] 载入 %s -> %zu 字节\n", path, mrom_size);//%z 修饰size
}

void load_flash(const char *path)
{
  FILE *fp = fopen(path, "rb");
  if (fp == nullptr) { printf("[flash] open %s fail\n", path); return; }  // 没给镜像就不 abort, 反正没程序用它
  fseek(fp, 0, SEEK_END);
  long fsz = ftell(fp);
  rewind(fp);
  flash_size = fread(flash_img, 1, sizeof(flash_img), fp);
  fclose(fp);
  printf("[flash] 载入 %s -> %zu 字节\n", path, flash_size);

 /* ★ pattern 烧在保留区: flash 偏移 0x10000 = CPU 地址 0x30010000
   *   程序 bin < 64KB, 永远不会长进这块地 —— 地址写死, 一次约定永久有效 */
  for (int i = 0; i < 4096; i++)
    flash_img[0x10000 + i] = (uint8_t)(i * 0x11); //在仿真世界里等价于硬件上的 FLASH_WRITE(0x30010000 + i, data)
  if (flash_size < 0x11000)
    flash_size = 0x11000;      // ★ 关键: pattern 区也算有效内容, 否则越界检查全拦

}


