#include <x86/x86.h>
#include "kbd.h"

#define RS -19 //right shift
#define LS -18 //left shift
#define LC -17 //left ctrl
#define LA -16 //left alt
#define CL -15 //capslock
#define NL -14 //numlock
#define SL -13 //scrollock
#define FC -12 //f12
#define FB -11 //f11
#define FA -10 //f10
#define F9 -9
#define F8 -8
#define F7 -7
#define F6 -6
#define F5 -5
#define F4 -4
#define F3 -3
#define F2 -2
#define F1 -1

static mykt_int_8 ss1[89] = {
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u',
	'i', 'o', 'p', '[', ']', '\n', LC, 'a', 's', 'd', 'f', 'g', 
	'h', 'j', 'k', 'l', ';', '\'', '`', LS, '\\', 'z', 'x', 'c', 
	'v', 'b', 'n', 'm', ',', '.', '/', RS, '*', LA, ' ', CL, F1, 
	F2, F3, F4, F5, F6, F7, F8, F9, FA, NL, SL, '7', '8', '9', 
	'-', '4', '5', '6', '+', '1', '2', '3', '0', '.', 0, 0, 0, 
	FB, FC
};

static kbd_evt_fp handler;

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

	// reset device and check for kbd ACK
	x86_outb(0x60, (mykt_int_8) 0xff);
	mykt_int_8 reset_ack = x86_inb(0x60);
	mykt_int_8 self_test_pass = x86_inb(0x60);
	if(reset_ack != (mykt_int_8) 0xfa || 
		self_test_pass != (mykt_int_8) 0xaa) {
		return -3;
	}

	// set scan code set 1
	x86_outb(0x60, (mykt_int_8) 0xf0);
	if(x86_inb(0x60) != (mykt_int_8) 0xfa) {
		return -2;
	}

	x86_outb(0x60, (mykt_int_8) 1);
	if(x86_inb(0x60) != (mykt_int_8) 0xfa) {
		return -1;
	}
	
	// enable interrupts
	x86_outb(0x64, (mykt_int_8) 0x60);
	x86_outb(0x60, (mykt_int_8) (ccb | 1));

	// enable device
	x86_outb(0x64, (mykt_int_8) 0xae);

	return 0;
}

__mykapi void kbd_set_handler(kbd_evt_fp h) {
	handler = h;
}

__mykapi void __kbd_evt() {
	mykt_int_8 ss = x86_inb(0x60);
	if(handler == 0) {
		return;
	}
	

}
