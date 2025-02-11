#include "CppUTest/TestHarness.h"
#include "trap.h"
#include "opcodes.h"
#include "registers.h"
#include "memory.h"

TEST_GROUP(OpTrap) {
    void setup(void) {
        registers_init();
        memory_init();
    }
};

TEST(OpTrap, UserDefVector) {
    uint16_t user_def_vector = 0x30;
    uint16_t user_def_vector_value = 0x1234;
    uint16_t prior_pc_value = 0x55AA;
    memory_write(user_def_vector, user_def_vector_value);
    uint16_t instruction = ((OP_TRAP << 12) | user_def_vector);

    registers[Register_PC] = prior_pc_value;
    op_trap(instruction);

    UNSIGNED_LONGS_EQUAL(prior_pc_value, registers[Register_R7]);
    UNSIGNED_LONGS_EQUAL(user_def_vector_value, registers[Register_PC]);
}