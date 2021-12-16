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
	__asm__ __volatile__ ("lidtl (%0);" :: "r"(i));

__mykapi void x86_outb(mykt_int_16 port, mykt_int_8 data);
__mykapi mykt_int_8 x86_inb(mykt_int_16 port);

#endif
