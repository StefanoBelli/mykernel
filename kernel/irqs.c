#include <misc/gcc.h>
#include <driver/kbd.h>
#include "irqs.h"
#include "ksleep.h"

void irq_timer(unused interrupt_frame frame) {
	__ksleep_tick();
}

void dont_optimize omit_frame_pointer irq_keyboard(unused interrupt_frame frame) {
	__kbd_evt();
}

void irq_reserved_slavepic(unused interrupt_frame frame) {

}
