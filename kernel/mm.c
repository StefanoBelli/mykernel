#include <x86/x86.h>
#include <misc/gcc.h>
#include <misc/types.h>
#include "mm.h"

typedef struct {
	udword present : 1;
	udword writeable : 1;
	udword supervisor : 1;
	udword write_through : 1;
	udword cache_disable : 1;
	udword accessed : 1;
	udword ignored : 6;
	udword addr : 20;
} packed mm_pgtbl;

typedef struct {
	udword present : 1;
	udword writeable : 1;
	udword supervisor : 1;
	udword write_through : 1;
	udword cache_disable : 1;
	udword accessed : 1;
	udword dirty : 1;
	udword ignored : 5;
	udword addr : 20;
} packed mm_page;

static mm_pgtbl* pagedir = (mm_pgtbl*) 0xc0003000;

void mm_init() {
	pagedir[0].present = 0;
	
	for(udword i = 0; i < 1024; ++i) {
		x86_invlpg(i * 4096);
	}
}
