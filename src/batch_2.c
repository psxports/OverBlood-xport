#include "functions.h"
#include <string.h>

/* Full original bodies, pending final integration and runtime validation */
uint32 func_80023bc0(void)
{
    uint32 index;
    FUNCTION_MARKER(0x80023BC0, "SLUS_004.64");
    index = 0;
    if (r_u32(0x8007F064) != 0xFFFFFFFF)
    {
        index = 1;
        while (r_u32(0x8007F064 + 44 * index) != 0xFFFFFFFF)
            ++index;
    }
    return index;
}

uint32 func_80020b7c(uint32 destination_index, uint32 source_index)
{
    uint32 mode;
    uint32 value;
    FUNCTION_MARKER(0x80020B7C, "SLUS_004.64");
    mode = r_u32(0x800EDFD0);
    value = r_u32(0x80081938 + 4 * source_index);
    value -= mode ? 850 : 1700;
    w_u32(0x80081958 + 4 * destination_index, value);
    return value;
}

static void resource_directory_core(sint32 count, uint32 types, uint32 offsets, uint32 sizes, uint32 directory, uint32 *native_types, uint32 *native_offsets, uint32 *native_sizes)
{
    uint32 index;
    uint32 cursor;
    uint32 value;
    cursor = directory;
    for (index = 0; (sint32)index < count; ++index)
    {
        value = func_8003cd10(directory, index);
        if (native_types != 0)
            native_types[index] = value;
        else
            w_u32(types, value);
        value = r_u32(cursor + 36);
        types += 4;
        if (native_offsets != 0)
            native_offsets[index] = value;
        else
            w_u32(offsets, value);
        value = r_u32(cursor + 40);
        offsets += 4;
        cursor += 40;
        if (native_sizes != 0)
            native_sizes[index] = value;
        else
            w_u32(sizes, value);
        sizes += 4;
    }
}

void func_8003a430(sint32 count, uint32 types, uint32 offsets, uint32 sizes, uint32 directory)
{
    FUNCTION_MARKER(0x8003A430, "SLUS_004.64");
    resource_directory_core(count, types, offsets, sizes, directory, 0, 0, 0);
}

void read_resource_directory(sint32 count, uint32 *types, uint32 *offsets, uint32 *sizes, uint32 directory)
{
    resource_directory_core(count, 0, 0, 0, directory, types, offsets, sizes);
}

void func_800210b8(void)
{
    FUNCTION_MARKER(0x800210B8, "SLUS_004.64");
    VSyncCallback(func_800214b4);
    ResetGraph(1);
    SetGraphDebug(0);
    func_8001f0ac();
}

uint32 func_8001ec00(uint32 path, uint32 destination)
{
    sint32 bytes;
    sint32 count;
    uint32 next;
    uint32 models;
    uint32 index;
    uint32 slot;
    uint32 object;
    uint32 coordinate;
    uint32 scale;
    FUNCTION_MARKER(0x8001EC00, "SLUS_004.64");
    bytes = func_80036184(guest_c_string(path), destination, r_s32(0x800CF7FC));
    next = destination;
    if (bytes)
    {
        models = destination + 4;
        next += 4 * ((uint32)bytes + 4 - (uint32)(bytes % 4));
        func_8004c75c(models);
        count = r_s32(destination + 8);
        models = destination + 12;
        for (index = 0; (sint32)index < count; ++index)
        {
            slot = r_u32(0x800CF9CC);
            object = 0x800DDD44 + 16 * slot;
            coordinate = 0x800D8748 + 80 * slot;
            w_u32(object + 4, coordinate);
            w_u32(coordinate + 68, 0x800D7BA4 + 40 * slot);
            coordinate = r_u32(object + 4);
            w_u32(coordinate + 32, 0);
            w_u32(coordinate + 28, 0);
            w_u32(coordinate + 24, 0);
            coordinate = r_u32(object + 4);
            scale = r_u32(coordinate + 68);
            w_u32(scale + 8, 4096);
            w_u32(scale + 4, 4096);
            w_u32(scale, 4096);
            coordinate = r_u32(object + 4);
            w_u32(coordinate + 72, 0);
            func_8004d864(models, object, index);
            slot = r_u32(0x800CF9CC);
            w_u32(object, 0);
            w_u32(object + 12, slot);
            func_8001b21c(object);
            coordinate = r_u32(object + 4);
            w_u32(coordinate, 0);
            slot = r_u32(0x800CF9CC);
            w_u32(0x800CF9CC, slot + 1);
        }
    }
    return next;
}

uint32 func_8001ed6c(uint32 bank, uint32 path, uint32 destination)
{
    sint32 bytes;
    sint32 count;
    uint32 next;
    uint32 models;
    uint32 index;
    uint32 object;
    uint32 coordinate;
    uint32 scale;
    FUNCTION_MARKER(0x8001ED6C, "SLUS_004.64");
    bytes = func_80036184(guest_c_string(path), destination, r_s32(0x800CF800));
    next = destination;
    if (bytes)
    {
        models = destination + 4;
        next += 4 * ((uint32)bytes + 4 - (uint32)(bytes % 4));
        func_8004c75c(models);
        count = r_s32(destination + 8);
        models = destination + 12;
        for (index = 0; (sint32)index < count; ++index)
        {
            object = 0x800EA2E4 + 128 * bank + 16 * index;
            coordinate = 0x800E2CA4 + 640 * bank + 80 * index;
            w_u32(object + 4, coordinate);
            w_u32(coordinate + 68, 0x800DF1C4 + 320 * bank + 40 * index);
            coordinate = r_u32(object + 4);
            w_u32(coordinate + 32, 0);
            w_u32(coordinate + 28, 0);
            w_u32(coordinate + 24, 0);
            coordinate = r_u32(object + 4);
            scale = r_u32(coordinate + 68);
            w_u32(scale + 8, 4096);
            w_u32(scale + 4, 4096);
            w_u32(scale, 4096);
            coordinate = r_u32(object + 4);
            w_u32(coordinate + 72, 0);
            func_8004d864(models, object, index);
            w_u32(object, 0);
            w_u32(object + 12, index);
            func_8001b21c(object);
            coordinate = r_u32(object + 4);
            w_u32(coordinate, 0);
        }
    }
    return next;
}

void func_800392e0(void)
{
    FUNCTION_MARKER(0x800392E0, "SLUS_004.64");
    SsUtSetReverbType(-4);
    SpuSetReverb(1);
    SsUtSetReverbDepth(15, 15);
    SsSetRVol(36, 36);
}

uint32 func_8003cd10(uint32 directory, uint32 index)
{
    uint32 cursor;
    uint32 value;
    uint32 character;
    char extension[3];
    FUNCTION_MARKER(0x8003CD10, "SLUS_004.64");
    cursor = directory + 40 * index + 4;
    if (r_u8(cursor) != '.')
    {
        ++cursor;
        do
        {
            value = r_u8(cursor);
            ++cursor;
        }
        while (value != '.');
        --cursor;
    }
    ++cursor;
    /* Inline the audited game copy into a native stack buffer */
    for (character = 0; character < 3; ++character)
    {
        value = r_u8(cursor);
        if (value - 97 < 26)
            value += 224;
        extension[character] = (char)(uint8)value;
        ++cursor;
    }
    return strncmp(extension, (const char *)psx_addr(0x800CFC24, 3), 3) == 0;
}

void func_8001aafc(void)
{
    uint16 value;
    FUNCTION_MARKER(0x8001AAFC, "SLUS_004.64");
    value = r_u16(0x800CF952);
    w_u16(0x800CF950, value);
    value = r_u16(0x800CF950);
    func_80047dec(value);
    w_u32(0x800EF5EC, 0);
    w_u32(0x800EF5F0, (uint32)-5000);
    w_u32(0x800EF5F4, (uint32)-10000);
    w_u32(0x800EF5F8, 0);
    w_u32(0x800EF5FC, 0);
    w_u32(0x800EF600, 0);
    w_u32(0x800EF604, 0);
    w_u32(0x800EF608, 0);
    func_8004cf4c(0x800EF5EC);
    w_u32(0x800F0290, 0);
    w_u32(0x800F0294, 0);
    w_u32(0x800F0298, 0);
    w_u32(0x800F029C, 0);
    w_u32(0x800F02A0, 0);
    w_u32(0x800F02A4, 0);
    w_u32(0x800F02A8, 0);
    w_u32(0x800F02AC, 0);
    func_8004cf4c(0x800F0290);
    func_8004e4bc(-2000);
}

void func_80021340(void)
{
    FUNCTION_MARKER(0x80021340, "SLUS_004.64");
    func_80020e78(20, 1);
    VSyncCallback(func_800214b4);
    ResetGraph(1);
    SetGraphDebug(0);
    w_u32(0x800CF7C0, 1);
}

void func_8002141c(void)
{
    FUNCTION_MARKER(0x8002141C, "SLUS_004.64");
    if (r_u32(0x800CF7CC))
    {
        if (r_u32(0x800CF8DC) != 100)
        {
            func_80020e78(21, 2);
            if (r_u32(0x800CF8DC) != 100)
                func_80020e78(1, 2);
        }
        func_800210b8();
    }
}

uint32 func_800240c0(void)
{
    uint32 input;
    uint32 position;
    uint32 next;
    uint32 result;
    FUNCTION_MARKER(0x800240C0, "SLUS_004.64");
    input = func_80012658();
    if (r_u32(0x800CFAB4) != input && input)
    {
        position = r_u32(0x800CFAB8);
        if (r_u32(0x800B294C + 4 * position) == input)
        {
            ++position;
            w_u32(0x800CFAB8, position);
            next = r_u32(0x800B294C + 4 * position);
            if (next == 0xFFFFFFFF)
            {
                func_8002372c(39);
                func_80028af4();
                VSync(120);
                func_800378e8();
                w_u32(0x800CFAB8, 0);
                w_u32(0x800CFAB4, next);
                w_u32(0x800CF7A4, 1);
            }
            w_u32(0x800CFAB4, input);
        }
        else
        {
            w_u32(0x800CFAB8, 0);
            w_u32(0x800CFAB4, 0xFFFFFFFF);
        }
    }
    result = r_u32(0x800CF7C0);
    if (result)
        result = func_800241b0();
    return result;
}

uint32 func_800241b0(void)
{
    uint32 input;
    uint32 position;
    uint32 next;
    uint32 result;
    FUNCTION_MARKER(0x800241B0, "SLUS_004.64");
    input = func_80012658();
    result = r_u32(0x800CFABC);
    if (result != input && input)
    {
        position = r_u32(0x800CFAC0);
        result = 0xFFFFFFFF;
        if (r_u32(0x800B2990 + 4 * position) == input)
        {
            ++position;
            w_u32(0x800CFAC0, position);
            next = r_u32(0x800B2990 + 4 * position);
            if (next == 0xFFFFFFFF)
            {
                func_8002372c(39);
                position = r_u32(0x800CFAC0);
                w_u32(0x800CFABC, input);
                w_u32(0x800EDFAC, 0);
                w_u32(0x800CFAC0, position + 1);
                result = 1;
                w_u32(0x800EDFE0, result);
            }
            else
            {
                position = r_u32(0x800CFAC0);
                next = r_u32(0x800B2990 + 4 * position);
                result = 0xFFFFFFFE;
                if (next == result)
                {
                    func_8002372c(2);
                    w_u32(0x800CFAC0, 0);
                    w_u32(0x800CFABC, 0xFFFFFFFF);
                    w_u32(0x800EDFE0, 2);
                    result = 500;
                    w_u32(0x800EDFAC, result);
                }
            }
            w_u32(0x800CFABC, input);
        }
        else
        {
            w_u32(0x800CFAC0, 0);
            w_u32(0x800CFABC, result);
        }
    }
    return result;
}

void func_80028af4(void)
{
    PSX_RECT rectangle;
    sint32 index;
    sint32 font;
    FUNCTION_MARKER(0x80028AF4, "SLUS_004.64");
    if (GsGetActiveBuff())
        GsSwapDispBuff();
    FntLoad(960, 256);
    font = FntOpen(-144, -104, 320, 200, 0, 512);
    SetDumpFnt(font);
    rectangle.x = 38;
    rectangle.y = 298;
    rectangle.w = 244;
    rectangle.h = 124;
    ClearImage(&rectangle, 144, 144, 144);
    DrawSync(0);
    for (index = 0; index < 120; ++index)
    {
        rectangle.x = 40;
        rectangle.y = (sint16)(index + 60);
        rectangle.w = 240;
        rectangle.h = 1;
        ClearImage(&rectangle, 0, 0, (uint8)index);
        DrawSync(0);
        rectangle.x = 40;
        rectangle.y = (sint16)(index + 300);
        rectangle.w = 240;
        rectangle.h = 1;
        ClearImage(&rectangle, 0, 0, (uint8)index);
        DrawSync(0);
    }
    func_80037934(guest_c_string(0x8007D7A0), -80, -20, 280, 200);
}

void func_8001ab94(void)
{
    uint32 fog[3];
    FUNCTION_MARKER(0x8001AB94, "SLUS_004.64");
    fog[0] = r_u32(0x800107F4);
    fog[1] = r_u32(0x800107F8);
    fog[2] = r_u32(0x800107FC);
    w_u32(0x800EF694, (uint32)-180);
    w_u32(0x800EF698, 100);
    w_u32(0x800EF69C, (uint32)-255);
    w_u8(0x800EF6A0, 100);
    w_u8(0x800EF6A1, 100);
    w_u8(0x800EF6A2, 100);
    GsSetFlatLight(0, (const GsF_LIGHT *)psx_addr(0x800EF694, 16));
    w_u32(0x800EF6A4, 255);
    w_u32(0x800EF6A8, (uint32)-50);
    w_u32(0x800EF6AC, 230);
    w_u8(0x800EF6B0, 100);
    w_u8(0x800EF6B1, 100);
    w_u8(0x800EF6B2, 100);
    GsSetFlatLight(1, (const GsF_LIGHT *)psx_addr(0x800EF6A4, 16));
    w_u32(0x800EF6B4, (uint32)-50);
    w_u32(0x800EF6B8, 50);
    w_u32(0x800EF6BC, 50);
    w_u8(0x800EF6C0, 144);
    w_u8(0x800EF6C1, 144);
    w_u8(0x800EF6C2, 144);
    GsSetFlatLight(2, (const GsF_LIGHT *)psx_addr(0x800EF6B4, 16));
    GsSetAmbient(900, 900, 900);
    GsSetLightMode(0);
    GsSetFogParam(fog);
}

void func_800177a8(void)
{
    uint32 index;
    uint32 path;
    const char *name;
    FUNCTION_MARKER(0x800177A8, "SLUS_004.64");
    for (index = 0; ; ++index)
    {
        path = r_u32(0x8007DB08 + 4 * index);
        name = guest_c_string(path);
        if (strcmp(name, guest_c_string(0x800CF7C4)) == 0)
            break;
        path = r_u32(0x8007DB08 + 4 * index);
        func_80039a00(guest_c_string(path), 0x800D779C + 24 * index);
    }
    for (index = 0; ; ++index)
    {
        path = r_u32(0x8007DB7C + 4 * index);
        name = guest_c_string(path);
        if (strcmp(name, guest_c_string(0x800CF7C4)) == 0)
            break;
        path = r_u32(0x8007DB7C + 4 * index);
        func_80039a00(guest_c_string(path), 0x800DD780 + 24 * index);
    }
}

void func_800239e4(uint32 mode)
{
    uint32 path;
    uint32 destination;
    uint32 source;
    uint32 bytes;
    uint32 header_bytes;
    uint32 body_bytes;
    sint32 source_mode;
    uint32 header;
    uint32 body;
    uint32 bank;
    uint32 table;
    FUNCTION_MARKER(0x800239E4, "SLUS_004.64");
    if (r_s16(0x800CF81C) != -1)
    {
        func_800237e8();
        VSync(0);
        func_80039204(r_s16(0x800CF81C));
    }
    path = r_u32(0x8007DAE0 + 4 * mode);
    destination = r_u32(0x800CFA20);
    source_mode = r_s32(0x800CF7E8);
    bytes = (uint32)func_80036184(guest_c_string(path), destination, source_mode);
    header_bytes = bytes;
    destination = r_u32(0x800CFA34);
    source = r_u32(0x800CFA20);
    memcpy(psx_addr(destination, bytes), psx_addr(source, bytes), bytes);
    path = r_u32(0x8007DAF4 + 4 * mode);
    destination = r_u32(0x800CFA20);
    source_mode = r_s32(0x800CF7E8);
    bytes = (uint32)func_80036184(guest_c_string(path), destination, source_mode);
    destination = r_u32(0x800CFA38);
    source = r_u32(0x800CFA20);
    memcpy(psx_addr(destination, bytes), psx_addr(source, bytes), bytes);
    path = r_u32(0x8007DACC + 4 * mode);
    destination = r_u32(0x800CFA20);
    source_mode = r_s32(0x800CF7E8);
    body_bytes = (uint32)func_80036184(guest_c_string(path), destination, source_mode);
    header = r_u32(0x800CFA34);
    body = r_u32(0x800CFA20);
    bank = func_800391a0((uint8 *)psx_addr(header, header_bytes), (uint8 *)psx_addr(body, body_bytes));
    body = r_u32(0x800CFA38);
    table = r_u32(0x800CFA3C);
    w_u16(0x800CF81C, (uint16)bank);
    func_80039320(body, table);
    ResetCallback();
    func_800392e0();
    VSyncCallback(func_800214b4);
}

char *func_8003cbb0(sint32 number, char *destination)
{
    const char *pattern;
    char digits[3];
    uint32 index;
    uint32 divisor;
    uint32 remainder;
    sint32 quotient;
    char *cursor;
    uint32 value;
    FUNCTION_MARKER(0x8003CBB0, "SLUS_004.64");
    pattern = guest_c_string(0x8007D820);
    strcpy(destination, pattern);
    remainder = (uint32)number;
    for (index = 0; index < 3; ++index)
    {
        divisor = func_8003d378(10, (sint32)(2 - index));
        quotient = geometry_divide(remainder, divisor);
        digits[index] = (char)(uint8)((uint32)quotient + 48);
        remainder -= (uint32)quotient * divisor;
    }
    cursor = destination;
    if ((uint8)*cursor != '?')
    {
        ++cursor;
        do
        {
            value = (uint8)*cursor;
            ++cursor;
        }
        while (value != '?');
        --cursor;
    }
    strncpy(cursor, digits, 3);
    return cursor;
}

uint32 read_slice_blocks(uint32 location, uint32 destination, uint32 first, uint32 last, uint32 offset, uint32 final_bytes, uint32 *callback_argument)
{
    uint32 difference;
    uint32 bytes;
    difference = last - first;
    func_80039ccc(location, destination, difference + 1);
    bytes = final_bytes + 2048 - offset + ((difference - 1) << 11);
    *callback_argument = func_80041820(destination, destination + offset, bytes);
    return bytes;
}

uint32 func_80039be4(uint32 location, uint32 destination, uint32 first, uint32 last, uint32 offset, uint32 final_bytes)
{
    uint32 callback_argument;
    FUNCTION_MARKER(0x80039BE4, "SLUS_004.64");
    return read_slice_blocks(location, destination, first, last, offset, final_bytes, &callback_argument);
}

uint32 func_8003ceec(void)
{
    uint16 page;
    FUNCTION_MARKER(0x8003CEEC, "SLUS_004.64");
    w_u32(0x800E9A78, 0x0A000000);
    page = GetTPage(2, 0, 320, 0);
    w_u16(0x800E9A84, page);
    w_u8(0x800E9A86, 0);
    w_u8(0x800E9A87, 0);
    w_u16(0x800E9A80, 256);
    w_u16(0x800E9A82, 240);
    w_u16(0x800E9A7C, (uint16)-160);
    w_u16(0x800E9A7E, (uint16)-120);
    func_8003aa84(0x800E9A78);
    w_u32(0x800EBE04, 0x0A000000);
    page = GetTPage(2, 0, 576, 0);
    w_u16(0x800EBE10, page);
    w_u8(0x800EBE12, 0);
    w_u8(0x800EBE13, 0);
    w_u16(0x800EBE0C, 64);
    w_u16(0x800EBE0E, 240);
    w_u16(0x800EBE08, 96);
    w_u16(0x800EBE0A, (uint16)-120);
    func_8003aa84(0x800EBE04);
    w_u32(0x800EC1D4, 0x60000000);
    w_u16(0x800EC1D8, (uint16)-160);
    w_u16(0x800EC1DA, (uint16)-120);
    w_u16(0x800EC1DC, 320);
    w_u16(0x800EC1DE, 240);
    return 320;
}

void func_8003d3a0(void)
{
    FUNCTION_MARKER(0x8003D3A0, "SLUS_004.64");
    GsClearOt(0, 0, psx_addr(0x800D003C, 20));
    GsClearOt(0, 0, psx_addr(0x800D0050, 20));
}

void func_8003d3e0(uint32 level)
{
    uint32 value;
    uint32 buffer;
    FUNCTION_MARKER(0x8003D3E0, "SLUS_004.64");
    value = level << 3;
    if (value == 256)
        value = 255;
    w_u8(0x800EC1E0, (uint8)value);
    w_u8(0x800EC1E1, (uint8)value);
    w_u8(0x800EC1E2, (uint8)value);
    buffer = r_u32(0x800CFD38);
    GsSortBoxFill(psx_addr(0x800EC1D4, 16), psx_addr(0x800D003C + 20 * buffer, 20), 0);
}

void func_8003d450(void)
{
    uint32 buffer;
    uint32 work;
    FUNCTION_MARKER(0x8003D450, "SLUS_004.64");
    DrawSync(0);
    VSync(2);
    GsSwapDispBuff();
    buffer = r_u32(0x800CFD38);
    GsSortClear(0, 0, 0, psx_addr(0x800D003C + 20 * buffer, 20));
    ResetGraph(1);
    buffer = r_u32(0x800CFD38);
    func_8004e5a4(0x800D003C + 20 * buffer);
    buffer = GsGetActiveBuff();
    work = r_u32(0x800CFD30 + 4 * buffer);
    w_u32(0x800CFD38, buffer);
    func_8004e594(work);
    buffer = r_u32(0x800CFD38);
    GsClearOt(0, 0, psx_addr(0x800D003C + 20 * buffer, 20));
}

static void copy_save_state(uint32 destination, uint32 source)
{
    uint32 offset;
    uint32 word0;
    uint32 word1;
    uint32 word2;
    uint32 word3;
    for (offset = 0; offset < 0x15F0; offset += 16)
    {
        word0 = r_u32(source + offset);
        word1 = r_u32(source + offset + 4);
        word2 = r_u32(source + offset + 8);
        word3 = r_u32(source + offset + 12);
        w_u32(destination + offset, word0);
        w_u32(destination + offset + 4, word1);
        w_u32(destination + offset + 8, word2);
        w_u32(destination + offset + 12, word3);
    }
    word0 = r_u32(source + offset);
    word1 = r_u32(source + offset + 4);
    word2 = r_u32(source + offset + 8);
    w_u32(destination + offset, word0);
    w_u32(destination + offset + 4, word1);
    w_u32(destination + offset + 8, word2);
}

void func_8001f4c4(uint32 bank, uint32 value)
{
    uint32 selected;
    uint32 data;
    uint32 buffer;
    uint32 path;
    sint32 source_mode;
    sint32 bytes;
    sint32 count;
    uint32 total;
    uint32 models;
    uint32 model;
    uint32 index;
    uint32 object;
    uint32 coordinate;
    uint32 scale;
    uint32 parent;
    FUNCTION_MARKER(0x8001F4C4, "SLUS_004.64");
    selected = value;
    if (r_u32(0x800EDFE0) == 1)
        selected = r_u32(0x8007D878 + 4 * value);
    if (r_u32(0x80081498 + 4 * bank) == selected)
        return;
    func_8001eff8();
    func_80017a74();
    data = r_u32(0x800B1C80 + 4 * bank);
    buffer = r_u32(0x800CF9FC);
    source_mode = r_s32(0x800CF7F4);
    path = r_u32(0x8007D830 + 4 * selected);
    bytes = func_80036184(guest_c_string(path), buffer, source_mode);
    if (bytes <= 0)
        return;
    buffer = r_u32(0x800CF9FC);
    memcpy(psx_addr(data, (uint32)bytes), psx_addr(buffer, (uint32)bytes), (uint32)bytes);
    total = r_u32(0x800CFE14);
    w_u32(0x800CFE14, total + (uint32)bytes + 4 - ((uint32)bytes & 3));
    models = data + 4;
    w_u32(0x800EC400 + 4 * bank, models);
    model = r_u32(0x800EC400 + 4 * bank);
    func_8004c75c(model);
    count = r_s32(data + 8);
    models = data + 12;
    func_80035940(0x80082104 + 12 * bank, 0x800EA704 + 560 * bank, 0x800E40A4 + 2800 * bank, 0x800DFBC4 + 1400 * bank, (uint32)count);
    for (index = 0; (sint32)index < count; ++index)
    {
        object = 0x800EA704 + 560 * bank + 16 * index;
        coordinate = 0x800E40A4 + 2800 * bank + 80 * index;
        w_u32(object + 4, coordinate);
        w_u32(coordinate + 68, 0x800DFBC4 + 1400 * bank + 40 * index);
        if (r_u32(0x80081498 + 4 * bank) == 0xFFFFFFFF)
        {
            coordinate = r_u32(object + 4);
            w_u32(coordinate + 32, 0);
            w_u32(coordinate + 28, 0);
            w_u32(coordinate + 24, 0);
            coordinate = r_u32(object + 4);
            scale = r_u32(coordinate + 68);
            w_u32(scale + 8, 4096);
            w_u32(scale + 4, 4096);
            w_u32(scale, 4096);
        }
        coordinate = r_u32(object + 4);
        parent = r_u32(0x800DDD48 + 16 * bank);
        w_u32(coordinate + 72, parent);
        func_8004d864(models, object, index);
        if (r_u32(0x80081498 + 4 * bank) == 0xFFFFFFFF)
        {
            func_8001b21c(object);
            coordinate = r_u32(object + 4);
            w_u32(coordinate, 0);
        }
        w_u32(object, 0);
        w_u32(object + 12, index + 1);
    }
    func_8001b21c(0x800DDD44 + 16 * bank);
    coordinate = r_u32(0x800DDD48 + 16 * bank);
    w_u32(coordinate, 0);
    w_u32(0x80082108 + 12 * bank, index);
    w_u32(0x80081498 + 4 * bank, selected);
    w_u32(0x800EE048 + 4 * bank, selected);
    func_80014ffc();
}

void func_8001ef00(void)
{
    uint32 value;
    sint32 cursor;
    FUNCTION_MARKER(0x8001EF00, "SLUS_004.64");
    func_80017a74();
    value = r_u32(0x800CFA20);
    w_u32(0x800CF9DC, 0);
    w_u32(0x800CF9EC, value);
    func_8001f174(51);
    cursor = r_s32(0x800CF9EC);
    value = (uint32)cursor + 4 - (uint32)(cursor % 4);
    w_u32(0x800CF9EC, value);
    w_u32(0x800CFA24, value);
    value = r_u32(0x800CF9DC);
    w_u32(0x800CF9E0, value);
    func_8001f174(52);
    value = r_u32(0x800CF9EC);
    w_u32(0x800CFA14, value);
    value = r_u32(0x800CF9DC);
    w_u32(0x800CF9E4, value);
}

static void start_stream_descriptor(uint32 descriptor, uint32 channel, uint32 duration, uint32 loop, uint32 volume, uint32 callback)
{
    uint32 word0;
    uint32 word1;
    uint32 word2;
    uint32 word3;
    uint32 word4;
    uint32 word5;
    word4 = r_u32(descriptor + 16);
    word5 = r_u32(descriptor + 20);
    word0 = r_u32(descriptor);
    word1 = r_u32(descriptor + 4);
    word2 = r_u32(descriptor + 8);
    word3 = r_u32(descriptor + 12);
    func_800385f8(word0, word1, word2, word3, word4, word5, 1, channel, duration, loop, volume, volume, callback);
}

void func_800178b0(sint32 value, uint32 mode)
{
    uint32 previous;
    sint32 number;
    sint32 group;
    sint32 channel;
    uint32 duration;
    uint32 callback;
    FUNCTION_MARKER(0x800178B0, "SLUS_004.64");
    if (!r_u32(0x800CF7CC) || r_u32(0x800CF860))
        return;
    if (!value)
    {
        func_80038854();
        w_u32(0x800CF8B4, 0);
        return;
    }
    previous = r_u32(0x800CF8B4);
    if (previous == (uint32)value)
        return;
    number = (sint32)((uint32)value - 1);
    if (previous)
        func_80038854();
    w_u32(0x800CF8B4, (uint32)value);
    w_u32(0x800CF8B8, (uint32)value);
    group = number / 8;
    channel = number % 8;
    callback = 0;
    if (!mode)
    {
        func_800315ec();
        func_80022a08();
        if (!r_u32(0x800CFA90))
            callback = 0x80012BFC;
    }
    duration = r_u32(0x800B1C9C + 32 * (uint32)group + 4 * (uint32)channel);
    start_stream_descriptor(0x800DD780 + 24 * (uint32)group, (uint32)channel, duration, 1, 80, callback);
}

void func_80017aa0(sint32 value, uint32 mode)
{
    sint32 number;
    sint32 group;
    sint32 channel;
    uint32 duration;
    uint32 callback;
    FUNCTION_MARKER(0x80017AA0, "SLUS_004.64");
    if (!r_u32(0x800CF7CC) || r_u32(0x800CF860))
        return;
    if (!value)
    {
        func_80038854();
        w_u32(0x800CF8B4, 0);
        return;
    }
    number = (sint32)((uint32)value - 1);
    if (r_u32(0x800CF8B4))
        func_80038854();
    w_u32(0x800CF8B4, (uint32)value + 100);
    group = number / 32;
    channel = number % 32;
    duration = r_u32(0x800B1CDC + 128 * (uint32)group + 4 * (uint32)channel);
    if (!duration)
        return;
    if (r_u32(0x800CF7A4) && (func_80012658() & 0x100))
    {
        start_stream_descriptor(0x800D779C + 24 * (uint32)group, (uint32)channel, 20000, 0, 96, 0);
        while (func_80012658())
            ;
        func_80038854();
        return;
    }
    duration = r_u32(0x800B1CDC + 128 * (uint32)group + 4 * (uint32)channel);
    callback = mode ? 0 : 0x80012BFC;
    start_stream_descriptor(0x800D779C + 24 * (uint32)group, (uint32)channel, duration, 0, 96, callback);
}

void func_8001b690(void)
{
    FUNCTION_MARKER(0x8001B690, "SLUS_004.64");
    w_u32(0x800EBB78, (uint32)-350);
    w_u32(0x800EBB7C, 0);
    w_u32(0x800EBB80, (uint32)-350);
    w_u32(0x800EBBB0, 350);
    w_u32(0x800EBBB4, 0);
    w_u32(0x800EBBB8, 350);
}

sint32 func_80023b2c(sint32 index)
{
    sint32 previous;
    FUNCTION_MARKER(0x80023B2C, "SLUS_004.64");
    previous = r_s32(0x800CF958);
    if (previous == index)
        return 0;
    if (index < 3)
    {
        if (previous < 3)
        {
            w_u32(0x800CF958, (uint32)index);
            return 0;
        }
        func_80023af4(2);
    }
    else
        func_80023af4(index);
    w_u32(0x800CF958, (uint32)index);
    return 1;
}

void func_80023af4(sint32 mode)
{
    FUNCTION_MARKER(0x80023AF4, "SLUS_004.64");
    func_80017a74();
    func_800239e4(4 - (uint32)mode);
    func_8001ef00();
}

uint32 func_80020a48(uint32 object, uint32 position)
{
    uint32 mode;
    uint32 coordinate;
    uint32 value;
    uint32 base;
    uint32 offset;
    FUNCTION_MARKER(0x80020A48, "SLUS_004.64");
    if (object == r_u32(0x800EE7EC))
        w_u32(0x800CF908, position);
    mode = r_u32(0x800EDFD0);
    coordinate = r_u32(0x800DDD48 + 16 * object);
    value = r_u32(0x80081938 + 4 * position);
    value -= mode ? 850 : 1700;
    w_u32(coordinate + 28, value);
    coordinate = r_u32(0x800DDD48 + 16 * object);
    base = r_u32(0x800CF828);
    w_u32(coordinate, 0);
    offset = 44 * (object + base - 1);
    w_u32(0x8007F08C + offset, (uint32)1 << (position & 31));
    func_8001b21c(0x800DDD44 + 16 * object);
    offset = 44 * (object - 1);
    w_u32(0x800EE72C + offset, position);
    return offset;
}

void func_8001f13c(void)
{
    sint32 resource;
    FUNCTION_MARKER(0x8001F13C, "SLUS_004.64");
    resource = r_s32(0x800CFA98);
    if (resource > 0)
    {
        w_u32(0x800CFA98, 0);
        func_8001f028(resource);
    }
}

void func_80022320(uint32 object, uint32 action, uint32 mode)
{
    FUNCTION_MARKER(0x80022320, "SLUS_004.64");
    if (!action)
        return;
    func_80024090();
    if (r_u32(0x800CF8BC + 4 * object) && r_s32(0x800EE7E8) > 0)
        func_80032d68(object, 3);
    func_800223b8(object, action, mode);
}

uint32 func_8002dbe4(uint8 *destination, const uint32 *source)
{
    uint32 index;
    uint32 row;
    uint32 value;
    FUNCTION_MARKER(0x8002DBE4, "SLUS_004.64");
    for (index = 0; index < 17; ++index)
    {
        *destination = 0;
        ++destination;
    }
    for (row = 0; row < 16; ++row)
    {
        for (index = 0; index < 8; ++index)
        {
            value = *source;
            *destination = (uint8)((value >> (4 * index)) & 7);
            ++destination;
        }
        for (index = 0; index < 9; ++index)
        {
            *destination = 0;
            ++destination;
        }
        ++source;
    }
    return 0;
}

void func_800413a8(void)
{
    uint32 buffer;
    FUNCTION_MARKER(0x800413A8, "SLUS_004.64");
    buffer = r_u32(0x800CFD48);
    func_8004e594(0x800D00C4 + 160 * buffer);
    buffer = r_u32(0x800CFD48);
    GsClearOt(0, 0, psx_addr(0x800D0204 + 20 * buffer, 20));
}

void func_800411c8(void)
{
    uint32 value;
    uint32 delta;
    uint32 buffer;
    FUNCTION_MARKER(0x800411C8, "SLUS_004.64");
    func_80041410();
    func_800413a8();
    value = r_u32(0x800CFD58);
    delta = r_u32(0x800CFD70);
    w_u32(0x800CFD58, value + delta);
    func_8004132c();
    value = r_u32(0x800CFD58);
    func_80041258((sint32)value);
    ResetGraph(1);
    buffer = r_u32(0x800CFD48);
    func_8004e5a4(0x800D0204 + 20 * buffer);
}

void func_80041258(sint32 value)
{
    uint32 offset;
    uint32 first;
    uint32 second;
    uint32 buffer;
    FUNCTION_MARKER(0x80041258, "SLUS_004.64");
    for (offset = 0; offset < 72; offset += 36)
    {
        first = 0x800D024C + offset;
        buffer = r_u32(0x800CFD48);
        GsSortFastSprite(psx_addr(first, 36), psx_addr(0x800D0204 + 20 * buffer, 20), 1);
        second = 0x800D0294 + offset;
        buffer = r_u32(0x800CFD48);
        GsSortFastSprite(psx_addr(second, 36), psx_addr(0x800D0204 + 20 * buffer, 20), 1);
        func_800414bc((uint32)value, first);
        func_800414bc((uint32)value, second);
    }
}

uint32 func_80041114(void)
{
    sint32 mode;
    uint32 buffer;
    FUNCTION_MARKER(0x80041114, "SLUS_004.64");
    mode = r_s32(0x800CFC5C);
    if (mode == 1)
    {
        func_800411c8();
        VSync(0);
    }
    else if (mode == 2)
    {
        func_8004df4c(0, 0, 0, 240);
        w_u32(0x800CFC5C, 0);
    }
    else if (mode == 3)
    {
        ResetGraph(1);
        buffer = r_u32(0x800CFD48);
        func_8004e5a4(0x800D0204 + 20 * buffer);
        VSync(0);
    }
    return r_u32(0x800CFC5C);
}

sint32 func_80020730(void)
{
    sint32 result;
    sint32 count;
    uint32 index;
    uint32 offset;
    sint32 first;
    sint32 second;
    FUNCTION_MARKER(0x80020730, "SLUS_004.64");
    result = r_s32(0x800CFEB4);
    if (result <= 0)
        return result;
    count = r_s32(0x800CFEB4);
    index = 0;
    do
    {
        offset = 56 * index;
        result = r_s32(0x80080194 + offset);
        if (result == -1)
            return result;
        first = r_s32(0x800801BC + offset);
        second = r_s32(0x800801C4 + offset);
        if (second < first)
        {
            w_u32(0x800801BC + offset, (uint32)second);
            w_u32(0x800801C4 + offset, (uint32)first);
        }
        first = r_s32(0x800801C0 + offset);
        second = r_s32(0x800801C8 + offset);
        ++index;
        if (second < first)
        {
            w_u32(0x800801C0 + offset, (uint32)second);
            w_u32(0x800801C8 + offset, (uint32)first);
        }
        result = (sint32)index < count;
    }
    while (result);
    return result;
}

sint32 func_80023c18(void)
{
    uint32 index;
    uint32 end;
    uint32 mask;
    uint32 offset;
    uint32 count;
    FUNCTION_MARKER(0x80023C18, "SLUS_004.64");
    index = func_80023bc0();
    w_u32(0x800CF828, index);
    if ((sint32)index < (sint32)(index + 4))
    {
        mask = (uint32)1 << (r_u32(0x800CF908) & 31);
        end = r_u32(0x800CF828) + 4;
        do
        {
            offset = 44 * index;
            w_u32(0x8007F064 + offset, 0);
            w_u32(0x8007F068 + offset, 2);
            w_u32(0x8007F06C + offset, (uint32)-400);
            w_u32(0x8007F070 + offset, 0);
            w_u32(0x8007F074 + offset, 400);
            w_u32(0x8007F078 + offset, 0);
            w_u32(0x8007F07C + offset, 0);
            w_u32(0x8007F080 + offset, 0);
            w_u32(0x8007F084 + offset, 0);
            w_u32(0x8007F088 + offset, 0);
            w_u32(0x8007F08C + offset, mask);
            count = r_u32(0x800CFD94);
            ++index;
            w_u32(0x800CFD94, count + 1);
        }
        while ((sint32)index < (sint32)end);
    }
    end = r_u32(0x800CF828) + 4;
    w_u32(0x8007F064 + 44 * end, 0xFFFFFFFF);
    return -1;
}

uint32 func_8002dc84(uint32 destination, uint32 source, sint32 width)
{
    uint32 row;
    uint32 column;
    uint32 digit;
    uint32 packed;
    uint32 value;
    FUNCTION_MARKER(0x8002DC84, "SLUS_004.64");
    for (row = 0; row < 20; ++row)
    {
        for (column = 0; (sint32)column < width; ++column)
        {
            packed = 0;
            w_u32(destination, 0);
            for (digit = 0; digit < 8; ++digit)
            {
                value = r_u8(source);
                ++source;
                packed |= (value & 15) << (4 * digit);
                w_u32(destination, packed);
            }
            destination += 4;
        }
    }
    return 0;
}

void func_8001f028(sint32 resource)
{
    uint32 value;
    sint32 cursor;
    FUNCTION_MARKER(0x8001F028, "SLUS_004.64");
    func_80017a74();
    value = r_u32(0x800CF9E8);
    w_u32(0x800CF9DC, value);
    cursor = r_s32(0x800CFA04);
    w_u32(0x800CFA98, (uint32)resource);
    w_u32(0x800CF9EC, (uint32)cursor);
    value = (uint32)cursor + 4 - (uint32)(cursor % 4);
    w_u32(0x800CF9EC, value);
    func_8003943c(0);
    func_8001f174((uint32)resource);
    func_8003943c(0);
    value = r_u32(0x800CF9EC);
    w_u32(0x800CFA08, value);
}

void func_800315ec(void)
{
    uint32 object;
    uint32 offset;
    uint32 cursor;
    uint32 value;
    uint32 expected;
    uint32 step;
    FUNCTION_MARKER(0x800315EC, "SLUS_004.64");
    for (object = 1; object < 5; ++object)
    {
        offset = 1040 * object;
        if (!r_u32(0x800DB6F0 + offset))
            continue;
        cursor = r_u32(0x800DB6FC + offset);
        value = r_u32(0x800DB2F0 + offset + 32 * cursor);
        if (value == 0xFFFFFFFF)
        {
            w_u32(0x800DB6FC + offset, 0);
            w_u32(0x800DB6F0 + offset, 0);
            w_u32(0x800818D8 + 4 * object, 0);
            w_u32(0x800818F8 + 4 * object, value);
            continue;
        }
        w_u32(0x800818B8 + 4 * object, value);
        if (func_8001b2f8(object, value, 0x800818D8 + 4 * object))
            continue;
        cursor = r_u32(0x800DB6FC + offset);
        value = r_u32(0x800DB2F0 + offset + 32 * cursor);
        if (value == 0xFFFFFFFF)
        {
            w_u32(0x800DB6FC + offset, 0);
            w_u32(0x800DB6F0 + offset, 0);
            w_u32(0x800818D8 + 4 * object, 0);
            w_u32(0x800818F8 + 4 * object, value);
            continue;
        }
        cursor = r_u32(0x800DB6FC + offset);
        expected = r_u32(0x800DB6F8 + offset);
        value = r_u32(0x800DB2F0 + offset + 32 * cursor);
        if (expected == value)
        {
            step = r_u32(0x800DB6F4 + offset);
            cursor -= step;
            w_u32(0x800DB6FC + offset, cursor);
            if ((sint32)cursor < 0)
                w_u32(0x800DB6FC + offset, cursor + 32);
        }
        else
        {
            cursor = r_u32(0x800DB6FC + offset);
            w_u32(0x800DB6FC + offset, cursor + 1);
            cursor = r_u32(0x800DB6FC + offset);
            if ((sint32)cursor >= 32)
                w_u32(0x800DB6FC + offset, cursor - 32);
        }
    }
}

void func_8001afcc(void)
{
    struct
    {
        sint16 value0;
        uint16 padding2;
        sint32 value4;
        uint8 red;
        uint8 green;
        uint8 blue;
        uint8 padding11;
    } fog;
    uint32 index;
    uint32 source;
    uint32 destination;
    uint32 value;
    sint32 red;
    sint32 green;
    sint32 blue;
    FUNCTION_MARKER(0x8001AFCC, "SLUS_004.64");
    for (index = 0; index < 3; ++index)
    {
        source = 0x80080F94 + 28 * index;
        destination = 0x800EF694 + 16 * index;
        if (r_u32(source))
        {
            value = r_u32(source + 4);
            w_u32(destination, value);
            value = r_u32(source + 8);
            w_u32(destination + 4, value);
            value = r_u32(source + 12);
            w_u32(destination + 8, value);
            value = r_u8(source + 16);
            w_u8(destination + 12, (uint8)value);
            value = r_u8(source + 20);
            w_u8(destination + 13, (uint8)value);
            value = r_u8(source + 24);
            w_u8(destination + 14, (uint8)value);
        }
        else
        {
            w_u32(destination, 0);
            w_u32(destination + 4, 0);
            w_u32(destination + 8, 1);
            w_u8(destination + 12, 1);
            w_u8(destination + 13, 1);
            w_u8(destination + 14, 1);
        }
        GsSetFlatLight((sint32)index, (const GsF_LIGHT *)psx_addr(destination, 16));
    }
    red = r_s32(0x800CFF94);
    green = r_s32(0x800CFF74);
    blue = r_s32(0x800CFF64);
    GsSetAmbient(red, green, blue);
    if (r_u32(0x800CFE9C))
    {
        value = r_u16(0x800CFE44);
        fog.value0 = (sint16)(uint16)(0 - value);
        fog.value4 = 0x01400000;
        fog.red = r_u8(0x800CFFAC);
        fog.green = r_u8(0x800CFF9C);
        fog.blue = r_u8(0x800CFF84);
        GsSetFogParam(&fog);
    }
    GsSetLightMode(r_s32(0x800CFE9C));
}

uint32 func_8001ea94(uint32 destination, uint32 source, sint32 bytes)
{
    uint32 next;
    uint32 models;
    sint32 count;
    uint32 index;
    uint32 slot;
    uint32 object;
    uint32 coordinate;
    uint32 scale;
    FUNCTION_MARKER(0x8001EA94, "SLUS_004.64");
    memmove(psx_addr(destination, (uint32)bytes), psx_addr(source, (uint32)bytes), (uint32)bytes);
    next = destination;
    if (bytes)
    {
        models = destination + 4;
        next += (uint32)bytes + 4 - (uint32)(bytes % 4) + 32;
        func_8004c75c(models);
        count = r_s32(destination + 8);
        models = destination + 12;
        w_u32(0x800CF8B0, (uint32)count);
        for (index = 0; (sint32)index < count; ++index)
        {
            slot = r_u32(0x800CF9CC);
            object = 0x800DDD44 + 16 * slot;
            coordinate = 0x800D8748 + 80 * slot;
            w_u32(object + 4, coordinate);
            w_u32(coordinate + 68, 0x800D7BA4 + 40 * slot);
            coordinate = r_u32(object + 4);
            w_u32(coordinate + 32, 0);
            w_u32(coordinate + 28, 0);
            w_u32(coordinate + 24, 0);
            coordinate = r_u32(object + 4);
            scale = r_u32(coordinate + 68);
            w_u32(scale + 8, 4096);
            w_u32(scale + 4, 4096);
            w_u32(scale, 4096);
            coordinate = r_u32(object + 4);
            w_u32(coordinate + 72, 0);
            func_8004d864(models, object, index);
            slot = r_u32(0x800CF9CC);
            w_u32(object + 12, slot);
            coordinate = r_u32(object + 4);
            w_u32(object, 0);
            w_u32(coordinate, 0);
            func_8001b21c(object);
            slot = r_u32(0x800CF9CC);
            w_u32(0x800CF9CC, slot + 1);
        }
    }
    return next;
}

void func_80022a08(void)
{
    uint32 object;
    uint32 coordinate;
    FUNCTION_MARKER(0x80022A08, "SLUS_004.64");
    for (object = 1; object < 5; ++object)
    {
        coordinate = r_u32(0x800DDD48 + 16 * object);
        w_u32(coordinate, 0);
        func_8001b21c(0x800DDD44 + 16 * object);
    }
}

sint32 func_800346a0(uint32 object)
{
    uint32 table;
    sint32 count;
    uint32 index;
    uint32 selected;
    FUNCTION_MARKER(0x800346A0, "SLUS_004.64");
    table = r_u32(0x800CFA5C + 4 * object);
    count = r_s32(table + 16);
    selected = 0;
    for (index = 0; (sint32)index < count; ++index)
    {
        if (r_u32(table + 32 + 4 * index))
        {
            w_u32(0x800EBE2C + 4 * selected, index);
            ++selected;
            w_u32(0x800816B8 + 4 * index, 1);
        }
        else
            w_u32(0x800816B8 + 4 * index, 0);
    }
    w_u32(0x800EBE2C + 4 * selected, 0xFFFFFFFF);
    return -1;
}

uint32 func_80035414(uint32 object)
{
    sint32 count;
    uint32 index;
    FUNCTION_MARKER(0x80035414, "SLUS_004.64");
    count = r_s32(0x800CFEA4);
    if (count > 0)
    {
        index = 0;
        do
        {
            if (r_u32(0x8007E064 + 64 * index) == 0xFFFFFFFF)
                break;
            if (func_800353ec(object, index))
                func_80034e4c(index);
            count = r_s32(0x800CFEA4);
            ++index;
        }
        while ((sint32)index < count);
    }
    return func_80021514();
}

uint32 func_800353ec(uint32 object, uint32 index)
{
    FUNCTION_MARKER(0x800353EC, "SLUS_004.64");
    return func_80032778((object << 6) + index + 200);
}

uint32 func_80032778(uint32 bit)
{
    uint32 word;
    FUNCTION_MARKER(0x80032778, "SLUS_004.64");
    word = r_u32(0x800EECD8 + 4 * (bit >> 5));
    return (word >> (bit & 31)) & 1;
}

uint32 func_80023b9c(uint32 first, uint32 second)
{
    uint32 sum;
    FUNCTION_MARKER(0x80023B9C, "SLUS_004.64");
    w_u32(0x800EDFE4, second);
    w_u32(0x800EDFE8, first);
    sum = first + second;
    w_u32(0x800CF9D4, (uint32)((sint32)sum >> 1));
    return 0x800EDFE4;
}

void func_80034d8c(sint32 object, uint32 enabled)
{
    FUNCTION_MARKER(0x80034D8C, "SLUS_004.64");
    if (object < 8)
    {
        if (enabled)
            func_8001e8b4(object);
        else
            func_8001e8d8(object);
    }
    else if (enabled)
        func_8001e894(0x800DDD44 + ((uint32)object << 4));
    else
        func_8001e878(0x800DDD44 + ((uint32)object << 4));
}

uint32 func_8001e878(uint32 object)
{
    uint32 value;
    uint32 coordinate;
    FUNCTION_MARKER(0x8001E878, "SLUS_004.64");
    value = r_u32(object);
    w_u32(object, value | 0x80000000);
    coordinate = r_u32(object + 4);
    w_u32(coordinate, 0);
    return coordinate;
}

uint32 func_8001e894(uint32 object)
{
    uint32 value;
    uint32 coordinate;
    FUNCTION_MARKER(0x8001E894, "SLUS_004.64");
    value = r_u32(object);
    w_u32(object, value & 0x7FFFFFFF);
    coordinate = r_u32(object + 4);
    w_u32(coordinate, 0);
    return coordinate;
}

uint32 func_8002a84c(uint32 object, uint32 value)
{
    uint32 result;
    FUNCTION_MARKER(0x8002A84C, "SLUS_004.64");
    w_u32(0x80081998 + 4 * object, value);
    result = 3;
    if (object == 3 && !value)
    {
        result = func_80031954(3) - 40 < 2;
        if (result)
        {
            func_80031c20(3, 26, 1, 0, 0, 0);
            result = func_80032320(3, 26);
        }
    }
    return result;
}

uint32 func_80016b3c(uint32 first, uint32 second)
{
    uint32 index;
    uint32 first_value;
    uint32 second_value;
    uint32 result;
    FUNCTION_MARKER(0x80016B3C, "SLUS_004.64");
    index = r_u32(0x800EE7EC);
    first_value = r_u32(0x80081978 + 4 * index);
    second_value = 0xFFFFFFFF;
    if (r_s32(0x800EE7F0) > 0)
    {
        index = r_u32(0x800EE7F0);
        second_value = r_u32(0x80081978 + 4 * index);
    }
    w_u32(0x800EE7EC, first);
    w_u32(0x800EE7F0, second);
    index = r_u32(0x800EE7EC);
    w_u32(0x80081978 + 4 * index, first_value);
    result = 0xFFFFFFFF;
    if (second_value != 0xFFFFFFFF)
    {
        index = r_u32(0x800EE7F0);
        result = 0x80081978 + 4 * index;
        w_u32(result, second_value);
    }
    return result;
}

void func_800288f4(uint32 mode)
{
    PSX_RECT rectangle;
    FUNCTION_MARKER(0x800288F4, "SLUS_004.64");
    VSync(0);
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 320;
    rectangle.h = 480;
    ClearImage(&rectangle, 0, 0, 0);
    DrawSync(0);
    if (GsGetActiveBuff())
        GsSwapDispBuff();
    func_80012c60();
    DrawSync(0);
    func_80040f0c(0, 128, mode);
    while (func_80041114())
        ;
    func_8001afcc();
    w_u32(0x800CF850, 0);
}

void func_80012c60(void)
{
    FUNCTION_MARKER(0x80012C60, "SLUS_004.64");
    func_80014d00();
    func_80026840();
    if (r_u32(0x800CF864))
        func_80012e54(1);
    else
        func_80012e54(r_u32(0x800CF86C));
    func_80013394();
    func_80015984();
}

uint32 func_8003240c(uint32 object)
{
    uint32 offset;
    uint32 cursor;
    FUNCTION_MARKER(0x8003240C, "SLUS_004.64");
    offset = 1040 * object;
    cursor = r_u32(0x800DB6FC + offset);
    return r_u32(0x800DB2F8 + offset + 32 * cursor);
}

uint32 func_8003244c(uint32 object)
{
    uint32 offset;
    uint32 cursor;
    FUNCTION_MARKER(0x8003244C, "SLUS_004.64");
    offset = 1040 * object;
    cursor = r_u32(0x800DB6FC + offset);
    return r_u32(0x800DB2FC + offset + 32 * cursor);
}

uint32 func_8003248c(uint32 object)
{
    uint32 offset;
    uint32 cursor;
    FUNCTION_MARKER(0x8003248C, "SLUS_004.64");
    offset = 1040 * object;
    cursor = r_u32(0x800DB6FC + offset);
    return r_u32(0x800DB300 + offset + 32 * cursor);
}

uint32 func_80031c20(uint32 object, uint32 action, uint32 enabled, uint32 value0, uint32 value1, uint32 value2)
{
    uint32 offset;
    uint32 cursor;
    uint32 entry;
    FUNCTION_MARKER(0x80031C20, "SLUS_004.64");
    offset = 1040 * object;
    cursor = r_u32(0x800DB6FC + offset);
    w_u32(0x800DB6F0 + offset, 1);
    entry = offset + 32 * cursor;
    w_u32(0x800DB2F0 + entry, action);
    w_u32(0x800DB2F4 + entry, enabled);
    w_u32(0x800DB2F8 + entry, value0);
    w_u32(0x800DB2FC + entry, value1);
    w_u32(0x800DB300 + entry, value2);
    w_u32(0x800DB6F8 + offset, 0xFFFFFFFF);
    w_u32(0x800DB6F4 + offset, 0);
    ++cursor;
    if ((sint32)cursor >= 32)
        cursor = 0;
    entry = offset + 32 * cursor;
    w_u32(0x800DB2F0 + entry, 0xFFFFFFFF);
    return entry;
}

uint32 func_80032320(uint32 object, uint32 value)
{
    uint32 offset;
    FUNCTION_MARKER(0x80032320, "SLUS_004.64");
    offset = 1040 * object;
    w_u32(0x800DB6F4 + offset, 0);
    w_u32(0x800DB6F8 + offset, value);
    return offset;
}

void func_80012e54(uint32 mode)
{
    uint32 object;
    FUNCTION_MARKER(0x80012E54, "SLUS_004.64");
    func_80013014((sint32)mode);
    func_80013178((sint32)mode);
    func_80013124((sint32)mode);
    func_800131bc(mode);
    func_800130e0(mode);
    func_80013058(mode);
    object = r_u32(0x800CFA6C);
    if (r_u32(0x800CF8BC + 4 * object))
        func_80032d68(object, 2);
}

void func_80013014(sint32 count)
{
    sint32 index;
    FUNCTION_MARKER(0x80013014, "SLUS_004.64");
    for (index = 0; index < count; ++index)
        func_80014c0c();
}

void func_80013178(sint32 count)
{
    sint32 index;
    FUNCTION_MARKER(0x80013178, "SLUS_004.64");
    for (index = 0; index < count; ++index)
        func_80027034();
}

void func_80013124(sint32 count)
{
    sint32 index;
    FUNCTION_MARKER(0x80013124, "SLUS_004.64");
    for (index = 0; index < count; ++index)
        if (r_u32(0x800CF8AC))
            func_80021514();
}

uint32 func_80014c0c(void)
{
    sint32 object;
    uint32 result;
    FUNCTION_MARKER(0x80014C0C, "SLUS_004.64");
    object = r_s32(0x800EE7EC);
    if (object > 0)
    {
        if (object == 3)
            func_8002839c(0, 3);
        else
            func_800254b8(0, r_u32(0x800EE7EC));
    }
    result = func_8001d480(r_u32(0x800EE7EC), 0);
    w_u32(0x800CFF7C, result);
    return result;
}

uint32 func_8003716c(uint32 x, uint32 z, uint32 radius, uint32 x0, uint32 z0, uint32 x1, uint32 z1)
{
    uint32 midpoint_x;
    uint32 midpoint_z;
    uint32 half_length;
    uint32 distance;
    FUNCTION_MARKER(0x8003716C, "SLUS_004.64");
    midpoint_x = (uint32)((sint32)(x0 + x1) >> 1);
    midpoint_z = (uint32)((sint32)(z0 + z1) >> 1);
    half_length = func_80036858(midpoint_x, midpoint_z, x1, z1);
    distance = func_80036858(x, z, midpoint_x, midpoint_z);
    return (sint32)(half_length + radius) >= (sint32)distance;
}

uint32 func_8001d480(uint32 object, uint16 distance)
{
    uint32 base;
    uint32 coordinate;
    uint32 scale;
    uint32 rotation_x;
    uint32 rotation_y;
    uint32 rotation_z;
    uint32 x;
    uint32 z;
    uint32 hit;
    sint32 out_x;
    sint32 out_z;
    VECTOR offset;
    FUNCTION_MARKER(0x8001D480, "SLUS_004.64");
    hit = 0;
    base = 0x800DDD44 + 16 * object;
    coordinate = r_u32(base + 4);
    scale = r_u32(coordinate + 68);
    rotation_x = r_u16(scale + 16);
    coordinate = r_u32(base + 4);
    scale = r_u32(coordinate + 68);
    rotation_y = r_u16(scale + 18);
    coordinate = r_u32(base + 4);
    scale = r_u32(coordinate + 68);
    rotation_z = r_u16(scale + 20);
    /* SVECTOR padding has no arithmetic meaning in the shared rotation services */
    func_800366a8(0, distance, rotation_x | (rotation_y << 16), rotation_z, &offset);
    coordinate = r_u32(base + 4);
    x = r_u32(coordinate + 24);
    z = r_u32(coordinate + 32);
    func_8001d594((uint32)offset.vx + x, (uint32)offset.vz + z, 650, &hit, &out_x, &out_z, -1);
    return hit;
}

uint32 func_8001d594(uint32 x, uint32 z, uint32 radius, uint32 *hit, sint32 *out_value, sint32 *out_index, sint32 excluded)
{
    uint32 index;
    uint32 offset;
    uint32 mask;
    uint32 mode;
    uint32 result;
    uint32 value;
    uint32 selected;
    sint32 x0;
    sint32 z0;
    sint32 x1;
    sint32 z1;
    FUNCTION_MARKER(0x8001D594, "SLUS_004.64");
    if (r_u32(0x800EDFD0))
        radius = (uint32)((sint32)radius >> 1);
    x = (uint32)((sint32)x >> 7);
    z = (uint32)((sint32)z >> 7);
    radius = (uint32)((sint32)radius >> 7);
    *hit = 0;
    *out_value = 0;
    if (r_u32(0x8007F064) == 0xFFFFFFFF)
        return 0;
    index = 0;
    for (;;)
    {
        offset = 44 * index;
        if (index != (uint32)excluded)
        {
            mask = r_u32(0x8007F08C + offset);
            selected = 1;
            if (mask)
            {
                mode = r_u32(0x800CF908);
                selected = (sint32)(mask & ((uint32)1 << (mode & 31))) > 0;
            }
            if (selected)
            {
                func_8001ba90(index, &x0, &z0, &x1, &z1);
                x0 >>= 7;
                z0 >>= 7;
                x1 >>= 7;
                z1 >>= 7;
                mode = r_u32(0x8007F068 + offset);
                if (mode == 1)
                    result = func_8003716c(x, z, radius, (uint32)x0, (uint32)z0, (uint32)x1, (uint32)z1);
                else if (mode == 2)
                    result = func_80037200(x, z, radius, (uint32)x0, (uint32)z0, (uint32)x1, (uint32)z1);
                else
                    result = (uint32)func_80036eec((sint32)x, (sint32)z, (sint32)radius, x0, z0, x1, z1);
                if (result == 1)
                {
                    value = r_u32(0x8007F07C + offset);
                    if (value && r_u32(0x8007F064 + offset))
                    {
                        if (!*hit)
                            *hit = value;
                        value = r_u32(0x8007F084 + offset);
                        *out_value = (sint32)value;
                        *out_index = (sint32)index;
                        return 1;
                    }
                }
            }
        }
        ++index;
        if (r_u32(0x8007F064 + 44 * index) == 0xFFFFFFFF)
            return 0;
    }
}

void func_800131bc(uint32 count)
{
    uint32 index;
    FUNCTION_MARKER(0x800131BC, "SLUS_004.64");
    for (index = 0; (sint32)index < (sint32)count; ++index)
    {
        func_800315ec();
        func_80012ed0();
        func_8002334c();
        if (r_u32(0x800CFE24))
            func_8002b3e0();
    }
}

void func_800130e0(uint32 count)
{
    uint32 index;
    FUNCTION_MARKER(0x800130E0, "SLUS_004.64");
    for (index = 0; (sint32)index < (sint32)count; ++index)
        func_80015100();
}

void func_80013058(uint32 count)
{
    uint32 index;
    FUNCTION_MARKER(0x80013058, "SLUS_004.64");
    for (index = 0; (sint32)index < (sint32)count; ++index)
        func_80014830();
}

uint32 func_80037200(uint32 x, uint32 z, uint32 radius, uint32 x0, uint32 z0, uint32 x1, uint32 z1)
{
    sint32 left;
    sint32 right;
    sint32 top;
    sint32 bottom;
    sint32 center_x;
    sint32 center_z;
    sint32 lower_x;
    sint32 upper_x;
    sint32 lower_z;
    sint32 upper_z;
    FUNCTION_MARKER(0x80037200, "SLUS_004.64");
    center_x = (sint32)x;
    center_z = (sint32)z;
    left = (sint32)x0 < (sint32)x1 ? (sint32)x0 : (sint32)x1;
    right = (sint32)x0 < (sint32)x1 ? (sint32)x1 : (sint32)x0;
    top = (sint32)z0 < (sint32)z1 ? (sint32)z0 : (sint32)z1;
    bottom = (sint32)z0 < (sint32)z1 ? (sint32)z1 : (sint32)z0;
    if (center_x >= left && center_x <= right && center_z >= top && center_z <= bottom)
        return 1;
    lower_x = (sint32)(x - radius);
    upper_x = (sint32)(x + radius);
    lower_z = (sint32)(z - radius);
    upper_z = (sint32)(z + radius);
    if (lower_x < left && upper_x < left)
        return 0;
    if (lower_x > right && upper_x > right)
        return 0;
    if (lower_z < top && upper_z < top)
        return 0;
    if (lower_z > bottom && upper_z > bottom)
        return 0;
    if ((sint32)func_80036858(x, z, x0, z0) < (sint32)radius)
        return 1;
    if ((sint32)func_80036858(x, z, x0, z1) < (sint32)radius)
        return 1;
    if ((sint32)func_80036858(x, z, x1, z1) < (sint32)radius)
        return 1;
    if ((sint32)func_80036858(x, z, x1, z0) < (sint32)radius)
        return 1;
    if (center_x >= left && center_x <= right)
    {
        if (center_z < top && upper_z >= top)
            return 1;
        if (center_z > bottom && lower_z <= bottom)
            return 1;
    }
    if (center_z < top || center_z > bottom)
        return 0;
    if (center_x < left && upper_x >= left)
        return 1;
    return center_x > right && lower_x <= right;
}

void func_80012ed0(void)
{
    uint32 object;
    uint32 action;
    FUNCTION_MARKER(0x80012ED0, "SLUS_004.64");
    for (object = 1; object < 4; ++object)
    {
        action = func_80031954(object);
        if (action - 23 < 2 || action == 25 || action == 14)
            w_u32(0x800E9A58 + 4 * object, action);
        else
            w_u32(0x800E9A58 + 4 * object, 0);
    }
}

void func_8001322c(uint32 mode, uint32 seconds)
{
    uint32 value;
    FUNCTION_MARKER(0x8001322C, "SLUS_004.64");
    w_u32(0x800CF844, mode);
    if (mode)
    {
        value = r_u32(0x800CF834);
        w_u32(0x800CF83C, value);
        w_u32(0x800CF840, 60 * seconds);
    }
}

void func_8001309c(sint32 count)
{
    sint32 index;
    FUNCTION_MARKER(0x8001309C, "SLUS_004.64");
    for (index = 0; index < count; ++index)
        func_80029034();
}

void func_800223b8(uint32 object, uint32 action, uint32 mode)
{
    uint32 previous;
    uint32 current;
    uint32 position;
    uint32 index;
    uint32 coordinate;
    uint32 scale;
    uint32 size;
    FUNCTION_MARKER(0x800223B8, "SLUS_004.64");
    w_u32(0x800CFA68, 1 - object);
    func_80017a74();
    w_u32(0x800CF87C, mode);
    if (func_80022ab0(action, 0, 0, 0, 0, 0, 0, 0) != 1)
    {
        w_u32(0x800CF87C, 0);
        return;
    }
    w_u32(0x800CF874, 1);
    w_u32(0x800EE7F8, 0);
    w_u32(0x800EE7FC, 0);
    w_u32(0x800EE800, 0);
    w_u32(0x800EE858, 0);
    w_u32(0x800CF864, 0);
    w_u32(0x800CF870, 0);
    func_80023c18();
    func_80016690();
    func_800228d0(0);
    previous = r_u32(0x800EE7E4);
    w_u32(0x800EE7E4, action);
    w_u32(0x800EE7E8, previous);
    func_8001afcc();
    func_800346a0(r_u32(0x800CFA68));
    func_800150f8();
    func_80035414(r_u32(0x800EE7E4));
    current = r_u32(0x800CFA68);
    object = r_u32(0x800EE7EC);
    position = r_u32(0x800CF908);
    w_u32(0x800CFA6C, current);
    func_80020a48(object, position);
    object = r_u32(0x800EE7EC);
    position = r_u32(0x800CF908);
    func_80020b7c(object, position);
    if (!r_u32(0x800EDFC0))
    {
        object = r_u32(0x800EE7F0);
        if (object)
        {
            position = r_u32(0x800CF908);
            func_80020a48(object, position);
            object = r_u32(0x800EE7F0);
            position = r_u32(0x800CF908);
            func_80020b7c(object, position);
        }
    }
    func_80023b9c((uint32)-2000, 2000);
    func_8001e8d8(4);
    func_80032d68(r_u32(0x800CFA68), 1);
    for (index = 1; index < 5; ++index)
    {
        size = r_u32(0x800EDFD0) ? 2048 : 4096;
        coordinate = r_u32(0x800DDD48 + 16 * index);
        scale = r_u32(coordinate + 68);
        w_u32(scale, size);
        coordinate = r_u32(0x800DDD48 + 16 * index);
        scale = r_u32(coordinate + 68);
        w_u32(scale + 4, size);
        coordinate = r_u32(0x800DDD48 + 16 * index);
        scale = r_u32(coordinate + 68);
        w_u32(scale + 8, size);
        position = r_u32(0x800CF908);
        func_80020b7c(index, position);
    }
    func_8001dc98();
    func_800173d0();
    func_80032d68(r_u32(0x800CFA68), 5);
    w_u32(0x800CF87C, 0);
}

void func_800327a0(uint32 object, uint32 component, uint32 value)
{
    uint32 coordinate;
    uint32 scale;
    FUNCTION_MARKER(0x800327A0, "SLUS_004.64");
    if (!object)
        return;
    if (component <= 8)
    {
        coordinate = r_u32(0x800DDD48 + 16 * object);
        if (component < 3)
            w_u32(coordinate + 24 + 4 * component, value);
        else
        {
            scale = r_u32(coordinate + 68);
            if (component < 6)
                w_u32(scale + 4 * (component - 3), value);
            else
                w_u16(scale + 16 + 2 * (component - 6), (uint16)value);
        }
    }
    func_8001b21c(0x800DDD44 + 16 * object);
    coordinate = r_u32(0x800DDD48 + 16 * object);
    w_u32(coordinate, 0);
}
