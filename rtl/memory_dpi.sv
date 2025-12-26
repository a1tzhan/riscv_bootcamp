// DPI-C imports
import "DPI-C" function void mem_init(input string hex_file);
import "DPI-C" function int mem_read(input int raddr);
import "DPI-C" function void mem_write(input int waddr, input int wdata, input byte wmask);

module memory_dpi(
    input logic clk,
    input logic [31:0] pc,           // Instruction fetch address
    input logic [31:0] addr,         // Data access address
    input logic [31:0] data_store,   // Data to store
    input logic store_flag,          // Store enable
    input logic load_flag,           // Load enable
    input logic byte_flag,           // Byte operation flag
    output logic [31:0] instruction, // Fetched instruction
    output logic [31:0] data         // Loaded data
);

    // Instruction fetch (combinational read)
    assign instruction = mem_read(pc);
    
    // Data load (combinational read)
    always_comb begin
        if (load_flag) begin
            logic [31:0] word_data;
            word_data = mem_read(addr);
            
            if (byte_flag) begin
                // LBU: Extract correct byte based on addr[1:0]
                case (addr[1:0])
                    2'b00: data = {24'b0, word_data[7:0]};
                    2'b01: data = {24'b0, word_data[15:8]};
                    2'b10: data = {24'b0, word_data[23:16]};
                    2'b11: data = {24'b0, word_data[31:24]};
                endcase
            end else begin
                // LW: Full word
                data = word_data;
            end
        end else begin
            data = 32'b0;
        end
    end
    
    // Data store (sequential write)
    always_ff @(posedge clk) begin
        if (store_flag) begin
            logic [7:0] wmask;
            logic [31:0] wdata;
            
            if (byte_flag) begin
                // SB: Write mask for single byte
                case (addr[1:0])
                    2'b00: begin wmask = 8'h01; wdata = {24'b0, data_store[7:0]}; end
                    2'b01: begin wmask = 8'h02; wdata = {16'b0, data_store[7:0], 8'b0}; end
                    2'b10: begin wmask = 8'h04; wdata = {8'b0, data_store[7:0], 16'b0}; end
                    2'b11: begin wmask = 8'h08; wdata = {data_store[7:0], 24'b0}; end
                endcase
            end else begin
                // SW: Write full word
                wmask = 8'h0F;
                wdata = data_store;
            end
            
            mem_write(addr, wdata, wmask);
        end
    end
    
    // Initialize memory on startup
    initial begin
        mem_init("/mnt/c/Users/Professional/Desktop/mdv101/riscv_bootcamp/miniRV/instructions.hex");
    end

endmodule