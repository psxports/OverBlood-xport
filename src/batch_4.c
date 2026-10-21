#include "functions.h"
#include <string.h>

/* Full original bodies, pending final integration and runtime validation */
uint32 func_800238bc(uint32 object, uint32 x, uint32 y, uint32 z, uint32 *output_x, uint32 *output_y, uint32 *output_z)
{
    uint32 actor;
    uint32 coordinate;
    uint32 rotation_x;
    uint32 rotation_y;
    uint32 rotation_z;
    uint32 value;
    VECTOR rotated;
    FUNCTION_MARKER(0x800238BC, "SLUS_004.64");
    actor = 0x800DDD44 + object * 16;
    coordinate = r_u32(actor + 4);
    coordinate = r_u32(coordinate + 0x44);
    rotation_x = r_u16(coordinate + 0x10);
    coordinate = r_u32(actor + 4);
    coordinate = r_u32(coordinate + 0x44);
    rotation_y = r_u16(coordinate + 0x12);
    coordinate = r_u32(actor + 4);
    coordinate = r_u32(coordinate + 0x44);
    rotation_z = r_u16(coordinate + 0x14);
    /* SVECTOR padding is not consumed by the shared rotation APIs */
    func_800366a8((uint16)x | ((uint32)(uint16)y << 16), (uint16)(0 - z),
                  rotation_x | (rotation_y << 16), rotation_z, &rotated);
    coordinate = r_u32(actor + 4);
    value = r_u32(coordinate + 0x18);
    *output_x = (uint32)rotated.vx + value;
    coordinate = r_u32(actor + 4);
    value = r_u32(coordinate + 0x1C);
    *output_y = (uint32)rotated.vy + value;
    coordinate = r_u32(actor + 4);
    value = r_u32(coordinate + 0x20);
    value += (uint32)rotated.vz;
    *output_z = value;
    return value;
}

uint32 func_80025ac4(uint32 object, uint32 action)
{
    uint32 first;
    uint32 second;
    uint32 distance;
    FUNCTION_MARKER(0x80025AC4, "SLUS_004.64");
    if (action - 8 < 2 || action - 6 < 2 || action - 43 < 2 || action - 49 < 2)
    {
        first = object == 1 ? 230 : 170;
        second = first;
        func_80031c20(object, 23, 1, 0, 0, first);
        func_80031b14(object, 24, 1, 0, 0, second);
        func_800319c0(object, 25, 1, 0, 0, 0);
        func_800319c0(object, 0, 1, 0, 0, 0);
        func_80032320(object, 0);
        w_u32(0x800CFE64, 1);
        w_u32(0x800CFE4C, 1);
        w_u32(0x800CFF3C, 1);
        w_u32(0x800F02F0 + object * 4, 0);
        w_u32(0x800F0310 + object * 4, 0);
        distance = first + second;
    }
    else if (action - 2 < 2 || action == 1 || action == 4 || action == 36 ||
             action == 5 || action - 43 < 2 || action - 49 < 2)
    {
        first = object == 1 ? 200 : 140;
        second = object == 1 ? 180 : 120;
        func_80031c20(object, 22, 1, 0, 0, 0);
        func_80031b14(object, 23, 1, 0, 0, first);
        func_800319c0(object, 24, 1, 0, 0, second);
        func_800319c0(object, 25, 1, 0, 0, 0);
        func_800319c0(object, 0, 1, 0, 0, 0);
        func_80032320(object, 0);
        w_u32(0x800CFE4C, 1);
        w_u32(0x800CFE64, 1);
        w_u32(0x800CFF3C, 1);
        w_u32(0x800F02F0 + object * 4, 0);
        w_u32(0x800F0310 + object * 4, 0);
        distance = first + second;
    }
    else
        return 0;
    w_u32(0x800F0330 + object * 4, distance);
    return func_800238bc(object, 0x800F02F0, 0x800F0310, 0x800F0330,
                       (uint32 *)psx_addr(0x800F02F0, 4),
                       (uint32 *)psx_addr(0x800F0310, 4),
                       (uint32 *)psx_addr(0x800F0330, 4));
}

void func_80025dc8(uint32 object, uint32 action)
{
    FUNCTION_MARKER(0x80025DC8, "SLUS_004.64");
    switch (action)
    {
    case 0:
        func_80031c20(object, 1, 1, 0, 0, 90);
        func_80031b14(object, 2, 1, 0, 0, 90);
        goto append_three;
    case 1:
        if (func_8003248c(object) != 0)
            return;
        func_80031b14(object, 2, 1, 0, 0, 90);
        goto append_three;
    case 4:
    case 5:
        func_80031b14(object, 1, 1, 0, 0, 90);
        goto append_two_three;
    case 8:
        func_80031b14(object, 10, 1, 0, 0, 90);
        goto append_two_three;
    case 9:
        func_80031b14(object, 11, 1, 0, 0, 90);
        func_800319c0(object, 3, 1, 0, 0, 90);
        goto append_two;
    case 17:
    case 18:
        func_80031b14(object, action == 17 ? 19 : 20, 1, 0, 0, 0);
        func_800319c0(object, 0, 1, 0, 0, 0);
        func_80032320(object, 0);
        return;
    case 21:
        func_80031b14(object, 0, 1, 0, 0, 0);
        func_800319c0(object, 1, 1, 0, 0, 90);
        goto append_two_three;
    case 32:
    case 34:
        if (r_u32(0x800CFE24) == 0)
        {
            func_80031c20(object, 34, 1, 0, 0, 40);
            func_80032320(object, 34);
        }
        return;
    case 36:
        if (r_u32(0x800CFE24) != 0)
            return;
        func_80031c20(object, 37, 1, 0, 0, 45);
        func_80031b14(object, 3, 1, 0, 0, 90);
        goto append_two;
    case 37:
        if (r_u32(0x800CFE24) != 0 && r_u32(0x800CFB1C) == 0)
            func_80031f28(object, 39, 0);
        return;
    default:
        return;
    }
append_two_three:
    func_800319c0(object, 2, 1, 0, 0, 90);
append_three:
    func_800319c0(object, 3, 1, 0, 0, 90);
    func_80032354(object, 1, 3);
    return;
append_two:
    func_800319c0(object, 2, 1, 0, 0, 90);
    func_80032354(object, 1, 2);
}

void func_80026110(uint32 object, uint32 action)
{
    FUNCTION_MARKER(0x80026110, "SLUS_004.64");
    switch (action)
    {
    case 0:
        func_80031c20(object, 27, 1, 0, 0, 90);
        func_80031b14(object, 8, 1, 0, 0, 230);
        goto append_nine;
    case 1:
    case 3:
        func_80031b14(object, 7, 1, 0, 0, 160);
        func_800319c0(object, 9, 1, 0, 0, 230);
        func_800319c0(object, 8, 1, 0, 0, 230);
        func_80032354(object, 1, 8);
        return;
    case 2:
        func_80031b14(object, 6, 1, 0, 0, 160);
        goto append_eight_nine;
    case 21:
        func_80031b14(object, 27, 1, 0, 0, 90);
        goto append_eight_nine;
    case 32:
    case 34:
        if (r_u32(0x800CFE24) == 0)
        {
            func_80031c20(object, 34, 1, 0, 0, 40);
            func_80032320(object, 34);
        }
        return;
    case 36:
        if (r_u32(0x800CFE24) != 0)
            return;
        func_80031c20(object, 38, 1, 0, 0, 0);
        func_80031b14(object, 27, 1, 0, 0, 160);
        goto append_eight_nine;
    case 37:
        if (r_u32(0x800CFE24) != 0 && r_u32(0x800CFB1C) == 0)
            func_80031f28(object, 39, 0);
        return;
    default:
        return;
    }
append_eight_nine:
    func_800319c0(object, 8, 1, 0, 0, 230);
append_nine:
    func_800319c0(object, 9, 1, 0, 0, 230);
    func_80032354(object, 1, 9);
}

void func_8002635c(uint32 object, uint32 action, uint32 blocked)
{
    FUNCTION_MARKER(0x8002635C, "SLUS_004.64");
    switch (action)
    {
    case 0:
    case 36:
    case 43:
    case 44:
        if (action == 44 && blocked != 0)
            return;
        func_80031c20(object, 44, 1, 0, 0, 90);
        func_80032320(object, 44);
        break;
    case 49:
    case 50:
        if (action == 50 && blocked != 0)
            return;
        func_80031c20(object, 50, 1, 0, 0, 90);
        func_80032320(object, 50);
        break;
    case 32:
    case 34:
        if (r_u32(0x800CFE24) == 0)
        {
            func_80031c20(object, 34, 1, 0, 0, 40);
            func_80032320(object, 34);
        }
        break;
    default:
        break;
    }
}

void func_8002645c(uint32 object, uint32 action, uint32 enabled)
{
    FUNCTION_MARKER(0x8002645C, "SLUS_004.64");
    switch (action)
    {
    case 0:
    case 2:
    case 3:
    case 36:
        func_80031ea4(object, 44);
        break;
    case 44:
        if (enabled != 0)
            func_80031ea4(object, 44);
        break;
    case 50:
        if (enabled != 0)
            func_80031ea4(object, 50);
        break;
    case 34:
        if (r_u32(0x800CFE24) == 0)
            func_80031ea4(object, 32);
        break;
    default:
        break;
    }
}

uint32 func_80031ea4(uint32 object, uint32 action)
{
    FUNCTION_MARKER(0x80031EA4, "SLUS_004.64");
    func_8003213c(object, action);
    return func_80032320(object, action);
}

void func_800264ec(uint32 object, uint32 action, uint32 blocked)
{
    FUNCTION_MARKER(0x800264EC, "SLUS_004.64");
    switch (action)
    {
    case 0:
    case 36:
    case 43:
    case 44:
        if (action == 44 && blocked != 0)
            return;
        func_80031c20(object, 44, 1, 0, 0, 90);
        func_80032320(object, 44);
        break;
    case 49:
    case 50:
        if (action == 50 && blocked != 0)
            return;
        func_80031c20(object, 50, 1, 0, 0, 90);
        func_80032320(object, 50);
        break;
    case 32:
    case 34:
        if (r_u32(0x800CFE24) == 0)
        {
            func_80031c20(object, 34, 1, 0, 0, 40);
            func_80032320(object, 34);
        }
        break;
    default:
        break;
    }
}

void func_800265ec(uint32 enabled)
{
    FUNCTION_MARKER(0x800265EC, "SLUS_004.64");
    if ((enabled & 255) != 0)
    {
        func_800378e8();
        w_u32(0x800CF8DC, 100);
    }
}

uint32 func_80026620(uint32 enabled, uint32 y_offset)
{
    uint32 active;
    uint32 selected;
    uint32 actor;
    uint32 value;
    uint32 index;
    uint32 offset;
    FUNCTION_MARKER(0x80026620, "SLUS_004.64");
    if (enabled == 0)
    {
        w_u32(0x800EE0A8, 0xFFFFFFFF);
        w_u32(0x800EDFF8, 0);
        return 0xFFFFFFFF;
    }
    active = r_u32(0x800EDFF8);
    if (active != 0)
        return active;
    selected = (uint32)(r_s32(0x800EE7EC) / 2) + 1;
    actor = r_u32(0x800DDD48 + selected * 16);
    value = r_u32(actor + 0x1C);
    w_u32(0x800EE004, 0);
    w_u32(0x800EE00C, 0);
    w_u32(0x800EDFFC, y_offset + value);
    w_u32(0x800EE000, 1);
    w_u32(0x800EE008, 1);
    for (index = 0; index < 8; ++index)
    {
        offset = index * 52;
        w_u32(0x800EE0A8 + offset, 1);
        w_u32(0x800EE0B0 + offset, 5);
        w_u32(0x800EE0B4 + offset, 0);
        w_u32(0x800EE0AC + offset, 0);
        actor = r_u32(0x800DDD48 + (index / 2 + 1) * 16);
        value = r_u32(actor + 0x18);
        w_u32(0x800EE0B8 + offset, value);
        value = r_u32(0x800EDFFC);
        w_u32(0x800EE0BC + offset, value + ((index & 1) << 6));
        actor = r_u32(0x800DDD48 + (index / 2 + 1) * 16);
        value = r_u32(actor + 0x20);
        w_u32(0x800EE0C4 + offset, 3072);
        w_u32(0x800EE0CC + offset, 3072);
        w_u32(0x800EE0C8 + offset, 4096);
        w_u32(0x800EE0D0 + offset, 0);
        w_u32(0x800EE0D4 + offset, 0);
        w_u32(0x800EE0D8 + offset, 0);
        w_u32(0x800EE0C0 + offset, value);
    }
    w_u32(0x800EE0A8 + index * 52, 0xFFFFFFFF);
    w_u32(0x800EDFF8, 1);
    return 1;
}

uint32 func_80027034(void)
{
    uint32 direction;
    uint32 selected;
    uint32 actor;
    uint32 target;
    uint32 delta;
    uint32 value;
    uint32 limit;
    uint32 index;
    uint32 offset;
    uint32 z;
    FUNCTION_MARKER(0x80027034, "SLUS_004.64");
    if (r_u32(0x800CF854) == 0)
        return 0xFFFFFFFF;
    direction = r_u32(0x800CFAD4);
    if (direction == 0xFFFFFFFF)
    {
        delta = r_u32(0x800CFAD0);
        value = r_u32(0x800CFAD8);
        delta -= value;
        selected = r_u32(0x800EE7EC);
        actor = r_u32(0x800DDD48 + selected * 16);
        value = r_u32(actor + 0x1C);
        w_u32(actor + 0x1C, value + delta);
        limit = r_u32(0x800CFACC);
        w_u32(0x800CFAD0, delta);
        if ((sint32)delta < (sint32)(0 - limit))
            w_u32(0x800CFAD4, 1);
    }
    else
    {
        selected = r_u32(0x800EE7EC);
        actor = r_u32(0x800DDD48 + selected * 16);
        delta = r_u32(0x800CFAD0);
        value = r_u32(actor + 0x1C);
        delta += 10;
        w_u32(actor + 0x1C, value + delta);
        limit = r_u32(0x800CFACC);
        direction = r_u32(0x800CFAD4);
        limit *= direction;
        w_u32(0x800CFAD0, delta);
        if ((sint32)limit < (sint32)delta)
            w_u32(0x800CFAD4, 0xFFFFFFFF);
    }
    selected = r_u32(0x800EE7EC);
    actor = r_u32(0x800DDD48 + selected * 16);
    target = r_u32(0x800DDE78);
    value = r_u32(actor + 0x18);
    w_u32(target + 0x18, value);
    selected = r_u32(0x800EE7EC);
    actor = r_u32(0x800DDD48 + selected * 16);
    target = r_u32(0x800DDE78);
    value = r_u32(actor + 0x20);
    w_u32(target + 0x20, value);
    for (index = 0; index < 16; ++index)
    {
        offset = index * 52;
        value = r_u32(0x800EE0BC + offset);
        w_u32(0x800EE0BC + offset, value - 90);
        value = r_u32(0x800EE0C0 + offset);
        w_u32(0x800EE0C0 + offset, value - 600);
        value = r_u32(0x800EE0C4 + offset);
        w_u32(0x800EE0C4 + offset, value + 800);
        value = r_u32(0x800EE0C8 + offset);
        w_u32(0x800EE0C8 + offset, value + 800);
        value = r_u32(0x800EE0CC + offset);
        w_u32(0x800EE0CC + offset, value + 256);
        value = r_u32(0x800EE0C4 + offset);
        w_u32(0x800EE0D0 + offset, 0);
        w_u32(0x800EE0D4 + offset, 0);
        w_u32(0x800EE0D8 + offset, 0);
        if ((sint32)value > 32768)
            w_u32(0x800EE0C4 + offset, 32768);
        if (r_s32(0x800EE0C8 + offset) > 32768)
            w_u32(0x800EE0C8 + offset, 32768);
        selected = r_u32(0x800EE7EC);
        actor = r_u32(0x800DDD48 + selected * 16);
        limit = r_u32(actor + 0x20);
        z = r_u32(0x800EE0C0 + offset);
        if ((sint32)z < (sint32)(limit - 16000))
        {
            value = r_u32(actor + 0x18);
            w_u32(0x800EE0B8 + offset, value);
            w_u32(0x800EE0BC + offset, 3700);
            value = r_u32(0x800EE0C0 + offset);
            w_u32(0x800EE0C8 + offset, 8192);
            w_u32(0x800EE0CC + offset, 8192);
            w_u32(0x800EE0C0 + offset, value + 18000);
            w_u32(0x800EE0C4 + offset, 16384);
        }
    }
    return 32;
}

uint32 func_800273f4(void)
{
    FUNCTION_MARKER(0x800273F4, "SLUS_004.64");
    w_u32(0x800EE0A8, 0xFFFFFFFF);
    return 0xFFFFFFFF;
}

void func_80027408(uint32 mode, uint32 object)
{
    uint32 actor;
    uint32 coordinate;
    uint32 rotation;
    uint32 action;
    uint32 saved_z;
    uint32 shift;
    uint32 input;
    uint32 mask;
    uint32 value;
    uint32 other;
    uint32 limit;
    uint32 selected;
    uint32 moved;
    uint32 hit;
    sint32 angle;
    FUNCTION_MARKER(0x80027408, "SLUS_004.64");
    (void)r_u32(0x800109D0);
    (void)r_u32(0x800109D4);
    (void)r_u32(0x800109D8);
    w_u32(0x800CFB1C, 0);
    actor = 0x800DDD44 + object * 16;
    action = func_80031954(object);
    coordinate = r_u32(actor + 4);
    mask = r_u32(0x800CF870);
    saved_z = r_u32(coordinate + 0x20);
    moved = 0;
    shift = (mode << 4) & 31;
    if (mask != 0)
    {
        input = r_u32(0x800CF934);
        if (((mask << shift) & input) != 0)
            return;
        w_u32(0x800CF870, 0);
    }
    input = r_u32(0x800CF934);
    if ((((uint32)2048 << shift) & input) != 0 && (((uint32)32 << shift) & input) != 0)
        func_800265ec(0);
    input = r_u32(0x800CF934);
    if ((((uint32)4 << shift) & input) != 0)
    {
        func_8002372c(1);
        func_80014ef8(1);
        mask = r_u32(0x800CF870);
        w_u32(0x800CF870, mask | 4);
    }
    if (r_u32(0x800CF7A4) != 0)
        func_800252ec();
    input = r_u32(0x800CF934);
    if ((((uint32)1 << shift) & input) != 0)
    {
        if ((((uint32)16384 << shift) & input) != 0)
        {
            if (r_u32(0x800EDFD8) == 2)
            {
                value = r_u32(0x800CF848);
                if ((sint32)value >= -447)
                    w_u32(0x800CF848, value - 32);
            }
            if (r_u32(0x800EDFD8) == 1)
            {
                value = r_u32(0x800CF9D4);
                other = r_u32(0x800CF9D8);
                value += other;
                limit = r_u32(0x800EDFE4);
                w_u32(0x800CF9D4, value);
                if ((sint32)limit < (sint32)value)
                    w_u32(0x800CF9D4, limit);
                coordinate = r_u32(actor + 4);
                other = r_u32(0x800CF9D0);
                value = r_u32(coordinate + 0x1C);
                value += other;
                other = r_u32(0x800CF9D4);
                w_u32(0x800EF5F0, value + other);
            }
        }
        input = r_u32(0x800CF934);
        if ((((uint32)1 << shift) & input) != 0 && (((uint32)4096 << shift) & input) != 0)
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
                other = r_u32(0x800CF9D8);
                value -= other;
                limit = r_u32(0x800EDFE8);
                w_u32(0x800CF9D4, value);
                if ((sint32)value < (sint32)limit)
                    w_u32(0x800CF9D4, limit);
                coordinate = r_u32(actor + 4);
                other = r_u32(0x800CF9D0);
                value = r_u32(coordinate + 0x1C);
                value += other;
                other = r_u32(0x800CF9D4);
                w_u32(0x800EF5F0, value + other);
            }
        }
    }
    input = r_u32(0x800CF934);
    if ((((uint32)32768 << shift) & input) != 0)
    {
        coordinate = r_u32(actor + 4);
        value = r_u32(coordinate + 0x18);
        w_u32(coordinate + 0x18, value - 400);
        rotation = r_u32(r_u32(actor + 4) + 0x44);
        value = r_u16(rotation + 0x12);
        w_u16(rotation + 0x12, value - 20);
        rotation = r_u32(r_u32(actor + 4) + 0x44);
        value = r_u16(rotation + 0x14);
        w_u16(rotation + 0x14, value - 20);
        coordinate = r_u32(actor + 4);
        moved = 1;
        w_u32(coordinate, 0);
    }
    input = r_u32(0x800CF934);
    if ((((uint32)8192 << shift) & input) != 0)
    {
        coordinate = r_u32(actor + 4);
        value = r_u32(coordinate + 0x18);
        w_u32(coordinate + 0x18, value + 400);
        rotation = r_u32(r_u32(actor + 4) + 0x44);
        value = r_u16(rotation + 0x12);
        w_u16(rotation + 0x12, value + 20);
        rotation = r_u32(r_u32(actor + 4) + 0x44);
        value = r_u16(rotation + 0x14);
        w_u16(rotation + 0x14, value + 20);
        coordinate = r_u32(actor + 4);
        moved = 1;
        w_u32(coordinate, 0);
    }
    if (moved == 0)
    {
        rotation = r_u32(r_u32(actor + 4) + 0x44);
        angle = r_s16(rotation + 0x12);
        if (angle >= 2057)
        {
            w_u16(rotation + 0x12, (uint32)angle - 20);
            coordinate = r_u32(actor + 4);
            w_u32(coordinate, 0);
        }
        else
        {
            rotation = r_u32(r_u32(actor + 4) + 0x44);
            angle = r_s16(rotation + 0x12);
            if (angle < 2040)
            {
                w_u16(rotation + 0x12, (uint32)angle + 20);
                coordinate = r_u32(actor + 4);
                w_u32(coordinate, 0);
            }
        }
        rotation = r_u32(r_u32(actor + 4) + 0x44);
        value = r_u16(rotation + 0x14);
        w_u16(rotation + 0x14, value - (uint32)((sint32)(sint16)value >> 3));
    }
    rotation = r_u32(r_u32(actor + 4) + 0x44);
    value = r_u16(rotation + 0x10);
    if (value != 0)
        w_u16(rotation + 0x10, value - (uint32)((sint32)(sint16)value >> 3));
    input = r_u32(0x800CF934);
    if ((((uint32)16384 << shift) & input) != 0)
    {
        coordinate = r_u32(actor + 4);
        value = r_u32(coordinate + 0x20);
        w_u32(coordinate + 0x20, value - 400);
    }
    input = r_u32(0x800CF934);
    if ((((uint32)4096 << shift) & input) != 0)
    {
        coordinate = r_u32(actor + 4);
        value = r_u32(coordinate + 0x20);
        w_u32(coordinate + 0x20, value + 400);
    }
    input = r_u32(0x800CF934);
    if ((((uint32)128 << shift) & input) != 0 && r_u32(0x800CFADC) == 0 && r_u32(0x800CFAF0) == 0)
    {
        w_u32(0x800CFADC, 1);
        w_u32(0x800CFAE0, 400);
        w_u32(0x800CFAE8, 30);
        w_u32(0x800CFAE4, 400);
        w_u32(0x800CFAEC, 0xFFFFFE0C);
        w_u32(0x800CFAF0, 0);
        func_8002372c(49);
        w_u32(0x800CF908, 2);
    }
    coordinate = r_u32(actor + 4);
    limit = r_u32(0x800CF828);
    value = r_u32(coordinate + 0x18);
    other = r_u32(coordinate + 0x20);
    if (func_8002a5d0(value, other, object, object + limit - 1) == 1)
    {
        coordinate = r_u32(actor + 4);
        w_u32(coordinate + 0x20, saved_z);
        coordinate = r_u32(actor + 4);
        w_u32(coordinate, 0);
    }
    value = r_u32(0x800CFAF0);
    if (value != 0)
    {
        --value;
        w_u32(0x800CFAF0, value);
        if (value == 0)
            func_8002372c(20);
    }
    if (r_u32(0x800CFADC) != 0)
    {
        selected = r_u32(0x800EE7EC);
        coordinate = r_u32(0x800DDD48 + selected * 16);
        other = r_u32(0x800CFAE4);
        value = r_u32(coordinate + 0x1C);
        w_u32(coordinate + 0x1C, value - other);
        value = r_u32(0x800CFAE8);
        other -= value;
        selected = r_u32(0x800EE7EC);
        coordinate = r_u32(0x800DDD48 + selected * 16);
        limit = r_u32(0x800CFAEC);
        value = r_u32(coordinate + 0x1C);
        w_u32(0x800CFAE4, other);
        if ((sint32)limit < (sint32)value && (sint32)other < 0)
        {
            coordinate = r_u32(0x800DDD48 + selected * 16);
            w_u32(0x800CFADC, 0);
            w_u32(0x800CF908, 0);
            w_u32(coordinate + 0x1C, limit);
            w_u32(0x800CFAF0, 30);
        }
    }
    selected = r_u32(0x800EE7EC);
    hit = func_8001d480(selected, 0);
    if (hit == 10 && r_u32(0x800CFADC) == 0)
    {
        rotation = r_u32(r_u32(actor + 4) + 0x44);
        w_u16(rotation + 0x10, 512);
        w_u32(0x800CFADC, 1);
        w_u32(0x800CFAE0, 400);
        w_u32(0x800CFAE8, 50);
        w_u32(0x800CFAE4, 400);
        w_u32(0x800CFAEC, 0xFFFFFE0C);
        w_u32(0x800CF908, 2);
        func_8002372c(57);
        selected = r_u32(0x800CFA6C);
        func_80032d68(selected, 10);
    }
    if (hit == 11 || hit == 12)
    {
        selected = r_u32(0x800EE7EC);
        coordinate = r_u32(0x800DDD48 + selected * 16);
        value = r_u32(coordinate + 0x18);
        w_u32(coordinate + 0x18, hit == 11 ? value - 1000 : value + 1000);
        rotation = r_u32(r_u32(actor + 4) + 0x44);
        w_u16(rotation + 0x12, 2048);
        rotation = r_u32(r_u32(actor + 4) + 0x44);
        w_u16(rotation + 0x14, 0);
        func_8002372c(57);
        selected = r_u32(0x800CFA6C);
        func_80032d68(selected, hit);
    }
    if (hit == 13)
    {
        value = r_u32(0x800CFAE8);
        w_u32(0x800CFAE8, value << 2);
        rotation = r_u32(r_u32(actor + 4) + 0x44);
        w_u16(rotation + 0x10, 800);
        rotation = r_u32(r_u32(actor + 4) + 0x44);
        w_u16(rotation + 0x12, 2048);
        rotation = r_u32(r_u32(actor + 4) + 0x44);
        w_u16(rotation + 0x14, 0);
        func_8002372c(57);
        selected = r_u32(0x800CFA6C);
        w_u32(0x800CF908, 2);
        func_80032d68(selected, 13);
    }
    if (action != 31)
    {
        selected = r_u32(0x800EE7EC);
        func_80031c20(selected, 31, 1, 0, 0, 0);
        selected = r_u32(0x800EE7EC);
        func_80032320(selected, 31);
        func_80031c20(2, 31, 1, 0, 0, 0);
        func_80032320(2, 31);
    }
    func_8001b21c(actor);
}

void func_80014ef8(uint32 advance)
{
    uint32 result;
    uint32 mode;
    FUNCTION_MARKER(0x80014EF8, "SLUS_004.64");
    result = func_80014f38(advance);
    if (result == 1)
    {
        mode = r_u32(0x800EDFD8);
        w_u32(0x800EE7F4, mode);
    }
}

uint32 func_80014f38(uint32 advance)
{
    uint32 previous;
    uint32 limit;
    uint32 mode;
    FUNCTION_MARKER(0x80014F38, "SLUS_004.64");
    previous = r_u32(0x800EDFD8);
    if (advance != 0)
    {
        limit = r_u32(0x800CF930);
        do
        {
            mode = r_u32(0x800EDFD8) + 1;
            w_u32(0x800EDFD8, mode);
            if ((sint32)limit < (sint32)mode)
                w_u32(0x800EDFD8, 0);
            mode = r_u32(0x800EDFD8);
        }
        while (r_u32(0x800EE014 + mode * 4) == 0);
    }
    mode = r_u32(0x800EDFD8);
    if (previous == mode)
    {
        func_8001f87c();
        func_8001f8a0(1025, 0, 60);
        func_8001f92c();
        return 0;
    }
    func_80015100();
    return 1;
}

void func_800252ec(void)
{
    uint32 input;
    uint32 mask;
    uint32 selection;
    uint32 value;
    FUNCTION_MARKER(0x800252EC, "SLUS_004.64");
    input = r_u32(0x800CF934);
    if ((input & 2) != 0 && (input & 32) != 0)
    {
        func_80017d0c(&selection, &value);
        return;
    }
    input = r_u32(0x800CF934);
    if ((input & 2) != 0 && (input & 128) != 0)
    {
        mask = r_u32(0x800CF870);
        w_u32(0x800CF870, mask | 128);
        func_8001f854();
    }
}

uint32 func_8001f854(void)
{
    uint32 cursor;
    uint32 limit;
    uint32 result;
    FUNCTION_MARKER(0x8001F854, "SLUS_004.64");
    cursor = r_u32(0x800CFA70);
    limit = r_u32(0x800CFA74);
    ++cursor;
    w_u32(0x800CFA70, cursor);
    result = (sint32)cursor < (sint32)limit;
    if (result == 0)
        w_u32(0x800CFA70, 0);
    return result;
}

uint32 func_80023fd8(uint32 object, uint32 enabled)
{
    uint32 index;
    uint32 shift;
    uint32 offset;
    uint32 value;
    FUNCTION_MARKER(0x80023FD8, "SLUS_004.64");
    index = r_u32(0x800CF828);
    shift = r_u32(0x800CF908);
    offset = (object + index - 1) * 44;
    w_u32(0x8007F08C + offset, (uint32)1 << (shift & 31));
    value = r_u32(0x80081978 + object * 4);
    w_u32(0x8007F088 + offset, enabled & value);
    return value;
}

uint32 func_80025374(void)
{
    uint32 result;
    uint32 selected;
    FUNCTION_MARKER(0x80025374, "SLUS_004.64");
    result = r_u32(0x800CF7A0);
    if (result != 0)
        return result;
    result = r_u32(0x800CFE24);
    if (result != 0)
        return result;
    selected = r_u32(0x800EE7EC);
    result = r_u32(0x800E9A58 + selected * 4);
    if (result != 0)
        return result;
    result = r_u32(0x800CF910);
    if (result != 0)
    {
        func_80016bf8();
        result = r_u32(0x800CF870) | 8;
        w_u32(0x800CF870, result);
    }
    return result;
}

uint32 func_8002540c(void)
{
    uint32 selected;
    uint32 result;
    FUNCTION_MARKER(0x8002540C, "SLUS_004.64");
    selected = r_u32(0x800EE7EC);
    result = r_u32(0x800E9A58 + selected * 4);
    if (result != 0)
        return result;
    result = r_u32(0x800CF910);
    if (result == 0)
        return result;
    if (func_8002e4b4() > 0)
    {
        func_8002372c(3);
        func_8001f87c();
        func_8001f940();
        return func_8002de0c();
    }
    func_8001f87c();
    func_8001f8a0(1018, 0, 60);
    return func_8001f92c();
}

void func_8002839c(uint32 mode, uint32 object)
{
    uint32 action;
    uint32 x;
    uint32 y;
    uint32 z;
    FUNCTION_MARKER(0x8002839C, "SLUS_004.64");
    (void)mode;
    action = func_80031954(object);
    z = r_u32(0x800CFED4);
    x = r_u32(0x800CFEBC);
    y = r_u32(0x800CFEC4);
    func_80019e24(object, 1, x, y, z, action);
    w_u32(0x800CFEBC, 0);
    w_u32(0x800CFEC4, 0);
    w_u32(0x800CFED4, 0);
}

sint32 func_8002e4b4(void)
{
    uint32 previous;
    uint32 coordinate;
    uint32 index;
    uint32 value;
    FUNCTION_MARKER(0x8002E4B4, "SLUS_004.64");
    previous = r_u32(0x800CFB7C);
    coordinate = r_u32(0x800DDD98);
    w_u32(coordinate, 0);
    for (index = 0; index < 50; ++index)
    {
        value = r_u32(0x800EF4D8 + index * 4);
        if (value != 0)
        {
            w_u32(0x800CFB80, previous);
            w_u32(0x800CF91C, 0);
            return (sint32)value;
        }
    }
    return 0;
}

void func_8001f940(void)
{
    FUNCTION_MARKER(0x8001F940, "SLUS_004.64");
    w_u32(0x800CF984, 0);
    w_u32(0x800CF964, 0);
}

uint32 func_8002de0c(void)
{
    uint32 result;
    uint32 coordinate;
    uint32 selected;
    uint32 previous;
    uint32 available;
    FUNCTION_MARKER(0x8002DE0C, "SLUS_004.64");
    result = r_u32(0x800CF918);
    if (result != 0)
        return result;
    coordinate = r_u32(0x800DDD98);
    w_u32(coordinate + 0x18, 0);
    coordinate = r_u32(0x800DDD98);
    w_u32(coordinate + 0x1C, 0);
    coordinate = r_u32(0x800DDD98);
    w_u32(coordinate + 0x20, 20000);
    coordinate = r_u32(0x800DDD98);
    w_u32(coordinate, 0);
    func_8001b21c(0x800DDD94);
    selected = r_u32(0x800EE010);
    selected = r_u32(0x800B30BC + selected * 24);
    func_8001b21c(0x800EB1F4 + selected * 16);
    func_8002e030();
    selected = r_u32(0x800EE010);
    previous = r_u32(0x800CFB7C);
    available = r_u32(0x800EF4D8 + selected * 4);
    w_u32(0x800CF91C, 0);
    w_u32(0x800CFB78, 0);
    w_u32(0x800CF918, 1);
    w_u32(0x800CFB80, previous);
    if (available == 0)
        return func_8002e510();
    return 1;
}

uint32 func_8002e2ac(uint32 selected)
{
    uint32 result;
    uint32 coordinate;
    uint32 previous;
    FUNCTION_MARKER(0x8002E2AC, "SLUS_004.64");
    result = r_u32(0x800CF918);
    if (result != 0)
        return result;
    coordinate = r_u32(0x800EA368);
    w_u32(0x800CF928, 0);
    w_u32(0x800EE010, selected);
    w_u32(coordinate, 0);
    func_8001e878(0x800EA364);
    coordinate = r_u32(0x800EA368);
    w_u32(coordinate + 0x18, 0xFFFFEA20);
    coordinate = r_u32(0x800EA368);
    w_u32(coordinate + 0x1C, 4200);
    coordinate = r_u32(0x800EA368);
    w_u32(coordinate + 0x20, 14000);
    func_8001b21c(0x800EA364);
    coordinate = r_u32(0x800DDD98);
    w_u32(coordinate + 0x18, 0);
    coordinate = r_u32(0x800DDD98);
    w_u32(coordinate + 0x1C, 0);
    coordinate = r_u32(0x800DDD98);
    w_u32(coordinate + 0x20, 20000);
    coordinate = r_u32(0x800DDD98);
    w_u32(coordinate, 0);
    func_8001b21c(0x800DDD94);
    previous = r_u32(0x800CFB7C);
    w_u32(0x800CFB74, 0);
    w_u32(0x800CF918, 2);
    w_u32(0x800CF91C, 0);
    w_u32(0x800CFB78, 0);
    w_u32(0x800CFB80, previous);
    return 2;
}

uint32 func_8002e510(void)
{
    uint32 coordinate;
    uint32 next;
    uint32 cursor;
    uint32 previous;
    uint32 value;
    FUNCTION_MARKER(0x8002E510, "SLUS_004.64");
    coordinate = r_u32(0x800DDD98);
    w_u32(coordinate, 0);
    next = r_u32(0x800EE010) + 1;
    if ((sint32)next < 50)
    {
        previous = r_u32(0x800CFB7C);
        for (cursor = next; (sint32)cursor < 50; ++cursor)
        {
            value = r_u32(0x800EF4D8 + cursor * 4);
            if (value != 0)
                goto found;
        }
    }
    if ((sint32)next > 0)
    {
        previous = r_u32(0x800CFB7C);
        for (cursor = 0; (sint32)cursor < (sint32)next; ++cursor)
        {
            value = r_u32(0x800EF4D8 + cursor * 4);
            if (value != 0)
                goto found;
        }
    }
    w_u32(0x800EE010, 0);
    return 0;
found:
    w_u32(0x800EE010, cursor);
    w_u32(0x800CFB80, previous);
    w_u32(0x800CF91C, 0);
    return value;
}

uint32 func_8002e8c8(void)
{
    uint32 coordinate;
    uint32 rotation;
    uint32 value;
    FUNCTION_MARKER(0x8002E8C8, "SLUS_004.64");
    coordinate = r_u32(0x800EA368);
    rotation = r_u32(coordinate + 0x44);
    value = r_u16(rotation + 0x10);
    w_u16(rotation + 0x10, value);
    coordinate = r_u32(0x800EA368);
    rotation = r_u32(coordinate + 0x44);
    value = r_u16(rotation + 0x12);
    w_u16(rotation + 0x12, value + 50);
    coordinate = r_u32(0x800EA368);
    rotation = r_u32(coordinate + 0x44);
    value = r_u16(rotation + 0x14);
    w_u16(rotation + 0x14, value + 50);
    coordinate = r_u32(0x800EA368);
    w_u32(coordinate, 0);
    return func_8001b21c(0x800EA364);
}

uint32 func_8002ea08(void)
{
    uint32 direction;
    uint32 value;
    uint32 selected;
    FUNCTION_MARKER(0x8002EA08, "SLUS_004.64");
    direction = r_u32(0x800CFBB4);
    value = r_u32(0x800CFBB0);
    value += direction << 3;
    w_u32(0x800CFBB0, value);
    if ((sint32)direction > 0)
    {
        if ((sint32)value >= 129)
        {
            w_u32(0x800CFBB4, 0xFFFFFFFF);
            w_u32(0x800CFBB0, 128);
        }
    }
    else if ((sint32)value < 0)
    {
        w_u32(0x800CFBB4, 1);
        w_u32(0x800CFBB0, 0);
    }
    selected = r_u32(0x800CFB74);
    value = r_u8(0x800CFBB0) + 64;
    w_u8(0x800E9C2C + (selected + 2) * 36, value);
    selected = r_u32(0x800CFB74);
    value = r_u32(0x800CFBB0) + 64;
    w_u8(0x800E9C2D + (selected + 2) * 36, (uint32)((sint32)value >> 1));
    selected = r_u32(0x800CFB74);
    w_u8(0x800E9C2E + (selected + 2) * 36, 32);
    return 32;
}

uint32 func_8003026c(void)
{
    uint32 state;
    FUNCTION_MARKER(0x8003026C, "SLUS_004.64");
    state = r_u32(0x800CF918);
    if (state == 2)
        return func_80030804();
    if ((sint32)state < 3)
    {
        if (state == 1)
            return func_800302ec();
        return 1;
    }
    if (state == 3)
        return func_800309e8();
    return 3;
}

uint32 func_80030804(void)
{
    uint32 input;
    uint32 mask;
    uint32 selected;
    uint32 ready;
    FUNCTION_MARKER(0x80030804, "SLUS_004.64");
    input = r_u32(0x800CF934);
    if ((input & 4096) != 0 && r_u32(0x800CFB74) != 0)
    {
        func_8002372c(4);
        mask = r_u32(0x800CF870);
        w_u32(0x800CFB74, 0);
        w_u32(0x800CF870, mask | 4096);
    }
    else
    {
        input = r_u32(0x800CF934);
        if ((input & 16384) != 0 && r_u32(0x800CFB74) == 0)
        {
            func_8002372c(4);
            mask = r_u32(0x800CF870);
            w_u32(0x800CFB74, 1);
            w_u32(0x800CF870, mask | 16384);
        }
    }
    if (r_u32(0x800CF844) == 2 || r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0)
    {
        w_u32(0x800CF918, 0);
        w_u32(0x800CF91C, 0);
    }
    input = r_u32(0x800CF934);
    if ((input & 32) != 0)
    {
        ready = r_u32(0x800CFB78);
        if (ready == 1)
        {
            w_u32(0x800CFB74, ready);
            w_u32(0x800CF918, 0);
            w_u32(0x800CF91C, 0);
            w_u32(0x800CFB78, 0);
            w_u32(0x800CF928, 0);
            func_8002372c(2);
            mask = r_u32(0x800CF870);
            w_u32(0x800CF934, 0);
            w_u32(0x800CF870, mask | 32);
        }
    }
    input = r_u32(0x800CF934);
    if ((input & 64) == 0)
        return 0;
    if (r_u32(0x800CFB78) != 1)
        return 1;
    selected = r_u32(0x800CFB74);
    if (selected == 0)
    {
        selected = r_u32(0x800EE010);
        w_u32(0x800CF928, selected);
    }
    else
        w_u32(0x800CF928, 0);
    mask = r_u32(0x800CF870);
    w_u32(0x800CFB78, 0);
    w_u32(0x800CF918, 0);
    w_u32(0x800CF91C, 0);
    w_u32(0x800CF934, 0);
    mask |= 64;
    w_u32(0x800CF870, mask);
    return mask;
}

uint32 func_800309e8(void)
{
    uint32 input;
    uint32 mask;
    uint32 selected;
    uint32 exit_requested;
    uint32 result;
    FUNCTION_MARKER(0x800309E8, "SLUS_004.64");
    input = r_u32(0x800CF934);
    if ((input & 4096) != 0 && r_u32(0x800CFB74) != 0)
    {
        func_8002372c(4);
        mask = r_u32(0x800CF870);
        w_u32(0x800CFB74, 0);
        w_u32(0x800CF870, mask | 4096);
    }
    else
    {
        input = r_u32(0x800CF934);
        if ((input & 16384) != 0 && r_u32(0x800CFB74) == 0)
        {
            func_8002372c(4);
            mask = r_u32(0x800CF870);
            w_u32(0x800CFB74, 1);
            w_u32(0x800CF870, mask | 16384);
        }
    }
    if (r_u32(0x800CF844) == 2 || r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0)
    {
        w_u32(0x800CF918, 0);
        w_u32(0x800CF91C, 0);
        w_u32(0x800CFB84, 0);
    }
    input = r_u32(0x800CF934);
    if ((input & 64) == 0)
        return 0;
    if (r_u32(0x800CFB78) != 1)
        return 1;
    func_8002372c(1);
    selected = r_u32(0x800CFB74);
    mask = r_u32(0x800CF870);
    exit_requested = r_u32(0x800CFB84);
    w_u32(0x800CFB78, 0);
    w_u32(0x800CF918, 0);
    w_u32(0x800CF91C, 0);
    w_u32(0x800CF934, 0);
    w_u32(0x800CF92C, selected);
    result = mask | 64;
    w_u32(0x800CF870, result);
    if (exit_requested != 0 && selected == 0)
    {
        func_80028898(2);
        func_800378e8();
        result = 100;
        w_u32(0x800CF8DC, result);
    }
    w_u32(0x800CFB84, 0);
    return result;
}

uint32 func_800302ec(void)
{
    uint32 previous;
    uint32 input;
    uint32 count;
    uint32 limit;
    uint32 direction;
    uint32 mask;
    uint32 selected;
    uint32 actor;
    uint32 value;
    uint32 message;
    FUNCTION_MARKER(0x800302EC, "SLUS_004.64");
    previous = r_u32(0x800CF93C);
    input = r_u32(0x800CF934);
    if (previous == input)
    {
        count = r_u32(0x800CF940);
        limit = r_u32(0x800CF944);
        if ((sint32)limit >= (sint32)count)
        {
            ++count;
            w_u32(0x800CF940, count);
            return count;
        }
        count = r_u32(0x800CF948);
        limit = r_u32(0x800CF94C);
        if ((sint32)limit >= (sint32)count)
        {
            ++count;
            w_u32(0x800CF948, count);
            return count;
        }
        w_u32(0x800CF948, 0);
    }
    else
    {
        w_u32(0x800CF940, 0);
        w_u32(0x800CF948, 0);
        w_u32(0x800CF93C, input);
    }
    input = r_u32(0x800CF934);
    direction = 0;
    if (input & 32768)
    {
        func_8002372c(4);
        func_8002e510();
        direction = 32768;
    }
    else if (input & 8192)
    {
        func_8002372c(4);
        func_8002e5cc();
        direction = 8192;
    }
    else if (input & 4096)
    {
        func_8002372c(4);
        func_8002e5cc();
        direction = 4096;
    }
    else if (input & 16384)
    {
        func_8002372c(4);
        func_8002e510();
        direction = 16384;
    }
    if (direction != 0)
    {
        mask = r_u32(0x800CF870);
        w_u32(0x800CF870, mask | direction);
    }
    if (r_u32(0x800CF934) & 32)
    {
        func_8002372c(2);
        mask = r_u32(0x800CF870);
        w_u32(0x800CF918, 0);
        w_u32(0x800CF91C, 0);
        w_u32(0x800CF870, mask | 32);
    }
    if (r_u32(0x800CF844) == 2 || r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0)
    {
        w_u32(0x800CF918, 0);
        w_u32(0x800CF91C, 0);
    }
    if ((r_u32(0x800CF934) & 64) == 0)
        return 0;
    if (r_s32(0x800CF91C) < 11)
        return 1;
    func_8002372c(1);
    selected = r_u32(0x800EE010);
    w_u32(0x800CF918, 0);
    w_u32(0x800CF91C, 0);
    w_u32(0x800CF924, selected);
    if (selected != 12)
    {
        if (selected != 14 && selected != 23)
        {
            if (r_u32(0x800CFF6C) == 0)
            {
                actor = r_u32(0x800EE7EC);
                value = func_8001d480(actor, 0);
                w_u32(0x800CFF6C, value);
            }
            if (r_u32(0x800CFD9C) == 0)
            {
                actor = r_u32(0x800EE7EC);
                value = func_8001d480(actor, (uint16)0xFFFFFDE4);
                w_u32(0x800CFD9C, value);
            }
        }
        selected = r_u32(0x800CF924);
    }
    if (selected == 12)
    {
        if (r_u32(0x800CFE24) == 0)
        {
            actor = r_u32(0x800EE7EC);
            message = actor == 2 ? 1020 : 1019;
            func_8001f87c();
            func_8001f8a0(message, 0, 1296000);
            func_8001f92c();
            mask = r_u32(0x800CF870);
            w_u32(0x800CF870, mask | 64);
            func_8001fbcc();
            func_8001fa08();
            func_8001fbd8();
            mask = r_u32(0x800CF870);
            w_u32(0x800CF870, mask | 64);
        }
        else
        {
            w_u32(0x800CFB58, 1);
            func_8002b078(1);
            func_8001f87c();
            func_8001f8a0(1001, 0, 60);
            func_8001f92c();
        }
        selected = r_u32(0x800CF924);
    }
    if (selected == 23)
    {
        func_8001f87c();
        if (r_u32(0x800CFE24) == 0)
        {
            actor = r_u32(0x800EE7EC);
            message = actor == 2 ? 1021 : 1016;
            func_8001f8a0(message, 0, 1296000);
            func_8001f92c();
            mask = r_u32(0x800CF870);
            w_u32(0x800CF870, mask | 64);
            func_8001fbcc();
            func_8001fa08();
            func_8001fbd8();
            mask = r_u32(0x800CF870);
            w_u32(0x800CF870, mask | 64);
        }
        else
        {
            value = r_u32(0x800CF8F4);
            limit = r_u32(0x800CF8F8);
            if (value == limit)
            {
                func_8001f8a0(1016, 0, 60);
                func_8001f92c();
            }
            else if ((sint32)value > 0 && value != 0xFFFFFFFF)
            {
                func_80028740(1, 100, 100);
                value = r_u32(0x800CF8F8);
                w_u32(0x800CF8F4, value);
                func_8002ddc4(23);
                func_8002372c(11);
                func_8001f8a0(1017, 0, 60);
                func_8001f92c();
            }
        }
    }
    if (r_u32(0x800CF924) == 14)
        func_80018ad4();
    mask = r_u32(0x800CF870) | 64;
    w_u32(0x800CF870, mask);
    return mask;
}

uint32 func_8002e5cc(void)
{
    uint32 next;
    uint32 cursor;
    uint32 previous;
    uint32 value;
    FUNCTION_MARKER(0x8002E5CC, "SLUS_004.64");
    next = r_u32(0x800EE010) - 1;
    if ((sint32)next >= 0)
    {
        previous = r_u32(0x800CFB7C);
        for (cursor = next; (sint32)cursor >= 0; --cursor)
        {
            value = r_u32(0x800EF4D8 + cursor * 4);
            if (value != 0)
                goto found;
        }
    }
    if ((sint32)next <= 49)
    {
        previous = r_u32(0x800CFB7C);
        for (cursor = 49; (sint32)cursor >= (sint32)next; --cursor)
        {
            value = r_u32(0x800EF4D8 + cursor * 4);
            if (value != 0)
                goto found;
        }
    }
    w_u32(0x800EE010, 0);
    return 1;
found:
    w_u32(0x800EE010, cursor);
    w_u32(0x800CFB80, previous);
    w_u32(0x800CF91C, 0);
    return value;
}

void func_80028740(uint32 enabled, uint32 value, uint32 duration)
{
    FUNCTION_MARKER(0x80028740, "SLUS_004.64");
    w_u32(0x800CF8E4, enabled);
    if (enabled != 0)
    {
        if ((sint32)value >= 0)
            w_u32(0x800CF8F4, value);
        w_u32(0x800CF8E8, 0);
        w_u32(0x800CF8F0, duration);
        w_u32(0x800CF8EC, duration);
    }
    else
    {
        w_u32(0x800CF8F4, 100);
        w_u32(0x800CF8E8, 0);
        w_u32(0x800CF8F0, 60);
        w_u32(0x800CF8EC, 60);
    }
}

uint32 func_8002ddc4(uint32 index)
{
    uint32 address;
    uint32 value;
    FUNCTION_MARKER(0x8002DDC4, "SLUS_004.64");
    address = 0x800EF4D8 + index * 4;
    value = r_u32(address);
    if ((sint32)value > 0)
        w_u32(address, value - 1);
    return value - 1;
}

uint32 func_8002b078(uint32 mode)
{
    FUNCTION_MARKER(0x8002B078, "SLUS_004.64");
    if (mode == 0)
    {
        func_80032d40(0);
        func_8001f87c();
        func_8001f8a0(1000, 0, 60);
        func_8001f92c();
    }
    else if (mode == 1)
    {
        func_80032d40(12);
        func_8001f87c();
        func_8001f8a0(1001, 0, 60);
        func_8001f92c();
    }
    return 1;
}

uint32 func_8002f9b0(uint32 sprite, uint32 page_x, uint32 page_y, uint32 u, uint32 v, uint32 x, uint32 y, uint32 width, uint32 height, uint32 clut_x, uint32 clut_y)
{
    uint32 page;
    FUNCTION_MARKER(0x8002F9B0, "SLUS_004.64");
    w_u32(sprite, 64);
    w_u16(sprite + 0x18, 16);
    w_u16(sprite + 0x1A, 16);
    w_u16(sprite + 8, width);
    w_u16(sprite + 10, height);
    w_u16(sprite + 4, x);
    w_u16(sprite + 6, y);
    page = GetTPage(0, 0, (sint32)page_x, (sint32)page_y);
    w_u16(sprite + 12, page);
    w_u8(sprite + 14, u);
    w_u8(sprite + 15, v);
    w_u16(sprite + 16, clut_x);
    w_u16(sprite + 18, clut_y);
    w_u8(sprite + 20, 128);
    w_u8(sprite + 21, 128);
    w_u8(sprite + 22, 128);
    w_u32(sprite + 32, 0);
    w_u16(sprite + 28, 4096);
    w_u16(sprite + 30, 4096);
    return 4096;
}

uint32 func_8002a520(uint32 *angle)
{
    uint32 value;
    uint32 result;
    FUNCTION_MARKER(0x8002A520, "SLUS_004.64");
    value = *angle;
    result = value - 4096;
    if ((sint32)value >= 4097)
    {
        do
        {
            *angle = result;
            value = result;
            result = value - 4096;
        }
        while ((sint32)value >= 4097);
        value = *angle;
    }
    if ((sint32)value < 0)
    {
        do
        {
            result = value + 4096;
            *angle = result;
            value = result;
        }
        while ((sint32)result < 0);
    }
    return result;
}

uint32 func_8002a4a4(uint32 first, uint32 second, uint32 tolerance)
{
    uint32 difference;
    uint32 result;
    FUNCTION_MARKER(0x8002A4A4, "SLUS_004.64");
    func_8002a520(&first);
    func_8002a520(&second);
    difference = second - first;
    func_8002a520(&difference);
    result = (sint32)tolerance >= (sint32)difference;
    if ((sint32)difference >= (sint32)(4096 - tolerance))
        return 1;
    return result;
}

sint32 func_8002a570(uint32 first, uint32 second)
{
    uint32 difference;
    FUNCTION_MARKER(0x8002A570, "SLUS_004.64");
    func_8002a520(&first);
    func_8002a520(&second);
    difference = second - first;
    func_8002a520(&difference);
    return (sint32)difference < 2049 ? 1 : -1;
}

uint32 func_80032d40(uint32 action)
{
    uint32 result;
    FUNCTION_MARKER(0x80032D40, "SLUS_004.64");
    result = func_80030b78(action);
    w_u32(0x800EDFDC, result);
    return result;
}

uint32 func_80030b78(uint32 action)
{
    FUNCTION_MARKER(0x80030B78, "SLUS_004.64");
    return r_u32(0x800B30C0 + action * 24);
}

uint32 func_80023ec8(uint32 object, uint32 enabled)
{
    uint32 offset;
    uint32 coordinate;
    uint32 value;
    uint32 mode;
    FUNCTION_MARKER(0x80023EC8, "SLUS_004.64");
    offset = (object + r_u32(0x800CF828) - 1) * 44;
    coordinate = 0x800DDD48 + object * 16;
    value = r_u32(r_u32(coordinate) + 24) - 400;
    w_u32(0x8007F06C + offset, value);
    value = r_u32(r_u32(coordinate) + 32) - 400;
    w_u32(0x8007F070 + offset, value);
    value = r_u32(r_u32(coordinate) + 24) + 400;
    w_u32(0x8007F074 + offset, value);
    value = r_u32(coordinate);
    mode = r_u32(0x800CF908);
    value = r_u32(value + 32);
    w_u32(0x8007F088 + offset, enabled);
    w_u32(0x8007F078 + offset, value + 400);
    value = (uint32)1 << (mode & 31);
    w_u32(0x8007F08C + offset, value);
    return value;
}

void func_80021130(sint32 movie)
{
    uint32 object;
    uint32 position;
    FUNCTION_MARKER(0x80021130, "SLUS_004.64");
    if (r_u32(0x800CF7CC) == 0)
        return;
    func_80020e78(movie, 2);
    func_80016250();
    func_800210b8();
    func_8001a830();
    func_8001ef00();
    func_80022a68();
    func_80016290();
    func_80016690();
    object = r_u32(0x800EE7EC);
    position = r_u32(0x800CF908);
    func_80020a48(object, position);
    object = r_u32(0x800EE7EC);
    position = r_u32(0x800CF908);
    func_80020b7c(object, position);
}

void func_80015064(void)
{
    uint32 mode;
    uint32 value;
    FUNCTION_MARKER(0x80015064, "SLUS_004.64");
    mode = r_u32(0x800EDFD8);
    switch (mode)
    {
    case 0:
    case 3:
        value = r_u16(0x800CF952);
        break;
    case 1:
        value = r_u16(0x800CF954);
        break;
    case 2:
        value = r_u16(0x800CF956);
        break;
    default:
        return;
    }
    w_u16(0x800CF950, value);
    func_80047dec(r_u16(0x800CF950));
}

uint32 func_80023308(uint32 value)
{
    FUNCTION_MARKER(0x80023308, "SLUS_004.64");
    w_u32(0x800EE02C, value);
    w_u32(0x800EE030, value);
    w_u32(0x800EE034, value);
    w_u32(0x800EE038, value);
    return 0x800EE02C;
}

void func_8002dda8(uint32 index)
{
    FUNCTION_MARKER(0x8002DDA8, "SLUS_004.64");
    w_u32(0x800EF4D8 + index * 4, 0);
}

uint32 func_8002dd84(uint32 index)
{
    uint32 address;
    uint32 value;
    FUNCTION_MARKER(0x8002DD84, "SLUS_004.64");
    address = 0x800EF4D8 + index * 4;
    value = r_u32(address) + 1;
    w_u32(address, value);
    return value;
}

uint32 func_80034e30(uint32 index)
{
    FUNCTION_MARKER(0x80034E30, "SLUS_004.64");
    return r_u32(0x8007E064 + (index << 6));
}

uint32 func_800353a0(uint32 bit)
{
    FUNCTION_MARKER(0x800353A0, "SLUS_004.64");
    return func_8003271c(bit, 1);
}

void func_80012d20(void)
{
    uint32 tick;
    FUNCTION_MARKER(0x80012D20, "SLUS_004.64");
    tick = (uint32)VSync(-1);
    w_u32(0x800CF834, tick);
    w_u32(0x800CF868, tick);
}

uint32 func_800181cc(void)
{
    uint32 tick;
    uint32 previous;
    uint32 elapsed;
    FUNCTION_MARKER(0x800181CC, "SLUS_004.64");
    tick = (uint32)VSync(-1);
    previous = r_u32(0x800CF830);
    w_u32(0x800CF834, tick);
    elapsed = tick - previous;
    elapsed += r_u32(0x800CF82C);
    w_u32(0x800EDFB0, elapsed);
    return elapsed;
}

uint32 func_80018244(void)
{
    uint32 cursor;
    uint32 value;
    uint32 checksum;
    FUNCTION_MARKER(0x80018244, "SLUS_004.64");
    w_u32(0x800EF5A0, 0);
    for (cursor = 0; cursor < 0x57E; ++cursor)
    {
        value = r_u32(0x800EDFA8 + cursor * 4);
        checksum = r_u32(0x800EF5A0);
        w_u32(0x800EF5A0, checksum + value);
    }
    return 0;
}

uint32 func_8001aca4(uint32 index, uint32 x, uint32 y, uint32 z)
{
    uint32 offset;
    FUNCTION_MARKER(0x8001ACA4, "SLUS_004.64");
    offset = index * 28;
    w_u32(0x80080FA4 + offset, x);
    w_u32(0x80080FA8 + offset, y);
    w_u32(0x80080FAC + offset, z);
    return offset;
}

uint32 func_80024048(sint32 mode)
{
    sint32 index;
    FUNCTION_MARKER(0x80024048, "SLUS_004.64");
    for (index = 1; index < 5; ++index)
        func_80023d9c(index, mode);
    return 0;
}

uint32 func_800359f4(uint32 animation, uint32 object_list, uint32 resource)
{
    static const uint8 identity_offsets[9] = {0, 8, 16, 4, 2, 10, 6, 14, 12};
    static const uint8 matrix_offsets[9] = {0, 6, 12, 2, 8, 14, 4, 10, 16};
    uint32 header;
    uint32 objects;
    uint32 object;
    uint32 command;
    uint32 flags;
    uint32 entry;
    uint32 matrix;
    uint32 data;
    uint32 index;
    uint32 offset;
    uint32 value;
    uint32 doubled;
    uint32 y;
    MATRIX local_matrix;
    MATRIX *target;
    VECTOR scale;
    VECTOR translation;
    FUNCTION_MARKER(0x800359F4, "SLUS_004.64");
    header = r_u32(animation);
    objects = r_u32(object_list);
    object = header & 0xFFFF;
    command = (header >> 16) & 15;
    flags = (header >> 20) & 15;
    entry = objects + object * 16;
    matrix = 0;
    if (entry != 16)
        matrix = r_u32(entry - 12) + 4;
    data = animation + 4;
    switch (command)
    {
    case 1:
        for (index = 0; index < 9; ++index)
        {
            offset = identity_offsets[index];
            value = index < 3 ? 4096 : 0;
            if (entry == 16)
                local_matrix.m[offset / 6][(offset % 6) / 2] = (sint16)value;
            else
                w_u16(matrix + offset, value);
        }
        /* Local angle and relative-transform results never escape */
        if ((flags & 2) != 0)
        {
            for (index = 0; index < 3; ++index)
                (void)r_s32(data + index * 4);
            data += 12;
        }
        if ((flags & 4) != 0)
        {
            scale.vx = r_s16(data);
            scale.vy = r_s16(data + 2);
            scale.vz = r_s16(data + 4);
            data += 8;
            if ((flags & 1) == 0)
            {
                target = entry == 16 ? &local_matrix : (MATRIX *)psx_addr(matrix, sizeof(MATRIX));
                ScaleMatrix(target, &scale);
            }
        }
        if ((flags & 8) != 0)
        {
            for (index = 0; index < 3; ++index)
                (void)r_u32(data + index * 4);
        }
        break;
    case 4:
        doubled = resource != 3 && resource != 16 && object == 1 && r_u32(0x800EDFE0) == 2;
        for (index = 0; index < 9; ++index)
        {
            value = r_u16(data + index * 2);
            if (doubled != 0)
                value <<= 1;
            offset = matrix_offsets[index];
            if (entry == 16)
                local_matrix.m[offset / 6][(offset % 6) / 2] = (sint16)value;
            else
                w_u16(matrix + offset, value);
        }
        data += 20;
        translation.vx = r_s32(data);
        y = r_u32(data + 4);
        if (doubled != 0)
            y += r_u32(0x800EDFAC);
        translation.vy = (sint32)y;
        translation.vz = r_s32(data + 8);
        target = entry == 16 ? &local_matrix : (MATRIX *)psx_addr(matrix, sizeof(MATRIX));
        TransMatrix(target, &translation);
        break;
    default:
        break;
    }
    return animation + ((header >> 24) << 2);
}

uint32 func_8001a34c(uint32 object, uint32 x, uint32 y, uint32 z)
{
    uint32 actor;
    uint32 pitch;
    uint32 yaw;
    uint32 roll;
    uint32 coordinate;
    uint32 value;
    VECTOR offset;
    FUNCTION_MARKER(0x8001A34C, "SLUS_004.64");
    actor = 0x800DDD48 + object * 16;
    pitch = r_u16(r_u32(r_u32(actor) + 68) + 16);
    yaw = r_u16(r_u32(r_u32(actor) + 68) + 18);
    roll = r_u16(r_u32(r_u32(actor) + 68) + 20);
    /* Packed high halfwords are unused SVECTOR padding */
    func_800366a8((x & 0xFFFF) | ((y & 0xFFFF) << 16), z & 0xFFFF, pitch | (yaw << 16), roll, &offset);
    coordinate = r_u32(actor);
    value = r_u32(coordinate + 24) + (uint32)offset.vx;
    w_u32(coordinate + 24, value);
    coordinate = r_u32(actor);
    value = r_u32(coordinate + 28) + (uint32)offset.vy;
    w_u32(coordinate + 28, value);
    coordinate = r_u32(actor);
    value = r_u32(coordinate + 32) + (uint32)offset.vz;
    w_u32(coordinate + 32, value);
    return value;
}

void func_8002df08(uint8 *destination, sint32 number)
{
    sint32 hundreds;
    sint32 tens;
    sint32 units;
    uint32 source;
    FUNCTION_MARKER(0x8002DF08, "SLUS_004.64");
    hundreds = number / 100;
    tens = (number % 100) / 10;
    units = (number % 100) % 10;
    if (hundreds != 0)
    {
        source = r_u32(0x800B3568 + (uint32)hundreds * 4);
        strncpy((char *)destination, (const char *)psx_addr(source, 2), 2);
        destination += 2;
    }
    if (tens != 0 || hundreds != 0)
    {
        source = r_u32(0x800B3568 + (uint32)tens * 4);
        strncpy((char *)destination, (const char *)psx_addr(source, 2), 2);
        destination += 2;
    }
    source = r_u32(0x800B3568 + (uint32)units * 4);
    strncpy((char *)destination, (const char *)psx_addr(source, 2), 2);
    destination[2] = 0;
}

uint32 func_8002f7c0(uint32 index)
{
    uint32 sprite;
    uint32 y;
    uint32 page;
    FUNCTION_MARKER(0x8002F7C0, "SLUS_004.64");
    sprite = 0x800E9C18 + index * 36;
    w_u32(sprite, 64);
    w_u16(sprite + 8, 256);
    w_u16(sprite + 10, 20);
    w_u16(sprite + 4, (uint32)-296 - index * 100);
    y = index * 20;
    w_u16(sprite + 6, y - 80);
    w_u16(sprite + 24, 16);
    w_u16(sprite + 26, 16);
    page = GetTPage(0, 0, 960, 256);
    w_u16(sprite + 12, page);
    w_u8(sprite + 14, 0);
    /* Removing a multiple of 256 preserves the stored byte */
    w_u8(sprite + 15, y + 385);
    w_u16(sprite + 16, 896);
    w_u16(sprite + 18, 496);
    w_u8(sprite + 20, 128);
    w_u8(sprite + 21, 128);
    w_u8(sprite + 22, 128);
    w_u32(sprite + 32, 0);
    w_u16(sprite + 28, 4096);
    w_u16(sprite + 30, 4096);
    w_u32(0x800EB9D4 + index * 4, 1);
    return 1;
}
