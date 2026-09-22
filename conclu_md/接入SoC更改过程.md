# 接入 ysyxSoC 更改过程

## 一、总路线

```
① 清理 + 修复 core 内部                        【已完成 — 批次1 中断原子性修复】
     ▼
② 内部级间握手重构                              【当前阶段】
     新增 stage_reg.v（参数化流水段寄存器，带 stall/flush）
     ctrl.v 退役，IFU/IDU/EXU/LSU/WBU 五级各自产生 in.ready / out.valid
     依据: 讲义 B1「总线视角下的处理器设计」（非强制重构，但它是后面每一步省力的前提）
     硬约束: 必须排在 icache 之前 —— 否则 icache 将来要跟着返工
     每批验收: 纯结构变换，total_inst 必须仍是 1915（一位不差）
     ▼
③ 接口层冻结
     AXI4 信号 + ysyxSoC 地址映射（CLINT 0x0200_0000）+ arbiter 改无饥饿调度
     ▼
④ 集成 ysyxSoC（拿仓库、换 mem、联仿跑通）
     ▼
⑤ icache（B4）
     ▼
⑥ 流水线（B5）+ 转发 / 冲刷 / 精确异常 / fence.i
     只动 core 内部，对外 AXI4 接口不动 —— 这是③冻结换来的
     ▼
⑦ 综合 + 时序分析（此时才第一次知道 NPC 真实 Fmax）
```

**接口层 = 分界线以上（别人怎么看你）**：`axi_lite_master.v`（总线语法）、`arbiter.v` / `axi_xbar.v`（总线规则与路由）、地址映射表（`clint.v` 译码 + `timer.c` 的 `CLINT_*` 宏）。冻结后 core 内部随便改。

---

# 2026-09-11 改动总结

三件事：**ctrl 分布式化**、**AXI4-Lite → AXI4**、**core.v 缩略**。均为纯结构变换，`total_inst=1915` 一位不差。

---

## 一、ctrl 集中式 → 分布式握手

### 为什么改

`ctrl.v` 是唯一 FSM，一个 `state` 同时干两件事：驱动控制（`pc_we`/`reg_we`/`fetch_req`/`mem_req`）和描述相位（EXE/MEM/WB）。后果：**相位成了原因而不是结果**，模块之间没有直接握手。

- 流水线做不了：单条 FSM 天生「一次一条指令」；
- 访存与总线解耦不了：LSU 等总线，ctrl 只能干等，其他段全停摆；
- 每加功能都要动 ctrl（中断/异常全塞一个 always，上次 CLINT 就踩过）。

**它是 icache 与流水线的前置条件，不做后面每一步都要返工。**

### 改法

把「我在第几拍」换成「**我手里有没有东西**」，相邻段直接握手：

```
IFU ──hold_valid──► EX_MEM ──exm_done──► LSU ──res_valid──► WB
 ▲                     ▲                  ▲
 └────out_ready(= retire)┴─────────────────┘
stage_dec.v : 只观测，无控制
```

**三段对称**（最值得记的设计点）：

| 段 | 模块 | 占有标志 | 我手里有东西 | 下游收走 |
|---|---|---|---|---|
| IF | `IFU.v` | `hold_valid` | `out_valid` | `out_ready` |
| EX~WB | `EX_MEM.v` | `busy_r` | `exm_done` | `out_ready` |
| MEM | `LSU.v` | `busy` | `res_valid` | `out_ready` |

共同模式：`!busy && in_valid → 占住` → `干活置 done` → `busy && done && out_ready → 松手`。

**为什么必须有保持寄存器**：总线返回是**单拍脉冲**（`handshake_done` 只在返回那拍有效），而 `out_ready`（WB 拍）跟它绝不同拍。不锁进保持寄存器（`res_rdy`/`done_r`/`hold_valid`），「返回」和「收走」永不同时成立，`busy` 清不掉 → **死锁**。

### 文件

| 文件 | 动作 | 说明 |
|---|---|---|
| `vsrc/ctrl.v` | **删除** | 控制信号下放到各段 |
| `vsrc/stage_dec.v` | **新增** | 相位译码器，**纯组合、无 clk、无 reg**，只喂 `state_dbg` |
| `vsrc/EX_MEM.v` | **新增** | EX/MEM 流水寄存器，收纳原寄生在 core 的 `alu_result_r`/`ex_done_r` |
| `vsrc/IFU.v` | 改 | `hold_valid/inst/pc` + `out_valid/out_ready`；`req_valid` 改为自发（`!rst && !hold_valid`） |
| `vsrc/LSU.v` | 改 | `busy/res_rdy/addr_r/wmask_r/wdata_r/rdata_r`；`in_ready/res_valid` 握手 |
| `vsrc/core.v` | 改 | 回归纯互连 |

### 两个易错点

**1. `stage_dec.v` 必须纯组合。** 判决链直接由各段事实组合：

```verilog
assign state = rst     ? `ST_IDLE : aborted       ? `ST_ERR :
               retire  ? `ST_WB   : mem_active    ? `ST_MEM :
               ex_stage_fire ? `ST_EXE : ifu_out_valid ? `ST_DEC : `ST_FET;
```

只要有时序（哪怕一拍），就会出现「它以为的相位」与「真实握手状态」错位。**相位是观测结果，不是原因。** 互斥性（别改书写顺序）：`retire` 要 `lsu_res_valid`，`mem_active` 要 `!lsu_res_valid`；`ex_stage_fire = busy && !done`，而 retire/mem_active 都要求 `done`；`ifu_out_valid` 全程恒 1，只能最后兜底。

**2. 退休判据吸收了原 ctrl 的两路分流：**

```verilog
wire is_mem  = idu_mem_re || idu_mem_we;
wire retire  = exm_done && (!is_mem || lsu_res_valid);  // 退休拍
wire mem_req = is_mem && exm_done;                      // EX 算完且访存 → 下单
```

非访存：`exm_done` 即退休；访存：再等 `lsu_res_valid`。`retire` 是**全局唯一时间基准**，`pc_we`/`reg_we`/CSR 写/中断判决全对齐在它上面。

### 配套：中断判决跟着改

```verilog
wire irq_taken = retire                  // 原为 ctrl_at_state_wb
              && csr_mstatus_mie && clint_mtip
              && (idu_npc_sel != `NPC_ECALL)
              && (idu_npc_sel != `NPC_MRET)
              && !idu_csr_wen;           // 新增：CSR 写指令退休拍不响应中断
```

- 加 `!idu_csr_wen`：CSR 写指令退休拍同时改 CSR 和 `pc_we`，响应中断会撞车；
- 排除 `ecall`：`npc_normal` 恰 = `mtvec`，响应该中断会把 `mepc` 写成 `mtvec`，返回地址丢失；
- 排除 `mret`：`npc_normal` 恰 = `mepc`，新 `mepc` = 旧 `mepc`，死循环；
- `trap_pc = irq_taken ? ifu_npc_normal : ir_pc` —— **中断存下一条（软件绝不 +4），异常存自己（软件 +4）**。

---

## 二、AXI4-Lite → AXI4

### 为什么改

`cpu-interface.md` 要求 AXI4 Master。Lite 没有 `id/len/size/burst/last`，只能单拍定长；SoC 的 xbar / DRAM 控制器期望完整字段，缺字段判协议违例；icache 要一次填一整行 cache line，Lite 表达不出来。

### 逐通道改动（每次只动一个通道，每批回归）

| 通道 | 新增信号 | 常量值 | 为什么 |
|---|---|---|---|
| AR | `arid` `arlen` `arsize` `arburst` | `0 / 8'd0 / 3'd2 / 2'b01` | `arlen=0` 表示 **1 拍**（不是 0 拍）；`arsize=2`→2^2=**4 字节**；`arburst=INCR` |
| R | `rid` `rlast` 进状态机 | — | 迁移判据 `(rvalid && rlast && !stall)`；`done = (rready && rvalid && rlast) \|\| (bvalid && bready)`。`rlast` 是 R 通道**唯一结束标记** |
| AW | `awid` `awlen` `awsize` `awburst` | 同 AR | 与 AR 对称 |
| W | `wlast`；`wmask` 改名 `wstrb` | `wlast=1'b1` | 单拍写恒为最后一拍；`wstrb` 对齐 `cpu-interface.md` |
| B | `bid` | — | 与 `awid` 同源，单 outstanding 无需核对 |

### 几处有意的判断

- **`wmask` → `wstrb`**：`cpu-interface.md` 写的就是 `io_master_wstrb`，名字不齐后面 wrapper 会接错；
- **模块改名 `axi_lite_master` → `ysyx_26020047_axi_master`**：遵守命名规范。文件名同步与否不影响编译（Makefile 用 `wildcard vsrc/*.v`，module 名才是关键）；
- **`rresp`/`bresp` 引出但未用**：`rresp[1]` 才是错误位（`00` OKAY / `01` EXOKAY / `10` SLVERR / `11` DECERR）。当前 slave 未做错误响应，等 slave 侧做完再加，**属已记账技术债，不是漏改**；
- **不加 `rid` 比对**：单 outstanding 下 `rid` 必等于 `arid`，加比对是纯冗余，还给组合路径加深度。

### 单拍 vs 将来 burst

当前 `arlen=0` 是**合法的 AXI4 单拍事务**，功能等价改造前的 Lite，所以 `total_inst` 能一位不差。将来做 burst 只需把 `arlen` 变量化 + R 通道按 `rlast` 计数——**状态机骨架已备好**（这就是 `rlast` 必须进判据、不能恒接 1 的原因）。

---

## 三、core.v 缩略（回归纯互连）

删掉的全是「状态」与「控制」，留下的全是「互连」：

| 删除/移出 | 去向 |
|---|---|
| `state` 寄存器 + `case(state)` | 删除（ctrl 退役） |
| `alu_result_r` / `ex_done_r` | 移入 `EX_MEM.v` |
| `fetch_req` / `mem_req` 的 ctrl 驱动 | IFU / LSU 自己产生 `req_valid` |
| `pc_we` | `assign pc_we = retire` |
| `reg_we` | `idu_rd_en && retire` |

现在 `core.v` 只剩三件职责：**线连接**、**退休判据**、**中断判决**。

---

## 四、本次踩的坑

**Bug：master 例化断线 → 全局死锁**

**现象**：`si 100` 后 `pc` 仍 `0x80000000`，`ir=0`，`state=1`；am-tests 完全卡死无输出。

**根因**：`core.v` 的 `ysyx_26020047_axi_master u_master(...)` 只连了 AXI 五通道，漏掉简单请求侧 8 个端口：`clk` `rst` `req_valid` `req_we` `req_addr` `req_wdata` `req_wstrb` `stall` `done` `resp_rdata`（其中 `clk/rst` 也未连）。

**死锁链**：

```
req_valid 悬空 = 0/X → master 永在 IDLE，done 恒 0
  → arbiter.m_valid_r 停在 1，交易永不完成
  → IFU.handshake_done 永不拉高 → hold_valid 恒 0 → PC 不前进 → 死锁
```

**为什么没早发现（教训）**：
1. Verilator 用 `-Wall -Wno-fatal`，`PINMISSING` 是 warning **不阻断编译**，只看 `%Error` 会静默通过；
2. 我只 grep 信号名检查「master 内部写得对不对」，**从没把端口列表与例化列表逐条对照**；
3. 默认「之前能跑所以连线是好的」——实际改名那批之后例化就已断，只是没有一批验证到它。

**硬性规矩**：例化后立刻 `make 2>&1 | grep -iE "%Error|PINMISSING|MULTIDRIVEN|IMPLICIT"`，不能只看 `%Error`。

---

## 五、验证

| 项目 | 结果 |
|---|---|
| Verilator | 无 `%Error` / `PINMISSING` / `MULTIDRIVEN` / `IMPLICIT` ✅ |
| `am-tests -h` | `total_inst=1915`，与基线完全一致 ✅ |
| `cpu-tests` | add / add-longlong / bit / bubble-sort / crc32 / div / dummy / load-store / hello-str 全 HIT GOOD TRAP ✅ |

结论：三件事均为**纯结构变换**，未改变任何指令级行为。

---

## 六、遗留与技术债

1. **`rresp`/`bresp` 未做错误上报**：等 slave 做出 `SLVERR`/`DECERR` 再加，当前不影响功能；
2. **burst（`arlen>0`）未实现**：icache 阶段（B4）必须做；
3. **SoC wrapper 未做**：内部名 `araddr`/`arvalid`…，规范要求 `io_master_*`。名字由 FIRRTL 从 BlackBox 展开自动生成，**内部模块不用改名**，只需一层 wrapper 做映射 + 接 `clock`/`reset`/`io_interrupt`；
4. **CLINT 地址布局不一致**（老账）：现在 `0xa0000050`，ysyxSoC 是 `0x0200_0000`（`mtime@0xBFF8`、`mtimecmp@0x4000`）。**接 SoC 前一次性改完**；
5. **`arbiter` 单 outstanding**：流水线的拦路虎（B5 重写）；
6. **`AXI_OVERVIEW.md` 已过期**：仍描述 IFU/LSU 各挂独立 master 的老架构；
7. **`rtc.v` 无复位**、`always @` 空格等风格项：单独排期。

---

## 七、下一步

```
① 清理 + 修复 core 内部                        【已完成】
② 级间握手重构（ctrl → 分布式）                【已完成 ← 今天】
③ 接口层冻结
     ├─ AXI4 字段对齐 cpu-interface.md         【已完成 ← 今天】
     ├─ 写 SoC wrapper（io_master_* 映射 + clock/reset/io_interrupt）  【下一步】
     ├─ CLINT 地址布局一次性改成 ysyxSoC 规范     【下一步】
     └─ arbiter 改无饥饿调度                    【下一步，为流水线铺路】
④ 集成 ysyxSoC（拿仓库、换 mem、联仿跑通）
⑤ icache（B4）
⑥ 流水线（B5）+ 转发 / 冲刷 / 精确异常 / fence.i
⑦ 综合 + 时序分析
```

---

# ysyxSoC 代码生成与接入要求（准备 + 环境配置）

> 性质：**准备工作 / 环境配置**。本节清单来自 ysyxSoC 接入任务书，是后续改 NPC 的硬性要求，对应「一、总路线」的第 ③ 步尾 + 第 ④ 步。

## A、生成 ysyxSoC 的 Verilog（一次性）

| 编号 | 命令 / 动作 | 说明 |
|---|---|---|
| A1 | 按 mill 官方文档安装 mill | `mill --version` 检查；**版本 >= 0.11**，不满足就装最新版 |
| A2 | `cd ysyxSoC && make dev-init` | 拉取 rocket-chip 子模块并打 patch；**只需一次** |
| A3 | `cd ysyxSoC && make verilog` | 产物：`ysyxSoC/build/ysyxSoCFull.v` |

A1、A2 只做一次；此后只需 A3。

## B、把 NPC 接入 ysyxSoC（按序执行）

### B1 总线：AXI4-Lite 扩展到完整 AXI4

依 `ysyxSoC/spec/cpu-interface.md` 的 master 总线，补齐 `id / len / size / burst / last`。

### B2 顶层接口命名规范

方向、命名、位宽必须与 `ysyxSoC/spec/cpu-interface.md` **完全一致**：

| 信号 | 方向(CPU 侧) | 位宽 | 名称 |
|---|---|---|---|
| 时钟 | input | 1 | `clock` |
| 复位(高电平有效) | input | 1 | `reset` |
| 外部中断 | input | 1 | `io_interrupt` |
| AXI4 Master 总线 | — | — | `io_master_*`（AW / W / B / AR / R 五通道） |

- CPU 文件名 `ysyx_8位学号.v`；顶层模块 `ysyx_8位学号`；内部模块 `ysyx_8位学号_模块名`。
- **不使用的顶层输出端口 → 赋常数 0**；**不使用的顶层输入端口 → 悬空**。

### B3 把 SoC 外设加入 verilator 编译

- Verilog 文件列表：加入 `ysyxSoC/perip` 及其**子目录下所有 `.v`**。
- include 搜索路径：加入 `ysyxSoC/perip/uart16550/rtl` 和 `ysyxSoC/perip/spi/rtl`。
- 具体怎么加：**RTFM**（`man verilator`）。建议通读 man 的 argument summary。

### B4 verilator 编译选项

- `--timescale "1ns/1ns"`
- `--no-timing`

### B5 顶层模块与改名

- Verilog 文件列表：加入 `ysyxSoC/build/ysyxSoCFull.v`。
- **仿真顶层模块设为 `ysyxSoCFull`**（定义在该文件里）。
- 把 `ysyxSoCFull.v` 里的 `ysyx_00000000` 改成**你的处理器模块名**。
- 处理器模块**不应再包含**之前习题的 AXI4-Lite SRAM 和 UART —— 改用 ysyxSoC 里的存储器和 UART 替代。
- 处理器模块**必须保留 CLINT** —— 它是流片工程里的一个模块，ysyxSoC 不含它。

### B6 仿真 C++ 侧

- 加桩函数，解决链接找不到 `flash_read` / `mrom_read` 的问题：

```cpp
extern "C" void flash_read(int32_t addr, int32_t *data) { assert(0); }
extern "C" void mrom_read(int32_t addr, int32_t *data) { assert(0); }
```

- 在 `main` 中**仿真开始前**加：

```cpp
Verilated::commandArgs(argc, argv);
```

用于解决运行时 plusargs 功能报错。

### B7 编译与首跑

- 用 verilator 编译出仿真可执行文件。
- 若遇**组合回环**错误 → 自行修改 RTL。
- 首跑预期现象：进入仿真主循环，但 **NPC 无有效输出**（留到下一阶段解决）。

### B8 代码检查（暂缓）

- ysyxSoC 有代码检查步骤，但因后续还要改进 NPC，**要求考核前再做**；现在感兴趣也可做，不强制。

## C、与「总路线」的对应 + 当前进度

| 总路线步骤 | 对应本节 |
|---|---|
| ③ 接口层冻结（AXI4 字段 + SoC wrapper） | B1 / B2 |
| ④ 集成 ysyxSoC（拿仓库、换 mem、联仿跑通） | A1-A3 + B3-B7 |

当前进度（截至 2026-09-12）：

| 项 | 状态 | 备注 |
|---|---|---|
| B1 / B2 | 已完成 | AXI4 字段扩展 + wrapper `vsrc/ysyx_26020047.v`（`io_master_*` + `clock/reset/io_interrupt`）|
| ④ 脚手架 | 已完成 | `npc/soc/Makefile` + `make lint` 跑通（elaboration 0 error）|
| ③ CLINT 地址对齐 | 未做 | `0xa0000050` → ysyxSoC `0x0200_0000`（`mtime@0xBFF8`、`mtimecmp@0x4000`）|
| ④ `soc_tb.cpp` | 未做 | `npc/soc/soc_tb.cpp` 缺失 → `make build` / `make run` 尚未跑通 |

## 附：AXI4 Master 端口全表（摘自 `ysyxSoC/spec/cpu-interface.md`，CPU 侧）

| 通道 | 信号 | 方向 | 位宽 |
|---|---|---|---|
| AW | `io_master_awready` | input | 1 |
| AW | `io_master_awvalid` | output | 1 |
| AW | `io_master_awaddr` | output | [31:0] |
| AW | `io_master_awid` | output | [3:0] |
| AW | `io_master_awlen` | output | [7:0] |
| AW | `io_master_awsize` | output | [2:0] |
| AW | `io_master_awburst` | output | [1:0] |
| W | `io_master_wready` | input | 1 |
| W | `io_master_wvalid` | output | 1 |
| W | `io_master_wdata` | output | [31:0] |
| W | `io_master_wstrb` | output | [3:0] |
| W | `io_master_wlast` | output | 1 |
| B | `io_master_bready` | output | 1 |
| B | `io_master_bvalid` | input | 1 |
| B | `io_master_bresp` | input | [1:0] |
| B | `io_master_bid` | input | [3:0] |
| AR | `io_master_arready` | input | 1 |
| AR | `io_master_arvalid` | output | 1 |
| AR | `io_master_araddr` | output | [31:0] |
| AR | `io_master_arid` | output | [3:0] |
| AR | `io_master_arlen` | output | [7:0] |
| AR | `io_master_arsize` | output | [2:0] |
| AR | `io_master_arburst` | output | [1:0] |
| R | `io_master_rready` | output | 1 |
| R | `io_master_rvalid` | input | 1 |
| R | `io_master_rresp` | input | [1:0] |
| R | `io_master_rdata` | input | [31:0] |
| R | `io_master_rlast` | input | 1 |
| R | `io_master_rid` | input | [3:0] |
