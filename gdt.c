#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Uefi.h>

#include "io.h"

UINT64 SegmentDescriptors[] = {
    0x0000000000000000,  // NULL Descriptor
    0x00AF9A000000FFFF,  // BaseAddress 0 Granularity 1
    // SegmentSize 1048575*4069=4294963200(4GB) Segment Present
    // Plivilege 0 Code Segment Read+Exec
    0x00CF93000000FFFF  // BaseAddress 0 Granularity 1
                        // SegmentSize 1048575*4069=4294963200(4GB) Segment
                        // Present Plivilege 0 Data Segment Read+Write
};
IA32_DESCRIPTOR Descriptor;

void sendparallelstub(UINT8 byte) {
    mapped_io_write(0x378, byte);
    UINT8 control = mapped_io_read(0x37a);
    mapped_io_write(0x37a, control | 1);
    int a;
    for (int i = 0; i < 200; i++) a += control;
    mapped_io_write(0x37a, control);
}

void GDT_init() {
    Descriptor.Limit = (UINT16)(sizeof(UINT64) * 3 - 1);
    Descriptor.Base = (UINT32)(UINTN)(VOID *)SegmentDescriptors;
    AsmWriteGdtr(&Descriptor);
    asm volatile(
        "mov $16, %ax\n"
        "mov %ax, %ss\n"
        "mov %ax, %ds\n"
        "mov %ax, %es\n"
        "mov %ax, %fs\n"
        "mov %ax, %gs\n"
        "sub $16,%rsp\n"
        "leaq end(%rip),%rax\n"
        "mov %rax,(%rsp)\n"
        "mov $8,%ax\n"
        "mov %ax,4(%rsp)\n"
        "ljmp *(%rsp)\n"
        "end:\n"
        "add $16,%rsp");
}