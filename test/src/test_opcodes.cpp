#include "CppUTest/TestHarness.h"
#include "opcodes.h"

TEST_GROUP(OpCodes) {
};

TEST(OpCodes, InstructionToOpCode) {
    uint16_t instruction = 0xF200;
    eOpCode op = op_instruction_to_opcode(instruction);
    UNSIGNED_LONGS_EQUAL(0xF, op);
}