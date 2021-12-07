#ifndef MYKERNEL_X86_H
#define MYKERNEL_X86_H

#include "types.h"

#define x86_cli() \
	__asm__ __volatile__ ("cli;")

#define x86_hlt() \
	__asm__ __volatile__ ("hlt;")

#define x86_sti() \
	__asm__ __volatile__ ("sti;")

void x86_outb(mykt_int_16 port, mykt_int_8 data);
mykt_int_8 x86_inb(mykt_int_16 port);

#endif
