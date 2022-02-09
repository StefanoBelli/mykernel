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

typedef enum {
	EXCP_DIVIDE_BY_ZERO,
	EXCP_DEBUG,
	EXCP_NMI,
	EXCP_BREAKPOINT,
	EXCP_OVERFLOW,
	EXCP_BOUND_RANGE_EXCEEDED,
	EXCP_INVALID_OPCODE,
	EXCP_DEVICE_NOT_AVAILABLE,
	EXCP_DOUBLE_FAULT,
	EXCP_COPROCESSOR_SEGMENT_OVERRUN,
	EXCP_INVALID_TSS,
	EXCP_SEGMENT_NOT_PRESENT,
	EXCP_STACK_SEGMENT_FAULT,
	EXCP_GENERAL_PROTECTION_FAULT,
	EXCP_PAGE_FAULT,
	EXCP_X87_FLOATING_POINT,
	EXCP_ALIGNMENT_CHECK,
	EXCP_MACHINE_CHECK,
	EXCP_RESERVED
} excpn;

typedef struct {
	udword gs;
	udword fs;
	udword es;
	udword ds;
	udword edi;
	udword esi;
	udword ebp;
	udword esp;
	udword ebx;
	udword edx;
	udword ecx;
	udword eax;
	udword intno;
	udword ec;
	udword eip;
	udword cs;
	udword efl;
	udword useresp;
	udword ss;
} interrupt_frame;

typedef void (*isrh_fp)(interrupt_frame);

__mykapi void isr_set_int_gates();
void isr_log_interrupt_frame(interrupt_frame);
__mykapi void isr_register_irq_handler(irqn, isrh_fp);
__mykapi void isr_register_excp_handler(excpn, isrh_fp);


#endif
