#include "device.h"
#include "memory.h"

void keyboard_update_data(uint16_t data) {
    memory_write(DEVICE_KBDR, data);
}

void machine_control_halt(void) {
    memory_write(DEVICE_MCR, 0x8000);
}
