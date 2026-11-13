`include "npc_defs.vh"

// redirect_unit — 跳转重定向控制器 (不含 CSR: ECALL / MRET 暂不处理)
//
//   跳转在 EX 段判定, 但前端 IFU 已经按 PC+4 推测取了两条指令, 总线里
//   还可能有一笔撤不回来的取指请求。所以「跳」不是改 PC 一个动作, 是
//   三件事在若干拍内协调完成:
//     ① 本拍把目标地址写进 pc_reg (ifu_npc_sel / ifu_pc_we)
//     ② 持续冲刷 IF/ID、ID/EX 两级, 挡住错误路径 (ifid_flush / idex_flush)
//     ③ 拒收旧路径返回的应答 (ifu_handshake), 直到目标指令真的到手
//
//   ★ 为什么状态放在这里而不是随指令走级间寄存器:
//       这些 reg 描述的是「整台机器当前是否处于改道中」, 不是某条指令的属性。
//       它们要作用到最前端的 IFU, 而级间寄存器只会往 MEM/WB(下游)走;
//       且冲刷期间前端全是气泡, 没有指令能携带状态, 也不可能活到总线
//       把目标指令送回来(4~6 拍, 而 jal 两拍就退休了)。
//
//   ★ 取指请求整形(电平 → 单拍脉冲)也放在这里:
//       drop_resp_r 需要 ifu_req_latched_r 判断「有没有在飞请求」,
//       合并后这根状态不必跨模块引到顶层。
module redirect_unit (
  input  wire        clk,
  input  wire        rst,

  // ── EX 段: 本拍在执行的指令想不想跳 ──
  input  wire        ex_valid,
  input  wire        ex_ready,          // 本拍 jal 能进 MEM 才允许触发
  input  wire [2:0]  ex_npc_sel,
  input  wire        ex_branch_taken,
  input  wire [31:0] ex_alu_result,     // 跳转目标(pc+imm / rs1+imm)

  // ── IFU 交付侧: 目标地址那条指令到了没 ──
  input  wire        if_valid,
  input  wire [31:0] if_pc,
  input  wire        if_id_ready,

  // ── 总线侧: 应答 ──
  input  wire        ifu_done,

  // ── 取指请求整形: IFU 电平 → 总线单拍脉冲 ──
  input  wire        ifu_req_valid,     // ← IFU: 电平, 保持到应答
  output wire        ifu_req_pulse,     // → cpu_bus_unit.ifu_req_valid

  // ── → IFU ──
  output wire [2:0]  ifu_npc_sel,       // 仅重定向首拍给跳转类型, 其余恒 PC4
  output wire        ifu_pc_we,         // pc_reg 写使能
  output wire        ifu_handshake,     // 门控后的 handshake_done

  // ── → 前端两级段寄存器 ──
  output wire        ifid_flush,
  output wire        idex_flush
);

  // ── 组合: 判定与门控 ──
  wire        ex_redirect;         // 本拍 EX 段确认跳转成立(一拍事件)
  wire [31:0] ex_redirect_pc;      // 目标地址(jalr 已清 bit0)
  wire        redirect_done;       // IFU 已举着目标地址的指令

  // ── 时序: 跨多拍的整机状态 ──
  reg         redirect_r;          // 「改道中」告示牌
  reg  [31:0] redirect_target_r;   // 目标地址快照
  reg         drop_resp_r;         // 有一份旧应答待拒收
  reg         ifu_req_latched_r;   // 取指请求已转达, 等 ifu_done 擦掉

  // ── 取指: 电平请求 → 单拍脉冲 ──
  //   arbiter.ifu_pending_r 按 icache 脉冲设计; 若请求持续为 1,
  //   完成拍会命中「置起优先」分支而清不掉, 导致不停重复取指。
  assign ifu_req_pulse = ifu_req_valid && !ifu_req_latched_r;

  always @(posedge clk)
  begin
    if (rst)                  ifu_req_latched_r <= 1'b0;
    else if (ifu_done)        ifu_req_latched_r <= 1'b0;
    else if (ifu_req_pulse)   ifu_req_latched_r <= 1'b1;
  end

  // ex_ready: 保证 jal 本拍能进 MEM, 否则 flush u_idex 会把它清掉,
  //           link 地址就写不回 RF。
  // !redirect_r: 重定向只触发一次, EX 段冻结时也不会重复触发。
  assign ex_redirect = ex_valid && ex_ready && !redirect_r && (
        (ex_npc_sel == `NPC_JAL) ||
        (ex_npc_sel == `NPC_JALR) ||
        ((ex_npc_sel == `NPC_BR) && ex_branch_taken));

  // ★ 与 IFU.npc_normal 的 NPC_JALR 分支必须算出同一个值, 否则
  //   redirect_done 永不成立 → 永久冲刷死锁。
  assign ex_redirect_pc = (ex_npc_sel == `NPC_JALR)
                        ? {ex_alu_result[31:1], 1'b0}
                        : ex_alu_result;

  // 非重定向拍一律 PC+4, 避免 ecall/mret 的 npc_sel 把 PC 改成 mtvec(0)
  assign ifu_npc_sel = ex_redirect ? ex_npc_sel : `NPC_PC4;

  // 目标 PC 处的指令一旦交付, 立即解除冲刷; 解除拍要恢复 fire 推 PC
  assign redirect_done = if_valid && (if_pc == redirect_target_r);

  // ── ifu_pc_we: pc_reg 的写使能 (三种拍, 任一成立就写) ──────────────────
  //   IFU 内部: else if (pc_we) pc_reg <= npc_normal;
  //   npc_normal 由 ifu_npc_sel 决定: 重定向首拍 = 跳转目标, 其余恒 cur_pc+4。
  //
  //   ① ex_redirect: 跳转首拍「强制写目标地址」。
  //      此时 IFU 往往没在交付(if_valid=0), ②不成立, 只能靠这一项把目标
  //      装进 pc_reg。它与 ifu_npc_sel 同拍配合, 才完成「改 PC」。
  //
  //   ② if_valid && if_id_ready: 正常交付拍「推 PC+4」(改动前的原式)。
  //      与 IFU 的 fire 同拍松手; pc4 参照本次交付指令的 PC, 不是 pc_reg。
  //
  //   ③ (!redirect_r || redirect_done): 给 ② 加的闸门。
  //      改道期间(redirect_r=1 且目标指令未回)禁止推 PC, 否则刚写入的
  //      目标地址下一拍就被 +4 冲掉, 目标指令永远取不到。
  //      redirect_done 那拍必须恢复推 PC, 否则 pc_reg 一直停在目标地址,
  //      会重复取同一条指令。
  //  注: redirect_r 是寄存器, 跳转首拍读到的是旧值 0, 所以 ① 此时不依赖 ③。
  assign ifu_pc_we = ex_redirect ||
                     (if_valid && if_id_ready && (!redirect_r || redirect_done));

  // 重定向发生时若已有取指请求在飞, 吞掉它的一次应答(总线侧照常完成)
//   drop_resp_r 管的是「几拍前发出的、还没回来的」那笔
// !ex_redirect 管的是「就在跳这一拍、当场完成的」那笔
  assign ifu_handshake = ifu_done && !drop_resp_r && !ex_redirect;

  assign ifid_flush = redirect_r && !redirect_done;   // ！re 这个逻辑防止自己重定向后的指令被冲掉
  assign idex_flush = redirect_r;

  always @(posedge clk)
  begin
    if (rst)
    begin
      redirect_r        <= 1'b0;
      redirect_target_r <= 32'b0;
      drop_resp_r       <= 1'b0;
    end
    else if (ex_redirect)   // 开始锁存
    begin
      redirect_r        <= 1'b1;
      redirect_target_r <= ex_redirect_pc;
      // ifu_done 同拍说明事务刚好完成, 无需再吞; 否则锁存标记等它完成
      // latch 慢一拍恰好只挡「改道前已接单」的请求: T 拍刚发的请求地址随 pc_reg 已变新, 不该吞
      drop_resp_r       <= ifu_req_latched_r && !ifu_done;
    end
    else   // 清理的逻辑
    begin
      if (ifu_done)       drop_resp_r <= 1'b0;
      if (redirect_done)  redirect_r  <= 1'b0;
    end
  end

endmodule
