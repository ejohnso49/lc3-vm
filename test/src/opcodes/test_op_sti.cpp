#include "CppUTest/TestHarness.h"
#include "memory.h"
#include "opcodes.h"
#include "registers.h"

TEST_GROUP(OpSti) {
    void setup(void) {
        registers_init();
        memory_init();
    }
};

TEST(OpSti, PosOffset) {
    uint16_t source = Register_R1;
    uint16_t pc = 0x100;
    uint16_t offset = 0x10;
    uint16_t address = 0x200;
    uint16_t value = 0x55;
    uint16_t instruction = ((OP_STI << 12) | (source << 9) | (offset & 0x1FF));

    memory_write(pc + offset, address);
    registers[Register_PC] = pc;
    registers[source] = value;

    op_sti(instruction);

    UNSIGNED_LONGS_EQUAL(value, memory_read(address));
}

TEST(OpSti, NegOffset) {
    uint16_t source = Register_R1;
    uint16_t pc = 0x100;
    int16_t offset = -0x10;
    uint16_t address = 0x200;
    uint16_t value = 0x55;
    uint16_t instruction = ((OP_STI << 12) | (source << 9) | (offset & 0x1FF));

    memory_write(pc + offset, address);
    registers[Register_PC] = pc;
    registers[source] = value;

    op_sti(instruction);

    UNSIGNED_LONGS_EQUAL(value, memory_read(address));
}
