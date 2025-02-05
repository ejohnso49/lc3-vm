#include <stdio.h>
#include "registers.h"
#include "memory.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    for (int i = 1; i < argc; i++) {
        if (!read_image(argv[i])) {
            printf("Failed to load image: %s\n", argv[i]);
            exit(1);
        }
    }

    memory_init();
    registers_init();

    printf("Starting LC3 Virtual Machine\n");
    processor_run();

    return 0;
}
