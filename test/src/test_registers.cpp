#include "CppUTest/TestHarness.h"
#include "registers.h"
#include "util.h"

TEST_GROUP(Registers) {
};

TEST(Registers, Init) {
    for (size_t i = 0; i < ARRAY_SIZE(registers); i++) {
        registers[i] = (uint16_t)0xAA55;
    }
    registers_init();

    for (size_t i = 0; i < ARRAY_SIZE(registers); i++) {
        if (i == Register_COND) {
            UNSIGNED_LONGS_EQUAL(RegCondFlag_ZERO, registers[i]);
        } else {
            UNSIGNED_LONGS_EQUAL(0, registers[i]);
        }
    }
}

TEST(Registers, UpdateCond) {
    registers_init();

    registers[Register_R0] = -1;
    registers_update_cond(Register_R0);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_NEG, registers[Register_COND]);

    registers[Register_R0] = 1;
    registers_update_cond(Register_R0);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_POS, registers[Register_COND]);

    registers[Register_R0] = 0;
    registers_update_cond(Register_R0);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_ZERO, registers[Register_COND]);
}