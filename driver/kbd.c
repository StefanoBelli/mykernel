#include <x86/x86.h>
#include "kbd.h"

#define AD 25 //arrow down
#define AR 24 //arrow right
#define AL 23 //arrow left
#define AU 22 //arrow up
#define RS 21 //right shift
#define LS 20 //left shift
#define RC 19 //right ctrl
#define LC 18 //left ctrl
#define RA 17 //right alt
#define LA 16 //left alt
#define CL 15 //capslock
#define NL 14 //numlock
#define SL 13 //scrollock
#define FC 12 //f12
#define FB 11 //f11
#define FA 10 //f10
#define F9 9
#define F8 8
#define F7 7
#define F6 6
#define F5 5
#define F4 4
#define F3 3
#define F2 2
#define F1 1

static const mykt_int_8 ss1[89] = {
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u',
	'i', 'o', 'p', '[', ']', '\n', LC, 'a', 's', 'd', 'f', 'g', 
	'h', 'j', 'k', 'l', ';', '\'', '`', LS, '\\', 'z', 'x', 'c', 
	'v', 'b', 'n', 'm', ',', '.', '/', RS, '*', LA, ' ', CL, F1, 
	F2, F3, F4, F5, F6, F7, F8, F9, FA, NL, SL, '7', '8', '9', 
	'-', '4', '5', '6', '+', '1', '2', '3', '0', '.', 0, 0, 0, 
	FB, FC
};

static const mykt_int_8 e0_ss1[81] = {
	[0x1c] = '\n',
	[0x1d] = RC,
	[0x35] = '/',
	[0x38] = RA,
	[0x48] = AU,
	[0x4b] = AL,
	[0x4d] = AR,
	[0x50] = AD,
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

	mykt_int_8 ch = 0;
	kbd_key k = 0;
	
	if(ss == (mykt_int_8) 0xe0) {
		mykt_int_8 m = x86_inb(0x60);
		if(m >= (mykt_int_8) 0x1c && m <= (mykt_int_8) 0xd0) {
			mykt_int_8 idx = m;
			if(m > 0x50) {
				k = 0x800;
				idx -= 128;
			}

			ch = e0_ss1[(mykt_uint_8) idx];
		}
	} else if(ss >= (mykt_int_8) 1 && ss <= (mykt_int_8) 0xd8) {
		mykt_int_8 idx = ss;
		if(ss > 0x58) {
			k = 0x800;
			idx -= 128;
		}

		ch = ss1[(mykt_uint_8) idx];
	}
	
	k = (kbd_key) (k | ch);

	if(ch >= F1 && ch <= FC) {
		k = (kbd_key) (k | (KEY_TYPE_FN << 8));
	} else if(ch >= SL && ch <= CL) {
		k = (kbd_key) (k | (KEY_TYPE_LOCK << 8));
	} else if(ch >= LA && ch <= RA) {
		k = (kbd_key) (k | (KEY_TYPE_ALT << 8));
	} else if(ch >= LC && ch <= RC) {
		k = (kbd_key) (k | (KEY_TYPE_CTRL << 8));
	} else if(ch >= LS && ch <= RS) {
		k = (kbd_key) (k | (KEY_TYPE_SHIFT << 8));
	} else if(ch >= AU && ch <= AD) {
		k = (kbd_key) (k | (KEY_TYPE_ARROW << 8));
	} else {
		k = (kbd_key) (k | (KEY_TYPE_CHAR << 8));
	}
	
	handler(k);
}

