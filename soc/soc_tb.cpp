#include "VysyxSoCFull.h"   // Verilator 生成的模型类
#include "VysyxSoCFull___024root.h"  // 内部信号
#include "verilated.h"      // Verilated::commandArgs / eval / vluint64_t
#include <cassert>          // 桩函数里用的 assert
#include <cstdio>
#include <cstdlib>          //abort
#include <cstdint>          // uint32_t / uint8_t


static const uint32_t MROM_BASE = 0x20000000u;
static volatile int mrom_count = 0;   // MROM 被访问次数(被 DPI 回调改, 用 volatile)
static size_t mrom_size = 0;
static  uint8_t mrom_img[4096];

static int ebreak_triggered;
static uint32_t ebreak_addr;

extern "C" void flash_read(int addr, int *data) { (void)addr; *data = 0; assert(0); }
extern "C" void mrom_read (int addr, int *data) 
{ 
  mrom_count++;                                // 计数 +1
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
static void load_mrom(const char *path)
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


static void gpio_init(VysyxSoCFull *top)
// SoC 顶层 ysyxSoCFull 有输入引脚（externalPins_gpio_in、ps2_clk、ps2_data、uart_rx…）。
// 真实芯片里，这些引脚连着外部器件（按钮、键盘、串口线）。
// 仿真里没有"外部世界"——你的 tb 就要扮演外部世界，把每根输入引脚拉到一个确定的值：
{
   // 1) 输入打桩 (避免未赋值 = 0, 尤其 uart_rx 空闲应为 1)
  top->externalPins_gpio_in  = 0;
  top->externalPins_ps2_clk  = 0;
  top->externalPins_ps2_data = 0;
  top->externalPins_uart_rx  = 1;
}

static void tick(VysyxSoCFull *top) 
{
  top->clock = 0; top->eval();   // 前半拍
  top->clock = 1; top->eval();   // 后半拍: 上升沿
}

static void reset_circuit(VysyxSoCFull *top)
{
    top->reset = 1;
    for(int i = 0; i < 15; i++) //复位信号 要至少10拍
    {
        tick(top);
    }
    top->reset = 0;
    top->clock = 0;
    top->eval();
}
static inline uint32_t cpu_a0(VysyxSoCFull *top) 
{
  return top->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__u_core__DOT__u_regfile__DOT__rf[10];  // a0 = x10
}

int main(int argc, char *argv[]) 
{
  Verilated::commandArgs(argc, argv);   // 讲义第10条: 让 verilator 能解析 plusargs
  const char *img_path = "test/char-test.bin";
  for (int i = 1; i < argc; i++) 
  {
    if (argv[i][0] != '-' && argv[i][0] != '+') { img_path = argv[i]; break; }
  }
  load_mrom(img_path);
  VysyxSoCFull *top = new VysyxSoCFull;
  gpio_init(top);
  reset_circuit(top);

    // 主循环: 跑满 MAX_CYC 拍(不再因"命中即停", 否则看不到计数)
  const long MAX_CYC = 20000000;
  for (long i = 0; i < MAX_CYC; i++)
  {
    tick(top);
    // if (i % 10000 == 0) printf("[soc_tb] cycle %ld\n", i);
    if(ebreak_triggered)  break;
  }
  printf("\n[soc_tb] ==== 结束 ====\n");
  printf("[soc_tb] ebreak@0x%08x\n",ebreak_addr);
  printf("[soc_tb] MROM 访问次数 = %d\n", mrom_count);

  uint32_t code = cpu_a0(top);      //  先读
  printf("[soc_tb] 退出码 = %u\n", code);
  delete top;                       //  再释放
  return (int)code ;

}

