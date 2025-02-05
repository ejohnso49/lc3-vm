#include "opcodes.h"
#include "memory.h"
#include "registers.h"

eOpCode op_instruction_to_opcode(uint16_t instruction) {
    return (eOpCode)(instruction >> 12);
}
