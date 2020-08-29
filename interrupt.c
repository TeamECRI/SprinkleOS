#include <Library/BaseLib.h>

#include "io.h"
#include "text.h"
#define SPECIAL_SHIFT_L 0b00000001
#define SPECIAL_SHIFT_R 0b00000010
#define SPECIAL_CTRL_L 0b00000100
#define SPECIAL_CTRL_R 0b00001000
#define SPECIAL_ALT_L 0b00010000
#define SPECIAL_ALT_R 0b00100000
#define SPECIAL_SUPER_L 0b01000000
#define SPECIAL_SUPER_R 0b10000000

void null_handler();
void kbd_handler();
IA32_IDT_GATE_DESCRIPTOR descriptors[256];

void descriptor_init() {
    for (int i = 0; i < 256; i++) {
        descriptors[i].Bits.Selector = 0x08;
        descriptors[i].Bits.GateType = IA32_IDT_GATE_TYPE_INTERRUPT_32;
        descriptors[i].Bits.OffsetLow = (UINT32)(UINTN)(VOID *)null_handler;
        descriptors[i].Bits.OffsetHigh =
            (UINT32)((UINTN)(VOID *)null_handler >> 16);
        descriptors[i].Bits.OffsetUpper =
            (UINT32)((UINTN)(VOID *)null_handler >> 32);
    }  // null descriptor set
}

void set_handler(int num, UINTN handler) {
    descriptors[num].Bits.OffsetLow = (UINT32)handler;
    descriptors[num].Bits.OffsetHigh = (UINT32)(handler >> 16);
    descriptors[num].Bits.OffsetUpper = (UINT32)(handler >> 32);
}

void master_pic_init() {
    mapped_io_write(0x0020, 0x11);  // ICW1
    mapped_io_write(0x0021, 32);    // ICW2
    mapped_io_write(0x0021, 0x04);  // ICW3
    mapped_io_write(0x0021, 0x01);  // ICW4
    mapped_io_write(0x0021, 0xFF);  // OCW1
}

void slave_pic_init() {
    mapped_io_write(0x00A0, 0x11);
    mapped_io_write(0x00A1, 40);
    mapped_io_write(0x00A1, 0x02);
    mapped_io_write(0x00A1, 0x01);
    mapped_io_write(0x00A1, 0xff);
}

void unmask_interrupt(UINT8 interrupt_num) {
    if (interrupt_num < 40) {
        UINT8 mask = mapped_io_read(0x0021);
        mapped_io_write(0x0021, mask & ~(1 << (interrupt_num - 32)));
    } else {
        UINT8 mask = mapped_io_read(0x00A1);
        mapped_io_write(0x00A1, mask & ~(1 << (interrupt_num - 40)));
    }
}

void end_of_interrupt(UINT8 interrupt_num) {
    if (interrupt_num < 40) {
        mapped_io_write(0x0020, 0x60 | (interrupt_num - 32));
    } else {
        mapped_io_write(0x00A0, 0x60 | (interrupt_num - 40));
    }
}

void interrupt_init() {
    IA32_DESCRIPTOR Descriptor;
    descriptor_init();
    set_handler(33, (UINTN)(VOID *)kbd_handler);
    Descriptor.Limit = (UINT16)(sizeof(descriptors) - 1);
    Descriptor.Base = (UINT32)(UINTN)(VOID *)descriptors;
    AsmWriteIdtr(&Descriptor);
    EnableInterrupts();
    master_pic_init();
    slave_pic_init();
    unmask_interrupt(33);
}

void keyboard_int_proc() {
    UINT8 data;
    // static char keyboard_special_keys = 0;
    data = mapped_io_read(0x64);
    if ((data & 0b00000001) == 0)  // output buffer is not full
        goto eoi;
    data = mapped_io_read(0x60);
    /*
    if (data & 0b10000000){  // key is broken
        switch (data & 0b01111111) {
            case 44:
                keyboard_special_keys &= ~SPECIAL_SHIFT_L;
                return;
            case 57:
                keyboard_special_keys &= ~SPECIAL_SHIFT_R;
                return;
            case 58:
                keyboard_special_keys &= ~SPECIAL_CTRL_L;
                return;
            case 64:
                keyboard_special_keys &= ~SPECIAL_CTRL_R;
                return;
            case 60:
                keyboard_special_keys &= ~SPECIAL_ALT_L;
                return;
            case 62:
                keyboard_special_keys &= ~SPECIAL_ALT_R;
                return;
            case :
                keyboard_special_keys &= ~SPECIAL_CTRL_L;
                return;
            default:
                return;
        }
    }
    */
    textout('0');
eoi:
    end_of_interrupt(33);
}