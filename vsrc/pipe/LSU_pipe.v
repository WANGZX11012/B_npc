`include "npc_defs.vh"
module LSU_pipe (

    input   wire        clk,        // 预留: 纯组合阶段用不上, 将来 MTRACE/flush 会用
    input   wire        rst,        // 预留(统一改成 rst, 与其他模块一致)

    // ── A. 上游: ex_mem_reg 的寄存输出 (MEM 段这一拍的指令) ──
    input   wire        mem_valid,     // 本槽有有效指令
    input   wire        mem_we,        // store
    input   wire        mem_re,        // load
    input   wire [1:0]  mem_width,     // MEM_BYTE / HALF / WORD
    input   wire        mem_signed,    // load 符号扩展(1) / 零扩展(0)
    input   wire [31:0] mem_addr,      // ← mem_alu_result
    input   wire [31:0] mem_wdata,     // ← mem_rs2_data

    // ── B. 请求侧 → arbiter_pipe.lsu_req_* ──
    output  wire        lsu_req_valid, // 电平: 持续到本单完成(靠 MEM 段冻结保持)
    output  wire        lsu_req_we,
    output  wire [31:0] lsu_req_addr,
    output  wire [31:0] lsu_req_wdata, // 已按字节摆位
    output  wire [3:0]  lsu_req_wstrb, // 写字节选通 wmask gen 防止wdata覆盖错地方

    // ── C. 响应侧 ← arbiter_pipe (只留数据) ──
    input   wire [31:0] lsu_rdata,     // 总线返回的 32 位原始数据

    // ── D. 结果 → mem_wb_reg.mem_mem_data ──
    output  wire [31:0] rdata_out      // 已裁剪 + 符号/零扩展

);

    wire is_access = mem_re || mem_we;

    wire [31:0] rdata_shifted = lsu_rdata >> {mem_addr[1:0], 3'b000};  // addr[1:0]*8 位
    wire [7:0]  b = rdata_shifted[7:0];
    wire [15:0] h = rdata_shifted[15:0];



    reg [3:0] wmask_gen;
    always @(*)
    begin
        case (mem_width)
            `MEM_BYTE: wmask_gen = (4'b0001 << mem_addr[1:0]);
            `MEM_HALF: wmask_gen = mem_addr[1] ? 4'b1100 : 4'b0011;
            default:   wmask_gen = 4'b1111;          // MEM_WORD
      endcase
    end

    assign lsu_req_valid = mem_valid && is_access;
    assign lsu_req_we = mem_we;
    assign lsu_req_addr = mem_addr;
    assign lsu_req_wstrb = wmask_gen;
    assign lsu_req_wdata = (mem_width == `MEM_BYTE) ? {4{mem_wdata[ 7:0]}} :
                         (mem_width == `MEM_HALF) ? {2{mem_wdata[15:0]}} :
                         mem_wdata;
    assign rdata_out = (mem_width == `MEM_BYTE) ? (mem_signed ? {{24{b[7]}},   b} : {24'b0, b})
                   : (mem_width == `MEM_HALF) ? (mem_signed ? {{16{h[15]}},  h} : {16'b0, h})
                   : lsu_rdata;



endmodule
