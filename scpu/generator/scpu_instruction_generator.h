#include <iostream>
#include <cstdlib>
#include <random>
#include <bitset>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>

class ScpuInstructionGenerator
{
public:
    ScpuInstructionGenerator() = default;
    uint16_t Generate();
};