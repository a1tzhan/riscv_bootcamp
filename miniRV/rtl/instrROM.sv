module instrROM(
    input logic clk,
     /* verilator lint_off UNUSED */
    input logic [31:0] pc,  // Lower 2 bits unused (word-aligned addressing)
    /* verilator lint_on UNUSED */
    input logic [31:0] addr,
    input logic [31:0] data_store,
    input logic store_flag,
    input logic load_flag,
    input logic byte_flag,
    output logic [31:0] instruction,
    output logic [31:0] data
);
   
   
    
    
    reg [31:0] mem [0:131071];  // 128K words = 512KB memory
    
    initial begin
        $readmemh("/mnt/c/Users/Professional/Desktop/mdv101/bootcamp/miniRV/instructions.hex", mem);
    end

    // Instruction fetch (word-addressed: divide PC by 4)
    assign instruction = mem[pc[18:2]];  // 17-bit word address (512KB range)
    
    // Data read
    always_comb begin
        if (load_flag) begin
            if (byte_flag) begin
                // Select correct byte based on addr[1:0]
                case (addr[1:0])
                    2'b00: data = {24'b0, mem[addr[18:2]][7:0]};
                    2'b01: data = {24'b0, mem[addr[18:2]][15:8]};
                    2'b10: data = {24'b0, mem[addr[18:2]][23:16]};
                    2'b11: data = {24'b0, mem[addr[18:2]][31:24]};
                endcase
            end else begin
                data = mem[addr[18:2]];
            end
        end else begin
            data = 32'b0;
        end
    end
    
    // Data write (sequential)
    always_ff @(posedge clk) begin
        if (store_flag) begin
            if(byte_flag) begin
                // Write to correct byte based on addr[1:0]
                case (addr[1:0])
                    2'b00: mem[addr[18:2]][7:0]   <= data_store[7:0];
                    2'b01: mem[addr[18:2]][15:8]  <= data_store[7:0];
                    2'b10: mem[addr[18:2]][23:16] <= data_store[7:0];
                    2'b11: mem[addr[18:2]][31:24] <= data_store[7:0];
                endcase
            end else begin
                mem[addr[18:2]] <= data_store;
            end
        end
    end

endmodule