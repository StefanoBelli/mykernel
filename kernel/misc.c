#include <x86/x86.h>
#include <kernel/kprintf.h>
#include <kernel/misc.h>
#include <kernel/isr.h>

static uint32_t pit_ticks;

static void __ksleep_tick(unused interrupt_frame f) {
	++pit_ticks;
}

__mykapi void dont_optimize omit_frame_pointer ksleep(uint32_t ms) {
	uint32_t start_pit_tick = pit_ticks;
	while(pit_ticks - start_pit_tick < ms) {}
}

__mykapi void ksleep_init() {
	isr_register_irq_handler(IRQ_TIMER, __ksleep_tick);
}

__mykapi void system_halt() {
	kprintf("kernel: system halted\n");
	x86_cli();
	x86_hlt();
}

__mykapi void kernel_bug() {
	kprintf("kernel: kernel bug -- getting trapped, goodbye\n");
	x86_int3();
}
