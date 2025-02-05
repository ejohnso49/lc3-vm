#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MEMORY_SIZE (1 << 16)

extern uint16_t memory[MEMORY_SIZE];

void memory_init(void);
uint16_t memory_read(uint16_t address);
void memory_write(uint16_t address, uint16_t value);

#ifdef __cplusplus
}
#endif
