#include <x86/x86.h>
#include "kbd.h"

__mykapi mykt_int_32 kbd_init() {
	// disable devices
	x86_outb(0x64, (mykt_int_8) 0xad);
	
	// flush output buffers
	x86_inb(0x60);

	// disable interrupt 0 and 1
	// and translation
	x86_outb(0x64, (mykt_int_8) 0x20);
	mykt_int_8 ccb = (mykt_int_8) (x86_inb(0x60) & 0xbc);
	x86_outb(0x64, 0x60);
	x86_outb(0x60, ccb);

	// enable device
	x86_outb(0x64, (mykt_int_8) 0xae);

	// reset device and check for kbd ACK
	x86_outb(0x60, (mykt_int_8) 0xff);
	mykt_int_8 reset_ack = x86_inb(0x60);
	mykt_int_8 self_test_pass = x86_inb(0x60);
	if(reset_ack != (mykt_int_8) 0xfa || self_test_pass != (mykt_int_8) 0xaa) {
		return -3;
	}
	
	// enable interrupts
	x86_outb(0x64, (mykt_int_8) 0x60);
	x86_outb(0x60, (mykt_int_8) (ccb | 1));

	// set scan code set 1
	x86_outb(0x60, (mykt_int_8) 0xf0);
	if(x86_inb(0x60) != (mykt_int_8) 0xfa) {
		return -2;
	}

	x86_outb(0x60, (mykt_int_8) 1);
	if(x86_inb(0x60) != (mykt_int_8) 0xfa) {
		return -1;
	}

	return 0;
}
