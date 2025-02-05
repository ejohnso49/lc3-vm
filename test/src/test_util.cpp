#include "CppUTest/TestHarness.h"
#include "util.h"

TEST_GROUP(Util) {
};

TEST(Util, SignExtend) {
    // Checks standard case, positive integer should not change bits
    int16_t value = 0x00FF;
    int16_t old_value = value;
    SIGN_EXTEND16(value, 9);
    LONGS_EQUAL(old_value, value);

    // Checks standard case, negative integer should change bits -1 in 9 bits -> -1 in 16
    value = 0x01FF;
    SIGN_EXTEND16(value, 9);
    CHECK(value != old_value);
    LONGS_EQUAL(-1, value);

    // Checks pathalogical case where bits outside of bit width are set, should not change bits
    value = 0x1001;
    old_value = value;
    SIGN_EXTEND16(value, 9);
    LONGS_EQUAL(old_value, value);
}