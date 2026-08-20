// ctrl — 多周期 FSM 控制器

module ctrl (

  // Clock & Reset
  input  wire         clk,
  input  wire         rst,

  // 输入: IDU
  input  wire         idu_mem_re,                      // load 指令
  input  wire         idu_mem_we,                      // store 指令
  input  wire         idu_invalid,                     // 非法指令(未实现/非法编码)

  // 输入: bus done 从设备
  input  wire         ifu_done,                        // IFU fetch complete
  input  wire         lsu_done,                        // LSU access complete

  // 输出: state
  output reg  [2:0]   state,                           // current FSM state

  // 输出: enable signals
  output wire         ir_we,                           // latch IR
  output wire         pc_we,                           // update PC
  output wire         reg_we,                          // write register file
  output wire         fetch_req,                       // FETCH state → IFU
  output wire         mem_req,                         // MEM state → LSU
  output wire         aborted                          // 非法指令/异常终止(对齐 NEMU_ABORT)
);

  localparam [2:0] IDLE = 0, FET = 1, DEC = 2, EXE = 3, MEM = 4, WB = 5, ERR = 6;
  reg [2:0] next_state;

  always @(posedge clk)
    state <= rst ? IDLE : next_state;

  always @(*)
  begin
    case (state)
      IDLE: next_state = FET;
      FET:  next_state = ifu_done ? DEC : FET;
      DEC:  next_state = idu_invalid ? ERR : EXE;   // 非法指令直接转入 ERR 停机
      EXE:  next_state = (idu_mem_re || idu_mem_we) ? MEM : WB;
      MEM:  next_state = lsu_done ? WB : MEM;
      WB:   next_state = FET;
      ERR:  next_state = ERR;                         // 卡死, 直到复位
      default: next_state = IDLE;
    endcase
  end

  assign fetch_req = (state == FET);
  assign mem_req   = (state == MEM);
  assign ir_we     = ifu_done && (state == FET);
  assign pc_we     = (state == WB);   // WB 阶段更新 PC: 此时 pc_reg 仍为本条地址, pc4=pc+4 正确写回 ra; posedge 后 FET 用新 PC
  assign reg_we    = (state == WB);
  assign aborted   = (state == ERR);  // 对齐 NEMU 的 NEMU_ABORT

endmodule
