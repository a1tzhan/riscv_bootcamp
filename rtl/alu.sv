module alu(
    input logic [31:0] a,
    input logic [31:0] b,
    input logic [31:0] pc,
    input logic [31:0] imm,
    input logic [6:0] opcode,
    output logic [31:0] addr,
    output logic [31:0] alu_out,
    output logic wen_pc,
    output logic store_flag,
    output logic load_flag
);
    always_comb begin
        alu_out = 32'b0;
        addr = 32'b0;
        wen_pc = 1'b0;
        store_flag = 1'b0;
        load_flag = 1'b0;
        case (opcode)
            7'b0010011: begin // ADDI
                alu_out = a + imm;
                wen_pc = 1'b0;
            end
            7'b1100111: begin // JALR
                alu_out = pc + 4;
                addr = (a + imm) & ~32'b1;
                wen_pc = 1'b1;
            end
            7'b0110011: begin // ADD
                alu_out = a + b;
                wen_pc = 1'b0;
            end
            7'b0110111: begin // LUI
                alu_out = imm;
                wen_pc = 1'b0;
            end
            7'b0000011: begin // LOAD
                addr = a + imm;
                wen_pc = 1'b0;
                load_flag = 1'b1;
            end
            7'b0100011: begin // STORE
                addr = a + imm;
                wen_pc = 1'b0;
                store_flag = 1'b1;
            end
            default: begin
                alu_out = 32'b0;
                addr = 32'b0;
                wen_pc = 1'b0;
                store_flag = 1'b0;
                load_flag = 1'b0;
            end
        endcase
    end 
endmodule