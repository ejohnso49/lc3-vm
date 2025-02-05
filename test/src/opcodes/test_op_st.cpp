#include "opcodes.h"
#include "CppUTest/TestHarness.h"
#include "memory.h"
#include "registers.h"

TEST_GROUP(OpSt) {
    void setup(void) {
        registers_init();
        memory_init();
    }
};

TEST(OpSt, PosOffset) {
    eRegister source = Register_R1;
    uint16_t source_val = 0x55;
    uint16_t pc_offset = 10 & 0x1FF;
    uint16_t instruction = ((OP_ST << 12) | (source << 9) | pc_offset); 
    registers[source] = source_val;

    op_st(instruction);

    UNSIGNED_LONGS_EQUAL(source_val, memory_read(pc_offset));
}

TEST(OpSt, NegOffset) {
    eRegister source = Register_R1;
    uint16_t source_val = 0x55;
    uint16_t pc_offset = -10 & 0x1FF;
    uint16_t instruction = ((OP_ST << 12) | (source << 9) | pc_offset); 
    registers[source] = source_val;

    op_st(instruction);

    UNSIGNED_LONGS_EQUAL(source_val, memory_read(-10));
}
