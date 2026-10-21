#include "functions.h"
#include "psx_press.h"
#include "psx_stream.h"
#include <string.h>

static uint32 *movie_next_frame_core(uint32 frame, uint32 stream, const uint32 *native_stream);

/* Full original bodies, pending final integration and runtime validation */
uint32 func_8003f0c0(uint32 device, uint32 *slots, uint32 *work)
{
    uint32 data[1408], previous_device, index, status, version, expected;
    FUNCTION_MARKER(0x8003F0C0, "SLUS_004.64");
    previous_device = r_u32(0x800CFD40);
    w_u32(0x800CFD40, device);
    for (index = 0; index < 4; ++index)
    {
        status = slots[index];
        if (status == 0xFFFFFFFF)
            continue;
        if (func_8003e390(data, slots, index, work) != 1)
        {
            slots[index] = 999;
            continue;
        }
        version = data[0];
        expected = r_u32(0x800CF7B8);
        if (version != expected)
            slots[index] = 999;
        if (func_8001820c(data) == 0)
            slots[index] = 999;
        func_8003ef50(data, index);
    }
    w_u32(0x800CFD40, previous_device);
    return 0;
}

uint32 func_8003f4f0(void)
{
    sint32 first_y, second_y;
    FUNCTION_MARKER(0x8003F4F0, "SLUS_004.64");
    w_u16(0x800D7B0C, (uint16)-60);
    w_u16(0x800D7B10, 64);
    w_u16(0x800D7B12, 17);
    w_u8(0x800D7B16, 0);
    w_u8(0x800D7B17, 18);
    w_u16(0x800D7B30, 7);
    w_u16(0x800D7B34, 69);
    w_u16(0x800D7B36, 6);
    w_u8(0x800D7B3A, 0);
    w_u8(0x800D7B3B, 35);
    first_y = -52;
    second_y = -43;
    do
    {
        w_u16(0x800D7B0E, (uint16)first_y);
        first_y += 44;
        GsSortFastSprite(psx_addr(0x800D7B08, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
        w_u16(0x800D7B32, (uint16)second_y);
        second_y += 44;
        GsSortFastSprite(psx_addr(0x800D7B2C, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
    } while (second_y < 133);
    return 0;
}

void func_8003f1d0(uint32 slot, uint32 alternate)
{
    FUNCTION_MARKER(0x8003F1D0, "SLUS_004.64");
    w_u16(0x800D7B0C, (uint16)-64);
    w_u16(0x800D7B0E, (uint16)(44 * slot - 60));
    w_u16(0x800D7B12, 6);
    w_u8(0x800D7B16, 0);
    if (alternate != 0)
    {
        w_u16(0x800D7B10, 89);
        w_u8(0x800D7B17, 52);
    }
    else
    {
        w_u16(0x800D7B10, 102);
        w_u8(0x800D7B17, 58);
    }
    GsSortFastSprite(psx_addr(0x800D7B08, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
}

void func_8003ee60(uint32 slot)
{
    FUNCTION_MARKER(0x8003EE60, "SLUS_004.64");
    w_u16(0x800D7B0E, (uint16)(44 * slot - 52));
    w_u8(0x800D7B16, 0);
    w_u16(0x800D7B12, 8);
    w_u16(0x800D7B0C, (uint16)-60);
    w_u8(0x800D7B17, 0);
    w_u16(0x800D7B10, 74);
    GsSortFastSprite(psx_addr(0x800D7B08, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
    w_u16(0x800D7B0C, 14);
    w_u8(0x800D7B17, 8);
    w_u16(0x800D7B10, 76);
    GsSortFastSprite(psx_addr(0x800D7B08, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
}

void func_8003e4f0(uint32 mode, uint32 selected, const uint32 *slots)
{
    uint32 index, status, device, buffer;
    FUNCTION_MARKER(0x8003E4F0, "SLUS_004.64");
    GsSortFastSprite(psx_addr(0x800E9A78, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 1);
    GsSortFastSprite(psx_addr(0x800EBE04, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 1);
    device = r_u32(0x800CFD40);
    buffer = r_u32(0x800CFD38);
    GsSortFastSprite(psx_addr(0x800D7A78 + 36 * device, 36), psx_addr(0x800D003C + 20 * buffer, 20), 0);
    for (index = 0; index < 4; ++index)
    {
        status = slots[index];
        if (status != 0xFFFFFFFF && status != 999)
        {
            if (status == 0xFFFFFFFE)
                func_8003ee60(index);
            else if (mode != 0 && selected == index)
                func_8003e978(selected, 1);
            else
                func_8003e978(index, 0);
        }
        if (mode == 1 && selected == index)
            func_8003f1d0(selected, 0);
        else if (mode == 2 && selected == index)
            func_8003f1d0(selected, 1);
    }
    GsSortFastSprite(psx_addr(0x800D7958 + 36 * selected, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
    GsSortFastSprite(psx_addr(0x800D79E8 + 36 * selected, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
}

void func_8003e978(uint32 slot, uint32 highlighted)
{
    uint32 row, value, buffer, index, time_address, x;
    FUNCTION_MARKER(0x8003E978, "SLUS_004.64");
    w_u16(0x800D7B78, (uint16)-56);
    row = 44 * slot;
    w_u16(0x800D7B7A, (uint16)(row - 52));
    value = r_u32(0x800D00B4 + (slot << 2));
    w_u8(0x800D7B83, 168);
    w_u16(0x800D7B7C, 48);
    w_u16(0x800D7B7E, 17);
    buffer = r_u32(0x800CFD38);
    w_u8(0x800D7B82, (uint8)(48 * (value - 1)));
    GsSortFastSprite(psx_addr(0x800D7B74, 36), psx_addr(0x800D003C + 20 * buffer, 20), 0);
    w_u16(0x800D7B54, (uint16)-55);
    w_u16(0x800D7B56, (uint16)(row - 49));
    value = r_u32(0x800D00B4 + (slot << 2));
    w_u8(0x800D7B5F, 199);
    w_u16(0x800D7B58, 48);
    w_u16(0x800D7B5A, 17);
    buffer = r_u32(0x800CFD38);
    w_u8(0x800D7B5E, (uint8)(48 * (value - 1)));
    GsSortFastSprite(psx_addr(0x800D7B50, 36), psx_addr(0x800D003C + 20 * buffer, 20), 0);
    if (highlighted == 0)
    {
        w_u16(0x800D7B78, 11);
        w_u16(0x800D7B7A, (uint16)(row - 60));
        w_u8(0x800D7B82, 154);
        w_u8(0x800D7B83, 185);
        w_u16(0x800D7B7C, 28);
        w_u16(0x800D7B7E, 8);
        GsSortFastSprite(psx_addr(0x800D7B74, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
        w_u16(0x800D7B54, 12);
        w_u16(0x800D7B56, (uint16)(row - 57));
        w_u8(0x800D7B5E, 154);
        w_u8(0x800D7B5F, 216);
        w_u16(0x800D7B58, 28);
        w_u16(0x800D7B5A, 8);
        GsSortFastSprite(psx_addr(0x800D7B50, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
    }
    row = 44 * (slot - 1);
    w_u16(0x800D7B7A, (uint16)(row - 5));
    w_u16(0x800D7B56, (uint16)(row - 2));
    w_u8(0x800D7B83, 185);
    w_u8(0x800D7B5F, 216);
    w_u16(0x800D7B7C, 14);
    w_u16(0x800D7B7E, 14);
    w_u16(0x800D7B58, 14);
    w_u16(0x800D7B5A, 14);
    time_address = 0x800D0084 + 12 * slot;
    for (index = 0; index < 3; ++index)
    {
        value = (uint32)(r_s32(time_address) / 10);
        w_u16(0x800D7B78, (uint16)(9 + 42 * index));
        w_u16(0x800D7B54, (uint16)(10 + 42 * index));
        buffer = r_u32(0x800CFD38);
        w_u8(0x800D7B82, (uint8)(14 * value));
        w_u8(0x800D7B5E, (uint8)(14 * value));
        GsSortFastSprite(psx_addr(0x800D7B74, 36), psx_addr(0x800D003C + 20 * buffer, 20), 0);
        GsSortFastSprite(psx_addr(0x800D7B50, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
        value = (uint32)(r_s32(time_address) % 10);
        w_u16(0x800D7B78, (uint16)(23 + 42 * index));
        w_u16(0x800D7B54, (uint16)(24 + 42 * index));
        buffer = r_u32(0x800CFD38);
        time_address += 4;
        w_u8(0x800D7B82, (uint8)(14 * value));
        w_u8(0x800D7B5E, (uint8)(14 * value));
        GsSortFastSprite(psx_addr(0x800D7B74, 36), psx_addr(0x800D003C + 20 * buffer, 20), 0);
        GsSortFastSprite(psx_addr(0x800D7B50, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
    }
    for (x = 37; x < 121; x += 42)
    {
        w_u16(0x800D7B78, (uint16)x);
        w_u16(0x800D7B54, (uint16)(x + 1));
        w_u8(0x800D7B82, 140);
        w_u8(0x800D7B5E, 140);
        GsSortFastSprite(psx_addr(0x800D7B74, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
        GsSortFastSprite(psx_addr(0x800D7B50, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
    }
}

void func_8003f8ac(void)
{
    sint32 last_handle, first_handle;
    FUNCTION_MARKER(0x8003F8AC, "SLUS_004.64");
    EnterCriticalSectionPSX();
    w_u32(0x800CFCF0, (uint32)OpenEvent(0xF4000001, 4, 0x2000, 0));
    w_u32(0x800CFCF8, (uint32)OpenEvent(0xF4000001, 0x8000, 0x2000, 0));
    w_u32(0x800CFD00, (uint32)OpenEvent(0xF4000001, 0x100, 0x2000, 0));
    w_u32(0x800CFD08, (uint32)OpenEvent(0xF4000001, 0x2000, 0x2000, 0));
    w_u32(0x800CFD10, (uint32)OpenEvent(0xF0000011, 4, 0x2000, 0));
    w_u32(0x800CFD18, (uint32)OpenEvent(0xF0000011, 0x8000, 0x2000, 0));
    w_u32(0x800CFD20, (uint32)OpenEvent(0xF0000011, 0x100, 0x2000, 0));
    last_handle = OpenEvent(0xF0000011, 0x2000, 0x2000, 0);
    first_handle = (sint32)r_u32(0x800CFCF0);
    w_u32(0x800CFD28, (uint32)last_handle);
    EnableEvent(first_handle);
    EnableEvent((sint32)r_u32(0x800CFCF8));
    EnableEvent((sint32)r_u32(0x800CFD00));
    EnableEvent((sint32)r_u32(0x800CFD08));
    EnableEvent((sint32)r_u32(0x800CFD10));
    EnableEvent((sint32)r_u32(0x800CFD18));
    EnableEvent((sint32)r_u32(0x800CFD20));
    EnableEvent((sint32)r_u32(0x800CFD28));
    ExitCriticalSection();
}

void func_80040eb4(void)
{
    FUNCTION_MARKER(0x80040EB4, "SLUS_004.64");
    InitCARD(1);
    StartCARD();
    _bu_init();
    func_8003f8ac();
}

uint32 func_8003d9f4(void)
{
    uint32 index, offset, row, column;
    FUNCTION_MARKER(0x8003D9F4, "SLUS_004.64");
    for (index = 0; index < 4; ++index)
    {
        offset = 36 * index;
        w_u32(0x800D7958 + offset, 0x0A000000);
        w_u16(0x800D7964 + offset, GetTPage(2, 0, 640, 0));
        row = index / 2;
        w_u16(0x800D7960 + offset, (uint16)(156 - 132 * row));
        w_u16(0x800D7962 + offset, 24);
        w_u16(0x800D795C + offset, (uint16)(0 - 8 - 24 * row));
        column = index - 2 * row;
        w_u16(0x800D795E + offset, (uint16)(20 * column - 12));
        w_u8(0x800D7966 + offset, 72);
        w_u8(0x800D7967 + offset, (uint8)(120 * column));
        func_8003aa84(0x800D7958 + offset);
    }
    w_u32(0x800EC1D4, 0x60000000);
    w_u16(0x800EC1D8, (uint16)-160);
    w_u16(0x800EC1DA, (uint16)-120);
    w_u16(0x800EC1DC, 320);
    w_u16(0x800EC1DE, 240);
    return 240;
}

void func_8003d7f8(uint32 device, uint32 *counter, uint32 *phase)
{
    uint32 value, offset;
    sint32 quotient, remainder;
    FUNCTION_MARKER(0x8003D7F8, "SLUS_004.64");
    GsSortFastSprite(psx_addr(0x800E9A78, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 1);
    GsSortFastSprite(psx_addr(0x800EBE04, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 1);
    value = *counter + 1;
    *counter = value;
    if (value == 2)
    {
        value = *phase + 1;
        *phase = value;
        if ((sint32)value >= 15)
            *phase = 0;
        *counter = 0;
    }
    remainder = (sint32)*phase % 3;
    offset = 36 * (device + 2);
    w_u8(0x800D7966 + offset, (uint8)(48 - 24 * (uint32)remainder));
    quotient = (sint32)*phase / 3;
    w_u8(0x800D7967 + offset, (uint8)(8 * (15 * device + 3 * (uint32)quotient)));
    GsSortFastSprite(psx_addr(0x800D7958 + 36 * device, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
    GsSortFastSprite(psx_addr(0x800D79A0 + 36 * device, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
}

uint32 func_8001b4b4(uint32 object, uint32 sequence, uint32 frame_address, uint32 steps)
{
    uint32 object_offset, sequence_offset, index, model, frame, animation, resource, result, end;
    FUNCTION_MARKER(0x8001B4B4, "SLUS_004.64");
    object_offset = object << 2;
    sequence_offset = sequence << 2;
    if (r_u32(0x800818F8 + object_offset) != sequence)
    {
        w_u32(0x800818F8 + object_offset, sequence);
        w_u32(frame_address, r_u32(0x800E27A4 + sequence_offset));
        w_u32(0x800E9830 + object_offset, r_u32(0x800EC480 + sequence_offset));
    }
    for (index = 0; (sint32)index < (sint32)steps; ++index)
    {
        model = r_u32(0x800EC400 + object_offset);
        frame = r_u32(frame_address);
        animation = r_u32(0x800E9830 + object_offset);
        resource = r_u32(0x80081498 + object_offset);
        result = func_80035954(frame, animation, 0x80082104 + 12 * object, resource, model, 2);
        w_u32(0x800E9830 + object_offset, result);
        frame = r_u32(frame_address);
        w_u32(frame_address, frame + 1);
    }
    end = r_u32(0x800EB9F8 + sequence_offset);
    end += r_u32(0x800E27A4 + sequence_offset);
    frame = r_u32(frame_address);
    if ((sint32)frame < (sint32)end)
        return 1;
    w_u32(frame_address, r_u32(0x800E27A4 + sequence_offset));
    w_u32(0x800E9830 + object_offset, r_u32(0x800EC480 + sequence_offset));
    return 0;
}

uint32 func_80016748(uint32 enabled)
{
    uint32 index, actor, floor, offset, object_offset, action, result;
    FUNCTION_MARKER(0x80016748, "SLUS_004.64");
    w_u32(0x800EDFC0, enabled);
    if (enabled != 0)
    {
        actor = r_u32(0x800EE7EC);
        floor = r_u32(0x800CF908);
        for (index = 0; index < 2; ++index)
        {
            if (index != 0)
                actor = r_u32(0x800EE7F0);
            offset = 44 * (actor - 1);
            w_u32(0x800EE72C + offset, floor);
            w_u32(0x800EE728 + offset, r_u32(0x800EE7E4));
            action = r_u32(0x80081978 + (actor << 2));
            object_offset = actor << 4;
            w_u32(0x800EE738 + offset, action);
            w_u32(0x800EE73C + offset, r_u32(r_u32(0x800DDD48 + object_offset) + 0x18));
            w_u32(0x800EE740 + offset, r_u32(r_u32(0x800DDD48 + object_offset) + 0x1C));
            w_u32(0x800EE744 + offset, r_u32(r_u32(0x800DDD48 + object_offset) + 0x20));
            w_u32(0x800EE748 + offset, (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + object_offset) + 0x44) + 0x10));
            w_u32(0x800EE74C + offset, (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + object_offset) + 0x44) + 0x12));
            w_u32(0x800EE750 + offset, (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + object_offset) + 0x44) + 0x14));
        }
        actor = r_u32(0x800EE7F0);
        w_u32(0x800EDFC4, actor);
        action = func_80031954(actor);
        w_u32(0x800EDFC8, action);
        if (action == 32 || action == 34)
            w_u32(0x800EDFC8, 32);
        else
            w_u32(0x800EDFC8, 0);
        result = r_u32(0x800EDFC4) << 2;
        w_u32(0x80081998 + result, 0);
        w_u32(0x800EE7F0, 0);
    }
    else
    {
        w_u32(0x800EE7F0, r_u32(0x800EDFC4));
        result = r_u32(0x800EDFC4) << 2;
        w_u32(0x80081998 + result, 1);
        w_u32(0x800EDFC4, 0);
    }
    return result;
}

uint32 func_80018284(void)
{
    uint32 action, partner, index, offset, object_offset, actor, saved_room, room;
    FUNCTION_MARKER(0x80018284, "SLUS_004.64");
    action = func_80031954(r_u32(0x800EE7EC));
    partner = r_u32(0x800EE7F0);
    w_u32(0x800EDFEC, action);
    if (partner != 0)
        w_u32(0x800EDFF0, func_80031954(partner));
    else
        w_u32(0x800EDFF0, 0);
    w_u32(0x800EDFA8, r_u32(0x800CF7B8));
    w_u32(0x800EDFB4, r_u32(0x800CF958));
    w_u32(0x800EDFBC, r_u32(0x800CF908));
    func_800181cc();
    for (index = 0; index < 4; ++index)
    {
        offset = 44 * index;
        w_u32(0x800EE738 + offset, r_u32(0x8008197C + (index << 2)));
        w_u32(0x800EE734 + offset, r_u32(0x8008199C + (index << 2)));
        if (r_u32(0x800EDFC4) - 1 == index)
            continue;
        actor = index + 1;
        w_u32(0x800EE730 + offset, func_80031954(actor));
        object_offset = actor << 4;
        w_u32(0x800EE73C + offset, r_u32(r_u32(0x800DDD48 + object_offset) + 0x18));
        w_u32(0x800EE740 + offset, r_u32(r_u32(0x800DDD48 + object_offset) + 0x1C));
        w_u32(0x800EE744 + offset, r_u32(r_u32(0x800DDD48 + object_offset) + 0x20));
        w_u32(0x800EE748 + offset, (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + object_offset) + 0x44) + 0x10));
        w_u32(0x800EE74C + offset, (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + object_offset) + 0x44) + 0x12));
        w_u32(0x800EE750 + offset, (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + object_offset) + 0x44) + 0x14));
    }
    actor = r_u32(0x800EDFC4);
    offset = 44 * (actor - 1);
    saved_room = r_u32(0x800EE728 + offset);
    room = r_u32(0x800EE7E4);
    if (saved_room == room)
    {
        w_u32(0x800EE738 + offset, r_u32(0x8008197C + ((actor - 1) << 2)));
        w_u32(0x800EE734 + offset, r_u32(0x8008199C + ((actor - 1) << 2)));
        w_u32(0x800EE730 + offset, func_80031954(actor));
        object_offset = actor << 4;
        w_u32(0x800EE73C + offset, r_u32(r_u32(0x800DDD48 + object_offset) + 0x18));
        w_u32(0x800EE740 + offset, r_u32(r_u32(0x800DDD48 + object_offset) + 0x1C));
        w_u32(0x800EE744 + offset, r_u32(r_u32(0x800DDD48 + object_offset) + 0x20));
        w_u32(0x800EE748 + offset, (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + object_offset) + 0x44) + 0x10));
        w_u32(0x800EE74C + offset, (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + object_offset) + 0x44) + 0x12));
        w_u32(0x800EE750 + offset, (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + object_offset) + 0x44) + 0x14));
    }
    return func_80018244();
}

uint32 func_800186b4(void)
{
    uint32 actor, partner, object, action, index, offset, object_offset, destination, mode, room, result;
    FUNCTION_MARKER(0x800186B4, "SLUS_004.64");
    func_80016250();
    w_u32(0x800CF860, 1);
    func_8001aafc();
    func_8001ab94();
    func_8001a830();
    if (func_80023b2c(r_u32(0x800EDFB4)) == 0)
        func_8001ef00();
    func_80016290();
    w_u32(0x800CF908, r_u32(0x800EDFBC));
    func_8001afcc();
    actor = r_u32(0x800EE7EC);
    partner = r_u32(0x800EE7F0);
    w_u32(0x800814B8, 0);
    mode = r_u32(0x800CFA6C);
    room = r_u32(0x800EE7E4);
    w_u32(0x800CFA90, 1);
    w_u32(0x800EE7E8, 0);
    func_80022320(mode, room, 0);
    w_u32(0x800CFA90, 0);
    w_u32(0x800CF87C, 1);
    w_u32(0x800EE7EC, actor);
    w_u32(0x800EE7F0, partner);
    func_8003943c(0);
    func_8001663c();
    func_80016690();
    func_80031884();
    func_80022a08();
    for (index = 1; index < 5; ++index)
        func_8001e8d8((sint32)index);
    func_8001f13c();
    w_u32(0x800CF908, r_u32(0x800EDFBC));
    for (index = 1; index < 5; ++index)
        func_80020a48(index, r_u32(0x800EE72C + 44 * (index - 1)));
    for (index = 1; index < 5; ++index)
        func_80020b7c(index, r_u32(0x800EE72C + 44 * (index - 1)));
    func_80020834(r_u32(0x800EDFBC));
    for (index = 0; index < 4; ++index)
    {
        offset = 44 * index;
        if (r_u32(0x800EE738 + offset) != 0)
            func_8001e8b4((sint32)(index + 1));
        else
            func_8001e8d8((sint32)(index + 1));
        w_u32(0x8008199C + (index << 2), r_u32(0x800EE734 + offset));
        object = index + 1;
        object_offset = object << 4;
        destination = r_u32(0x800DDD48 + object_offset);
        w_u32(destination + 0x18, r_u32(0x800EE73C + offset));
        destination = r_u32(0x800DDD48 + object_offset);
        w_u32(destination + 0x1C, r_u32(0x800EE740 + offset));
        destination = r_u32(0x800DDD48 + object_offset);
        w_u32(destination + 0x20, r_u32(0x800EE744 + offset));
        destination = r_u32(r_u32(0x800DDD48 + object_offset) + 0x44);
        w_u16(destination + 0x10, r_u16(0x800EE748 + offset));
        destination = r_u32(r_u32(0x800DDD48 + object_offset) + 0x44);
        w_u16(destination + 0x12, r_u16(0x800EE74C + offset));
        destination = r_u32(r_u32(0x800DDD48 + object_offset) + 0x44);
        w_u16(destination + 0x14, r_u16(0x800EE750 + offset));
        actor = r_u32(0x800EE7EC);
        action = r_u32(0x800EE730 + offset);
        if (object != actor && object != r_u32(0x800EE7F0))
        {
            func_80031c20(object, action, 1, 0, 0, 0);
            func_80032320(object, action);
        }
    }
    actor = r_u32(0x800EE7EC);
    action = r_u32(0x800EDFEC);
    func_80019378(actor, action);
    partner = r_u32(0x800EE7F0);
    if (partner != 0)
        func_80019378(partner, r_u32(0x800EDFF0));
    func_8001dc98();
    func_80014ffc();
    w_u32(0x800CF82C, r_u32(0x800EDFB0));
    result = (uint32)VSync(-1);
    w_u32(0x800CF830, result);
    w_u32(0x800CF860, 0);
    return result;
}

void func_800190ec(sint32 identifier)
{
    char pattern[64], path[64], *digits;
    uint8 parts[3];
    uint32 source, destination, shift, high, low, words[4], group, word;
    sint32 music, source_mode;
    FUNCTION_MARKER(0x800190EC, "SLUS_004.64");
    memcpy(pattern, psx_addr(0x80010494, 17), 17);
    memset(pattern + 17, 0, 47);
    strcpy(path, pattern);
    digits = strchr(path, '?');
    parts[0] = (uint8)(identifier / 100);
    parts[1] = (uint8)((identifier % 100) / 10);
    parts[2] = (uint8)((identifier % 100) % 10);
    for (word = 0; word < 3; ++word)
        digits[word] = (char)(parts[word] + 48);
    func_80017a74();
    func_8003943c(0);
    source = r_u32(0x800CF9FC);
    source_mode = r_s32(0x800CF804);
    func_80036184(path, source, source_mode);
    func_800162b0();
    source = r_u32(0x800CF9FC);
    destination = 0x800EDFA8;
    shift = (source & 3) << 3;
    for (group = 0; group < 351; ++group)
    {
        for (word = 0; word < 4; ++word)
        {
            if (shift != 0)
            {
                high = r_u32((source + (word << 2) + 3) & 0xFFFFFFFC);
                low = r_u32((source + (word << 2)) & 0xFFFFFFFC);
                words[word] = (low >> shift) | (high << (32 - shift));
            }
            else
                words[word] = r_u32(source + (word << 2));
        }
        for (word = 0; word < 4; ++word)
        {
            w_u32(destination + (word << 2), words[word]);
            if (shift != 0)
                w_u32(destination + (word << 2), words[word]);
        }
        source += 16;
        destination += 16;
    }
    for (word = 0; word < 3; ++word)
    {
        high = r_u32((source + (word << 2) + 3) & 0xFFFFFFFC);
        low = r_u32((source + (word << 2)) & 0xFFFFFFFC);
        if (shift != 0)
            words[word] = (low >> shift) | (high << (32 - shift));
        else
            words[word] = low;
    }
    for (word = 0; word < 3; ++word)
    {
        w_u32(destination + (word << 2), words[word]);
        w_u32(destination + (word << 2), words[word]);
    }
    func_800186b4();
    music = r_s32(0x800EDFB8);
    w_u32(0x800CF8B4, 0);
    if (music > 0)
    {
        if (music < 101)
            func_800178b0(music, 0);
        else
            func_80017aa0((sint32)(r_u32(0x800EDFB8) - 100), 0);
    }
}

void func_8001992c(void)
{
    uint32 page, index, first, second, base, offset;
    const char *format;
    FUNCTION_MARKER(0x8001992C, "SLUS_004.64");
    if (r_u32(0x800CFE24) != 0)
        return;
    page = r_u32(0x800CFA70) - 1;
    if (page > 6)
        return;
    switch (page)
    {
    case 0:
        FntPrint("-----EVENT-------\n");
        FntPrint("run event = %d\n", r_s32(0x800CFF7C));
        FntPrint("push event = %d\n", r_s32(0x800CFE0C));
        FntPrint("push event2 = %d\n", r_s32(0x800CFE1C));
        FntPrint("use event = %d\n", r_s32(0x800CFF6C));
        FntPrint("use event2 = %d\n", r_s32(0x800CFD9C));
        FntPrint("last event = %d\n", r_s32(0x800CFDE4));
        FntPrint("macro ptr = %d\n", r_s32(0x800CFF8C));
        FntPrint("macro cmd = %d\n", r_s32(0x800CFF54));
        break;
    case 1:
        FntPrint("-----MEMORY-------\n");
        first = r_u32(0x800CFA48);
        second = r_u32(0x800CFA4C);
        FntPrint("ROOM-ADDR = %x-%x\n", first, second);
        first = r_u32(0x800CFA50);
        second = r_u32(0x800CFA54);
        FntPrint("MES-ADDR = %x-%x\n", first, second);
        first = r_u32(0x800CFA5C);
        second = r_u32(0x800CFA64);
        FntPrint("MAC-ADDR = %x-%x\n", first, second);
        first = r_u32(0x800CFA20);
        second = r_u32(0x800CFA14);
        FntPrint("TOD-ADDR = %x-%x\n", first, second);
        first = r_u32(0x800CFA04);
        second = r_u32(0x800CFA08);
        FntPrint("GEST-TOD = %x-%x\n", first, second);
        first = r_u32(0x800CF9FC);
        second = r_u32(0x800CFA00);
        FntPrint("READ-BUF = %x-%x\n", first, second);
        first = r_u32(0x800CFA28);
        second = r_u32(0x800CFA2C);
        FntPrint("MOVIE-ADDR = %x-%x\n", first, second);
        first = r_u32(0x800CFA78);
        second = r_u32(0x800CFA7C);
        FntPrint("AREA1 = %x-%x\n", first, second);
        first = r_u32(0x800CFA80);
        second = r_u32(0x800CFA84);
        FntPrint("AREA2 = %x-%x\n", first, second);
        first = r_u32(0x800CFA88);
        second = r_u32(0x800CFA8C);
        FntPrint("AREA3 = %x-%x\n", first, second);
        break;
    case 2:
    case 3:
    case 4:
        if (page == 2)
        {
            FntPrint("-----WORK-------\n");
            base = 0x800814B8;
            format = "WORK:[%2d]=%5d [%2d] =%5d\n";
        }
        else if (page == 3)
        {
            FntPrint("-----SAVE WORK-------\n");
            base = 0x800EE8D8;
            format = "SWORK:[%2d]=%5d [%2d] =%5d\n";
        }
        else
        {
            FntPrint("-----INFOMATION-------\n");
            base = 0x800EE7D8;
            format = "INFO:[%2d]=%5d [%2d] =%5d\n";
        }
        for (index = 0; index < 16; ++index)
        {
            second = r_u32(base + 64 + (index << 2));
            first = r_u32(base + (index << 2));
            FntPrint(format, (sint32)index, (sint32)first, (sint32)(index + 16), (sint32)second);
        }
        break;
    case 5:
        FntPrint("-----DEBUG 1-------\n");
        FntPrint("PUSH OWNER:=%d\n", r_s32(0x800CF8C4));
        FntPrint("RoomObjectNum:=%d\n", r_s32(0x800CF8B0));
        FntPrint("NOWROOM:=%d\n", r_s32(0x800EE7E4));
        FntPrint("OLDROOM:=%d\n", r_s32(0x800EE7E8));
        FntPrint("GROUND:=%d\n", r_s32(0x800CF908));
        offset = 44 * (r_u32(0x800EDFC4) - 1);
        FntPrint("BUNRI_SUB_G:=%d\n", r_s32(0x800EE72C + offset));
        FntPrint("AnimeNum:=%d\n", r_s32(0x800CFEA4));
        FntPrint("FrameMode:=%d\n", r_s32(0x800CF864));
        FntPrint("OldDatTime:=%d\n", r_s32(0x800CF82C));
        FntPrint("StartTime:=%d\n", r_s32(0x800CF830));
        FntPrint("NowTime:=%d\n", r_s32(0x800CF834));
        FntPrint("Now_Packet:=%d\n", r_s32(0x800CF7AC));
        FntPrint("FrameMode:=%d\n", r_s32(0x800CF864));
        break;
    case 6:
        FntPrint("----- VOICE COUNTER ------\n");
        FntPrint("VOICE CNT:=(%d)\n", (sint32)func_80012bbc());
        break;
    }
    FntFlush(-1);
}

void func_8003fd20(void)
{
    FUNCTION_MARKER(0x8003FD20, "SLUS_004.64");
    EnterCriticalSectionPSX();
    CloseEvent((sint32)r_u32(0x800CFCF0));
    CloseEvent((sint32)r_u32(0x800CFCF8));
    CloseEvent((sint32)r_u32(0x800CFD00));
    CloseEvent((sint32)r_u32(0x800CFD08));
    CloseEvent((sint32)r_u32(0x800CFD10));
    CloseEvent((sint32)r_u32(0x800CFD18));
    CloseEvent((sint32)r_u32(0x800CFD20));
    CloseEvent((sint32)r_u32(0x800CFD28));
    ExitCriticalSection();
}

sint32 func_8003d5bc(uint32 first, uint32 second)
{
    uint32 counter, phase, timer, device, level, buttons, confirmed;
    sint32 result;
    FUNCTION_MARKER(0x8003D5BC, "SLUS_004.64");
    w_u32(0x800CFD30, first);
    w_u32(0x800CFD34, second);
    func_8003d52c();
    timer = 0;
    device = 0;
    func_80039dc4(779, 0, 0, r_u32(0x800CF9FC));
    w_u32(0x800CFC18, 0);
    func_8003d9f4();
    func_8003aa84(0x800E9A78);
    func_8003aa84(0x800EBE04);
    phase = 0;
    counter = 0;
    func_8003d3a0();
    level = 32;
    do
    {
        --level;
        func_8003d450();
        func_8003d3e0(level);
        func_8003d7f8(device, &counter, &phase);
    } while (level != 0);
    for (;;)
    {
        confirmed = 0;
        func_8003d450();
        func_800240c0();
        func_8003d7f8(device, &counter, &phase);
        buttons = PadRead(0);
        if ((buttons & 0x1000) != 0)
        {
            if ((sint32)timer >= 301)
                timer = 300;
            if (device == 1)
            {
                func_8002372c(4);
                device = 0;
            }
        }
        if ((buttons & 0x4000) != 0)
        {
            if ((sint32)timer >= 301)
                timer = 300;
            if (device == 0)
            {
                func_8002372c(4);
                device = 1;
            }
        }
        if ((buttons & 0x40) != 0)
        {
            if ((sint32)timer >= 301)
                timer = 300;
            if (r_u8(0x800CFC35) == 0)
            {
                confirmed = 1;
                func_8002372c(1);
            }
        }
        else
            w_u8(0x800CFC35, 0);
        if ((buttons & 0x800) != 0)
        {
            if ((sint32)timer >= 301)
                timer = 300;
            if (r_u8(0x800CFC34) == 0)
            {
                confirmed = 1;
                func_8002372c(1);
            }
        }
        else
            w_u8(0x800CFC34, 0);
        ++timer;
        if ((sint32)timer >= 601)
        {
            result = -1;
            break;
        }
        if (confirmed != 0)
        {
            result = (sint32)device;
            break;
        }
    }
    for (level = 1; level < 34; ++level)
    {
        func_8003d450();
        func_8003d3e0(level);
        func_8003d7f8(device, &counter, &phase);
    }
    return result;
}

uint32 func_8003f610(void)
{
    uint32 index, offset;
    FUNCTION_MARKER(0x8003F610, "SLUS_004.64");
    for (index = 0; index < 16; ++index)
    {
        offset = 36 * index;
        w_u32(0x800D7958 + offset, 0x0A000000);
        w_u16(0x800D7964 + offset, GetTPage(2, 0, 640, 0));
        func_8003aa84(0x800D7958 + offset);
    }
    for (index = 0; index < 4; ++index)
    {
        offset = 36 * index;
        w_u8(0x800D7966 + offset, 0);
        w_u8(0x800D7967 + offset, (uint8)(43 * index));
        w_u16(0x800D7960 + offset, 59);
        w_u16(0x800D7962 + offset, 42);
        w_u16(0x800D795C + offset, (uint16)-134);
        w_u16(0x800D795E + offset, (uint16)(43 * index - 66));
    }
    w_u16(0x800D79CE, 40);
    for (index = 0; index < 4; ++index)
    {
        offset = 36 * (index + 4);
        w_u8(0x800D7966 + offset, 60);
        w_u8(0x800D7967 + offset, (uint8)(38 * index));
        w_u16(0x800D7960 + offset, 195);
        w_u16(0x800D7962 + offset, 37);
        w_u16(0x800D795C + offset, (uint16)-68);
        w_u16(0x800D795E + offset, (uint16)(43 * index - 63));
    }
    for (index = 0; index < 2; ++index)
    {
        offset = 36 * (index + 8);
        w_u8(0x800D7966 + offset, (uint8)(60 + 37 * index));
        w_u8(0x800D7967 + offset, 152);
        w_u16(0x800D7960 + offset, 37);
        w_u16(0x800D7962 + offset, 11);
        w_u16(0x800D795C + offset, (uint16)-20);
        w_u16(0x800D795E + offset, (uint16)-85);
    }
    for (offset = 432; offset < 504; offset += 36)
        w_u16(0x800D7964 + offset, GetTPage(2, 0, 896, 0));
    w_u32(0x800D7B50, r_u32(0x800D7B50) + 0x40000000);
    return 0x800D7B50;
}

sint32 func_8003fa54(uint32 first, uint32 second)
{
    uint32 channel, status;
    FUNCTION_MARKER(0x8003FA54, "SLUS_004.64");
    channel = first != 0 ? 16 : 0;
    _card_info((sint32)channel);
    status = func_8003fb70();
    if (status == 1)
        return -2;
    if (status != 0 && status != 3)
        return 0;
    if (status == 3)
    {
        func_8003fcc8();
        func_80042450(channel);
        func_8003fbf0();
    }
    func_8003fc70();
    psx_bios_card_load_guest(channel);
    status = func_8003fb70();
    if (status == 0)
        return 1;
    if (status == 2)
        return -2;
    if (status != 3)
        return 0;
    return func_8004016c(channel, second) == 1 ? 1 : -1;
}

uint32 func_8004016c(uint32 channel, uint32 work)
{
    uint32 index, texture, input, confirmed;
    FUNCTION_MARKER(0x8004016C, "SLUS_004.64");
    func_8003d3a0();
    func_80040500(channel != 0 ? 8 : 7, 0, work);
    for (index = 0; index < 4; ++index)
        func_80040500(index, index + 1, work);
    w_u32(0x800D7AE4, 0x08000000);
    w_u16(0x800D7AF0, GetTPage(0, 0, 960, 256));
    w_u8(0x800D7AF2, 0);
    w_u8(0x800D7AF3, 0);
    w_u16(0x800D7AEC, 255);
    w_u16(0x800D7AEE, 100);
    w_u16(0x800D7AF4, 960);
    w_u16(0x800D7AF6, 481);
    w_u16(0x800D7AE8, (uint16)-130);
    w_u16(0x800D7AEA, (uint16)-50);
    func_8003aa84(0x800D7AE4);
    texture = r_u16(0x800D7AF0);
    w_u32(0x800F0174, 0x08000000);
    w_u8(0x800F0188, 255);
    w_u8(0x800F0189, 96);
    w_u8(0x800F018A, 0);
    w_u16(0x800F0178, (uint16)-92);
    w_u16(0x800F017A, 30);
    w_u8(0x800F0182, 38);
    w_u8(0x800F0183, 80);
    w_u16(0x800F0184, 960);
    w_u16(0x800F0186, 481);
    w_u16(0x800F017C, 36);
    w_u16(0x800F017E, 20);
    w_u16(0x800F0180, (uint16)texture);
    for (;;)
    {
        func_8003d450();
        GsSortFastSprite(psx_addr(0x800F0174, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
        GsSortFastSprite(psx_addr(0x800D7AE4, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
        input = func_8003d034();
        if (input == 6)
        {
            func_8002372c(2);
            confirmed = 0;
            break;
        }
        if (input == 5)
        {
            func_8002372c(1);
            confirmed = 1;
            break;
        }
    }
    func_8003d3a0();
    if (confirmed == 1)
    {
        func_80040500(4, 0, work);
        w_u16(0x800D7AEE, 20);
        w_u16(0x800D7AE8, (uint16)-130);
        w_u16(0x800D7AEA, (uint16)-10);
        GsSortFastSprite(psx_addr(0x800D7AE4, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
        func_8003d450();
        GsSortFastSprite(psx_addr(0x800D7AE4, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
        func_8003d450();
        func_80040590(channel != 0 ? 0x800CFC44 : 0x800CFC3C, work);
        return 1;
    }
    func_80040500(9, 0, work);
    w_u16(0x800D7AEE, 20);
    w_u16(0x800D7AE8, (uint16)-130);
    w_u16(0x800D7AEA, (uint16)-10);
    do
    {
        GsSortFastSprite(psx_addr(0x800D7AE4, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
        func_8003d450();
        input = func_8003d034();
    } while (input != 6);
    return 0;
}

uint32 func_80040500(uint32 message, uint32 row, uint32 work)
{
    uint32 descriptor[16];
    FUNCTION_MARKER(0x80040500, "SLUS_004.64");
    descriptor[0] = 0x800B5074 + 31 * message;
    descriptor[1] = 960;
    descriptor[2] = 256 + 20 * row;
    descriptor[3] = 960;
    descriptor[4] = 481;
    descriptor[5] = 0xFFFFFF;
    descriptor[6] = 0;
    descriptor[7] = 15;
    descriptor[8] = 1;
    descriptor[9] = 0;
    descriptor[14] = work;
    descriptor[15] = work + 6880;
    render_text_descriptor(descriptor);
    return 80;
}

uint32 func_800400d8(uint32 message, uint32 row, uint32 work)
{
    uint32 descriptor[16];
    FUNCTION_MARKER(0x800400D8, "SLUS_004.64");
    descriptor[0] = 0x800B5018 + 30 * message;
    descriptor[1] = 960;
    descriptor[2] = 256 + 20 * row;
    descriptor[3] = 960;
    descriptor[4] = 481;
    descriptor[5] = 0xFFFFFF;
    descriptor[6] = 0;
    descriptor[7] = 15;
    descriptor[8] = 1;
    descriptor[9] = 0;
    descriptor[14] = work;
    descriptor[15] = work + 6880;
    render_text_descriptor(descriptor);
    return 80;
}

uint32 func_8003e6ec(uint32 message, uint32 work)
{
    uint32 descriptor[16], input;
    FUNCTION_MARKER(0x8003E6EC, "SLUS_004.64");
    func_8003d3a0();
    descriptor[0] = 0x800B4D98 + 80 * message;
    descriptor[1] = 960;
    descriptor[2] = 256;
    descriptor[3] = 960;
    descriptor[4] = 481;
    descriptor[5] = 0xFFFFFF;
    descriptor[6] = 0;
    descriptor[7] = 14;
    descriptor[8] = 1;
    descriptor[9] = 0;
    descriptor[14] = work;
    descriptor[15] = work + 6880;
    render_text_descriptor(descriptor);
    descriptor[0] = 0x800B4DC0 + 80 * message;
    descriptor[1] = 960;
    descriptor[2] = 276;
    descriptor[3] = 960;
    descriptor[4] = 481;
    descriptor[5] = 0xFFFFFF;
    descriptor[6] = 0;
    descriptor[7] = 14;
    descriptor[8] = 1;
    descriptor[9] = 0;
    descriptor[14] = work;
    descriptor[15] = work + 6880;
    render_text_descriptor(descriptor);
    w_u32(0x800D7958, 0x08000000);
    w_u16(0x800D7964, GetTPage(0, 0, 960, 256));
    w_u8(0x800D7966, 0);
    w_u8(0x800D7967, 0);
    w_u16(0x800D7960, 238);
    w_u16(0x800D7962, 40);
    w_u16(0x800D7968, 960);
    w_u16(0x800D796A, 481);
    w_u16(0x800D795C, (uint16)-112);
    w_u16(0x800D795E, (uint16)-10);
    func_8003aa84(0x800D7958);
    do
    {
        func_8003d450();
        GsSortFastSprite(psx_addr(0x800D7958, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
        input = func_8003d034();
    } while (input != 6);
    return input;
}

uint32 func_8003fdc8(uint32 work, uint32 selected, const uint32 *slots, uint32 first_message)
{
    uint32 index, offset, texture, input, result;
    FUNCTION_MARKER(0x8003FDC8, "SLUS_004.64");
    func_8003d3a0();
    for (index = first_message; (sint32)index < 3; ++index)
        func_800400d8(index, index, work);
    w_u32(0x800D7AE4, 0x08000000);
    w_u16(0x800D7AF0, GetTPage(0, 0, 960, 256));
    w_u8(0x800D7AF2, 0);
    w_u8(0x800D7AF3, 0);
    w_u16(0x800D7AEC, 238);
    w_u16(0x800D7AEE, 60);
    w_u16(0x800D7AF4, 960);
    w_u16(0x800D7AF6, 481);
    w_u16(0x800D7AE8, (uint16)-76);
    w_u16(0x800D7AEA, (uint16)-30);
    func_8003aa84(0x800D7AE4);
    for (index = 0; index < 16; ++index)
    {
        offset = 36 * index;
        if (index != 11)
        {
            w_u8(0x800D796C + offset, r_u8(0x800D796C + offset) >> 1);
            w_u8(0x800D796D + offset, r_u8(0x800D796D + offset) >> 1);
            w_u8(0x800D796E + offset, r_u8(0x800D796E + offset) >> 1);
        }
    }
    texture = r_u16(0x800D7AF0);
    w_u32(0x800F0174, 0x08000000);
    w_u8(0x800F0188, 255);
    w_u8(0x800F0189, 96);
    w_u8(0x800F018A, 0);
    w_u16(0x800F0178, 25);
    w_u16(0x800F017A, (uint16)-10);
    w_u8(0x800F0182, 101);
    w_u8(0x800F0183, 20);
    w_u16(0x800F0184, 960);
    w_u16(0x800F0186, 481);
    w_u16(0x800F017C, 54);
    w_u16(0x800F017E, 20);
    w_u16(0x800F0180, (uint16)texture);
    for (;;)
    {
        GsSortFastSprite(psx_addr(0x800F0174, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
        GsSortFastSprite(psx_addr(0x800D7AE4, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
        func_8003e4f0(0, selected, slots);
        func_8003d450();
        input = func_8003d034();
        if (input == 6)
        {
            func_8002372c(2);
            result = 1;
            break;
        }
        if (input == 5)
        {
            func_8002372c(1);
            result = 0;
            break;
        }
    }
    for (offset = 0; offset < 576; offset += 36)
    {
        if (r_u8(0x800D796C + offset) == 64)
            func_8003aa84(0x800D7958 + offset);
    }
    func_8003e4f0(0, selected, slots);
    func_8003d450();
    return result;
}

uint32 func_8003f288(uint32 path, uint32 buffer)
{
    uint32 types[6], offsets[6], sizes[6], index, x, y, width, height, rect_xy, rect_wh;
    FUNCTION_MARKER(0x8003F288, "SLUS_004.64");
    func_8003ccac(guest_c_string(path), buffer);
    read_resource_directory(5, types, offsets, sizes, buffer);
    for (index = 0; index < 2; ++index)
    {
        x = r_u16(0x800B4FC8 + (index << 2));
        y = r_u16(0x800B4FDC + (index << 2));
        width = r_u16(0x800B4FF0 + (index << 2));
        height = r_u16(0x800B5004 + (index << 2));
        rect_xy = x | (y << 16);
        rect_wh = width | (height << 16);
        func_8003cdd4(guest_c_string(path), buffer, offsets[index], sizes[index], types[index], rect_xy, rect_wh);
    }
    func_8003ceec();
    func_8003aa84(0x800E9A78);
    func_8003aa84(0x800EBE04);
    for (index = 0; index < 2; ++index)
    {
        func_8003d450();
        GsSortFastSprite(psx_addr(0x800E9A78, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 1);
        GsSortFastSprite(psx_addr(0x800EBE04, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 1);
        func_8003f4f0();
    }
    func_8003d450();
    for (index = 2; index < 5; ++index)
    {
        x = r_u16(0x800B4FC8 + (index << 2));
        y = r_u16(0x800B4FDC + (index << 2));
        width = r_u16(0x800B4FF0 + (index << 2));
        height = r_u16(0x800B5004 + (index << 2));
        rect_xy = x | (y << 16);
        rect_wh = width | (height << 16);
        func_8003cdd4(guest_c_string(path), buffer, offsets[index], sizes[index], types[index], rect_xy, rect_wh);
    }
    return 0;
}

sint32 func_8001fbe8(uint32 room_header)
{
    uint32 cursor, value, old_count, count, index, field, offset, object, parent, transform;
    uint32 words[16];
    static const uint32 header_counts[4] = {0x800CFD94, 0x800CFEB4, 0x800CFEA4, 0x800CFE74};
    static const uint32 lighting_fields[8] = {0x800CFF94, 0x800CFF74, 0x800CFF64, 0x800CFE9C, 0x800CFFAC, 0x800CFF9C, 0x800CFF84, 0x800CFE44};
    FUNCTION_MARKER(0x8001FBE8, "SLUS_004.64");
    cursor = room_header + 40;
    value = r_u32(cursor);
    old_count = r_u32(0x800CFF2C);
    cursor += 4;
    w_u32(0x800CFF2C, value);
    for (field = 0; field < 4; ++field)
    {
        value = r_u32(cursor);
        cursor += 4;
        w_u32(header_counts[field], value);
    }
    for (index = 0; index < 4; ++index)
    {
        value = r_u32(cursor);
        cursor += 4;
        w_u32(0x80081918 + 4 * index, value);
        value = r_u32(cursor);
        cursor += 4;
        w_u32(0x80081938 + 4 * index, value);
    }
    for (index = 8; (sint32)index < (sint32)old_count; ++index)
    {
        object = r_u32(0x800DDD48 + 16 * index);
        w_u32(object, 1);
    }
    count = r_u32(0x800CFF2C);
    index = 0;
    while ((sint32)index < (sint32)count)
    {
        for (field = 0; field < 16; ++field)
        {
            words[field] = r_u32(cursor);
            cursor += 4;
        }
        offset = 16 * index;
        object = r_u32(0x800DDD48 + offset);
        if (words[2] != 0)
            parent = r_u32(0x800DDD48 + 16 * words[2]);
        else
            parent = 0;
        w_u32(object + 0x48, parent);
        value = r_u32(0x800DDD44 + offset);
        value = words[0] != 0 ? value & 0x7FFFFFFF : value | 0x80000000;
        w_u32(0x800DDD44 + offset, value);
        w_u32(0x800EBC14 + 4 * index, words[0]);
        w_u32(0x800F0054 + 4 * index, words[2]);
        w_u32(0x800EF754 + 4 * index, words[1]);
        w_u32(0x800E9B14 + 4 * index, words[4]);
        w_u32(0x800DF0C4 + 4 * index, words[5]);
        w_u32(0x800EC030 + 4 * index, words[6]);
        w_u32(0x800EC604 + 4 * index, words[3]);
        for (field = 0; field < 3; ++field)
        {
            object = r_u32(0x800DDD48 + offset);
            w_u32(object + 0x18 + 4 * field, words[7 + field]);
        }
        for (field = 0; field < 3; ++field)
        {
            object = r_u32(0x800DDD48 + offset);
            transform = r_u32(object + 0x44);
            w_u32(transform + 4 * field, words[10 + field]);
        }
        for (field = 0; field < 3; ++field)
        {
            object = r_u32(0x800DDD48 + offset);
            transform = r_u32(object + 0x44);
            w_u16(transform + 0x10 + 2 * field, (uint16)words[13 + field]);
        }
        object = r_u32(0x800DDD48 + offset);
        w_u32(object, 0);
        func_8001b21c(0x800DDD44 + offset);
        count = r_u32(0x800CFF2C);
        ++index;
    }
    count = r_u32(0x800CFD94);
    for (index = 0; (sint32)index < (sint32)count; ++index)
    {
        for (field = 0; field < 11; ++field)
        {
            value = r_u32(cursor);
            cursor += 4;
            w_u32(0x8007F064 + 44 * index + 4 * field, value);
        }
    }
    w_u32(0x8007F064 + 44 * index, 0xFFFFFFFF);
    count = r_u32(0x800CFEB4);
    for (index = 0; (sint32)index < (sint32)count; ++index)
    {
        for (field = 0; field < 14; ++field)
        {
            value = r_u32(cursor);
            cursor += 4;
            w_u32(0x80080194 + 56 * index + 4 * field, value);
        }
    }
    w_u32(0x80080194 + 56 * index, 0xFFFFFFFF);
    if (r_u32(0x800CF880) != 0)
    {
        for (index = 0; index < 3; ++index)
        {
            for (field = 0; field < 7; ++field)
            {
                value = r_u32(cursor);
                cursor += 4;
                w_u32(0x80080F94 + 28 * index + 4 * field, value);
            }
        }
    }
    else
        cursor += 84;
    count = r_u32(0x800CFEA4);
    if ((sint32)count > 0)
    {
        for (index = 0; (sint32)index < (sint32)count; ++index)
        {
            for (field = 0; field < 14; ++field)
            {
                value = r_u32(cursor);
                cursor += 4;
                w_u32(0x8007E064 + 64 * index + 4 * field, value);
            }
            value = r_u32(cursor);
            w_u32(0x8007E064 + 64 * index + 60, 0);
            w_u32(0x8007E064 + 64 * index + 56, value);
            cursor += 4;
        }
        count = r_u32(0x800CFEA4);
    }
    w_u32(0x8007E064 + 64 * count, 0xFFFFFFFF);
    count = r_u32(0x800CFE74);
    for (index = 0; (sint32)index < (sint32)count; ++index)
    {
        for (field = 0; field < 7; ++field)
        {
            value = r_u32(cursor);
            cursor += 4;
            w_u32(0x8007DCE4 + 28 * index + 4 * field, value);
        }
    }
    count = r_u32(0x800CFE74);
    w_u32(0x8007DCE4 + 28 * count, 0xFFFFFFFF);
    if (r_u32(0x800CF880) != 0)
    {
        for (field = 0; field < 8; ++field)
        {
            value = r_u32(cursor);
            cursor += 4;
            w_u32(lighting_fields[field], value);
        }
    }
    func_8001afcc();
    return func_80020730();
}

void func_80023828(sint32 resource)
{
#ifndef NDEBUG
    uint32 end_sector, start_sector;
#endif
    FUNCTION_MARKER(0x80023828, "SLUS_004.64");
    func_80017aa0(resource, 1);
    while (func_800385e8() != 0)
    {
        if ((func_80012658() & 0x20) != 0)
        {
            func_80038854();
            break;
        }
    }
    func_8002372c(1);
#ifndef NDEBUG
    end_sector = r_u32(0x800CFFBC);
    start_sector = r_u32(0x800CFEAC);
    printf("xa=%dsect.\n", (sint32)(end_sector - start_sector));
#endif
}

static uint32 movie_prepare_frame_core(uint32 frame, uint32 stream, const uint32 *native_stream)
{
    uint32 retries, selected, output, bytes;
    uint32 *data;
    retries = 0x800000;
    for (;;)
    {
        data = movie_next_frame_core(frame, stream, native_stream);
        --retries;
        if (data != 0)
            break;
        if (retries == 0)
            return 0;
    }
    selected = r_u32(frame + 8);
    w_u32(frame + 8, selected == 0 ? 1 : 0);
    selected = r_u32(frame + 8);
    output = r_u32(frame + (selected << 2));
    bytes = 4 + (*data & 0xFFFF) * 4;
    DecDCTvlc(data, (uint32 *)psx_addr(output, bytes));
    return StFreeRing(data);
}

uint32 func_800312e8(uint32 frame, uint32 stream)
{
    FUNCTION_MARKER(0x800312E8, "SLUS_004.64");
    return movie_prepare_frame_core(frame, stream, 0);
}

uint32 prepare_movie_frame(uint32 frame, const uint32 *stream)
{
    return movie_prepare_frame_core(frame, 0, stream);
}

static sint32 stream_location_core(uint32 location_guest, uint8 *native_location)
{
    sint32 result;
    do
    {
        while (CdControl(2, native_location != 0 ? native_location : (uint8 *)psx_addr(location_guest, 4), 0) == 0)
        {
        }
        result = CdRead2(0x1C0);
    }
    while (result == 0);
    return result;
}

sint32 func_800315a4(uint32 location)
{
    FUNCTION_MARKER(0x800315A4, "SLUS_004.64");
    return stream_location_core(location, 0);
}

sint32 start_stream_location(uint8 *location)
{
    return stream_location_core(0, location);
}

static uint32 *movie_next_frame_core(uint32 frame, uint32 stream, const uint32 *native_stream)
{
    uint32 retries, result, limit, number, width, height, previous, mode, scaled, changed;
    uint32 *data, *header;
    StHEADER *native_header;
    PSX_RECT rectangle;
    retries = 0x800000;
    for (;;)
    {
        result = StGetNext(&data, &header);
        --retries;
        if (result == 0)
            break;
        if (retries == 0)
        {
#ifndef NDEBUG
            fprintf(stderr, "OBL: Movie frame wait exhausted\n");
#endif
            abort();
        }
    }
    native_header = (StHEADER *)header;
    limit = (native_stream != 0 ? native_stream[5] : r_u32(stream + 0x14));
    number = native_header->frameCount;
    if (number >= limit)
        w_u32(0x800CFC68, 1);
    width = native_header->width;
    previous = r_u32(0x800CFBD8);
    changed = width != previous;
    if (changed == 0)
    {
        height = native_header->height;
        previous = r_u32(0x800CFBDC);
        changed = height != previous;
    }
    if (changed != 0)
    {
        mode = (native_stream != 0 ? native_stream[1] : r_u32(stream + 4));
        rectangle.x = 0;
        rectangle.y = 0;
        if (mode == 1)
        {
            width = (native_stream != 0 ? native_stream[2] : r_u32(stream + 8));
            scaled = (width << 1) + width;
            rectangle.w = (sint16)((sint32)(scaled + (scaled >> 31)) >> 1);
        }
        else
            rectangle.w = (sint16)(native_stream != 0 ? (uint16)native_stream[2] : r_u16(stream + 8));
        height = (native_stream != 0 ? native_stream[3] : r_u32(stream + 12));
        rectangle.h = (sint16)(height << 1);
        ClearImage(&rectangle, 0, 0, 0);
        width = native_header->width;
        height = native_header->height;
        w_u32(0x800CFBD8, width);
        w_u32(0x800CFBDC, height);
    }
    mode = (native_stream != 0 ? native_stream[1] : r_u32(stream + 4));
    if (mode == 1)
    {
        width = r_u32(0x800CFBD8);
        scaled = (width << 1) + width;
        width = (scaled + (scaled >> 31)) >> 1;
    }
    else
        width = r_u16(0x800CFBD8);
    w_u16(frame + 0x24, (uint16)width);
    w_u16(frame + 0x1C, (uint16)width);
    height = r_u16(0x800CFBDC);
    w_u16(frame + 0x26, (uint16)height);
    w_u16(frame + 0x1E, (uint16)height);
    w_u16(frame + 0x32, (uint16)height);
    return data;
}

uint32 *func_80031390(uint32 frame, uint32 stream)
{
    FUNCTION_MARKER(0x80031390, "SLUS_004.64");
    return movie_next_frame_core(frame, stream, 0);
}

void func_80031070(void)
{
    uint32 previous_buffer, selected, packed_xy, packed_wh, offset, x, width, pixels, product;
    sint32 numerator, denominator, remainder, quotient, left, right, current, height, adjusted, groups;
    PSX_RECT rectangle;
    FUNCTION_MARKER(0x80031070, "SLUS_004.64");
    if (r_u32(0x800DF03C) != 0)
    {
        StCdInterrupt();
        w_u32(0x800DF03C, 0);
    }
    previous_buffer = r_u32(0x800CFFD8);
    selected = r_u32(0x800CFFD8);
    r_u32(0x800CFFF0);
    packed_xy = r_u32(0x800CFFF0);
    r_u32(0x800CFFF4);
    packed_wh = r_u32(0x800CFFF4);
    rectangle.x = (sint16)packed_xy;
    rectangle.y = (sint16)(packed_xy >> 16);
    rectangle.w = (sint16)packed_wh;
    rectangle.h = (sint16)(packed_wh >> 16);
    w_u32(0x800CFFD8, selected == 0 ? 1 : 0);
    remainder = 0;
    if (r_u32(0x800CFC60) != 0)
    {
        selected = r_u32(0x800CFFEC);
        denominator = r_s16(0x800CFFF4);
        numerator = r_s16(0x800CFFE0 + (selected << 3));
        quotient = geometry_divide((uint32)numerator, (uint32)denominator);
        remainder = numerator - quotient * denominator;
    }
    if (remainder != 0)
    {
        x = r_u16(0x800CFFF0);
        w_u32(0x800CFC60, 0);
        w_u16(0x800CFFF0, (uint16)(x + (uint32)remainder));
    }
    else
    {
        x = r_u16(0x800CFFF0);
        width = r_u16(0x800CFFF4);
        w_u16(0x800CFFF0, (uint16)(x + width));
    }
    selected = r_u32(0x800CFFEC);
    offset = selected << 3;
    left = r_s16(0x800CFFDC + offset);
    right = r_s16(0x800CFFE0 + offset);
    current = r_s16(0x800CFFF0);
    if (current < left + right)
    {
        height = r_s16(0x800CFFF6);
        selected = r_u32(0x800CFFD8);
        width = (uint32)r_s16(0x800CFFF4);
        adjusted = height - 1;
        if (adjusted < 0)
            adjusted = height + 14;
        groups = (adjusted >> 4) + 1;
        product = (width << 4) * (uint32)groups;
        pixels = r_u32(0x800CFFD0 + (selected << 2));
        func_8004267c(pixels, (sint32)product >> 1);
    }
    else
    {
        w_u32(0x800CFFF8, 1);
        w_u32(0x800CFC60, 1);
        w_u32(0x800CFFEC, selected == 0 ? 1 : 0);
        selected = r_u32(0x800CFFEC);
        offset = selected << 3;
        x = r_u16(0x800CFFDC + offset);
        w_u16(0x800CFFF0, (uint16)x);
        x = r_u16(0x800CFFDE + offset);
        w_u16(0x800CFFF2, (uint16)x);
    }
    pixels = r_u32(0x800CFFD0 + (previous_buffer << 2));
    func_800443d4(&rectangle, pixels);
}

static void movie_start_core(uint8 *location, uint32 stream, const uint32 *native_stream, void (*callback)(void))
{
    uint32 ring, mode, start;
    DecDCTReset(0);
    DecDCToutCallback(callback);
    ring = (native_stream != 0 ? native_stream[10] : r_u32(stream + 0x28));
    StSetRing((uint32 *)psx_addr(ring, 32 * 2048), 32);
    mode = (native_stream != 0 ? native_stream[1] : r_u32(stream + 4));
    start = (native_stream != 0 ? native_stream[4] : r_u32(stream + 0x10));
    StSetStream(mode, start, 0xFFFFFFFF, 0, 0);
    start_stream_location(location);
    start = (native_stream != 0 ? native_stream[4] : r_u32(stream + 0x10));
    func_8006d5cc(0, start, 0xFFFFFFFF);
}

void func_80030fec(uint8 *location, uint32 stream, void (*callback)(void))
{
    FUNCTION_MARKER(0x80030FEC, "SLUS_004.64");
    movie_start_core(location, stream, 0, callback);
}

void start_movie(uint8 *location, const uint32 *stream, void (*callback)(void))
{
    movie_start_core(location, 0, stream, callback);
}

sint32 func_80030b9c(uint32 *descriptor)
{
    PSX_RECT clear_rectangle;
    DISPENV display;
    CdlFILE file;
    uint32 held, mode, selected, pixels, product, viewport, input;
    sint32 height, width, adjusted, groups, result;
    FUNCTION_MARKER(0x80030B9C, "SLUS_004.64");
    w_u32(0x800CFC60, 1);
    SetDispMask(0);
    clear_rectangle.x = 0;
    clear_rectangle.y = 0;
    clear_rectangle.w = 640;
    clear_rectangle.h = 512;
    ClearImage(&clear_rectangle, 0, 0, 0);
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, 64, 64);
    while (find_movie_resource(&file, descriptor[0]) == 0)
    {
    }
    init_movie_frame(0x800CFFC4, descriptor);
    start_movie((uint8 *)&file.pos, descriptor, func_80031070);
    prepare_movie_frame(0x800CFFC4, descriptor);
    w_u32(0x800CFC68, 0);
    held = 1;
    for (;;)
    {
        mode = descriptor[1];
        selected = r_u32(0x800CFFCC);
        pixels = r_u32(0x800CFFC4 + (selected << 2));
        func_80042600(pixels, mode == 1 ? 3 : 2);
        height = r_s16(0x800CFFF6);
        selected = r_u32(0x800CFFD8);
        width = r_s16(0x800CFFF4);
        adjusted = height - 1;
        if (adjusted < 0)
            adjusted = height + 14;
        groups = (adjusted >> 4) + 1;
        product = ((uint32)width << 4) * (uint32)groups;
        pixels = r_u32(0x800CFFD0 + (selected << 2));
        func_8004267c(pixels, (sint32)product >> 1);
        prepare_movie_frame(0x800CFFC4, descriptor);
        func_8003151c(0x800CFFC4);
        VSync(4);
        viewport = r_u32(0x800CFFEC);
        mode = descriptor[1];
        if (mode == 1)
        {
            SetDefDispEnv(&display, 0, viewport == 0 ? 240 : 0, 480, 240);
            width = display.disp.w;
            width = (width * 2) / 3;
            display.isrgb24 = 1;
            display.disp.w = (sint16)width;
        }
        else
        {
            SetDefDispEnv(&display, 0, viewport == 0 ? 240 : 0, 320, 240);
            display.isrgb24 = 0;
        }
        PutDispEnv(&display);
        SetDispMask(1);
        if (r_u32(0x800CFC68) == 1)
        {
            result = 1;
            break;
        }
        mode = descriptor[15];
        if (PadRead(0) & (PADRdown | PADstart))
        {
            result = 2;
            break;
        }
        if (mode - 1 < 2)
        {
            input = PadRead(1);
            if ((input & 0x800) != 0)
            {
                input = PadRead(1);
                if ((input & 0x20) != 0)
                {
                    result = 2;
                    break;
                }
            }
            mode = descriptor[15];
            if (mode == 2)
            {
                input = PadRead(1);
                if ((input & 0x800) != 0)
                {
                    input = PadRead(1);
                    if ((input & 0x100) != 0)
                    {
                        w_u32(0x800CF8DC, 100);
                        result = 2;
                        break;
                    }
                }
            }
            continue;
        }
        if (mode == 0 && PadRead(1) != 0)
        {
            if (held == 0)
            {
                result = 2;
                break;
            }
            continue;
        }
        held = 0;
    }
    func_8006d5cc(1, 0, 0);
    DecDCToutCallback(0);
    func_8006bed8();
    SsSetSerialAttr(0, 0, 0);
    SsSetSerialVol(0, 0, 0);
    while (CdControlB(9, 0, 0) == 0)
    {
    }
    func_8004df4c(0, 0, 0, 240);
    return result;
}

uint32 func_800414cc(void)
{
    uint32 page;
    FUNCTION_MARKER(0x800414CC, "SLUS_004.64");
    w_u32(0x800D024C, 0x0A000000);
    page = GetTPage(2, 0, 0, 0);
    w_u16(0x800D0258, (uint16)page);
    w_u8(0x800D025A, 0);
    w_u8(0x800D025B, 240);
    w_u16(0x800D0254, 256);
    w_u16(0x800D0256, 16);
    w_u16(0x800D0250, (uint16)-160);
    w_u16(0x800D0252, (uint16)-120);
    w_u32(0x800D0270, 0x0A000000);
    page = GetTPage(2, 0, 256, 0);
    w_u16(0x800D027C, (uint16)page);
    w_u8(0x800D027E, 0);
    w_u8(0x800D027F, 240);
    w_u16(0x800D0278, 64);
    w_u16(0x800D027A, 16);
    w_u16(0x800D0274, 96);
    w_u16(0x800D0276, (uint16)-120);
    w_u32(0x800D0294, 0x0A000000);
    page = GetTPage(2, 0, 0, 256);
    w_u16(0x800D02A0, (uint16)page);
    w_u8(0x800D02A2, 0);
    w_u8(0x800D02A3, 0);
    w_u16(0x800D029C, 256);
    w_u16(0x800D029E, 224);
    w_u16(0x800D0298, (uint16)-160);
    w_u16(0x800D029A, (uint16)-104);
    w_u32(0x800D02B8, 0x0A000000);
    page = GetTPage(2, 0, 256, 256);
    w_u16(0x800D02C4, (uint16)page);
    w_u8(0x800D02C6, 0);
    w_u8(0x800D02C7, 0);
    w_u16(0x800D02C0, 64);
    w_u16(0x800D02C2, 224);
    w_u16(0x800D02BC, 96);
    w_u16(0x800D02BE, (uint16)-104);
    return page;
}

void func_80040f0c(uint32 start, uint32 end, uint32 mode)
{
    uint32 index, offset, step;
    FUNCTION_MARKER(0x80040F0C, "SLUS_004.64");
    VSync(0);
    for (index = 0; index < 2; ++index)
    {
        offset = 20 * index;
        w_u32(0x800D0204 + offset, 2);
        w_u32(0x800D0210 + offset, 0);
        w_u32(0x800D020C + offset, 0);
        w_u32(0x800D0208 + offset, 0x800D022C + 16 * index);
        w_u32(0x800D0214 + offset, 0x800D0238 + 16 * index);
    }
    func_800414cc();
    w_u32(0x800CFD48, 0);
    ResetGraph(1);
    func_8004df4c(0, 0, 0, 0);
    GsSwapDispBuff();
    if (start == 0 || end == 0)
    {
        w_u32(0x800CFD60, start);
        w_u32(0x800CFD68, end);
        w_u32(0x800CFD58, start);
        step = (sint32)end < (sint32)start ? 0 - mode : mode;
        w_u32(0x800CFD70, step);
        func_80041444(r_u32(0x800CFD60));
        w_u32(0x800CFC5C, 1);
    }
    else if (start == 255 || end == 255)
    {
        if (start == 255)
        {
            w_u32(0x800CFD60, 255);
            w_u32(0x800CFD68, 0);
            w_u32(0x800CFD58, 255);
            step = 0 - (mode << 1);
        }
        else
        {
            w_u32(0x800CFD60, 0);
            w_u32(0x800CFD68, end);
            w_u32(0x800CFD58, 0);
            step = mode << 1;
        }
        w_u32(0x800CFD70, step);
        func_80041444(128);
        w_u32(0x800D02DC, 0x50000000);
        w_u16(0x800D02E0, (uint16)-160);
        w_u16(0x800D02E2, (uint16)-120);
        w_u16(0x800D02E4, 320);
        w_u16(0x800D02E6, 240);
        w_u32(0x800CFC5C, 3);
    }
    VSync(0);
}

uint32 func_80040684(uint32 device, uint8 *entries)
{
    char pattern[24];
    DIRENTRY entry;
    uint32 packed, size, count;
    uint16 suffix;
    uint8 *destination;
    FUNCTION_MARKER(0x80040684, "SLUS_004.64");
    if (device == 0)
    {
        packed = r_u32(0x800CFC3C);
        suffix = (uint16)r_s16(0x800CFC40);
    }
    else if (device == 1)
    {
        packed = r_u32(0x800CFC44);
        suffix = (uint16)r_s16(0x800CFC48);
    }
    else
        return 1;
    memcpy(pattern, &packed, 4);
    memcpy(pattern + 4, &suffix, 2);
    count = 0;
    if (func_80041770(pattern, &entry) == &entry)
    {
        destination = entries;
        do
        {
            strcpy((char *)destination, entry.name);
            size = (uint32)entry.size;
            ++count;
            memcpy(destination + 20, &size, 4);
            destination += 24;
        }
        while (nextfile(&entry) == &entry);
    }
    return count;
}

uint32 func_8003e8e0(uint32 device, uint8 *const *entries, uint32 *counts, uint32 *slots, uint32 *work)
{
    uint32 count, result;
    FUNCTION_MARKER(0x8003E8E0, "SLUS_004.64");
    count = func_80040684(device, entries[device]);
    counts[device] = count;
    result = func_8003e2a0(entries[device], (sint32)count, slots);
    func_8003f0c0(device, slots, work);
    return result;
}

uint32 func_80040590(uint32 device_path, uint32 work)
{
    uint32 status, input;
    FUNCTION_MARKER(0x80040590, "SLUS_004.64");
    status = func_80041700(device_path);
    func_80040500(status == 1 ? 5 : 6, 0, work);
    do
    {
        GsSortFastSprite(psx_addr(0x800D7AE4, 36), psx_addr(0x800D003C + 20 * r_u32(0x800CFD38), 20), 0);
        func_8003d450();
        input = func_8003d034();
    }
    while (input != 6);
    return input;
}

sint32 func_80018c40(void)
{
    uint32 source, destination, pass, block, word, count, unaligned, source_shift, destination_shift;
    uint32 address, high, low, old, words[4];
    sint32 music;
    FUNCTION_MARKER(0x80018C40, "SLUS_004.64");
    func_8003943c(0);
    if (func_8003db7c(1, 0x800EDFA8, r_u32(0x800CF9FC), 0x80082164, 0x800972E4) != 1)
        return 0;
    func_8003943c(0);
    for (pass = 0; pass < 2; ++pass)
    {
        if (pass == 0)
        {
            destination = r_u32(0x800CF9FC);
            source = 0x800EDFA8;
        }
        else
        {
            source = r_u32(0x800CF9FC);
            destination = 0x800EDFA8;
        }
        unaligned = (source | destination) & 3;
        source_shift = (source & 3) << 3;
        destination_shift = (destination & 3) << 3;
        for (block = 0; block < 352; ++block)
        {
            count = block == 351 ? 3 : 4;
            for (word = 0; word < count; ++word)
            {
                address = source + (word << 2);
                if (unaligned != 0 || block == 351)
                {
                    high = r_u32((address + 3) & 0xFFFFFFFC);
                    low = r_u32(address & 0xFFFFFFFC);
                    words[word] = source_shift != 0 ? (low >> source_shift) | (high << (32 - source_shift)) : low;
                }
                else
                    words[word] = r_u32(address);
            }
            for (word = 0; word < count; ++word)
            {
                address = destination + (word << 2);
                if (unaligned != 0 || block == 351)
                {
                    if (destination_shift != 0)
                    {
                        old = r_u32((address + 3) & 0xFFFFFFFC);
                        high = (old & (0xFFFFFFFF << destination_shift)) | (words[word] >> (32 - destination_shift));
                        w_u32((address + 3) & 0xFFFFFFFC, high);
                        old = r_u32(address & 0xFFFFFFFC);
                        low = (old & (0xFFFFFFFF >> (32 - destination_shift))) | (words[word] << destination_shift);
                        w_u32(address & 0xFFFFFFFC, low);
                    }
                    else
                    {
                        w_u32(address, words[word]);
                        w_u32(address, words[word]);
                    }
                }
                else
                    w_u32(address, words[word]);
            }
            source += 16;
            destination += 16;
        }
        if (pass == 0)
            func_800162b0();
        else
            func_800186b4();
    }
    music = r_s32(0x800EDFB8);
    w_u32(0x800CF8B4, 0);
    if (music > 0)
    {
        if (music < 101)
            func_800178b0(music, 0);
        else
            func_80017aa0((sint32)(r_u32(0x800EDFB8) - 100), 0);
    }
    return 1;
}

void func_80018ad4(void)
{
    uint32 blocked, actor, music;
    FUNCTION_MARKER(0x80018AD4, "SLUS_004.64");
    if (r_u32(0x800CF910) == 0)
        return;
    blocked = 1;
    if (r_u32(0x800CF878) != 0 && r_u32(0x800CF8E4) == 0 && r_u32(0x800CF844) == 0)
    {
        actor = r_u32(0x800EE7EC);
        blocked = r_s32(0x800E9A58 + (actor << 2)) > 0;
    }
    if (blocked != 0)
    {
        func_8001f87c();
        func_8001f8a0(1007, 0, 60);
        func_8001f92c();
        func_8002372c(2);
        return;
    }
    func_80032d68(r_u32(0x800CFA6C), 9);
    music = r_u32(0x800CF8B4);
    w_u32(0x800EDFB8, music);
    func_80017a74();
    VSync(2);
    func_80018284();
    func_8001eff8();
    func_8003db7c(0, 0x800EDFA8, r_u32(0x800CF9FC), 0x80082164, 0x800972E4);
    r_u32(0x800EE7E4);
    func_80022a68();
    func_8001afcc();
    func_80015064();
    func_8001f13c();
    music = r_u32(0x800EDFB8);
    if ((sint32)music > 0)
    {
        if ((sint32)music < 101)
            func_800178b0((sint32)music, 0);
        else
            func_80017aa0((sint32)(r_u32(0x800EDFB8) - 100), 0);
    }
}

void func_80037934(const char *message, sint32 x, sint32 y, sint32 width, sint32 height)
{
    sint32 stream;
    uint32 index;
    FUNCTION_MARKER(0x80037934, "SLUS_004.64");
    stream = FntOpen(x, y, width, height, 0, 256);
    SetDumpFnt(stream);
    for (index = 0; index < 2; ++index)
    {
        GsSwapDispBuff();
        FntPrint(message);
        FntFlush(-1);
        DrawSync(0);
    }
    stream = FntOpen(-144, -104, 320, 200, 0, 512);
    SetDumpFnt(stream);
}
