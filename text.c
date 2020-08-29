#include "text.h"

#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
#include <Protocol/SimpleFileSystem.h>

#include "fb.h"
#include "font.h"
/*
char keycode[] = {
0x0,
};
*/
/*
void textinit(EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fsp) {
    EFI_FILE_PROTOCOL *root, *file;

    EFI_STATUS Status = fsp->OpenVolume(fsp, &root);
    if (EFI_ERROR(Status)) {
        Print(L"Error:Failed to open root filesystem - %r", Status);
        return;
    }

    Status = root->Open(root, &file, L"font.bdf", EFI_FILE_MODE_READ,
                        EFI_FILE_READ_ONLY);
    if (EFI_ERROR(Status)) {
        Print(L"Error:Failed to open font file - %r", Status);
        return;
    }
    UINTN buf_size = 1;
    char* fontfiledata = AllocateRuntimeZeroPool(buf_size);
    if (!fontfiledata) {
        Print(L"Error:Failed to allocate font memory");
        return;
    }

    Status = file->Read(file, &buf_size, (VOID*)fontfiledata);
    if (Status == EFI_BUFFER_TOO_SMALL) {
        FreePool(fontfiledata);
        fontfiledata = AllocateRuntimeZeroPool(buf_size);
        if (!fontfiledata) {
            Print(L"Error:Failed to allocate font memory");
            return;
        }
        Status = file->Read(file, &buf_size, (VOID*)fontfiledata);
        if (EFI_ERROR(Status)) {
            Print(L"Error:Failed to read font file - %r", Status);
            return;
        }
    } else if (EFI_ERROR(Status)) {
        Print(L"Error:Failed to read font file - %r", Status);
        return;
    }
    file->Close(file);
    root->Close(root);
}*/

void textout(UINT8 code) {
    static UINTN x = 0, y = 0;
    for (int row = 0; row < 13; row++) {
        for (int column = 0; column < 8; column++) {
            EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pixel =
                (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)buffer.BaseAddress +
                y * 13 * buffer.HorizontalRes + row * buffer.HorizontalRes +
                8 * x + column;
            if ((font[code][row] >> (7 - column)) & 0x1)
                RGBtoPixel(pixel, 0x00FF00);
        }
    }
    if (x < (buffer.HorizontalRes / 8) - 1)
        x++;
    else if (y < buffer.VerticalRes / 13) {
        x = 0;
        y++;
    }
}