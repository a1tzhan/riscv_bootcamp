module decoder(
    input logic [31:0] instruction,
    output logic [31:0] imm,
    output logic [4:0] rs2,
    output logic [4:0] rs1,
    output logic [4:0] rd,
    output logic byte_flag,
    output logic [6:0] opcode
);      

        assign opcode = instruction[6:0];
        always_comb begin
        rs1 = 5'b00000;
        rs2 = 5'b00000;
        rd = 5'b00000;
        imm = {32{1'b0}};
        byte_flag = 1'b0;
        case (opcode)
            7'b0010011, 7'b1100111: begin 
                rs1 = instruction[19:15];
                rd = instruction[11:7];
                imm = {{20{instruction[31]}}, instruction[31:20]};
            end
            7'b0110011: begin
                rs1 = instruction[19:15];
                rs2 = instruction[24:20];
                rd = instruction[11:7];
            end
            7'b0110111: begin
                rd = instruction[11:7];
                imm = {instruction[31:12], {12'b0}};
            end
            7'b0000011: begin //LOAD
                byte_flag = instruction[14:12] == 3'b100 ? 1'b1 : 1'b0; // LB
                rs1 = instruction[19:15];
                rd = instruction[11:7];
                imm = {{20{instruction[31]}}, instruction[31:20]};
            end
            7'b0100011:begin //STORE
                byte_flag = instruction[14:12] == 3'b000 ? 1'b1 : 1'b0; // SB
                rs2 = instruction[24:20];
                rs1 = instruction[19:15];
                imm = {{20{instruction[31]}}, instruction[31:25], instruction[11:7]};
            end
            default: begin
                rs1 = 5'b00000;
                rs2 = 5'b00000;
                rd = 5'b00000;
                imm = {32{1'b0}};
                byte_flag = 1'b0;
            end
        endcase
        end
endmodule