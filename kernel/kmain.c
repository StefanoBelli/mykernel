#include <x86/x86.h>
#include "kvga.h"

#define S "log:\tentry\n"

void kmain() {

	char what[11] = S;
	char what1[4] = "ciao";

	kvga_clear(VGA_TEXT_COLOR_BLACK, VGA_TEXT_COLOR_WHITE);

	for(int i = 0; i < 24; ++i)
		kvga_write(what, VGA_TEXT_COLOR_BLACK, VGA_TEXT_COLOR_WHITE, 11);
	
	kvga_write(what1, VGA_TEXT_COLOR_BLACK, VGA_TEXT_COLOR_WHITE,4);

	kvga_update_cursor();

	x86_cli();
	x86_hlt();
}
