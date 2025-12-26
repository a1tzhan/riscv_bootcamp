module minirv(
    input logic clk,
    input logic rst
);

    logic [31:0] alu_addr_out;
    logic wen_alu_pc;
    logic [31:0] pc_to_instrROM;
    logic [31:0] instruction_to_decoder;
    logic [31:0] imm_to_alu;
    logic [6:0] opcode_to_alu;
    logic [4:0] rs1_to_regfile;
    logic [4:0] rs2_to_regfile;
    logic [4:0] rd_to_regfile;
    logic [31:0] q1_to_alu;
    logic [31:0] q2_to_alu;
    logic [31:0] alu_out_to_regfile;
    logic alu_out_store;
    logic alu_out_load;
    logic [31:0] r0;
    logic [31:0] r1;
    logic [31:0] r2;
    logic [31:0] r3;
    logic [31:0] r4;
    logic [31:0] r5;
    logic [31:0] r6;
    logic [31:0] r7;
    logic [31:0] r8;
    logic [31:0] r9;
    logic [31:0] r10;
    logic [31:0] r11;
    logic [31:0] r12;
    logic [31:0] r13;
    logic [31:0] r14;
    logic [31:0] r15;
    logic [31:0] rom_to_regfile;
    logic byte_flag;


    pc minirv_pc(
        .addr(alu_addr_out),
        .clk(clk),
        .rst(rst),
        .ext_wen(wen_alu_pc),
        .q(pc_to_instrROM)
    );

    instrROM minirv_instrROM(
        .clk(clk),
        .pc(pc_to_instrROM ), 
        .data_store(q2_to_alu),
        .addr(alu_addr_out),
        .byte_flag(byte_flag),
        .store_flag(alu_out_store),
        .load_flag(alu_out_load),
        .instruction(instruction_to_decoder),
        .data(rom_to_regfile)
    );

    decoder minirv_decoder(
        .instruction(instruction_to_decoder),
        .imm(imm_to_alu),
        .rs2(rs2_to_regfile),
        .rs1(rs1_to_regfile),
        .rd(rd_to_regfile),
        .byte_flag(byte_flag),
        .opcode(opcode_to_alu)
    );

    monitor minirv_monitor(
        .clk(clk),
        .instruction(instruction_to_decoder),
        .reg_0(r0),
        .reg_1(r1),
        .reg_2(r2),
        .reg_3(r3),
        .reg_4(r4),
        .reg_5(r5),
        .reg_6(r6),
        .reg_7(r7),
        .reg_8(r8),
        .reg_9(r9),
        .reg_10(r10),
        .reg_11(r11),
        .reg_12(r12),
        .reg_13(r13),
        .reg_14(r14),
        .reg_15(r15)
    );

    alu minirv_alu(
        .a(q1_to_alu),
        .b(q2_to_alu),
        .pc(pc_to_instrROM),
        .imm(imm_to_alu),
        .opcode(opcode_to_alu),
        .alu_out(alu_out_to_regfile), 
        .addr(alu_addr_out),
        .wen_pc(wen_alu_pc),
        .store_flag(alu_out_store),
        .load_flag(alu_out_load)
    );

    register_file minirv_register_file(
        .clk(clk),
        .rst(rst),
        .data(alu_out_load ? rom_to_regfile : alu_out_to_regfile), 
        .rs1(rs1_to_regfile),
        .rs2(rs2_to_regfile),
        .rd(rd_to_regfile),
        .q1(q1_to_alu),
        .q2(q2_to_alu),
        .reg_0(r0),
        .reg_1(r1),
        .reg_2(r2),
        .reg_3(r3),
        .reg_4(r4),
        .reg_5(r5),
        .reg_6(r6),
        .reg_7(r7),
        .reg_8(r8),
        .reg_9(r9),
        .reg_10(r10),
        .reg_11(r11),
        .reg_12(r12),
        .reg_13(r13),
        .reg_14(r14),
        .reg_15(r15)
    );

endmodule
