#include "CppUTest/TestHarness.h"
#include "memory.h"
#include "util.h"

TEST_GROUP(Memory) {
    void setup(void) {
        memory_init();
    }
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

TEST(Memory, Read) {
    for (size_t i = 0; i < 32; i++) {
        memory[i] = (uint16_t)i;
    }

    for (size_t i = 0; i < 32; i++) {
        uint16_t value = memory_read(i);
        UNSIGNED_LONGS_EQUAL(i, value);
    }
}

TEST(Memory, Write) {
    for (size_t i = 0; i < 32; i++) {
        memory[i] = 0x55;
    }

    for (size_t i = 0; i < 32; i++) {
        memory_write(i, 0);
        UNSIGNED_LONGS_EQUAL(0, memory[i]);
    }
}
