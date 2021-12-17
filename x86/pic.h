#ifndef X86_PIC_H
#define X86_PIC_H

#include "types.h"

void x86_pic_remap();
void x86_pic_eoi(mykt_uint_8 irq);

#endif
