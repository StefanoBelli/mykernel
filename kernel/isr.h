#ifndef MYKERNEL_ISR_H
#define MYKERNEL_ISR_H

#include <misc/types.h>
#include <misc/gcc.h>

typedef struct {
    mykt_uint_32 gs;
    mykt_uint_32 fs;
    mykt_uint_32 es;
    mykt_uint_32 ds;
    mykt_uint_32 edi;
    mykt_uint_32 esi;
    mykt_uint_32 ebp;
    mykt_uint_32 esp;
    mykt_uint_32 ebx;
    mykt_uint_32 edx;
    mykt_uint_32 ecx;
    mykt_uint_32 eax;
    mykt_uint_32 intno;
    mykt_uint_32 ec;
    mykt_uint_32 eip;
    mykt_uint_32 cs;
    mykt_uint_32 efl;
    mykt_uint_32 useresp;
    mykt_uint_32 ss;
} interrupt_frame;

__mykapi void isr_set_int_gates();
void isr_log_interrupt_frame(interrupt_frame);

#endif
