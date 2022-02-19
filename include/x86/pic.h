#ifndef X86_PIC_H
#define X86_PIC_H

#include "types.h"

__mykapi void x86_pic_remap();
__mykapi void x86_pic_eoi(uint8_t irq);
__mykapi void x86_pic_set_mask(uint8_t irq);
__mykapi void x86_pic_clear_mask(uint8_t irq);

#endif
