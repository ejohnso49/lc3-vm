#include "CppUTest/TestHarness.h"
#include "registers.h"
#include "opcodes.h"

TEST_GROUP(OpNot) {
    void setup(void) {
        registers_init();
    }
};

TEST(OpNot, Not) {
    uint16_t dest = Register_R0;
    uint16_t source = Register_R1;
    uint16_t source_val = 0xFFFF;
    uint16_t instruction = ((OP_NOT << 12) | (dest << 9) | (source << 6) | (0x3F));
    registers[source] = source_val;

    op_not(instruction);

    UNSIGNED_LONGS_EQUAL((uint16_t)~source_val, registers[dest]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_ZERO, registers[Register_PSR]);
}
