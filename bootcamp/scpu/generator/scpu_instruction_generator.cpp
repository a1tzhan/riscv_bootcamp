#include "scpu_instruction_generator.h"

uint16_t ScpuInstructionGenerator::Generate()
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
#ifdef MAIN
int main(int argc, char *argv[])
{
    ScpuInstructionGenerator generator;

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <N>\n"
                  << "  <N>  number of instructions to generate\n";
        return 1;
    }
    int N;
    try
    {
        N = std::stoi(argv[1]);
        if (N <= 0)
            throw std::invalid_argument("non-positive");
    }
    catch (...)
    {
        std::cerr << "Error: <N> must be a positive integer.\n";
        return 1;
    }

    const std::string out_filename = "instructions.hex";
    std::ofstream out(out_filename);
    if (!out)
    {
        std::cerr << "Error: cannot open output file '" << out_filename << "' for writing.\n";
        return 2;
    }

    for (int i = 0; i < N; i++)
    {
        uint16_t instruction = generator.Generate();
        out << std::hex
            << std::setw(4)
            << instruction
            << '\n';
    }
    out.close();
    std::cout << "Generated " << N << " instructions in '"
              << out_filename << "'.\n";
    return 0;
}
#endif