#include "memory.h"
#include "util.h"
#include <string.h>

uint16_t memory[MEMORY_SIZE] = {0};

void memory_init(void) {
    memset(memory, 0, sizeof(memory));
}

uint16_t memory_read(uint16_t address) {
    return memory[address];
}

void memory_write(uint16_t address, uint16_t value) {
    memory[address] = value;
}
