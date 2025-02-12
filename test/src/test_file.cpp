#include "CppUTest/TestHarness.h"
#include "file.h"
#include "registers.h"
#include "memory.h"
#include <stdio.h>
#include <unistd.h>


TEST_GROUP(File) {
    void setup(void) {
        registers_init();
        memory_init();
    }
};

TEST(File, FileReadImage) {
    const char *file_name = "test/bin/test_program.bin";
    CHECK_FALSE(file_read_image(file_name));

    // Test program contains 14 words (16-bit words) of data
    for (size_t i = 0; i < 14; i++) {
        uint16_t data = memory_read(0x3000 + i);
        uint8_t lower = data & 0xFFFF;
        uint8_t upper = data >> 8;

        UNSIGNED_LONGS_EQUAL(i + 2, lower);
        UNSIGNED_LONGS_EQUAL(0x1, upper);
    }
}
