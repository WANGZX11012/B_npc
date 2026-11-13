`include "npc_defs.vh"

// if_id_reg — IF/ID 段寄存器
//   流水线第一级。IF 取到指令后锁存到这里, ID 每拍从这里读。
module if_id_reg (
  input  wire        clk,
  input  wire        rst,

  // ── 上游: IFU ──
  input  wire        if_valid,      // ← IFU 这拍取到了有效指令
  input  wire [31:0] if_pc,         // ← ifu_out_pc
  input  wire [31:0] if_inst,       // ← ifu_inst
  output wire        if_ready,      // → IF/ID 寄存器这拍能接收新指 给ifu的

  // ── 下游: IDU ──
  output reg         id_valid,          //当前寄存器锁存的指令是有效的
  output reg  [31:0] id_pc,
  output reg  [31:0] id_inst,
  input  wire        id_ready,      // ID 准备好接收指令

  // ── 控制 ──
  input  wire        flush          // 分支冲刷: 当作从没取过
);

  // 下游能收 = 我空着, 或者我这条这拍就走
  // 反压：下游通过拉低 Ready 信号，强制上游暂停数据生产的机制
  assign if_ready = !id_valid || id_ready;

  always @(posedge clk)
  begin
    if (rst || flush)
    begin
      id_valid <= 1'b0;
      id_pc    <= 32'b0;
      id_inst  <= 32'b0;
    end
    else if (id_ready)          // 本拍把我这条交出去
    begin
      id_valid <= if_valid;     // ← 注意: 不是 1'b1
      id_pc    <= if_pc;
      id_inst  <= if_inst;
    end
    // 其他情况: 保持不动
  end

endmodule
