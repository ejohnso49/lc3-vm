#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "registers.h"
#include "opcodes.h"
#include "exceptions.h"

TEST_GROUP(OpRes) {
    void teardown(void) {
        mock().clear();
    }
};

TEST(OpRes, Res) {
    uint16_t instruction = OP_RES << 12;

    mock().expectOneCall("exception");
    op_res(instruction);

    mock().checkExpectations();
}
