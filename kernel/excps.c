#include "excps.h"

void excp_debug(interrupt_frame frame) {
	isr_log_interrupt_frame(frame);
}

void excp_breakpoint(interrupt_frame frame) {
	isr_log_interrupt_frame(frame);
}