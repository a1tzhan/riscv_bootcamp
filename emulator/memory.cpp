#include "svdpi.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <cstring>

#define MEM_SIZE (128 * 1024 * 1024) // 128MB
static uint8_t memory[MEM_SIZE];

// Initialize memory from hex file
extern "C" void mem_init(const char *hex_file)
{
    std::ifstream in(hex_file);
    if (!in)
    {
        std::cerr << "Error: cannot open '" << hex_file << "' for memory initialization.\n";
        return;
    }

    std::string line;
    uint32_t addr = 0;
    while (std::getline(in, line) && addr < MEM_SIZE)
    {
        uint32_t word = std::stoul(line, nullptr, 16);
        // Store in little-endian format
        memory[addr + 0] = (word >> 0) & 0xFF;
        memory[addr + 1] = (word >> 8) & 0xFF;
        memory[addr + 2] = (word >> 16) & 0xFF;
        memory[addr + 3] = (word >> 24) & 0xFF;
        addr += 4;
    }
    std::cout << "Loaded " << (addr / 4) << " words into memory\n";
}

// Read 32-bit word from memory (word-aligned)
extern "C" uint32_t mem_read(uint32_t raddr)
{
    uint32_t aligned_addr = raddr & ~0x3u; // Word-align address

    if (aligned_addr >= MEM_SIZE)
    {
        std::cerr << "Memory read out of bounds: 0x" << std::hex << raddr << std::endl;
        return 0;
    }

    // Read 4 bytes in little-endian format
    uint32_t data = (uint32_t)memory[aligned_addr + 0] |
                    ((uint32_t)memory[aligned_addr + 1] << 8) |
                    ((uint32_t)memory[aligned_addr + 2] << 16) |
                    ((uint32_t)memory[aligned_addr + 3] << 24);
    return data;
}

// Write to memory with byte mask
extern "C" void mem_write(uint32_t waddr, uint32_t wdata, uint8_t wmask)
{
    uint32_t aligned_addr = waddr & ~0x3u; // Word-align address

    if (aligned_addr >= MEM_SIZE)
    {
        std::cerr << "Memory write out of bounds: 0x" << std::hex << waddr << std::endl;
        return;
    }

    // Write each byte according to mask
    if (wmask & 0x1)
        memory[aligned_addr + 0] = (wdata >> 0) & 0xFF;
    if (wmask & 0x2)
        memory[aligned_addr + 1] = (wdata >> 8) & 0xFF;
    if (wmask & 0x4)
        memory[aligned_addr + 2] = (wdata >> 16) & 0xFF;
    if (wmask & 0x8)
        memory[aligned_addr + 3] = (wdata >> 24) & 0xFF;
}
