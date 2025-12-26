module pc(
    input logic [31:0] addr,
    input logic clk,
    input logic rst,
    input logic ext_wen,
    output logic [31:0] q
);
    logic [31:0] d_in;
    
    assign d_in = ext_wen ? addr : (q + 32'd4);
    
    register pc_reg(
        .clk(clk),
        .rst(rst),
        .wen(1'b1),
        .d(d_in),
        .q(q)
    );
endmodule