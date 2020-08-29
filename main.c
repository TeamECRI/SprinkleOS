#include <Library/BaseMemoryLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
/*
#include <Pi/PiMultiPhase.h>
#include <Protocol/MpService.h>
*/

#include <Uefi.h>
#include <Uefi/UefiSpec.h>

#include "fb.h"
#include "gdt.h"
#include "interrupt.h"
#include "text.h"

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle,
                           IN EFI_SYSTEM_TABLE *SystemTable) {
    EFI_STATUS Status;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fsp;
    // EFI_MP_SERVICES_PROTOCOL *mps;

    SystemTable->BootServices->SetWatchdogTimer(
        0, 0, 0, NULL);  // Disable watch dog timer

    Status = SystemTable->BootServices->LocateProtocol(
        &gEfiGraphicsOutputProtocolGuid, NULL,
        (VOID **)&gop);  // Get GOP Protocol
    if (EFI_ERROR(Status)) {
        Print(L"Error:Failed to locate EFI Graphics Output Protocol - %r",
              Status);
        return Status;
    }

    Status = SystemTable->BootServices->LocateProtocol(
        &gEfiSimpleFileSystemProtocolGuid, NULL, (VOID **)&fsp);
    if (EFI_ERROR(Status)) {
        Print(L"Error:Failed to locate EFI Simple FileSystem Protocol - %r",
              Status);
        return Status;
    }

    /*
        Status = SystemTable->BootServices->LocateProtocol(
            &gEfiMpServiceProtocolGuid, NULL,
            (VOID **)&mps);  // Get MultiProcessor Protocol
        if (EFI_ERROR(Status)) {
            Print(L"Error:Failed to locate EFI MP Services Protocol - %r",
       Status); return Status;
        }
    */

    FrameBuffer_init(gop);
    UINTN MemoryMapSize = 1, MapKey, DescriptorSize;
    UINT32 DescriptorVersion;
    do {
        EFI_MEMORY_DESCRIPTOR *mem_desc =
            (EFI_MEMORY_DESCRIPTOR *)AllocatePool(MemoryMapSize);
        Status = SystemTable->BootServices->GetMemoryMap(
            &MemoryMapSize, mem_desc, &MapKey, &DescriptorSize,
            &DescriptorVersion);
        if (EFI_ERROR(Status)) continue;
        Status =
            SystemTable->BootServices->ExitBootServices(ImageHandle, MapKey);
    } while (EFI_ERROR(Status));
    GDT_init();
    interrupt_init();
    for (int y = 0; y < buffer.VerticalRes; y++) {
        for (int x = 0; x < buffer.HorizontalRes; x++) {
            EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pixel =
                (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)buffer.BaseAddress +
                (buffer.HorizontalRes * y) + x;
            RGBtoPixel(pixel, 0xFF0000);
        }
    }
    textout('A');
    textout('p');
    textout('p');
    textout('l');
    textout('e');
    while (1) asm volatile("hlt");
    return Status;
}