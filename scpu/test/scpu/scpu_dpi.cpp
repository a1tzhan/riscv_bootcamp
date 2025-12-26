#include "Vscpu.h"
#include "verilated.h"
#include "../../generator/scpu_instruction_generator.h"

#include <iostream>
#include <bitset>
#include <fstream>
#include <cstdlib>
#include <ctime>

void tick(Vscpu *tb)
{
    tb->clk = 0;
    tb->eval();
    tb->clk = 1;
    tb->eval();
}

void reset(Vscpu *tb)
{
    tb->rst = 1;
    tick(tb);
    tick(tb);
    tb->rst = 0;
}

int main(int argc, char **argv)
{
    ScpuInstructionGenerator generator;
    Verilated::commandArgs(argc, argv);
    Vscpu *tb = new Vscpu;

    std::srand(std::time(nullptr));
    int n = rand() % 16;
    std::ifstream in("/mnt/c/Users/Professional/Desktop/mdv101/bootcamp/scpu/instructions.hex");
    std::string line;
    std::string generate = "./generate_inst " + std::to_string(n);
    int result = system(generate.c_str());
    int tests = 0;
    if (result != 0)
    {
        std::cerr << "Failed to run instruction generator\n";
        return 1;
    }

    if (!in)
    {
        std::cerr << "Error: cannot open 'instructions.hex' for reading.\n";
        return 1;
    }
    reset(tb);

    while (std::getline(in, line))
    {
        uint16_t instruction = std::stoul(line, nullptr, 16); // read hex
        std::bitset<8> x(instruction);
        std::cout << "Instruction is: " << x << std::dec << std::endl;
        for (int i = 0; i < 2; i++)
        {
            tick(tb);
        }
        tick(tb);
        tests++;
    }

    std::cout << "\nTop_module tests complete. Tests ran: " << tests << std::endl;
    in.close();
    tb->final();
    delete tb;
    return 0;
}