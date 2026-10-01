#include "soc_tb.h"

#include <cassert>          // 桩函数里用的 assert
#include <cstdio>
#include <cstdlib>          //abort
#include <cstdint>          // uint32_t / uint8_t

static const uint32_t MROM_BASE = 0x20000000u;
static size_t mrom_size = 0;
static  uint8_t mrom_img[4096];

volatile int mrom_count       = 0;   // ← 原来 static, 现在 main 要打印它
int          ebreak_triggered = 0;   
uint32_t     ebreak_addr      = 0;


extern "C" void flash_read(int addr, int *data) { (void)addr; *data = 0; assert(0); }
extern "C" void mrom_read (int addr, int *data) 
{ 
  mrom_count++;  
  // printf("[ifetch] 0x%08x\n", (uint32_t)addr);  //打印当前指令   
  
  if (mrom_count == 1) printf("Soc visit mrom (first)\n");
  uint32_t off = uint32_t(addr) - MROM_BASE;
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
