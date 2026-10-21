#include "functions.h"

/* Zero selects the existing native standard GPU owner */
const uint32 xport_gpu_graph_type_address = 0;

void xport_main(void)
{
    const PSX_EXE executable = {"DATA/SLUS_004.64", 0x80010000, 0x800CFC60, 0x800F035C, 0x800CEDA0, 0x800F035C, 0xFFC9C};
    uint32 heap_size;
    if (!xport_psx_exe_load(&executable))
    {
#ifndef NDEBUG
        fprintf(stderr, "OBL: Cannot load initial data from DATA/SLUS_004.64\n");
#endif
        abort();
    }
    heap_size = (r_u32(0x800CF798) - 8 - r_u32(0x800CF79C)) - 0xF035C;
    w_u32(0x800CEDA4, heap_size);
    psx_bios_init_user_heap(0x800F0360, heap_size);
    if (!mount_resource_source())
    {
#ifndef NDEBUG
        fprintf(stderr, "OBL: Cannot mount extracted resources from DATA\n");
#endif
        abort();
    }
    if (!bind_krom_font())
    {
#ifndef NDEBUG
        fprintf(stderr, "OBL: Cannot load font resource DATA/KROM15.BIN\n");
#endif
        abort();
    }
    bind_sequence_runtime();
    func_80012698();
}
