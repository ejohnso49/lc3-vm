#include "processor.h"
#include "registers.h"
#include "memory.h"
#include "opcodes.h"

#include <stdbool.h>

static bool running = false;

uint16_t prv_processor_fetch(void) {
    return memory_read(registers[Register_PC]++);
}

void processor_run(void) {
    running = true;
    while (running) {
        uint16_t instruction = prv_processor_fetch();
        eOpCode op = (eOpCode)(instruction >> 12);

        switch (op) {
            case OP_BR:
                op_br(instruction);
                break;
            case OP_ADD:
                op_add(instruction);
                break;
            case OP_LD:
                op_ld(instruction);
                break;
            case OP_ST:
                op_st(instruction);
                break;
            case OP_JSR:
                op_jsr(instruction);
                break;
            case OP_AND:
                op_and(instruction);
                break;
            case OP_LDR:
                op_ldr(instruction);
                break;
            case OP_STR:
                op_str(instruction);
                break;
            case OP_RTI:
                op_rti(instruction);
                break;
            case OP_NOT:
                op_not(instruction);
                break;
            case OP_LDI:
                op_ldi(instruction);
                break;
            case OP_STI:
                op_sti(instruction);
                break;
            case OP_JMP:
                op_jmp(instruction);
                break;
            case OP_RES:
                op_res(instruction);
                break;
            case OP_LEA:
                op_lea(instruction);
                break;
            case OP_TRAP:
                op_trap(instruction);
                break;
            case OP_MAX:
            default:
                printf("Error: Invalid opcode: %x\n", op);
                exit(10);
        }
    }
}