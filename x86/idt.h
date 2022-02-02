#ifndef X86_IDT_H
#define X86_IDT_H

#include <misc/gcc.h>
#include "types.h"

#define IDT_EXCP 0xaf
#define IDT_IRQ 0xae

typedef void(*int_gate_fp)();

__mykapi void x86_idt_install();
__mykapi void x86_set_int_gate(ubyte m, ubyte i, int_gate_fp g);

#endif
