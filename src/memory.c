#include "memory.h"
#include "util.h"
#include <string.h>

uint16_t memory[MEMORY_SIZE] = {0};

void memory_init(void) {
    memset(memory, 0, ARRAY_SIZE(memory));
}
