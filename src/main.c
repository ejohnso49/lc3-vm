#include <stdio.h>
#include "registers.h"
#include "memory.h"

int main() {
    memory_init();
    registers_init();

    printf("Starting LC3 Virtual Machine\n");
    return 0;
}
