#include "CppUTestExt/MockSupport.h"

extern "C" {
    void exception(void) {
        mock().actualCall("exception");
    }
}
