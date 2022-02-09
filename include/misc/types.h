#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#ifdef __i386__
#include <x86/types.h>
#endif

typedef struct {
	uword x;
	uword y;
} pair_uword;

#endif
