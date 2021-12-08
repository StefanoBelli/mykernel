#include <x86/x86.h>
#include "kvga.h"

void kmain() {
	char c[61] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

	kvga_write(c, VGA_TEXT_COLOR_BLACK, VGA_TEXT_COLOR_WHITE, 61);

	x86_cli();
	x86_hlt();
}
