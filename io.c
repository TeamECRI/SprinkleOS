#include "io.h"
UINT8 mapped_io_read(UINT16 addr) {
    UINT8 data;
    asm volatile("inb %1,%0" : "=a"(data) : "d"(addr));
    return data;
}

void mapped_io_write(UINT16 addr, UINT8 data) {
    asm volatile("outb %0,%1" ::"a"(data), "d"(addr));
}
