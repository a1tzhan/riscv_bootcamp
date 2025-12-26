module register(
    input logic clk,
    input logic rst,
    input logic wen,
    input logic [31:0] d, 
    output logic [31:0] q
);
    always_ff @(posedge clk or posedge rst) begin
        if (rst) q <= 32'b0;
        else if(wen && !rst) q <= d;
    end
endmodule