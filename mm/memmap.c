#include <mm/memmap.h>
#include <mm/pgtbl.h>
#include <kernel/kprintf.h>

#define MIN_PHYS_MEM_AVAIL 0x100000

typedef struct {
    uint32_t base_low;
    uint32_t base_high;
    uint32_t length_low;
    uint32_t length_high;
    uint32_t type;
    uint32_t reserved; // ACPI things
} packed memory_map_entry;

static uint32_t __avail_phys_mem_min;
static uint32_t __avail_phys_mem_max;

static uint32_t __pt_ptstore[1024] aligned(4096);

uint32_t* pt;
uint32_t pt_phys;

__mykapi uint32_t mm_memmap_seek() {
    uint32_t n_ents = *(uint32_t*) 0xffc07e00;
    memory_map_entry* map = (memory_map_entry*) 0xffc07e04;

    kprintf("bios-e820: provides the following "
            "memory map (rhs range next int8_t incl):\n"
            "memmap: got %u total entries\n", n_ents);

    for(uint32_t i = 0; i < n_ents; ++i) {
        char* typestr = "reserved";
        uint32_t max_mem = map[i].length_low + map[i].base_low - 1;
        if(map[i].type == 1) {
            typestr = "usable";
            if(map[i].base_low <= MIN_PHYS_MEM_AVAIL
               && max_mem > __avail_phys_mem_max) {
                __avail_phys_mem_min = MIN_PHYS_MEM_AVAIL;
                __avail_phys_mem_max = max_mem;
            }
        }

        kprintf("memmap: from %p to %p is %s\n", map[i].base_low,
                max_mem, typestr);
    }

    return __avail_phys_mem_min != MIN_PHYS_MEM_AVAIL;
}

__mykapi uint32_t mm_memmap_ptstore_setup() {
    uint32_t _pt_start = 1 + ((__avail_phys_mem_max - 0x400000 - 1023) >> 12);
    __avail_phys_mem_min += 0x400000;

    pt_phys = _pt_start * 0x1000;

    pd[1022] = ((uint32_t) __pt_ptstore - 0xc0000000 + 0x100000) | 3;

    for(uint32_t i = 0; i < 1024; ++i) {
        __pt_ptstore[i] = (_pt_start + i) * 0x1000 | 3;
    }

    __avail_phys_mem_max -= 0x400000;
    pt = (uint32_t*) 0xff800000;

    return __avail_phys_mem_max <= __avail_phys_mem_min;
}

__mykapi void mm_memmap_log_avail_memory() {
    kprintf("kernel: total available memory - %u bytes\n"
            "kernel: total available memory - from %p to %p\n",
            __avail_phys_mem_max - __avail_phys_mem_min + 1,
            __avail_phys_mem_min, __avail_phys_mem_max);
}

__mykapi uint32_t __mm_memmap_get_avail_phys_mem_min() {
    return __avail_phys_mem_min;
}

__mykapi uint32_t __mm_memmap_get_avail_phys_mem_max() {
    return __avail_phys_mem_max;
}