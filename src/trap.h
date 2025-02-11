#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum TrapVector {
    TRAP_GETC = 0x20,
    TRAP_OUT = 0x21,
    TRAP_PUTS = 0x22,
    TRAP_IN = 0x23,
    TRAP_PUTSP = 0x24,
    TRAP_HALT = 0x25,
} eTrapVector;

void trap_getc(void);
void trap_out(void);
void trap_puts(void);
void trap_in(void);
void trap_putsp(void);
void trap_halt(void);

#ifdef __cplusplus
}
#endif
