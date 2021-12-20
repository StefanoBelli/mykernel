#include "ksleep.h"

static int pit_ticks;

__mykapi void __ksleep_tick() {
	++pit_ticks;
}

__mykapi void dont_optimize omit_frame_pointer ksleep(mykt_int_32 ms) {
	mykt_int_32 start_pit_tick = pit_ticks;
	while(pit_ticks - start_pit_tick < ms) {}
}
