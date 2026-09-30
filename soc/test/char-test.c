#define UART_BASE 0x10000000
#define UART_TX 0 //发送的偏移

//在裸机（bare-metal）环境中，没有操作系统帮你调用 main()
// CPU 复位后，PC 指向的起始地址最终会跳转到 _start
void _start()
{
    // *(volatile char*)0x0f002000 = 1;   // ★ 临时: 写穿 SRAM 边界, 验完删
    *(volatile char*)0xA0000000 = 1;   // ★ 临时: 故意写未映射地址, 验完删掉
    *(volatile char*)(UART_BASE + UART_TX) = 'A';  //sb指令 soc里面的uart rtl实现打印
    *(volatile char*)(UART_BASE + UART_TX) = 'c';  //sb指令 soc里面的uart rtl实现打印
    // 直接将串口发送队列中的字符打印出来。  uart tfifo
    //不用外接一个真的串口接收器，就能在终端看到 CPU 送出的字节。

    // 把 'A'（ASCII 码 0x41）写入地址 0x10000000。 最前面那个是解引用
    // *(volatile char*)(UART_BASE + UART_TX) = '\n';
    while(1);//进入 while(1) 死循环，CPU 停止工作
}

