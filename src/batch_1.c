#include "functions.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

/* Full original bodies, pending final integration and runtime validation */
uint32 func_8001a450(void)
{
    FUNCTION_MARKER(0x8001A450, "SLUS_004.64");
    ResetGraph(0);
    SetGraphDebug(0);
    PadInit(1);
    w_u32(0x800CF934, 0);
    GsInitGraph(320, 240, 4, 1, 0);
    GsDefDispBuff(0, 0, 0, 240);
    GsInit3D();
    InitGeom();
    w_u32(0x800EBD14, 10);
    w_u32(0x800EBD18, 0x800ADC64);
    w_u32(0x800EBD1C, 1);
    w_u32(0x800EBD28, 10);
    w_u32(0x800EBD2C, 0x800AEC64);
    w_u32(0x800EBD30, 1);
    w_u32(0x800EC708, 10);
    w_u32(0x800EC70C, 0x800AFC64);
    w_u32(0x800EC710, 0);
    w_u32(0x800EC714, 2);
    w_u32(0x800EC71C, 10);
    w_u32(0x800EC720, 0x800B0C64);
    w_u32(0x800EC724, 0);
    w_u32(0x800EC728, 2);
    w_u32(0x800EC750, 9);
    w_u32(0x800EC754, 0x800ACC64);
    w_u32(0x800EC758, 0);
    w_u32(0x800EC75C, 0);
    w_u32(0x800EC764, 9);
    w_u32(0x800EC768, 0x800AD464);
    w_u32(0x800EC76C, 0);
    w_u32(0x800EC770, 0);
    w_u32(0x800EC778, 8);
    w_u32(0x800EC77C, 0x800AC464);
    w_u32(0x800EC780, 0);
    w_u32(0x800EC784, 0);
    w_u32(0x800EC78C, 8);
    w_u32(0x800EC790, 0x800AC864);
    w_u32(0x800EC794, 0);
    w_u32(0x800EC798, 0);
    return 0x800EC778;
}

sint32 func_800378e8(void)
{
    PSX_RECT rectangle;
    FUNCTION_MARKER(0x800378E8, "SLUS_004.64");
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 320;
    rectangle.h = 480;
    ClearImage(&rectangle, 0, 0, 0);
    return DrawSync(0);
}

sint32 func_8001eff8(void)
{
    FUNCTION_MARKER(0x8001EFF8, "SLUS_004.64");
    DrawSync(0);
    VSync(4);
    return ResetGraph(1);
}

void func_800222d0(uint8 *destination, const uint8 *source, sint32 length)
{
    sint32 index;
    uint32 character;
    FUNCTION_MARKER(0x800222D0, "SLUS_004.64");
    for (index = 0; index < length; ++index)
    {
        character = *source;
        if (character - 0x61 < 26)
            character += 0xE0;
        else
            character = *source;
        *destination = (uint8)character;
        ++destination;
        ++source;
    }
    *destination = 0;
}

static uint32 movie_frame_init_core(uint32 destination, uint32 source, const uint32 *native_source)
{
    uint32 value;
    uint32 format;
    w_u32(destination, (native_source != 0 ? native_source[11] : r_u32(source + 0x2C)));
    value = (native_source != 0 ? native_source[12] : r_u32(source + 0x30));
    w_u32(destination + 8, 0);
    w_u32(destination + 4, value);
    w_u32(destination + 0x0C, (native_source != 0 ? native_source[13] : r_u32(source + 0x34)));
    value = (native_source != 0 ? native_source[14] : r_u32(source + 0x38));
    w_u32(destination + 0x14, 0);
    w_u32(destination + 0x10, value);
    w_u16(destination + 0x18, (native_source != 0 ? (uint16)native_source[6] : r_u16(source + 0x18)));
    w_u16(destination + 0x1A, (native_source != 0 ? (uint16)native_source[7] : r_u16(source + 0x1C)));
    w_u16(destination + 0x20, (native_source != 0 ? (uint16)native_source[8] : r_u16(source + 0x20)));
    value = (native_source != 0 ? (uint16)native_source[9] : r_u16(source + 0x24));
    w_u32(destination + 0x28, 0);
    w_u16(destination + 0x22, (uint16)value);
    w_u16(destination + 0x2C, (native_source != 0 ? (uint16)native_source[6] : r_u16(source + 0x18)));
    w_u16(destination + 0x2E, (native_source != 0 ? (uint16)native_source[7] : r_u16(source + 0x1C)));
    format = (native_source != 0 ? native_source[1] : r_u32(source + 4)) == 1 ? 24 : 16;
    w_u16(destination + 0x30, (uint16)format);
    w_u32(destination + 0x34, 0);
    return format;
}

uint32 func_80030f54(uint32 destination, uint32 source)
{
    FUNCTION_MARKER(0x80030F54, "SLUS_004.64");
    return movie_frame_init_core(destination, source, 0);
}

uint32 init_movie_frame(uint32 destination, const uint32 *source)
{
    return movie_frame_init_core(destination, 0, source);
}

uint32 func_80016250(void)
{
    FUNCTION_MARKER(0x80016250, "SLUS_004.64");
    func_8003943c(0x80015FF8);
    w_u32(0x800EB894, r_u32(0x800EB894) & 0xF7FFFFFF);
    return 0x800EB894;
}

void func_8003943c(uint32 callback)
{
    FUNCTION_MARKER(0x8003943C, "SLUS_004.64");
    w_u32(0x800CFCA0, callback);
}

void func_8001f0ac(void)
{
    FUNCTION_MARKER(0x8001F0AC, "SLUS_004.64");
    w_u32(0x800CFA98, 0);
}

uint32 func_800286bc(uint32 enabled, sint32 value, uint32 duration)
{
    FUNCTION_MARKER(0x800286BC, "SLUS_004.64");
    w_u32(0x800CF8E4, enabled);
    if (enabled)
    {
        if (value >= 0)
            w_u32(0x800CF8F4, (uint32)value);
        w_u32(0x800CF8E8, duration != 0);
        w_u32(0x800CF8F0, duration);
        w_u32(0x800CF8EC, duration);
        return 1;
    }
    w_u32(0x800CF8F4, 100);
    w_u32(0x800CF8E8, 0);
    w_u32(0x800CF8F0, 60);
    w_u32(0x800CF8EC, 60);
    return 60;
}

sint32 func_80014ffc(void)
{
    FUNCTION_MARKER(0x80014FFC, "SLUS_004.64");
    if (r_u32(0x800EDFD8) == 2)
        w_u32(0x800CF90C, 0);
    else if (r_u32(0x800EDFD8) == 0)
        w_u32(0x800CF90C, 1);
    else if (r_u32(0x800EDFD8) == 1)
        w_u32(0x800CF90C, 2);
    return func_80015100();
}

uint32 func_80015a0c(void)
{
    uint32 result;
    uint32 delta;
    FUNCTION_MARKER(0x80015A0C, "SLUS_004.64");
    result = r_u32(0x800CF818);
    if (result)
    {
        result = r_u32(0x800EF5F0);
        delta = r_u32(0x800CF808);
        w_u32(0x800EF5F0, result + delta);
        result = r_u32(0x800EF5FC) + delta;
        w_u32(0x800EF5FC, result);
    }
    return result;
}

void func_8001e8b4(sint32 index)
{
    FUNCTION_MARKER(0x8001E8B4, "SLUS_004.64");
    if (index > 0)
        w_u32(0x80081978 + ((uint32)index << 2), 1);
}

void func_8001e8d8(sint32 index)
{
    FUNCTION_MARKER(0x8001E8D8, "SLUS_004.64");
    if (index > 0)
    {
        func_80023d9c(index, 0);
        w_u32(0x80081978 + ((uint32)index << 2), 0);
    }
}

uint32 func_8003151c(uint32 object)
{
    uint32 result;
    uint32 remaining;
    uint32 index;
    FUNCTION_MARKER(0x8003151C, "SLUS_004.64");
    result = r_u32(object + 0x34);
    if (!result)
    {
        remaining = 0x7FFFFF;
        do
        {
            if (!remaining)
            {
                index = r_u32(object + 0x28);
                w_u32(object + 0x34, 1);
                w_u32(object + 0x28, index == 0);
                index = r_u32(object + 0x28);
                w_u16(object + 0x2C, r_u16(object + (index << 3) + 0x18));
                index = r_u32(object + 0x28);
                w_u16(object + 0x2E, r_u16(object + (index << 3) + 0x1A));
            }
            result = r_u32(object + 0x34);
            --remaining;
        } while (!result);
    }
    w_u32(object + 0x34, 0);
    return result;
}

uint32 func_80016120(void)
{
    uint32 row;
    uint32 column;
    uint32 flags;
    FUNCTION_MARKER(0x80016120, "SLUS_004.64");
    func_80036184("Tim\\Messfnt.tim", r_u32(0x800CF9FC), r_s32(0x800CF7E4));
    func_8001a598(19, r_u32(0x800CF9FC));
    for (row = 0; row < 10; ++row)
    {
        for (column = 0; column < 16; ++column)
            func_8001aa28(0x800EA110, 0x800D9C68 + 36 * (16 * row + column), 8 * column, 16 * row, 8, 16);
    }
    func_80036184("Tim\\Sysfnt.tim", r_u32(0x800CF9FC), r_s32(0x800CF7E4));
    func_8001a598(5, r_u32(0x800CF9FC));
    func_8001aa28(0x800E9F18, 0x800EB894, 20, 20, 44, 44);
    flags = r_u32(0x800EB894);
    w_u32(0x800EB8B4, 0);
    w_u32(0x800EB894, flags & 0xF7FFFFFF);
    w_u16(0x800EB8AC, 22);
    w_u16(0x800EB8AE, 22);
    return 22;
}

uint32 func_8001aa28(uint32 source, uint32 destination, uint32 u, uint32 v, uint32 width, uint32 height)
{
    uint32 value;
    FUNCTION_MARKER(0x8001AA28, "SLUS_004.64");
    w_u32(destination, r_u32(source));
    w_u16(destination + 8, (uint16)width);
    w_u16(destination + 10, (uint16)height);
    w_u16(destination + 4, r_u16(source + 4));
    w_u16(destination + 6, r_u16(source + 6));
    w_u16(destination + 0x18, r_u16(source + 0x18));
    w_u16(destination + 0x1A, r_u16(source + 0x1A));
    w_u16(destination + 0x0C, r_u16(source + 0x0C));
    w_u8(destination + 0x0E, (uint8)(r_u8(source + 0x0E) + u));
    w_u8(destination + 0x0F, (uint8)(r_u8(source + 0x0F) + v));
    w_u16(destination + 0x10, r_u16(source + 0x10));
    w_u16(destination + 0x12, r_u16(source + 0x12));
    w_u8(destination + 0x14, r_u8(source + 0x14));
    w_u8(destination + 0x15, r_u8(source + 0x15));
    w_u8(destination + 0x16, r_u8(source + 0x16));
    w_u32(destination + 0x20, r_u32(source + 0x20));
    w_u16(destination + 0x1C, r_u16(source + 0x1C));
    value = r_u16(source + 0x1C);
    w_u16(destination + 0x1E, (uint16)value);
    return value;
}

uint32 func_80035f6c(void)
{
    FUNCTION_MARKER(0x80035F6C, "SLUS_004.64");
    FntFlush(-1);
    VSync(0);
    ResetGraph(1);
    return GsSwapDispBuff();
}

uint32 func_8003609c(void)
{
    FUNCTION_MARKER(0x8003609C, "SLUS_004.64");
    FntFlush(-1);
    VSync(0);
    ResetGraph(1);
    return GsSwapDispBuff();
}

uint32 func_800360d4(const char *path)
{
    FUNCTION_MARKER(0x800360D4, "SLUS_004.64");
    FntLoad(960, 256);
    SetDumpFnt(FntOpen(-144, -104, 320, 200, 0, 512));
    while (PadRead(0) & 0x40)
        ;
    do
    {
        FntPrint("read error\n");
        FntPrint("%s", path);
        func_8003609c();
    } while (!(PadRead(0) & 0x40));
    while (PadRead(0) & 0x40)
        ;
    return 0;
}

/* Convert original host/CD path spellings to extracted resources */
FILE *open_resource(const char *path)
{
    char native_path[512];
    size_t length;
    if (strncmp(path, "i:\\pax\\ob\\", 10) == 0 || strncmp(path, "I:\\PAX\\OB\\", 10) == 0)
        path += 10;
    while (*path == '/' || *path == '\\')
        ++path;
    memcpy(native_path, "DATA/", 5);
    length = 5;
    while (*path && *path != ';')
    {
        if (length + 1 >= sizeof(native_path))
            return NULL;
        native_path[length++] = *path == '\\' ? '/' : *path;
        ++path;
    }
    native_path[length] = 0;
    return xport_fopen(native_path, "rb");
}

sint32 func_80036494(const char *path, uint32 destination)
{
    FILE *file;
    long length;
    uint32 remaining;
    uint32 offset;
    size_t count;
    size_t received;
    FUNCTION_MARKER(0x80036494, "SLUS_004.64");
    file = open_resource(path);
    if (!file)
    {
        func_800360d4(path);
        return 0;
    }
    if (fseek(file, 0, SEEK_END) || (length = ftell(file)) < 0 || length > INT32_MAX)
    {
        fclose(file);
        func_800360d4(path);
        return 0;
    }
    remaining = (uint32)length;
    offset = 0;
    do
    {
        if (fseek(file, (long)offset, SEEK_SET))
            break;
        count = remaining > 0xFFFE ? 0xFFFE : remaining;
        received = xport_fread(psx_addr(destination, count), 1, count, file);
        remaining -= (uint32)received;
        if (!received)
            break;
        destination += (uint32)received;
        if ((sint32)remaining <= 0)
            break;
        offset += (uint32)received;
    } while (1);
    fclose(file);
    /* Original terminal memset starts at the current destination */
    memset(psx_addr(destination, 2048), 0, 2048);
    return (sint32)length;
}

/* Native callback ABI discards the original incidental return carrier */
static void vsync_callback(void)
{
    func_800214b4();
}

void func_80012698(void)
{
    uint32 buffer;
    uint32 work;
    uint32 end;
    sint32 result;
    uint32 selection;
    uint32 selection_value;
    uint32 frame;
    PSX_RECT rectangle;
    FUNCTION_MARKER(0x80012698, "SLUS_004.64");
    /* Host CRT and host stack replace __main and the original stack switch */
    func_8001a450();
    srandPSX(1);
    func_800378e8();
    FntLoad(960, 256);
    buffer = func_80035fa4(0xD1F0);
    w_u32(0x800CFA38, buffer);
    buffer += 0x2800;
    w_u32(0x800CFA34, buffer);
    w_u32(0x800CFA3C, buffer + 0x9470);
    buffer = func_80035fa4(0x101D0);
    w_u32(0x800CFA5C, buffer);
    w_u32(0x800CFA60, buffer + 0x80E8);
    w_u32(0x800CFA64, buffer + 0x101D0);
    w_u32(0x800CFA18, func_80035fa4(0x59290));
    buffer = func_80035fa4(0x88F68);
    w_u32(0x800CFA20, buffer);
    w_u32(0x800CFA28, buffer);
    work = buffer + 0x493E0;
    w_u32(0x800CF9FC, work);
    end = work + 0x3FB88;
    w_u32(0x800CFA00, end);
    w_u32(0x800CFA04, work);
    w_u32(0x800CFA80, buffer);
    w_u32(0x800CFA84, work);
    w_u32(0x800CFA88, work);
    w_u32(0x800CFA8C, end);
    buffer = r_u32(0x800CFA18);
    w_u32(0x800CFA78, buffer);
    w_u32(0x800CFA7C, buffer + 0x59290);
    while (!CdInit())
        ;
    func_800392e0();
    func_800393a0();
    ResetCallback();
    VSyncCallback(vsync_callback);
    ResetCallback();
    VSyncCallback(vsync_callback);
    w_u32(0x800EDFB4, 4);
    func_80036184("Tim\\Ealogo.tim", r_u32(0x800CFA28), r_s32(0x800CF7E4));
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 320;
    rectangle.h = 240;
    LoadImagePSX(&rectangle, (uint32 *)psx_addr(r_u32(0x800CFA28) + 20, 320 * 240 * 2));
    VSync(0);
    DrawSync(0);
    SetDispMask(1);
    for (frame = 0; frame < 180; ++frame)
    {
        VSync(0);
        if (PadRead(0) & (PADRdown | PADstart))
            break;
    }
    if (r_u32(0x800CF7A4))
        func_80028af4();
    else
    {
        func_80021478();
        DrawSync(0);
        VSync(0);
    }
    func_80028ce0();
    w_u32(0x800C81A8, 0xAF0);
    w_u16(0x800C81AC, 0x38);
    w_u16(0x800C81AE, 0x38);
    func_80016120();
    func_80016250();
    func_800162b0();
    func_8001f384();
    func_80016250();
    func_80017598();
    if (r_u32(0x800CF7CC))
        func_800177a8();
    w_u32(0x800CF958, 4);
    func_800239e4(0);
    func_80016290();
    func_8001aafc();
    func_8001ab94();
    SetDumpFnt(FntOpen(-144, -104, 320, 200, 0, 512));
    w_u16(0x800CF950, r_u16(0x800CF952));
    func_80047dec(r_u16(0x800CF950));
    for (;;)
    {
        w_u32(0x800CF870, 0);
        func_80017a74();
        func_80017884();
        func_800162b0();
        w_u32(0x800EDFE0, 0);
        w_u32(0x800EDFAC, 0);
        for (;;)
        {
            w_u32(0x800CFA94, 0xFFFFFFFF);
            result = func_8002138c();
            w_u32(0x800CFA94, (uint32)result);
            if (result != 1)
                break;
            func_8001a830();
            if (func_80018c40() == result)
                goto run_scene;
        }
        if (r_u32(0x800CF7A4))
        {
            func_8001aafc();
            func_8001ab94();
            func_80016250();
            func_8001a830();
            func_8001663c();
            if (!func_80023b2c(4))
                func_8001ef00();
            func_80016290();
            func_80016690();
            w_u32(0x800CF82C, 0);
            do
            {
                w_u32(0x800CFA90, 1);
                func_80017d0c(&selection, &selection_value);
                w_u32(0x800CFA90, 0);
            } while (selection);
        }
        else
        {
            func_8002141c();
            func_8001aafc();
            func_8001ab94();
            func_80016250();
            func_8001a830();
            func_8001663c();
            if (!func_80023b2c(4))
                func_8001ef00();
            func_80016290();
            w_u32(0x800CFA90, 1);
            func_80022320(r_u32(0x800CFA6C), 1, 1);
            w_u32(0x800CFA90, 0);
            func_80016690();
            w_u32(0x800CF82C, 0);
        }
run_scene:
        w_u32(0x800CF830, (uint32)VSync(-1));
        func_80012d20();
        while (!r_u32(0x800CF8DC) && !r_u32(0x800CF8E0))
        {
            func_80012bfc();
            func_80015c44();
            w_u32(0x800CF850, 0);
        }
        result = r_s32(0x800CF8DC);
        if (result > 0 && result != 100)
        {
            func_80032d68(r_u32(0x800CFA6C), 4);
            func_80017a74();
            func_8002841c();
        }
        func_8002372c(0);
        if (r_u32(0x800CF8E0))
        {
            func_80017a74();
            func_80021340();
        }
    }
}

uint32 func_80035fa4(uint32 bytes)
{
    uint32 address;
    FUNCTION_MARKER(0x80035FA4, "SLUS_004.64");
    address = mallocPSX(bytes);
    if (!address)
    {
        FntLoad(448, 256);
        SetDumpFnt(FntOpen(32, 32, 320, 200, 0, 256));
        for (;;)
        {
            FntPrint("out of memory");
            func_80035f6c();
        }
    }
    if (address >= 0x801EFFFF - bytes)
    {
        FntLoad(448, 256);
        SetDumpFnt(FntOpen(32, 32, 320, 200, 0, 256));
        for (;;)
        {
            FntPrint("out of memory(%x:%d)", address, (sint32)bytes);
            func_80035f6c();
        }
    }
    return address;
}

void func_80016290(void)
{
    FUNCTION_MARKER(0x80016290, "SLUS_004.64");
    func_8003943c(0);
}

uint32 func_800162b0(void)
{
    uint32 index;
    uint32 mode;
    FUNCTION_MARKER(0x800162B0, "SLUS_004.64");
    w_u32(0x800CF7A0, 0);
    func_8001eff8();
    func_8001f0ac();
    w_u32(0x800CF860, 0);
    w_u32(0x800CF870, 0);
    w_u32(0x800CFB84, 0);
    w_u32(0x800CFA90, 0);
    w_u32(0x800CFC18, 0);
    w_u32(0x800CF910, 1);
    w_u32(0x800CF854, 0);
    w_u32(0x800CF914, 1);
    w_u32(0x800CF864, 0);
    w_u32(0x800CF908, 0);
    w_u32(0x800EDFC0, 0);
    w_u32(0x800EDFC4, 0);
    w_u32(0x800EDFB4, 4);
    w_u32(0x800EDFCC, 1);
    w_u32(0x800EDFD0, 0);
    w_u32(0x800EDFB8, 0);
    w_u32(0x800EDFDC, 0);
    w_u32(0x800EE048, 0);
    w_u32(0x800EE04C, 0);
    w_u32(0x800EE050, 4);
    w_u32(0x800EE054, 3);
    w_u32(0x800EE058, 9);
    w_u32(0x800EE05C, 7);
    w_u32(0x800EE060, 8);
    w_u32(0x800EE088, 0);
    w_u32(0x800EE08C, 1);
    w_u32(0x800EE090, 1);
    w_u32(0x800EE094, 2);
    w_u32(0x800EE098, 1);
    w_u32(0x800EE014, 1);
    w_u32(0x800EE018, 1);
    w_u32(0x800EE01C, 1);
    w_u32(0x800EE020, 1);
    w_u32(0x800EDFE4, 2500);
    w_u32(0x800EDFE8, 1500);
    w_u32(0x800CF848, 0);
    w_u32(0x800CF84C, 0);
    for (index = 1; index < 5; ++index)
        w_u32(0x800EE068 + 4 * index, 1);
    for (index = 0; index < 128; ++index)
        w_u32(0x800814B8 + 4 * index, 0);
    for (index = 0; index < 256; ++index)
        w_u32(0x800EE8D8 + 4 * index, 0);
    for (index = 0; index < 512; ++index)
        w_u32(0x800EECD8 + 4 * index, 0);
    for (index = 0; index < 64; ++index)
        w_u32(0x800EE7D8 + 4 * index, 0);
    for (index = 0; index < 50; ++index)
        w_u32(0x800EF4D8 + 4 * index, 0);
    for (index = 0; index < 128; ++index)
        w_u32(0x800816B8 + 4 * index, 0);
    w_u32(0x800CF8DC, 0);
    w_u32(0x800CF8E0, 0);
    w_u32(0x800CF844, 0);
    w_u32(0x800CF840, 100);
    func_800286bc(0, 100, 60);
    w_u32(0x800CF880, 1);
    w_u32(0x800EDFD8, 0);
    func_80014ffc();
    func_8001e8b4(1);
    func_8001e8d8(2);
    func_8001e8d8(3);
    func_8001e8d8(4);
    mode = r_u32(0x800CF908);
    w_u32(0x800EDFB4, 4);
    w_u32(0x800EE02C, 1);
    w_u32(0x800EE030, 1);
    w_u32(0x800EE034, 1);
    w_u32(0x800EE038, 1);
    w_u32(0x800CFE24, 0);
    w_u32(0x800CFDDC, 0);
    w_u32(0x800CF818, 0);
    w_u32(0x800CF858, 0);
    w_u32(0x800EDFF8, 0);
    w_u32(0x800EE0A8, 0xFFFFFFFF);
    w_u32(0x800CF918, 0);
    w_u32(0x800CF91C, 0);
    w_u32(0x800CF85C, 0);
    w_u32(0x800EDFF4, 3);
    func_80020834(mode);
    w_u32(0x800EDFD4, 0);
    func_80014ffc();
    w_u32(0x800EE7F8, 0);
    w_u32(0x800EE7FC, 0);
    w_u32(0x800EE800, 0);
    w_u32(0x800EE858, 0);
    w_u32(0x800EE868, 0);
    w_u32(0x800EE85C, 0);
    w_u32(0x800EE860, 0);
    w_u32(0x800EE864, 0);
    w_u32(0x800EE7E8, 0);
    w_u32(0x800CF874, 1);
    w_u32(0x800CF878, 1);
    func_80031884();
    w_u32(0x8008199C, 0);
    w_u32(0x800819A0, 0);
    w_u32(0x800819A4, 0);
    w_u32(0x800819A8, 0);
    w_u32(0x800CF7B0, 0);
    for (index = 0; index < 8; ++index)
    {
        w_u32(0x800E9A58 + 4 * index, 0);
        w_u32(0x800F02F0 + 4 * index, 0);
        w_u32(0x800F0310 + 4 * index, 0);
        w_u32(0x800F0330 + 4 * index, 0);
    }
    w_u32(0x800EE7EC, 1);
    return func_8001f87c();
}

uint32 func_80028ce0(void)
{
    static const uint32 targets[] = {
        0x80063068, 0x800631B0, 0x80062F28, 0x8004EA70,
        0x8005D25C, 0x80054924, 0x80062DEC, 0x8005098C,
        0x80063584, 0x80063714, 0x80063444, 0x8004F3E0,
        0x8005DBCC, 0x80055238, 0x800632FC, 0x80051F50,
        0x800659E4, 0x80065B54, 0x80065880, 0x800572E8,
        0x80047E0C, 0x8005FE10, 0x80065714, 0x80059580,
        0x80065F98, 0x8006614C, 0x80065E3C, 0x80057D60,
        0x80048888, 0x80060848, 0x80065CC4, 0x8005ADC8,
        0x80063B80, 0x80063CF8, 0x80063A14, 0x8004FE6C,
        0x8005E658, 0x80055C20, 0x800638AC, 0x80052964,
        0x80064B90, 0x80064D70, 0x80064A1C, 0x800512A0,
        0x8005F170, 0x80056700, 0x8006489C, 0x80053444,
        0x800667F0, 0x8006699C, 0x80066654, 0x80058914,
        0x8004943C, 0x80061338, 0x800664B4, 0x8005B8E8,
        0x80066EA8, 0x800670B4, 0x80066D10, 0x80059FAC,
        0x8004A0A8, 0x80061F60, 0x80066B54, 0x8005C504,
        0x8004C0C8, 0x8004DFEC, 0x8004CBB4, 0x8004C310,
        0x8004E234, 0x8004CD48
    };
    uint32 index;
    FUNCTION_MARKER(0x80028CE0, "SLUS_004.64");
    for (index = 0; index < sizeof(targets) / sizeof(targets[0]); ++index)
        w_u32(0x800D9B50 + 4 * index, targets[index]);
    return 0x800D9B50;
}

uint32 func_80031884(void)
{
    uint32 index;
    uint32 offset;
    FUNCTION_MARKER(0x80031884, "SLUS_004.64");
    for (index = 0; index < 5; ++index)
    {
        offset = 1040 * index;
        w_u32(0x800DB2F0 + offset, 0xFFFFFFFF);
        w_u32(0x800DB310 + offset, 0xFFFFFFFF);
        w_u32(0x800DB2F4 + offset, 1);
        w_u32(0x800DB6F0 + offset, 0);
        w_u32(0x800DB6F8 + offset, 0xFFFFFFFF);
        w_u32(0x800DB6F4 + offset, 0xFFFFFFFF);
        w_u32(0x800DB6FC + offset, 0);
        w_u32(0x800DB2F8 + offset, 0);
        w_u32(0x800DB2FC + offset, 0);
        w_u32(0x800DB300 + offset, 0);
    }
    return 0;
}

uint32 func_80020834(uint32 mode)
{
    uint32 selected;
    uint32 object;
    uint32 value;
    uint32 result;
    FUNCTION_MARKER(0x80020834, "SLUS_004.64");
    selected = r_u32(0x800EE7EC);
    w_u32(0x800CF908, mode);
    if (selected)
    {
        if (!r_u32(0x800EDFD0))
        {
            object = r_u32(0x800DDD48 + (selected << 4));
            value = r_u32(0x80081938 + (mode << 2)) - 1700;
        }
        else
        {
            object = r_u32(0x800DDD48 + (selected << 4));
            value = r_u32(0x80081938 + (r_u32(0x800CF908) << 2)) - 850;
        }
        w_u32(object + 0x1C, value);
        object = r_u32(0x800DDD48 + (selected << 4));
        w_u32(object, 0);
        func_8001b21c(0x800DDD44 + (selected << 4));
    }
    selected = r_u32(0x800EE7F0);
    if (selected && !r_u32(0x800EDFC0))
    {
        if (!r_u32(0x800EDFD0))
        {
            object = r_u32(0x800DDD48 + (selected << 4));
            value = r_u32(0x80081938 + (r_u32(0x800CF908) << 2)) - 1700;
        }
        else
        {
            object = r_u32(0x800DDD48 + (selected << 4));
            value = r_u32(0x80081938 + (r_u32(0x800CF908) << 2)) - 850;
        }
        w_u32(object + 0x1C, value);
        object = r_u32(0x800DDD48 + (selected << 4));
        w_u32(object, 0);
        func_8001b21c(0x800DDD44 + (selected << 4));
        selected = r_u32(0x800EE7F0) - 1;
        w_u32(0x800EE72C + 44 * selected, mode);
    }
    result = 44 * (r_u32(0x800EE7EC) - 1);
    w_u32(0x800EE72C + result, mode);
    return result;
}

uint32 func_8001f87c(void)
{
    FUNCTION_MARKER(0x8001F87C, "SLUS_004.64");
    w_u32(0x800CF97C, 0);
    w_u32(0x800CF980, 0);
    w_u32(0x800D85AC, 0xFFFFFFFF);
    w_u32(0x800CF984, 0);
    w_u32(0x800CF964, 0);
    return 0xFFFFFFFF;
}

uint32 func_8001a830(void)
{
    FUNCTION_MARKER(0x8001A830, "SLUS_004.64");
    w_u32(0x800CF9F0, r_u32(0x800CFA20));
    return func_8001a858(0);
}

uint32 func_8001663c(void)
{
    uint32 index;
    FUNCTION_MARKER(0x8001663C, "SLUS_004.64");
    for (index = 1; index < 7; ++index)
        func_8001f4c4(index, r_u32(0x800EE048 + 4 * index));
    return 0;
}

uint32 func_80016690(void)
{
    FUNCTION_MARKER(0x80016690, "SLUS_004.64");
    func_8001b690();
    func_80031884();
    func_8003222c(1, 0, 1, 0, 0, 0);
    func_8003222c(2, 0, 1, 0, 0, 0);
    func_8003222c(3, 26, 1, 0, 0, 0);
    if (!r_u32(0x800CFE24))
        return func_8003222c(4, 0, 1, 0, 0, 0);
    return func_8002ac0c(NULL);
}

uint32 func_80017a74(void)
{
    uint32 result;
    FUNCTION_MARKER(0x80017A74, "SLUS_004.64");
    result = r_u32(0x800CF8B4);
    if (result)
    {
        result = func_80038854();
        w_u32(0x800CF8B4, 0);
    }
    return result;
}

uint32 func_80017884(void)
{
    FUNCTION_MARKER(0x80017884, "SLUS_004.64");
    w_u32(0x800EE7EC, 1);
    w_u32(0x800EE7F0, 3);
    w_u32(0x800EE7E4, 0);
    w_u32(0x800CFA68, 0);
    w_u32(0x800CFA6C, 0);
    return 0x800EE7EC;
}

sint32 func_80023d9c(sint32 index, sint32 mode)
{
    uint32 offset;
    uint32 object;
    uint32 value;
    uint32 shift;
    FUNCTION_MARKER(0x80023D9C, "SLUS_004.64");
    offset = 44 * ((uint32)index + r_u32(0x800CF828) - 1);
    object = r_u32(0x800DDD48 + ((uint32)index << 4));
    w_u32(0x8007F06C + offset, r_u32(object + 0x18) - 400);
    object = r_u32(0x800DDD48 + ((uint32)index << 4));
    w_u32(0x8007F070 + offset, r_u32(object + 0x20) - 400);
    object = r_u32(0x800DDD48 + ((uint32)index << 4));
    w_u32(0x8007F074 + offset, r_u32(object + 0x18) + 400);
    object = r_u32(0x800DDD48 + ((uint32)index << 4));
    value = r_u32(object + 0x20);
    shift = r_u32(0x800CF908);
    w_u32(0x8007F078 + offset, value + 400);
    /* MIPS variable shifts use only the low five bits */
    w_u32(0x8007F08C + offset, (uint32)1 << (shift & 31));
    value = r_u32(0x80081978 + ((uint32)index << 2));
    w_u32(0x8007F088 + offset, (uint32)mode & value);
    return (sint32)value;
}

uint32 func_8001b21c(uint32 object)
{
    uint32 owner;
    uint32 coordinate;
    uint32 matrix;
    uint32 result;
    FUNCTION_MARKER(0x8001B21C, "SLUS_004.64");
    /* Original temporary vector is read before the coordinate writes */
    (void)r_u32(r_u32(object + 4) + 0x18);
    (void)r_u32(r_u32(object + 4) + 0x1C);
    (void)r_u32(r_u32(object + 4) + 0x20);
    owner = r_u32(object + 4);
    coordinate = r_u32(owner + 0x44);
    matrix = owner + 4;
    w_u32(coordinate + 0x18, r_u32(owner + 0x18));
    owner = r_u32(object + 4);
    w_u32(coordinate + 0x1C, r_u32(owner + 0x1C));
    owner = r_u32(object + 4);
    w_u32(coordinate + 0x20, r_u32(owner + 0x20));
    RotMatrix((SVECTOR *)psx_addr(coordinate + 0x10, sizeof(SVECTOR)), (MATRIX *)psx_addr(matrix, sizeof(MATRIX)));
    ScaleMatrix((MATRIX *)psx_addr(matrix, sizeof(MATRIX)), (VECTOR *)psx_addr(coordinate, sizeof(VECTOR)));
    TransMatrix((MATRIX *)psx_addr(matrix, sizeof(MATRIX)), (VECTOR *)psx_addr(coordinate + 0x18, sizeof(VECTOR)));
    result = r_u32(object + 4);
    w_u32(result, 0);
    return result;
}

uint32 func_80035940(uint32 object, uint32 value, uint32 unused0, uint32 unused1, uint32 extra)
{
    FUNCTION_MARKER(0x80035940, "SLUS_004.64");
    (void)unused0;
    (void)unused1;
    w_u32(object + 4, 0);
    w_u32(object, value);
    w_u32(object + 8, extra);
    return extra;
}

/* Establish a bounded native string span at a host CRT boundary */
const char *guest_c_string(uint32 address)
{
    size_t length = 0;
    while (r_u8(address + (uint32)length))
        ++length;
    return (const char *)psx_addr(address, length + 1);
}

uint32 func_8001f384(void)
{
    uint32 index;
    uint32 path;
    uint32 destination;
    FUNCTION_MARKER(0x8001F384, "SLUS_004.64");
    w_u32(0x800CF9CC, 0);
    w_u32(0x800CFE14, r_u32(0x800CFA18));
    index = 0;
    for (;;)
    {
        path = r_u32(0x8007D8C8 + 4 * index);
        if (!strcmp(guest_c_string(path), guest_c_string(0x800CF7C4)))
            break;
        path = r_u32(0x8007D8C8 + 4 * index);
        destination = r_u32(0x800CFE14);
        ++index;
        w_u32(0x800CFE14, func_8001ec00(path, destination));
    }
    w_u32(0x800CF9B8, r_u32(0x800CF9CC));
    index = 0;
    for (;;)
    {
        path = r_u32(0x8007D8BC + 4 * index);
        if (!strcmp(guest_c_string(path), guest_c_string(0x800CF7C4)))
            break;
        path = r_u32(0x8007D8BC + 4 * index);
        destination = r_u32(0x800CFE14);
        w_u32(0x800CFE14, func_8001ed6c(index, path, destination));
        ++index;
    }
    destination = r_u32(0x800CFE14);
    w_u32(0x800B1C84, destination);
    destination += 0x7210;
    w_u32(0x800B1C88, destination);
    destination += 0x7148;
    w_u32(0x800B1C8C, destination);
    destination += 0x3E80;
    w_u32(0x800B1C90, destination);
    destination += 0x7210;
    w_u32(0x800B1C94, destination);
    destination += 0xD6D8;
    w_u32(0x800B1C98, destination);
    w_u32(0x800CFA48, destination + 0x34BC);
    func_8001663c();
    w_u32(0x800CF9BC, 7);
    return 7;
}

uint32 func_80012658(void)
{
    uint32 buttons;
    FUNCTION_MARKER(0x80012658, "SLUS_004.64");
    xport_poll();
    buttons = PadRead(0);
    if (buttons == 0x900)
        func_800265ec(1);
    return buttons;
}

uint32 func_8002372c(uint32 mode)
{
    FUNCTION_MARKER(0x8002372C, "SLUS_004.64");
    if (!mode)
        return func_800237e8();
    return func_80038dc8(mode, r_s16(0x800CF81C), 1, 127);
}

sint32 func_8002138c(void)
{
    sint32 result;
    FUNCTION_MARKER(0x8002138C, "SLUS_004.64");
    result = r_s32(0x800CF7CC);
    if (!result)
        return result;
    for (;;)
    {
        func_80020e78(24, 0);
        for (;;)
        {
            func_8001eff8();
            result = func_8003d5bc(0x80082164, 0x800972E4);
            if (result != -1)
            {
                func_800210b8();
                return result;
            }
            if (func_80020e78(23, 0) != 2)
                break;
        }
    }
}

uint32 func_8003d52c(void)
{
    uint32 index;
    uint32 offset;
    FUNCTION_MARKER(0x8003D52C, "SLUS_004.64");
    for (index = 0; index < 2; ++index)
    {
        offset = 20 * index;
        w_u32(0x800D003C + offset, 2);
        w_u32(0x800D0048 + offset, 0);
        w_u32(0x800D0044 + offset, 0);
        w_u32(0x800D0040 + offset, 0x800D0064 + 16 * index);
        w_u32(0x800D004C + offset, 0x800D0070 + 16 * index);
    }
    return 0;
}

uint32 func_8003aa84(uint32 object)
{
    FUNCTION_MARKER(0x8003AA84, "SLUS_004.64");
    w_u8(object + 0x14, 128);
    w_u8(object + 0x15, 128);
    w_u8(object + 0x16, 128);
    return 128;
}

uint32 func_8003d378(uint32 base, sint32 exponent)
{
    uint32 result = 1;
    FUNCTION_MARKER(0x8003D378, "SLUS_004.64");
    while (exponent > 0)
    {
        result *= base;
        --exponent;
    }
    return result;
}

void func_8003cd88(uint32 destination, uint32 source, sint32 length)
{
    sint32 index;
    uint32 value;
    FUNCTION_MARKER(0x8003CD88, "SLUS_004.64");
    for (index = 0; index < length; ++index)
    {
        value = r_u8(source);
        if (value - 0x61 < 26)
            value += 0xE0;
        w_u8(destination, (uint8)value);
        ++destination;
        ++source;
    }
}

uint32 func_800237e8(void)
{
    FUNCTION_MARKER(0x800237E8, "SLUS_004.64");
    return func_8003905c();
}

uint32 func_8001dc98(void)
{
    uint32 owner;
    uint32 index;
    uint32 entry;
    uint32 coordinate;
    uint32 mode;
    sint32 chosen = -1;
    sint32 priority = -1;
    sint32 x;
    sint32 z;
    sint32 candidate;
    FUNCTION_MARKER(0x8001DC98, "SLUS_004.64");
    owner = 0x800DDD44 + (r_u32(0x800EE7EC) << 4);
    if (r_u32(0x80080194) == 0xFFFFFFFF)
        return 0xFFFFFFFF;
    mode = r_u32(0x800CF908);
    index = 0;
    do
    {
        entry = 56 * index;
        if (r_u32(0x80080194 + entry) && mode == r_u32(0x800801A0 + entry))
        {
            coordinate = r_u32(owner + 4);
            candidate = r_s32(0x800801BC + entry);
            x = r_s32(coordinate + 0x18);
            if (x >= candidate && r_s32(0x800801C4 + entry) >= x)
            {
                candidate = r_s32(0x800801C0 + entry);
                z = r_s32(coordinate + 0x20);
                if (z >= candidate && r_s32(0x800801C8 + entry) >= z)
                {
                    candidate = r_s32(0x8008019C + entry);
                    if (priority < candidate)
                    {
                        priority = candidate;
                        chosen = (sint32)index;
                    }
                }
            }
        }
        ++index;
    } while (r_u32(0x80080194 + 56 * index) != 0xFFFFFFFF);
    if (chosen == -1)
        return 0xFFFFFFFF;
    return func_8001db38((uint32)chosen, r_u32(0x80080198 + 56 * (uint32)chosen));
}

void func_800366a8(uint32 input_xy, uint32 input_z, uint32 rotation_xy, uint32 rotation_z, VECTOR *output)
{
    SVECTOR input;
    SVECTOR rotation;
    MATRIX *matrix;
    FUNCTION_MARKER(0x800366A8, "SLUS_004.64");
    input.vx = (sint16)input_xy;
    input.vy = (sint16)(input_xy >> 16);
    input.vz = (sint16)input_z;
    input.pad = (sint16)(input_z >> 16);
    rotation.vx = (sint16)rotation_xy;
    rotation.vy = (sint16)(rotation_xy >> 16);
    rotation.vz = (sint16)rotation_z;
    rotation.pad = (sint16)(rotation_z >> 16);
    matrix = (MATRIX *)psx_addr(0x800EBD64, sizeof(MATRIX));
    RotMatrix(&rotation, matrix);
    SetRotMatrix(matrix);
    SetTransMatrix(matrix);
    RotTrans(&input, output, (sint32 *)psx_addr(0x800CFDB4, sizeof(sint32)));
}

/* Rotate the camera offset through the existing shared GTE service */
static void camera_offset(uint32 actor, uint16 y, sint16 z, VECTOR *output)
{
    uint32 coordinate;
    uint32 rotation_x;
    uint32 rotation_y;
    uint32 rotation_z;
    coordinate = r_u32(r_u32(actor + 4) + 0x44);
    rotation_x = r_u16(coordinate + 0x10);
    coordinate = r_u32(r_u32(actor + 4) + 0x44);
    rotation_y = r_u16(coordinate + 0x12);
    coordinate = r_u32(r_u32(actor + 4) + 0x44);
    rotation_z = r_u16(coordinate + 0x14);
    /* SVECTOR padding has no arithmetic meaning in RotMatrix or RotTrans */
    func_800366a8((uint32)y << 16, (uint16)z, rotation_x | (rotation_y << 16), rotation_z, output);
    output->vx = (sint32)((uint32)output->vx + r_u32(r_u32(actor + 4) + 0x18));
    output->vy = (sint32)((uint32)output->vy + r_u32(r_u32(actor + 4) + 0x1C));
    output->vz = (sint32)((uint32)output->vz + r_u32(r_u32(actor + 4) + 0x20));
}

sint32 func_80015100(void)
{
    uint32 actor;
    uint32 mode;
    uint32 selected;
    uint32 coordinate;
    uint32 value;
    uint32 x;
    uint32 z;
    uint32 camera_y;
    uint32 delta;
    uint32 shift;
    uint32 action;
    uint32 target_offset;
    uint32 result;
    uint16 offset_y;
    uint32 crouch_offset;
    VECTOR offset;
    FUNCTION_MARKER(0x80015100, "SLUS_004.64");
    actor = 0x800DDD44 + (r_u32(0x800EE7EC) << 4);
    if (!r_u32(0x800EDFD4))
    {
        mode = r_u32(0x800EDFD8);
        if (mode == 0 || mode == 3)
        {
            selected = r_u32(0x800EE7EC);
            w_u32(0x80081978 + (selected << 2), 1);
            value = r_u32(0x800EDFD8);
            w_u32(0x800EF608, 0);
            w_u32(0x800CF90C, value);
            if (mode == 0)
                func_8001dc98();
            else
                func_8001e2f0();
            w_u32(0x800CF848, 0);
            w_u32(0x800CF84C, 0);
        }
        else if (mode == 1)
        {
            selected = r_u32(0x800EE7EC);
            w_u32(0x80081978 + (selected << 2), 1);
            w_u32(0x800CF90C, r_u32(0x800EDFD8));
            crouch_offset = r_u32(0x800EDFD0) ? 850 : 0;
            offset_y = r_u16(0x800CF9D4);
            offset_y = (uint16)(r_u16(0x800CF9D0) + offset_y);
            camera_offset(actor, offset_y, 3000, &offset);
            x = r_u32(0x800EF5EC);
            z = r_u32(0x800EF5F4);
            action = (uint32)func_8001cb14(x, z, (uint32)offset.vx, (uint32)offset.vz);
            if (action != 1)
            {
                coordinate = r_u32(actor + 4);
                x = r_u32(coordinate + 0x18);
                z = r_u32(coordinate + 0x20);
                action = (uint32)func_8001cb14(x, z, (uint32)offset.vx, (uint32)offset.vz);
            }
            if (action == 1)
            {
                camera_offset(actor, offset_y, -3000, &offset);
                coordinate = r_u32(actor + 4);
                x = r_u32(coordinate + 0x18);
                z = r_u32(coordinate + 0x20);
                if (func_8001cb14(x, z, (uint32)offset.vx, (uint32)offset.vz) == 1)
                    camera_offset(actor, (uint16)(r_u16(0x800CF9D4) - 1500), 3000, &offset);
            }
            w_u32(0x800EF608, 0);
            shift = r_u32(0x800EDFD0) ? 5 : 4;
            value = r_u32(0x800EF5EC);
            delta = (uint32)((sint32)((uint32)offset.vx - value) >> shift);
            w_u32(0x800EF5EC, value + delta);
            value = r_u32(0x800EF5F0);
            delta = (uint32)((sint32)((uint32)offset.vy - value) >> shift);
            w_u32(0x800EF5F0, value + delta);
            value = r_u32(0x800EF5F4);
            delta = (uint32)((sint32)((uint32)offset.vz - value) >> shift);
            w_u32(0x800EF5F4, value + delta);
            action = func_80031954(r_u32(0x800EE7EC));
            target_offset = 0;
            if ((action == 32 || action == 34) && !r_u32(0x800CFE24))
                target_offset = 1200;
            if (r_u32(0x800EDFD0))
                target_offset >>= 1;
            w_u32(0x800EF5F8, r_u32(r_u32(actor + 4) + 0x18));
            camera_y = r_u32(r_u32(actor + 4) + 0x1C) - 1000 + crouch_offset + target_offset;
            w_u32(0x800EF5FC, camera_y);
            w_u32(0x800EF600, r_u32(r_u32(actor + 4) + 0x20));
            if (r_u32(0x800EE7EC) == 3)
                w_u32(0x800EF5FC, camera_y + 2000);
            w_u32(0x800CF848, 0);
            w_u32(0x800CF84C, 0);
        }
        else if (mode == 2)
        {
            selected = r_u32(0x800EE7EC);
            if (selected != 3 && r_u32(0x800CFE24))
                w_u32(0x80081978 + (r_u32(0x800EE7EC) << 2), 3);
            else
            {
                if (selected != 3)
                    selected = r_u32(0x800EE7EC);
                func_80023fd8(selected, 1);
                w_u32(0x80081978 + (r_u32(0x800EE7EC) << 2), 0);
            }
            z = r_u32(0x800CFE24) ? 300 : 500;
            value = r_u32(0x800EDFD8);
            shift = r_u32(0x800EDFD0);
            w_u32(0x800CF90C, value);
            crouch_offset = shift ? (uint32)-150 : (uint32)-550;
            w_u32(0x800EF5EC, 0);
            delta = r_u32(0x800EDFAC);
            shift = r_u32(0x800EDFD0);
            w_u32(0x800EF5F4, z);
            w_u32(0x800EF5F8, 0);
            camera_y = crouch_offset - (uint32)((sint32)(delta << 1) >> (shift & 31));
            w_u32(0x800EF5F0, camera_y);
            w_u32(0x800EF5FC, camera_y);
            w_u32(0x800EF600, z - 5000);
            if (shift)
            {
                w_u32(0x800EF5F4, z >> 1);
                w_u32(0x800EF600, (uint32)((sint32)(z - 5000) >> 1));
            }
            selected = r_u32(0x800EE7EC);
            if (selected == 3)
            {
                w_u32(0x800EF608, r_u32(0x800EADD8));
                w_u32(0x800EF5F0, r_u32(0x800EF5F0) - 800);
                w_u32(0x800EF5FC, r_u32(0x800EF5FC) - 800);
            }
            else
            {
                selected = r_u32(0x800EE7EC);
                w_u32(0x800EF608, r_u32(0x800EA708 + 560 * selected));
            }
            w_u32(0x800EF604, 0);
            value = r_u16(0x800CF848);
            action = r_u16(0x800CF84C);
            func_800366a8(0, (uint16)-10000, value | (action << 16), 0, &offset);
            w_u32(0x800EF5F8, (uint32)offset.vx);
            w_u32(0x800EF5FC, (uint32)offset.vy);
            w_u32(0x800EF600, (uint32)offset.vz);
        }
    }
    func_80015a0c();
    result = 360 * r_u32(0x800EE7F8);
    w_u32(0x800EF604, result);
    return (sint32)result;
}

uint32 func_80031954(uint32 index)
{
    uint32 offset;
    uint32 action;
    FUNCTION_MARKER(0x80031954, "SLUS_004.64");
    offset = 1040 * index;
    if (!r_u32(0x800DB6F0 + offset))
        return 0xFFFFFFFF;
    action = r_u32(0x800DB6FC + offset);
    return r_u32(0x800DB2F0 + offset + (action << 5));
}

uint32 func_8001ba90(uint32 index, sint32 *x0, sint32 *z0, sint32 *x1, sint32 *z1)
{
    uint32 offset;
    sint32 transform;
    sint32 first_x;
    sint32 first_y;
    sint32 first_z;
    sint32 second_x;
    sint32 second_y;
    sint32 second_z;
    FUNCTION_MARKER(0x8001BA90, "SLUS_004.64");
    offset = 44 * index;
    transform = r_s32(0x8007F084 + offset);
    if (!transform || transform >= r_s32(0x800CFF2C))
    {
        *x0 = r_s32(0x8007F06C + offset);
        *z0 = r_s32(0x8007F070 + offset);
        *x1 = r_s32(0x8007F074 + offset);
        *z1 = r_s32(0x8007F078 + offset);
        return (uint32)*z1;
    }
    first_x = r_s32(0x8007F06C + offset);
    first_y = 0;
    first_z = r_s32(0x8007F070 + offset);
    second_x = r_s32(0x8007F074 + offset);
    second_y = 0;
    second_z = r_s32(0x8007F078 + offset);
    func_8001b6cc(transform, &first_x, &first_y, &first_z, &second_x, &second_y, &second_z);
    *x0 = first_x;
    *z0 = first_z;
    *x1 = second_x;
    *z1 = second_z;
    return (uint32)second_z;
}

sint32 func_8001cb14(uint32 x0, uint32 z0, uint32 x1, uint32 z1)
{
    sint32 start_x;
    sint32 start_z;
    sint32 end_x;
    sint32 end_z;
    sint32 left;
    sint32 top;
    sint32 right;
    sint32 bottom;
    uint32 index;
    uint32 offset;
    uint32 excluded;
    uint32 mask;
    sint32 type;
    sint32 hit;
    FUNCTION_MARKER(0x8001CB14, "SLUS_004.64");
    start_x = (sint32)x0 >> 7;
    start_z = (sint32)z0 >> 7;
    end_x = (sint32)x1 >> 7;
    end_z = (sint32)z1 >> 7;
    if (r_u32(0x8007F064) == 0xFFFFFFFF)
        return 0;
    index = 0;
    do
    {
        offset = 44 * index;
        if (!r_u32(0x8007F064 + offset) || !r_u32(0x8007F088 + offset))
            goto next_region;
        excluded = r_u32(0x800CF828);
        excluded += r_u32(0x800EE7EC) - 1;
        if (index == excluded)
            goto next_region;
        mask = r_u32(0x8007F08C + offset);
        if (mask && (sint32)(((uint32)1 << (r_u32(0x800CF908) & 31)) & mask) <= 0)
            goto next_region;
        func_8001ba90(index, &left, &top, &right, &bottom);
        left >>= 7;
        top >>= 7;
        right >>= 7;
        bottom >>= 7;
        type = r_s32(0x8007F068 + 44 * index);
        if (type == 0)
            hit = func_80036ca0(start_x, start_z, end_x, end_z, left, top, right, bottom);
        else if (type == 1)
            hit = func_80036d00(start_x, start_z, end_x, end_z, left, top, right, bottom);
        else if (type == 2)
            hit = func_80036a84(left, top, right, bottom, start_x, start_z, end_x, end_z);
        else
            goto next_region;
        if (hit)
            return 1;
next_region:
        ++index;
    } while (r_u32(0x8007F064 + 44 * index) != 0xFFFFFFFF);
    return 0;
}

uint32 func_80036858(uint32 x0, uint32 z0, uint32 x1, uint32 z1)
{
    uint32 dx;
    uint32 dz;
    uint32 square;
    FUNCTION_MARKER(0x80036858, "SLUS_004.64");
    dx = x1 - x0;
    dz = z1 - z0;
    square = dx * dx + dz * dz;
    if ((sint32)square <= 0)
        return 0;
    return SquareRoot0((sint32)square);
}

/* Preserve the original BREAK paths before signed host division */
sint32 geometry_divide(uint32 numerator, uint32 denominator)
{
    if (!denominator)
    {
        trap(7);
        abort();
    }
    if (denominator == 0xFFFFFFFF && numerator == 0x80000000)
    {
        trap(6);
        abort();
    }
    return (sint32)numerator / (sint32)denominator;
}

sint32 func_8003749c(sint32 *out_x, sint32 *out_z, sint32 x0, sint32 z0, sint32 x1, sint32 z1, sint32 x2, sint32 z2, sint32 x3, sint32 z3)
{
    uint32 dx1;
    uint32 dz1;
    uint32 dx2;
    uint32 dz2;
    uint32 first;
    uint32 second;
    uint32 denominator;
    uint32 numerator_x;
    uint32 numerator_z;
    sint32 min_x0;
    sint32 max_x0;
    sint32 min_z0;
    sint32 max_z0;
    sint32 min_x1;
    sint32 max_x1;
    sint32 min_z1;
    sint32 max_z1;
    sint32 intersect_x;
    sint32 intersect_z;
    sint32 overlap_x;
    sint32 overlap_z;
    FUNCTION_MARKER(0x8003749C, "SLUS_004.64");
    dz1 = (uint32)z1 - (uint32)z0;
    dx2 = (uint32)x3 - (uint32)x2;
    first = dz1 * dx2;
    dx1 = (uint32)x1 - (uint32)x0;
    dz2 = (uint32)z3 - (uint32)z2;
    second = dz2 * dx1;
    denominator = first - second;
    min_x0 = x0 < x1 ? x0 : x1;
    max_x0 = x0 < x1 ? x1 : x0;
    min_z0 = z0 < z1 ? z0 : z1;
    max_z0 = z0 < z1 ? z1 : z0;
    min_x1 = x2 < x3 ? x2 : x3;
    max_x1 = x2 < x3 ? x3 : x2;
    min_z1 = z2 < z3 ? z2 : z3;
    max_z1 = z2 < z3 ? z3 : z2;
    if (!denominator)
    {
        if ((((uint32)z0 * dx1 - dz1 * (uint32)x0 - (uint32)z2 * dx1) * dx2 + second * (uint32)x2) != 0)
            return 0;
        *out_x = (sint32)((uint32)x0 + (uint32)x1 + (uint32)x2 + (uint32)x3) >> 2;
        *out_z = (sint32)((uint32)z0 + (uint32)z1 + (uint32)z2 + (uint32)z3) >> 2;
        overlap_x = (min_x1 >= min_x0 && min_x1 <= max_x0) || (max_x1 >= min_x0 && max_x1 <= max_x0);
        overlap_z = (min_z1 >= min_z0 && min_z1 <= max_z0) || (max_z1 >= min_z0 && max_z1 <= max_z0);
        return overlap_x && overlap_z;
    }
    numerator_x = dx1 * dx2 * (uint32)z2 - second * (uint32)x2 - dx1 * dx2 * (uint32)z0 + first * (uint32)x0;
    intersect_x = geometry_divide(numerator_x, denominator);
    numerator_z = dz1 * dz2 * (uint32)x0 - second * (uint32)z0 + first * (uint32)z2 - dz1 * dz2 * (uint32)x2;
    intersect_z = geometry_divide(numerator_z, denominator);
    *out_x = intersect_x;
    *out_z = intersect_z;
    if (*out_x < min_x0 || *out_x > max_x0)
        return 0;
    if (*out_z < min_z0 || *out_z > max_z0)
        return 0;
    if (*out_x < min_x1 || *out_x > max_x1)
        return 0;
    return *out_z >= min_z1 && *out_z <= max_z1;
}

sint32 func_80036ca0(sint32 x0, sint32 z0, sint32 x1, sint32 z1, sint32 left, sint32 top, sint32 right, sint32 bottom)
{
    sint32 intersect_x;
    sint32 intersect_z;
    FUNCTION_MARKER(0x80036CA0, "SLUS_004.64");
    return func_8003749c(&intersect_x, &intersect_z, x0, z0, x1, z1, left, top, right, bottom) == 1;
}

sint32 func_80036a84(sint32 left, sint32 top, sint32 right, sint32 bottom, sint32 x0, sint32 z0, sint32 x1, sint32 z1)
{
    sint32 min_x;
    sint32 max_x;
    sint32 min_z;
    sint32 max_z;
    sint32 intersect_x;
    sint32 intersect_z;
    FUNCTION_MARKER(0x80036A84, "SLUS_004.64");
    min_x = left < right ? left : right;
    max_x = left < right ? right : left;
    min_z = top < bottom ? top : bottom;
    max_z = top < bottom ? bottom : top;
    if (func_8003749c(&intersect_x, &intersect_z, x0, z0, x1, z1, left, top, right, top))
        return 1;
    if (func_8003749c(&intersect_x, &intersect_z, x0, z0, x1, z1, right, top, right, bottom))
        return 1;
    if (func_8003749c(&intersect_x, &intersect_z, x0, z0, x1, z1, right, bottom, left, bottom))
        return 1;
    if (func_8003749c(&intersect_x, &intersect_z, x0, z0, x1, z1, left, bottom, left, top))
        return 1;
    if (x0 >= min_x && x0 <= max_x && z0 >= min_z && z0 <= max_z)
        return 1;
    return x1 >= min_x && x1 <= max_x && z1 >= min_z && z1 <= max_z;
}

sint32 func_80036d00(sint32 x0, sint32 z0, sint32 x1, sint32 z1, sint32 left, sint32 top, sint32 right, sint32 bottom)
{
    uint32 length;
    sint32 center_x;
    sint32 center_z;
    FUNCTION_MARKER(0x80036D00, "SLUS_004.64");
    length = func_80036858((uint32)x0, (uint32)z0, (uint32)x1, (uint32)z1);
    center_x = (sint32)((uint32)x0 + (uint32)x1) >> 1;
    center_z = (sint32)((uint32)z0 + (uint32)z1) >> 1;
    return func_80036eec(center_x, center_z, (sint32)length >> 1, left, top, right, bottom) != 0;
}

sint32 func_80036eec(sint32 center_x, sint32 center_z, sint32 radius, sint32 x0, sint32 z0, sint32 x1, sint32 z1)
{
    uint32 dx;
    uint32 dz;
    uint32 reverse_dx;
    uint32 z_square;
    uint32 x_product;
    uint32 denominator;
    uint32 cross;
    uint32 numerator;
    sint32 projection_x;
    sint32 projection_z;
    FUNCTION_MARKER(0x80036EEC, "SLUS_004.64");
    if (radius >= (sint32)func_80036858((uint32)center_x, (uint32)center_z, (uint32)x0, (uint32)z0))
        return 1;
    if (radius >= (sint32)func_80036858((uint32)center_x, (uint32)center_z, (uint32)x1, (uint32)z1))
        return 1;
    dz = (uint32)z1 - (uint32)z0;
    z_square = dz * dz;
    dx = (uint32)x1 - (uint32)x0;
    reverse_dx = 0 - dx;
    x_product = reverse_dx * dx;
    denominator = z_square - x_product;
    if (!denominator)
        return 0;
    cross = dx * dz;
    numerator = cross * (uint32)center_z - x_product * (uint32)center_x - cross * (uint32)z0 + z_square * (uint32)x0;
    projection_x = geometry_divide(numerator, denominator);
    cross = dz * reverse_dx;
    numerator = cross * (uint32)x0 - x_product * (uint32)z0 + z_square * (uint32)center_z - cross * (uint32)center_x;
    projection_z = geometry_divide(numerator, denominator);
    if (radius < (sint32)func_80036858((uint32)center_x, (uint32)center_z, (uint32)projection_x, (uint32)projection_z))
        return 0;
    if (projection_x < (x0 < x1 ? x0 : x1) || projection_x > (x0 < x1 ? x1 : x0))
        return 0;
    return projection_z >= (z0 < z1 ? z0 : z1) && projection_z <= (z0 < z1 ? z1 : z0);
}

static void transform_point(sint32 *x, sint32 *y, sint32 *z)
{
    uint32 scale;
    uint32 product;
    uint16 component;
    scale = r_u32(0x800D7924);
    product = (uint32)*x * scale;
    w_u32(0x800EF5AC, (uint32)((sint32)product >> 12));
    product = (uint32)*y;
    scale = r_u32(0x800D7928);
    product *= scale;
    w_u32(0x800EF5B0, (uint32)((sint32)product >> 12));
    product = (uint32)*z;
    scale = r_u32(0x800D792C);
    product *= scale;
    w_u32(0x800EF5B4, (uint32)((sint32)product >> 12));
    w_u16(0x800CFE2C, r_u16(0x800EF5AC));
    w_u16(0x800CFE2E, r_u16(0x800EF5B0));
    component = r_u16(0x800EF5B4);
    w_u32(0x800CFDB4, 0);
    w_u16(0x800CFE30, component);
    RotTrans((SVECTOR *)psx_addr(0x800CFE2C, sizeof(SVECTOR)), (VECTOR *)psx_addr(0x800EB9C4, sizeof(VECTOR)), (sint32 *)psx_addr(0x800CFDB4, sizeof(sint32)));
    *x = r_s32(0x800EB9C4);
    *y = r_s32(0x800EB9C8);
    *z = r_s32(0x800EB9CC);
}

void func_8001b6cc(sint32 index, sint32 *x0, sint32 *y0, sint32 *z0, sint32 *x1, sint32 *y1, sint32 *z1)
{
    uint32 actor;
    uint32 coordinate;
    sint32 parent;
    FUNCTION_MARKER(0x8001B6CC, "SLUS_004.64");
    if (!index)
        return;
    for (;;)
    {
        actor = 0x800DDD44 + ((uint32)index << 4);
        coordinate = r_u32(r_u32(actor + 4) + 0x44);
        w_u32(0x800D7924, r_u32(coordinate));
        coordinate = r_u32(r_u32(actor + 4) + 0x44);
        w_u32(0x800D7928, r_u32(coordinate + 4));
        coordinate = r_u32(r_u32(actor + 4) + 0x44);
        w_u32(0x800D792C, r_u32(coordinate + 8));
        w_u32(0x800EF5AC, r_u32(r_u32(actor + 4) + 0x18));
        w_u32(0x800EF5B0, r_u32(r_u32(actor + 4) + 0x1C));
        w_u32(0x800EF5B4, r_u32(r_u32(actor + 4) + 0x20));
        TransMatrix((MATRIX *)psx_addr(0x800F0248, sizeof(MATRIX)), (VECTOR *)psx_addr(0x800EF5AC, sizeof(VECTOR)));
        SetTransMatrix((MATRIX *)psx_addr(0x800F0248, sizeof(MATRIX)));
        coordinate = r_u32(r_u32(actor + 4) + 0x44);
        w_u16(0x800CFDCC, r_u16(coordinate + 0x10));
        coordinate = r_u32(r_u32(actor + 4) + 0x44);
        w_u16(0x800CFDCE, r_u16(coordinate + 0x12));
        coordinate = r_u32(r_u32(actor + 4) + 0x44);
        w_u16(0x800CFDD0, r_u16(coordinate + 0x14));
        RotMatrix((SVECTOR *)psx_addr(0x800CFDCC, sizeof(SVECTOR)), (MATRIX *)psx_addr(0x800F0268, sizeof(MATRIX)));
        SetRotMatrix((MATRIX *)psx_addr(0x800F0268, sizeof(MATRIX)));
        transform_point(x0, y0, z0);
        transform_point(x1, y1, z1);
        parent = r_s32(0x800F0054 + ((uint32)index << 2));
        if (!parent || parent >= r_s32(0x800CFF2C))
            break;
        index = parent;
    }
}

uint32 func_8001db38(uint32 index, uint32 value)
{
    uint32 offset;
    uint32 actor;
    uint32 level;
    uint32 height;
    uint32 result;
    FUNCTION_MARKER(0x8001DB38, "SLUS_004.64");
    offset = 56 * index;
    actor = 0x800DDD44 + (r_u32(0x800EE7EC) << 4);
    w_u32(0x800EF5EC, r_u32(0x800801A4 + offset));
    level = r_u32(0x800801A0 + offset);
    height = r_u32(0x800801A8 + offset);
    height += r_u32(0x80081938 + (level << 2));
    w_u32(0x800EF5F0, height);
    w_u32(0x800EF5F4, r_u32(0x800801AC + offset));
    if (value)
    {
        w_u32(0x800EF5F8, r_u32(r_u32(actor + 4) + 0x18));
        w_u32(0x800EF5FC, r_u32(r_u32(actor + 4) + 0x1C));
        result = r_u32(r_u32(actor + 4) + 0x20);
    }
    else
    {
        w_u32(0x800EF5F8, r_u32(0x800801B0 + offset));
        level = r_u32(0x800801A0 + offset);
        height = r_u32(0x800801B4 + offset);
        height += r_u32(0x80081938 + (level << 2));
        w_u32(0x800EF5FC, height);
        result = r_u32(0x800801B8 + offset);
    }
    w_u32(0x800EF600, result);
    return result;
}

static void camera_approach(uint32 address, uint32 velocity_address, uint32 target, sint32 stop_on_equal)
{
    sint32 velocity;
    uint32 value;
    sint32 stop;
    velocity = r_s32(velocity_address);
    if (!velocity)
        return;
    value = r_u32(address) + (uint32)velocity;
    w_u32(address, value);
    if (velocity > 0)
        stop = stop_on_equal ? (sint32)value >= (sint32)target : (sint32)value > (sint32)target;
    else
        stop = stop_on_equal ? (sint32)value <= (sint32)target : (sint32)value < (sint32)target;
    if (stop)
    {
        w_u32(address, target);
        w_u32(velocity_address, 0);
    }
}

void func_8001e2f0(void)
{
    uint32 actor;
    sint32 mode;
    uint32 offset;
    uint32 level;
    uint32 height;
    uint32 camera_x;
    uint32 camera_y;
    uint32 camera_z;
    uint32 target_x;
    uint32 target_y;
    uint32 target_z;
    uint32 value;
    uint32 next;
    FUNCTION_MARKER(0x8001E2F0, "SLUS_004.64");
    actor = 0x800DDD44 + (r_u32(0x800EE7EC) << 4);
    mode = r_s32(0x800CF88C);
    w_u32(0x800EF608, 0);
    if (mode == 0)
    {
        value = r_u32(0x800CF884);
        if (value != 0xFFFFFFFF)
            func_8001db38(value, r_u32(0x800CF888));
        return;
    }
    if (mode != 1 && mode != 2)
        return;
    offset = 56 * r_u32(0x800CF884);
    level = r_u32(0x800801A0 + offset);
    camera_x = r_u32(0x800801A4 + offset);
    if (mode == 1)
    {
        camera_y = r_u32(0x800801A8 + offset);
        height = r_u32(0x80081938 + (level << 2));
        camera_z = r_u32(0x800801AC + offset);
        target_x = r_u32(0x800801B0 + offset);
        target_y = r_u32(0x800801B4 + offset);
        target_z = r_u32(0x800801B8 + offset);
        camera_y += height;
        target_y += height;
        value = r_u32(0x800EF5EC);
        next = value + (uint32)((sint32)(camera_x - value) >> 4);
        value = r_u32(0x800EF5F0);
        w_u32(0x800EF5EC, next);
        next = value + (uint32)((sint32)(camera_y - value) >> 4);
        value = r_u32(0x800EF5F4);
        w_u32(0x800EF5F0, next);
        w_u32(0x800EF5F4, value + (uint32)((sint32)(camera_z - value) >> 4));
        if (r_u32(0x800CF888))
        {
            w_u32(0x800EF5F8, r_u32(r_u32(actor + 4) + 0x18));
            w_u32(0x800EF5FC, r_u32(r_u32(actor + 4) + 0x1C));
            w_u32(0x800EF600, r_u32(r_u32(actor + 4) + 0x20));
        }
        else
        {
            value = r_u32(0x800EF5F8);
            next = value + (uint32)((sint32)(target_x - value) >> 4);
            value = r_u32(0x800EF5FC);
            w_u32(0x800EF5F8, next);
            next = value + (uint32)((sint32)(target_y - value) >> 4);
            value = r_u32(0x800EF600);
            w_u32(0x800EF5FC, next);
            w_u32(0x800EF600, value + (uint32)((sint32)(target_z - value) >> 4));
        }
        return;
    }
    height = r_u32(0x80081938 + (level << 2));
    camera_y = r_u32(0x800801A8 + offset);
    camera_z = r_u32(0x800801AC + offset);
    target_y = r_u32(0x800801B4 + offset);
    target_x = r_u32(0x800801B0 + offset);
    target_z = r_u32(0x800801B8 + offset);
    target_y += height;
    camera_y += height;
    camera_approach(0x800EF5EC, 0x800CF890, camera_x, 1);
    camera_approach(0x800EF5F0, 0x800CF894, camera_y, 1);
    camera_approach(0x800EF5F4, 0x800CF898, camera_z, 1);
    if (r_u32(0x800CF888))
    {
        w_u32(0x800EF5F8, r_u32(r_u32(actor + 4) + 0x18));
        w_u32(0x800EF5FC, r_u32(r_u32(actor + 4) + 0x1C));
        w_u32(0x800EF600, r_u32(r_u32(actor + 4) + 0x20));
    }
    else
    {
        camera_approach(0x800EF5F8, 0x800CF89C, target_x, 1);
        /* Original target Y clamps negative motion only after passing */
        value = (uint32)r_s32(0x800CF8A0);
        if (value)
        {
            next = r_u32(0x800EF5FC) + value;
            w_u32(0x800EF5FC, next);
            if (((sint32)value > 0 && (sint32)next >= (sint32)target_y) || ((sint32)value < 0 && (sint32)next < (sint32)target_y))
            {
                w_u32(0x800EF5FC, target_y);
                w_u32(0x800CF8A0, 0);
            }
        }
        camera_approach(0x800EF600, 0x800CF8A4, target_z, 0);
    }
}

uint32 func_80028a94(void)
{
    FUNCTION_MARKER(0x80028A94, "SLUS_004.64");
    while (PadRead(0) & 0x40)
        ;
    while (!(PadRead(0) & 0x40))
        ;
    return 0x40;
}

void func_80021478(void)
{
    FUNCTION_MARKER(0x80021478, "SLUS_004.64");
    if (r_u32(0x800CF7CC))
    {
        func_80020e78(23, 1);
        VSyncCallback(vsync_callback);
    }
}

void func_800214b4(void)
{
    sint32 mode;
    FUNCTION_MARKER(0x800214B4, "SLUS_004.64");
    mode = r_s32(0x800CF95C);
    if (mode == 1)
        func_800389fc();
    else if (mode == 2)
        func_80038c14();
    SsSeqCalledTbyT();
}

uint32 func_8003905c(void)
{
    uint32 cursor;
    uint16 value;
    sint16 sequence;
    FUNCTION_MARKER(0x8003905C, "SLUS_004.64");
    cursor = 0x800EC1E4;
    for (;;)
    {
        value = r_u16(cursor);
        sequence = r_s16(cursor);
        if (sequence == 99)
            return (uint32)value << 16;
        if ((sint16)value != -1 && (sint16)SsIsEos((sint16)value, 0) == 1)
            SsSeqStop(r_s16(cursor));
        cursor += 8;
    }
}

uint32 func_800390d8(void)
{
    uint32 cursor;
    uint32 offset;
    uint16 sequence;
    sint16 sentinel;
    FUNCTION_MARKER(0x800390D8, "SLUS_004.64");
    cursor = 0x800EC1E4;
    sequence = r_u16(cursor);
    sentinel = r_s16(cursor);
    while (sentinel != 99)
    {
        cursor += 8;
        if ((sint16)sequence != -1)
            func_80078db4((sint16)sequence);
        sentinel = r_s16(cursor);
        sequence = r_u16(cursor);
    }
    w_u16(0x800EC2E4, 99);
    w_u32(0x800EC2E8, 99);
    for (offset = 0; offset < 0x100; offset += 8)
    {
        w_u32(0x800EC1E8 + offset, 0xFFFFFFFF);
        w_u16(0x800EC1E4 + offset, 0xFFFF);
    }
    return 0;
}

void func_80039204(sint16 bank)
{
    FUNCTION_MARKER(0x80039204, "SLUS_004.64");
    func_800390d8();
    SsVabClose(bank);
}

void func_8003a3d0(const char *path, uint32 destination, uint32 offset, uint32 length, uint32 enabled)
{
    FUNCTION_MARKER(0x8003A3D0, "SLUS_004.64");
    load_resource_rectangle(path, destination, offset, length, enabled, 320, 0x00F00140);
}

sint32 func_8003e18c(uint32 first, uint32 second)
{
    sint32 result;
    FUNCTION_MARKER(0x8003E18C, "SLUS_004.64");
    result = func_8003fa54(first, second);
    if (result == 0 || result == -2)
        result = func_8003fa54(first, second);
    return result;
}

void func_80040eec(void)
{
    FUNCTION_MARKER(0x80040EEC, "SLUS_004.64");
    func_8003fd20();
}

void func_80024090(void)
{
    FUNCTION_MARKER(0x80024090, "SLUS_004.64");
    w_u32(0x800CFE0C, 0);
    w_u32(0x800CFE1C, 0);
    w_u32(0x800CFF7C, 0);
    w_u32(0x800CFF6C, 0);
    w_u32(0x800CFD9C, 0);
}

uint32 func_80041444(uint32 value)
{
    uint32 offset;
    FUNCTION_MARKER(0x80041444, "SLUS_004.64");
    for (offset = 0; offset < 72; offset += 36)
    {
        func_800414bc(value, 0x800D024C + offset);
        func_800414bc(value, 0x800D0294 + offset);
    }
    return 0;
}

void func_800414bc(uint32 value, uint32 object)
{
    FUNCTION_MARKER(0x800414BC, "SLUS_004.64");
    w_u8(object + 20, (uint8)value);
    w_u8(object + 21, (uint8)value);
    w_u8(object + 22, (uint8)value);
}

uint32 func_80041410(void)
{
    uint32 value;
    FUNCTION_MARKER(0x80041410, "SLUS_004.64");
    value = r_u32(0x800CFD48);
    w_u32(0x800CFD48, value == 0);
    return 1;
}

sint32 func_8004132c(void)
{
    sint32 result;
    sint32 current;
    sint32 target;
    FUNCTION_MARKER(0x8004132C, "SLUS_004.64");
    result = r_s32(0x800CFD70);
    if (result > 0)
    {
        current = r_s32(0x800CFD58);
        target = r_s32(0x800CFD68);
        if (current >= target)
        {
            w_u32(0x800CFC5C, 2);
            w_u32(0x800CFD58, (uint32)target);
            return 2;
        }
        result = r_s32(0x800CFD70);
    }
    if (result < 0)
    {
        current = r_s32(0x800CFD58);
        target = r_s32(0x800CFD68);
        result = 2;
        if (target >= current)
        {
            w_u32(0x800CFC5C, 2);
            w_u32(0x800CFD58, (uint32)target);
        }
    }
    return result;
}
