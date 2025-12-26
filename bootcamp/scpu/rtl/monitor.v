import "DPI-C" function void test_instruction(input bit [7:0] instruction, input bit [7:0] reg_0, input bit [7:0] reg_1, input bit [7:0] reg_2,
                                        input bit [7:0] reg_3);
module monitor(
    input wire clk,
    input wire [7:0] instruction, 
    input wire [7:0] reg_0,
    input wire [7:0] reg_1,
    input wire [7:0] reg_2,
    input wire [7:0] reg_3
);

    reg dpi = 1;

    always @(posedge clk) begin
        dpi <= 1;
    end

    always @(posedge dpi) begin
        test_instruction(
            instruction,
            reg_0, reg_1, reg_2, reg_3
        );
    end
endmodule