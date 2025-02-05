#include "CppUTest/TestHarness.h"
#include "memory.h"
#include "util.h"

TEST_GROUP(Memory) {
};

TEST(Memory, Init) {
    for (size_t i = 0; i < ARRAY_SIZE(memory); i++) {
        memory[i] = (uint16_t)0xAA55;
    }
    memory_init();

    for (size_t i = 0; i < ARRAY_SIZE(memory); i++) {
        UNSIGNED_LONGS_EQUAL(0, memory[i]);
    }    
}
