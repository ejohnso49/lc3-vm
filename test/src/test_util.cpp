#include "CppUTest/TestHarness.h"
#include "util.h"

TEST_GROUP(Util) {
};

TEST(Util, SignExtend) {
    // Checks standard case, positive integer should not change bits
    int16_t value = 0x00FF;
    LONGS_EQUAL(value, sign_extend_16(value, 9));

    // Checks standard case, negative integer should change bits -1 in 9 bits -> -1 in 16
    value = 0x01FF;
    value = sign_extend_16(value, 9);
    LONGS_EQUAL(-1, value);

    // Checks pathalogical case where bits outside of bit width are set, should not change bits
    value = 0x1001;
    LONGS_EQUAL(value, sign_extend_16(value, 9));
}

TEST(Util, ZeroExtend) {
    int8_t value = 0x30;
    UNSIGNED_LONGS_EQUAL((uint16_t)value, zero_extend_16(value, 8));
}

TEST(Util, Swap) {
    uint16_t value = 0xAA55;
    uint16_t swapped_value = swap_16(value);

    UNSIGNED_LONGS_EQUAL(0x55AA, swapped_value);
}
