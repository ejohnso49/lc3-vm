#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SIGN_EXTEND16(value, bits) \
    do { \
        if ((value >> (bits - 1)) & 1) { \
            value |= (0xFFFF << bits); \
        } \
    } while (0);

#ifdef __cplusplus
}
#endif
