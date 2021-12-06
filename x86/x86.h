#ifndef MYKERNEL_X86_H
#define MYKERNEL_X86_H

#define x86_cli() \
	__asm__ __volatile__ ("cli;")

#define x86_hlt() \
	__asm__ __volatile__ ("hlt;")

#define x86_sti() \
	__asm__ __volatile__ ("sti;")

#endif
