#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MEMORY_SIZE (1 << 16)

extern uint16_t memory[MEMORY_SIZE];

void memory_init(void);

#ifdef __cplusplus
}
#endif
