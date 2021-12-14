#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#ifdef __i386__
#include <x86/types.h>
#endif

typedef struct {
	mykt_uint_16 x;
	mykt_uint_16 y;
} mykt_pair_uint_16;

#endif
