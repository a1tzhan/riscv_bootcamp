module register_file(
    input logic clk,
    input logic rst,
    input logic [31:0] data,
    input logic [4:0] rs1,
    input logic [4:0] rs2,
    input logic [4:0] rd,
    output logic [31:0] q1,
    output logic [31:0] q2,
    output logic [31:0] reg_0,
    output logic [31:0] reg_1,
    output logic [31:0] reg_2,
    output logic [31:0] reg_3,
    output logic [31:0] reg_4,
    output logic [31:0] reg_5,
    output logic [31:0] reg_6,
    output logic [31:0] reg_7,
    output logic [31:0] reg_8,
    output logic [31:0] reg_9,
    output logic [31:0] reg_10,
    output logic [31:0] reg_11,
    output logic [31:0] reg_12,
    output logic [31:0] reg_13,
    output logic [31:0] reg_14,
    output logic [31:0] reg_15
);    
    register reg0(
        .clk(clk),
        .rst(rst),
        .wen(1'b0),
        .d(32'h00000000),
        .q(reg_0)
    );
    register reg1(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b00001),
        .d(data),
        .q(reg_1)
    );
    register reg2(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b00010),
        .d(data),
        .q(reg_2)
    );
    register reg3(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b00011),
        .d(data),
        .q(reg_3)
    );

    register reg4(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b00100),
        .d(data),
        .q(reg_4)
    );

    register reg5(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b00101),
        .d(data),
        .q(reg_5)
    );

    register reg6(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b00110),
        .d(data),
        .q(reg_6)
    );

    register reg7(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b00111),
        .d(data),
        .q(reg_7)
    );

    register reg8(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b01000),
        .d(data),
        .q(reg_8)
    );

    register reg9(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b01001),
        .d(data),
        .q(reg_9)
    );

    register reg10(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b01010),
        .d(data),
        .q(reg_10)
    );

    register reg11(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b01011),
        .d(data),
        .q(reg_11)
    );

    register reg12(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b01100),
        .d(data),
        .q(reg_12)
    );

    register reg13(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b01101),
        .d(data),
        .q(reg_13)
    );

    register reg14(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b01110),
        .d(data),
        .q(reg_14)
    );

    register reg15(
        .clk(clk),
        .rst(rst),
        .wen(rd == 5'b01111),
        .d(data),
        .q(reg_15)
    );

    always_comb begin
        case (rs1)
            5'b00000: q1 = reg_0;
            5'b00001: q1 = reg_1;
            5'b00010: q1 = reg_2;
            5'b00011: q1 = reg_3;
            5'b00100: q1 = reg_4;
            5'b00101: q1 = reg_5;
            5'b00110: q1 = reg_6;
            5'b00111: q1 = reg_7;
            5'b01000: q1 = reg_8;
            5'b01001: q1 = reg_9;
            5'b01010: q1 = reg_10;
            5'b01011: q1 = reg_11;
            5'b01100: q1 = reg_12;
            5'b01101: q1 = reg_13;
            5'b01110: q1 = reg_14;
            5'b01111: q1 = reg_15;
            default: q1 = 32'b0;
        endcase

        case (rs2)
            5'b00000: q2 = reg_0;
            5'b00001: q2 = reg_1;
            5'b00010: q2 = reg_2;
            5'b00011: q2 = reg_3;
            5'b00100: q2 = reg_4;
            5'b00101: q2 = reg_5;
            5'b00110: q2 = reg_6;
            5'b00111: q2 = reg_7;
            5'b01000: q2 = reg_8;
            5'b01001: q2 = reg_9;
            5'b01010: q2 = reg_10;
            5'b01011: q2 = reg_11;
            5'b01100: q2 = reg_12;
            5'b01101: q2 = reg_13;
            5'b01110: q2 = reg_14;
            5'b01111: q2 = reg_15;
            default: q2 = 32'b0;
        endcase
    end

endmodule