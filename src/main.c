#include <stdio.h>
#include "registers.h"
#include "memory.h"
#include "file.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    if (file_read_image(argv[1])) {
        printf("Failed to load image: %s\n", argv[i]);
        exit(1);
    }

    memory_init();
    registers_init();
    registers_pc_init();

    printf("Starting LC3 Virtual Machine\n");
    processor_run();

    return 0;
}
