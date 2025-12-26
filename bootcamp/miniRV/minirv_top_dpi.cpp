#include "emulator/minirv_emu.h"
#include "svdpi.h"
#include <iostream>

extern "C" void test_instruction(svBitVecVal *instruction,
                                 svBitVecVal *reg0, svBitVecVal *reg1, svBitVecVal *reg2, svBitVecVal *reg3,
                                 svBitVecVal *reg4, svBitVecVal *reg5, svBitVecVal *reg6, svBitVecVal *reg7,
                                 svBitVecVal *reg8, svBitVecVal *reg9, svBitVecVal *reg10, svBitVecVal *reg11,
                                 svBitVecVal *reg12, svBitVecVal *reg13, svBitVecVal *reg14, svBitVecVal *reg15)
{
    static MinirvEmulator emulator;
    static bool initialized = false;
    if (!initialized)
    {
        emulator.PopulateMemory();
        initialized = true;
    }
    emulator.Evaluate(static_cast<uint32_t>(instruction[0] & 0xFFFFFFFF));
    uint32_t registers[16] = {reg0[0], reg1[0], reg2[0], reg3[0], reg4[0], reg5[0], reg6[0], reg7[0],
                              reg8[0], reg9[0], reg10[0], reg11[0], reg12[0], reg13[0], reg14[0], reg15[0]};

    // std::cout << "Am I running?" << std::endl
    //<< "MY instruction: " << std::bitset<32>(instruction[0]) << std::endl;
    for (int i = 0; i < 16; i++)
    {
        if (emulator.GetRegisterValue(i) != registers[i])
        {
            std::cout << "Mismatch! on instruction: " << std::bitset<32>(instruction[0]) << std::endl;
            std::cout << "Hardware: " << reg0[0] << "   " << reg1[0] << "   " << reg2[0] << "   " << reg3[0] << "   " << reg4[0] << "   " << reg5[0] << "   " << reg6[0] << "   " << reg7[0] << "   " << reg8[0] << "   " << reg9[0] << "   " << reg10[0] << "   " << reg11[0] << "   " << reg12[0] << "   " << reg13[0] << "   " << reg14[0] << "   " << reg15[0] << std::endl;
            std::cout << "Emulator: " << emulator.GetRegisterValue(0) << "   " << emulator.GetRegisterValue(1) << "   " << emulator.GetRegisterValue(2) << "   " << emulator.GetRegisterValue(3) << "   " << emulator.GetRegisterValue(4) << "   " << emulator.GetRegisterValue(5) << "   " << emulator.GetRegisterValue(6) << "   " << emulator.GetRegisterValue(7) << "   " << emulator.GetRegisterValue(8) << "   " << emulator.GetRegisterValue(9) << "   " << emulator.GetRegisterValue(10) << "   " << emulator.GetRegisterValue(11) << "   " << emulator.GetRegisterValue(12) << "   " << emulator.GetRegisterValue(13) << "   " << emulator.GetRegisterValue(14) << "   " << emulator.GetRegisterValue(15) << std::endl;
        }
    }
    // std::cout << "Regs:" << std::endl;
    // std::cout << "Hardware: " << reg0[0] << "   " << reg1[0] << "   " << reg2[0] << "   " << reg3[0] << "   " << reg4[0] << "   " << reg5[0] << "   " << reg6[0] << "   " << reg7[0] << "   " << reg8[0] << "   " << reg9[0] << "   " << reg10[0] << "   " << reg11[0] << "   " << reg12[0] << "   " << reg13[0] << "   " << reg14[0] << "   " << reg15[0] << std::endl;
    // std::cout << "Emulator: " << emulator.GetRegisterValue(0) << "   " << emulator.GetRegisterValue(1) << "   " << emulator.GetRegisterValue(2) << "   " << emulator.GetRegisterValue(3) << "   " << emulator.GetRegisterValue(4) << "   " << emulator.GetRegisterValue(5) << "   " << emulator.GetRegisterValue(6) << "   " << emulator.GetRegisterValue(7) << "   " << emulator.GetRegisterValue(8) << "   " << emulator.GetRegisterValue(9) << "   " << emulator.GetRegisterValue(10) << "   " << emulator.GetRegisterValue(11) << "   " << emulator.GetRegisterValue(12) << "   " << emulator.GetRegisterValue(13) << "   " << emulator.GetRegisterValue(14) << "   " << emulator.GetRegisterValue(15) << std::endl;
}
