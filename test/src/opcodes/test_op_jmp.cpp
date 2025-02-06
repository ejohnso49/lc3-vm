#include "CppUTest/TestHarness.h"
#include "registers.h"
#include "opcodes.h"

TEST_GROUP(OpJmp) {
    void setup(void) {
        registers_init();
    }
};

TEST(OpJmp, JmpReg) {
    eRegister base = Register_R1;
    uint16_t base_val = 0x200;
    uint16_t instruction = ((OP_JMP << 12) | (base << 6));

    registers[base] = base_val;

    op_jmp(instruction);

    UNSIGNED_LONGS_EQUAL(base_val, registers[Register_PC]);
}

TEST(OpJmp, Ret) {
    uint16_t new_pc = 0x200;
    uint16_t instruction = ((OP_JMP << 12) | (0x7 << 6));
    registers[Register_R7] = new_pc;

    op_jmp(instruction);

    UNSIGNED_LONGS_EQUAL(new_pc, registers[Register_PC]);
}
