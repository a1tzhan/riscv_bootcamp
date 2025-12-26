module decoder(
    input wire [7:0] instruction,
    output wire [3:0] addr,
    output wire [3:0] imm,
    output wire [1:0] rs2,
    output wire [1:0] rs1,
    output wire [1:0] rd,
    output wire [1:0] opcode
);
        assign opcode = instruction[7:6];
        assign addr = instruction[5:2];
        assign imm = instruction[3:0];
        assign rs2 = instruction[1:0];
        assign rs1 = opcode == 2'b11 ? 2'b00 : instruction[3:2];
        assign rd = instruction[5:4];
endmodule