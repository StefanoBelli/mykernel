#include <misc/gcc.h>
#include "irqs.h"
#include "ksleep.h"

void irq_timer(unused interrupt_frame frame) {
	__ksleep_tick();
}

void irq_keyboard(unused interrupt_frame frame) {

}

void irq_reserved_slavepic(unused interrupt_frame frame) {

}
