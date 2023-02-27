#ifndef MYKERNEL_X86_H
#define MYKERNEL_X86_H

#include <misc/gcc.h>
#include "types.h"

#define x86_int3() \
	__asm__ __volatile__ ("int $3;")

#define x86_cli() \
	__asm__ __volatile__ ("cli;")

#define x86_hlt() \
	__asm__ __volatile__ ("hlt;")

#define x86_sti() \
	__asm__ __volatile__ ("sti;")

#define x86_lidt(i) \
	__asm__ __volatile__ ("lidtl (%0);" :: "r"(i))

#define x86_invlpg(va) \
	__asm__ __volatile__ ("invlpg (%0);" :: "r"(va) : "memory")

__mykapi void x86_outb(int16_t port, int8_t data);
__mykapi int8_t x86_inb(int16_t port);

#endif
