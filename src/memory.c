#include "memory.h"
#include "util.h"
#include "device.h"
#include <string.h>

uint16_t memory[MEMORY_SIZE] = {0};

void memory_init(void) {
    memset(memory, 0, sizeof(memory));
}

uint16_t memory_read(uint16_t address) {
    if (address == DEVICE_KBSR) {
        keyboard_check_status();
    }
    return memory[address];
}

void memory_write(uint16_t address, uint16_t value) {
    memory[address] = value;
}
