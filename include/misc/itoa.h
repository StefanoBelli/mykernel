#ifndef STRING_MYKERNEL_H
#define STRING_MYKERNEL_H

#include "types.h"
#include "gcc.h"

__mykapi int8_t* ltoa(int32_t value, int8_t* buf);
__mykapi int8_t* ultoa(uint32_t value, int8_t* buf, uint8_t base);
__mykapi int8_t* ustoa(uint16_t value, int8_t* buf, uint8_t base);
__mykapi int8_t* ubtoa(uint8_t value, int8_t* buf, uint8_t base);

#endif
