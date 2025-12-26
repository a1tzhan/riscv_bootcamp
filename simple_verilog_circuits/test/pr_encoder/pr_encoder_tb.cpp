#include "Vpr_encoder.h"
#include "verilated.h"
#include <iostream>
#include <random>
#include <bitset>

int main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv);
    Vpr_encoder *tb = new Vpr_encoder;

    // Initialize random number generators
    std::mt19937 gen(42); // Seed for reproducibility
    std::uniform_int_distribution<uint32_t> dist(0, 0xFFFF);
    std::bernoulli_distribution bdist(0.5);

    uint16_t arr[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    // Test all modes and operations
    for (int mode = 0; mode < 10; mode++)
    {
        // Generate random inputs
        for (int i = 0; i < 9; i++)
        {
            arr[i] = dist(gen) % 2;
        }
        // Apply inputs to DUT;
        tb->in1 = arr[0];
        std::cout << arr[0] << std::endl;
        tb->in2 = arr[1];
        std::cout << arr[1] << std::endl;
        tb->in3 = arr[2];
        std::cout << arr[2] << std::endl;
        tb->in4 = arr[3];
        std::cout << arr[3] << std::endl;
        tb->in5 = arr[4];
        std::cout << arr[4] << std::endl;
        tb->in6 = arr[5];
        std::cout << arr[5] << std::endl;
        tb->in7 = arr[6];
        std::cout << arr[6] << std::endl;
        tb->in8 = arr[7];
        std::cout << arr[7] << std::endl;
        tb->in9 = arr[8];
        std::cout << arr[8] << std::endl;

        // Evaluate design
        tb->eval();

        // Compute expected output
        uint16_t exp_out = 0;
        for (int i = 0; i < 9; i++)
        {
            if (arr[i] == 1)
            {
                exp_out = i + 1;
            }
        }

        // Check results
        if (tb->out != exp_out)
        {
            std::cerr << "ERROR: Mode=" << exp_out << std::endl;
        }
        std::cout << "Output: " << std::bitset<4>(tb->out) << std::endl;
        std::cout << exp_out << std::endl;
    }

    std::cout << "\nEncoder tests complete." << std::endl;
    tb->final();
    delete tb;
    return 0;
}