#include <Protocol/GraphicsOutput.h>

struct FrameBuffer {
    EFI_PHYSICAL_ADDRESS BaseAddress;
    UINTN Size;
    UINT32 HorizontalRes;
    UINT32 VerticalRes;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
};

extern struct FrameBuffer buffer;

void FrameBuffer_init(EFI_GRAPHICS_OUTPUT_PROTOCOL *gop);
void RGBtoPixel(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *pixel, UINT32 RGB);