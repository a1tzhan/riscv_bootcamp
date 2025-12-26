module register4(
    input wire clk,
    input wire rst,
    input wire wen,
    input wire [3:0] d,
    output wire [3:0] q
);
    reg [3:0] q_reg;
    assign q = q_reg;
    always @(posedge clk or posedge rst) begin
        if (rst) q_reg <= 4'b0;
        else if (wen && !rst) q_reg <= d;
    end

endmodule
