#include "CppUTest/TestHarness.h"
#include "util.h"

TEST_GROUP(Util) {
};

TEST(Util, SignExtend) {
    uint16_t value = 0x0011;
    uint16_t old_value = value;
    SIGN_EXTEND16(value, 9);
    UNSIGNED_LONGS_EQUAL(value, old_value);
}