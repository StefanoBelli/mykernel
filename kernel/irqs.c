#include <x86/idt.h>
#include <misc/gcc.h>
#include "irqs.h"

#define int_handler static interrupt void

int_handler irq0(void* a){
}

int_handler irq1(void* a){
}

int_handler irq2(void* a){
}

int_handler irq3(void* a){
}

int_handler irq4(void* a){
}

int_handler irq5(void* a){
}

int_handler irq6(void* a){
}

int_handler irq7(void* a){
}

int_handler irq8(void* a){
}

int_handler irq9(void* a){
}

int_handler irq10(void* a){
}

int_handler irq11(void* a){
}

int_handler irq12(void* a){
}

int_handler irq13(void* a){
}

int_handler irq14(void* a){
}

int_handler irq15(void* a){
}

void irq_gates_install() {
	x86_set_int_gate(0x20, irq0);
	x86_set_int_gate(0x21, irq1);
	x86_set_int_gate(0x22, irq2);
	x86_set_int_gate(0x23, irq3);
	x86_set_int_gate(0x24, irq4);
	x86_set_int_gate(0x25, irq5);
	x86_set_int_gate(0x26, irq6);
	x86_set_int_gate(0x27, irq7);
	x86_set_int_gate(0x28, irq8);
	x86_set_int_gate(0x29, irq9);
	x86_set_int_gate(0x2a, irq10);
	x86_set_int_gate(0x2b, irq11);
	x86_set_int_gate(0x2c, irq12);
	x86_set_int_gate(0x2d, irq13);
	x86_set_int_gate(0x2e, irq14);
	x86_set_int_gate(0x2f, irq15);
}

