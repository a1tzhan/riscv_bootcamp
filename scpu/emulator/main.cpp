#include "scpu_emu.h"

uint16_t gen_inst()
{
    // Generate random values for the specified fields
    uint16_t opcode = rand() % 2; // 2 bits (0-3)
    uint16_t rd = rand() % 4;     // 2 bits (0-3)
    uint16_t rs1 = rand() % 4;    // 2 bits (0-3)
    uint16_t rs2 = rand() % 4;    // 2 bits (0-3)

    // Construct the instruction following the format
    if (opcode == 0x1)
    {
        opcode = 0x2; // Load Immediate
    }
    uint16_t instruction = (opcode << 6) |
                           (rd << 4) |
                           (rs1 << 2) | rs2;
    return instruction;
}

int main()
{
    ScpuEmulator emulator;

    std::mt19937 gen(42); // Seed for reproducibility
    std::uniform_int_distribution<uint32_t> dist(0, 0xFFFF);
    std::bernoulli_distribution bdist(0.5);
    srand(time(0));

    int errors = 0;
    const int NUM_TESTS = 1000;
    for (int i = 0; i < NUM_TESTS; i++)
    {
        uint16_t instruction = gen_inst();
        emulator.Evaluate(instruction);
        uint16_t regValue = emulator.GetRegisterValue(0);
    }

    return 0;
}