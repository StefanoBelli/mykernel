#ifndef MYKERNEL_ISR_H
#define MYKERNEL_ISR_H

#include <misc/types.h>
#include <misc/gcc.h>

typedef enum {
	IRQ_TIMER,
	IRQ_KEYBOARD,
	IRQ_PIC2,
	IRQ_COM2_4,
	IRQ_COM1_3,
	IRQ_LPT2,
	IRQ_FDC,
	IRQ_LPT1_3,
	IRQ_RTC,
	IRQ_9,
	IRQ_10,
	IRQ_11,
	IRQ_MOUSE,
	IRQ_MATH_COPROC,
	IRQ_PRIMARY_IDE_CH,
	IRQ_SECONDARY_IDE_CH
} irqn;

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

typedef void (*isrh_fp)(interrupt_frame);

__mykapi void isr_set_int_gates();
void isr_log_interrupt_frame(interrupt_frame);
__mykapi void isr_register_irq_handler(irqn, isrh_fp);

#endif
