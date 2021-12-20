#include "ksleep.h"

static mykt_uint_32 pit_ticks;

__mykapi void __ksleep_tick() {
	++pit_ticks;
}

__mykapi void dont_optimize omit_frame_pointer ksleep(mykt_uint_32 ms) {
	mykt_uint_32 start_pit_tick = pit_ticks;
	while(pit_ticks - start_pit_tick < ms) {}
}
