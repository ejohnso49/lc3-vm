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
                break;
            case OP_ADD:
                break;
            case OP_LD:
                break;
            case OP_ST:
                break;
            case OP_JSR:
                break;
            case OP_AND:
                break;
            case OP_LDR:
                break;
            case OP_STR:
                break;
            case OP_RTI:
                break;
            case OP_NOT:
                break;
            case OP_LDI:
                break;
            case OP_STI:
                break;
            case OP_JMP:
                break;
            case OP_RES:
                break;
            case OP_LEA:
                break;
            case OP_TRAP:
                break;
            case OP_MAX:
            default:
                printf("Error: Invalid opcode: %x\n", op);
                exit(10);
        }
    }
}