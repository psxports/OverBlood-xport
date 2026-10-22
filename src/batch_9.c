#include "functions.h"
#include <string.h>

/* Full original bodies, pending final integration and runtime validation */
sint32 func_80035814(const char *path, uint32 destination)
{
    sint32 handle, size, amount;
    uint32 remaining, position, current, transferred;
    FUNCTION_MARKER(0x80035814, "SLUS_004.64");
    handle = PCopen((char *)path, 0, 0);
    if (handle == -1)
        return -1;
    size = PClseek(handle, 0, 2);
    remaining = (uint32)size;
    current = destination;
    position = 0;
    for (;;)
    {
        PClseek(handle, (sint32)position, 0);
        amount = (sint32)remaining > 65534 ? 65534 : (sint32)remaining;
        transferred = (uint32)func_8006e698(handle, current, amount);
        remaining -= transferred;
        if (transferred == 0)
            break;
        current += transferred;
        if ((sint32)remaining <= 0)
            break;
        position += transferred;
    }
    PCclose(handle);
    return size;
}

uint32 func_80036384(const char *path, uint32 destination, uint32 offset, uint32 length)
{
    sint32 handle, amount;
    uint32 remaining, current, transferred, total;
    FUNCTION_MARKER(0x80036384, "SLUS_004.64");
    handle = PCopen((char *)path, 0, 0);
    if (handle == -1)
    {
        func_800360d4(path);
        return 0;
    }
    PClseek(handle, 0, 2);
    PClseek(handle, (sint32)offset, 0);
    remaining = length;
    current = destination;
    total = 0;
    do
    {
        PClseek(handle, (sint32)(offset + total), 0);
        amount = (sint32)remaining > 65534 ? 65534 : (sint32)remaining;
        transferred = (uint32)func_8006e698(handle, current, amount);
        if (transferred == 0)
            break;
        current += transferred;
        remaining -= transferred;
        total += transferred;
    }
    while ((sint32)remaining > 0);
    PCclose(handle);
    memset(psx_addr(current, 2048), 0, 2048);
    return total;
}

uint32 func_8003658c(const char *path, uint32 source, uint32 length)
{
    sint32 handle, amount;
    uint32 remaining, position, current, transferred;
    FUNCTION_MARKER(0x8003658C, "SLUS_004.64");
    handle = PCcreat((char *)path, 0);
    remaining = length;
    current = source;
    position = 0;
    for (;;)
    {
        PClseek(handle, (sint32)position, 0);
        amount = (sint32)remaining > 65534 ? 65534 : (sint32)remaining;
        transferred = (uint32)func_8006e95c(handle, current, amount);
        remaining -= transferred;
        if (transferred == 0)
            break;
        current += transferred;
        if ((sint32)remaining <= 0)
            break;
        position += transferred;
    }
    PCclose(handle);
    return length;
}

void func_80018e7c(sint32 identifier)
{
    char pattern[64], path[64], *digits;
    uint8 parts[3];
    uint32 blocked, actor, index, music, destination;
    FUNCTION_MARKER(0x80018E7C, "SLUS_004.64");
    memcpy(pattern, psx_addr(0x80010464, 27), 27);
    memset(pattern + 27, 0, 37);
    blocked = 1;
    if (r_u32(0x800CF878) != 0 && r_u32(0x800CF8E4) == 0 && r_u32(0x800CF844) == 0)
    {
        actor = r_u32(0x800EE7EC);
        blocked = r_s32(0x800E9A58 + (actor << 2)) > 0;
    }
    if (blocked != 0)
    {
        func_80028c44("    DONT SAVE NOW!");
        func_8002372c(2);
        func_80028a94();
        return;
    }
    strcpy(path, pattern);
    digits = strchr(path, '?');
    parts[0] = (uint8)(identifier / 100);
    parts[1] = (uint8)((identifier % 100) / 10);
    parts[2] = (uint8)((identifier % 100) % 10);
    for (index = 0; index < 3; ++index)
        digits[index] = (char)(parts[index] + 48);
    music = r_u32(0x800CF8B4);
    w_u32(0x800EDFB8, music);
    func_80017a74();
    func_80018284();
    destination = r_u32(0x800CF9FC);
    func_800417c0(destination, 0x800EDFA8, 5628);
    destination = r_u32(0x800CF9FC);
    func_8003658c(path, destination, 5628);
    func_8001f13c();
    w_u32(0x800CF8B4, 0);
    if ((sint32)music > 0)
    {
        if ((sint32)music < 101)
            func_800178b0((sint32)music, 0);
        else
            func_80017aa0((sint32)(music - 100), 0);
    }
}

uint32 func_8004087c(const char *name)
{
    char path[26];
    uint32 index, prefix;
    FUNCTION_MARKER(0x8004087C, "SLUS_004.64");
    for (index = 26; index != 0; --index)
        path[index - 1] = 0;
    prefix = r_u32(0x800CFD40) == 0 ? 0x800CFC3C : 0x800CFC44;
    strncpy(path, (const char *)psx_addr(prefix, 5), 5);
    strncpy(path + 5, name, 16);
    if (func_800416f0(path) != 0)
        return 1;
    return func_800416f0(path) != 0;
}

uint32 func_80040920(const char *name)
{
    char path[26];
    uint32 index, prefix;
    sint32 handle;
    FUNCTION_MARKER(0x80040920, "SLUS_004.64");
    for (index = 26; index != 0; --index)
        path[index - 1] = 0;
    prefix = r_u32(0x800CFD40) == 0 ? 0x800CFC3C : 0x800CFC44;
    strncpy(path, (const char *)psx_addr(prefix, 5), 5);
    strncpy(path + 5, name, 16);
    handle = openPSX(path, 0x10200);
    if (handle == -1)
    {
        handle = openPSX(path, 0x10200);
        if (handle == -1)
            return 0;
    }
    closePSX(handle);
    return 1;
}

uint32 func_80040748(const char *name, uint32 *data, uint32 slot, uint32 *work)
{
    char path[26];
    uint32 index, prefix, value;
    sint32 handle;
    FUNCTION_MARKER(0x80040748, "SLUS_004.64");
    for (index = 26; index != 0; --index)
        path[index - 1] = 0;
    prefix = r_u32(0x800CFD40) == 0 ? 0x800CFC3C : 0x800CFC44;
    strncpy(path, (const char *)psx_addr(prefix, 5), 5);
    strncpy(path + 5, name, 16);
    handle = openPSX(path, 1);
    if (handle == -1)
        return 0;
    if (lseekPSX(handle, 512, 0) == -1)
    {
        closePSX(handle);
        return 0;
    }
    if (readPSX(handle, work, 5632) != 5632)
    {
        closePSX(handle);
        return 0;
    }
    for (index = 0; index < 1407; ++index)
    {
        value = work[index];
        data[index] = value;
    }
    closePSX(handle);
    return 1;
}

uint32 func_800409e4(const char *name, uint32 *data, uint32 slot, uint8 *header)
{
    char path[26];
    uint32 index, prefix;
    sint32 handle;
    FUNCTION_MARKER(0x800409E4, "SLUS_004.64");
    for (index = 26; index != 0; --index)
        path[index - 1] = 0;
    prefix = r_u32(0x800CFD40) == 0 ? 0x800CFC3C : 0x800CFC44;
    strncpy(path, (const char *)psx_addr(prefix, 5), 5);
    strncpy(path + 5, name, 16);
    handle = openPSX(path, 2);
    if (handle == -1)
        return 0;
    func_80040b04(header, slot, data);
    if (writePSX(handle, header, 512) != 512)
    {
        closePSX(handle);
        return 0;
    }
    if (writePSX(handle, data, 5632) != 5632)
    {
        closePSX(handle);
        return 0;
    }
    closePSX(handle);
    return 1;
}

void func_80040b04(uint8 *header, uint32 slot, uint32 *data)
{
    uint32 words[3], index, offset, value;
    uint8 tail, byte0, byte1, byte2, *icons, *frame;
    sint32 mode;
    FUNCTION_MARKER(0x80040B04, "SLUS_004.64");
    header[0] = 83;
    header[1] = 67;
    header[2] = 19;
    header[3] = 1;
    for (index = 0; index < 3; ++index)
    {
        r_u32(0x80011630 + 4 * index);
        words[index] = r_u32(0x80011630 + 4 * index);
    }
    memcpy(header + 4, words, 12);
    r_u32(0x8001163C);
    words[0] = r_u32(0x8001163C);
    r_u32(0x80011640);
    words[1] = r_u32(0x80011640);
    tail = (uint8)r_s8(0x80011644);
    memcpy(header + 16, words, 8);
    header[24] = tail;
    header[24] = 0x82;
    header[25] = (uint8)(slot + 80);
    r_u32(0x800CFC4C);
    value = r_u32(0x800CFC4C);
    byte0 = (uint8)r_s8(0x800CFC50);
    byte1 = (uint8)r_s8(0x800CFC51);
    memcpy(header + 26, &value, 4);
    header[30] = byte0;
    header[31] = byte1;
    tail = (uint8)r_s8(0x800CFC52);
    header[32] = tail;
    header[32] = 0x82;
    header[33] = (uint8)(((uint8 *)data)[12] + 79);
    byte0 = (uint8)r_s8(0x800CFC54);
    byte1 = (uint8)r_s8(0x800CFC55);
    byte2 = (uint8)r_s8(0x800CFC56);
    header[34] = byte0;
    header[35] = byte1;
    header[36] = byte2;
    value = data[2];
    icons = header + 512;
    func_80040d24((sint32)value, header + 38);
    for (index = 28; index != 0; --index)
        header[68 + index - 1] = 0;
    DrawSync(0);
    ResetGraph(1);
    func_8003943c(0);
    mode = r_s32(0x800CF7D0);
    load_native_resource("ETCCG\\ICON.ALL", icons, mode);
    memcpy(&offset, icons + 36, 4);
    frame = icons + offset;
    for (index = 0; index < 32; ++index)
        header[96 + index] = frame[20 + index];
    for (index = 0; index < 128; ++index)
        header[128 + index] = frame[64 + index];
    memcpy(&offset, icons + 76, 4);
    frame = icons + offset;
    for (index = 0; index < 128; ++index)
        header[256 + index] = frame[64 + index];
    memcpy(&offset, icons + 116, 4);
    frame = icons + offset;
    for (index = 0; index < 128; ++index)
        header[384 + index] = frame[64 + index];
}

void func_80017d0c(uint32 *selection, uint32 *value)
{
    uint32 response[3], index, actor, mode;
    sint32 stream;
    FUNCTION_MARKER(0x80017D0C, "SLUS_004.64");
    func_8004df4c(0, 0, 0, 0);
    GsSwapDispBuff();
    func_80037a30(response, 0x80081F9C, 1);
    FntLoad(960, 256);
    stream = FntOpen(-144, -104, 320, 200, 0, 512);
    SetDumpFnt(stream);
    func_8004df4c(0, 0, 0, 240);
    switch (response[0])
    {
    case 0:
        if (response[2] != 0)
        {
            mode = r_u32(0x800CFA6C);
            w_u32(0x800CFA90, 1);
            w_u32(0x800814B8, 0xFFFFFFFF);
            func_80022320(mode, response[2], 1);
            func_8003537c(response[2]);
        }
        break;
    case 1:
        w_u32(0x800CFE0C, response[2]);
        break;
    case 2:
        func_80020834(response[2]);
        for (index = 1; index < 5; ++index)
            func_80020b7c(index, response[2]);
        break;
    case 3:
        func_80018e7c((sint32)response[2]);
        break;
    case 4:
        func_800190ec((sint32)response[2]);
        break;
    case 5:
        func_80017a74();
        func_80021130((sint32)response[2]);
        break;
    case 9:
        index = response[2];
        if (r_u32(0x80081978 + (index << 2)) == 0)
        {
            func_8001e8b4((sint32)index);
            if (response[2] == 3)
                w_u32(0x800819A4, 3);
            else
                w_u32(0x80081998 + (response[2] << 2), 1);
            index = response[2];
            actor = r_u32(0x800EE7EC);
            if (index != actor)
                w_u32(0x800EE7F0, index);
        }
        else
            func_8001e8d8((sint32)index);
        break;
    case 10:
        func_8001de3c(response[2], 1, 1, 30);
        break;
    case 11:
        func_8001de3c(response[2], 1, 0, 30);
        break;
    case 12:
        while (func_80012658() != 0)
        {
        }
        func_80018100(response[2], 180, 1);
        for (;;)
        {
            if (func_8003cba4() == 0 && r_u32(0x800CF8D8) == 2)
                break;
            func_80012bfc();
        }
        break;
    case 13:
        func_80023b2c(response[2]);
        break;
    case 14:
        actor = r_u32(0x800EE7EC);
        func_80031c20(actor, response[2], 1, 0, 0, 0);
        func_8001fbcc();
        actor = r_u32(0x800EE7EC);
        while (r_u32(0x800DB6F0 + 1040 * actor) != 0)
        {
            func_80012bfc();
            actor = r_u32(0x800EE7EC);
        }
        func_8001fbd8();
        actor = r_u32(0x800EE7EC);
        func_80031c20(actor, 0, 1, 0, 0, 0);
        actor = r_u32(0x800EE7EC);
        func_80032320(actor, 0);
        break;
    case 15:
        func_8002dd84(response[2]);
        func_8002e2ac(response[2]);
        break;
    case 16:
        func_8002a8c8(response[2]);
        break;
    default:
        break;
    }
    *selection = response[0];
    if (response[0] != 0xFFFFFFFF)
        *value = response[2];
}

uint32 func_8003816c(void)
{
    static const uint32 edge_masks[8] = {0x20, 0x40, 0x10, 0x80, 4, 8, 1, 2};
    static const uint32 edge_latches[8] = {0x800CFBF8, 0x800CFBF9, 0x800CFBFB, 0x800CFBFA, 0x800CFBFC, 0x800CFBFD, 0x800CFBFE, 0x800CFBFF};
    static const uint32 edge_results[8] = {5, 6, 8, 7, 9, 10, 11, 12};
    static const uint32 direction_masks[4] = {0x1000, 0x4000, 0x8000, 0x2000};
    uint32 input, index, state, timer;
    FUNCTION_MARKER(0x8003816C, "SLUS_004.64");
    input = PadRead(0);
    for (index = 0; index < 4; ++index)
    {
        if ((input & edge_masks[index]) != 0)
        {
            if (r_u8(edge_latches[index]) == 0)
            {
                w_u8(edge_latches[index], 1);
                return edge_results[index];
            }
        }
        else
            w_u8(edge_latches[index], 0);
    }
    for (index = 0; index < 4; ++index)
    {
        if ((input & direction_masks[index]) != 0)
        {
            state = r_u8(0x800CFBF4 + index);
            if (state == 0)
            {
                w_u8(0x800CFBF4 + index, 1);
                w_u32(0x800CFC14, 30);
                return index + 1;
            }
            if (state == 1)
            {
                timer = r_u32(0x800CFC14) - 1;
                w_u32(0x800CFC14, timer);
                if (timer == 0)
                    w_u8(0x800CFBF4 + index, 2);
            }
            else if (state == 2)
            {
                timer = r_u32(0x800CFC14);
                if (timer == 0)
                {
                    w_u32(0x800CFC14, 5);
                    return index + 1;
                }
                w_u32(0x800CFC14, timer - 1);
            }
        }
        else
            w_u8(0x800CFBF4 + index, 0);
    }
    for (index = 4; index < 8; ++index)
    {
        if ((input & edge_masks[index]) != 0)
        {
            if (r_u8(edge_latches[index]) == 0)
            {
                w_u8(edge_latches[index], 1);
                return edge_results[index];
            }
        }
        else
            w_u8(edge_latches[index], 0);
    }
    return 0;
}

uint32 func_80037df8(uint32 entry, uint32 menu_index)
{
    uint32 count, kind, list, cursor, visible, selected, scroll, row, highlighted, text, number;
    uint32 input, callback, cell, last, limit, before;
    FUNCTION_MARKER(0x80037DF8, "SLUS_004.64");
    func_800385b4();
    kind = r_u32(entry);
    count = 0;
    if (kind != 0)
        count = kind;
    else
    {
        list = r_u32(entry + 12);
        cursor = list;
        while (r_u32(cursor) != 0xFFFFFFFF)
        {
            cursor += 4;
            ++count;
        }
    }
    visible = (sint32)count < 7 ? count : 7;
    cell = menu_index << 2;
    selected = 0;
    if (r_u32(0x800B4BDC + cell) == count)
    {
        selected = r_u32(0x800B4ADC + cell);
        scroll = r_u32(0x800B4B5C + cell);
    }
    else
        scroll = 0;
    for (;;)
    {
        text = r_u32(entry + 4);
        FntPrint("<< %s >>\n\n", guest_c_string(text));
        highlighted = scroll + selected;
        limit = scroll + visible;
        for (row = scroll; (sint32)row < (sint32)limit; ++row)
        {
            kind = r_u32(entry);
            if (kind == 0)
            {
                list = r_u32(entry + 12);
                text = r_u32(entry + 8);
                number = r_u32(list + (row << 2));
            }
            else
            {
                text = r_u32(entry + 8);
                number = row;
            }
            FntPrint(row == highlighted ? ">> %s %d\n" : "   %s %d\n", guest_c_string(text), (sint32)number);
        }
        input = func_8003816c();
        if (input == 6)
        {
            w_u32(0x800B4ADC + cell, selected);
            w_u32(0x800B4B5C + cell, scroll);
            w_u32(0x800B4BDC + cell, count);
            callback = r_u32(entry + 16);
            if (callback == 0)
                return scroll + selected;
            dispatch_debug_menu_callback(callback, scroll + selected);
        }
        if (input == 5)
        {
            w_u32(0x800B4ADC + cell, selected);
            w_u32(0x800B4B5C + cell, scroll);
            w_u32(0x800B4BDC + cell, count);
            return 0xFFFFFFFF;
        }
        if (input == 1)
        {
            --selected;
            if ((sint32)selected < 0)
            {
                selected = 0;
                if (scroll != 0)
                    --scroll;
            }
        }
        if (input == 2)
        {
            ++selected;
            last = visible - 1;
            if ((sint32)last < (sint32)selected)
            {
                selected = last;
                if (scroll != count - visible)
                    ++scroll;
            }
        }
        if (input == 3)
        {
            before = (sint32)scroll < (sint32)visible;
            scroll -= visible;
            if (before != 0)
                scroll = 0;
        }
        if (input == 4)
        {
            before = (sint32)(count - (visible << 1) + 1) < (sint32)scroll;
            scroll += visible;
            if (before != 0)
                scroll = count - visible;
        }
        if (input == 9)
        {
            scroll = 0;
            selected = 0;
        }
        if (input == 10)
        {
            scroll = count - visible;
            selected = visible - 1;
        }
        FntFlush(-1);
        DrawSync(0);
        VSync(0);
        GsSwapDispBuff();
    }
}

sint32 read_whole_resource(const char *filename, uint32 destination, uint8 *native_destination)
{
    CdlFILE file;
    uint32 count, packed, callback;
    uint8 *output;
    while (find_extracted_resource(&file, filename) == 0)
    {
    }
    count = (file.size + 2047) / 2048;
    if (count > UINT32_MAX / 2048)
        abort();
    memcpy(&packed, &file.pos, 4);
    output = native_destination != NULL ? native_destination : (uint8 *)psx_addr(destination, count * 2048);
    if (!read_resource_blocks(packed, output, count))
    {
#ifndef NDEBUG
        fprintf(stderr, "OBL: Cannot read extracted resource %s\n", filename);
#endif
        abort();
    }
    callback = r_u32(0x800CFCA0);
    if (callback != 0)
        dispatch_resource_callback(callback, 1);
    return (sint32)file.size;
}

sint32 func_8003944c(const char *filename, uint32 destination)
{
    FUNCTION_MARKER(0x8003944C, "SLUS_004.64");
    return read_whole_resource(filename, destination, NULL);
}

uint32 func_80039ccc(uint32 location, uint32 destination, uint32 count)
{
    uint32 callback;
    FUNCTION_MARKER(0x80039CCC, "SLUS_004.64");
    if (count > UINT32_MAX / 2048 || !read_resource_blocks(location, psx_addr(destination, count * 2048), count))
    {
#ifndef NDEBUG
        fprintf(stderr, "OBL: Cannot read extracted resource blocks at %08X\n", location);
#endif
        abort();
    }
    callback = r_u32(0x800CFCA0);
    if (callback != 0)
        dispatch_resource_callback(callback, 1);
    return 1;
}

uint32 func_80039a00(const char *filename, uint32 location)
{
    FUNCTION_MARKER(0x80039A00, "SLUS_004.64");
    while (find_extracted_resource((CdlFILE *)psx_addr(location, 24), filename) == 0)
    {
    }
    return location;
}

uint32 func_80039a44(uint32 location, uint32 destination, uint32 start_block, uint32 first_byte, uint32 last_byte, uint32 *callback_argument)
{
    uint32 length;
    FUNCTION_MARKER(0x80039A44, "SLUS_004.64");
    func_80039ccc(location, destination, 1);
    length = last_byte - first_byte + 1;
    *callback_argument = func_80041820(destination, destination + first_byte, length);
    return length;
}

uint32 func_80039b14(uint32 location, uint32 destination, uint32 start_block, uint32 first_byte, uint32 last_byte, uint32 *callback_argument)
{
    uint32 length;
    FUNCTION_MARKER(0x80039B14, "SLUS_004.64");
    func_80039ccc(location, destination, 2);
    length = last_byte + 2048 - first_byte;
    *callback_argument = func_80041820(destination, destination + first_byte, length);
    return length;
}

static uint32 resource_slice_core(uint32 packed_location, uint32 destination, uint32 first, uint32 last, uint32 offset, uint32 final_bytes)
{
    CdlLOC position;
    uint32 block, difference, bytes, callback, argument, running;
    memcpy(&position, &packed_location, 4);
    block = (uint32)CdPosToInt(&position);
    CdIntToPos((sint32)(block + first), &position);
    memcpy(&packed_location, &position, 4);
    difference = last - first;
    if (difference == 0)
        bytes = func_80039a44(packed_location, destination, first, offset, final_bytes, &argument);
    else if (difference + 1 == 2)
        bytes = func_80039b14(packed_location, destination, first, offset, final_bytes, &argument);
    else
        bytes = read_slice_blocks(packed_location, destination, first, last, offset, final_bytes, &argument);
    callback = r_u32(0x800CFCA0);
    if (callback != 0)
    {
        do
        {
            callback = r_u32(0x800CFCA0);
            running = poll_resource_callback(callback, &argument);
        }
        while (running != 0);
    }
    return bytes;
}

uint32 func_8003954c(const char *filename, uint32 destination, uint32 offset, uint32 length)
{
    CdlFILE file;
    uint32 end, first, last, remainder, final_bytes, packed;
    FUNCTION_MARKER(0x8003954C, "SLUS_004.64");
    first = (uint32)((sint32)offset / 2048);
    end = offset + length;
    last = (uint32)((sint32)end / 2048);
    remainder = offset - (first << 11);
    final_bytes = end - (last << 11);
    while (find_extracted_resource(&file, filename) == 0)
    {
    }
    memcpy(&packed, &file.pos, 4);
    return resource_slice_core(packed, destination, first, last, remainder, final_bytes);
}

uint32 func_800397b0(uint32 descriptor, uint32 destination, uint32 offset, uint32 length)
{
    uint32 end, first, last, remainder, final_bytes, high, low, shift, packed;
    FUNCTION_MARKER(0x800397B0, "SLUS_004.64");
    first = (uint32)((sint32)offset / 2048);
    end = offset + length;
    last = (uint32)((sint32)end / 2048);
    high = r_u32((descriptor + 3) & 0xFFFFFFFC);
    low = r_u32(descriptor & 0xFFFFFFFC);
    shift = (descriptor & 3) << 3;
    packed = shift != 0 ? (low >> shift) | (high << (32 - shift)) : low;
    remainder = offset - (first << 11);
    final_bytes = end - (last << 11);
    return resource_slice_core(packed, destination, first, last, remainder, final_bytes);
}

static uint32 load_resource_slice_path(const char *path, uint32 destination, uint32 offset, uint32 length, uint32 source_mode, uint32 file_location, sint32 explicit_location)
{
    char formatted[256];
    uint8 filename[256];
    uint32 format;
    sint32 name_length;
    FUNCTION_MARKER(0x8003621C, "SLUS_004.64");
    func_8001eff8();
    format = r_u32(0x800B4AD0 + (source_mode << 2));
    sprintf(formatted, guest_c_string(format), path);
    name_length = (sint32)strlen(formatted);
    func_800222d0(filename, (const uint8 *)formatted, name_length);
    if (source_mode == 1)
        return func_8003954c((const char *)filename, destination, offset, length);
    if ((sint32)source_mode < 2)
    {
        if (source_mode == 0)
            return func_80036384((const char *)filename, destination, offset, length);
        return 1;
    }
    if (source_mode == 2)
    {
        if (explicit_location)
            return func_800397b0(file_location, destination, offset, length);
        return func_8003954c((const char *)filename, destination, offset, length);
    }
    return 2;
}

uint32 func_8003621c(uint32 path, uint32 destination, uint32 offset, uint32 length, uint32 source_mode, uint32 file_location)
{
    return load_resource_slice_path(guest_c_string(path), destination, offset, length, source_mode, file_location, 1);
}

uint32 load_resource_slice_native(const char *path, uint32 destination, uint32 offset, uint32 length, uint32 source_mode, uint32 file_location)
{
    return load_resource_slice_path(path, destination, offset, length, source_mode, file_location, 1);
}

uint32 load_named_resource_slice(const char *path, uint32 destination, uint32 offset, uint32 length, uint32 source_mode)
{
    return load_resource_slice_path(path, destination, offset, length, source_mode, 0, 0);
}

sint32 func_8003db7c(uint32 mode, uint32 state, uint32 backup, uint32 work, uint32 menu)
{
    uint8 entries[2][384];
    uint8 *entry_ptrs[2];
    uint32 counts[2], matches[2], cards[2], slots[2][4];
    uint32 *slot_ptrs[2];
    uint32 device, selected, input, available, iteration, match_result;
    sint32 probe, result, read_result;
    FUNCTION_MARKER(0x8003DB7C, "SLUS_004.64");
    w_u32(0x800CFD30, work);
    entry_ptrs[0] = entries[0];
    entry_ptrs[1] = entries[1];
    slot_ptrs[0] = slots[0];
    slot_ptrs[1] = slots[1];
    w_u32(0x800CFD34, menu);
    result = 0;
    func_8003d52c();
    func_8003f610();
    func_8003d3a0();
    func_8003f288(mode != 0 ? 0x80011620 : 0x80011610, backup);
    func_80040eb4();
    cards[0] = (uint32)func_8003e18c(0, backup);
    if (cards[0] == 0)
        cards[1] = (uint32)func_8003e18c(1, backup);
    else
        cards[1] = 0;
    cards[1] = 0;
    if (cards[0] == 0xFFFFFFFE)
    {
        func_8003e6ec(4, backup);
        result = -2;
    }
    else if (cards[0] == 0)
    {
        func_8003e6ec(0, backup);
        result = -2;
    }
    else if (cards[0] == 0xFFFFFFFF)
        result = -2;
    if (result != -2)
    {
        for (probe = 1; probe >= 0; --probe)
        {
            if (cards[probe] == 1)
                matches[probe] = func_8003e8e0((uint32)probe, entry_ptrs, counts, slot_ptrs[probe], (uint32 *)psx_addr(backup, 5632));
        }
        if (result != -2)
        {
            available = 0;
            if (mode == 0)
            {
                if (cards[0] == 1)
                    available = func_8003e1e4(0, slot_ptrs[0], cards) != 0;
                else if (cards[1] == 1)
                    available = func_8003e1e4(1, slot_ptrs[1], cards) != 0;
                if (available == 0)
                {
                    func_8003e6ec(3, backup);
                    result = -2;
                }
            }
            else if (mode == 1)
            {
                if (cards[0] == 1)
                    available = matches[0] != 0;
                else if (cards[1] == 1)
                    available = matches[1] != 0;
                if (available == 0)
                {
                    func_8003e6ec(2, backup);
                    result = -2;
                }
            }
        }
    }
    w_u32(0x800CFD40, cards[0] == 0 ? 1 : 0);
    func_8003d3a0();
    while (result == 0)
    {
        device = r_u32(0x800CFD40);
        selected = r_u32(0x800CFC38);
        func_8003e4f0(0, selected, slot_ptrs[device]);
        func_8003d450();
        input = func_8003d034();
        if (input == 1)
        {
            func_8002372c(4);
            selected = r_u32(0x800CFC38) - 1;
            w_u32(0x800CFC38, selected);
            if ((sint32)selected < 0)
                w_u32(0x800CFC38, 3);
            continue;
        }
        if (input == 2)
        {
            func_8002372c(4);
            selected = r_u32(0x800CFC38) + 1;
            w_u32(0x800CFC38, selected);
            if ((sint32)selected >= 4)
                w_u32(0x800CFC38, 0);
            continue;
        }
        if (input == 5)
        {
            func_8002372c(2);
            result = -1;
            continue;
        }
        if (input != 6)
            continue;
        func_8002372c(1);
        if (mode == 0)
        {
            device = r_u32(0x800CFD40);
            selected = r_u32(0x800CFC38);
            if (slots[device][selected] != 0xFFFFFFFF && func_8003fdc8(backup, selected, slot_ptrs[device], 0) != 0)
                continue;
        }
        for (iteration = 0; iteration < 2; ++iteration)
        {
            device = r_u32(0x800CFD40);
            selected = r_u32(0x800CFC38);
            func_8003e4f0(mode == 0 ? 1 : 2, selected, slot_ptrs[device]);
            func_8003d450();
        }
        if (result == -2)
            continue;
        device = r_u32(0x800CFD40);
        selected = r_u32(0x800CFC38);
        if (mode == 0)
        {
            if (slots[device][selected] == 0xFFFFFFFE)
            {
                func_8002372c(2);
                continue;
            }
            if (func_8003e43c((uint32 *)psx_addr(state, 5632), slot_ptrs[device], selected, (uint8 *)psx_addr(backup, 5632)) == 0)
            {
                func_8003e6ec(5, backup);
                result = -2;
                continue;
            }
            device = r_u32(0x800CFD40);
            match_result = func_8003e8e0(device, entry_ptrs, counts, slot_ptrs[device], (uint32 *)psx_addr(backup, 5632));
            device = r_u32(0x800CFD40);
            matches[device] = match_result;
            func_8003e1e4(device, slot_ptrs[device], cards);
            func_8002372c(11);
        }
        else
        {
            read_result = func_8003e390((uint32 *)psx_addr(state, 5632), slot_ptrs[device], selected, (uint32 *)psx_addr(backup, 5632));
            if (read_result == 1)
            {
                func_8002372c(11);
                result = 1;
            }
            else if (read_result == -1)
            {
                func_8003e6ec(6, backup);
                result = -2;
            }
        }
    }
    func_80040eec();
    if (result == -2)
        return -1;
    device = r_u32(0x800CFD40);
    selected = r_u32(0x800CFC38);
    func_8003e4f0(0, selected, slot_ptrs[device]);
    for (iteration = 1; iteration <= 33; ++iteration)
    {
        func_8003d450();
        func_8003d3e0(iteration);
        device = r_u32(0x800CFD40);
        selected = r_u32(0x800CFC38);
        func_8003e4f0(0, selected, slot_ptrs[device]);
    }
    return result;
}

sint32 func_8003ce84(uint32 tim, uint32 position, uint32 dimensions)
{
    PSX_RECT rectangle;
    uint32 info[7];
    sint32 result;
    FUNCTION_MARKER(0x8003CE84, "SLUS_004.64");
    rectangle.x = (sint16)position;
    rectangle.y = (sint16)(position >> 16);
    rectangle.w = (sint16)dimensions;
    rectangle.h = (sint16)(dimensions >> 16);
    VSync(2);
    DrawSync(0);
    ResetGraph(1);
    func_8004c7d4(tim + 4, info);
    func_800443d4(&rectangle, info[3]);
    do
    {
        result = DrawSync(1);
    }
    while (result != 0);
    return result;
}

sint32 func_80039dc4(uint32 resource, uint32 value0, uint32 value1, uint32 buffer)
{
    char filename[32];
    uint32 types[16], offsets[16], sizes[16];
    uint32 index, object;
    FUNCTION_MARKER(0x80039DC4, "SLUS_004.64");
    SetGraphDebug(0);
    object = 0x800D7958;
    for (index = 0; index < 144; index += 9)
    {
        func_8003aa84(object);
        object += 36;
    }
    func_8003cbb0((sint32)resource, filename);
    load_resource_header(filename, buffer);
    if (resource == 57)
    {
        read_resource_directory(2, types, offsets, sizes, buffer);
        func_8003a3d0(filename, buffer, offsets[0], sizes[0], types[0]);
        load_resource_rectangle(filename, buffer, offsets[1], sizes[1], types[1], 640, 0x00D000EB);
        w_u32(0x800CFCB0, 2);
        w_u32(0x800CFCE0, 0);
        w_u32(0x800CFCE8, 0);
        w_u32(0x800EE818, 0);
        w_u32(0x800EE81C, 0);
        w_u32(0x800EE834, 0);
        w_u32(0x800CFC1C, 0);
        w_u32(0x800CFC20, 0);
        func_8003c498();
        goto finish;
    }
    if ((sint32)resource < 58)
    {
        if ((sint32)resource < 22)
            goto load_default;
        if ((sint32)resource < 24)
        {
            read_resource_directory(4, types, offsets, sizes, buffer);
            func_8003a3d0(filename, buffer, offsets[0], sizes[0], types[0]);
            load_resource_rectangle(filename, buffer, offsets[1], sizes[1], types[1], 640, 0x00100050);
            load_resource_rectangle(filename, buffer, offsets[2], sizes[2], types[2], 768, 0x00B8005C);
            load_resource_rectangle(filename, buffer, offsets[3], sizes[3], types[3], 896, 0x00B8005C);
            w_u32(0x800CFCB0, 0);
            w_u32(0x800CFCE0, 0);
            w_u32(0x800CFCE8, 0);
            w_u32(0x800CFC1C, 0);
            w_u32(0x800CFC20, 0);
            w_u32(0x800CFCD0, 0);
            goto finish;
        }
        if (resource != 32)
            goto load_default;
        read_resource_directory(3, types, offsets, sizes, buffer);
        func_8003a3d0(filename, buffer, offsets[0], sizes[0], types[0]);
        load_resource_rectangle(filename, buffer, offsets[1], sizes[1], types[1], 640, 0x00CF005D);
        load_resource_rectangle(filename, buffer, offsets[2], sizes[2], types[2], 768, 0x00B8005C);
        w_u32(0x800CFCB0, 2);
        w_u32(0x800CFCE0, 0);
        w_u32(0x800CFCE8, 0);
        w_u32(0x800EE81C, 0);
        w_u32(0x800CFC1C, 0);
        w_u32(0x800CFC20, 0);
        func_8003bcd0();
        goto finish;
    }
    if ((sint32)resource < 777)
        goto load_default;
    if ((sint32)resource < 779)
    {
        read_resource_directory(2, types, offsets, sizes, buffer);
        func_8003a3d0(filename, buffer, offsets[0], sizes[0], types[0]);
        load_resource_rectangle(filename, buffer, offsets[1], sizes[1], types[1], 640, 0x00F00140);
        if (resource == 777)
            func_8003c7e8();
        else
            func_8003c9c4();
        goto finish;
    }
    if (resource != 779)
        goto load_default;
    read_resource_directory(2, types, offsets, sizes, buffer);
    func_8003a3d0(filename, buffer, offsets[0], sizes[0], types[0]);
    load_resource_rectangle(filename, buffer, offsets[1], sizes[1], types[1], 640, 0x00F000E4);
    goto finish;
load_default:
    read_resource_directory(1, types, offsets, sizes, buffer);
    func_8003a3d0(filename, buffer, offsets[0], sizes[0], types[0]);
finish:
    func_8003ceec();
    w_u32(0x800CFCA8, resource);
    w_u32(0x800CFC18, 2);
    w_u32(0x800CFCB8, value0);
    w_u32(0x800CFCC0, value1);
    w_u32(0x800CFCC8, 32);
    return 32;
}

void func_800389fc(void)
{
    FUNCTION_MARKER(0x800389FC, "SLUS_004.64");
    if (r_u32(0x800CFC78) == 0)
        func_80038b2c();
    else
        func_80038a38();
}

void func_800388b4(void)
{
    uint8 result[8];
    sint32 position;
    FUNCTION_MARKER(0x800388B4, "SLUS_004.64");
    w_u32(0x800CF95C, 3);
    SsSetSerialAttr(0, 0, 0);
    SsSetSerialVol(0, 0, 0);
    while (CdControlB(9, 0, 0) == 0)
    {
    }
    while (CdControlB(0x11, 0, result) == 0)
    {
    }
    position = func_80069b68(result + 5);
    w_u32(0x800CFFBC, (uint32)position);
}

void func_80038938(void)
{
    CdlLOC position;
    uint8 result[8];
    uint32 left, right, sector;
    FUNCTION_MARKER(0x80038938, "SLUS_004.64");
    if (r_u32(0x800CF95C) != 3)
        return;
    left = r_u32(0x800CFC88);
    right = r_u32(0x800CFC90);
    w_u32(0x800CF95C, 1);
    func_800393f0(left, right);
    sector = r_u32(0x800CFC80);
    w_u32(0x800CFC70, 1);
    if (sector != 0)
        w_u32(0x800CFC80, 0);
    sector = r_u32(0x800CFFBC);
    CdIntToPos((sint32)sector, &position);
    while (CdControlB(2, (uint8 *)&position, result) == 0)
    {
    }
    while (CdControl(0x1B, (uint8 *)&position, result) == 0)
    {
    }
}

uint32 func_80038d6c(uint32 command)
{
    CdlLOC position;
    uint32 sector;
    FUNCTION_MARKER(0x80038D6C, "SLUS_004.64");
    sector = r_u32(0x800CFEAC);
    w_u32(0x800CFC70, 1);
    CdIntToPos((sint32)sector, &position);
    CdControlF((uint8)command, (uint8 *)&position);
    sector = r_u32(0x800CFEAC);
    w_u32(0x800CFFBC, sector);
    return 1;
}

void func_80038a38(void)
{
    uint8 result[8];
    sint32 status, current, stop, start;
    FUNCTION_MARKER(0x80038A38, "SLUS_004.64");
    status = CdSync(1, result);
    if (status == 2)
    {
        CdControlF(0x11, result);
        current = func_80069b68(result + 5);
        stop = r_s32(0x800CFDC4);
        w_u32(0x800CFFBC, (uint32)current);
        if (stop < current)
            goto outside;
        start = r_s32(0x800CFEAC);
        if (current < start)
            goto outside;
        if (r_u32(0x800CFC70) != 0 && current != start)
            w_u32(0x800CFC70, 0);
        return;
outside:
        if (r_u32(0x800CFC70) == 0)
        {
            func_80038d6c(0x1B);
            w_u32(0x800CFC70, 1);
        }
    }
    else if (status == 5)
        func_80038d6c(0x1B);
}

void func_80038b2c(void)
{
    uint8 result[8];
    sint32 status, current;
    uint32 stop, start, difference, midpoint;
    FUNCTION_MARKER(0x80038B2C, "SLUS_004.64");
    status = CdSync(1, result);
    if (status == 2)
    {
        CdControlF(0x11, result);
        current = func_80069b68(result + 5);
        stop = r_u32(0x800CFDC4);
        w_u32(0x800CFFBC, (uint32)current);
        if ((sint32)stop < current)
            goto outside;
        start = r_u32(0x800CFEAC);
        if (current < (sint32)start)
            goto outside;
        difference = stop - start;
        midpoint = start + (uint32)((sint32)(difference + (difference >> 31)) >> 1);
        if ((sint32)midpoint < current)
            w_u32(0x800CFC80, 1);
        return;
outside:
        if (r_u32(0x800CFC80) != 0)
            func_80038854();
    }
    else if (status == 5)
        func_80038d6c(0x1B);
}

void func_80038c14(void)
{
    uint8 result[8];
    uint16 volume[2];
    sint32 status, current, stop, start;
    FUNCTION_MARKER(0x80038C14, "SLUS_004.64");
    status = CdSync(1, result);
    if (status == 2)
    {
        CdControlF(0x11, result);
        current = func_80069b68(result + 5);
        stop = r_s32(0x800CFDC4);
        w_u32(0x800CFFBC, (uint32)current);
        if (stop < current)
            goto outside;
        start = r_s32(0x800CFEAC);
        if (current < start)
            goto outside;
        if (r_u32(0x800CFC70) != 0 && current != start)
            w_u32(0x800CFC70, 0);
        goto fade;
outside:
        if (r_u32(0x800CFC70) == 0)
        {
            func_80038d6c(0x1B);
            w_u32(0x800CFC70, 1);
        }
    }
    else if (status == 5)
        func_80038854();
fade:
    func_80075480(0, volume);
    volume[0] = (uint16)(volume[0] - 1);
    volume[1] = (uint16)(volume[1] - 1);
    SsSetSerialVol(0, (sint16)volume[0], (sint16)volume[1]);
    if (volume[0] == 0 && volume[1] == 0)
        func_80038854();
}

uint32 func_80038854(void)
{
    FUNCTION_MARKER(0x80038854, "SLUS_004.64");
    w_u32(0x800CF95C, 0);
    SsSetSerialAttr(0, 0, 0);
    SsSetSerialVol(0, 0, 0);
    while (CdControlB(9, 0, 0) == 0)
    {
    }
    CdFlush();
    /* Preserve the original SDK return carrier */
    return 0x1325;
}

uint32 func_800385f8(uint32 word0, uint32 word1, uint32 word2, uint32 word3, uint32 word4, uint32 word5, uint32 enabled, uint32 channel, uint32 duration, uint32 loop, uint32 left, uint32 right, uint32 callback)
{
#ifdef AP_WEB
    /* Only looping background STR tracks are packaged for Web */
    if (loop == 0)
    {
        w_u32(0x800CF95C, 0);
        w_u32(0x800CF8B4, 0);
        return 0;
    }
#endif
    CdlLOC location;
    uint8 packed[3], result[8], mode[8], filter[2];
    uint32 start;
    sint32 pending, status;
    FUNCTION_MARKER(0x800385F8, "SLUS_004.64");
    w_u32(0x800CFC88, left);
    w_u32(0x800CFC90, right);
    pending = 0;
    SsSetSerialAttr(0, 0, 0);
    SsSetSerialVol(0, 0, 0);
    packed[0] = (uint8)word0;
    packed[1] = (uint8)(word0 >> 8);
    packed[2] = (uint8)(word0 >> 16);
    start = (uint32)func_80069b68(packed);
    w_u32(0x800CFEAC, start);
    CdIntToPos((sint32)start, &location);
    while (CdControl(0x15, (uint8 *)&location, result) == 0)
    {
        if (callback != 0)
            dispatch_resource_callback(callback, 0x15);
    }
    while (pending == 0)
    {
        if (callback != 0)
            dispatch_resource_callback(callback, 1);
        status = CdSync(1, 0);
        if (status == 5)
            pending = -1;
        else if (status == 2)
            pending = 1;
    }
    mode[0] = 0xC8;
    while (CdControl(0xE, mode, result) == 0)
    {
        if (callback != 0)
            dispatch_resource_callback(callback, 0xE);
    }
    filter[0] = (uint8)enabled;
    filter[1] = (uint8)channel;
    while (CdControl(0xD, filter, result) == 0)
    {
        if (callback != 0)
            dispatch_resource_callback(callback, 0xD);
    }
    left = r_u32(0x800CFC88);
    right = r_u32(0x800CFC90);
    w_u32(0x800CF95C, 1);
    w_u32(0x800CFC78, loop);
    w_u32(0x800CFC80, 0);
    func_800393f0(left, right);
    start = r_u32(0x800CFEAC);
    w_u32(0x800CFC70, 0);
    w_u32(0x800CFDC4, duration + start);
    w_u32(0x800CFFBC, start);
    CdIntToPos((sint32)start, &location);
    while (CdControl(0x1B, (uint8 *)&location, result) == 0)
    {
        if (callback != 0)
            dispatch_resource_callback(callback, 0x1B);
    }
    start = r_u32(0x800CFEAC);
    w_u32(0x800CFFBC, start);
    return start;
}

void func_80013394(void)
{
    MATRIX light, screen, other_light, other_screen;
    uint32 buffer, group, index, object, coordinate, vector, value, flags;
    uint32 count, offset, parent, mode, pitch, yaw, roll, result, table;
    FUNCTION_MARKER(0x80013394, "SLUS_004.64");
    func_8004cf4c(0x800EF5EC);
    buffer = GsGetActiveBuff();
    w_u32(0x800CFDEC, buffer);
    func_8004e594(0x80082164 + buffer * 86400);
    buffer = r_u32(0x800CFDEC);
    GsClearOt(0, 0, psx_addr(0x800EBD14 + buffer * 20, 20));
    buffer = r_u32(0x800CFDEC);
    GsClearOt(0, 0, psx_addr(0x800EC708 + buffer * 20, 20));
    if (r_u32(0x800CF918) != 0 || r_u32(0x800CF8E4) != 0)
    {
        buffer = r_u32(0x800CFDEC);
        GsClearOt(0, 0, psx_addr(0x800EC750 + buffer * 20, 20));
    }
    buffer = r_u32(0x800CFDEC);
    GsClearOt(0, 0, psx_addr(0x800EC778 + buffer * 20, 20));
    if (r_u32(0x800CFC18) != 0)
    {
        func_8003a688();
        w_u32(0x800CF8D8, 1);
        goto overlays;
    }
    if (r_u32(0x800CF8D8) == 1)
    {
        func_80017a74();
        func_80018190();
        w_u32(0x800CF8D8, 2);
    }
    if (r_u32(0x800EDFD0) != 0)
        func_8001ad80();
    for (group = 1; group < 5; ++group)
    {
        value = r_u32(0x80081978 + (group << 2));
        if (value == 0)
            continue;
        index = value - 1;
        count = r_u32(0x80082108 + group * 12);
        if ((sint32)index >= (sint32)count)
            continue;
        do
        {
            object = 0x800EA704 + group * 560 + (index << 4);
            value = r_u32(object + 12);
            ++index;
            if (value != 0xFFFFFFFF && r_u32(object + 8) != 0)
            {
                flags = r_u32(object);
                if ((sint32)flags >= 0)
                {
                    w_u32(object, flags & 0xFFFFF1FF);
                    coordinate = r_u32(object + 4);
                    func_8004e5c8(coordinate, &light, &screen);
                    GsSetLightMatrix(&light);
                    coordinate = r_u32(object + 4);
                    func_8004c8b8(coordinate, &screen);
                    SetRotMatrix(&screen);
                    SetTransMatrix(&screen);
                    buffer = r_u32(0x800CFDEC);
                    func_8004b4f0(object, 0x800EBD14 + buffer * 20, 4, 0x1F800000);
                }
            }
            count = r_u32(0x80082108 + group * 12);
        }
        while ((sint32)index < (sint32)count);
    }
    if (r_u32(0x800EDFD0) != 0)
        func_8001afcc();
    if (r_u32(0x800EDFDC) != 0)
    {
        group = r_u32(0x800EE7EC);
        if (r_u32(0x80081978 + (group << 2)) != 0 && (r_u32(0x800EDFD8) != 2 || r_u32(0x800CFE24) != 0))
        {
            index = r_u32(0x800EDFDC);
            object = 0x800EB414 + (index << 4);
            group = r_u32(0x800EE7EC);
            coordinate = r_u32(object + 4);
            value = r_u32(0x800EA728 + group * 560);
            w_u32(coordinate + 72, value);
            coordinate = r_u32(object + 4);
            w_u32(coordinate + 24, 0);
            coordinate = r_u32(object + 4);
            w_u32(coordinate + 28, 0);
            coordinate = r_u32(object + 4);
            w_u32(coordinate + 32, 0);
            if (r_u32(object + 12) != 0xFFFFFFFF && r_u32(object + 8) != 0)
            {
                coordinate = r_u32(object + 4);
                func_8004e5c8(coordinate, &light, &screen);
                GsSetLightMatrix(&light);
                coordinate = r_u32(object + 4);
                func_8004c8b8(coordinate, &screen);
                SetRotMatrix(&screen);
                SetTransMatrix(&screen);
                buffer = r_u32(0x800CFDEC);
                func_8004b4f0(object, 0x800EBD14 + buffer * 20, 4, 0x1F800000);
            }
        }
    }
    if (r_s32(0x800EE800) > 0 && r_s32(0x800EE7FC) > 0)
        func_8001446c();
    if (r_s32(0x800EE858) > 0 && r_s32(0x800EE868) > 0)
        func_80014520();
    for (group = 1; group < 5; ++group)
    {
        value = r_u32(0x800EE088 + (group << 2));
        if (value == 0 || r_u32(0x80081978 + (group << 2)) == 0)
            continue;
        object = 0x800EA2D4 + (value << 4);
        func_80015b2c(object, 0x800DDD44 + (group << 4), group);
        coordinate = r_u32(object + 4);
        vector = r_u32(coordinate + 68);
        value = r_u32(0x800819D8 + (group << 2));
        mode = r_u32(0x800EDFD0);
        value = (uint32)(((sint32)(0x2000 - value) >> 1) >> (mode & 31));
        w_u32(vector, value);
        coordinate = r_u32(object + 4);
        vector = r_u32(coordinate + 68);
        value = r_u32(0x800819D8 + (group << 2));
        mode = r_u32(0x800EDFD0);
        value = (uint32)(((sint32)(0x2000 - value) >> 1) >> (mode & 31));
        w_u32(vector + 8, value);
        func_8001b21c(object);
        if (r_u32(object + 12) != 0xFFFFFFFF && r_u32(object + 8) != 0)
        {
            coordinate = r_u32(object + 4);
            func_8004e5c8(coordinate, &light, &screen);
            GsSetLightMatrix(&light);
            coordinate = r_u32(object + 4);
            func_8004c8b8(coordinate, &screen);
            SetRotMatrix(&screen);
            SetTransMatrix(&screen);
            buffer = r_u32(0x800CFDEC);
            func_8004b4f0(object, 0x800EC778 + buffer * 20, 6, 0x1F800000);
        }
    }
    for (index = 0; index < 32; ++index)
    {
        offset = index * 52;
        value = r_u32(0x800EE0A8 + offset);
        if (value == 0xFFFFFFFF)
            break;
        if (value == 0)
            continue;
        value = r_u32(0x800EE0B0 + offset);
        object = 0x800EA2E4 + (value << 4);
        coordinate = r_u32(object + 4);
        vector = r_u32(coordinate + 68);
        value = r_u32(0x800EE0C4 + offset);
        w_u32(vector, value);
        coordinate = r_u32(object + 4);
        vector = r_u32(coordinate + 68);
        value = r_u32(0x800EE0C8 + offset);
        w_u32(vector + 4, value);
        coordinate = r_u32(object + 4);
        vector = r_u32(coordinate + 68);
        value = r_u32(0x800EE0CC + offset);
        w_u32(vector + 8, value);
        coordinate = r_u32(object + 4);
        value = r_u32(0x800EE0B8 + offset);
        w_u32(coordinate + 24, value);
        coordinate = r_u32(object + 4);
        value = r_u32(0x800EE0BC + offset);
        w_u32(coordinate + 28, value);
        coordinate = r_u32(object + 4);
        value = r_u32(0x800EE0C0 + offset);
        w_u32(coordinate + 32, value);
        parent = r_u32(0x800EE0B4 + offset);
        if (parent == 0)
        {
            coordinate = r_u32(object + 4);
            w_u32(coordinate + 72, 0);
        }
        else
        {
            parent = r_u32(0x800EE0B4 + offset);
            coordinate = r_u32(object + 4);
            value = r_u32(0x800DDD48 + (parent << 4));
            w_u32(coordinate + 72, value);
        }
        roll = r_u32(0x800EE0D8 + offset);
        flags = r_u32(0x800EE0AC + offset);
        pitch = r_u32(0x800EE0D0 + offset);
        yaw = r_u32(0x800EE0D4 + offset);
        func_800146c0(object, flags, pitch, yaw, roll);
        if (r_u32(object + 12) != 0xFFFFFFFF && r_u32(object + 8) != 0)
        {
            coordinate = r_u32(object + 4);
            func_8004e5c8(coordinate, &light, &screen);
            GsSetLightMatrix(&light);
            coordinate = r_u32(object + 4);
            func_8004c8b8(coordinate, &screen);
            SetRotMatrix(&screen);
            SetTransMatrix(&screen);
            buffer = r_u32(0x800CFDEC);
            func_8004b4f0(object, 0x800EBD14 + buffer * 20, 4, 0x1F800000);
        }
    }
    index = 8;
    object = 0x800DDDC4;
    count = r_u32(0x800CF9B8);
    while (index < count)
    {
        mode = r_u32(0x800CF908);
        value = r_u32(0x800EF754 + (index << 2));
        if ((((uint32)1 << (mode & 31)) & value) != 0 && r_u32(object + 12) != 0xFFFFFFFF && r_u32(object + 8) != 0)
        {
            flags = r_u32(object);
            if ((sint32)flags >= 0)
            {
                if (r_u32(0x800DF0C4 + (index << 2)) != 0 && r_u32(0x800CF874) != 0)
                    value = (flags & 0xFFFFF1FF) | 0x400;
                else
                    value = r_u32(object) & 0xFFFFF1FF;
                w_u32(object, value);
                coordinate = r_u32(object + 4);
                func_8004e5c8(coordinate, &other_light, &other_screen);
                GsSetLightMatrix(&other_light);
                coordinate = r_u32(object + 4);
                func_8004c8b8(coordinate, &other_screen);
                SetRotMatrix(&other_screen);
                SetTransMatrix(&other_screen);
                buffer = r_u32(0x800CFDEC);
                func_8004b4f0(object, 0x800EC708 + buffer * 20, 4, 0x1F800000);
            }
        }
        count = r_u32(0x800CF9B8);
        ++index;
        object += 16;
    }
    index = 8;
    object = 0x800DDDC4;
    count = r_u32(0x800CF9B8);
    while (index < count)
    {
        mode = r_u32(0x800CF908);
        value = r_u32(0x800EF754 + (index << 2));
        if ((((uint32)1 << (mode & 31)) & value) == 0 && r_u32(object + 12) != 0xFFFFFFFF && r_u32(object + 8) != 0)
        {
            flags = r_u32(object);
            if ((sint32)flags >= 0)
            {
                if (r_u32(0x800DF0C4 + (index << 2)) != 0 && r_u32(0x800CF874) != 0)
                    value = (flags & 0xFFFFF1FF) | 0x400;
                else
                    value = r_u32(object) & 0xFFFFF1FF;
                w_u32(object, value);
                coordinate = r_u32(object + 4);
                func_8004e5c8(coordinate, &other_light, &other_screen);
                GsSetLightMatrix(&other_light);
                coordinate = r_u32(object + 4);
                func_8004c8b8(coordinate, &other_screen);
                SetRotMatrix(&other_screen);
                SetTransMatrix(&other_screen);
                buffer = r_u32(0x800CFDEC);
                func_8004b4f0(object, 0x800EBD14 + buffer * 20, 4, 0x1F800000);
            }
        }
        count = r_u32(0x800CF9B8);
        ++index;
        object += 16;
    }
overlays:
    if (r_u32(0x800CF7B0) != 0 && r_u32(0x800CF7A4) == 0)
    {
        mode = r_u32(0x800CF918);
        w_u16(0x800EA0F0, 0);
        w_u16(0x800EA0F2, 0);
        table = mode == 0 ? 0x800EBD14 : 0x800EC750;
        buffer = r_u32(0x800CFDEC);
        GsSortSprite(psx_addr(0x800EA0EC, 36), psx_addr(table + buffer * 20, 20), 0);
    }
    mode = r_u32(0x800CF918);
    if (mode == 2)
        func_8002eae4();
    else if (mode == 1)
        func_8002ee8c();
    else if (mode == 3)
        func_8002f1c4();
    if (r_u32(0x800CF844) == 1)
        func_800142b4();
    if (r_u32(0x800CF8E4) != 0)
    {
        buffer = r_u32(0x800CFDEC);
        func_80028480(0x800EC750 + buffer * 20);
    }
    if (r_u32(0x800CFC18) != 0)
    {
        if (r_u32(0x800CF918) == 0)
        {
            func_8001fac8();
            buffer = r_u32(0x800CFDEC);
            func_800194b4(0x800EC708 + buffer * 20);
            if (r_u32(0x800CF918) != 0 || r_u32(0x800CF8E4) != 0)
                goto menu_overlay;
        }
        else
        {
menu_overlay:
            buffer = r_u32(0x800CFDEC);
            result = GsSortOtPSX(0x800EC750 + buffer * 20, 0x800EC708 + buffer * 20);
            w_u32(0x800CFD8C, result);
        }
        buffer = r_u32(0x800CFDEC);
        result = GsSortOtPSX(0x800EC778 + buffer * 20, 0x800EBD14 + buffer * 20);
        w_u32(0x800CFD8C, result);
        buffer = r_u32(0x800CFDEC);
        result = GsSortOtPSX(0x800EBD14 + buffer * 20, 0x800EC708 + buffer * 20);
    }
    else
    {
        if (r_u32(0x800CF918) == 0)
        {
            func_8001fac8();
            buffer = r_u32(0x800CFDEC);
            func_800194b4(0x800EC708 + buffer * 20);
            if (r_u32(0x800CF918) != 0 || r_u32(0x800CF8E4) != 0)
                goto game_overlay;
        }
        else
        {
game_overlay:
            buffer = r_u32(0x800CFDEC);
            result = GsSortOtPSX(0x800EC750 + buffer * 20, 0x800EC708 + buffer * 20);
            w_u32(0x800CFD8C, result);
        }
        buffer = r_u32(0x800CFDEC);
        result = GsSortOtPSX(0x800EBD14 + buffer * 20, 0x800EC708 + buffer * 20);
        w_u32(0x800CFD8C, result);
        buffer = r_u32(0x800CFDEC);
        result = GsSortOtPSX(0x800EC778 + buffer * 20, 0x800EC708 + buffer * 20);
    }
    w_u32(0x800CFD8C, result);
    DrawSync(0);
    if (r_u32(0x800CF864) != 0)
    {
        VSync(2);
        result = 1;
    }
    else
        result = (uint32)func_80012d48();
    w_u32(0x800CF86C, result);
    ResetGraph(1);
    GsSwapDispBuff();
    table = r_u32(0x800CFD8C);
    GsSortClear(0, 0, 0, psx_addr(table, 20));
    table = r_u32(0x800CFD8C);
    func_8004e5a4(table);
    if (r_u32(0x800CF7A4) != 0)
        func_8001992c();
}

void func_800242d4(uint32 mode, uint32 object)
{
    uint32 transform, action, shift, held, pad, value, limit, coordinate, vector;
    uint32 facing, blocked, next, queue_action, queue_value, timer;
    FUNCTION_MARKER(0x800242D4, "SLUS_004.64");
    w_u32(0x800CFE4C, 0);
    w_u32(0x800CFF24, 0);
    w_u32(0x800CFE54, 0);
    w_u32(0x800CFF1C, 0);
    w_u32(0x800CFF3C, 0);
    w_u32(0x800CFE64, 0);
    w_u32(0x800CFB1C, 0);
    transform = 0x800DDD44 + (object << 4);
    action = func_80031954(object);
    held = r_u32(0x800CF870);
    facing = 0;
    shift = (mode << 4) & 31;
    if (held != 0)
    {
        pad = r_u32(0x800CF934);
        if (((held << shift) & pad) != 0)
            w_u32(0x800CF934, ~held & pad);
        else
            w_u32(0x800CF870, 0);
    }
    pad = r_u32(0x800CF934);
    if ((((uint32)0x800 << shift) & pad) != 0 && (((uint32)0x20 << shift) & pad) != 0)
        func_800265ec(0);
    if ((((uint32)4 << shift) & r_u32(0x800CF934)) != 0)
    {
        func_8002372c(1);
        func_80014ef8(1);
        held = r_u32(0x800CF870);
        w_u32(0x800CF870, held | 4);
        return;
    }
    if (r_u32(0x800CFE24) == 0 && (((uint32)8 << shift) & r_u32(0x800CF934)) != 0)
    {
        func_80025374();
        return;
    }
    if ((((uint32)0x100 << shift) & r_u32(0x800CF934)) != 0)
    {
        func_8002540c();
        held = r_u32(0x800CF870);
        w_u32(0x800CF870, held | 0x100);
        return;
    }
    if (r_u32(0x800CF7A4) != 0)
        func_800252ec();
    if (r_u32(0x800CF914) == 0)
        goto final_guard;
    if ((((uint32)8 << shift) & r_u32(0x800CF934)) != 0 && r_u32(0x800CFE24) != 0)
    {
        w_u32(0x800CFB1C, 1);
        func_8002b32c();
    }
    if ((((uint32)0x40 << shift) & r_u32(0x800CF934)) != 0)
    {
        if (r_u32(0x800CFE24) != 0)
            func_8002b0e8();
        else
        {
            if (r_u32(0x800CFE0C) == 0)
            {
                value = func_8001d480(object, 0);
                w_u32(0x800CFE0C, value);
            }
            if (r_u32(0x800CFE1C) == 0)
            {
                value = func_8001d480(object, 0xFDE4);
                w_u32(0x800CFE1C, value);
            }
        }
    }
    if ((((uint32)2 << shift) & r_u32(0x800CF934)) != 0 && r_u32(0x800CFE24) != 0)
    {
        func_8002b004();
        held = r_u32(0x800CF870);
        w_u32(0x800CF870, held | 2);
    }
    if (r_u32(0x800CF858) != 0)
    {
        value = r_u32(0x800EE7EC);
        coordinate = r_u32(0x800DDD48 + (value << 4));
        vector = r_u32(coordinate + 68);
        value = r_u16(vector + 18);
        w_u16(vector + 18, (uint16)(value & 0xFFF));
        value = r_u32(0x800EE7EC);
        coordinate = r_u32(0x800DDD48 + (value << 4));
        vector = r_u32(coordinate + 68);
        value = (uint32)r_s16(vector + 18);
        facing = value - 0x401 < 0x7FF;
        if (facing != 0)
        {
            if (action - 0x31 < 2)
                func_80031f28(object, 0x2A, 0x2C);
            else if (action - 0x2B < 2)
                func_80031ea4(object, 0x2C);
        }
        else
        {
            if (action - 0x2B < 2)
                func_80031f28(object, 0x30, 0x32);
            else if (action - 0x31 < 2)
                func_80031ea4(object, 0x32);
        }
        action = func_80031954(object);
    }
    func_8003248c(object);
    if ((((uint32)0x10 << shift) & r_u32(0x800CF934)) != 0 && r_u32(0x800EDFCC) != 0 && r_u32(0x800CFE24) == 0)
    {
        w_u32(0x800819B8 + (object << 2), 60);
        switch (action)
        {
        case 0:
        case 2:
        case 3:
        case 0x24:
            func_80031f28(object, 0x1F, 0x20);
            goto accept_action;
        case 0x20:
        case 0x22:
            if (r_u32(0x800CF858) == 0)
                func_80031f28(object, 0x21, 0);
            else if (facing != 0)
                func_80031f28(object, 0x2F, 0x2B);
            else
                func_80031f28(object, 0x35, 0x31);
            goto accept_action;
        case 0x2B:
        case 0x2C:
            next = 0x2E;
            goto action_combo;
        case 0x31:
        case 0x32:
            next = 0x34;
            goto action_combo;
        default:
            w_u32(0x800CFF24, 1);
            break;
        }
    }
    goto camera;
action_combo:
    func_80031c20(object, next, 1, 0, 0, 0);
    func_80031b14(object, 0x20, 1, 0, 0, 0);
    func_80032320(object, 0x20);
accept_action:
    held = r_u32(0x800CF870);
    w_u32(0x800CF870, held | 0x10);
    return;
camera:
    pad = r_u32(0x800CF934);
    if ((((uint32)1 << shift) & pad) != 0)
    {
        if ((((uint32)0x4000 << shift) & pad) != 0)
        {
            if (r_u32(0x800EDFD8) == 2)
            {
                value = r_u32(0x800CF848);
                if ((sint32)value > -448)
                    w_u32(0x800CF848, value - 32);
            }
            if (r_u32(0x800EDFD8) == 1)
            {
                value = r_u32(0x800CF9D4);
                value += r_u32(0x800CF9D8);
                limit = r_u32(0x800EDFE4);
                w_u32(0x800CF9D4, value);
                if ((sint32)limit < (sint32)value)
                    w_u32(0x800CF9D4, limit);
                coordinate = r_u32(transform + 4);
                value = r_u32(0x800CF9D0);
                value += r_u32(coordinate + 28);
                value += r_u32(0x800CF9D4);
                w_u32(0x800EF5F0, value);
            }
            w_u32(0x800CFF1C, 1);
            pad = r_u32(0x800CF934);
        }
        if ((((uint32)1 << shift) & pad) != 0 && (((uint32)0x1000 << shift) & pad) != 0)
        {
            if (r_u32(0x800EDFD8) == 2)
            {
                value = r_u32(0x800CF848);
                if ((sint32)value < 384)
                    w_u32(0x800CF848, value + 32);
            }
            if (r_u32(0x800EDFD8) == 1)
            {
                value = r_u32(0x800CF9D4);
                value -= r_u32(0x800CF9D8);
                limit = r_u32(0x800EDFE8);
                w_u32(0x800CF9D4, value);
                if ((sint32)value < (sint32)limit)
                    w_u32(0x800CF9D4, limit);
                coordinate = r_u32(transform + 4);
                value = r_u32(0x800CF9D0);
                value += r_u32(coordinate + 28);
                value += r_u32(0x800CF9D4);
                w_u32(0x800EF5F0, value);
            }
            w_u32(0x800CFF1C, 1);
        }
    }
    if ((((uint32)0x8000 << shift) & r_u32(0x800CF934)) != 0)
    {
        func_80025758(object, action);
        coordinate = r_u32(transform + 4);
        vector = r_u32(coordinate + 68);
        value = r_u16(vector + 18);
        w_u16(vector + 18, (uint16)(value - 60));
        coordinate = r_u32(transform + 4);
        w_u32(coordinate, 0);
        func_8001b21c(transform);
        w_u32(0x800CFE54, 1);
    }
    if ((((uint32)0x2000 << shift) & r_u32(0x800CF934)) != 0)
    {
        func_80025758(object, action);
        coordinate = r_u32(transform + 4);
        vector = r_u32(coordinate + 68);
        value = r_u16(vector + 18);
        w_u16(vector + 18, (uint16)(value + 60));
        coordinate = r_u32(transform + 4);
        w_u32(coordinate, 0);
        func_8001b21c(transform);
        w_u32(0x800CFE54, 1);
    }
    blocked = func_8003248c(object);
    if (r_u32(0x800CFF1C) == 0 && r_u32(0x800CFB1C) == 0)
    {
        pad = r_u32(0x800CF934);
        if ((((uint32)0x20 << shift) & pad) != 0)
        {
            if ((((uint32)0x1000 << shift) & pad) != 0)
            {
                if (r_u32(0x800CF858) == 0)
                    func_80026110(object, action);
                else
                    func_8002635c(object, action, blocked);
                w_u32(0x800CFE4C, 1);
                w_u32(0x800CFF3C, 1);
            }
        }
        else if ((((uint32)0x1000 << shift) & r_u32(0x800CF934)) != 0)
        {
            if (r_u32(0x800CF858) == 0)
            {
                if (r_u32(0x800CFE24) == 0)
                    func_80025dc8(object, action);
                else
                    func_80026110(object, action);
            }
            else
                func_800264ec(object, action, blocked);
            w_u32(0x800CFF3C, 1);
            w_u32(0x800CFE4C, 1);
        }
    }
    pad = r_u32(0x800CF934);
    if ((((uint32)0x80 << shift) & pad) != 0)
    {
        if ((((uint32)0x1000 << shift) & pad) != 0)
            func_80025ac4(object, action);
        else
        {
            pad = r_u32(0x800CF934);
            if ((((uint32)0x80 << shift) & pad) != 0 && (((uint32)0x1000 << shift) & pad) == 0)
                func_80025940(object, action, blocked, transform);
        }
    }
    if (r_u32(0x800CFF1C) == 0 && (((uint32)0x4000 << shift) & r_u32(0x800CF934)) != 0)
    {
        if (action == 0 || action - 4 < 2)
        {
            func_80031c20(object, 0x15, 1, 0, 0, 0xFFFFFFA6);
            func_80032320(object, 0x15);
            w_u32(0x800CFE4C, 1);
        }
        if (action - 2 < 2)
        {
            func_80031c20(object, 0x15, 1, 0, 0, 0xFFFFFFA6);
            func_80032320(object, 0x15);
            w_u32(0x800CFE4C, 1);
        }
        if (r_u32(0x800CFE24) == 0)
        {
            if (action == 0x24)
            {
                func_80031c20(object, 0x15, 1, 0, 0, 0xFFFFFFA6);
                func_80032320(object, 0x15);
                w_u32(0x800CFE4C, 1);
            }
            if (action == 0x20)
            {
                func_80031c20(object, 0x22, 1, 0, 0, 0xFFFFFFD8);
                func_80032320(object, 0x22);
                w_u32(0x800CFE4C, 1);
            }
            if (action == 0x22)
            {
                func_80031c20(object, 0x22, 1, 0, 0, 0xFFFFFFD8);
                func_80032320(object, 0x22);
                w_u32(0x800CFE4C, 1);
            }
        }
        else if (action == 0x25 && r_u32(0x800CFB1C) == 0)
            func_80031f28(object, 0x27, 0);
        w_u32(0x800CFF3C, 1);
    }
    if (r_u32(0x800CFE64) != 0 || r_u32(0x800CFE4C) != 0 || r_u32(0x800CFF1C) != 0 || r_u32(0x800CFE54) != 0 || r_u32(0x800CFB1C) != 0)
        goto final_guard;
    if (r_u32(0x800CF858) != 0)
    {
        func_8002645c(object, action, blocked);
        goto final_guard;
    }
    switch (action)
    {
    case 1:
        func_80031b14(object, 2, 1, 0, 0, 90);
        queue_action = 4;
        queue_value = 0;
        goto queue_idle;
    case 2:
        func_80031ee0(object, 4, 0);
        break;
    case 3:
        func_80031ee0(object, 5, 0);
        break;
    case 6:
        func_80031b14(object, 10, 1, 0, 0, 90);
        queue_action = 4;
        queue_value = 22;
        goto queue_idle;
    case 7:
        func_80031b14(object, 11, 1, 0, 0, 90);
        queue_action = 5;
        queue_value = 22;
        goto queue_idle;
    case 8:
        func_80031b14(object, 10, 1, 0, 0, 90);
        queue_action = 5;
        queue_value = 45;
        goto queue_idle;
    case 9:
        func_80031b14(object, 11, 1, 0, 0, 90);
        queue_action = 4;
        queue_value = 45;
        goto queue_idle;
    case 17:
        func_80031ee0(object, 19, 0);
        break;
    case 18:
        func_80031ee0(object, 20, 0);
        break;
    case 21:
        func_80031e68(object, 0);
        break;
    case 34:
        if (r_u32(0x800CFE24) != 0)
            return;
        func_80031ea4(object, 32);
        break;
    case 37:
        if (r_u32(0x800CFE24) == 0)
            goto idle_timer;
        func_80031f28(object, 39, 0);
        break;
    default:
        break;
    }
    goto final_guard;
queue_idle:
    func_800319c0(object, queue_action, 1, 0, 0, queue_value);
    func_800319c0(object, 0, 1, 0, 0, 0);
    func_80032320(object, 0);
final_guard:
    if (r_u32(0x800CFE24) != 0)
        return;
idle_timer:
    if (r_u32(0x800CFF1C) == 0 && r_u32(0x800CFE4C) == 0 && r_u32(0x800CFF24) == 0 && r_u32(0x800CFE54) == 0 && r_u32(0x800EDFD8) != 2)
    {
        timer = 0x800819B8 + (object << 2);
        value = r_u32(timer) - 1;
        w_u32(timer, value);
        if ((sint32)value > 0)
            return;
        if (action == 0x24)
        {
            func_80031f28(object, 0x27, 0x24);
            w_u32(timer, 180);
            return;
        }
        if (action != 0)
            return;
        func_80031ee0(object, 0x23, 0x24);
    }
    w_u32(0x800819B8 + (object << 2), 60);
}
