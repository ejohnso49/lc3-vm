#include "CppUTest/TestHarness.h"
#include "opcodes.h"
#include "memory.h"
#include "registers.h"

TEST_GROUP(OpStr) {
    void setup(void) {
        registers_init();
        memory_init();
    }
};

TEST(OpStr, PosOffset) {
    uint16_t test_val = 0x55;
    eRegister source = Register_R0;
    eRegister base = Register_R6;
    uint16_t offset = 0x10 & 0x1FF;
    uint16_t base_val = 0x100;

    uint16_t instruction = ((OP_STR << 12) | (source << 9) | (base << 6) | (offset));

    registers[source] = test_val;
    registers[base] = base_val;

    op_str(instruction);

    UNSIGNED_LONGS_EQUAL(test_val, memory_read(base_val + offset));
}

TEST(OpStr, NegOffSet) {
    uint16_t test_val = 0x55;
    eRegister source = Register_R0;
    eRegister base = Register_R6;
    int16_t offset = -0x10 & 0x3F;
    uint16_t base_val = 0x100;

    uint16_t instruction = ((OP_STR << 12) | (source << 9) | (base << 6) | (offset));

    registers[source] = test_val;
    registers[base] = base_val;

    op_str(instruction);

    UNSIGNED_LONGS_EQUAL(test_val, memory_read(base_val + -0x10));
}
