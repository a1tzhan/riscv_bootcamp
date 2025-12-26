module pr_encoder(
    input wire in1,
    input wire in2,
    input wire in3,
    input wire in4,
    input wire in5,
    input wire in6,
    input wire in7,
    input wire in8,
    input wire in9,
    output wire [3:0] out
);
    reg [3:0] outreg;
    assign out = outreg;
    always @(*) begin
        case (1'b1)
            in9: outreg = 4'b1001;
            in8: outreg = 4'b1000;
            in7: outreg = 4'b0111;
            in6: outreg = 4'b0110;
            in5: outreg = 4'b0101;
            in4: outreg = 4'b0100;
            in3: outreg = 4'b0011;
            in2: outreg = 4'b0010;
            in1: outreg = 4'b0001;
            default: outreg = 4'b0000; // No input active
        endcase
    end

endmodule