module register_file(
    input wire clk,
    input wire rst,
    input wire [7:0] data,
    input wire wen,
    input wire [1:0] rs1,
    input wire [1:0] rs2,
    input wire [1:0] rd,
    output wire [7:0] q1,
    output wire [7:0] q2,
    output wire [7:0] r0,
    output wire [7:0] r1,
    output wire [7:0] r2,
    output wire [7:0] r3

);
    reg [7:0] q1_reg;
    reg [7:0] q2_reg;

    assign q1 = q1_reg;
    assign q2 = q2_reg;

    wire [7:0] reg0_to_mux;
    wire [7:0] reg1_to_mux;
    wire [7:0] reg2_to_mux;
    wire [7:0] reg3_to_mux;

    assign r0 = reg0_to_mux;
    assign r1 = reg1_to_mux;
    assign r2 = reg2_to_mux;
    assign r3 = reg3_to_mux;
    
    register reg0(
        .clk(clk),
        .rst(rst),
        .wen(wen && (rd == 2'b00)),
        .d(data),
        .q(reg0_to_mux)
    );
    register reg1(
        .clk(clk),
        .rst(rst),
        .wen(wen && (rd == 2'b01)),
        .d(data),
        .q(reg1_to_mux)
    );
    register reg2(
        .clk(clk),
        .rst(rst),
        .wen(wen && (rd == 2'b10)),
        .d(data),
        .q(reg2_to_mux)
    );
    register reg3(
        .clk(clk),
        .rst(rst),
        .wen(wen && (rd == 2'b11)),
        .d(data),
        .q(reg3_to_mux)
    );

    always @(*) begin
        case (rs1)
            2'b00: q1_reg = reg0_to_mux;
            2'b01: q1_reg = reg1_to_mux;
            2'b10: q1_reg = reg2_to_mux;
            2'b11: q1_reg = reg3_to_mux;
        endcase

        case (rs2)
            2'b00: q2_reg = reg0_to_mux;
            2'b01: q2_reg = reg1_to_mux;
            2'b10: q2_reg = reg2_to_mux;
            2'b11: q2_reg = reg3_to_mux;
        endcase
    end

endmodule