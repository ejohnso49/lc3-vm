#include "opcodes.h"
#include "memory.h"
#include "registers.h"
#include "util.h"
#include <stdbool.h>

void op_br(uint16_t instruction) {
    uint8_t cond_bits = (instruction >> 9) & 0x7;
    uint16_t pc_offset = instruction & 0x1FF;

    uint16_t r_cond = registers[Register_COND];
    if (cond_bits & r_cond) {
        SIGN_EXTEND16(pc_offset, 9);
        registers[Register_PC] += pc_offset;
    }
}

void op_add(uint16_t instruction) {
    bool immediate = (instruction & 0x20);
    eRegister dest = (instruction >> 9) & 0x7;
    eRegister src_1 = (instruction >> 6) & 0x7;
    int16_t src_1_val = (int16_t)registers[src_1];
    int16_t src_2_val = 0;

    if (immediate) {
        src_2_val = instruction & 0x1F;
        SIGN_EXTEND16(src_2_val, 5);
    } else {
        eRegister src_2 = instruction & 0x7;
        src_2_val = registers[src_2];
    }

    registers[dest] = src_1_val + src_2_val;
    registers_update_cond(dest);
}

void op_ld(uint16_t instruction) {
    uint16_t dest = (instruction >> 9) & 0x7;
    uint16_t pc_offset = instruction & 0x1FF;
    uint16_t pc = registers[Register_PC];

    SIGN_EXTEND16(pc_offset, 9);

    registers[dest] = memory_read(pc + pc_offset);
    registers_update_cond(dest);
}
