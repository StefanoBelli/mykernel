#include "x86.h"
#include "pic.h"

#define PIC1_CTRL 0x20
#define PIC1_DATA 0x21
#define PIC2_CTRL 0xa0
#define PIC2_DATA 0xa1

#define ICW1 0x11
#define ICW2_OFF1 0x20
#define ICW2_OFF2 0x28
#define ICW3_PIC1 4
#define ICW3_PIC2 2
#define ICW4 1
#define ZERO_DATA_REG 0

#define EOI 0x20

__mykapi void x86_pic_remap() {
	// Start PIC initialization sequence
	x86_outb(PIC1_CTRL, ICW1);
	x86_outb(PIC2_CTRL, ICW1);

	// Map IRQs
	x86_outb(PIC1_DATA, ICW2_OFF1);
	x86_outb(PIC2_DATA, ICW2_OFF2);

	// Tell PICs that they are in a master/slave config
	x86_outb(PIC1_DATA, ICW3_PIC1);
	x86_outb(PIC2_DATA, ICW3_PIC2);

	// Tell PICs that they are running in 8086 env
	x86_outb(PIC1_DATA, ICW4);
	x86_outb(PIC2_DATA, ICW4);

	// Zero data PICs data registers
	x86_outb(PIC1_DATA, ZERO_DATA_REG);
	x86_outb(PIC2_DATA, ZERO_DATA_REG);
}

__mykapi void x86_pic_eoi(mykt_uint_8 intno) {
	if(intno >= 40) {
		x86_outb(PIC2_CTRL, EOI);
	}

	x86_outb(PIC1_CTRL, EOI);
}

__mykapi void x86_pic_set_mask(mykt_uint_8 irq) {
    mykt_int_16 port;
    mykt_int_8 value;

    if(irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    
    value = (mykt_int_8) (x86_inb(port) | (1 << irq));
    x86_outb(port, value);
}

__mykapi void x86_pic_clear_mask(mykt_uint_8 irq) {
    mykt_int_16 port;
    mykt_int_8 value;

    if(irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = (mykt_int_8) (x86_inb(port) & ~(1 << irq));
    x86_outb(port, value);
}
