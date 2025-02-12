#include "file.h"
#include "memory.h"
#include "util.h"
#include <stdint.h>

static int prv_file_read_image(FILE *file) {
    // First get .ORIGIN location
    uint16_t origin = 0;

    int result = fread(&origin, sizeof(origin), 1, file);
    if (result != 1) {
        if (ferror(file)) {
            printf("Error reading file \n");
            return -1;
        } else if (feof(file)) {
            printf("Error, reached EOF before reading origin\n");
            return -1;
        } else {
            printf("An unknown error occurred reading image\n");
            return -1;
        }
    }
    origin = swap_16(origin);

    uint16_t max_file_size = MEMORY_SIZE - origin;
    result = fread(&memory[origin], sizeof(uint16_t), max_file_size, file);
    if (ferror(file)) {
        printf("Error reading data from file\n");
        return -1;
    }

    // Swap image bytes after reading into memory
    for (size_t i = 0; i < max_file_size; i++) {
        memory[i + origin] = swap_16(memory[i + origin]);
    }

    return 0;
}

int file_read_image(const char *image_path) {
    FILE *image_file = fopen(image_path, "rb");
    if (image_file == NULL) {
        printf("Could not open image file at %s\n", image_path);
        return -1;
    }

    int result = prv_file_read_image(image_file);
    fclose(image_file);

    return result;
}
