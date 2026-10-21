#include "functions.h"

/* Full original adapters, pending final integration and runtime validation */
uint32 func_80073870(sint16 bank, sint16 program, uint8 value)
{
    FUNCTION_MARKER(0x80073870, "SLUS_004.64");
    return spu_vab_set_program_pan(bank, program, value);
}

uint32 func_8003ccac(const char *path, uint32 destination)
{
    uint32 mode;
    FUNCTION_MARKER(0x8003CCAC, "SLUS_004.64");
    DrawSync(0);
    SetDispMask(1);
    func_8003943c(0);
    mode = r_u32(0x800CF7D0);
    return load_named_resource_slice(path, destination, 0, 0x4000, mode);
}

uint32 func_8003cdd4(const char *path, uint32 destination, uint32 offset, uint32 length, uint32 enabled, uint32 rect_xy, uint32 rect_wh)
{
    uint32 mode;
    FUNCTION_MARKER(0x8003CDD4, "SLUS_004.64");
    if (enabled != 1)
        return 1;
    DrawSync(0);
    SetDispMask(1);
    func_8003943c(0);
    mode = r_u32(0x800CF7D0);
    load_named_resource_slice(path, destination, offset, length, mode);
    return (uint32)func_8003ce84(destination, rect_xy, rect_wh);
}

uint32 func_80067e3c(uint32 rotation, uint32 matrix)
{
    SVECTOR *angles;
    MATRIX *output;
    FUNCTION_MARKER(0x80067E3C, "SLUS_004.64");
    angles = (SVECTOR *)psx_addr(rotation, 6);
    output = (MATRIX *)psx_addr(matrix, 18);
    gte_rot_matrix_scalar(angles, output);
    return matrix;
}

uint32 func_800769c0(sint16 sequence, sint16 separation, uint8 value)
{
    SpuSequenceSchedulerTrack *record;
    FUNCTION_MARKER(0x800769C0, "SLUS_004.64");
    record = spu_sequence_scheduler.tracks[(uint32)(sint32)sequence] + (uint32)(sint32)separation;
    return spu_sequence_scheduler_data_entry(record, sequence, separation, value, sequence_data_entry_commands, 128, func_80077634);
}

uint32 func_80076f64(sint16 bank, sint16 program, sint16 tone, sint16 command, uint8 value)
{
    VagAtr attributes = {0};
    uint32 result;
    FUNCTION_MARKER(0x80076F64, "SLUS_004.64");
    result = spu_vab_nrpn_attr_by_value(command, bank, program, tone, attributes, value);
    if ((uint16)command >= 23)
        return (uint32)(sint32)command * 4;
    if (command >= 20)
        return 0x80077208;
    return result;
}

sint32 func_80068ac8(uint32 matrix)
{
    FUNCTION_MARKER(0x80068AC8, "SLUS_004.64");
    return gte_matrix_near_identity((const MATRIX *)psx_addr(matrix, 18));
}

void func_800709e4(uint32 voice, uint16 left, uint16 right)
{
    FUNCTION_MARKER(0x800709E4, "SLUS_004.64");
    spu_sequence_vm_noise_key_on_direct((uint8)voice, (sint16)left, (sint16)right);
}

void func_80071e34(uint16 left, uint16 right)
{
    FUNCTION_MARKER(0x80071E34, "SLUS_004.64");
    spu_sequence_vm_noise_key_on_allocated((sint16)left, (sint16)right);
}

void func_80071f90(uint16 left, uint16 right)
{
    FUNCTION_MARKER(0x80071F90, "SLUS_004.64");
    spu_sequence_vm_noise_key_on_allocated((sint16)left, (sint16)right);
}

void func_80070d60(uint32 voice, sint16 bend)
{
    FUNCTION_MARKER(0x80070D60, "SLUS_004.64");
    spu_sequence_vm_voice_bend_offset((uint8)voice, bend);
}

uint32 func_80072238(sint16 sequence, sint16 bank, sint16 program, uint16 bend)
{
    FUNCTION_MARKER(0x80072238, "SLUS_004.64");
    return spu_sequence_vm_sequence_bend(sequence, bank, program, bend);
}

sint32 func_800749f8(uint16 voice, sint16 bank, sint16 program, sint16 note, uint16 new_note, uint16 fine)
{
    FUNCTION_MARKER(0x800749F8, "SLUS_004.64");
    return spu_sequence_vm_voice_set_pitch(voice, bank, program, note, new_note, fine);
}

sint32 func_80074b58(uint16 voice, sint16 bank, sint16 program, sint16 note, uint16 adsr1, uint16 adsr2)
{
    FUNCTION_MARKER(0x80074B58, "SLUS_004.64");
    return spu_sequence_vm_voice_set_adsr(voice, bank, program, note, adsr1, adsr2);
}

void func_80070508(uint32 voice)
{
    FUNCTION_MARKER(0x80070508, "SLUS_004.64");
    spu_sequence_vm_noise_on(&spu_sequence_scheduler, (uint8)voice);
}

uint32 sequence_channel_volume(sint16 sequence, sint16 separation, uint8 value)
{
    return spu_sequence_scheduler_volume(&spu_sequence_scheduler, sequence, separation, value, func_80073938, func_80077634);
}

uint32 sequence_channel_pan(sint16 sequence, sint16 separation, uint8 value)
{
    return spu_sequence_scheduler_pan(&spu_sequence_scheduler, sequence, separation, value, func_80073938, func_80077634);
}

uint32 sequence_channel_expression(sint16 sequence, sint16 separation, uint8 value)
{
    return spu_sequence_scheduler_expression(&spu_sequence_scheduler, sequence, separation, value, func_80073938, func_80077634);
}

uint32 sequence_channel_damper(sint16 sequence, sint16 separation, uint8 value)
{
    return spu_sequence_scheduler_damper(&spu_sequence_scheduler, sequence, separation, value, func_80077634);
}

uint32 sequence_channel_reverb(sint16 sequence, sint16 separation, uint8 value)
{
    return spu_sequence_scheduler_reverb_depth(&spu_sequence_scheduler, sequence, separation, value, spu_sequence_vm_reverb_depth, func_80077634);
}

uint32 func_80075e80(sint16 sequence, sint16 separation, uint8 controller)
{
    FUNCTION_MARKER(0x80075E80, "SLUS_004.64");
    return spu_sequence_scheduler_control_change(&spu_sequence_scheduler, sequence, separation, controller, &spu_sequence_handlers, func_80077634);
}

sint32 func_80073e44(sint16 bank, sint16 program, sint16 tone, sint16 note, sint16 fine, sint16 left, sint16 right)
{
    FUNCTION_MARKER(0x80073E44, "SLUS_004.64");
    return SsUtKeyOn(bank, program, tone, note, fine, left, right);
}

sint32 func_80074450(sint16 voice, sint16 bank, sint16 program, sint16 tone, sint16 note, sint16 fine, sint16 left, sint16 right)
{
    FUNCTION_MARKER(0x80074450, "SLUS_004.64");
    return SsUtKeyOnV(voice, bank, program, tone, note, fine, left, right);
}

sint32 func_80044ce4(void)
{
    FUNCTION_MARKER(0x80044CE4, "SLUS_004.64");
    return GetODE();
}

sint32 func_80043e70(sint32 reverse)
{
    FUNCTION_MARKER(0x80043E70, "SLUS_004.64");
    return SetGraphReverse(reverse);
}

sint32 func_80043ff0(sint32 enabled)
{
    FUNCTION_MARKER(0x80043FF0, "SLUS_004.64");
    return SetGraphQue(enabled);
}

void func_8004e594(uint32 work)
{
    FUNCTION_MARKER(0x8004E594, "SLUS_004.64");
    GsSetWorkBase((uint32 *)psx_addr(work, 4));
}

void func_8004e4bc(sint32 distance)
{
    FUNCTION_MARKER(0x8004E4BC, "SLUS_004.64");
    gs_set_clip_distance(distance);
}

PsxInterruptCallback func_8007d060(PsxInterruptCallback callback)
{
    FUNCTION_MARKER(0x8007D060, "SLUS_004.64");
    return SpuSetTransferCallback(callback);
}

uint32 func_80073938(sint16 sequence, sint16 bank, sint16 program, uint16 volume, uint16 pan)
{
    FUNCTION_MARKER(0x80073938, "SLUS_004.64");
    return spu_sequence_vm_set_volume(&spu_sequence_scheduler, sequence, bank, program, volume, pan);
}

PsxCallbackDriver *func_8006d960(void)
{
    FUNCTION_MARKER(0x8006D960, "SLUS_004.64");
    return stopIntr();
}

PsxCallbackDriver *func_8006d990(void)
{
    FUNCTION_MARKER(0x8006D990, "SLUS_004.64");
    return restartIntr();
}

PsxInterruptCallback func_8006d930(uint32 slot, PsxInterruptCallback callback)
{
    FUNCTION_MARKER(0x8006D930, "SLUS_004.64");
    return setIntrVSync(slot, callback);
}

void func_8006bed8(void)
{
    FUNCTION_MARKER(0x8006BED8, "SLUS_004.64");
    EnterCriticalSectionPSX();
    CdDataCallback(NULL);
    CdReadyCallback(NULL);
    ExitCriticalSection();
}

sint32 func_8006e0d0(void)
{
    FUNCTION_MARKER(0x8006E0D0, "SLUS_004.64");
    return GetVideoMode();
}

sint32 func_8007a300(void)
{
    FUNCTION_MARKER(0x8007A300, "SLUS_004.64");
    return spu_stop_transfer();
}

uint32 func_8007adc0(uint32 destination, uint32 address_units, uint32 blocks)
{
    uint32 bytes = (uint32)(uint16)blocks << 6;
    FUNCTION_MARKER(0x8007ADC0, "SLUS_004.64");
    return spu_read_blocks(psx_addr(destination, bytes), (uint16)address_units, (uint16)blocks);
}

void func_8004b4f0(uint32 object, uint32 ordering_table, uint32 shift, uint32 scratch)
{
    FUNCTION_MARKER(0x8004B4F0, "SLUS_004.64");
    bind_gs_subdivision_controls();
    gs_sort_object4(object, ordering_table, shift, scratch);
}

#include "psx_gpu.h"

uint32 func_8001a598(uint32 index, uint32 tim)
{
    GpuTimImage image;
    uint32 segment, physical, available, descriptor, result;
    sint32 x, y;
    FUNCTION_MARKER(0x8001A598, "SLUS_004.64");
    VSync(2);
    DrawSync(0);
    SetDispMask(1);
    segment = tim & 0xE0000000;
    physical = tim & 0x1FFFFFFF;
    if ((segment != 0 && segment != 0x80000000 && segment != 0xA0000000) || physical > PSX_DRAM_SIZE - 8)
        abort();
    available = PSX_DRAM_SIZE - physical - 4;
    if (!gpu_decode_tim_body(psx_addr(tim + 4, available), available, &image))
        abort();
    result = (uint32)LoadImagePSX(&image.pixels, (uint32 *)image.pixel_data);
    if ((image.mode & 8) != 0)
        result = (uint32)LoadImagePSX(&image.clut, (uint32 *)image.clut_data);
    if (index == 0)
        return result;
    descriptor = 0x800E9E64 + index * 36;
    w_u32(descriptor, ((image.mode & 3) << 24) | 0x40);
    w_u16(descriptor + 8, (uint16)image.pixels.w);
    w_u16(descriptor + 4, 0);
    w_u16(descriptor + 6, 0);
    w_u16(descriptor + 10, (uint16)image.pixels.h);
    w_u16(descriptor + 24, 16);
    w_u16(descriptor + 26, 16);
    x = image.pixels.x;
    y = image.pixels.y;
    w_u16(descriptor + 12, GetTPage(0, 0, x, y));
    w_u8(descriptor + 14, (uint8)(x % 64));
    w_u8(descriptor + 15, (uint8)(y % 256));
    w_u16(descriptor + 16, (uint16)image.clut.x);
    w_u32(descriptor + 32, 0);
    w_u16(descriptor + 18, (uint16)image.clut.y);
    w_u8(descriptor + 20, 128);
    w_u8(descriptor + 21, 128);
    w_u8(descriptor + 22, 128);
    w_u16(descriptor + 28, 4096);
    w_u16(descriptor + 30, 4096);
    return index * 36;
}

#include <string.h>

void resource_load_error(const char *message)
{
    func_80037934(message, -144, -104, 320, 200);
}

uint32 func_8001a858(uint32 mode)
{
    char path[264], *digits;
    uint8 parts[3];
    sint32 identifier = (sint32)mode;
    sint32 count, source_mode;
    uint32 index, destination, result, archive, entry, offset, descriptor;
    FUNCTION_MARKER(0x8001A858, "SLUS_004.64");
    strcpy(path, guest_c_string(0x8007D938));
    digits = strchr(path, '?');
    parts[0] = (uint8)(identifier / 100);
    parts[1] = (uint8)((identifier % 100) / 10);
    parts[2] = (uint8)((identifier % 100) % 10);
    for (index = 0; index < 3; ++index)
        digits[index] = (char)(parts[index] + 48);
    destination = r_u32(0x800CF9F0);
    source_mode = r_s32(0x800CF7E0);
    result = (uint32)func_80036184(path, destination, source_mode);
    if (result == 0)
    {
        resource_load_error(guest_c_string(0x800107DC));
        result = func_80028a94();
    }
    archive = r_u32(0x800CF9F0);
    count = r_s32(archive);
    entry = archive + 4;
    if (count > 0)
    {
        for (index = 0; (sint32)index < count; ++index)
        {
            offset = r_u32(entry + 0x20);
            func_8001a598(index, archive + offset);
            entry += 0x28;
        }
        result = 0;
    }
    if (mode == 0)
    {
        for (index = 0; index < 11; ++index)
        {
            descriptor = 0x800E9E64 + (index + 6) * 36;
            w_u32(descriptor, (r_u32(descriptor) & 0x8FFFFFFF) | 0x40000000);
        }
        result = 0;
    }
    return result;
}

void func_8001f174(uint32 resource)
{
    char path[264], *digits;
    uint8 parts[3];
    sint32 identifier = (sint32)resource;
    sint32 count, bytes, source_mode;
    uint32 pattern, index, destination, archive, entry, slot, data, value;
    FUNCTION_MARKER(0x8001F174, "SLUS_004.64");
    func_8001eff8();
    pattern = 0x8007DA4C + ((uint32)(identifier / 20) << 5);
    strcpy(path, guest_c_string(pattern));
    digits = strchr(path, '?');
    parts[0] = (uint8)(identifier / 100);
    parts[1] = (uint8)((identifier % 100) / 10);
    parts[2] = (uint8)((identifier % 100) % 10);
    for (index = 0; index < 3; ++index)
        digits[index] = (char)(parts[index] + 48);
    destination = r_u32(0x800CF9EC);
    source_mode = r_s32(0x800CF7D8);
    bytes = func_80036184(path, destination, source_mode);
    if (bytes == 0)
    {
        resource_load_error(guest_c_string(0x80010800));
        func_80028a94();
    }
    archive = r_u32(0x800CF9EC);
    count = r_s32(archive);
    entry = archive + 4;
    for (index = 0; (sint32)index < count; ++index)
    {
        slot = r_u32(0x800CF9DC);
        data = archive + r_u32(entry + 0x20);
        w_u32(0x800EC480 + (slot << 2), data + 8);
        w_u32(0x800EB9F8 + (slot << 2), r_u32(data + 4));
        data = r_u32(0x800EC480 + (slot << 2));
        value = r_u32(data + 4);
        w_u32(0x800CF9DC, slot + 1);
        w_u32(0x800E27A4 + (slot << 2), value);
        entry += 0x28;
    }
    value = (uint32)bytes + 4 - (uint32)(bytes % 4);
    archive = r_u32(0x800CF9EC);
    w_u32(0x800CF9EC, archive + value);
}

uint32 func_80022ab0(uint32 resource, uint32 skip_models, uint32 skip_images, uint32 skip_script, uint32 skip_world, uint32 skip_mac, uint32 skip_tod, uint32 preserve_allocations)
{
    char path[264], *digits;
    uint8 parts[4];
    sint32 identifier = (sint32)resource;
    sint32 count;
    uint32 index, archive, entry, result, location, capacity, data_base;
    uint32 file_offset, buffered, discarded, chunk, remainder, destination;
    uint32 data, bytes, value, slot, model_end;
    PSX_RECT rectangle;
    FUNCTION_MARKER(0x80022AB0, "SLUS_004.64");
    strcpy(path, guest_c_string(0x8007D94C + ((uint32)(identifier / 20) << 5)));
    digits = strchr(path, '?');
    parts[0] = (uint8)(identifier / 1000);
    parts[1] = (uint8)((identifier % 1000) / 100);
    parts[2] = (uint8)((identifier % 100) / 10);
    parts[3] = (uint8)((identifier % 100) % 10);
    for (index = 0; index < 4; ++index)
        digits[index] = (char)(parts[index] + 48);
    if (r_u32(0x800CF7D4) == 0)
    {
        func_8003943c(0);
        if (r_u32(0x800EE7E4) != 0 && r_u32(0x800CF87C) != 0)
            func_80028898(2);
    }
    else if (r_u32(0x800CF87C) == 0)
    {
        func_8003943c(0);
        DrawSync(0);
        func_8001eff8();
    }
    else
    {
        func_8003943c(0x80041114);
        if (r_u32(0x800EE7E4) != 0)
        {
            func_80013394();
            func_80013394();
            DrawSync(0);
            func_8001eff8();
        }
        func_80040f0c(128, 0, 2);
    }
    func_8001eff8();
    archive = r_u32(0x800CF9FC);
    location = 0x800DE14C + resource * 24;
    result = load_resource_slice_native(path, archive, 0, 0x3DB88, r_u32(0x800CF7D4), location);
    func_8003943c(0);
    VSync(0);
    setRECT(&rectangle, 0, 0, 320, 480);
    ClearImage(&rectangle, 0, 0, 0);
    DrawSync(0);
    if (skip_world == 0)
        func_80021ebc();
    if (result == 0)
        return 0;
    count = r_s32(archive);
    w_u32(0x800CFE14, r_u32(0x800CFA48));
    entry = archive + 4;
    if (preserve_allocations == 0)
    {
        w_u32(0x800CF9DC, r_u32(0x800CF9E4));
        if (skip_mac == 0)
        {
            w_u32(0x800EBE2C, 0xFFFFFFFF);
            w_u32(0x800CF8BC + (r_u32(0x800CFA68) << 2), 0);
        }
    }
    value = r_u32(entry + 0x20);
    file_offset = 0x3DB88;
    discarded = 0;
    buffered = 0;
    capacity = 0x3DB88 - value;
    data_base = archive + value;
    for (index = 0; (sint32)index < count; ++index)
    {
        chunk = r_u32(entry + 0x48) - r_u32(entry + 0x20);
        remainder = capacity - buffered;
        if ((sint32)(buffered + chunk) < (sint32)capacity)
        {
            /* Reload the next offset after the original conditional branch */
            chunk = r_u32(entry + 0x48) - r_u32(entry + 0x20);
            buffered += chunk;
        }
        else
        {
            func_80041820(data_base, data_base + buffered, remainder);
            destination = data_base + remainder;
            discarded += buffered;
            if ((destination & 3) != 0)
            {
                resource_load_error(guest_c_string(0x80010838));
                func_80028a94();
            }
            DrawSync(0);
            load_resource_slice_native(path, destination, file_offset, buffered, r_u32(0x800CF7D4), location);
            file_offset += buffered;
            buffered = r_u32(entry + 0x48) - r_u32(entry + 0x20);
        }
        result = func_800221a4((const uint8 *)guest_c_string(entry));
        switch (result)
        {
        case 1:
            if (skip_models == 0)
            {
                w_u32(0x800CF9CC, 8);
                data = r_u32(entry + 0x20);
                bytes = r_u32(entry + 0x24);
                model_end = func_8001ea94(r_u32(0x800CFE14), archive + data - discarded, (sint32)bytes);
                w_u32(0x800CFE14, model_end);
                w_u32(0x800CFE14, model_end + 4 - (uint32)((sint32)model_end % 4));
                value = r_u32(0x800CF9CC);
                skip_models = 1;
                w_u32(0x800CF9B8, value);
            }
            break;
        case 2:
            if (skip_images == 0)
                func_8001a598(0, archive + r_u32(entry + 0x20) - discarded);
            break;
        case 3:
            if (skip_world == 0)
            {
                data = archive + r_u32(entry + 0x20) - discarded;
                value = r_u32(data);
                if (value == r_u32(0x800CF7BC))
                    func_8001fbe8(data);
                else
                {
                    if (value == 7)
                        func_80028c44(guest_c_string(0x8007D7E0));
                    func_80028a94();
                }
                skip_world = 1;
            }
            break;
        case 4:
            if (skip_script == 0)
            {
                data = r_u32(entry + 0x20);
                bytes = r_u32(entry + 0x24);
                destination = r_u32(0x800CFE14);
                w_u32(0x800CFA50, destination);
                w_u32(0x800CFA54, bytes + destination);
                w_u32(0x800CFA58, bytes);
                func_80041820(destination, archive + data - discarded, bytes);
                value = bytes + 4 + r_u32(0x800CFE14);
                w_u32(0x800CFE14, value);
                w_u32(0x800CFE14, value + 4 - (uint32)((sint32)value % 4));
                skip_script = 1;
            }
            break;
        case 5:
            if (skip_mac == 0)
            {
                slot = r_u32(0x800CFA68);
                data = r_u32(entry + 0x20);
                bytes = r_u32(entry + 0x24);
                destination = r_u32(0x800CFA5C + (slot << 2));
                func_80041820(destination, archive + data - discarded, bytes);
                slot = r_u32(0x800CFA68);
                skip_mac = 1;
                w_u32(0x800CF8BC + (slot << 2), 1);
            }
            break;
        case 6:
            if (skip_tod == 0)
            {
                data = r_u32(entry + 0x20);
                destination = r_u32(0x800CFE14);
                bytes = r_u32(entry + 0x24);
                func_80041820(destination, archive + data - discarded, bytes);
                slot = r_u32(0x800CF9DC);
                destination = r_u32(0x800CFE14);
                w_u32(0x800EC480 + (slot << 2), destination + 8);
                w_u32(0x800EB9F8 + (slot << 2), r_u32(destination + 4));
                data = r_u32(0x800EC480 + (slot << 2));
                w_u32(0x800E27A4 + (slot << 2), r_u32(data + 4));
                bytes = r_u32(entry + 0x24);
                w_u32(0x800CF9DC, slot + 1);
                value = destination + bytes;
                w_u32(0x800CFE14, value);
                w_u32(0x800CFE14, value + 4 - (uint32)((sint32)value % 4));
            }
            break;
        }
        entry += 0x28;
    }
    if (preserve_allocations == 0)
    {
        value = r_u32(0x800CFE14);
        value = value + 4 - (uint32)((sint32)value % 4);
        slot = r_u32(0x800CF9DC);
        w_u32(0x800CFE14, value);
        w_u32(0x800CFA1C, value);
        destination = value + 0x35C0;
        w_u32(0x800CFE14, destination);
        w_u32(0x800CFA4C, destination);
        w_u32(0x800CF9E8, slot);
        w_u32(0x800CFE14, value + 0x35C4 - (uint32)((sint32)destination % 4));
    }
    func_8003943c(0);
    return 1;
}
