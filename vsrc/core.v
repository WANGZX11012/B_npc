`include "npc_defs.vh"
// 命名约定: 内部连线一律带"来源模块"前缀, 一眼看出信号从哪来、去哪里
//   ifu_*   IFU        输出
//   lsu_*   LSU        输出
//   arb_*   arbiter    输出
//   mst_*   axi_lite_master 输出 (含 AXI4-Lite 五通道)
//   idu_*   IDU        输出
//   rf_*    RegisterFile 输出
//   exu_*   EXU        输出
//   wbu_*   WBU        输出
//   csr_*   CSRFile    输出
//   ctrl_*  ctrl       输出
//   xbar_*  axi_xbar   输出
  //   lfsr_*  lfsr       输出
  //   exm_*   EX_MEM     输出
  //   _r 后缀 core 自己的时序锁存(mmio_flag_r)
module core (

  // Clock & Reset
  input         clk,
  input         rst,
`ifdef YSYXSOC
  // ── SoC 模式: AXI4 Master 引出到顶层 ──
  // AR 读地址通道: CPU 发地址
  output [3:0]  io_master_arid,
  output [31:0] io_master_araddr,
  output [7:0]  io_master_arlen,
  output [2:0]  io_master_arsize,
  output [1:0]  io_master_arburst,
  output        io_master_arvalid,
  input         io_master_arready,

  // R 读数据通道: 从设备回数据
  input  [3:0]  io_master_rid,
  input  [31:0] io_master_rdata,
  input  [1:0]  io_master_rresp,
  input         io_master_rlast,
  input         io_master_rvalid,
  output        io_master_rready,

  // AW 写地址通道: CPU 发地址
  output [3:0]  io_master_awid,
  output [31:0] io_master_awaddr,
  output [7:0]  io_master_awlen,
  output [2:0]  io_master_awsize,
  output [1:0]  io_master_awburst,
  output        io_master_awvalid,
  input         io_master_awready,

  // W 写数据通道: CPU 发数据
  output [31:0] io_master_wdata,
  output [3:0]  io_master_wstrb,
  output        io_master_wlast,
  output        io_master_wvalid,
  input         io_master_wready,

  // B 写响应通道: 从设备回应答
  input  [3:0]  io_master_bid,
  input  [1:0]  io_master_bresp,
  input         io_master_bvalid,
  output        io_master_bready,
`endif

  // 输出: to top / monitor
  output [31:0] pc,          // 当前 PC, IFU 直接驱动
  output        halt,        // ebreak 时拉高
  output        aborted,     // 非法指令/异常终止(对齐 NEMU_ABORT)
  output [31:0] ir_dbg,      // IR for monitor
  output [2:0]  state_dbg,   // ctrl_state for monitor
  output reg    inst_retire, // 指令完成标志
  output        mmio_dbg     // 本条指令是否访问了外设(供 difftest 跳过比对)
);



  // ═══════════════ IFU ↔ arbiter ═══════════════
  wire [31:0] ifu_pc4;          // IFU → WBU (jal/jalr 写 rd = pc+4)
  wire [31:0] ifu_npc_normal;   // IFU → 第 4 步作中断 mepc (未被中断劫持的 next pc)
  wire [31:0] ifu_inst;         // IFU → IR 
  wire        ifu_req_valid;    // IFU → arbiter (取指请求)
  wire [31:0] ifu_req_addr;     // IFU → arbiter (取指地址)
  wire        arb_ifu_done;     // arbiter → IFU (握手完成)
  wire [31:0] arb_ifu_rdata;    // arbiter → IFU (返回指令)
    // ═══════════════ IFU 握手输出 ═══════════════
  wire        ifu_out_valid;    // IFU → 手里攥着一条取回的指令
  wire [31:0] ifu_out_pc;       // IFU → 这条指令自己的 PC

  // ═══════════════ LSU ↔ arbiter ═══════════════
  wire        lsu_req_valid;    // LSU → arbiter (访存请求)
  wire [31:0] lsu_req_addr;     // LSU → arbiter (访存地址)
  wire [31:0] lsu_req_wdata;    // LSU → arbiter (store 数据)
  wire [3:0]  lsu_req_wmask;    // LSU → arbiter (字节写使能)
  wire        arb_lsu_done;     // arbiter → LSU (握手完成)
  wire [31:0] arb_lsu_rdata;    // arbiter → LSU (返回数据)
  wire [31:0] lsu_rdata;        // LSU → WBU (load 数据, 已符号/零扩展)
  wire        lsu_in_ready;     // LSU → "访存段能收新单"(!busy), 
  wire        lsu_res_valid;    // 给下游 


  // ═══════════════ arbiter ↔ axi_lite_master ═══════════════
  wire        arb_req_valid;    // arbiter → master (合并后的请求)
  wire        arb_req_we;       // arbiter → master
  wire [31:0] arb_req_addr;     // arbiter → master
  wire [31:0] arb_req_wdata;    // arbiter → master
  wire [3:0]  arb_req_wstrb;    // arbiter → master
  wire        mst_done;         // master → arbiter (传输完成)
  wire [31:0] mst_resp_rdata;   // master → arbiter (读数据)

  // ═══════════════ axi_lite_master → axi_xbar (AXI4-Lite 五通道) ═══════════════
  wire [31:0] mst_araddr, mst_awaddr, mst_wdata, mst_rdata;
  wire        mst_arvalid, mst_arready, mst_rvalid, mst_rready;
  wire [1:0]  mst_rresp;
  wire        mst_resp_err; //出错检测  
  wire        mst_awvalid, mst_awready, mst_wvalid, mst_wready;
  wire [3:0]  mst_wstrb;
  wire [1:0]  mst_bresp;
  wire        mst_bvalid, mst_bready;
  // ═══════════════ axi_master 的 AXI4 字段(第二批引到 SoC 顶层) ═══════════════
  wire [3:0]  mst_arid, mst_awid;
  wire [7:0]  mst_arlen, mst_awlen;
  wire [2:0]  mst_arsize, mst_awsize;
  wire [1:0]  mst_arburst, mst_awburst;
  wire        mst_wlast;
  // 下游从设备的身份标记: 单跑模式从设备是 AXI4-Lite(不产生这三根),
  // SoC 模式是真 AXI4(这三根由从设备给出)
  // 这三条不接: rlast 变组合 X, done 永不成立, 回归必挂
  wire        mst_rlast;
  wire [3:0]  mst_rid, mst_bid;
`ifndef YSYXSOC
  // 单跑: 内部从设备(xbar→pmem/uart/rtc/clint)是 AXI4-Lite, 不产生这三根;
  //       单拍语义下 rlast 恒 1 → done 判据退化成 rvalid
  assign mst_rlast = 1'b1;
  assign mst_rid   = 4'd0;
  assign mst_bid   = 4'd0;
`endif




  // ═══════════════ lfsr → axi_lite_master ═══════════════
  wire [7:0]  lfsr_val;         // lfsr → 停顿阈值比较
  wire        lfsr_stall;       // → axi_lite_master.stall (随机总线停顿)

  // ═══════════════ IDU → 各模块 ═══════════════
  wire [4:0]  idu_rs1;          // → RegisterFile.r_addr1
  wire [4:0]  idu_rs2;          // → RegisterFile.r_addr2
  wire [4:0]  idu_rd;           // → RegisterFile.w_addr
  wire        idu_rd_en;        // → RegisterFile.wen (与 retire 相与)
  wire [31:0] idu_imm;          // → EXU / WBU
  wire [3:0]  idu_alu_op;       // → EXU
  wire        idu_alu_en;       // → EXU
  wire        idu_alu_src2_imm; // → EXU
  wire        idu_alu_src1_pc;  // → EXU
  wire [2:0]  idu_wb_sel;       // → WBU
  wire [2:0]  idu_npc_sel;      // → IFU (next-pc 选择) / CSRFile (ecall/mret 判定)
  wire        idu_mem_re;       // → LSU
  wire        idu_mem_we;       // → LSU 
  wire [1:0]  idu_mem_width;    // → LSU
  wire        idu_mem_signed;   // → LSU
  wire [2:0]  idu_branch_type;  // → EXU
  wire        idu_invalid;      // → ctrl (非法指令)
  wire [11:0] idu_csr_idx;      // → CSRFile
  wire        idu_csr_wen;      // → CSRFile
  wire        idu_csr_s_w;      // → CSRFile (置位/原值写)

  // ═══════════════ RegisterFile / EXU / WBU ═══════════════
  wire [31:0] rf_rdata1;        // RegisterFile → EXU / CSRFile.csr_wdata
  wire [31:0] rf_rdata2;        // RegisterFile → LSU.wdata_in
  wire [31:0] exu_alu_result;   // EXU → IFU (跳转目标) / EX_MEM.result_in
  wire        exu_branch_taken; // EXU → IFU (分支成立)
  wire [31:0] wbu_wb_data;      // WBU → RegisterFile.w_data

  // ═══════════════ CSRFile → ═══════════════
  wire [31:0] csr_data;         // CSRFile → WBU (csr 读值写回 rd)
  wire [31:0] csr_mtvec;        // CSRFile → IFU (trap 入口)
  wire [31:0] csr_mepc;         // CSRFile → IFU (mret 返回地址)
  wire        csr_mstatus_mie;  // CSRFile → irq_taken 判决
  // ═══════════════ stage_dec → (纯组合相位观测, 只喂 state_dbg) ═══════════════
  wire [2:0]  state_now;        // → state_dbg


  // ═══════════════ 未用端口(保留连接, 避免 PINMISSING) ═══════════════
  wire        idu_unused_rs1_en;  // IDU → 未用
  wire        idu_unused_rs2_en;  // IDU → 未用
  wire [31:0] rf_unused_r_a0;     // RegisterFile → 未用
  // ═══════════════ axi_xbar → 各从设备(驱动侧) ═══════════════
  // mem 从口(xbar 端口叫 mem_*, 这里接到 core 的 dmem_* 线)
  wire [31:0] dmem_araddr, dmem_awaddr, dmem_wdata;
  wire [3:0]  dmem_wmask;
  wire        dmem_arvalid, dmem_rready, dmem_awvalid, dmem_wvalid, dmem_bready;
  // uart 从口
  wire [31:0] uart_araddr, uart_awaddr, uart_wdata;
  wire [3:0]  uart_wmask;
  wire        uart_arvalid, uart_rready, uart_awvalid, uart_wvalid, uart_bready;
  // rtc 从口(只读)
  wire [31:0] rtc_araddr;
  wire        rtc_arvalid;
  // clint 从口(含写通道, 路由到 mtimecmp)
  wire [31:0] clint_araddr;
  wire        clint_arvalid;
  wire [31:0] clint_awaddr, clint_wdata;
  wire        clint_awvalid, clint_wvalid;
  wire        clint_bready;
  // MMIO 标记(xbar 判定, 供 difftest 跳过比对)
  wire        xbar_mmio_sel;

  // ═══════════════ 各从设备 → axi_xbar(响应侧) ═══════════════
  // mem
  wire        dmem_arready, dmem_rvalid, dmem_awready, dmem_wready, dmem_bvalid;
  wire [31:0] dmem_rdata;
  wire [1:0]  dmem_rresp, dmem_bresp;
  // uart
  wire        uart_arready, uart_rvalid;
  wire [31:0] uart_rdata;
  wire [1:0]  uart_rresp;
  wire        uart_awready, uart_wready, uart_bvalid;
  wire [1:0]  uart_bresp;
  // rtc
  wire        rtc_arready, rtc_rvalid;
  wire [31:0] rtc_rdata;
  wire [1:0]  rtc_rresp;
  // clint
  wire        clint_arready, clint_rvalid;
  wire [31:0] clint_rdata;
  wire [1:0]  clint_rresp;
  wire        clint_awready, clint_wready, clint_bvalid;
  wire [1:0]  clint_bresp;
  wire        clint_mtip;   // 定时器中断请求 → irq_taken 判决

  // ═══════════════ EX_MEM 输出(EX~WB 段的结果寄存) ═══════════════
  wire [31:0] exm_result;      // EX/MEM 棒的 data: 锁存后的 alu_result, 跨拍稳定
  wire        exm_done;        // EX/MEM 棒的 valid: EX 段已算完, 结果可交
  wire        exm_stage_fire;  // 本拍正在把 EXU 的结果锁进来

  // ═══════════════ core 自己的寄存器 ═══════════════
  reg        mmio_flag_r;    // 本条指令是否访问了外设(供 difftest 跳过比对)
  reg        aborted_r;      // 非法指令: 命中后粘住, 直到复位
  // 过渡期语义信号: 供值暂时还是状态比较, B3 换成段间握手, 使用点不动  
  wire        ex_stage_fire    = exm_stage_fire;  // EX 段交班拍(由 EX_MEM 自持)

  // ── 退休判据(影子已验证与 ctrl_pc_we 逐拍一致后才接管) ──
  //   is_mem  : 本条是 load / store
  //   exm_done: EX/MEM 接力棒的 valid —— EX 段已算完(exm_result 的 valid 位)
  //   retire  : WB 段有效 = 本条指令退休拍
  //   非访存指令 EX 完成即退休; 访存指令还要等 LSU 结果就绪(lsu_res_valid)。
  //   ctrl 里 "EXE→MEM 还是 EXE→WB" 的两路分流, 被这个 || 吸收。
  wire        is_mem  = idu_mem_re || idu_mem_we;              // 访存操作
  wire        retire  = exm_done && (!is_mem || lsu_res_valid);  // 退休拍
  wire        mem_req = is_mem && exm_done;                     // EX 算完且是访存 → 向 LSU 下单
  // MEM 段进行中 = 访存单已下、结果还没回来(到 handshake 那拍为止)
  wire        mem_stage_active = is_mem && exm_done && !lsu_res_valid;

  // 下游"能收" = 本条退休(IFU 松手 / LSU 交班都看它)
  //   与 retire 现在等价, 但 B3 会分化: retire 永远是"本条退休",
  //   本信号还要再 && 反压链(下游堵住时就算退休也不许进新指令), 故名字分开保留。
  wire        wb_stage_ready   = retire;
  // ── IR ── 不再是寄存器: 指令和它的 PC 由 IFU 的保持寄存器直接提供
  //   hold_inst / hold_pc 在整条指令的 DEC..WB 期间恒定, 正是 IR 该有的语义。
  wire [31:0] IR;
  wire [31:0] ir_pc;
  assign IR    = ifu_inst;
  assign ir_pc = ifu_out_pc;  
  // ── 中断响应判决 ──
  //   只在退休拍响应: 这一拍 reg_we/pc_we/CSR 写同时发生, 是唯一的原子指令边界
  //   csr_mstatus_mie: mstatus.MIE, 软件 iset() 打开才响应
  //   clint_mtip     : mtime >= mtimecmp, 硬件中断请求
  //   排除 ecall / mret, 否则 mepc 会被写坏:
  //     ecall: npc_normal 恰好 = mtvec, mepc 会变成 mtvec, 返回地址丢失
  //     mret : npc_normal 恰好 = mepc,  新 mepc = 旧 mepc, mret 后死循环
  wire        irq_taken = retire
                       && csr_mstatus_mie
                       && clint_mtip
                       && (idu_npc_sel != `NPC_ECALL)
                       && (idu_npc_sel != `NPC_MRET)
                       && !idu_csr_wen;   // CSR 写指令的退休拍不响应中断

  // ── 存进 mepc 的值 ──
  //   异常存自己(软件 +4 跳过); 中断存下一条(软件绝不能 +4)
  wire [31:0] trap_pc = irq_taken ? ifu_npc_normal : ir_pc;
  // ── 输出打包 ──
  assign halt      = (IR == 32'h00100073);
  assign ir_dbg    = IR;
  assign state_dbg = state_now;
  assign aborted   = aborted_r;   // 非法指令/异常终止
  assign mmio_dbg  = mmio_flag_r;



  // ── IFU ── 私有请求接口接 arbiter
  IFU u_ifu (
    .clk(clk), .rst(rst),
    .pc_we(retire), 
    .alu_result(exu_alu_result), .npc_sel(idu_npc_sel),
    .branch_taken(exu_branch_taken),
    .csr_mtvec(csr_mtvec), .csr_mepc(csr_mepc),
    .irq_taken(irq_taken),                 // 中断行为 劫持取指
    .access_fault(access_fault),          // 总线出错 强制写pc
    .req_valid(ifu_req_valid),
    .req_addr(ifu_req_addr),
    .handshake_done(arb_ifu_done),
    .resp_rdata(arb_ifu_rdata),
    .out_ready(wb_stage_ready),       // 过渡期: WB 拍下游把指令取走(hold 松手条件)
    .out_valid(ifu_out_valid), .out_pc(ifu_out_pc),
    .pc(pc), .pc4(ifu_pc4), .inst(ifu_inst),
    .npc_normal(ifu_npc_normal)       // 未被中断劫持的 next-pc, 中断时作 mepc
  );
 // ── IDU ──
  IDU u_idu (
    .inst(IR),
    .rs1(idu_rs1), .rs2(idu_rs2), .rd(idu_rd),
    .rs1_en(idu_unused_rs1_en), .rs2_en(idu_unused_rs2_en), .rd_en(idu_rd_en),
    .imm(idu_imm),
    .alu_op(idu_alu_op), .alu_src2_imm(idu_alu_src2_imm),
    .alu_en(idu_alu_en), .alu_src1_pc(idu_alu_src1_pc),
    .wb_sel(idu_wb_sel), .npc_sel(idu_npc_sel),
    .mem_re(idu_mem_re), .mem_we(idu_mem_we),
    .mem_width(idu_mem_width), .mem_signed(idu_mem_signed),
    .branch_type(idu_branch_type), .invalid(idu_invalid),
    .csr_idx(idu_csr_idx), .csr_wen(idu_csr_wen), .csr_s_w(idu_csr_s_w)
  );

  // ── 寄存器堆 ──
  RegisterFile #(.ADDR_WIDTH(5), .DATA_WIDTH(32)) u_regfile (
    .clk(clk),
    .w_data(wbu_wb_data), .w_addr(idu_rd),
    .r_addr1(idu_rs1), .r_addr2(idu_rs2),
    .wen(idu_rd_en && retire),
    .r_data1(rf_rdata1), .r_data2(rf_rdata2), .r_a0(rf_unused_r_a0)
  );

  // ── EXU ──
  EXU u_exu (
    .rs1_data(rf_rdata1), .rs2_data(rf_rdata2),
    .imm(idu_imm), .alu_en(idu_alu_en), .alu_op(idu_alu_op),
    .alu_src2_imm(idu_alu_src2_imm), .alu_src1_pc(idu_alu_src1_pc),
    .pc(pc), .branch_type(idu_branch_type),
    .alu_result(exu_alu_result), .branch_taken(exu_branch_taken)
  );

  // ── EX_MEM: EX/MEM 流水寄存器, 把 EXU 的组合结果举到 WB 收走为止 ──
  EX_MEM u_ex_mem (
    .clk(clk), .rst(rst),
    .in_valid(ifu_out_valid),      // 上游: IFU 手上有指令
    .result_in(exu_alu_result),    // 数据: EXU 组合算出的结果
    .out_ready(retire),            // 下游: WB 段收走才松手
    .exm_result(exm_result),
    .exm_done(exm_done),
    .exm_stage_fire(exm_stage_fire)
  );

 // ── LSU（访存控制器：私有请求 → arbiter）──
  LSU u_lsu (
    .clk(clk),  .rst(rst),
    .mem_re(idu_mem_re), .mem_we(idu_mem_we),
    .mem_width(idu_mem_width), .mem_signed(idu_mem_signed),
    .wdata_in(rf_rdata2), .addr_in(exm_result),
    .rdata_in(arb_lsu_rdata),
    .handshake_done(arb_lsu_done),
    .req_valid(lsu_req_valid),
    .req_addr(lsu_req_addr),
    .req_wdata(lsu_req_wdata),
    .req_wmask(lsu_req_wmask),

    .in_valid(mem_req),
    .in_ready(lsu_in_ready),
    .out_ready(wb_stage_ready),

    .res_valid(lsu_res_valid),
    
    .rdata_out(lsu_rdata)
  );
  // ── WBU ──
  WBU u_wbu (
    .wb_sel(idu_wb_sel), .pc4(ifu_pc4),
    .alu_result(exm_result), .mem_data(lsu_rdata),
    .csr_data(csr_data), .imm(idu_imm),
    .wb_data(wbu_wb_data)
  );

  // ── CSRFile ──
  CSRFile #(.ADDR_WIDTH(12)) u_CSRFile (
    .clk(clk), .rst(rst), .at_state_wb(retire),
    .csr_wen(idu_csr_wen), .csr_s_w(idu_csr_s_w),
    .ecall_trap(idu_npc_sel == `NPC_ECALL),
    .ebreak_trap(IR == 32'h00100073),
    .mret_exec(idu_npc_sel == `NPC_MRET),
    .irq_trap(irq_taken),                 
    .ecall_pc(trap_pc), .csr_wdata(rf_rdata1), .csr_idx(idu_csr_idx),
    .mstatus_mie(csr_mstatus_mie),     
    .csr_mtvec(csr_mtvec), .csr_mepc(csr_mepc), .csr_data(csr_data)
  );
  // ── 相位译码器(纯组合, 只观测不控制) ──
  stage_dec u_stage_dec (
    .rst(rst),
    .ifu_out_valid(ifu_out_valid),
    .ex_stage_fire(ex_stage_fire),
    .mem_active(mem_stage_active),
    .retire(retire),
    .aborted(aborted_r),
    .state(state_now)
  );

  // ── 仲裁器：IFU/LSU 两个 master 合并成一路（IFU 固定优先）──
  arbiter u_arb (
    .clk(clk), .rst(rst),
    .ifu_req_valid(ifu_req_valid), .ifu_req_addr(ifu_req_addr),
    .ifu_done(arb_ifu_done), .ifu_resp_rdata(arb_ifu_rdata),
    .lsu_req_valid(lsu_req_valid), .lsu_req_we(idu_mem_we),
    .lsu_req_addr(lsu_req_addr), .lsu_req_wdata(lsu_req_wdata),
    .lsu_req_wstrb(lsu_req_wmask),
    .lsu_done(arb_lsu_done), .lsu_resp_rdata(arb_lsu_rdata),
    .m_req_valid(arb_req_valid), .m_req_we(arb_req_we),
    .m_req_addr(arb_req_addr), .m_req_wdata(arb_req_wdata),
    .m_req_wstrb(arb_req_wstrb),
    .m_done(mst_done), .m_resp_rdata(mst_resp_rdata)
  );

  // ── 唯一的 AXI4-Lite 协议适配层（IFU 读 / LSU 读写 共用）──
  ysyx_26020047_axi_master u_master(
    .clk(clk), .rst(rst),
    // 简单请求侧 ← arbiter
    .req_valid(arb_req_valid), .req_we(arb_req_we),
    .req_addr(arb_req_addr),   .req_wdata(arb_req_wdata),
    .req_wstrb(arb_req_wstrb), .stall(lfsr_stall),
    // 完成/读数据 → arbiter
    .done(mst_done), .resp_rdata(mst_resp_rdata), 
    // 错误检测
    .resp_err(mst_resp_err),
    // AR
    .arid(mst_arid), .araddr(mst_araddr), .arlen(mst_arlen), .arsize(mst_arsize),
    .arburst(mst_arburst), .arvalid(mst_arvalid), .arready(mst_arready),
    // R
    .rid(mst_rid), .rdata(mst_rdata), .rvalid(mst_rvalid), .rresp(mst_rresp),
    .rlast(mst_rlast), .rready(mst_rready),
    // AW
    .awid(mst_awid), .awaddr(mst_awaddr), .awlen(mst_awlen), .awsize(mst_awsize),
    .awburst(mst_awburst), .awvalid(mst_awvalid), .awready(mst_awready),
    // W
    .wdata(mst_wdata), .wvalid(mst_wvalid), .wstrb(mst_wstrb),
    .wlast(mst_wlast), .wready(mst_wready),
    // B
    .bid(mst_bid), .bresp(mst_bresp), .bvalid(mst_bvalid), .bready(mst_bready)

  );
  // ── LFSR:每拍推进, 按阈值产生随机总线停顿 ──
  // lfsr 输出 1~255(不含 0), 阈值 16 → 约 1/16 概率停一拍
`ifdef HAS_LFSR
  lfsr u_lfsr (
    .clk (clk),
    .rst (rst),
    .en  (1'b1),
    .val (lfsr_val)
  );
  assign lfsr_stall = (lfsr_val < 8'd16); //小于16就stall
`else
  assign lfsr_stall = 1'b0;               // 未开 LFSR: 总线不停顿
`endif


`ifdef YSYXSOC
  // ═══════════ SoC 模式: 片内只留 CLINT, 其余地址走外部 AXI4 ═══════════
  // CLINT 占 0x0200_0000~0x0200_ffff, 这一段留在片内; 其它一律发往 SoC。
  wire sel_r = (mst_araddr[31:16] == 16'h0200);   // 本次读落在 CLINT?
  wire sel_w = (mst_awaddr[31:16] == 16'h0200);   // 本次写落在 CLINT?

  // ── 片内 CLINT ──
  wire        c_arready, c_rvalid, c_awready, c_wready, c_bvalid;
  wire [31:0] c_rdata;
  wire [1:0]  c_rresp, c_bresp;
  clint u_clint (
    .clk(clk), .rst(rst),
    .araddr(mst_araddr), .arvalid(mst_arvalid && sel_r), .arready(c_arready),
    .rdata(c_rdata), .rresp(c_rresp), .rvalid(c_rvalid), .rready(mst_rready),
    .awaddr(mst_awaddr), .awvalid(mst_awvalid && sel_w), .awready(c_awready),
    .wdata(mst_wdata), .wvalid(mst_wvalid && sel_w), .wready(c_wready),
    .bresp(c_bresp), .bvalid(c_bvalid), .bready(mst_bready),
    .mtip(clint_mtip)
  );

  // ── 请求侧: 发往 SoC 的部分 (master 发出的字段直接透传, valid 用 !sel 门控) ──
  assign io_master_arvalid = mst_arvalid && !sel_r; //非clint 的道路
  assign io_master_arid    = mst_arid;
  assign io_master_araddr  = mst_araddr;
  assign io_master_arlen   = mst_arlen;
  assign io_master_arsize  = mst_arsize;
  assign io_master_arburst = mst_arburst;
  assign io_master_rready  = mst_rready;

  assign io_master_awvalid = mst_awvalid && !sel_w;  // 非clint 从第一个状态控制
  assign io_master_awid    = mst_awid;
  assign io_master_awaddr  = mst_awaddr;
  assign io_master_awlen   = mst_awlen;
  assign io_master_awsize  = mst_awsize;
  assign io_master_awburst = mst_awburst;

  assign io_master_wvalid  = mst_wvalid && !sel_w;// 非clint 的道路
  assign io_master_wdata   = mst_wdata;
  assign io_master_wstrb   = mst_wstrb;
  assign io_master_wlast   = mst_wlast;

  assign io_master_bready  = mst_bready;

  // ── 响应侧: 二选一 ──
  assign mst_arready = sel_r ? c_arready : io_master_arready;
  assign mst_awready = sel_w ? c_awready : io_master_awready;
  assign mst_wready  = sel_w ? c_wready  : io_master_wready;

  assign mst_rdata   = sel_r ? c_rdata   : io_master_rdata;
  assign mst_rvalid  = sel_r ? c_rvalid  : io_master_rvalid;
  assign mst_rresp   = sel_r ? c_rresp   : io_master_rresp;
  assign mst_rlast   = sel_r ? 1'b1      : io_master_rlast;   // CLINT 是单拍(Lite)
  assign mst_rid     = sel_r ? 4'd0      : io_master_rid;

  assign mst_bvalid  = sel_w ? c_bvalid  : io_master_bvalid;
  assign mst_bresp   = sel_w ? c_bresp   : io_master_bresp;
  assign mst_bid     = sel_w ? 4'd0      : io_master_bid;

  // ── SoC 模式不跑 difftest ──
  assign xbar_mmio_sel = 1'b0;

`else
  // ═══════════════ 单跑模式: 内部 xbar + 四个从设备 + 主存 ═══════════════

  axi_xbar u_xbar (
    // 主口 ← axi_lite_master
    .m_araddr (mst_araddr),  .m_arvalid (mst_arvalid),  .m_arready (mst_arready),
    .m_rdata  (mst_rdata),   .m_rresp   (mst_rresp),    .m_rvalid  (mst_rvalid),  .m_rready (mst_rready),
    .m_awaddr (mst_awaddr),  .m_awvalid (mst_awvalid),  .m_awready (mst_awready),
    .m_wdata  (mst_wdata),   .m_wmask   (mst_wstrb),    .m_wvalid  (mst_wvalid),  .m_wready (mst_wready),
    .m_bresp  (mst_bresp),   .m_bvalid  (mst_bvalid),   .m_bready  (mst_bready),
    // 从口 → mem
    .mem_araddr (dmem_araddr),  .mem_arvalid (dmem_arvalid),  .mem_arready (dmem_arready),
    .mem_rdata  (dmem_rdata),   .mem_rresp   (dmem_rresp),    .mem_rvalid  (dmem_rvalid),  .mem_rready (dmem_rready),
    .mem_awaddr (dmem_awaddr),  .mem_awvalid (dmem_awvalid),  .mem_awready (dmem_awready),
    .mem_wdata  (dmem_wdata),   .mem_wmask   (dmem_wmask),    .mem_wvalid  (dmem_wvalid),  .mem_wready (dmem_wready),
    .mem_bresp  (dmem_bresp),   .mem_bvalid  (dmem_bvalid),   .mem_bready  (dmem_bready),
    // 从口 → uart
    .uart_araddr (uart_araddr),  .uart_arvalid (uart_arvalid),  .uart_arready (uart_arready),
    .uart_rdata  (uart_rdata),   .uart_rresp   (uart_rresp),    .uart_rvalid  (uart_rvalid),  .uart_rready (uart_rready),
    .uart_awaddr (uart_awaddr),  .uart_awvalid (uart_awvalid),  .uart_awready (uart_awready),
    .uart_wdata  (uart_wdata),   .uart_wmask   (uart_wmask),    .uart_wvalid  (uart_wvalid),  .uart_wready (uart_wready),
    .uart_bresp  (uart_bresp),   .uart_bvalid  (uart_bvalid),   .uart_bready  (uart_bready),
    // 从口 → rtc（只读）
    .rtc_araddr (rtc_araddr),  .rtc_arvalid (rtc_arvalid),  .rtc_arready (rtc_arready),
    .rtc_rdata  (rtc_rdata),   .rtc_rresp   (rtc_rresp),    .rtc_rvalid  (rtc_rvalid),
    // 从口 → clint（读 mtime/mtimecmp + 写 mtimecmp）
    .clint_araddr (clint_araddr),  .clint_arvalid (clint_arvalid),  .clint_arready (clint_arready),
    .clint_rdata  (clint_rdata),   .clint_rresp   (clint_rresp),    .clint_rvalid  (clint_rvalid),
    .clint_awaddr (clint_awaddr),  .clint_awvalid (clint_awvalid),  .clint_awready (clint_awready),
    .clint_wdata  (clint_wdata),   .clint_wvalid  (clint_wvalid),   .clint_wready  (clint_wready),
    .clint_bresp  (clint_bresp),   .clint_bvalid  (clint_bvalid),   .clint_bready  (clint_bready),
    // MMIO 标记
    .mmio_sel (xbar_mmio_sel)
  );

  rtc u_rtc (
    .clk    (clk),
    .araddr (rtc_araddr),
    .arvalid(rtc_arvalid),
    .arready(rtc_arready),
    .rdata  (rtc_rdata),
    .rresp  (rtc_rresp),
    .rvalid (rtc_rvalid),
    .rready (mst_rready)   // rtc 的 rready 不走 xbar(xbar 无 rtc_rready 口), 直接连 master
  );

  clint u_clint (
    .clk    (clk),
    .rst    (rst),
    .araddr (clint_araddr),
    .arvalid(clint_arvalid),
    .arready(clint_arready),
    .rdata  (clint_rdata),
    .rresp  (clint_rresp),
    .rvalid (clint_rvalid),
    .rready (mst_rready),  // clint 的 rready 不走 xbar(xbar 无 clint_rready 口), 直接连 master
    // 写通道 → mtimecmp
    .awaddr (clint_awaddr), .awvalid(clint_awvalid), .awready(clint_awready),
    .wdata  (clint_wdata),  .wvalid (clint_wvalid),  .wready (clint_wready),
    .bresp  (clint_bresp),  .bvalid (clint_bvalid),  .bready (clint_bready),
    // 中断
    .mtip   (clint_mtip)
  );

  uart u_uart (
    .clk    (clk),
    .araddr (uart_araddr), .arvalid(uart_arvalid), .arready(uart_arready),
    .rdata  (uart_rdata), .rresp(uart_rresp), .rvalid(uart_rvalid), .rready(uart_rready),
    .awaddr (uart_awaddr),
    .awvalid(uart_awvalid),
    .awready(uart_awready),
    .wdata  (uart_wdata),
    .wmask  (uart_wmask),
    .wvalid (uart_wvalid),
    .wready (uart_wready),
    .bresp  (uart_bresp),
    .bvalid (uart_bvalid),
    .bready (uart_bready)
  );

`ifdef DPI_MEM
  // DPI 模式: 取指/访存经 DPI-C 读写 NEMU pmem, 只保留一个实例。
  // pmem 段 = 0x80000000~0x87FFFFFF (128MB), 由 xbar 的 mem 从口统一路由。
  dpic_mem u_mem (
    .clk(clk),
    .araddr(dmem_araddr), .arvalid(dmem_arvalid), .arready(dmem_arready),
    .rdata(dmem_rdata), .rresp(dmem_rresp), .rvalid(dmem_rvalid), .rready(dmem_rready),
    .awaddr(dmem_awaddr), .awvalid(dmem_awvalid), .awready(dmem_awready),
    .wdata(dmem_wdata), .wmask(dmem_wmask), .wvalid(dmem_wvalid), .wready(dmem_wready),
    .bresp(dmem_bresp), .bvalid(dmem_bvalid), .bready(dmem_bready)
  );
`else
  // 非 DPI 模式: 用一块 data_mem(读写)同时服务取指与访存, inst_mem 已并入。
  pmem u_pmem (                  // delay from menuconfig
    .clk(clk),
    .araddr(dmem_araddr), .arvalid(dmem_arvalid), .arready(dmem_arready),
    .rdata(dmem_rdata), .rresp(dmem_rresp), .rvalid(dmem_rvalid), .rready(dmem_rready),
    .awaddr(dmem_awaddr), .awvalid(dmem_awvalid), .awready(dmem_awready),
    .wdata(dmem_wdata), .wmask(dmem_wmask), .wvalid(dmem_wvalid), .wready(dmem_wready),
    .bresp(dmem_bresp), .bvalid(dmem_bvalid), .bready(dmem_bready)
  );
`endif

`endif
  // 返回给 axi_lite_master 的应答多选（含未命中地址的 DECERR 兜底）已整体移入 axi_xbar。

  // ═══════════════════════════════════════════════════════════════
  //  时序逻辑区: 按段分组, 每个 always 块只管自己那个段
  // ═══════════════════════════════════════════════════════════════
  // ── MMIO 标记: EX 拍清零, MEM 拍采样 ──
  //   xbar 判定本次访问是否落在 rtc/clint/uart, 标记本条指令为 MMIO
  always @(posedge clk)
  begin
    if (rst)
    begin
      mmio_flag_r <= 1'b0;
    end
    else if (ex_stage_fire)
    begin
      mmio_flag_r <= 1'b0;
    end
    else if (mem_stage_active)
    begin
      mmio_flag_r <= xbar_mmio_sel;
    end
  end

  // ── 非法指令: 命中即粘住 ──
  //   ifu_out_valid 必需: 复位后 IR 还没取回来, 组合的 idu_invalid 是 X, 会误报 ABORT
  //   无 else: 一旦置起就保持到复位, 对齐 NEMU_ABORT "停机" 而不是 "闪一拍"
  always @(posedge clk)
  begin
    if (rst)
    begin
      aborted_r <= 1'b0;
    end
    else if (ifu_out_valid && idu_invalid)
    begin
      aborted_r <= 1'b1;
    end
  end

  // ── 退休指示: 打一拍输出给 monitor ──
  always @(posedge clk)
  begin
    if (rst)
    begin
      inst_retire <= 1'b0;
    end
    else
    begin
      inst_retire <= retire;
    end
  end
  // ── Access Fault: 命中即粘住, 直到复位 ──
  //   讲义建议: 未实现 CTE 前不做完整 trap, 先把错误"暴露"出来;
  //   否则 CPU 拿着错误数据继续跑, 故障点离病因几十万拍, 极难查。
  `ifdef YSYXSOC
  // ── 地址白名单: 落在这几段之外 = 越界 ──
  //   为什么不能只靠 resp:
  //     实测这颗 SoC 的 AXI Xbar 对"没有任何从设备认领"的地址返回 OKAY, 静默吞掉
  //     (见 ysyxSoC/build/ysyxSoCFull.v:1207 —— 两个分支的默认值都是 2'h0);
  //     只有落在某个从设备辖区内、但超出它容量的, 才拿得到 DECERR(如 SRAM 越界)。
  //   所以"越界"必须由 NPC 自己判一份白名单兜底, 和 resp 检测互补。
  function addr_legal;
    input [31:0] a;
    begin
      addr_legal = (a[31:12] == 20'h20000)    // MROM  0x2000_0000 ~ 0x2000_0fff (4KB)
                || (a[31:13] == 19'h07800)    // SRAM  0x0f00_0000 ~ 0x0f00_1fff (8KB)
                || (a[31:12] == 20'h10000)    // UART  0x1000_0000
                || (a[31:16] == 16'h0200);    // CLINT 0x0200_0000
    end
  endfunction

  // 地址通道有效时就判: 读或写, 落在白名单之外即越界
  wire addr_bad = (mst_arvalid && !addr_legal(mst_araddr))
               || (mst_awvalid && !addr_legal(mst_awaddr));
`else
  wire addr_bad = 1'b0;                       // 单跑模式地址图不同, 不启用
`endif

  reg         access_fault_r;    // 出错标志: 一旦置起就不再清, 直到复位
  reg  [31:0] fault_addr_r;      // 第一次出错的地址 —— 排查时最关键的信息

  always @(posedge clk) 
  begin
    if (rst) 
    begin
      access_fault_r <= 1'b0;
      fault_addr_r   <= 32'b0;
    end else if (mst_resp_err || addr_bad) 
    begin
      access_fault_r <= 1'b1;
      if (!access_fault_r) fault_addr_r <= arb_req_addr;   // 只抓第一次, 不被后续覆盖
    end
  end
  wire access_fault = access_fault_r;


`include "core_dbg.vh"

endmodule


