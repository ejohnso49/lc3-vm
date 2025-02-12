#include "device.h"
#include "memory.h"
#include <stdbool.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

static bool prv_check_stdin(void) {
    fd_set readfds = {0};
    struct timeval timeout = {0};
    int nfds = 1;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    int ready = select(nfds, &readfds, NULL, NULL, &timeout);
    if (ready < 0) {
        printf("Error checking stdin[%d]\n", ready);
        return false;
    } else if (ready == 0) {
        return false;
    }

    return FD_ISSET(STDIN_FILENO, &readfds);
}

void keyboard_update_data(uint16_t data) {
    memory_write(DEVICE_KBDR, data);
}

void keyboard_check_status(void) {
    if (prv_check_stdin()) {
        int c = getchar();
        c &= (~0xFF00);

        memory[DEVICE_KBSR] = DEVICE_KBSR_STATUS_MASK;
        keyboard_update_data((uint16_t)c);
    } else {
        memory[DEVICE_KBSR] = 0;
    }
}

void machine_control_halt(void) {
    memory_write(DEVICE_MCR, 0x8000);
}
