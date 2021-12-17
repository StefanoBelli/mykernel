#ifndef X86_IDT_H
#define X86_IDT_H

#include "types.h"

typedef void(*int_gate_fp)(void*);

void x86_idt_install();
void x86_set_trap_gate(mykt_uint_8 i, int_gate_fp g);
void x86_set_int_gate(mykt_uint_8 i, int_gate_fp g);

#endif
