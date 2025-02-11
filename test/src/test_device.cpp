#include "CppUTest/TestHarness.h"
#include "device.h"
#include "memory.h"

TEST_GROUP(Device) {
    void setup(void) {
        memory_init();
    }
};

TEST(Device, KeyboardUpdate) {
    char c = 'c';
    keyboard_update_data(c);
    UNSIGNED_LONGS_EQUAL(c, memory_read(DEVICE_KBDR));
}

TEST(Device, McrHalt) {
    machine_control_halt();
    CHECK((memory_read(DEVICE_MCR) & DEVICE_MCR_CLK_ENABLE_MASK) != 0);
}