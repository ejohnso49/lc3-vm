#include "registers.h"
#include <string.h>
#include "util.h"

uint16_t registers[Register_MAX] = {0};

void registers_init(void) {
    memset(registers, 0, sizeof(registers));
    registers[Register_COND] = RegCondFlag_ZERO;
}

void registers_update_cond(eRegister reg) {
    uint16_t result = registers[reg];

    uint16_t flag = 0;
    if (result == 0) {
        flag = RegCondFlag_ZERO;
    } else if ((int16_t)result < 0) {
        flag = RegCondFlag_NEG;
    } else {
        flag = RegCondFlag_POS;
    }

    registers[Register_COND] = flag;
}

void registers_pc_init(void) {
    registers[Register_PC] = REGISTERS_PC_DEFAULT_START;
}