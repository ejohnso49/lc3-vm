#include "CppUTest/TestHarness.h"
#include "memory.h"
#include "opcodes.h"
#include "registers.h"

TEST_GROUP(OpLdi) {
    void setup(void) {
        registers_init();
        memory_init();
    }
};

TEST(OpLdi, PosOffset) {
    uint16_t dest = Register_R1;
    uint16_t pc = 0x100;
    uint16_t offset = 0x10;
    uint16_t address = 0x200;
    uint16_t value = 0x55;
    uint16_t instruction = ((OP_LDI << 12) | (dest << 9) | (offset & 0x1FF));

    memory_write(pc + offset, address);
    memory_write(address, value);
    registers[Register_PC] = pc;

    op_ldi(instruction);

    UNSIGNED_LONGS_EQUAL(value, registers[dest]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_POS, registers[Register_PSR]);
}

TEST(OpLdi, NegOffset) {
    uint16_t dest = Register_R1;
    uint16_t pc = 0x100;
    int16_t offset = -0x10;
    uint16_t address = 0x200;
    uint16_t value = 0x55;
    uint16_t instruction = ((OP_LDI << 12) | (dest << 9) | (offset & 0x1FF));

    memory_write(pc + offset, address);
    memory_write(address, value);
    registers[Register_PC] = pc;

    op_ldi(instruction);

    UNSIGNED_LONGS_EQUAL(value, registers[dest]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_POS, registers[Register_PSR]);
}
