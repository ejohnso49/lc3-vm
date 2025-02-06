#include "opcodes.h"
#include "CppUTest/TestHarness.h"
#include "registers.h"

TEST_GROUP(OpBr) {
    void setup(void) {
        registers_init();
        registers_pc_init();
    }
};

TEST(OpBr, OpCodeBrNegOffset) {
    uint8_t cond_bits = RegCondFlag_ZERO;
    uint16_t pc_offset = -10 & 0x01FF;
    uint16_t instruction = (OP_BR << 12) | (cond_bits << 9) | (pc_offset);

    op_br(instruction);

    uint16_t new_pc = registers[Register_PC];
    UNSIGNED_LONGS_EQUAL(REGISTERS_PC_DEFAULT_START - 10, new_pc);
}

TEST(OpBr, OpCodeBrPosOffset) {
    uint8_t cond_bits = RegCondFlag_ZERO;
    uint16_t pc_offset = 10 & 0x01FF;
    uint16_t instruction = (OP_BR << 12) | (cond_bits << 9) | (pc_offset);

    op_br(instruction);

    uint16_t new_pc = registers[Register_PC];
    UNSIGNED_LONGS_EQUAL(REGISTERS_PC_DEFAULT_START + 10, new_pc);
}

TEST(OpBr, OpCodeBrCondZ_NoBranch) {
    uint8_t cond_bits = RegCondFlag_ZERO;
    uint16_t pc_offset = 10 & 0x01FF;
    uint16_t instruction = (OP_BR << 12) | (cond_bits << 9) | (pc_offset);
    registers[Register_PSR] = RegCondFlag_POS;

    op_br(instruction);
    uint16_t new_pc = registers[Register_PC];
    UNSIGNED_LONGS_EQUAL(REGISTERS_PC_DEFAULT_START , new_pc);
}

TEST(OpBr, OpCodeBrCondN_Branch) {
    uint8_t cond_bits = RegCondFlag_NEG;
    uint16_t pc_offset = 10 & 0x01FF;
    uint16_t instruction = (OP_BR << 12) | (cond_bits << 9) | (pc_offset);
    registers[Register_PSR] = RegCondFlag_NEG;

    op_br(instruction);
    uint16_t new_pc = registers[Register_PC];
    UNSIGNED_LONGS_EQUAL(REGISTERS_PC_DEFAULT_START + 10, new_pc);
}

TEST(OpBr, OpCodeBrCondN_NoBranch) {
    uint8_t cond_bits = RegCondFlag_POS;
    uint16_t pc_offset = 10 & 0x01FF;
    uint16_t instruction = (OP_BR << 12) | (cond_bits << 9) | (pc_offset);
    registers[Register_PSR] = RegCondFlag_NEG;

    op_br(instruction);
    uint16_t new_pc = registers[Register_PC];
    UNSIGNED_LONGS_EQUAL(REGISTERS_PC_DEFAULT_START , new_pc);
}

TEST(OpBr, OpCodeBrCondP_Branch) {
    uint8_t cond_bits = RegCondFlag_POS;
    uint16_t pc_offset = 10 & 0x01FF;
    uint16_t instruction = (OP_BR << 12) | (cond_bits << 9) | (pc_offset);
    registers[Register_PSR] = RegCondFlag_POS;

    op_br(instruction);
    uint16_t new_pc = registers[Register_PC];
    UNSIGNED_LONGS_EQUAL(REGISTERS_PC_DEFAULT_START + 10, new_pc);
}

TEST(OpBr, OpCodeBrCondP_NoBranch) {
    uint8_t cond_bits = RegCondFlag_NEG;
    uint16_t pc_offset = 10 & 0x01FF;
    uint16_t instruction = (OP_BR << 12) | (cond_bits << 9) | (pc_offset);
    registers[Register_PSR] = RegCondFlag_POS;

    op_br(instruction);
    uint16_t new_pc = registers[Register_PC];
    UNSIGNED_LONGS_EQUAL(REGISTERS_PC_DEFAULT_START , new_pc);
}