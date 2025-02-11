#include "trap.h"
#include <stdio.h>
#include <stdint.h>
#include "registers.h"

#define TRAP_IN_PROMPT ("Input a character> ")

void trap_getc(void) {
    // Let's assume for now that we do not need to modify the KBSR
    // We'll assume that KBSR[15] is set to 0 when KBDR is read
    int c = getchar();
    if (c == EOF) {
        printf("Hit end of file reading from stdin\n");
        exit(1);
    }

    // Clear the upper byte
    c &= (~0xFF00);

    // Update the KBDR for consistency
    keyboard_update_data((uint16_t)c);

    // Copy the char into R0
    registers[Register_R0] = (uint16_t)c;
    registers_update_cond(Register_R0);
}

void trap_out(void) {
    char c = (char)registers[Register_R0];
    int result = putchar(c);
    if (result == EOF) {
        printf("Hit end of file writing to stdout\n");
        exit(1);
    }
}

void trap_puts(void) {
    char *str = registers[Register_R0];
    char current = (char)memory_read((uint16_t)str);
    while(current != '\0') {
        int result = putchar(current);
        if (result == EOF) {
            printf("Hit end of file writing to stdout\n");
            exit(1);
        }

        str++;
        current = (char)memory_read((uint16_t)str);
    }
}

void trap_in(void) {
    printf("%s", TRAP_IN_PROMPT);
    trap_getc();
    trap_out();
}

void trap_putsp(void) {
    char *str = registers[Register_R0];
    uint16_t current = memory_read((uint16_t)str);

    while (current != 0x0000) {
        char lower = current & 0xFF;
        char upper = (current &0xFF00) >> 8;

        int result = putchar(lower);
        if (result == EOF) {
            printf("Hit end of file writing to stdout\n");
            exit(1);
        }

        if (upper != '\0') {
            result = putchar(upper);
            if (result == EOF) {
                printf("Hit end of file writing to stdout\n");
                exit(1);
            }
        } else {
            // Hit upper bytes as 0x00, break early
            break;
        }

        str++;
        current = memory_read((uint16_t)str);
    }

}

void trap_halt(void) {
    machine_control_halt();
    printf("Halting\n");
#if !defined(CONFIG_TEST)
    exit(1);
#endif
}
