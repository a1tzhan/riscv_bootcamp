#include <Vscpu.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
#include "scpu_tb.h"

void scpu_tb::reset(Vscpu *scpu, VerilatedVcdC *tfp)
{
    scpu->rst = 1;
    scpu->clk = 0;
    scpu->eval();
    if (tfp)
        tfp->dump(sim_time++);
    scpu->clk = 1;
    scpu->eval();
    if (tfp)
        tfp->dump(sim_time++);
    scpu->rst = 0;
}

void scpu_tb::tick(Vscpu *scpu, VerilatedVcdC *tfp, int cycles)
{
    scpu->clk = 0;
    scpu->eval();
    if (tfp)
        tfp->dump(sim_time++);
    scpu->clk = 1;
    scpu->eval();
    if (tfp)
        tfp->dump(sim_time++);
}

int scpu_tb::get_pc(Vscpu *scpu)
{
    return scpu->scpu->pc->q;
}

int scpu_tb::get_register(Vscpu *scpu, int reg_num)
{
    switch (reg_num)
    {
    case 0:
        return scpu->scpu->register_file->q1;
    case 1:
        return scpu->scpu->register_file->q2;
    default:
        std::cerr << "Invalid register number: " << reg_num << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

int scpu_tb::get_alu_out(Vscpu *scpu)
{
    return scpu->scpu->alu->alu_out;
}

void scpu_tb::print_state(Vscpu *scpu)
{
    std::cout << "PC: " << get_pc(scpu) << std::endl;
    std::cout << "Register 0: " << get_register(scpu, 0) << std::endl;
    std::cout << "Register 1: " << get_register(scpu, 1) << std::endl;
    std::cout << "ALU Output: " << get_alu_out(scpu) << std::endl;
}

int main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv);
    Vscpu *tb = new Vscpu;

    srand(time(0));

    int errors = 0;
    const int NUM_TESTS = 1000;
    uint8_t regs[4] = {0, 0, 0, 0};

    scpu_tb::reset(tb);

    // Set all registers and test all ALU operations on them. Do it 1000 times.
    // I have to  check that outputs are correct in the correct register but restore the register value afterwards.
    for (int i = 0; i < NUM_TESTS; i++)
    {
        // Generate instruction
        uint8_t instruction = scpu_tb::gen_inst();
        uint8_t a = regs[(instruction >> 6) & 0x3];
        uint8_t b;
        int imm = 0;
        if ((instruction & 0x3) == 1)
            b = (instruction >> 2) & 0xF;
        else
            b = regs[(instruction >> 4) & 0x3];
        // Calculate expected value
        uint8_t exp_alu_out;
        scpu_tb::compute_instruction(a, b, ((instruction >> 2) & 0x3), exp_alu_out);
        regs[(instruction >> 6) & 0x3] = exp_alu_out;

        // Test instruction on inputs
        scpu_tb::test_inst(tb, instruction, exp_alu_out, errors, regs);
    }

    std::cout << "\nScpu tests complete. Errors: " << errors << std::endl;
    tb->final();
    delete tb;
    return errors ? 1 : 0;
}