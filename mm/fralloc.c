#include <mm/fralloc.h>

static mm_fralloc_stats stats;

__mykapi mm_fralloc_stats mm_fralloc_get_stats() {
	return stats;
}

__mykapi void mm_fralloc_log_stats(const mm_fralloc_stats* s) {

}

__mykapi udword mm_fralloc_init(udword low_addr, udword high_addr) {
	return 0;
}

__mykapi udword mm_fralloc_reserve() {
	return 0;
}

__mykapi udword mm_fralloc_release(udword phys) {
	return 0;
}
