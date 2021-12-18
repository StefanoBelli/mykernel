#include <x86/x86.h>
#include "kprintf.h"
#include "misc.h"

__mykapi void system_halt() {
	kprintf("system halted\n");
	x86_cli();
	x86_hlt();
}

