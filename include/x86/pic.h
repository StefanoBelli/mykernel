#ifndef X86_PIC_H
#define X86_PIC_H

#include "types.h"

__mykapi void x86_pic_remap();
__mykapi void x86_pic_eoi(ubyte irq);
__mykapi void x86_pic_set_mask(ubyte irq);
__mykapi void x86_pic_clear_mask(ubyte irq);

#endif
