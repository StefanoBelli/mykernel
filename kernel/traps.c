#include <x86/idt.h>
#include <misc/gcc.h>
#include "traps.h"

#define int_handler static interrupt void

int_handler divide_by_zero(void* a){ // 0
}

int_handler debug(void* a){ // 1
}

int_handler nmi(void* a){ // 2
}

int_handler breakpoint(void* a){ // 3
}

int_handler overflow(void* a){ // 4
}

int_handler bound_range_exceeded(void* a){ // 5
}

int_handler invalid_opcode(void* a){ // 6
}

int_handler device_not_available(void* a){ // 7
}

int_handler double_fault(void* a){ // 8
}

int_handler coprocessor_segment_overrun(void* a){ // 9
}

int_handler invalid_tss(void* a){ // 10
}

int_handler segment_not_present(void* a){ // 11
}

int_handler stack_segment_fault(void* a){ // 12
}

int_handler general_protection_fault(void* a){ // 13
}

int_handler page_fault(void* a){ // 14
}

int_handler x87_floating_point_exception(void* a){ // 16
}

int_handler alignment_check(void* a){ // 17
}
	
int_handler machine_check(void* a){ // 18
}

int_handler reserved(void* a){ // 15, 19..32
	__asm__("nop;");
}

void trap_gates_install() {
	x86_set_trap_gate(0, divide_by_zero);
	x86_set_trap_gate(1, debug);
	x86_set_trap_gate(2, nmi);
	x86_set_trap_gate(3, breakpoint);
	x86_set_trap_gate(4, overflow);
	x86_set_trap_gate(5, bound_range_exceeded);
	x86_set_trap_gate(6, invalid_opcode);
	x86_set_trap_gate(7, device_not_available);
	x86_set_trap_gate(8, double_fault);
	x86_set_trap_gate(9, coprocessor_segment_overrun);
	x86_set_trap_gate(10, invalid_tss);
	x86_set_trap_gate(11, segment_not_present);
	x86_set_trap_gate(12, stack_segment_fault);
	x86_set_trap_gate(13, general_protection_fault);
	x86_set_trap_gate(14, page_fault);
	x86_set_trap_gate(16, x87_floating_point_exception);
	x86_set_trap_gate(17, alignment_check);
	x86_set_trap_gate(18, machine_check);
	
	x86_set_trap_gate(15, reserved);
	for(mykt_uint_8 i = 19; i < 32; ++i) {
		x86_set_trap_gate(i, reserved);
	}
}

