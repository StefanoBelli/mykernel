#include <driver/kbd.h>
#include "kkbdin.h"

__mykapi mykt_int_32 kkbdin_init() {
	return kbd_init();
}

__mykapi mykt_int_32 kkbdin_read(mykt_int_8 *dest, mykt_int_32 size) {
	return 0;
}

