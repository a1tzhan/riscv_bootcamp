module pc(
    input wire [3:0] addr,
    input wire clk,
    input wire rst,
    input wire ext_wen,
    output wire [3:0] q
);
    reg [3:0] q_reg;
    assign q = q_reg;
    wire [3:0] d_in;
    assign d_in = ext_wen ? addr : (q_reg + 4'b1);
    register4 pc_reg(
        .clk(clk),
        .rst(rst),
        .wen(1),
        .d(d_in),
        .q(q_reg)
    );
endmodule