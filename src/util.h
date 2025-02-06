#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

inline int16_t sign_extend_16(int16_t value, uint8_t bits) {
    if ((value >> (bits - 1)) & 1) {
        value |= (0xFFFF << bits);
    }

    return value;
}

inline uint16_t zero_extend_16(uint16_t value, uint8_t bits) {
    return value | (0xFFFFUL >> bits);
}

#ifdef __cplusplus
}
#endif
