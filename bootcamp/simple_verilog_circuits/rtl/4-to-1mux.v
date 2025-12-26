module 4-to-1mux(
    input wire i1[7:0],
    input wire i2[7:0],
    input wire i3[7:0],
    input wire i4[7:0],
    input wire [1:0] sel,
    output reg [7:0] out
);

    always@(*) begin
        case(sel)
            2'b00: out = i1;
            2'b01: out = i2;
            2'b10: out = i3;
            2'b11: out = i4;
            default: out = 8'b00000000;
        endcase
    end
endmodule
