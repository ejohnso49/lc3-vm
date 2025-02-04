#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_StupidTest(void) {
    TEST_ASSERT_EQUAL_HEX8(40, 40);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_StupidTest);
    return UNITY_END();
}