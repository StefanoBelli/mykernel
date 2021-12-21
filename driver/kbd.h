#ifndef MYKERNEL_KBD_DRIVER_H
#define MYKERNEL_KBD_DRIVER_H

#include <misc/gcc.h>
#include <misc/types.h>

typedef mykt_uint_16 kbd_key;
typedef mykt_uint_8 kbd_key_payld_ch;

typedef enum {
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
} kbd_key_payld_fn;

typedef enum {
	ARROW_UP,
	ARROW_LEFT,
	ARROW_RIGHT,
	ARROW_DOWN
} kbd_key_payld_arrow;

typedef enum {
	LOCK_SCROLL,
	LOCK_NUM,
	LOCK_CAPS
} kbd_key_payld_lock;

typedef enum {
	SHIFT_LEFT,
	SHIFT_RIGHT
} kbd_key_payld_shift;

typedef enum {
	CTRL_LEFT,
	CTRL_RIGHT
} kbd_key_payld_ctrl;

typedef enum {
	ALT_LEFT,
	ALT_RIGHT
} kbd_key_payld_alt;

typedef enum {
	KEY_TYPE_CHAR,
	KEY_TYPE_ARROW,
	KEY_TYPE_FN,
	KEY_TYPE_LOCK,
	KEY_TYPE_SHIFT,
	KEY_TYPE_CTRL,
	KEY_TYPE_ALT
} kbd_key_type;

typedef enum {
	KEY_PRESS_PRESSED,
	KEY_PRESS_RELEASED
} kbd_key_press;

#define kbd_key_get_keypress(k) (k & 0x1800) >> 11
#define kbd_key_get_type(k) (k & 0x700) >> 8
#define kbd_key_get_payld(k) (k & 0xff)

typedef void (*__mykapi kbd_evt_fp)(kbd_key);

__mykapi mykt_int_32 kbd_init();
__mykapi void kbd_set_handler(kbd_evt_fp);
__mykapi void __kbd_evt();

#endif
