#ifndef MYKERNEL_IRQS_H
#define MYKERNEL_IRQS_H

#include "isr.h"

// IRQs with numbering are placeholders without implementation

void irq_timer(interrupt_frame);
void irq_keyboard(interrupt_frame);
void irq_reserved_slavepic(interrupt_frame);
void irq_3(interrupt_frame);
void irq_4(interrupt_frame);
void irq_5(interrupt_frame);
void irq_6(interrupt_frame);
void irq_7(interrupt_frame);
void irq_8(interrupt_frame);
void irq_9(interrupt_frame);
void irq_10(interrupt_frame);
void irq_11(interrupt_frame);
void irq_12(interrupt_frame);
void irq_13(interrupt_frame);
void irq_14(interrupt_frame);
void irq_15(interrupt_frame);

#endif
