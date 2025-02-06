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
    eRegister dest = (instruction >> 9) & 0x7;
    uint16_t pc_offset = instruction & 0x1FF;
    uint16_t pc = registers[Register_PC];

    SIGN_EXTEND16(pc_offset, 9);

    registers[dest] = memory_read(pc + pc_offset);
    registers_update_cond(dest);
}

void op_st(uint16_t instruction) {
    eRegister source = (instruction >> 9) & 0x7;
    uint16_t pc_offset = instruction & 0x1FF;
    uint16_t pc = registers[Register_PC];
    uint16_t value = registers[source];

    SIGN_EXTEND16(pc_offset, 9);
    memory_write(pc + pc_offset, value);
}

void op_jsr(uint16_t instruction) {
    bool imm = (instruction & 0x800);
    uint16_t new_pc = 0;

    // Store incremented PC
    registers[Register_R7] = registers[Register_PC];

    if (imm) {
        uint16_t pc_offset = (instruction & 0x7FF);
        SIGN_EXTEND16(pc_offset, 11);
        new_pc = registers[Register_PC] + pc_offset;
    } else {
        eRegister base_r = (instruction >> 6) & 0x7;
        new_pc = registers[base_r];
    }

    registers[Register_PC] = new_pc;
}

void op_and(uint16_t instruction) {
    bool imm = instruction & 0x40;
    eRegister dest = (instruction >> 9) & 0x7;
    eRegister sr1 = (instruction >> 6) & 0x7;
    uint16_t result = 0;

    if (imm) {
        uint16_t imm_val = instruction & 0x1F;
        SIGN_EXTEND16(imm_val, 5);
        result = registers[sr1] & imm_val;
    } else {
        eRegister sr2 = instruction & 0x7;
        result = registers[sr1] & registers[sr2];
    }

    registers[dest] = result;
    registers_update_cond(dest);
}

void op_ldr(uint16_t instruction) {
    eRegister dest = (instruction >> 9) & 0x3;
    eRegister base = (instruction >> 6) & 0x3;
    int16_t offset = instruction & 0x3F;

    SIGN_EXTEND16(offset, 6);
    registers[dest] = memory_read(registers[base] + offset);
    registers_update_cond(dest);
}