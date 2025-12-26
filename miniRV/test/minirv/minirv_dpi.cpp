#include "Vminirv.h"
#include "verilated.h"

#include <iostream>
#include <bitset>
#include <fstream>
#include <cstdlib>
#include <ctime>

void tick(Vminirv *tb)
{
    tb->clk = 0;
    tb->eval();
    tb->clk = 1;
    tb->eval();
}

void reset(Vminirv *tb)
{
    tb->rst = 1;
    tick(tb);
    tick(tb);
    tb->rst = 0;
}

int main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv);
    Vminirv *tb = new Vminirv;

    std::ifstream in("/mnt/c/Users/Professional/Desktop/mdv101/bootcamp/miniRV/instructions.hex");
    std::string line;
    int tests = 0;
    int num_tests = 6000;
    if (!in)
    {
        std::cerr << "Error: cannot open 'instructions.hex' for reading.\n";
        return 1;
    }

    reset(tb);
    while (tests < num_tests)
    {
        tick(tb);
        tests++;
    }

    std::cout << "\nTop_module tests complete. Tests ran: " << tests << std::endl;
    in.close();
    tb->final();
    delete tb;
    return 0;
}