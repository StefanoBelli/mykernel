#ifndef MYKERNEL_X86_H
#define MYKERNEL_X86_H

#include <misc/gcc.h>
#include "types.h"

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

__mykapi void x86_outb(word port, byte data);
__mykapi byte x86_inb(word port);

#endif