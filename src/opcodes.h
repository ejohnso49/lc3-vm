#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum OpCode {
    OP_BR = 0,
    OP_ADD,
    OP_LD,
    OP_ST,
    OP_JSR,
    OP_AND,
    OP_LDR,
    OP_STR,
    OP_RTI,
    OP_NOT,
    OP_LDI,
    OP_STI,
    OP_JMP,
    OP_RES,
    OP_LEA,
    OP_TRAP,
    OP_MAX,
} eOpCode;

void op_add(uint16_t instruction);
void op_ld(uint16_t instruction);
void op_st(uint16_t instruction);
void op_st(uint16_t instruction);
void op_jsr(uint16_t instruction);
void op_and(uint16_t instruction);
void op_ldr(uint16_t instruction);
void op_str(uint16_t instruction);
void op_rti(uint16_t instruction);
void op_not(uint16_t instruction);
void op_ldi(uint16_t instruction);
void op_sti(uint16_t instruction);
void op_jmp(uint16_t instruction);
void op_res(uint16_t instruction);
void op_lea(uint16_t instruction);
void op_trap(uint16_t instruction);

#ifdef __cplusplus
}
#endif
