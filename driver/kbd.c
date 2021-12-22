#include <x86/x86.h>
#include "kbd.h"

#define AD KBD_KEY_PAYLD_ARROW_DOWN //arrow down
#define AR KBD_KEY_PAYLD_ARROW_RIGHT //arrow right
#define AL KBD_KEY_PAYLD_ARROW_LEFT //arrow left
#define AU KBD_KEY_PAYLD_ARROW_UP //arrow up
#define RS KBD_KEY_PAYLD_RIGHT_SHIFT //right shift
#define LS KBD_KEY_PAYLD_LEFT_SHIFT //left shift
#define RC KBD_KEY_PAYLD_RIGHT_CTRL //right ctrl
#define LC KBD_KEY_PAYLD_LEFT_CTRL //left ctrl
#define RA KBD_KEY_PAYLD_RIGHT_ALT //right alt
#define LA KBD_KEY_PAYLD_LEFT_ALT //left alt
#define CL KBD_KEY_PAYLD_CAPS_LOCK //capslock
#define NL KBD_KEY_PAYLD_NUM_LOCK //numlock
#define SL KBD_KEY_PAYLD_SCROLL_LOCK //scrollock
#define FC KBD_KEY_PAYLD_F12 //f12
#define FB KBD_KEY_PAYLD_F11 //f11
#define FA KBD_KEY_PAYLD_F10 //f10
#define F9 KBD_KEY_PAYLD_F9
#define F8 KBD_KEY_PAYLD_F8
#define F7 KBD_KEY_PAYLD_F7
#define F6 KBD_KEY_PAYLD_F6
#define F5 KBD_KEY_PAYLD_F5
#define F4 KBD_KEY_PAYLD_F4
#define F3 KBD_KEY_PAYLD_F3
#define F2 KBD_KEY_PAYLD_F2
#define F1 KBD_KEY_PAYLD_F1

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
	
	// enable interrupt 0
	// keep interrupt 1 and translation disabled
	x86_outb(0x64, (mykt_int_8) 0x60);
	x86_outb(0x60, (mykt_int_8) (ccb | 1));

	// enable device
	x86_outb(0x64, (mykt_int_8) 0xae);

	return 0;
}

__mykapi void kbd_set_handler(kbd_evt_fp h) {
	handler = h;
}

__mykapi void dont_optimize omit_frame_pointer __kbd_evt() {
	static mykt_uint_8 expects_sb = 0;
	mykt_uint_8 fb = (mykt_uint_8) x86_inb(0x60);
	mykt_uint_8 sb;

	if(!expects_sb && fb == 0xe0) {
		expects_sb = 1;
		return;
	} else if(expects_sb) {
		sb = (mykt_uint_8) x86_inb(0x60);
	}

	if(handler == 0) {
		return;
	}

	const mykt_int_8* ssp = 0;
	mykt_uint_8 rel = 0;
	mykt_uint_8 idx = 0;
	kbd_key k = 0;

	if(expects_sb) {
		expects_sb = 0;
		if(sb >= 0x1c && sb <= 0xd0) {
			idx = sb;
			ssp = e0_ss1;
			rel = sb > 0x50;
		} else {
			return;
		}
	} else if(fb >= 1 && fb <= 0xd8) {
		idx = fb;
		ssp = ss1;
		rel = fb > 0x58;
	} else {
		return;
	}

	if(rel) {
		k = 0x800;
		idx -= 128;
	}

	mykt_int_8 ch = ssp[idx];
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

