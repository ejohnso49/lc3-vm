#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define DEVICE_KBSR (0xFE00)
#define DEVICE_KBDR (0xFE02)
#define DEVICE_DSR (0xFE04)
#define DEVICE_DDR (0xFE06)
#define DEVICE_MCR (0xFFFE)
#define DEVICE_MCR_CLK_ENABLE_MASK (1 << 15)

void keyboard_update_data(uint16_t data);
void machine_control_halt(void);

#ifdef __cplusplus
}
#endif
