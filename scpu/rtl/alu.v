module alu(
    input wire [7:0] a,
    input wire [7:0] b,
    input wire [3:0] imm,
    input wire [1:0] opcode,
    output wire [7:0] alu_out,
    output wire wen,
    output wire wen_pc
);
    assign alu_out = opcode[1] ? {4'b0, imm} : (a + b);
    assign wen = !(opcode == 2'b11);
    assign wen_pc = !(a == b) && (opcode == 2'b11);
endmodule