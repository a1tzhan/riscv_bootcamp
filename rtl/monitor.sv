import "DPI-C" function void test_instruction(input bit [31:0] instruction, input bit [31:0] reg_0, input bit [31:0] reg_1, input bit [31:0] reg_2,
                                        input bit [31:0] reg_3, input bit [31:0] reg_4, input bit [31:0] reg_5, input bit [31:0] reg_6,
                                        input bit [31:0] reg_7, input bit [31:0] reg_8, input bit [31:0] reg_9, input bit [31:0] reg_10,
                                        input bit [31:0] reg_11, input bit [31:0] reg_12, input bit [31:0] reg_13, input bit [31:0] reg_14,
                                        input bit [31:0] reg_15);
module monitor(
    input logic clk,
    input logic [31:0] instruction, 
    input logic [31:0] reg_0,
    input logic [31:0] reg_1,
    input logic [31:0] reg_2,
    input logic [31:0] reg_3,
    input logic [31:0] reg_4,
    input logic [31:0] reg_5,
    input logic [31:0] reg_6,
    input logic [31:0] reg_7,
    input logic [31:0] reg_8,
    input logic [31:0] reg_9,
    input logic [31:0] reg_10,
    input logic [31:0] reg_11,
    input logic [31:0] reg_12,
    input logic [31:0] reg_13,
    input logic [31:0] reg_14,
    input logic [31:0] reg_15
);

    logic [31:0] prev_instruction;
    always_ff @(posedge clk) begin
            // Call DPI with previous instruction to match hardware timing
            test_instruction(
                prev_instruction,
                reg_0, reg_1, reg_2, reg_3, reg_4, reg_5, reg_6, reg_7,
                reg_8, reg_9, reg_10, reg_11, reg_12, reg_13, reg_14, reg_15
            );
            prev_instruction <= instruction;
        end
endmodule