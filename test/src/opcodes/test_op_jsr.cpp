#include "opcodes.h"
#include "CppUTest/TestHarness.h"
#include "registers.h"

TEST_GROUP(OpJsr) {
    void setup(void) {
        registers_init();
    }
};

TEST(OpJsr, PosOffset) {
    uint16_t pc_offset = 10 & 0x7FF;
    uint16_t instruction = ((OP_JSR << 12) | (1 << 11) | (pc_offset));

    op_jsr(instruction);

    UNSIGNED_LONGS_EQUAL(10, registers[Register_PC]);
}

TEST(OpJsr, NegOffset) {
    uint16_t pc_offset = -10 & 0x7FF;
    uint16_t instruction = ((OP_JSR << 12) | (1 << 11) | (pc_offset));

    op_jsr(instruction);

    LONGS_EQUAL(-10, (int16_t)registers[Register_PC]);
}

TEST(OpJsr, RegVal) {
    eRegister base_r = Register_R1;
    registers[base_r] = 10;

    uint16_t instruction = ((OP_JSR << 12) | (base_r << 6));

    op_jsr(instruction);

    UNSIGNED_LONGS_EQUAL(10, registers[Register_PC]);
}