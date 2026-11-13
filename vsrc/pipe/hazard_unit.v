// RAW冒险检测
module hazard_unit(
    input   wire            id_valid, // ID段 是否有指令
    input   wire    [4:0]   id_rs1,     
    input   wire    [4:0]   id_rs2,
    input   wire            id_rs1_en,  // 是否要读
    input   wire            id_rs2_en,  // 是否要读

    input   wire            ex_valid,
    input   wire    [4:0]   ex_rd,
    input   wire            ex_rd_en,

    input   wire            mem_valid,
    input   wire    [4:0]   mem_rd,
    input   wire            mem_rd_en,

    input   wire            wb_valid,
    input   wire    [4:0]   wb_rd,
    input   wire            wb_rd_en,

    output  wire            stall  // 等待信号

);

// 我要读 rs1, 而且其他地方要写 rs1
    wire hit_rs1 = id_valid && id_rs1_en && (id_rs1 != 5'b0) 
        && 
        ((ex_valid  && ex_rd_en  && (ex_rd  == id_rs1)) ||
        (mem_valid && mem_rd_en && (mem_rd == id_rs1)) ||
        (wb_valid  && wb_rd_en  && (wb_rd  == id_rs1)));

    wire hit_rs2 = id_valid && id_rs2_en && (id_rs2 != 5'b0) 
        && 
        ((ex_valid  && ex_rd_en  && (ex_rd  == id_rs2)) ||
        (mem_valid && mem_rd_en && (mem_rd == id_rs2)) ||
        (wb_valid  && wb_rd_en  && (wb_rd  == id_rs2)));

    assign stall = hit_rs1 || hit_rs2;


endmodule
