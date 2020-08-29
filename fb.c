#include "fb.h"
struct FrameBuffer buffer;
void FrameBuffer_init(
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop) {  // Initialize framebuffer struct
    buffer.BaseAddress = gop->Mode->FrameBufferBase;
    buffer.Size = gop->Mode->FrameBufferSize;
    buffer.HorizontalRes = gop->Mode->Info->HorizontalResolution;
    buffer.VerticalRes = gop->Mode->Info->VerticalResolution;
    buffer.PixelFormat = gop->Mode->Info->PixelFormat;
}

void RGBtoPixel(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pixel,
                UINT32 RGB) {  // 0xaaaaaa format RGB to BGR Pixel format
    pixel->Blue = RGB & 0xff;
    pixel->Green = (RGB >> 8) & 0xff;
    pixel->Red = (RGB >> 16) & 0xff;
}