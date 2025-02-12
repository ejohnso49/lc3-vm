#include "registers.h"
#include "memory.h"
#include "processor.h"
#include "file.h"
#include "system.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    signal(SIGINT, handle_interrupt);
    disable_input_buffering();

    memory_init();
    registers_init();
    registers_pc_init();

    if (file_read_image(argv[1])) {
        printf("Failed to load image: %s\n", argv[1]);
        exit(1);
    }

    printf("Starting LC3 Virtual Machine\n");
    processor_run();
    restore_input_buffering();

    return 0;
}
