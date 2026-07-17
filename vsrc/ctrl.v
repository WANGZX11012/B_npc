module ctrl (
  input  wire clk, rst,
  input  wire idu_mem_re, idu_mem_we,
  input  wire ifu_done,          // IFU bus 取指完成
  input  wire lsu_done,          // LSU bus 访存完成
  output reg  [2:0] state,
  output wire ir_we, pc_we, reg_we, fetch_req, mem_req
);

  localparam [2:0] IDLE = 0, FET = 1, DEC = 2, EXE = 3, MEM = 4, WB = 5;

  reg [2:0] next_state;

  always @(posedge clk)
    state <= rst ? IDLE : next_state;

  always @(*) begin
    case (state)
      IDLE: next_state = FET;
      FET:  next_state = ifu_done ? DEC : FET;
      DEC:  next_state = EXE;
      EXE:  next_state = (idu_mem_re || idu_mem_we) ? MEM : WB; //加了个控制 只有读写请求才会进入MEM状态
      MEM:  next_state = lsu_done ? WB : MEM;              // LSU 完成才走
      WB:   next_state = FET;
      default: next_state = IDLE;
    endcase
  end

  assign fetch_req = (state == FET);
  assign mem_req   = (state == MEM);
  assign ir_we     = ifu_done && (state == FET);
  assign pc_we     = ifu_done && (state == FET);
  assign reg_we    = (state == WB);

endmodule
