#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "trap.h"
#include "opcodes.h"
#include "registers.h"
#include "memory.h"
#include "device.h"

extern "C" {
#include <stdio.h>

int getchar(void) {
    return mock().actualCall("getchar").returnIntValue();
}

int putchar(int c) {
    if (c == 0) {
        printf("what the fuck\n");
    }
    return mock().actualCall("putchar").withIntParameter("c", c).returnIntValue();
}

}

TEST_GROUP(OpTrap) {
    void setup(void) {
        registers_init();
        memory_init();
    }

    void teardown(void) {
        mock().clear();
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

TEST(OpTrap, Getc) {
    uint16_t instruction = ((OP_TRAP << 12) | TRAP_GETC);

    mock().expectOneCall("getchar").andReturnValue('c');

    op_trap(instruction);

    UNSIGNED_LONGS_EQUAL('c', registers[Register_R0]);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_POS, registers[Register_PSR]);
    mock().checkExpectations();
}

TEST(OpTrap, Out) {
    uint16_t value = 'c';
    uint16_t instruction = ((OP_TRAP << 12) | TRAP_OUT);

    registers[Register_R0] = value;
    mock().expectOneCall("putchar").withParameter("c", value);

    op_trap(instruction);
    mock().checkExpectations();
}

TEST(OpTrap, Puts) {
    uint16_t str_address = 0x1234;
    const char *str = "hello";
    uint16_t instruction = ((OP_TRAP << 12) | TRAP_PUTS);

    for (size_t i = 0; i < strlen(str); i++) {
        memory_write(str_address + i, str[i]);
        mock().expectOneCall("putchar").withParameter("c", str[i]);
    }

    registers[Register_R0] = str_address;

    op_trap(instruction);
    mock().checkExpectations();
}

TEST(OpTrap, In) {
    uint16_t instruction = ((OP_TRAP << 12) | TRAP_IN);
    uint16_t value = 'c';

    mock().expectOneCall("getchar").andReturnValue(value);
    mock().expectOneCall("putchar").withParameter("c", value);

    op_trap(instruction);
    mock().checkExpectations();
    UNSIGNED_LONGS_EQUAL(value, registers[Register_R0]);
}

TEST(OpTrap, Putsp) {
    uint16_t instruction = ((OP_TRAP << 12) | TRAP_PUTSP);
    uint16_t str_address = 0x1234;
    const char *str = "hello";

    for (size_t i = 0, j = 0; i < strlen(str); i += 2, j++) {
        uint16_t combined = (str[i + 1] << 8) | str[i];
        memory_write(str_address + j, combined);
        mock().expectOneCall("putchar").withParameter("c", str[i]);
        if (str[i + 1] != '\0') {
            mock().expectOneCall("putchar").withParameter("c", str[i + 1]);
        }
    }

    registers[Register_R0] = str_address;

    op_trap(instruction);
    mock().checkExpectations();
}

TEST(OpTrap, Halt) {
    uint16_t instruction ((OP_TRAP << 12) | TRAP_HALT);

    op_trap(instruction);

    UNSIGNED_LONGS_EQUAL(0x8000, memory_read(DEVICE_MCR));
}
