#include "unity.h"
#include <stdio.h>

void setUp(void) {
    printf("Hello regular setup\n");
}
void tearDown(void) {
    printf("Hello regular teardown");
}

void stupid_test(void) {
    printf("Running stupid_test\n");
    TEST_ASSERT_EQUAL_CHAR(0x1, 0x2);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(stupid_test);
    RUN_TEST(stupid_test);
    return UNITY_END();
}