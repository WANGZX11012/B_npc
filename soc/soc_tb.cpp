
#include "verilated.h"      // Verilated::commandArgs / eval / vluint64_t
#include "soc_tb.h"
#include "soc_difftest.h"

#include <cassert>          // 桩函数里用的 assert
#include <cstdio>
#include <cstdlib>          //abort
#include <cstdint>          // uint32_t / uint8_t

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

static void init_all(VysyxSoCFull * top ,const char* img_path)
{
  cpu_dbg_init(); // 设定scope 作用域
  gpio_init(top);
  reset_circuit(top);
  difftest_init(top, img_path);
}



int main(int argc, char *argv[]) 
{
  Verilated::commandArgs(argc, argv);   // 讲义第10条: 让 verilator 能解析 plusargs
  const char *img_path = "test/char-test.bin";

  uint32_t cpu_gprs[32];

  for (int i = 1; i < argc; i++) 
  {
    if (argv[i][0] != '-' && argv[i][0] != '+') { img_path = argv[i]; break; }
  }
  load_mrom(img_path);
  VysyxSoCFull *top = new VysyxSoCFull;
  init_all(top, img_path);

    // 主循环: 跑满 MAX_CYC 拍(不再因"命中即停", 否则看不到计数)
  const long MAX_CYC = 20000000;
  for (long i = 0; i < MAX_CYC; i++)
  {
    tick(top);
    
    // if (i % 10000 == 0) printf("[soc_tb] cycle %ld\n", i);
    if(ebreak_triggered)  break;
    #if ENABLE_DIFFTEST
      if (cpu_inst_retire(top))                      // 用"写完了"的那个, 不是"要写了"的
      {
        cpu_get_gprs(top, cpu_gprs);
        cpu_gprs[5] = 1;
        if (!difftest_step(cpu_pc(top), cpu_gprs))
        {
          printf("[soc_tb] DIFFTEST 不一致, 停止\n");
          break;
        }
      }
  #endif
  }

  
  printf("\n[soc_tb] ==== 结束 ====\n");
  printf("[soc_tb] ebreak@0x%08x\n",ebreak_addr);
  printf("[soc_tb] MROM 访问次数 = %d\n", mrom_count);

  cpu_get_gprs(top, cpu_gprs);
  uint32_t cpu_a0 = cpu_gprs[10];
  printf("[soc_tb] 退出码 = %u\n", cpu_a0);
  delete top;                       //  再释放
  
  return difftest_ok() ? (int)cpu_a0 : 1;                  // 关掉时恒 true

}

