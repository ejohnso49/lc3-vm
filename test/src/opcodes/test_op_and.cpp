#include "opcodes.h"
#include "CppUTest/TestHarness.h"
#include "registers.h"

TEST_GROUP(OpAnd) {
    void setup(void) {
        registers_init();
    }
};

TEST(OpAnd, TwoRegs) {
    eRegister dest = Register_R0;
    eRegister sr1 = Register_R1;
    eRegister sr2 = Register_R2;
    uint16_t sr1_val = 0x55;
    uint16_t sr2_val = 0xAA;

    uint16_t instruction = ((OP_AND << 12) | (dest << 9) | (sr1 << 6) | (sr2));

    registers[sr1] = sr1_val;
    registers[sr2] = sr2_val;

    op_and(instruction);

    UNSIGNED_LONGS_EQUAL(0, registers[dest]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_ZERO, registers[Register_COND]);
}

TEST(OpAnd, NegImm) {
    eRegister dest = Register_R0;
    eRegister sr1 = Register_R1;
    uint16_t imm = -1 & 0x1F;
    uint16_t sr1_val = 0x6;
    uint16_t instruction = ((OP_AND << 12) | (dest << 9) | (sr1 << 6) | (1 << 5) | (imm));

    registers[sr1] = sr1_val;

    op_and(instruction);

    UNSIGNED_LONGS_EQUAL(sr1_val, registers[dest]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_POS, registers[Register_COND]);

}