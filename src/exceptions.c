#include "exceptions.h"
#include <stdio.h>
#include "registers.h"

void exception(void) {
    printf("An exception occurred at %x\n", registers[Register_PC] - 1);
    exit(10);
}