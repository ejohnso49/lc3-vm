#include "CppUTest/TestHarness.h"
#include "registers.h"
#include "opcodes.h"
#include "memory.h"
#include "util.h"

TEST_GROUP(OpLdr) {
    void setup(void) {
        registers_init();
        memory_init();
    }
};

TEST(OpLdr, PosOffset) {
    eRegister dest = Register_R1;
    eRegister base = Register_R0;
    uint16_t base_val = 0x100;
    uint16_t offset = 0x10 & 0x3F;
    uint16_t test_val = 0x5555;

    uint16_t instruction = ((OP_LDR << 12) | (dest << 9) | (base << 6) | (offset));

    registers[base] = base_val;
    memory_write(base_val + offset, test_val);

    op_ldr(instruction);

    UNSIGNED_LONGS_EQUAL(test_val, registers[dest]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_POS, registers[Register_COND]);
}

TEST(OpLdr, NegOffset) {
    eRegister dest = Register_R1;
    eRegister base = Register_R0;
    uint16_t base_val = 0x100;
    int16_t offset = -0x10 & 0x3F;
    uint16_t test_val = 0xAAAA;

    uint16_t instruction = ((OP_LDR << 12) | (dest << 9) | (base << 6) | (offset));

    registers[base] = base_val;
    
    SIGN_EXTEND16(offset, 6);
    memory_write(base_val + (int16_t)offset, test_val);

    op_ldr(instruction);

    UNSIGNED_LONGS_EQUAL(test_val, registers[dest]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_NEG, registers[Register_COND]);
}