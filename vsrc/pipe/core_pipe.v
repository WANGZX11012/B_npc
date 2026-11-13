`include "npc_defs.vh"

//=============================================================================
// core_pipe — B5 五级流水线核
//   端口与 core.v 一致, 由 top.v 在 CORE_PIPE 宏下例化。
//
//   数据流 → , ready 反压 ← ;  [ ] 内为段寄存器
//
//   取指 / 访存统一走 dpic_mem (IFU/LSU → arbiter → AXI master)
//   IFU ─→ [u_ifid] ─→ IDU/RF ─→ [u_idex] ─→ EXU ─→
//                  [u_exmem] ─→ [u_memwb] ─→ WBU ─→ RF
//
//   文件结构:
//     0  声明区    只声明信号, 不含任何 assign / always
//     1~13 例化区  只写端口连接
//     9  逻辑区    所有 assign / always 集中在文件末尾
//
//   命名约定:
//     ifu_*         IFU ↔ arbiter 取指接口
//     if_*          IFU → u_ifid 的交付侧, 组合
//     if_id_*       u_ifid 端口组: 寄存输出 + 逆流 ready
//     idu_*         IDU 组合译码, 当拍有效
//     ex_/mem_/wb_  后续各级沿用旧名
//=============================================================================
module core_pipe (

  // ── Clock & Reset ──
  input  wire        clk,
  input  wire        rst,

  // ── 输出: to top / monitor (端口必须与 core.v 完全一致) ──
  output wire [31:0] pc,        //  架构 PC(退休更新) 例如0x0指令写回后 pc就变成0x4
  output wire        halt,
  output wire        aborted,
  output wire [31:0] retire_inst_dbg,
  output wire [2:0]  state_dbg,
  output wire        inst_retire,   // ← u_retire (端口类型必须是 wire)
  output wire        mmio_dbg

);

    //===========================================================================
  // 0. 信号声明 (按流水级: IF → ID → EX → MEM → WB)
  //===========================================================================

  // ── A. 取指接口: IFU ↔ arbiter ──
  wire        ifu_req_valid;      // IFU 输出: 取指请求(电平, 保持到应答)
  wire [31:0] ifu_req_addr;       // IFU 输出: 取指地址 = pc_reg
  wire        ifu_done;           // arbiter → IFU: 单拍完成脉冲
  wire [31:0] ifu_rdata;          // arbiter → IFU: 返回的指令字
  wire        ifu_req_pulse;      // ← u_redirect: 电平转单拍后的请求

  // ── B. IFU → u_ifid 交付侧 (组合, 无寄存) ──
  wire [31:0] pc_q;            // ← IFU: pc_reg 触发器 Q 端 = 当前取指地址
  wire [31:0] if_pc4;          // ← IFU: 当前指令 PC+4 = 下一条 PC
  wire [31:0] if_inst;         // → u_ifid: 交付的指令(bypass 或 hold)
  wire [31:0] if_npc_normal;   // ← IFU: 未被劫持的 next-PC(仅观测)
  wire        if_valid;        // → u_ifid: 本次交付有效(= IFU hold_valid)
  wire [31:0] if_pc;           // → u_ifid: 这条指令自己的 PC

  // ── C. 停顿与冒险控制 (三个同类信号放一块) ──
  wire        raw_hazard;      // hazard_unit 输出: 检测到 RAW
  wire        idex_bubble;     // 仲裁后: 本拍真的向 EX 注气泡
  wire        mem_stall;       // MEM 等总线: 冻上游 + WB 注气泡

  // ── D. 跳转重定向: 全部状态收进 redirect_unit, 顶层只留 5 根输出线 ──
  wire [2:0]  ifu_npc_sel;         // → u_ifu: 仅重定向首拍用跳转类型
  wire        ifu_pc_we;           // → u_ifu: 何时写 pc_reg
  wire        ifu_handshake;       // → u_ifu: 门控后的 handshake_done
  wire        ifid_flush;          // → u_ifid: 冲 IF/ID
  wire        idex_flush;          // → u_idex: 冲 ID/EX

  // ── C. u_ifid (IF/ID 段寄存器): 拍末锁存, 端口组统一 if_id_ 前缀 ──
  wire        if_id_valid;     // ← u_ifid 寄存输出: ID 级槽位有效
  wire [31:0] if_id_pc;        // ← u_ifid 寄存输出: ID 级指令 PC
  wire [31:0] if_id_inst;      // ← u_ifid 寄存输出: → IDU 译码输入
  wire        if_id_ready;     // ← u_ifid → IFU: 本级能收新指(逆流反压)

  // ── D. IDU 组合译码 + RF 读口 (→ u_idex) ──
  //   idu_* 无寄存无握手: if_id_inst 变则当拍变; 与 rf_rdata* 同拍被 u_idex 锁走
  wire [4:0]  idu_rs1;         // ← IDU → RF.r_addr1: 源寄存器 1 地址
  wire [4:0]  idu_rs2;         // ← IDU → RF.r_addr2: 源寄存器 2 地址
  wire [4:0]  idu_rd;          // ← IDU → u_idex: 目的寄存器地址
  wire        idu_rs1_en;      // ← IDU → u_idex: rs1 读使能
  wire        idu_rs2_en;      // ← IDU → u_idex: rs2 读使能
  wire        idu_rd_en;       // ← IDU → u_idex: 本指令写 rd
  wire [31:0] idu_imm;         // ← IDU → u_idex: 符号展开后的立即数
  wire [3:0]  idu_alu_op;      // ← IDU → u_idex: ALU 运算码
  wire        idu_alu_en;      // ← IDU → u_idex: 使用 ALU
  wire        idu_alu_src2_imm;// ← IDU → u_idex: 第二操作数取 imm(否则 rs2)
  wire        idu_alu_src1_pc; // ← IDU → u_idex: 第一操作数取 PC(auipc/jal)
  wire [2:0]  idu_wb_sel;      // ← IDU → u_idex: 写回来源(ALU/PC4/MEM/CSR/IMM)
  wire [2:0]  idu_npc_sel;     // ← IDU → u_idex: next-PC 选择(未回连 IFU)
  wire [2:0]  idu_branch_type; // ← IDU → u_idex: 分支条件类型
  wire        idu_mem_re;      // ← IDU → u_idex: load 使能
  wire        idu_mem_we;      // ← IDU → u_idex: store 使能
  wire        idu_mem_signed;  // ← IDU → u_idex: load 符号扩展
  wire [1:0]  idu_mem_width;   // ← IDU → u_idex: 访存宽度(B/H/W)
  wire [11:0] idu_csr_idx;     // ← IDU → u_idex: CSR 地址
  wire        idu_csr_wen;     // ← IDU → u_idex: CSR 写使能
  wire        idu_csr_s_w;     // ← IDU → u_idex: csrrs / csrrw 区分
  wire        idu_fence_i;     // ← IDU → u_idex: fence.i 冲刷 icache
  wire        idu_invalid;     // ← IDU → u_idex: 非法指令标记(未接 aborted)
  wire [31:0] rf_rdata1;       // ← RF 组合读出 → u_idex: 操作数 1
  wire [31:0] rf_rdata2;       // ← RF 组合读出 → u_idex: 操作数 2

  // ── E. u_idex (ID/EX 段寄存器): 拍末锁存 ID 段译码结果 + 操作数 ──
  wire        ex_valid;        // ← u_idex 寄存输出: EX 级槽位有效
  wire [31:0] ex_pc;           // ← u_idex → EXU: 本指令 PC
  wire [31:0] ex_inst;         // EX 级指令编码
  wire [31:0] ex_rs1_data;     // ← u_idex → EXU: 操作数 1
  wire [31:0] ex_rs2_data;     // ← u_idex → EXU: 操作数 2 / store 数据
  wire [31:0] ex_imm;          // ← u_idex → EXU/u_exmem: 立即数
  wire [4:0]  ex_rd;           // ← u_idex → u_exmem: 目的寄存器
  wire        ex_rd_en;        // ← u_idex → u_exmem: 写 rd 使能
  wire [3:0]  ex_alu_op;       // ← u_idex → EXU: ALU 运算码
  wire        ex_alu_en;       // ← u_idex → EXU: 使用 ALU
  wire        ex_alu_src2_imm; // ← u_idex → EXU: 第二操作数取 imm
  wire        ex_alu_src1_pc;  // ← u_idex → EXU: 第一操作数取 PC
  wire [2:0]  ex_npc_sel;      // ← u_idex → u_exmem: next-PC 选择
  wire [2:0]  ex_branch_type;  // ← u_idex → EXU: 分支条件类型
  wire [2:0]  ex_wb_sel;       // ← u_idex → u_exmem: 写回来源
  wire        ex_mem_re;       // ← u_idex → u_exmem: load 使能
  wire        ex_mem_we;       // ← u_idex → u_exmem: store 使能
  wire        ex_mem_signed;   // ← u_idex → u_exmem: load 符号扩展
  wire [1:0]  ex_mem_width;    // ← u_idex → u_exmem: 访存宽度
  wire [11:0] ex_csr_idx;      // ← u_idex → u_exmem: CSR 地址
  wire        ex_csr_wen;      // ← u_idex → u_exmem: CSR 写使能
  wire        ex_csr_s_w;      // ← u_idex → u_exmem: csrrs / csrrw
  wire        ex_fence_i;      // ← u_idex → u_exmem: fence.i
  wire        ex_invalid;      // ← u_idex → u_exmem: 非法指令
  wire        id_ready;        // ← u_idex → u_ifid: 本级能收新指(逆流反压)

  // ── F. EXU 组合输出 (→ u_exmem): 当拍算出, 不寄存 ──
  wire [31:0] ex_alu_result;   // ← EXU → u_exmem: 运算结果 / 访存地址 / 跳转目标
  wire        ex_branch_taken; // ← EXU: 分支条件成立(当前未回连 IFU)

  // ── G. u_exmem (EX/MEM 段寄存器): 拍末锁存 EX 结果 ──
  wire        mem_valid;       // ← u_exmem 寄存输出: MEM 级槽位有效
  wire [31:0] mem_pc;          // ← u_exmem → u_memwb: 本指令 PC
  wire [31:0] mem_inst;        // MEM 级指令编码
  wire [31:0] mem_alu_result;  // ← u_exmem → u_memwb: ALU 结果
  wire [31:0] mem_rs1_data;    // ← u_exmem → u_memwb: CSR 写数据
  wire [31:0] mem_rs2_data;    // ← u_exmem → u_memwb: store 数据
  wire [31:0] mem_imm;         // ← u_exmem → u_memwb: 立即数(lui)
  wire [4:0]  mem_rd;          // ← u_exmem → u_memwb: 目的寄存器
  wire        mem_rd_en;       // ← u_exmem → u_memwb: 写 rd 使能
  wire        mem_re;          // ← u_exmem: load 使能(LSU 未接)
  wire        mem_we;          // ← u_exmem: store 使能(LSU 未接)
  wire        mem_signed;      // ← u_exmem: load 符号扩展(LSU 未接)
  wire [1:0]  mem_width;       // ← u_exmem: 访存宽度(LSU 未接)
  wire [2:0]  mem_wb_sel;      // ← u_exmem → u_memwb: 写回来源
  wire [11:0] mem_csr_idx;     // ← u_exmem → u_memwb: CSR 地址
  wire        mem_csr_wen;     // ← u_exmem → u_memwb: CSR 写使能
  wire        mem_csr_s_w;     // ← u_exmem → u_memwb: csrrs / csrrw
  wire        mem_invalid;     // ← u_exmem → u_memwb: 非法指令
  wire        mem_ready;       // ← u_memwb → u_exmem: 下游能收
  wire        ex_ready;        // ← u_exmem → u_idex: 本级能收(逆流反压)


  // ── H. u_memwb (MEM/WB 段寄存器): 拍末锁存, 输出进 WBU / RF ──
  wire        wb_valid;        // ← u_memwb 寄存输出: WB 级槽位有效
  wire [31:0] wb_pc;           // ← u_memwb → WBU: 本指令 PC(算 pc4)
  wire [31:0] wb_inst;         // WB 级指令编码
  wire [31:0] wb_alu_result;   // ← u_memwb → WBU: ALU 结果
  wire [31:0] wb_mem_data;     // ← u_memwb → WBU: 访存数据(当前桩 0)
  wire [31:0] wb_csr_data;     // ← u_memwb → WBU: CSR 读值(当前桩 0)
  wire [31:0] wb_rs1_data;     // ← u_memwb: CSR 写数据(CSR 未接)
  wire [31:0] wb_imm;          // ← u_memwb → WBU: 立即数(lui)
  wire [2:0]  wb_wb_sel;       // ← u_memwb → WBU: 写回来源选择
  wire [4:0]  wb_rd;           // ← u_memwb → RF.w_addr: 目的寄存器
  wire        wb_rd_en;        // ← u_memwb → RF.wen: 写 rd 使能
  wire [11:0] wb_csr_idx;      // ← u_memwb: CSR 地址(CSR 未接)
  wire        wb_csr_wen;      // ← u_memwb: CSR 写使能(CSR 未接)
  wire        wb_csr_s_w;      // ← u_memwb: csrrs / csrrw(CSR 未接)
  wire        wb_invalid;      // ← u_memwb: 非法指令(未接 aborted)
  wire [31:0] wb_data;         // ← WBU 组合输出 → RF.w_data: 选出的写回值
  // ── I. LSU / 总线侧 ──
  wire        lsu_req_valid, lsu_req_we, lsu_ready;
  wire [31:0] lsu_req_addr, lsu_req_wdata, lsu_rdata, rdata_out;
  wire [3:0]  lsu_req_wstrb;

  // arbiter ↔ master 的简单请求线已收进 cpu_bus_unit 内部, 顶层不再可见

  // cpu_bus_unit ↔ dpic_mem: AXI4-Lite 五通道(将来这里插 xbar)
  wire        d_arvalid, d_arready, d_rvalid, d_rlast, d_rready;
  wire [31:0] d_araddr, d_rdata;
  wire [7:0]  d_arlen;
  wire [1:0]  d_rresp, d_bresp;
  wire        d_awvalid, d_awready, d_wvalid, d_wready;
  wire [31:0] d_awaddr, d_wdata;
  wire [3:0]  d_wmask;
  wire        d_bvalid, d_bready;

  // ── ① IFU: 取指请求经 arbiter → AXI master, 交付 if_* → u_ifid ──
  IFU u_ifu (
    .clk               (clk),   // 时钟
    .rst               (rst),   // 同步复位
    .pc_we             (ifu_pc_we),        // ← u_redirect: 交付 / 重定向时写 PC
    .alu_result        (ex_alu_result),    // ← EX 段: 跳转目标(pc+imm 或 rs1+imm)
    .npc_sel           (ifu_npc_sel),      // ← u_redirect: 仅重定向首拍非 PC4
    .branch_taken      (ex_branch_taken),  // ← EX 段: 分支条件成立
    .csr_mtvec         (32'b0),   // ← 异常入口(当前固定 0)
    .csr_mepc          (32'b0),   // ← mret 返回地址(当前固定 0)
    .irq_taken         (1'b0),   // ← 中断响应(当前固定 0)
    .access_fault      (1'b0),   // ← 总线错误(当前固定 0)
    .req_valid         (ifu_req_valid),   // → 逻辑区转成脉冲后给 arbiter(电平保持到应答)
    .req_addr          (ifu_req_addr),   // → arbiter: 取指地址
    .handshake_done    (ifu_handshake),   // ← u_redirect: 门控后(丢弃在飞应答)
    .resp_rdata        (ifu_rdata),   // ← arbiter.ifu_rdata: 返回的指令字
    .out_ready         (if_id_ready),   // ← u_ifid: 本级能收新指(逆流反压)
    .out_valid         (if_valid),   // → u_ifid: 本次交付有效
    .out_pc            (if_pc),   // → u_ifid: 这条指令的 PC
    .pc                (pc_q),   // → pc_reg 的 Q 端(观测)
    .pc4               (if_pc4),   // → 当前指令 PC+4
    .inst              (if_inst),   // → u_ifid: 交付的指令编码
    .npc_normal        (if_npc_normal)   // → 未被劫持的 next-PC(仅观测)
  );

  // ── ② u_ifid: ← if_*(IFU), 出 if_id_* → IDU / u_idex ──
  if_id_reg u_ifid (
    .clk               (clk),   // 时钟
    .rst               (rst),   // 同步复位
    // ← 上游 IFU
    .if_valid          (if_valid),   // ← IFU: 交付有效
    .if_pc             (if_pc),   // ← IFU: 指令 PC
    .if_inst           (if_inst),   // ← IFU: 指令编码
    .if_ready          (if_id_ready),   // → IFU: 本级能收(逆流反压)
    // → 下游 IDU / u_idex
    .id_valid          (if_id_valid),   // → ID 级槽位有效
    .id_pc             (if_id_pc),   // → ID 级指令 PC
    .id_inst           (if_id_inst),   // → IDU: 指令编码
    .id_ready          (id_ready),   // ← u_idex: 下游能收
    .flush             (ifid_flush)   // ← u_redirect: 跳转冲刷错误路径
  );

  // ── ③ IDU 纯组合: ← if_id_inst, 出 idu_* → u_idex / RF ──
  IDU u_idu (
    .inst              (if_id_inst),   // ← u_ifid: 待译码指令
    .rs1               (idu_rs1),   // → RF: 源寄存器 1 地址
    .rs2               (idu_rs2),   // → RF: 源寄存器 2 地址
    .rd                (idu_rd),   // → u_idex: 目的寄存器
    .rs1_en            (idu_rs1_en),   // → u_idex: rs1 读使能
    .rs2_en            (idu_rs2_en),   // → u_idex: rs2 读使能
    .rd_en             (idu_rd_en),   // 写 rd 使能
    .imm               (idu_imm),   // → u_idex: 展开后的立即数
    .alu_op            (idu_alu_op),   // → u_idex: ALU 运算码
    .alu_en            (idu_alu_en),   // → u_idex: 使用 ALU
    .alu_src2_imm      (idu_alu_src2_imm),   // → u_idex: 第二操作数取 imm
    .alu_src1_pc       (idu_alu_src1_pc),   // → u_idex: 第一操作数取 PC
    .wb_sel            (idu_wb_sel),   // 写回来源选择
    .npc_sel           (idu_npc_sel),   // → u_idex: next-PC 选择(未回连 IFU)
    .mem_re            (idu_mem_re),   // → u_idex: load 使能
    .mem_we            (idu_mem_we),   // → u_idex: store 使能
    .mem_width         (idu_mem_width),   // 访存宽度
    .mem_signed        (idu_mem_signed),   // load 符号扩展
    .branch_type       (idu_branch_type),   // → u_idex: 分支条件类型
    .invalid           (idu_invalid),   // 非法指令标记(未接 aborted)
    .csr_idx           (idu_csr_idx),   // CSR 地址
    .csr_wen           (idu_csr_wen),   // CSR 写使能
    .csr_s_w           (idu_csr_s_w),   // csrrs / csrrw
    .fence_i           (idu_fence_i)   // fence.i
  );

  // ── ④ RF: 读口在 ID 段(← idu_rs*), 写口由 WB 回绕(← wb_data/wb_rd) ──
  RegisterFile #(.ADDR_WIDTH(5), .DATA_WIDTH(32)) u_regfile (
    .clk               (clk),   // 时钟
    .w_data            (wb_data),   // ← WBU: 选出的写回值
    .w_addr            (wb_rd),   // ← u_memwb: 目的寄存器
    .r_addr1           (idu_rs1),   // ← IDU: 读地址 1
    .r_addr2           (idu_rs2),   // ← IDU: 读地址 2
    .wen               (wb_valid && wb_rd_en),   // ← WB: 写使能(valid && rd_en)
    .r_data1           (rf_rdata1),   // → u_idex: 操作数 1(组合读)
    .r_data2           (rf_rdata2),   // → u_idex: 操作数 2(组合读)
    .r_a0              ()   // → a0 观测口(当前悬空)
  );


  // ── ⑤' hazard_unit: RAW 冒险判定(结果在逻辑区仲裁成 idex_bubble) ──
  hazard_unit u_hazard (
    .id_valid    (if_id_valid),   // ← u_ifid: IF/ID 槽里有指令
    .id_rs1      (idu_rs1),       // ← IDU: 要读的源寄存器 1
    .id_rs2      (idu_rs2),       // ← IDU: 要读的源寄存器 2
    .id_rs1_en   (idu_rs1_en),    // ← IDU: 真的读 rs1 吗
    .id_rs2_en   (idu_rs2_en),    // ← IDU: 真的读 rs2 吗

    .ex_valid    (ex_valid),      // ← u_idex
    .ex_rd       (ex_rd),         // ← u_idex
    .ex_rd_en    (ex_rd_en),      // ← u_idex
    .mem_valid   (mem_valid),     // ← u_exmem
    .mem_rd      (mem_rd),        // ← u_exmem
    .mem_rd_en   (mem_rd_en),     // ← u_exmem
    .wb_valid    (wb_valid),      // ← u_memwb
    .wb_rd       (wb_rd),         // ← u_memwb
    .wb_rd_en    (wb_rd_en),      // ← u_memwb

    .stall       (raw_hazard)          // → u_idex.stall
  );

  // ── ⑤'' redirect_unit: 跳转重定向(EX 判定 → 改 PC / 冲前端 / 拒收旧应答) ──
  redirect_unit u_redirect (
    .clk(clk), .rst(rst),
    .ex_valid(ex_valid), .ex_ready(ex_ready),
    .ex_npc_sel(ex_npc_sel), .ex_branch_taken(ex_branch_taken),
    .ex_alu_result(ex_alu_result),
    .if_valid(if_valid), .if_pc(if_pc), .if_id_ready(if_id_ready),
    .ifu_done(ifu_done),
    .ifu_req_valid(ifu_req_valid), .ifu_req_pulse(ifu_req_pulse),
    .ifu_npc_sel(ifu_npc_sel), .ifu_pc_we(ifu_pc_we),
    .ifu_handshake(ifu_handshake),
    .ifid_flush(ifid_flush), .idex_flush(idex_flush)
  );

  // ── ⑤ u_idex: ← ID 段, 出 ex_* → EXU / u_exmem ──
  id_ex_reg u_idex (
    .clk               (clk),   // 时钟
    .rst               (rst),   // 同步复位

    // ── 上游: ID 段 ──
    .id_valid          (if_id_valid),   // ← u_ifid: 槽位有效
    .id_pc             (if_id_pc),   // ← u_ifid: 指令 PC
    .id_inst           (if_id_inst),   // ← u_ifid: 已寄存的指令编码
    .id_rs1_data       (rf_rdata1),   // ← RF: 操作数 1
    .id_rs2_data       (rf_rdata2),   // ← RF: 操作数 2
    .id_imm            (idu_imm),   // ← IDU: 立即数
    .id_rd             (idu_rd),   // ← IDU: 目的寄存器
    .id_rd_en          (idu_rd_en),
    .id_alu_op         (idu_alu_op),   // ← IDU: ALU 运算码
    .id_alu_en         (idu_alu_en),   // ← IDU: 使用 ALU
    .id_alu_src2_imm   (idu_alu_src2_imm),   // ← IDU: 第二操作数取 imm
    .id_alu_src1_pc    (idu_alu_src1_pc),   // ← IDU: 第一操作数取 PC
    .id_npc_sel        (idu_npc_sel),   // ← IDU: next-PC 选择
    .id_branch_type    (idu_branch_type),   // ← IDU: 分支条件类型
    .id_mem_re         (idu_mem_re),   // ← IDU: load 使能
    .id_mem_we         (idu_mem_we),   // ← IDU: store 使能
    .id_mem_width      (idu_mem_width),
    .id_mem_signed     (idu_mem_signed),
    .id_wb_sel         (idu_wb_sel),   // ← IDU: 写回来源
    .id_csr_idx        (idu_csr_idx),
    .id_csr_wen        (idu_csr_wen),
    .id_csr_s_w        (idu_csr_s_w),
    .id_fence_i        (idu_fence_i),   // ← IDU: fence.i
    .id_invalid        (idu_invalid),   // ← IDU: 非法指令
    .id_ready          (id_ready),   // → u_ifid: 本级能收(逆流反压)

    // ── 下游: EX 段 ──
    .ex_valid          (ex_valid),   // → EX 级槽位有效
    .ex_pc             (ex_pc),   // → EX 级指令 PC
    .ex_inst           (ex_inst),   // → EX 级指令编码
    .ex_rs1_data       (ex_rs1_data),   // → EX 级操作数 1
    .ex_rs2_data       (ex_rs2_data),   // → EX 级操作数 2
    .ex_imm            (ex_imm),   // → EX 级立即数
    .ex_rd             (ex_rd),   // → EX 级目的寄存器
    .ex_rd_en          (ex_rd_en),
    .ex_alu_op         (ex_alu_op),   // → EX 级 ALU 运算码
    .ex_alu_en         (ex_alu_en),   // → EX 级使用 ALU
    .ex_alu_src2_imm   (ex_alu_src2_imm),   // → EX 级操作数选择
    .ex_alu_src1_pc    (ex_alu_src1_pc),   // → EX 级第一操作数取 PC
    .ex_npc_sel        (ex_npc_sel),   // → EX 级 next-PC 选择
    .ex_branch_type    (ex_branch_type),   // → EX 级分支条件类型
    .ex_mem_re         (ex_mem_re),   // → EX 级 load 使能
    .ex_mem_we         (ex_mem_we),   // → EX 级 store 使能
    .ex_mem_width      (ex_mem_width),
    .ex_mem_signed     (ex_mem_signed),
    .ex_wb_sel         (ex_wb_sel),   // → EX 级写回来源
    .ex_csr_idx        (ex_csr_idx),
    .ex_csr_wen        (ex_csr_wen),
    .ex_csr_s_w        (ex_csr_s_w),
    .ex_fence_i        (ex_fence_i),   // → EX 级 fence.i
    .ex_invalid        (ex_invalid),   // → EX 级非法指令
    .ex_ready          (ex_ready),   // ← u_exmem: 下游能收

    // ── 控制 ──
    .flush             (idex_flush),   // ← u_redirect: 跳转冲刷错误路径
    .stall             (idex_bubble)
  );


  // ── ⑥ EXU 纯组合: ← ex_*, 出 ex_alu_result → u_exmem ──
  EXU u_exu (
    .rs1_data          (ex_rs1_data),   // ← u_idex: 操作数 1
    .rs2_data          (ex_rs2_data),   // ← u_idex: 操作数 2
    .imm               (ex_imm),   // ← u_idex: 立即数
    .alu_en            (ex_alu_en),   // ← u_idex: 使用 ALU
    .alu_op            (ex_alu_op),   // ← u_idex: ALU 运算码
    .alu_src2_imm      (ex_alu_src2_imm),   // ← u_idex: 第二操作数取 imm
    .alu_src1_pc       (ex_alu_src1_pc),   // ← u_idex: 第一操作数取 PC
    .pc                (ex_pc),   // ← u_idex: 本指令 PC(不能用取指 PC)
    .branch_type       (ex_branch_type),   // ← u_idex: 分支条件类型
    .alu_result        (ex_alu_result),   // → u_exmem: 结果 / 地址 / 跳转目标
    .branch_taken      (ex_branch_taken)   // → 分支成立(当前未回连 IFU)
  );


  // ── ⑦ u_exmem: ← EX 段, 出 mem_* → u_memwb ──
  ex_mem_reg u_exmem (
    .clk               (clk),   // 时钟
    .rst               (rst),   // 同步复位

    // ── 上游: EX 段 ──
    .ex_valid          (ex_valid),   // ← u_idex: 槽位有效
    .ex_pc             (ex_pc),   // ← u_idex: 指令 PC
    .ex_inst           (ex_inst),   // ← u_idex: 指令编码
    .ex_alu_result     (ex_alu_result),   // ← EXU: 运算结果
    .ex_rs1_data       (ex_rs1_data),   // ← u_idex: CSR 写数据
    .ex_rs2_data       (ex_rs2_data),   // ← u_idex: store 数据
    .ex_imm            (ex_imm),   // ← u_idex: 立即数(lui)
    .ex_rd             (ex_rd),   // ← u_idex: 目的寄存器
    .ex_rd_en          (ex_rd_en),   // ← u_idex: 写 rd 使能
    .ex_mem_re         (ex_mem_re),   // ← u_idex: load 使能
    .ex_mem_we         (ex_mem_we),   // ← u_idex: store 使能
    .ex_mem_width      (ex_mem_width),
    .ex_mem_signed     (ex_mem_signed),
    .ex_wb_sel         (ex_wb_sel),   // ← u_idex: 写回来源
    .ex_csr_idx        (ex_csr_idx),
    .ex_csr_wen        (ex_csr_wen),
    .ex_csr_s_w        (ex_csr_s_w),
    .ex_invalid        (ex_invalid),   // ← u_idex: 非法指令
    .ex_ready          (ex_ready),   // → u_idex: 本级能收(逆流反压)

    // ── 下游: MEM 段 ──
    .mem_valid         (mem_valid),   // → MEM 级槽位有效
    .mem_pc            (mem_pc),   // → MEM 级指令 PC
    .mem_inst          (mem_inst),   // → MEM 级指令编码
    .mem_alu_result    (mem_alu_result),   // → MEM 级 ALU 结果
    .mem_rs1_data      (mem_rs1_data),   // → MEM 级 CSR 写数据
    .mem_rs2_data      (mem_rs2_data),   // → MEM 级 store 数据
    .mem_imm           (mem_imm),   // → MEM 级立即数
    .mem_rd            (mem_rd),   // → MEM 级目的寄存器
    .mem_rd_en         (mem_rd_en),   // → MEM 级写 rd 使能
    .mem_re            (mem_re),   // → MEM 级 load 使能(LSU 未接)
    .mem_we            (mem_we),   // → MEM 级 store 使能(LSU 未接)
    .mem_width         (mem_width),   // → MEM 级访存宽度(LSU 未接)
    .mem_signed        (mem_signed),   // → MEM 级符号扩展(LSU 未接)
    .mem_wb_sel        (mem_wb_sel),   // → MEM 级写回来源
    .mem_csr_idx       (mem_csr_idx),
    .mem_csr_wen       (mem_csr_wen),
    .mem_csr_s_w       (mem_csr_s_w),
    .mem_invalid       (mem_invalid),   // → MEM 级非法指令
    .mem_ready         (mem_ready),   // ← u_memwb: 下游能收(当前恒 1)

    // ── 控制 ──
    .flush             (1'b0)   // ← 冲刷(当前固定 0, 未接分支)
  );

  // ── ⑧ u_memwb: ← MEM 段, 出 wb_* → WBU / RF ──
  mem_wb_reg u_memwb (
    .clk               (clk),   // 时钟
    .rst               (rst),   // 同步复位
    // ── 上游: MEM 段 ──
    .mem_valid         (mem_valid),   // ← u_exmem: 槽位有效
    .mem_pc            (mem_pc),   // ← u_exmem: 指令 PC
    .mem_inst          (mem_inst),   // ← u_exmem: 指令编码
    .mem_alu_result    (mem_alu_result),   // ← u_exmem: ALU 结果
    .mem_mem_data      (rdata_out),   // ← LSU.rdata_out
    .mem_csr_data      (32'b0),   // ← CSRFile 读口(当前桩 0)
    .mem_rs1_data      (mem_rs1_data),   // ← u_exmem: CSR 写数据
    .mem_imm           (mem_imm),   // ← u_exmem: 立即数(lui)
    .mem_wb_sel        (mem_wb_sel),   // ← u_exmem: 写回来源
    .mem_rd            (mem_rd),   // ← u_exmem: 目的寄存器
    .mem_rd_en         (mem_rd_en),   // ← u_exmem: 写 rd 使能
    .mem_csr_idx       (mem_csr_idx),
    .mem_csr_wen       (mem_csr_wen),
    .mem_csr_s_w       (mem_csr_s_w),
    .mem_invalid       (mem_invalid),   // ← u_exmem: 非法指令
    .mem_ready         (mem_ready),   // → u_exmem: 本级能收(逆流反压)
    // ── 下游: WB 段 ──
    .wb_valid          (wb_valid),   // → WB 级槽位有效
    .wb_pc             (wb_pc),   // → WB 级指令 PC
    .wb_inst           (wb_inst),   // → WB 级指令编码
    .wb_alu_result     (wb_alu_result),   // → WBU: ALU 结果
    .wb_mem_data       (wb_mem_data),   // → WBU: 访存数据
    .wb_csr_data       (wb_csr_data),   // → WBU: CSR 读值
    .wb_rs1_data       (wb_rs1_data),   // → CSR 写数据(CSR 未接)
    .wb_imm            (wb_imm),   // → WBU: 立即数(lui)
    .wb_wb_sel         (wb_wb_sel),   // → WBU: 写回来源选择
    .wb_rd             (wb_rd),   // → RF.w_addr: 目的寄存器
    .wb_rd_en          (wb_rd_en),   // → RF.wen: 写 rd 使能
    .wb_csr_idx        (wb_csr_idx),
    .wb_csr_wen        (wb_csr_wen),
    .wb_csr_s_w        (wb_csr_s_w),
    .wb_invalid        (wb_invalid),   // → 非法指令(未接 aborted)
    .wb_ready          (1'b1),   // ← 终点恒 1: WB 无下游
    // ── 控制 ──
    .flush             (1'b0),   // ← 冲刷(当前固定 0, 未接分支)
    .mem_stall         (mem_stall)
  );


  // ── ⑨ WBU 纯组合: ← wb_*, 出 wb_data → RF.w_data ──
  WBU u_wbu (
    .pc4               (wb_pc + 32'd4),   // ← wb_pc + 4: jal/jalr 链接地址
    .alu_result        (wb_alu_result),   // ← u_memwb: ALU 结果
    .mem_data          (wb_mem_data),   // ← u_memwb: 访存数据
    .csr_data          (wb_csr_data),   // ← u_memwb: CSR 读值
    .imm               (wb_imm),   // ← u_memwb: 立即数(lui)
    .wb_sel            (wb_wb_sel),   // ← u_memwb: 写回来源选择
    .wb_data           (wb_data)   // → RF.w_data: 选出的写回值
  );

  // ── ⑨' retire_unit: 退休观测 → 架构 PC / halt / 顶层调试输出 ──
  retire_unit u_retire (
    .clk(clk), .rst(rst),
    .wb_valid(wb_valid), .wb_inst(wb_inst), .wb_pc(wb_pc),
    .pc(pc), .halt(halt),
    .retire_inst_dbg(retire_inst_dbg), .inst_retire(inst_retire)
  );

  // ── ⑩ LSU: MEM 段访存(纯组合, 结果靠 u_memwb 锁存) ──
  LSU_pipe u_lsu (
    .clk(clk), .rst(rst),
    .mem_valid(mem_valid), .mem_we(mem_we), .mem_re(mem_re),
    .mem_width(mem_width), .mem_signed(mem_signed),
    .mem_addr(mem_alu_result), .mem_wdata(mem_rs2_data),
    .lsu_req_valid(lsu_req_valid), .lsu_req_we(lsu_req_we),
    .lsu_req_addr(lsu_req_addr), .lsu_req_wdata(lsu_req_wdata),
    .lsu_req_wstrb(lsu_req_wstrb),
    .lsu_rdata(lsu_rdata), .rdata_out(rdata_out)
  );

  // ── ⑪ 总线主端通路: arbiter + AXI master 打包 ──
  //   对外 AXI 主口与 axi_xbar.m_* 对齐; 将来插 xbar 时只改这里的接线
  cpu_bus_unit u_cpu_bus (
    .clk(clk), .rst(rst),
    // IFU 侧
    .ifu_req_valid(ifu_req_pulse), .ifu_req_addr(ifu_req_addr),
    .ifu_req_len(8'd0),          // 单字取指: arlen=0 → rlast=1, 不做 burst
    .ifu_done(ifu_done), .ifu_rdata(ifu_rdata),
    // LSU 侧
    .lsu_req_valid(lsu_req_valid), .lsu_req_we(lsu_req_we),
    .lsu_req_addr(lsu_req_addr), .lsu_req_wdata(lsu_req_wdata),
    .lsu_req_wstrb(lsu_req_wstrb),
    .lsu_ready(lsu_ready), .lsu_rdata(lsu_rdata),
    // AXI 主口 → dpic_mem (将来这里插 xbar)
    .araddr(d_araddr), .arlen(d_arlen), .arvalid(d_arvalid), .arready(d_arready),
    .rdata(d_rdata), .rresp(d_rresp), .rvalid(d_rvalid),
    .rlast(d_rlast), .rready(d_rready),
    .awaddr(d_awaddr), .awvalid(d_awvalid), .awready(d_awready),
    .wdata(d_wdata), .wstrb(d_wmask), .wvalid(d_wvalid), .wready(d_wready),
    .bresp(d_bresp), .bvalid(d_bvalid), .bready(d_bready)
  );

  // ── ⑫ 主存从设备(DPI-C, 单跑) ──
  //    R=1 → 读延迟约 3 拍, 足以验 MEM 段多拍冻结; 想拉长改 .R(5)
  dpic_mem #(.R(1)) u_dmem (
    .clk(clk),
    .araddr(d_araddr), .arvalid(d_arvalid), .arready(d_arready), .arlen(d_arlen),
    .rdata(d_rdata), .rresp(d_rresp), .rvalid(d_rvalid),
    .rready(d_rready), .rlast(d_rlast),
    .awaddr(d_awaddr), .awvalid(d_awvalid), .awready(d_awready),
    .wdata(d_wdata), .wmask(d_wmask), .wvalid(d_wvalid), .wready(d_wready),
    .bresp(d_bresp), .bvalid(d_bvalid), .bready(d_bready)
  );


  //===========================================================================
  // 9. 顶层胶水 (只剩常量绑定与两行停顿仲裁; 所有时序逻辑都在子模块内)
  //===========================================================================

  // ── 9.1 停顿仲裁 (纯胶水: 一行反相 + 一行与门, 不值得抽模块) ──
  assign mem_stall    = !lsu_ready;                  // 总线没完成 → 冻 MEM + 上游
  // ★ RAW 注气泡不能被 mem_stall 屏蔽。
  //   mem_stall(访存等总线)会冻住 MEM 及上游, 但 hazard_unit 在这期间
  //   仍然持续报 RAW。若把 idex_bubble 压成 0, 解冻那一拍 ID 段那条
  //   依赖 load 结果的指令已经被放行, 读到的是尚未写回的旧值 → 静默算错。
  //   注气泡与「保持」不冲突: u_idex 的清零分支优先级高于 id_ready,
  //   而 mem_stall 时 id_ready 本就为 0, 清空气泡不会往下游传。
  assign idex_bubble  = raw_hazard; // 用于idex的stall

  // ── 9.2 顶层输出常量 (其余输出由 u_retire 直接驱动端口) ──
  assign aborted         = 1'b0;         // → 非法指令终止(当前未接)
  assign state_dbg       = 3'b0;         // → 相位观测(当前未接)
  assign mmio_dbg        = 1'b0;         // → MMIO 标记(当前未接)

endmodule
