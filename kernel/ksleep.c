#include "isr.h"
#include "ksleep.h"

static mykt_uint_32 pit_ticks;

static void __ksleep_tick(unused interrupt_frame f) {
	++pit_ticks;
}

__mykapi void dont_optimize omit_frame_pointer ksleep(mykt_uint_32 ms) {
	mykt_uint_32 start_pit_tick = pit_ticks;
	while(pit_ticks - start_pit_tick < ms) {}
}

__mykapi void ksleep_init() {
	isr_register_irq_handler(IRQ_TIMER, __ksleep_tick);
}
