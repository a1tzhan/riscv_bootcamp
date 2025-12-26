#include "minirv_emu.h"

MinirvEmulator::MinirvEmulator() : registers_(16, 0), memory_(131072, 0) // 128K words
{
    pc_ = 0; // Start at 0 to match RTL reset
}

void MinirvEmulator::PopulateMemory()
{
    std::ifstream in("/mnt/c/Users/Professional/Desktop/mdv101/bootcamp/miniRV/instructions.hex");
    std::string line;
    if (!in)
    {
        std::cerr << "Error: cannot open 'instructions.hex' for reading.\n";
    }
    int tests = 0;
    int num_tests = 131071; // Load more instructions
    while (tests < num_tests && std::getline(in, line))
    {
        uint32_t instruction = std::stoul(line, nullptr, 16); // read hex
        memory_[tests] = instruction;
        tests++;
    }
}

void MinirvEmulator::Evaluate(uint32_t instruction)
{
    uint32_t opcode = (instruction & 0x7F);
    uint32_t rs1 = registers_[(instruction >> 15) & 0x1F];
    uint32_t rs2 = registers_[(instruction >> 20) & 0x1F];
    uint32_t rd = (instruction >> 7) & 0x1F;
    signed imm, addr;
    pc_ += 4; // Increment for next instruction
    std::cout << "Evaluating instruction: " << std::bitset<32>(instruction) << std::endl;
    switch (opcode)
    {
    case 0x13: // ADDI
        imm = (instruction >> 20) & 0xFFF;
        // Sign extend 12-bit immediate
        if (imm & 0x800)
            imm |= 0xFFFFF000;
        registers_[rd] = rs1 + imm;
        break;
    case 0x67: // JALR
        imm = (instruction >> 20) & 0xFFF;
        if (imm & 0x800)
            imm |= 0xFFFFF000;
        registers_[rd] = pc_;   // Save return address (current instr addr + 4)
        pc_ = (rs1 + imm) & ~1; // Jump to target
        break;
    case 0x33: // ADD
        registers_[rd] = rs1 + rs2;
        break;
    case 0x37: // LUI
        imm = (instruction >> 12) & 0xFFFFF;
        registers_[rd] = imm << 12;
        break;
    case 0x03: // Load
    {
        uint32_t funct3 = (instruction >> 12) & 0x7;
        imm = (instruction >> 20) & 0xFFF;
        // Sign extend 12-bit immediate
        if (imm & 0x800)
            imm |= 0xFFFFF000;
        addr = rs1 + imm;
        if (funct3 == 0x2) // LW (funct3 = 010)
        {
            registers_[rd] = memory_[addr / 4];
        }
        else if (funct3 == 0x4) // LBU (funct3 = 100)
        {
            // Select correct byte based on addr[1:0]
            uint32_t word = memory_[addr / 4];
            uint32_t byte_offset = addr & 0x3;
            registers_[rd] = (word >> (byte_offset * 8)) & 0xFF;
        }
        break;
    }
    case 0x23: // Store
    {
        uint32_t funct3 = (instruction >> 12) & 0x7;
        imm = ((instruction >> 25) << 5) | ((instruction >> 7) & 0x1F);
        if (imm & 0x800)
            imm |= 0xFFFFF000;
        addr = rs1 + imm;
        if (funct3 == 0x2) // SW (funct3 = 010)
        {
            memory_[addr / 4] = rs2;
        }
        else if (funct3 == 0x0) // SB (funct3 = 000)
        {
            // Write to correct byte, preserve other bytes
            uint32_t byte_offset = addr & 0x3;
            uint32_t mask = ~(0xFF << (byte_offset * 8));
            memory_[addr / 4] = (memory_[addr / 4] & mask) | ((rs2 & 0xFF) << (byte_offset * 8));
        }
        break;
    }
    default:
        break;
    }
    registers_[0] = 0; // x0 is always 0
}

uint32_t MinirvEmulator::GetRegisterValue(uint32_t reg_num)
{
    return registers_[reg_num];
}