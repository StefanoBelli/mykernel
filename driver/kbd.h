#ifndef MYKERNEL_KBD_DRIVER_H
#define MYKERNEL_KBD_DRIVER_H

#include <misc/gcc.h>
#include <misc/types.h>

typedef struct {
	union {
		mykt_int_8 ch;
		
		enum {
			FN_1,
			FN_2,
			FN_3,
			FN_4,
			FN_5,
			FN_6,
			FN_7,
			FN_8,
			FN_9,
			FN_10,
			FN_11,
			FN_12
		} fn;
		
		enum {
			LOCK_SCROLL,
			LOCK_NUM,
			LOCK_CAPS
		} lock;
		
		enum {
			SHIFT_LEFT,
			SHIFT_RIGHT
		} shift;
		
		enum {
			CTRL_LEFT
		} ctrl;
		
		enum {
			ALT_LEFT
		} alt;
	} key;

	enum {
		KEY_TYPE_CHAR,
		KEY_TYPE_ARROW,
		KEY_TYPE_FN,
		KEY_TYPE_LOCK,
		KEY_TYPE_SHIFT,
		KEY_TYPE_CTRL,
		KEY_TYPE_ALT
	} key_type;

	enum {
		KEY_PRESS_PRESSED,
		KEY_PRESS_RELEASED
	} key_press;
} kbd_key;

typedef void (*__mykapi kbd_evt_fp)(kbd_key);

__mykapi mykt_int_32 kbd_init();
__mykapi void kbd_set_handler(kbd_evt_fp);
__mykapi void __kbd_evt();

#endif
