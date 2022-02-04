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

void mm_init() {

}
