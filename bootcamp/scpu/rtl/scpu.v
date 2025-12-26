module scpu(
    input wire clk,
    input wire rst,
    output wire [7:0] r0,
    output wire [7:0] r1,
    output wire [7:0] r2,
    output wire [7:0] r3
);

    wire [3:0] decoder_addr_to_pc;
    wire wen_alu_pc;
    wire [3:0] pc_to_instrROM;
    wire [7:0] instruction_to_decoder;
    wire [3:0] imm_to_alu;
    wire [1:0] opcode_to_alu;
    wire [1:0] rs1_to_regfile;
    wire [1:0] rs2_to_regfile;
    wire [1:0] rd_to_regfile;
    wire [7:0] q1_to_alu;
    wire [7:0] q2_to_alu;
    wire [7:0] alu_out_to_regfile;
    wire alu_out_wen;


    pc scpu_pc(
        .addr(decoder_addr_to_pc),
        .clk(clk),
        .rst(rst),
        .ext_wen(wen_alu_pc),
        .q(pc_to_instrROM)
    );

    instrROM scpu_instrROM(
        .pc(pc_to_instrROM ), 
        .instruction(instruction_to_decoder)
    );

    decoder scpu_decoder(
        .instruction(instruction_to_decoder),
        .addr(decoder_addr_to_pc),
        .imm(imm_to_alu),
        .rs2(rs2_to_regfile),
        .rs1(rs1_to_regfile),
        .rd(rd_to_regfile),
        .opcode(opcode_to_alu)
    );

    monitor scpu_monitor(
        .clk(clk),
        .instruction(instruction_to_decoder),
        .reg_0(r0),
        .reg_1(r1),
        .reg_2(r2),
        .reg_3(r3)
    );

    alu scpu_alu(
        .a(q1_to_alu),
        .b(q2_to_alu),
        .imm(imm_to_alu),
        .opcode(opcode_to_alu),
        .alu_out(alu_out_to_regfile), 
        .wen(alu_out_wen), 
        .wen_pc(wen_alu_pc) 
    );

    register_file scpu_register_file(
        .clk(clk),
        .rst(rst),
        .data(alu_out_to_regfile), 
        .wen(alu_out_wen), 
        .rs1(rs1_to_regfile),
        .rs2(rs2_to_regfile),
        .rd(rd_to_regfile),
        .q1(q1_to_alu),
        .q2(q2_to_alu),
        .r0(r0),
        .r1(r1),
        .r2(r2),
        .r3(r3)
    );

endmodule
