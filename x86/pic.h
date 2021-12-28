#ifndef X86_PIC_H
#define X86_PIC_H

#include "types.h"

__mykapi void x86_pic_remap();
__mykapi void x86_pic_eoi(mykt_uint_8 irq);
__mykapi void x86_pic_set_mask(mykt_uint_8 irq);
__mykapi void x86_pic_clear_mask(mykt_uint_8 irq);

#endif
