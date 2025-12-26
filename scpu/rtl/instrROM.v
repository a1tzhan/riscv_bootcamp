module instrROM(
    input wire [3:0] pc,
    output wire [7:0] instruction
);
    reg [7:0] mem [0:15];
    reg [7:0] instruction_out;
    assign instruction = instruction_out;
    
    initial begin
        $readmemh("/mnt/c/Users/Professional/Desktop/mdv101/bootcamp/scpu/instructions.hex", mem);
    end

    always @(*) begin
        instruction_out = mem[pc];
    end

    
endmodule