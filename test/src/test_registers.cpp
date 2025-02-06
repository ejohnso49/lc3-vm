#include "CppUTest/TestHarness.h"
#include "registers.h"
#include "util.h"
#include <stdbool.h>

TEST_GROUP(Registers) {
    void setup(void) {
        registers_init();
    }
};

TEST(Registers, Init) {
    for (size_t i = 0; i < ARRAY_SIZE(registers); i++) {
        registers[i] = (uint16_t)0xAA55;
    }
    registers_init();

    for (size_t i = 0; i < ARRAY_SIZE(registers); i++) {
        if (i == Register_PSR) {
            UNSIGNED_LONGS_EQUAL(RegCondFlag_ZERO, registers[i]);
        } else {
            UNSIGNED_LONGS_EQUAL(0, registers[i]);
        }
    }
}

TEST(Registers, UpdateCondNeg) {
    registers[Register_R0] = -1;
    registers_update_cond(Register_R0);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_NEG, registers[Register_PSR]);
}

TEST(Registers, UpdateCondPos) {
    registers[Register_R0] = 1;
    registers_update_cond(Register_R0);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_POS, registers[Register_PSR]);
}

TEST(Registers, UpdateCondZero) {
    registers[Register_R0] = 0;
    registers_update_cond(Register_R0);
    UNSIGNED_LONGS_EQUAL(RegCondFlag_ZERO, registers[Register_PSR]);
}

TEST(Registers, PcInit) {
    registers_pc_init();

    for (size_t i = 0; i < ARRAY_SIZE(registers); i++) {
        if (i == Register_PSR) {
            UNSIGNED_LONGS_EQUAL(RegCondFlag_ZERO, registers[i]);
        } else if (i == Register_PC) {
            UNSIGNED_LONGS_EQUAL(REGISTERS_PC_DEFAULT_START, registers[i]);
        } else {
            UNSIGNED_LONGS_EQUAL(0, registers[i]);
        }
    }
}

TEST(Registers, PsrPrivilegeMode) {
    uint16_t psr = 0xFFFF;
    CHECK(REGISTERS_PSR_PRIVILEGE_MODE(psr));

    psr = 0;
    CHECK_FALSE(REGISTERS_PSR_PRIVILEGE_MODE(psr));
}

TEST(Registers, PsrPrivilegeLevel) {
    uint16_t psr = 0x0700;
    BYTES_EQUAL(7, REGISTERS_PSR_PRIVILEGE_LVL(psr));
}