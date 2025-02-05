#include "opcodes.h"
#include "registers.h"
#include "memory.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(OpLd) {
    void setup(void) {
        registers_init();
        memory_init();
    }
};

TEST(OpLd, PositiveOffset) {
    uint16_t offset = 10 & 0x1FF;
    uint16_t test_val = 0x55;
    eRegister dest = Register_R1;
    uint16_t instruction = ((OP_BR << 12) | (dest << 9) | (offset));

    memory_write(offset, test_val);
    op_ld(instruction);

    UNSIGNED_LONGS_EQUAL(test_val, registers[dest]);
}

TEST(OpLd, NegativeOffset) {
    uint16_t offset = -10 & 0x1FF;
    uint16_t test_val = 0x55;
    eRegister dest = Register_R1;
    uint16_t instruction = ((OP_BR << 12) | (dest << 9) | (offset));

    memory_write(-10, test_val);
    op_ld(instruction);

    UNSIGNED_LONGS_EQUAL(test_val, registers[dest]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_POS, registers[Register_COND]);
}