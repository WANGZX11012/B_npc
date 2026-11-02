`define I_LEN 32
`define REG_WIDTH 5
// 引入统一控制信号编码：mem_width / wb_sel
`include "npc_defs.vh"

module IDU (
  input  [`I_LEN-1:0]       inst,
  output [`REG_WIDTH-1:0]   rs1,
  output [`REG_WIDTH-1:0]   rs2,
  output [`REG_WIDTH-1:0]   rd,

  output                    rs1_en,
  output                    rs2_en,
  output                    rd_en,

  output [31:0]             imm,
  
  output reg [3:0]          alu_op,
  output reg                alu_en,     //新增控制
  output reg                alu_src2_imm, //alu的第二个输入是rs2 还是imm的判断信号
  output                    alu_src1_pc, // 当为 AUIPC 时，ALU 的第一个操作数由 PC 提供

  output                    mem_re,
  output                    mem_we,
  output [1:0]              mem_width, //字节有1,2,4的选择  
  output                    mem_signed, //符号加载 无符号加载控制                

  output [2:0]              wb_sel,
  output [2:0]              npc_sel, //扩展到3位
  output [2:0]              branch_type,    //BNE BLT等等的判断
  output                    invalid,

  output [11:0]             csr_idx,
  output                    csr_wen,
  output                    csr_s_w,  //csrrs 还是 csrrw的判断位 决定是否要或rs1
  
  output                    fence_i


);

localparam IMM_I = 3'b000;
localparam IMM_S = 3'b001;
localparam IMM_U = 3'b010;
localparam IMM_B = 3'b011;
localparam IMM_J = 3'b100;

  wire [6:0] opcode = inst[6:0];
  wire [2:0] funct3 = inst[14:12];
  wire [6:0] funct7 = inst[31:25];

  //CSR index
  assign csr_idx = inst[31:20];
  


  wire [2:0] imm_type;   // 立即数类型: assign 驱动, 故为 wire

  //具体指令的判断译码（组合逻辑中生成 reg 标志位）指令的注册

  //跳转相关
  reg is_jal;
  reg is_jalr;
  reg is_bne; //rs1 rs2不相等 pc变为pc + imm
  reg is_beq;
  reg is_bge; //大于等于 bigger equal
  reg is_bgeu;
  reg is_blt; //branh less than
  reg is_bltu;


  //load相关
  reg is_lui;
  reg is_lbu;
  reg is_lw;
  reg is_lb;
  reg is_lh;
  reg is_lhu;

  //system
  reg is_ebreak;
  reg is_csrrs; //csr读后置位
  reg is_csrrw; //csr读后写
  reg is_ecall;
  reg is_mret;

  reg is_fence_i; // FENCE / FENCE.I 冲刷icache

  //store相关
  reg is_sb;
  reg is_sw;
  reg is_sh;

  //算术相关
  reg is_auipc;//！！！
  reg is_or;
  reg is_ori;
  reg is_xor;
  reg is_xori;
  reg is_add;
  reg is_addi;
  reg is_sub;
  reg is_slti;
  reg is_sltiu;
  reg is_and; // R-type and
  reg is_andi;//与立即数

  reg is_sra; //移动有关
  reg is_srai;//移动有关
  reg is_srl; //逻辑右移动
  reg is_sll; //逻辑左移
  reg is_slli; // slli (I-type)
  reg is_srli; //把rs1逻辑右移

  
  reg is_sltu;
  reg is_slt;

  always @(*) 
  begin
    is_jal    = 1'b0;
    is_jalr   = 1'b0;
    is_lui    = 1'b0;
    is_auipc  = 1'b0;
    is_sb     = 1'b0;
    is_sw     = 1'b0;
    
    is_lw     = 1'b0;
    is_ebreak = 1'b0;
    is_xor    = 1'b0;
    is_xori   = 1'b0;
    is_add    = 1'b0;
    is_addi   = 1'b0;
    is_sub    = 1'b0;
    is_or     = 1'b0;
    is_ori    = 1'b0;
    is_and    = 1'b0;
    is_andi   = 1'b0;

    is_sh     = 1'b0;
    is_sll    = 1'b0;
    is_slli   = 1'b0;
    is_slti   = 1'b0;
    is_sltiu  = 1'b0;
    is_sra    = 1'b0;
    is_srl    = 1'b0;
    is_srai   = 1'b0;
    is_sltu   = 1'b0;
    is_slt    = 1'b0;
    is_srli   = 1'b0;

    is_bne    = 1'b0;
    is_beq    = 1'b0;
    is_bge    = 1'b0;
    is_bgeu   = 1'b0;
    is_blt    = 1'b0;
    is_bltu   = 1'b0;
    is_lh     = 1'b0;
    is_lhu    = 1'b0;
    is_lb     = 1'b0;
    is_lbu    = 1'b0;

    is_csrrs  = 1'b0;
    is_csrrw  = 1'b0;
    is_ecall  = 1'b0;
    is_mret   = 1'b0;
    is_fence_i  = 1'b0;



    case (opcode)
      7'b1101111: 
      begin // jal
        is_jal = 1'b1;
      end

      7'b1100111: 
      begin // jalr
        if (funct3 == 3'b000) 
          is_jalr = 1'b1;
      end
      
      7'b0110111: 
      begin // lui
        is_lui = 1'b1;
      end

      7'b0010111: 
      begin // auipc
        is_auipc = 1'b1;
      end

      7'b0100011: 
      begin // store
        case (funct3)
          3'b000: begin is_sb = 1'b1; end
          3'b010: begin is_sw = 1'b1; end
          3'b001: begin is_sh = 1'b1; end
          default: ;
        endcase
      end

      7'b0000011: 
      begin // load
        case (funct3)
          3'b000: begin is_lb  = 1'b1; end
          3'b010: begin is_lw  = 1'b1; end
          3'b100: begin is_lbu = 1'b1; end
          3'b001: begin is_lh  = 1'b1; end
          3'b101: begin is_lhu = 1'b1; end
          default: ;
        endcase
      end

      7'b0110011: 
      begin // R-type arithmetic
        case (funct3)
          3'b000: 
          begin
            if (funct7 == 7'b0000000) begin is_add = 1'b1; end // add
            if (funct7 == 7'b0100000) begin is_sub = 1'b1; end // sub
          end
          3'b011: if (funct7 == 7'b0000000) begin is_sltu = 1'b1; end // sltu
          3'b010: if (funct7 == 7'b0000000) begin is_slt = 1'b1; end // slt
          3'b100: if (funct7 == 7'b0000000) begin is_xor = 1'b1; end // xor
          3'b110: if (funct7 == 7'b0000000) begin is_or = 1'b1; end // or
          3'b111: if (funct7 == 7'b0000000) begin is_and = 1'b1; end // and
          3'b101: begin 
                    if (funct7 == 7'b0100000) is_sra = 1'b1; // sra
                    if (funct7 == 7'b0000000)  is_srl = 1'b1; // srl
                  end

          3'b001: if (funct7 == 7'b0000000) begin is_sll = 1'b1; end //sll
          default: ;
        endcase
      end

      7'b0010011: 
      begin // I-type arithmetic
        case (funct3)
          3'b000: begin is_addi = 1'b1; end // addi
          3'b001: begin if(funct7 == 7'b000_0000) is_slli = 1'b1; end // slli
          3'b010: begin is_slti = 1'b1; end // slti
          3'b011: begin is_sltiu = 1'b1; end // sltiu
          3'b100: begin is_xori = 1'b1; end // xori
          3'b110: begin is_ori  = 1'b1; end // ori
          3'b101: begin 
                    if (funct7 == 7'b0100000) is_srai = 1'b1;// srai
                    if (funct7 == 7'b0000000)  is_srli = 1'b1; //srli
                  end 
          3'b111: begin is_andi = 1'b1; end //andi
          default: ;
        endcase
      end

      7'b1100011:
      begin
        case(funct3)
          3'b000: is_beq = 1'b1;
          3'b001: is_bne = 1'b1;
          3'b101: is_bge = 1'b1;
          3'b111: is_bgeu= 1'b1;
          3'b100: is_blt = 1'b1;
          3'b110: is_bltu= 1'b1;
          default: ;
        endcase
      end

      7'b1110011://system 相关
      begin
        case (inst)
          32'h00100073: is_ebreak = 1'b1;
          32'h00000073: is_ecall = 1'b1;
          32'h30200073: is_mret  = 1'b1;
          default: ;
        endcase


        if (funct3 == 3'b010)
          is_csrrs = 1'b1;
        else if(funct3 == 3'b001)
          is_csrrw = 1'b1;

      end

      7'b0001111: // FENCE / FENCE.I — 单周期设计中无需内存屏障，视为 NOP
      begin
        if(funct3 == 3'b001)
          is_fence_i = 1'b1;
      end

      default: ;
    endcase

  

  end
 


  // ── 指令大类译码: 供后面 rs1_en/rs2_en/rd_en 复用 ──
  wire is_rtype  = (opcode == 7'b0110011);   // R-type: add/sub/xor/or/and/sll/srl/sra/slt/sltu
  wire is_itype  = (opcode == 7'b0010011);   // I-type: addi/xori/ori/andi/slli/srli/srai/slti/sltiu
  wire is_load   = (opcode == 7'b0000011);   // lb/lbu/lh/lhu/lw
  wire is_store  = (opcode == 7'b0100011);   // sb/sh/sw
  wire is_branch = (opcode == 7'b1100011);   // beq/bne/blt/bge/bltu/bgeu
  wire is_csr    = (opcode == 7'b1110011) && ((funct3 == 3'b001) || (funct3 == 3'b010));

  assign rs1 = inst[19:15];
  assign rs2 = inst[24:20];
  assign rd  = inst[11:7];

  // 寄存器读使能
  // rs1: addi/add/jalr/lw/lbu/sw/sb/xor/xori/sub 都需要
  // rs2: add/sw/sb/xor/sub 需要
  assign rs1_en = is_rtype | is_itype | is_load | is_store | is_branch | is_jalr | is_csr;
  assign rs2_en = is_rtype | is_store | is_branch;
  assign rd_en  = is_rtype | is_itype | is_load | is_lui | is_auipc | is_jal | is_jalr | is_csr;

  
  /*alu related*/
  // 用 case 结构解码 ALU 操作，按 opcode 分组，R-type/I-type 细化
  // 默认值
  always @(*) 
  begin
    //初始化
    alu_op = `ALU_ADD;
    alu_en = 1'b0;
    alu_src2_imm = 1'b0;

    case (opcode)
      7'b1101111:
      begin // jal：pc + imm
        alu_en = 1'b1;
        alu_src2_imm = 1'b1;
        alu_op = `ALU_ADD;
      end

      7'b1100111:
      begin // jalr：rs1 + imm
        if (funct3 == 3'b000) 
        begin
          alu_en = 1'b1;
          alu_src2_imm = 1'b1;
          alu_op = `ALU_ADD;
        end
      end

      7'b0110011: //算术相关
      begin // R-type
        alu_en = 1'b1;
        case (funct3)
          3'b000: alu_op = (funct7 == 7'b0100000) ? `ALU_SUB : `ALU_ADD; // add / sub
          3'b100: alu_op = `ALU_XOR; // xor
          3'b111: alu_op = `ALU_AND; // and
          3'b110: alu_op = `ALU_OR;  // or
          3'b001: alu_op = `ALU_SLL; // sll
          3'b101: alu_op = (funct7 == 7'b0100000) ? `ALU_SRA : `ALU_SRL; // srl / sra
          3'b010: alu_op = `ALU_SLT; // slt
          3'b011: alu_op = `ALU_SLTU; // sltu
          default: alu_op = `ALU_ADD;
        endcase
      end

      7'b0010111:
      begin // auipc
        alu_en = 1'b1;
        alu_src2_imm = 1'b1;
        alu_op = `ALU_ADD;
      end

      7'b0000011:
      begin // load address = rs1 + imm
        alu_en = 1'b1;
        alu_src2_imm = 1'b1;
        alu_op = `ALU_ADD; // lw / lbu / load相关都是一样的地址计算
      end
 
      7'b0100011:
      begin // store address = rs1 + imm
        alu_en = 1'b1;
        alu_src2_imm = 1'b1;
        alu_op = `ALU_ADD; // sw / sb  / sh 地址计算
      end


      7'b0010011: 
      begin // I-type ALU immediate
        alu_en = 1'b1;
        alu_src2_imm = 1'b1;//指令带i的置为1
        case (funct3)
          3'b000: alu_op = `ALU_ADD;  //addi
          // 3'b000: alu_op = `ALU_SUB; // addi (temporary bug injection)
          3'b100: alu_op = `ALU_XOR; // xori
          3'b111: alu_op = `ALU_AND; // andi
          3'b110: alu_op = `ALU_OR;  // ori
          3'b001: alu_op = `ALU_SLL; // slli (funct7 may be checked in EXU if needed)
          3'b101: alu_op = (funct7 == 7'b0100000) ? `ALU_SRA : `ALU_SRL; // srli/srai
          3'b010: alu_op = `ALU_SLT; // slti
          3'b011: alu_op = `ALU_SLTU; // sltiu
          default: alu_op = `ALU_ADD;
        endcase
      end

      7'b1100011:
      begin // branch address = pc + imm
        case(funct3)
          3'b000, 3'b001, 3'b101, 3'b111, 3'b100, 3'b110:
          begin // bne  bge bgeu blt bltu
            alu_en = 1'b1;
            alu_src2_imm = 1'b1;
            alu_op = `ALU_ADD;
          end
          default: ;
        endcase
      end

      default: 
      begin
        alu_op = `ALU_ADD;
        alu_en = 1'b0;
        alu_src2_imm = 1'b0;
      end
    endcase
  end

  assign alu_src1_pc = is_auipc | is_jal | is_bne | is_bge | is_bgeu | is_blt | is_bltu | is_beq; // auipc / jal / 分支b 由 pc 作为 ALU 第一个操作数

    // npc_sel:
  // 2'b00 -> pc + 4
  // 2'b01 -> jalr target (rs1 + imm)
  // 2'b10 -> jal target  (pc + imm)
  assign npc_sel = is_jalr ? `NPC_JALR :
                   (is_bne | is_beq | is_bge | is_bgeu | is_blt | is_bltu)  ? `NPC_BR   :
                   is_jal  ? `NPC_JAL  : is_ecall ? `NPC_ECALL : is_mret ? `NPC_MRET : `NPC_PC4;
  // 访存相关
  assign mem_re = is_lb | is_lbu | is_lw | is_lh | is_lhu;
  assign mem_we = is_sb | is_sw | is_sh;
  
  // 访存宽度: funct3[1:0] 本身就是宽度编码, 与 MEM_BYTE/HALF/WORD 完全一致
  assign mem_width = funct3[1:0];


  assign mem_signed = is_lh | is_lb;
  
  // wb_sel:
  // 写回来源选择：
  // addi/add -> ALU，jal/jalr -> pc+4，lw/lbu -> MEM，lui -> IMM
  // 写回来源: 分支按互斥优先级排列, ALU 类(R/I/auipc)落到 default
  assign wb_sel = (is_jal | is_jalr) ? `WB_PC4 :
                  (is_load)          ? `WB_MEM :
                  (is_lui)           ? `WB_IMM :
                  (is_csr)           ? `WB_CSR : `WB_ALU;


  
  
  assign branch_type = is_beq ? `BR_BEQ : is_bne ? `BR_BNE : is_bge ? `BR_BGE : 
                       is_bgeu ? `BR_BGEU : is_blt  ? `BR_BLT :
                       is_bltu ? `BR_BLTU : `BR_NONE;

  // RV32 shift-immediate 非法编码：inst[25] (= shamt[5]) 必须为 0 移位时的非法判断
  wire illegal_shift_imm = (opcode == 7'b0010011) &&
                           ((funct3 == 3'b001) || (funct3 == 3'b101)) &&
                           inst[25];

  // invalid: 合法指令 = 写回类(rd_en) | store | 分支 | ecall/ebreak/mret/fence
  assign invalid = illegal_shift_imm |
                   ~(rd_en | is_store | is_branch | is_ebreak | is_ecall | is_mret | is_fence_i);


  // csrrw 总是写 CSR；csrrs 仅在 rs1≠x0 时写（RISC-V 规范要求 rs1=x0 时只读不写）
  assign csr_wen = is_csrrw | (is_csrrs & (rs1 != 5'b0));
  assign csr_s_w = is_csrrs ? 1'b1 : 1'b0 ; //1代表要和rs1或

  assign  fence_i = is_fence_i;

  // 立即数类型: 复用 opcode 大类, 不再重复比较 opcode
  assign imm_type = (is_itype | is_load | is_jalr) ? IMM_I :
                    (is_lui   | is_auipc)          ? IMM_U :
                    (is_store)                     ? IMM_S :
                    (is_branch)                    ? IMM_B :
                    (is_jal)                       ? IMM_J : IMM_I;


  /*立即数生成逻辑 (集成从ImmGen)*/
  wire [31:0] imm_i = {{20{inst[31]}}, inst[31:20]};
  wire [31:0] imm_s = {{20{inst[31]}}, inst[31:25], inst[11:7]}; //没毛
  wire [31:0] imm_u = {inst[31:12], 12'b0};
  wire [31:0] imm_b = {{19{inst[31]}}, inst[31], inst[7], inst[30:25], inst[11:8], 1'b0};
  wire [31:0] imm_j = {{11{inst[31]}}, inst[31], inst[19:12], inst[20], inst[30:21], 1'b0};

  assign imm = (imm_type == IMM_I) ? imm_i :
               (imm_type == IMM_S) ? imm_s :
               (imm_type == IMM_U) ? imm_u :
               (imm_type == IMM_B) ? imm_b :
               (imm_type == IMM_J) ? imm_j :
               32'h0;

endmodule
