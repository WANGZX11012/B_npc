//处理经过axi lite总线后的信号 包括一些地址 数据 valid ready信号

module axi_xbar(
    //── m_* = 上游 axi_lite_master 侧 ──
    //master 把 arbiter 的简单请求(req_*)翻译成 AXI 五通道后喂给 xbar，
    //xbar 再按地址把请求路由到下面三个从口之一。
    //ar
    input [31:0]            m_araddr,
    input                   m_arvalid,
    output                  m_arready,
    //r
    output [31:0]           m_rdata,
    output [1:0]            m_rresp,
    output                  m_rvalid,
    input                   m_rready,
    //aw：写地址（master 发地址+valid，从设备回 ready）
    input [31:0]            m_awaddr,   // 你已有
    input                   m_awvalid,  // master 发
    output                  m_awready,  // 从设备回
    //w：写数据
    input [31:0]            m_wdata,    // master 发
    input [3:0]             m_wmask,    // master 发（字节使能，不是 wstrb）
    input                   m_wvalid,   // master 发
    output                  m_wready,   // 从设备回
    //b：写响应（从设备回应答，master 发 ready）
    output [1:0]            m_bresp,    // 从设备回
    output                  m_bvalid,   // 从设备回
    input                   m_bready,   // master 发

    //================== 从端 dmem_*：内存（完整 5 通道）==================
    output [31:0]           mem_araddr,
    output                  mem_arvalid,
    input                   mem_arready,
    input [31:0]            mem_rdata,
    input [1:0]             mem_rresp,
    input                   mem_rvalid,
    output                  mem_rready,
    output [31:0]           mem_awaddr,
    output                  mem_awvalid,
    input                   mem_awready,
    output [31:0]           mem_wdata,
    output [3:0]            mem_wmask,
    output                  mem_wvalid,
    input                   mem_wready,
    input [1:0]             mem_bresp,
    input                   mem_bvalid,
    output                  mem_bready,

    //================== 从端 uart_*：串口（完整 5 通道）==================
    output [31:0]           uart_araddr,
    output                  uart_arvalid,
    input                   uart_arready,
    input [31:0]            uart_rdata,
    input [1:0]             uart_rresp,
    input                   uart_rvalid,
    output                  uart_rready,
    output [31:0]           uart_awaddr,
    output                  uart_awvalid,
    input                   uart_awready,
    output [31:0]           uart_wdata,
    output [3:0]            uart_wmask,
    output                  uart_wvalid,
    input                   uart_wready,
    input [1:0]             uart_bresp,
    input                   uart_bvalid,
    output                  uart_bready,

    //================== 从端 rtc_*：RTC（只读，只有 ar/r 通道）==================
    output [31:0]           rtc_araddr,
    output                  rtc_arvalid,
    input                   rtc_arready,
    input [31:0]            rtc_rdata,
    input [1:0]             rtc_rresp,
    input                   rtc_rvalid,

    //================== 输出给 core 的 MMIO 标记 ==================
    output                  mmio_sel
);

 wire ar_uart = (m_araddr[31:4] == 28'ha00003f);  //读到串口
 wire ar_rtc = (m_araddr[31:8] == 24'ha00000);
 wire ar_mem = (m_araddr[31:24] >= 8'h80) && (m_araddr[31:24] <=8'h87);

 wire aw_uart = (m_awaddr[31:4] == 28'ha00003f);  //写
 wire aw_rtc = (m_awaddr[31:8] == 24'ha00000);
 wire aw_mem = (m_awaddr[31:24] >= 8'h80) && (m_awaddr[31:24] <=8'h87);

 assign mem_arvalid = ar_mem && m_arvalid;
 assign uart_arvalid = ar_uart && m_arvalid;
 assign rtc_arvalid = ar_rtc && m_arvalid;

 assign mem_awvalid = aw_mem && m_awvalid;
 assign uart_awvalid = aw_uart && m_awvalid;
//  assign rtc_awvalid = aw_rtc && m_awvalid;
assign mem_wvalid   = aw_mem  && m_wvalid;
assign uart_wvalid  = aw_uart && m_wvalid;

//──── 读地址广播 ────
assign mem_araddr  = m_araddr;
assign uart_araddr = m_araddr;
assign rtc_araddr  = m_araddr;
//──── 写地址广播 ────
assign mem_awaddr  = m_awaddr;
assign uart_awaddr = m_awaddr;
//──── 写数据广播（字节使能 wmask 也要广播）────
assign mem_wdata   = m_wdata;
assign uart_wdata  = m_wdata;
assign mem_wmask   = m_wmask;
assign uart_wmask  = m_wmask;
//──── master 的 ready 广播（谁被选中谁才用它）────
assign mem_rready  = m_rready;
assign uart_rready = m_rready;
assign mem_bready  = m_bready;
assign uart_bready = m_bready;
 
//输出信号 和axi交互的东西 也就是xbar是axi和从设备的桥梁
assign m_arready = ar_uart ? uart_arready : ar_rtc ? rtc_arready : ar_mem ? mem_arready : 1'b1;
assign m_rvalid  = ar_uart ? uart_rvalid  : ar_rtc ? rtc_rvalid  : ar_mem ? mem_rvalid  : 1'b1;
assign m_rdata   = ar_uart ? uart_rdata   : ar_rtc ? rtc_rdata   : ar_mem ? mem_rdata   : 32'b0;
assign m_rresp   = ar_uart ? uart_rresp   : ar_rtc ? rtc_rresp   : ar_mem ? mem_rresp   : 2'b11;

assign m_awready = aw_uart ? uart_awready : aw_mem ? mem_awready : 1'b1;
assign m_wready  = aw_uart ? uart_wready  : aw_mem ? mem_wready  : 1'b1;
assign m_bvalid  = aw_uart ? uart_bvalid  : aw_mem ? mem_bvalid  : 1'b1;
assign m_bresp   = aw_uart ? uart_bresp   : aw_mem ? mem_bresp   : 2'b11; //11：DECERR 10：SLVERR 00：OKAY 01：EXOKAY

//difftest跳过标记
assign mmio_sel = ar_uart || ar_rtc || aw_uart || aw_rtc;


endmodule
