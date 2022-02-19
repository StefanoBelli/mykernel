#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#ifdef __i386__
#include "x86/types.h"
#endif

typedef struct {
	uint16_t x;
	uint16_t y;
} pair_uword;

#endif
