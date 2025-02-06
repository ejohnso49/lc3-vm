#include "CppUTest/TestHarness.h"
#include "opcodes.h"
#include "registers.h"

TEST_GROUP(OpAdd) {
    void setup(void) {
        registers_init();
    }
};

TEST(OpAdd, TwoRegs_TwoPos) {
    registers[Register_R0] = 1;
    registers[Register_R1] = 1;

    uint16_t instruction = ((OP_ADD << 12) | (Register_R2 << 9) | (Register_R0 << 6) | (Register_R1 << 0));
    op_add(instruction);

    LONGS_EQUAL(2, registers[Register_R2]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_POS, registers[Register_PSR]);
}

TEST(OpAdd, TwoRegs_OnePos) {
    registers[Register_R0] = -1;
    registers[Register_R1] = 0;

    uint16_t instruction = ((OP_ADD << 12) | (Register_R2 << 9) | (Register_R0 << 6) | (Register_R1 << 0));
    op_add(instruction);

    LONGS_EQUAL(-1, (int16_t)registers[Register_R2]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_NEG, registers[Register_PSR]);
}

TEST(OpAdd, TwoRegs_TwoNeg) {
    registers[Register_R0] = -1;
    registers[Register_R1] = -1;

    uint16_t instruction = ((OP_ADD << 12) | (Register_R2 << 9) | (Register_R0 << 6) | (Register_R1 << 0));
    op_add(instruction);

    LONGS_EQUAL(-2, (int16_t)registers[Register_R2]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_NEG, registers[Register_PSR]);
}

TEST(OpAdd, Imm_Neg) {
    registers[Register_R0] = 5;
    uint8_t imm = -6 & 0x1f;

    uint16_t instruction = ((OP_ADD << 12) | (Register_R1 << 9) | (Register_R0 << 6) | (1 << 5) | (imm));
    op_add(instruction);

    LONGS_EQUAL(-1, (int16_t)registers[Register_R1]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_NEG, registers[Register_PSR]);
}

TEST(OpAdd, Imm_Pos) {
    registers[Register_R0] = -1;
    uint8_t imm = 6 & 0x1f;

    uint16_t instruction = ((OP_ADD << 12) | (Register_R1 << 9) | (Register_R0 << 6) | (1 << 5) | (imm));
    op_add(instruction);

    LONGS_EQUAL(5, (int16_t)registers[Register_R1]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_POS, registers[Register_PSR]);
}
