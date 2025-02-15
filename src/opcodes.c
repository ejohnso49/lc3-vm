#include "opcodes.h"
#include "memory.h"
#include "registers.h"
#include "util.h"
#include "exceptions.h"
#include "trap.h"
#include <stdbool.h>

void op_br(uint16_t instruction) {
    uint8_t cond_bits = (instruction >> 9) & 0x7;
    uint16_t pc_offset = instruction & 0x1FF;

    uint16_t r_cond = registers[Register_PSR];
    if (cond_bits & r_cond) {
        registers[Register_PC] += sign_extend_16(pc_offset, 9);;
    }
}

void op_add(uint16_t instruction) {
    bool immediate = (instruction & 0x20);
    eRegister dest = (instruction >> 9) & 0x7;
    eRegister src_1 = (instruction >> 6) & 0x7;
    int16_t src_1_val = (int16_t)registers[src_1];
    int16_t src_2_val = 0;

    if (immediate) {
        src_2_val = sign_extend_16(instruction & 0x1F, 5);
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

    pc_offset = sign_extend_16(pc_offset, 9);

    registers[dest] = memory_read(pc + pc_offset);
    registers_update_cond(dest);
}

void op_st(uint16_t instruction) {
    eRegister source = (instruction >> 9) & 0x7;
    uint16_t pc_offset = instruction & 0x1FF;
    uint16_t pc = registers[Register_PC];
    uint16_t value = registers[source];

    pc_offset = sign_extend_16(pc_offset, 9);
    memory_write(pc + pc_offset, value);
}

void op_jsr(uint16_t instruction) {
    bool imm = (instruction & 0x800);
    uint16_t new_pc = 0;

    // Store incremented PC
    registers[Register_R7] = registers[Register_PC];

    if (imm) {
        new_pc = registers[Register_PC] + sign_extend_16(instruction & 0x7FF, 11);
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
        result = registers[sr1] & sign_extend_16(imm_val, 5);
    } else {
        eRegister sr2 = instruction & 0x7;
        result = registers[sr1] & registers[sr2];
    }

    registers[dest] = result;
    registers_update_cond(dest);
}

void op_ldr(uint16_t instruction) {
    eRegister dest = (instruction >> 9) & 0x7;
    eRegister base = (instruction >> 6) & 0x7;
    int16_t offset = instruction & 0x3F;

    offset = sign_extend_16(offset, 6);
    registers[dest] = memory_read(registers[base] + offset);
    registers_update_cond(dest);
}

void op_str(uint16_t instruction) {
    eRegister source = (instruction >> 9) & 0x7;
    eRegister base = (instruction >> 6) & 0x7;
    int16_t offset = instruction & 0x3F;

    offset = sign_extend_16(offset, 6);
    memory_write(registers[base] + offset, registers[source]);
}

void op_rti(uint16_t instruction) {
    bool user_mode = REGISTERS_PSR_PRIVILEGE_MODE(registers[Register_PSR]);

    if (user_mode) {
        exception();
    }

    registers[Register_PC] = memory_read(registers[Register_R6]++);
    registers[Register_PSR] = memory_read(registers[Register_R6]++);
}

void op_not(uint16_t instruction) {
    uint16_t dest = (instruction >> 9) & 0x7;
    uint16_t source = (instruction >> 6) & 0x7;

    registers[dest] = ~registers[source];
    registers_update_cond(dest);
}

void op_ldi(uint16_t instruction) {
    uint16_t dest = (instruction >> 9) & 0x7;
    int16_t offset = instruction & 0x1FF;
    uint16_t pc = registers[Register_PC];

    offset = sign_extend_16(offset, 9);
    uint16_t address = memory_read(pc + offset);

    registers[dest] = memory_read(address);
    registers_update_cond(dest);
}

void op_sti(uint16_t instruction) {
    uint16_t source = (instruction >> 9) & 0x7;
    int16_t offset = instruction & 0x1FF;
    uint16_t pc = registers[Register_PC];

    offset = sign_extend_16(offset, 9);
    uint16_t address = memory_read(pc + offset);

    memory_write(address, registers[source]);
}

void op_jmp(uint16_t instruction) {
    eRegister base = (instruction >> 6) & 0x7;

    registers[Register_PC] = registers[base];
}

void op_res(uint16_t instruction) {
    exception();
}

void op_lea(uint16_t instruction) {
    eRegister dest = (instruction >> 9) & 0x7;
    int16_t offset = instruction & 0x1FF;

    offset = sign_extend_16(offset, 9);
    registers[dest] = registers[Register_PC] + offset;
    registers_update_cond(dest);
}

static void prv_op_trap(uint16_t vector) {
    switch (vector) {
        case TRAP_GETC:
            trap_getc();
            break;
        case TRAP_OUT:
            trap_out();
            break;
        case TRAP_PUTS:
            trap_puts();
            break;
        case TRAP_IN:
            trap_in();
            break;
        case TRAP_PUTSP:
            trap_putsp();
            break;
        case TRAP_HALT:
            trap_halt();
            break;
        default:
            printf("Bad trap %x\n", vector);
            exit(1);
    }

    // Restore PC after trap "vector" completes
    registers[Register_PC] = registers[Register_R7];
}

void op_trap(uint16_t instruction) {
    registers[Register_R7] = registers[Register_PC];

    uint16_t vector = zero_extend_16((instruction & 0xFF), 8);

    if (vector >= 0x20 && vector <= 0x25) {
        prv_op_trap(vector);
    } else {
        // Other vectors must restore original PC before returning
        registers[Register_PC] = memory_read(vector);
    }
}
