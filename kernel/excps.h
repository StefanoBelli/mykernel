#ifndef MYKERNEL_EXCPS_H
#define MYKERNEL_EXCPS_H

#include "isr.h"

// placeholders for future usages

void excp_divide_by_zero(interrupt_frame);
void excp_debug(interrupt_frame);
void excp_nmi(interrupt_frame);
void excp_breakpoint(interrupt_frame);
void excp_overflow(interrupt_frame);
void excp_bound_range_exceeded(interrupt_frame);
void excp_invalid_opcode(interrupt_frame);
void excp_device_not_available(interrupt_frame);
void excp_double_fault(interrupt_frame);
void excp_coprocessor_segment_overrun(interrupt_frame);
void excp_invalid_tss(interrupt_frame);
void excp_segment_not_present(interrupt_frame);
void excp_stack_segment_fault(interrupt_frame);
void excp_general_protection_fault(interrupt_frame);
void excp_page_fault(interrupt_frame);
void excp_x87_floating_point(interrupt_frame);
void excp_alignment_check(interrupt_frame);
void excp_machine_check(interrupt_frame);
void excp_reserved(interrupt_frame);

#endif
