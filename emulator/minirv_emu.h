#include <iostream>
#include <cstdlib>
#include <cassert>
#include <random>
#include <bitset>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

class MinirvEmulator
{
public:
    MinirvEmulator();

    void Evaluate(uint32_t instruction);
    uint32_t GetRegisterValue(uint32_t reg_num);
    void PopulateMemory();

private:
    std::vector<uint32_t> registers_;
    std::vector<uint32_t> memory_;
    uint32_t pc_;
};