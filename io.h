#include <Uefi.h>
#include <Uefi/UefiSpec.h>
UINT8 mapped_io_read(UINT16 addr);
void mapped_io_write(UINT16 addr, UINT8 data);