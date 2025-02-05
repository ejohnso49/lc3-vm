#include "CppUTest/TestHarness.h"
#include "opcodes.h"
#include "registers.h"

TEST_GROUP(OpCodes) {
};

TEST(OpCodes, InstructionToOpCode) {
    uint16_t instruction = 0xF200;
    eOpCode op = OPCODES_FROM_INSTRUCTION(instruction);
    UNSIGNED_LONGS_EQUAL(0xF, op);
}
