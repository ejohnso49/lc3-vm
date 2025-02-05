#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum Register {
    Register_R0 = 0,
    Register_R1,
    Register_R2,
    Register_R3,
    Register_R4,
    Register_R5,
    Register_R6,
    Register_R7,
    Register_PC,
    Register_COND,
    Register_MAX,
} eRegister;

typedef enum RegCondFlag {
    RegCondFlag_POS = 1 << 0,
    RegCondFlag_ZERO = 1 << 1,
    RegCondFlag_NEG = 1 << 2,
} eRegCondFlag;

extern uint16_t registers[Register_MAX];

void registers_init(void);

#ifdef __cplusplus
}
#endif
