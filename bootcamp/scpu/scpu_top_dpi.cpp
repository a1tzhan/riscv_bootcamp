#include "emulator/scpu_emu.h"
#include "svdpi.h"
#include <iostream>

extern "C" void test_instruction(svBitVecVal *instruction,
                                 svBitVecVal *reg0, svBitVecVal *reg1, svBitVecVal *reg2, svBitVecVal *reg3,
                                 svBitVecVal *reg4)
{
    static ScpuEmulator emulator;

    emulator.Evaluate(static_cast<uint16_t>(instruction[0] & 0xFF));

    uint16_t registers[4] = {reg0[0], reg1[0], reg2[0], reg3[0]};
    for (int i = 0; i < 4; i++)
    {
        if (emulator.GetRegisterValue(i) != registers[i])
        {
            std::cout << "Mismatch! ";
            std::cout << reg0[0] << "   " << reg1[0] << "   " << reg2[0] << "   " << reg3[0] << std::endl;
            std::cout << emulator.GetRegisterValue(0) << "   " << emulator.GetRegisterValue(1) << "   " << emulator.GetRegisterValue(2) << "   " << emulator.GetRegisterValue(3) << std::endl;
        }
    }
}
