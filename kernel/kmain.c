#include <x86/x86.h>
#include <misc/string.h>
#include "kvga.h"

void kmain() {
	char buf[100];
	int wrote = myk_snprintf(buf, 100, "ciao coglione %p a",buf);
	kvga_write(buf, VGA_TEXT_COLOR_BLACK, VGA_TEXT_COLOR_WHITE, wrote, kvga_clear);
	x86_cli();
	x86_hlt();
}
