#include "scpu_emu.h"

ScpuEmulator::ScpuEmulator() : registers_(4, 0)
{
}

uint16_t ScpuEmulator::Evaluate(uint16_t instruction)
{
    uint16_t opcode = ((instruction >> 6) & 0x3);
    uint16_t a = registers_[(instruction >> 2) & 0x3];
    uint16_t b = registers_[instruction & 0x3];
    uint16_t imm = (instruction) & 0xF;
    uint16_t addr = (instruction >> 2) & 0xF;
    uint16_t out = 0;
    switch (opcode)
    {
    case 0x0:
        out = a + b;
        registers_[(instruction >> 4) & 0x3] = out;
        break;
    case 0x2:
        out = imm;
        registers_[(instruction >> 4) & 0x3] = out;
        break;
    case 0x3:
        if (registers_[instruction & 0x3] != registers_[0])
            out = addr;
        break;
    default:
        out = 0;
        break;
    }
    return out;
}

uint16_t ScpuEmulator::GetRegisterValue(uint16_t reg_num)
{
    return registers_[reg_num];
}