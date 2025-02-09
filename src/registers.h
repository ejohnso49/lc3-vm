#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define REGISTERS_PC_DEFAULT_START (0x3000)

#define REGISTERS_PSR_PRIVILEGE_MODE(psr) (((psr) & 0x8000) > 0)
#define REGISTERS_PSR_PRIVILEGE_LVL(psr) (((psr) >> 8) & 0x7)

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
    Register_PSR,
    Register_MAX,
} eRegister;

typedef enum RegCondFlag {
    RegCondFlag_POS = 1 << 0,
    RegCondFlag_ZERO = 1 << 1,
    RegCondFlag_NEG = 1 << 2,
} eRegCondFlag;

extern uint16_t registers[Register_MAX];

void registers_init(void);
void registers_update_cond(eRegister reg);
void registers_pc_init(void);

#ifdef __cplusplus
}
#endif
