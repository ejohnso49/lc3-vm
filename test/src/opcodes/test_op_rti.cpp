#include "CppUTest/TestHarness.h"
#include "registers.h"
#include "memory.h"
#include "opcodes.h"

TEST_GROUP(Op_Rti) {
    void setup(void) {
        registers_init();
    }
};

IGNORE_TEST(Op_Rti, UserMode) {
    FAIL("TODO Handle user mode RTI exception\n");
}

TEST(Op_Rti, SupervisorMode) {
    uint16_t stack_ptr = 0x100;
    uint16_t pc = 0x200;
    uint16_t psr = (0x7 << 8) | (RegCondFlag_NEG);
    uint16_t instruction = OP_RTI << 12;
    registers[Register_R6] = stack_ptr;

    memory_write(stack_ptr, pc);
    memory_write(stack_ptr + 1, psr);

    op_rti(instruction);

    UNSIGNED_LONGS_EQUAL(pc, registers[Register_PC]);
    UNSIGNED_LONGS_EQUAL(psr, registers[Register_PSR]);
}
