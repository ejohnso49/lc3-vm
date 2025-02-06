#include "CppUTest/TestHarness.h"
#include "registers.h"
#include "opcodes.h"

TEST_GROUP(OpLea) {
    void setup(void) {
        registers_init();
    }
};

TEST(OpLea, PosOffset) {
    eRegister dest = Register_R1;
    uint16_t pc = 0x200;
    uint16_t offset = 0x10 & 0x1FF;
    uint16_t instruction = ((OP_LEA << 12) | (dest << 9) | offset);

    registers[Register_PC] = pc;

    op_lea(instruction);

    UNSIGNED_LONGS_EQUAL(pc + offset, registers[dest]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_POS, registers[Register_PSR]);
}

TEST(OpLea, NegOffset) {
    eRegister dest = Register_R1;
    uint16_t pc = 0x200;
    int16_t offset = -0x10;
    uint16_t instruction = ((OP_LEA << 12) | (dest << 9) | (offset & 0x1FF));

    registers[Register_PC] = pc;

    op_lea(instruction);

    UNSIGNED_LONGS_EQUAL(pc + offset, registers[dest]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_POS, registers[Register_PSR]);
}
