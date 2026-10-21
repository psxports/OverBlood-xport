#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Full original bodies, pending final integration and runtime validation */
void func_8002fa84(uint32 item)
{
    uint32 state;
    uint32 count;
    uint32 value;
    uint32 text_base;
    uint32 line;
    uint32 format_address;
    uint32 y;
    const char *format;
    const char *amount;
    sint32 length;
    FUNCTION_MARKER(0x8002FA84, "SLUS_004.64");
    state = r_u32(0x800CF91C);
    if (state > 10)
        return;
    switch (state)
    {
    case 0:
        for (count = 0; count < 4; ++count)
            w_u32(0x800EB9E0 - count * 4, 0);
        if (item == 12)
            value = r_u32(0x800EDFF4);
        else
            value = r_u32(0x800EF4D8 + item * 4);
        func_8002df08((uint8 *)psx_addr(0x800CFEF4, 7), (sint32)value);
        w_u32(0x800D771C, 0x800CFBB8);
        w_u32(0x800D7740, 1);
        w_u32(0x800D7730, 65535);
        w_u32(0x800D7734, 0);
        w_u32(0x800D7720, 960);
        w_u32(0x800D7724, 385);
        w_u32(0x800D7728, 896);
        w_u32(0x800D772C, 496);
        length = (sint32)strlen(guest_c_string(0x800CFBB8));
        value = r_u32(0x800CF91C);
        w_u32(0x800D7738, (uint32)length >> 1);
        w_u32(0x800D773C, 4);
        w_u32(0x800CF91C, value + 1);
        return;
    case 2:
        format_address = 0x800B3590 + item * 160;
        y = 385;
        line = 0;
        break;
    case 4:
        format_address = 0x800B35B8 + item * 160;
        y = 405;
        line = 1;
        break;
    case 6:
        format_address = 0x800B35E0 + item * 160;
        y = 425;
        line = 2;
        break;
    case 8:
        format_address = 0x800B3608 + item * 160;
        y = 445;
        line = 3;
        break;
    default:
        w_u32(0x800CF91C, r_u32(0x800CF91C) + 1);
        return;
    }
    format = guest_c_string(format_address);
    amount = guest_c_string(0x800CFEF4);
    length = snprintf(NULL, 0, format, amount);
    sprintf((char *)psx_addr(0x800EC150, (uint32)length + 1), format, amount);
    text_base = r_u32(0x800CFA1C);
    w_u32(0x800D771C, 0x800EC150);
    w_u32(0x800D7720, 960);
    w_u32(0x800D7724, y);
    w_u32(0x800D7754, text_base);
    w_u32(0x800D7758, text_base + 6880);
    length = (sint32)strlen(guest_c_string(0x800EC150));
    w_u32(0x800D7738, (uint32)length >> 1);
    func_8002d700(0x800D771C);
    func_8002f7c0(line);
    w_u32(0x800CF91C, r_u32(0x800CF91C) + 1);
}

uint32 func_8001be34(sint32 x, sint32 z, sint32 radius, uint32 *event, uint32 *owner, uint32 *hit_index, uint32 ignored_index, uint32 ignored_owner)
{
    uint32 index;
    uint32 offset;
    uint32 value;
    uint32 modes;
    uint32 kind;
    uint32 hit;
    sint32 x0;
    sint32 z0;
    sint32 x1;
    sint32 z1;
    FUNCTION_MARKER(0x8001BE34, "SLUS_004.64");
    if (r_u32(0x800EDFD0) != 0)
        radius >>= 1;
    x >>= 7;
    z >>= 7;
    radius >>= 7;
    *event = 0;
    *owner = 0;
    index = 0;
    while (r_u32(0x8007F064 + index * 44) != 0xFFFFFFFF)
    {
        offset = index * 44;
        if (index != ignored_index)
        {
            value = r_u32(0x8007F084 + offset);
            if ((value != ignored_owner || ignored_owner == 0xFFFFFFFF) && r_u32(0x8007F088 + offset) != 0)
            {
                modes = r_u32(0x8007F08C + offset);
                if (modes == 0 || (sint32)(modes & ((uint32)1 << (r_u32(0x800CF908) & 31))) > 0)
                {
                    func_8001ba90(index, &x0, &z0, &x1, &z1);
                    x0 >>= 7;
                    z0 >>= 7;
                    x1 >>= 7;
                    z1 >>= 7;
                    kind = r_u32(0x8007F068 + offset);
                    if (kind == 1)
                        hit = func_8003716c((uint32)x, (uint32)z, (uint32)radius, (uint32)x0, (uint32)z0, (uint32)x1, (uint32)z1);
                    else if (kind == 2)
                        hit = func_80037200((uint32)x, (uint32)z, (uint32)radius, (uint32)x0, (uint32)z0, (uint32)x1, (uint32)z1);
                    else
                        hit = (uint32)func_80036eec(x, z, radius, x0, z0, x1, z1);
                    if (hit == 1)
                    {
                        if (*event == 0 && r_u32(0x8007F064 + offset) != 0)
                            *event = r_u32(0x8007F07C + offset);
                        if (r_u32(0x8007F088 + offset) != 0)
                        {
                            *owner = r_u32(0x8007F084 + offset);
                            *hit_index = index;
                            return 1;
                        }
                    }
                }
            }
        }
        ++index;
    }
    return 0;
}

uint32 func_8002a5d0(uint32 x, uint32 z, uint32 object, uint32 last_object)
{
    uint32 event;
    uint32 owner;
    uint32 hit_index;
    FUNCTION_MARKER(0x8002A5D0, "SLUS_004.64");
    return func_8001be34((sint32)x, (sint32)z, 650, &event, &owner, &hit_index, last_object, object) != 0;
}

uint32 func_800299c8(uint32 object, uint32 x, uint32 z)
{
    uint32 actor;
    uint32 coordinate;
    uint32 shift;
    uint32 step;
    uint32 next_x;
    uint32 next_z;
    uint32 value;
    FUNCTION_MARKER(0x800299C8, "SLUS_004.64");
    actor = 0x800DDD48 + object * 16;
    if (func_8002a5d0(x, z, object, object + r_u32(0x800CF828) - 1) != 1)
        return 0;
    if (func_8002a60c(r_u32(0x800EE7EC), object, &next_x, &next_z, 1800, 0) != 0)
        return 0;
    shift = r_u32(0x800EDFD0);
    coordinate = r_u32(actor);
    value = r_u32(coordinate + 24);
    step = (uint32)((sint32)90 >> (shift & 31));
    w_u32(coordinate + 24, value + step);
    coordinate = r_u32(actor);
    value = r_u32(coordinate + 32);
    w_u32(coordinate + 32, value + step);
    func_80024048(0);
    return 1;
}

void func_8002e67c(void)
{
    uint32 delay;
    uint32 coordinate;
    uint32 rotation;
    uint32 selected;
    uint32 axis;
    uint32 increment;
    uint32 value;
    FUNCTION_MARKER(0x8002E67C, "SLUS_004.64");
    delay = r_u32(0x800CFB80);
    if ((sint32)delay > 0)
    {
        w_u32(0x800CFB80, delay - 1);
        func_8001e8d8(5);
        return;
    }
    func_8001e8b4(5);
    w_u32(r_u32(0x800DDD98) + 24, 0);
    w_u32(r_u32(0x800DDD98) + 28, 0);
    coordinate = r_u32(0x800DDD98);
    w_u32(coordinate + 32, r_u32(coordinate + 32) - 1000);
    coordinate = r_u32(0x800DDD98);
    if (r_s32(coordinate + 32) < 4000)
        w_u32(coordinate + 32, 4000);
    for (axis = 0; axis < 3; ++axis)
    {
        selected = r_u32(0x800EE010);
        if (r_u32(0x800B30C4 + selected * 24 + axis * 4) == 0)
        {
            rotation = r_u32(r_u32(0x800DDD98) + 68);
            w_u16(rotation + 16 + axis * 2, 0);
        }
    }
    for (axis = 0; axis < 3; ++axis)
    {
        selected = r_u32(0x800EE010);
        coordinate = r_u32(0x800DDD98);
        rotation = r_u32(coordinate + 68);
        increment = r_u16(0x800B30C4 + selected * 24 + axis * 4);
        value = r_u16(rotation + 16 + axis * 2);
        w_u16(rotation + 16 + axis * 2, value + increment);
    }
    w_u32(r_u32(0x800DDD98), 0);
    func_8001b21c(0x800DDD94);
}

uint32 func_8002e95c(uint32 ordering_table, uint32 x, uint32 y, uint32 width, uint32 height, uint32 priority)
{
    uint32 box[4];
    uint32 color;
    uint32 direction;
    uint32 value;
    FUNCTION_MARKER(0x8002E95C, "SLUS_004.64");
    color = r_u8(0x800CFBB0);
    box[0] = 0x40000000;
    box[1] = (x & 0xFFFF) | ((y & 0xFFFF) << 16);
    box[2] = (width & 0xFFFF) | ((height & 0xFFFF) << 16);
    box[3] = color | (color << 16);
    GsSortBoxFill(box, psx_addr(ordering_table, 20), priority);
    direction = r_u32(0x800CFBB4);
    value = r_u32(0x800CFBB0) + (direction << 3);
    w_u32(0x800CFBB0, value);
    if ((sint32)direction > 0)
    {
        if ((sint32)value < 129)
            return 1;
        w_u32(0x800CFBB4, 0xFFFFFFFF);
        w_u32(0x800CFBB0, 128);
        return 128;
    }
    if ((sint32)value < 0)
    {
        w_u32(0x800CFBB4, 1);
        w_u32(0x800CFBB0, 0);
        return 1;
    }
    return value;
}

void func_8002ac54(void)
{
    uint32 value;
    uint32 available;
    uint32 parameter;
    FUNCTION_MARKER(0x8002AC54, "SLUS_004.64");
    w_u32(0x800CF870, r_u32(0x800CF870) | 8);
    func_80017a74();
    func_8002afe8();
    func_80031b14(r_u32(0x800EE7EC), 0, 1, 0, 0, 0);
    func_80032320(r_u32(0x800EE7EC), 0);
    w_u32(0x800CFE24, 0);
    func_8001ef90(52);
    func_8001f13c();
    w_u32(0x800819E8, 0);
    w_u32(0x800CFB1C, 0);
    func_80032d40(0);
    value = r_u32(0x800EE7F0);
    if (value != 0)
        w_u32(0x80081998 + value * 4, 1);
    func_80023d9c(4, 0);
    available = r_u32(0x800CFDF4);
    parameter = r_u32(0x800CFB24);
    w_u32(0x800EE0A8, 0xFFFFFFFF);
    w_u32(0x800CF878, available);
    /* The preceding helper leaves its zero mode in a1 */
    if ((sint32)parameter > 0)
        func_800178b0((sint32)parameter, 0);
    func_80028740(0, 100, 100);
    value = r_u32(0x800CFA6C);
    w_u32(0x800CF914, 1);
    func_80032d68(value, 7);
}

uint32 func_8002ad90(void)
{
    FUNCTION_MARKER(0x8002AD90, "SLUS_004.64");
    w_u32(0x800EE0A8, 1);
    w_u32(0x800EE0B0, 2);
    w_u32(0x800EE0AC, 3);
    w_u32(0x800EE0B4, 0);
    w_u32(0x800CFEFC, 0);
    w_u32(0x800CFF04, (uint32)-1000);
    w_u32(0x800CFF0C, 1000);
    w_u32(0x800CFFA4, 7000);
    w_u32(0x800EE0C4, 7000);
    w_u32(0x800EE0C8, 7000);
    w_u32(0x800EE0CC, 7000);
    w_u32(0x800CFB68, 4096);
    w_u32(0x800CFB64, 3);
    w_u32(0x800EE0DC, 1);
    w_u32(0x800EE0E4, 4);
    w_u32(0x800EE0E0, 3);
    w_u32(0x800EE0E8, 0);
    w_u32(0x800EE0F8, 4096);
    w_u32(0x800EE0FC, 4096);
    w_u32(0x800EE100, 4096);
    w_u32(0x800EE104, 0);
    w_u32(0x800EE108, 0);
    w_u32(0x800EE10C, 0);
    w_u32(0x800EE110, 0xFFFFFFFF);
    w_u32(0x800CFB60, 1);
    return 0xFFFFFFFF;
}

uint32 func_8002ae78(void)
{
    uint32 actor;
    uint32 x;
    uint32 y;
    uint32 z;
    uint32 scale;
    uint32 delay;
    FUNCTION_MARKER(0x8002AE78, "SLUS_004.64");
    if (r_u32(0x800CFB60) != 0)
    {
        actor = r_u32(0x800EE7EC);
        y = r_u32(0x800CFF04);
        z = r_u32(0x800CFF0C);
        x = r_u32(0x800CFEFC);
        scale = r_u32(0x800CFFA4);
        w_u32(0x800EE0B8, x);
        y -= 30;
        w_u32(0x800EE0BC, y);
        z -= 10;
        w_u32(0x800EE0C0, z);
        x = r_u32(0x800EE0B8);
        y = r_u32(0x800EE0BC);
        z = r_u32(0x800EE0C0);
        scale += 200;
        w_u32(0x800CFFA4, scale);
        w_u32(0x800EE0C4, scale);
        w_u32(0x800EE0C8, scale);
        w_u32(0x800EE0CC, scale);
        w_u32(0x800CFF04, y);
        w_u32(0x800CFF0C, z);
        func_800238bc(actor, x, y, z, (uint32 *)psx_addr(0x800EE0B8, 4), (uint32 *)psx_addr(0x800EE0BC, 4), (uint32 *)psx_addr(0x800EE0C0, 4));
        w_u32(0x800EE0EC, 0);
        w_u32(0x800EE0F0, (uint32)-1100);
        w_u32(0x800EE0F4, 1400);
        actor = r_u32(0x800EE7EC);
        x = r_u32(0x800EE0EC);
        y = r_u32(0x800EE0F0);
        z = r_u32(0x800EE0F4);
        scale = r_u32(0x800CFB68);
        w_u32(0x800EE0F8, scale);
        w_u32(0x800EE0FC, scale);
        w_u32(0x800EE100, scale);
        func_800238bc(actor, x, y, z, (uint32 *)psx_addr(0x800EE0EC, 4), (uint32 *)psx_addr(0x800EE0F0, 4), (uint32 *)psx_addr(0x800EE0F4, 4));
        if (r_s32(0x800EE0C4) >= 10001)
        {
            w_u32(0x800CFB60, 0);
            w_u32(0x800EE0A8, 0);
        }
    }
    delay = r_u32(0x800CFB64);
    scale = r_u32(0x800CFB68);
    --delay;
    w_u32(0x800CFB64, delay);
    scale += 4096;
    w_u32(0x800CFB68, scale);
    if ((sint32)delay <= 0)
        w_u32(0x800EE0DC, 0);
    return scale;
}

void func_8002afe8(void)
{
    FUNCTION_MARKER(0x8002AFE8, "SLUS_004.64");
    w_u32(0x800CFB60, 0);
    w_u32(0x800EE0A8, 0);
    w_u32(0x800EE0DC, 0);
}

uint32 func_8002b004(void)
{
    uint32 selected;
    uint32 limit;
    FUNCTION_MARKER(0x8002B004, "SLUS_004.64");
    for (;;)
    {
        selected = r_u32(0x800CFB58);
        limit = r_u32(0x800CFB5C);
        ++selected;
        w_u32(0x800CFB58, selected);
        if ((sint32)limit < (sint32)selected)
            w_u32(0x800CFB58, 0);
        selected = r_u32(0x800CFB58);
        if (selected == 0)
            break;
        if (selected == 1 && func_8002ddf0(12) != 0)
            break;
    }
    return func_8002b078(r_u32(0x800CFB58));
}

uint32 func_8002b32c(void)
{
    uint32 actor;
    uint32 action;
    uint32 first;
    uint32 mode;
    FUNCTION_MARKER(0x8002B32C, "SLUS_004.64");
    actor = r_u32(0x800EE7EC);
    action = func_80031954(actor);
    first = r_u32(0x800CFDAC);
    if ((sint32)action >= (sint32)first && (sint32)(first + 3) >= (sint32)action)
        return 0;
    if (action - 31 < 10)
        return 1;
    mode = r_u32(0x800CFB58);
    if (mode == 0)
    {
        func_8001f87c();
        func_8001f8a0(1006, 0, 60);
        func_8001f92c();
    }
    else if (mode != 1)
        return 1;
    return func_80031f28(actor, 36, 37);
}

uint32 func_8002ddf0(uint32 index)
{
    FUNCTION_MARKER(0x8002DDF0, "SLUS_004.64");
    return r_u32(0x800EF4D8 + index * 4);
}

uint32 func_8001ef90(uint32 resource)
{
    uint32 result;
    FUNCTION_MARKER(0x8001EF90, "SLUS_004.64");
    result = r_u32(0x800CFA24);
    if (result != 0)
    {
        func_80017a74();
        w_u32(0x800CF9EC, r_u32(0x800CFA24));
        w_u32(0x800CF9DC, r_u32(0x800CF9E0));
        func_8001f174(resource);
        w_u32(0x800CFA14, r_u32(0x800CF9EC));
        result = r_u32(0x800CF9DC);
        w_u32(0x800CF9E4, result);
    }
    return result;
}

void func_8002b3e0(void)
{
    FUNCTION_MARKER(0x8002B3E0, "SLUS_004.64");
    func_8002ae78();
    func_8002b42c();
    func_8002bac0();
    if (r_u32(0x800CF904) == 2)
        func_8002ac54();
}

uint32 func_8002b0e8(void)
{
    uint32 actor;
    uint32 action;
    uint32 first;
    uint32 mode;
    uint32 remaining;
    uint32 result;
    FUNCTION_MARKER(0x8002B0E8, "SLUS_004.64");
    actor = r_u32(0x800EE7EC);
    action = func_80031954(actor);
    first = r_u32(0x800CFDAC);
    if ((sint32)action >= (sint32)first && (sint32)(first + 3) >= (sint32)action)
        return 0;
    result = 1;
    if (action - 31 >= 10)
    {
        mode = r_u32(0x800CFB20);
        if (mode == 0)
            func_80031c20(actor, 31, 1, 0, 0, 0);
        else if (mode == 1)
            func_80031c20(actor, 32, 1, 0, 0, 0);
        else if (mode == 2)
            func_80031c20(actor, 33, 1, 0, 0, 0);
        func_80031b14(actor, 0, 1, 0, 0, 0);
        result = func_80032320(actor, 0);
    }
    mode = r_u32(0x800CFB58);
    if (mode == 0)
        return result;
    if (mode != 1)
        return 1;
    if (action != 37)
        return 37;
    remaining = r_u32(0x800EDFF4);
    if (remaining != 0)
    {
        w_u32(0x800EDFF4, remaining - 1);
        func_80031c20(actor, 38, 1, 0, 0, 0);
        func_80031b14(actor, 37, 1, 0, 0, 0);
        return func_80032320(actor, 37);
    }
    if (func_8002ddf0(19) != 0)
    {
        func_8002ddc4(19);
        func_8001f87c();
        func_8001f8a0(1008, 0, 60);
        func_8001f92c();
        w_u32(0x800EDFF4, 10);
        return 10;
    }
    func_8001f87c();
    func_8001f8a0(1009, 0, 60);
    func_8001f92c();
    func_80031c20(actor, 39, 1, 0, 0, 0);
    func_80031b14(actor, 0, 1, 0, 0, 0);
    return func_80032320(actor, 0);
}

uint32 func_8002c618(uint32 damage, uint32 action)
{
    uint32 value;
    uint32 actor;
    FUNCTION_MARKER(0x8002C618, "SLUS_004.64");
    value = r_u32(0x800CF8F4) - damage;
    if ((sint32)value > 0)
        func_800287ac(0 - damage);
    else
        w_u32(0x800CF8F4, 0);
    value = r_u32(0x800CF8F4);
    if (value == 0)
    {
        if (action != r_u32(0x800CFDAC))
        {
            func_80031c20(r_u32(0x800EE7EC), 35, 1, 0, 0, 0);
            func_80031b14(r_u32(0x800EE7EC), 40, 1, 0, 0, 0);
            func_80032320(r_u32(0x800EE7EC), 40);
        }
        actor = r_u32(0x800EE7EC);
        w_u32(0x800CF914, 0);
        value = actor * 4;
        w_u32(0x800EE088 + value, 0);
    }
    return value;
}

uint32 func_800287ac(uint32 delta)
{
    uint32 value;
    FUNCTION_MARKER(0x800287AC, "SLUS_004.64");
    value = r_u32(0x800CF8F4);
    w_u32(0x800CF8F4, delta + value);
    return value;
}

uint32 func_8002ceac(uint32 object, uint32 direction)
{
    uint32 result;
    uint32 base;
    FUNCTION_MARKER(0x8002CEAC, "SLUS_004.64");
    result = func_80031954(object);
    base = r_u32(0x800CFDAC);
    result -= 4;
    if (base != result)
        return result;
    func_80031c20(object, base + 6, 1, direction * 180, 0, 20);
    func_80031b14(object, r_u32(0x800CFDAC) + 16, 1, 0, 0, 0);
    return func_800319c0(object, r_u32(0x800CFDAC) + 4, 1, 0, 0, 0);
}

uint32 func_8002cf64(uint32 object, uint32 direction)
{
    uint32 result;
    uint32 base;
    FUNCTION_MARKER(0x8002CF64, "SLUS_004.64");
    result = func_80031954(object);
    base = r_u32(0x800CFDAC);
    result -= 4;
    if (base != result)
        return result;
    func_80031c20(object, base + 6, 1, direction * 180, 0, 20);
    return func_80031b14(object, r_u32(0x800CFDAC) + 17, 1, 0, 0, 0);
}

uint32 func_8002cff8(uint32 object)
{
    uint32 action;
    uint32 base;
    uint32 relative;
    FUNCTION_MARKER(0x8002CFF8, "SLUS_004.64");
    action = func_80031954(object);
    func_80031954(r_u32(0x800EE7EC));
    base = r_u32(0x800CFDAC);
    relative = action - base;
    if (relative != 4 && relative != 6)
        return 6;
    func_80031c20(object, base + 9, 1, 0, 0, 0);
    func_80031b14(object, r_u32(0x800CFDAC) + 4, 1, 0, 0, 0);
    func_80032320(object, r_u32(0x800CFDAC) + 4);
    if (r_s32(0x800CFE34) >= 3)
        return func_8002372c(62);
    return func_8002372c(r_u32(0x800B2F68 + (r_u32(0x800CFEDC) << 6)));
}

uint32 func_8002d0f8(uint32 object)
{
    uint32 action;
    uint32 base;
    uint32 relative;
    FUNCTION_MARKER(0x8002D0F8, "SLUS_004.64");
    action = func_80031954(object);
    func_80031954(r_u32(0x800EE7EC));
    base = r_u32(0x800CFDAC);
    relative = action - base;
    if (relative != 4 && relative != 6)
        return 6;
    if (r_s32(0x800CFE34) >= 3)
    {
        func_80031c20(object, base + 16, 1, 0, 0, 0);
        func_80031b14(object, r_u32(0x800CFDAC) + 17, 1, 0, 0, 0);
        func_800319c0(object, r_u32(0x800CFDAC) + 4, 1, 0, 0, 0);
        func_80032320(object, r_u32(0x800CFDAC) + 4);
        return func_8002372c(62);
    }
    func_80031c20(object, base + 16, 1, 0, 0, 0);
    func_80031b14(object, r_u32(0x800CFDAC) + 4, 1, 0, 0, 0);
    func_80032320(object, r_u32(0x800CFDAC) + 4);
    return func_8002372c(r_u32(0x800B2F68 + (r_u32(0x800CFEDC) << 6)));
}

uint32 func_8002d268(uint32 object)
{
    uint32 action;
    uint32 duration;
    uint32 base;
    uint32 relative;
    FUNCTION_MARKER(0x8002D268, "SLUS_004.64");
    action = func_80031954(object);
    func_80031954(r_u32(0x800EE7EC));
    duration = r_s32(0x800CFE34) < 3 ? 180 : 90;
    base = r_u32(0x800CFDAC);
    relative = action - base;
    if (relative == 4)
    {
        func_80031c20(object, base + 5, 1, 0, 0, duration);
        func_80031b14(object, r_u32(0x800CFDAC) + 6, 1, 0, 0, duration);
    }
    else if (relative == 9)
    {
        func_80031b14(object, base + 5, 1, 0, 0, duration);
        func_800319c0(object, r_u32(0x800CFDAC) + 6, 1, 0, 0, duration);
    }
    else
        return 9;
    return func_80032320(object, r_u32(0x800CFDAC) + 6);
}

uint32 func_8002d388(uint32 object)
{
    uint32 action;
    uint32 base;
    uint32 relative;
    FUNCTION_MARKER(0x8002D388, "SLUS_004.64");
    action = func_80031954(object);
    func_80031954(r_u32(0x800EE7EC));
    base = r_u32(0x800CFDAC);
    relative = action - base;
    if (relative == 7)
        return func_80031ee0(object, base + 4, base + 4);
    if ((sint32)relative >= 8)
    {
        if (relative != 9)
            return 9;
    }
    else if ((sint32)relative < 5)
        return 1;
    base = r_u32(0x800CFDAC);
    return func_80031ee0(object, base + 7, base + 4);
}

uint32 func_8002c2a8(uint32 action, uint32 mode)
{
    uint32 base;
    uint32 actor;
    uint32 source;
    uint32 coordinate;
    uint32 rotation;
    uint32 angle;
    uint32 sound;
    FUNCTION_MARKER(0x8002C2A8, "SLUS_004.64");
    if (action == 40)
        return 40;
    if (action - 34 < 2)
        return 1;
    base = r_u32(0x800CFDAC);
    if ((sint32)action >= (sint32)base && (sint32)action <= (sint32)(base + 3))
        return 0;
    actor = r_u32(0x800EE7EC);
    if (mode == 0)
        func_80031c20(actor, 34, 1, 0, 0, (uint32)-45);
    else if (mode == 1)
    {
        source = r_u32(0x800DDD88);
        coordinate = r_u32(0x800DDD48 + actor * 16);
        rotation = r_u32(source + 68);
        angle = r_u16(rotation + 18);
        rotation = r_u32(coordinate + 68);
        w_u16(rotation + 18, angle + 2048);
        func_80031c20(actor, base, 1, 0, 0, (uint32)-720);
        func_80031b14(actor, r_u32(0x800CFDAC) + 1, 1, 0, 0, 0);
        func_800319c0(actor, r_u32(0x800CFDAC) + 2, 1, 0, 0, 0);
        func_800319c0(actor, r_u32(0x800CFDAC) + 3, 1, 0, 0, 0);
    }
    else
        return 1;
    func_800319c0(actor, 0, 1, 0, 0, 0);
    func_80032320(actor, 0);
    sound = r_u32(0x800B2F70 + (r_u32(0x800CFEDC) << 6));
    w_u32(0x800CF914, 0);
    return func_8002372c(sound);
}

uint32 func_8002c45c(uint32 mode)
{
    uint32 value;
    uint32 base;
    FUNCTION_MARKER(0x8002C45C, "SLUS_004.64");
    value = r_u32(0x800CFB70);
    if (value != 0)
        return value;
    value = r_u32(0x800CF8FC);
    if ((sint32)value <= 0)
        return value;
    value = r_u32(0x800CF904);
    if (value != 0)
        return value;
    value = func_80031954(4);
    base = r_u32(0x800CFDAC);
    if (value == base + 16)
        return value;
    if (mode == 1 || mode == 2)
    {
        func_80031f28(4, base + (mode == 1 ? 11 : 10), base + 4);
        return func_8002372c(r_u32(0x800B2F58 + (r_u32(0x800CFEDC) << 6)));
    }
    if ((sint32)mode < 3)
        return 1;
    if (mode == 3)
        func_80031c20(4, base + 8, 1, 0, 0, (uint32)-90);
    else if (mode == 4)
    {
        func_80020a48(4, r_u32(0x800CF908));
        func_80031c20(4, r_u32(0x800CFDAC) + 8, 1, 0, 0, (uint32)-90);
    }
    else
        return 3;
    func_800319c0(4, r_u32(0x800CFDAC) + 4, 1, 0, 0, 0);
    func_80032320(4, r_u32(0x800CFDAC) + 4);
    return func_8002372c(r_u32(0x800B2F60 + (r_u32(0x800CFEDC) << 6)));
}

uint32 func_8002c74c(uint32 object, uint32 distance, uint32 *owner, uint32 *hit_index)
{
    uint32 radius;
    uint32 actor;
    uint32 pitch;
    uint32 yaw;
    uint32 roll;
    uint32 coordinate;
    uint32 x;
    uint32 z;
    uint32 ignored_index;
    uint32 ignored_owner;
    uint32 event;
    uint32 found_owner;
    uint32 found_index;
    VECTOR offset;
    FUNCTION_MARKER(0x8002C74C, "SLUS_004.64");
    *owner = 0;
    radius = r_u32(0x800EDFD0) == 0 ? 650 : 325;
    actor = 0x800DDD48 + object * 16;
    pitch = r_u16(r_u32(r_u32(actor) + 68) + 16);
    yaw = r_u16(r_u32(r_u32(actor) + 68) + 18);
    roll = r_u16(r_u32(r_u32(actor) + 68) + 20);
    /* Packed high halfwords are unused SVECTOR padding */
    func_800366a8(0, distance & 0xFFFF, pitch | (yaw << 16), roll, &offset);
    coordinate = r_u32(actor);
    x = r_u32(coordinate + 24);
    z = r_u32(coordinate + 32);
    ignored_index = r_u32(0x800CF828);
    ignored_owner = r_u32(0x800EE7EC);
    if (func_8001c194((sint32)(x + (uint32)offset.vx), (sint32)(z + (uint32)offset.vz), (sint32)radius, &event, &found_owner, &found_index, object + ignored_index - 1, ignored_owner) != 1)
        return 0;
    *owner = found_owner;
    *hit_index = found_index;
    return 1;
}

uint32 func_8001c194(sint32 x, sint32 z, sint32 radius, uint32 *event, uint32 *owner, uint32 *hit_index, uint32 ignored_index, uint32 ignored_owner)
{
    uint32 index;
    uint32 offset;
    uint32 value;
    uint32 modes;
    uint32 kind;
    uint32 hit;
    sint32 x0;
    sint32 z0;
    sint32 x1;
    sint32 z1;
    FUNCTION_MARKER(0x8001C194, "SLUS_004.64");
    if (r_u32(0x800EDFD0) != 0)
        radius >>= 1;
    x >>= 7;
    z >>= 7;
    radius >>= 7;
    *event = 0;
    *owner = 0;
    index = r_u32(0x800CF828);
    while (r_u32(0x8007F064 + index * 44) != 0xFFFFFFFF)
    {
        offset = index * 44;
        if (index != ignored_index)
        {
            value = r_u32(0x8007F084 + offset);
            if ((value != ignored_owner || ignored_owner == 0xFFFFFFFF) && r_u32(0x8007F088 + offset) != 0)
            {
                modes = r_u32(0x8007F08C + offset);
                if (modes == 0 || (sint32)(modes & ((uint32)1 << (r_u32(0x800CF908) & 31))) > 0)
                {
                    func_8001ba90(index, &x0, &z0, &x1, &z1);
                    x0 >>= 7;
                    z0 >>= 7;
                    x1 >>= 7;
                    z1 >>= 7;
                    kind = r_u32(0x8007F068 + offset);
                    if (kind == 1)
                        hit = func_8003716c((uint32)x, (uint32)z, (uint32)radius, (uint32)x0, (uint32)z0, (uint32)x1, (uint32)z1);
                    else if (kind == 2)
                        hit = func_80037200((uint32)x, (uint32)z, (uint32)radius, (uint32)x0, (uint32)z0, (uint32)x1, (uint32)z1);
                    else
                        hit = (uint32)func_80036eec(x, z, radius, x0, z0, x1, z1);
                    if (hit == 1)
                    {
                        if (*event == 0 && r_u32(0x8007F064 + offset) != 0)
                            *event = r_u32(0x8007F07C + offset);
                        if (r_u32(0x8007F088 + offset) != 0)
                        {
                            *owner = r_u32(0x8007F084 + offset);
                            *hit_index = index;
                            return 1;
                        }
                    }
                }
            }
        }
        ++index;
    }
    return 0;
}

uint32 func_80015ff8(void)
{
    uint32 active;
    FUNCTION_MARKER(0x80015FF8, "SLUS_004.64");
    w_u32(0x800EB8B4, r_u32(0x800EB8B4) + 512);
    active = GsGetActiveBuff();
    w_u32(0x800CFDEC, active);
    func_8004e594(0x80082164 + active * 86400);
    GsClearOt(0, 0, psx_addr(0x800EBD14 + r_u32(0x800CFDEC) * 20, 20));
    GsSortSprite(psx_addr(0x800EB894, 36), psx_addr(0x800EBD14 + r_u32(0x800CFDEC) * 20, 20), 0);
    DrawSync(0);
    ResetGraph(1);
    GsSwapDispBuff();
    GsSortClear(0, 0, 0, psx_addr(0x800EBD14 + r_u32(0x800CFDEC) * 20, 20));
    func_8004e5a4(0x800EBD14 + r_u32(0x800CFDEC) * 20);
    return 1;
}

uint32 func_8001f950(void)
{
    uint32 value;
    uint32 index;
    FUNCTION_MARKER(0x8001F950, "SLUS_004.64");
    for (;;)
    {
        value = r_u32(0x800CF844);
        if (value == 2)
            return value;
        value = r_u32(0x800CF8DC);
        if (value != 0)
            return value;
        value = r_u32(0x800CF8E0);
        if (value != 0)
            return value;
        if (r_s32(0x800CF964) <= 0)
        {
            index = r_u32(0x800CF97C);
            value = r_u32(0x800D85AC + index * 12);
            if (value == 0xFFFFFFFF)
                return value;
        }
        func_80012bfc();
        func_80015c44();
        w_u32(0x800CF850, 0);
    }
}

void func_800211ec(sint32 first_movie, sint32 second_movie)
{
    uint32 object;
    uint32 position;
    FUNCTION_MARKER(0x800211EC, "SLUS_004.64");
    if (r_u32(0x800CF7CC) == 0)
        return;
    func_80020e78(first_movie, 2);
    func_80020e78(second_movie, 2);
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

uint32 func_8002e3a0(uint32 first, uint32 second, uint32 value)
{
    uint32 state;
    uint32 coordinate;
    uint32 previous;
    FUNCTION_MARKER(0x8002E3A0, "SLUS_004.64");
    state = r_u32(0x800CF918);
    if (state != 0)
        return state;
    func_8002372c(3);
    coordinate = r_u32(0x800EA368);
    w_u32(0x800CFB84, value);
    w_u32(0x800CF928, 0);
    w_u32(0x800EE010, 15);
    w_u32(coordinate, 0);
    func_8001e878(0x800EA364);
    w_u32(r_u32(0x800EA368) + 24, (uint32)-5600);
    w_u32(r_u32(0x800EA368) + 28, 4200);
    w_u32(r_u32(0x800EA368) + 32, 14000);
    func_8001b21c(0x800EA364);
    w_u32(r_u32(0x800DDD98) + 32, 20000);
    w_u32(r_u32(0x800DDD98), 0);
    func_8001b21c(0x800DDD94);
    previous = r_u32(0x800CFB7C);
    w_u32(0x800CFB74, 0);
    w_u32(0x800CF918, 3);
    w_u32(0x800CF91C, 0);
    w_u32(0x800CFB78, 0);
    w_u32(0x800CFEE4, first);
    w_u32(0x800CFEEC, second);
    w_u32(0x800CFB80, previous);
    return 3;
}

uint32 func_80021288(sint32 first_movie, sint32 second_movie, uint32 object, uint32 resource)
{
    uint32 result;
    FUNCTION_MARKER(0x80021288, "SLUS_004.64");
    result = r_u32(0x800CF7CC);
    if (result == 0)
        return result;
    if (first_movie >= 0)
        func_80020e78(first_movie, 2);
    if (second_movie >= 0)
        func_80020e78(second_movie, 2);
    func_80016250();
    func_800210f8();
    func_8001a830();
    func_8001ef00();
    func_80016290();
    w_u32(0x800EE0A8, 0xFFFFFFFF);
    func_80022320(resource, object, r_u32(0x800CF820));
    func_8003537c(object);
    return func_80016690();
}

uint32 func_80021e14(uint32 owner, uint32 value)
{
    uint32 index;
    uint32 offset;
    uint32 next;
    uint32 result;
    FUNCTION_MARKER(0x80021E14, "SLUS_004.64");
    if (r_u32(0x8007E064) == 0xFFFFFFFF)
        return 0xFFFFFFFF;
    index = 0;
    do
    {
        offset = index << 6;
        if (r_u32(0x8007E098 + offset) == owner)
        {
            if (r_u32(0x8007E064 + offset) == 0)
            {
                w_u32(0x8007E064 + offset, 1);
                w_u32(0x8007E0A0 + offset, value);
            }
        }
        ++index;
        next = r_u32(0x8007E064 + (index << 6));
        result = (sint32)index < 64;
    }
    while (next != 0xFFFFFFFF && result != 0);
    return result;
}

uint32 func_80026a6c(uint32 enabled)
{
    uint32 previous;
    FUNCTION_MARKER(0x80026A6C, "SLUS_004.64");
    if (enabled != 0)
    {
        w_u32(0x800EDFB4, r_u32(0x800CF958));
        w_u32(0x800CF858, 1);
        w_u32(0x800CF7A0, 1);
        func_8001f0b8(58);
        func_80031c20(r_u32(0x800EE7EC), 43, 1, 0, 0, 0);
        func_80032320(r_u32(0x800EE7EC), 43);
        previous = r_u32(0x800CF878);
        w_u32(0x800CF878, 0);
        w_u32(0x800CF7A0, 0);
        w_u32(0x800CFAC8, previous);
    }
    else
    {
        previous = r_u32(0x800CFAC8);
        w_u32(0x800CF858, 0);
        w_u32(0x800CF878, previous);
    }
    w_u32(0x800CF934, 0);
    return previous;
}

void func_80028c44(const char *message)
{
    PSX_RECT rectangle;
    sint32 stream;
    FUNCTION_MARKER(0x80028C44, "SLUS_004.64");
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 320;
    rectangle.h = 480;
    ClearImage(&rectangle, 32, 32, 64);
    FntLoad(960, 256);
    stream = FntOpen(-144, -104, 320, 200, 0, 512);
    func_80046940(stream);
    func_80037934(message, -100, -20, 280, 100);
}

uint32 func_8001f0b8(uint32 resource)
{
    uint32 value;
    uint32 remainder;
    FUNCTION_MARKER(0x8001F0B8, "SLUS_004.64");
    func_80017a74();
    w_u32(0x800CF9DC, r_u32(0x800CF9E8));
    value = r_u32(0x800CFA04);
    w_u32(0x800CF9EC, value);
    remainder = (uint32)((sint32)value % 4);
    w_u32(0x800CF9EC, value + 4 - remainder);
    func_8003943c(0);
    func_8001f174(resource);
    func_8003943c(0);
    value = r_u32(0x800CF9EC);
    w_u32(0x800CFA08, value);
    return value;
}

uint32 func_8003537c(uint32 bit)
{
    FUNCTION_MARKER(0x8003537C, "SLUS_004.64");
    return func_8003271c(bit + 50, 1);
}

uint32 func_8003259c(uint32 object, uint32 x, uint32 y, uint32 z)
{
    uint32 actor;
    FUNCTION_MARKER(0x8003259C, "SLUS_004.64");
    actor = 0x800DDD48 + object * 16;
    w_u32(r_u32(actor) + 24, x);
    w_u32(r_u32(actor) + 28, y);
    w_u32(r_u32(actor) + 32, z);
    w_u32(r_u32(actor), 0);
    return func_8001b21c(0x800DDD44 + object * 16);
}

uint32 func_80032694(uint32 object, uint32 x, uint32 y, uint32 z)
{
    uint32 actor;
    FUNCTION_MARKER(0x80032694, "SLUS_004.64");
    actor = 0x800DDD48 + object * 16;
    w_u32(r_u32(actor) + 24, x);
    w_u32(r_u32(actor) + 28, y);
    w_u32(r_u32(actor) + 32, z);
    w_u32(r_u32(actor), 0);
    return func_8001b21c(0x800DDD44 + object * 16);
}

uint32 func_80034c88(uint32 object, uint32 part)
{
    uint32 coordinate;
    FUNCTION_MARKER(0x80034C88, "SLUS_004.64");
    if (object == 0)
    {
        w_u32(0x800EF608, 0);
        return 1;
    }
    if ((sint32)object >= 8 || part == 0xFFFFFFFF)
        coordinate = r_u32(0x800DDD48 + object * 16);
    else
        coordinate = r_u32(0x800EA708 + (object * 35 + part) * 16);
    w_u32(0x800EF608, coordinate);
    return coordinate;
}

uint32 func_800356ec(uint32 destination, uint32 source, uint32 remaining)
{
    uint32 cursor;
    uint32 character;
    uint32 count;
    FUNCTION_MARKER(0x800356EC, "SLUS_004.64");
    cursor = func_800356c0(source);
    for (;;)
    {
        character = r_u8(cursor);
        if (character == 13 && r_u8(cursor + 1) == 10)
        {
            cursor += 2;
            break;
        }
        character = r_u8(cursor);
        w_u8(destination, character);
        count = r_u32(remaining);
        ++cursor;
        ++destination;
        if ((sint32)count <= 0)
            break;
        w_u32(remaining, count - 1);
    }
    w_u8(destination, 0);
    return cursor;
}

uint32 func_80021ebc(void)
{
    uint32 index;
    uint32 offset;
    uint32 field;
    uint32 object;
    uint32 coordinate;
    uint32 rotation;
    FUNCTION_MARKER(0x80021EBC, "SLUS_004.64");
    index = 0;
    if (r_s32(0x800CFEA4) > 0)
    {
        do
        {
            offset = index << 6;
            for (field = 0; field < 3; ++field)
            {
                object = r_u32(0x8007E068 + offset);
                coordinate = r_u32(0x800DDD48 + object * 16);
                w_u32(coordinate + 24 + field * 4, 0);
            }
            for (field = 0; field < 3; ++field)
            {
                object = r_u32(0x8007E068 + offset);
                coordinate = r_u32(0x800DDD48 + object * 16);
                rotation = r_u32(coordinate + 68);
                w_u32(rotation + field * 4, 4096);
            }
            for (field = 0; field < 3; ++field)
            {
                object = r_u32(0x8007E068 + offset);
                coordinate = r_u32(0x800DDD48 + object * 16);
                rotation = r_u32(coordinate + 68);
                w_u16(rotation + 16 + field * 2, 0);
            }
            object = r_u32(0x8007E068 + offset);
            coordinate = r_u32(0x800DDD48 + object * 16);
            if (r_u32(coordinate) != 0)
            {
                func_8001b21c(0x800DDD44 + object * 16);
                object = r_u32(0x8007E068 + offset);
                w_u32(r_u32(0x800DDD48 + object * 16), 0);
            }
            w_u32(0x8007E064 + offset, 0);
            w_u32(0x8007E0A0 + offset, 0);
            ++index;
        }
        while ((sint32)index < r_s32(0x800CFEA4));
    }
    w_u32(0x8007E064, 0xFFFFFFFF);
    return 0xFFFFFFFF;
}

void func_80036328(uint8 *destination, const char *name, uint32 mode)
{
    char formatted[256];
    uint32 format;
    sint32 length;
    FUNCTION_MARKER(0x80036328, "SLUS_004.64");
    format = r_u32(0x800B4AD0 + mode * 4);
    sprintf(formatted, guest_c_string(format), name);
    length = (sint32)strlen(formatted);
    func_800222d0(destination, (const uint8 *)formatted, length);
}

uint32 func_800221a4(const uint8 *filename)
{
    const uint8 *cursor;
    uint8 extension[128];
    uint32 index;
    FUNCTION_MARKER(0x800221A4, "SLUS_004.64");
    cursor = filename;
    if (*cursor == 0)
        return 0;
    if (*cursor != '.')
    {
        ++cursor;
        while (*cursor != '.')
            ++cursor;
    }
    func_800222d0(extension, cursor + 1, 3);
    for (index = 0; index < 6; ++index)
    {
        if (strncmp((const char *)extension, (const char *)psx_addr(0x800CFA9C + index * 4, 3), 3) == 0)
            return index + 1;
    }
    return 0;
}

uint32 func_80017598(void)
{
    uint32 index;
    uint32 resource;
    uint32 digit;
    uint8 digits[4];
    char pattern[256];
    uint8 filename[256];
    char *number;
    sint32 value;
    FUNCTION_MARKER(0x80017598, "SLUS_004.64");
    if (r_u32(0x800CF7D4) != 2)
        return 2;
    index = 0;
    for (;;)
    {
        resource = r_u32(0x8007DB88 + index * 4);
        if (resource == 0xFFFFFFFF)
            return 0xFFFFFFFF;
        value = (sint32)resource;
        strcpy(pattern, guest_c_string(0x8007D94C + (uint32)(value / 20) * 32));
        number = strchr(pattern, '?');
        digits[0] = (uint8)(value / 1000);
        digits[1] = (uint8)((value % 1000) / 100);
        digits[2] = (uint8)((value % 100) / 10);
        digits[3] = (uint8)((value % 100) % 10);
        for (digit = 0; digit < 4; ++digit)
            number[digit] = (char)(digits[digit] + 48);
        func_80036328(filename, pattern, r_u32(0x800CF7D4));
        func_80039a00((const char *)filename, 0x800DE14C + resource * 24);
        ++index;
    }
}

static sint32 load_whole_resource_path(const char *path, uint32 destination, uint8 *native_destination, sint32 source_mode)
{
    char formatted[256];
    uint8 filename[256];
    uint32 format;
    sint32 length;
    func_8001eff8();
    format = r_u32(0x800B4AD0 + ((uint32)source_mode << 2));
    sprintf(formatted, guest_c_string(format), path);
    length = (sint32)strlen(formatted);
    func_800222d0(filename, (const uint8 *)formatted, length);
    if (native_destination != NULL)
        return read_resource_native((const char *)filename, native_destination, source_mode);
    if (source_mode == 0)
        return func_80036494((const char *)filename, destination);
    return func_8003944c((const char *)filename, destination);
}


sint32 func_80036184(const char *path, uint32 destination, sint32 source_mode)
{
    FUNCTION_MARKER(0x80036184, "SLUS_004.64");
    return load_whole_resource_path(path, destination, NULL, source_mode);
}

sint32 load_native_resource(const char *path, uint8 *destination, sint32 source_mode)
{
    return load_whole_resource_path(path, 0, destination, source_mode);
}

void func_80028480(uint32 ordering_table)
{
    uint32 value;
    uint32 countdown;
    uint32 width;
    FUNCTION_MARKER(0x80028480, "SLUS_004.64");
    if (r_u32(0x800CF8E8) != 0)
    {
        value = r_u32(0x800CF8F4);
        if ((sint32)value < 0)
            goto depleted;
        countdown = r_u32(0x800CF8EC) - 1;
        w_u32(0x800CF8EC, countdown);
        if ((sint32)countdown <= 0)
        {
            w_u32(0x800CF8F4, value - 1);
            w_u32(0x800CF8EC, r_u32(0x800CF8F0));
        }
    }
    value = r_u32(0x800CF8F4);
    if ((sint32)value < 0)
    {
depleted:
        countdown = r_u32(0x800CF8F0);
        w_u32(0x800CF8F4, 0);
        w_u32(0x800CF8EC, countdown);
        func_80028408(0);
        w_u32(0x800CF8E4, 0);
        value = r_u32(0x800CF8F4);
        if ((sint32)value < 0)
            value = 0;
    }
    width = (uint32)((sint32)((100 - value) * 80) / 100);
    func_800287dc(ordering_table, 64, 0, 48, 140 - width, (uint32)-96, width, 6, 0);
    func_800287dc(ordering_table, 0, 0, 96, 60, (uint32)-96, 80, 6, 0);
    func_800287dc(ordering_table, 8, 8, 8, 59, (uint32)-97, 82, 8, 0);
    func_800287dc(ordering_table, 96, 96, 96, 58, (uint32)-98, 84, 10, 0);
    func_800287dc(ordering_table, 0, 0, 0, 57, (uint32)-99, 86, 12, 0);
}

void func_80028408(uint32 mode)
{
    FUNCTION_MARKER(0x80028408, "SLUS_004.64");
    w_u32(0x800CF8DC, mode + 1);
}

void func_8001ad80(void)
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
    FUNCTION_MARKER(0x8001AD80, "SLUS_004.64");
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
            w_u32(destination + 8, 0);
            w_u8(destination + 12, 0);
            w_u8(destination + 13, 0);
            w_u8(destination + 14, 0);
        }
        GsSetFlatLight((sint32)index, (const GsF_LIGHT *)psx_addr(destination, 16));
    }
    red = (sint32)(r_u32(0x800CFF94) << 2);
    green = (sint32)(r_u32(0x800CFF74) << 2);
    blue = (sint32)(r_u32(0x800CFF64) << 2);
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

uint32 func_80026e64(void)
{
    uint32 index;
    uint32 effect;
    uint32 actor;
    uint32 value;
    FUNCTION_MARKER(0x80026E64, "SLUS_004.64");
    for (index = 0; index < 16; ++index)
    {
        effect = 0x800EE0A8 + index * 52;
        w_u32(effect, 1);
        w_u32(effect + 8, 6);
        w_u32(effect + 4, 3);
        w_u32(effect + 12, 0);
        actor = r_u32(0x800EE7EC);
        value = r_u32(r_u32(0x800DDD48 + actor * 16) + 24);
        w_u32(effect + 16, value);
        actor = r_u32(0x800EE7EC);
        value = r_u32(r_u32(0x800DDD48 + actor * 16) + 28);
        w_u32(effect + 20, value + 4200);
        actor = r_u32(0x800EE7EC);
        value = r_u32(r_u32(0x800DDD48 + actor * 16) + 32);
        w_u32(effect + 32, 8192);
        w_u32(effect + 36, 8192);
        w_u32(effect + 40, 0);
        w_u32(effect + 44, 0);
        w_u32(effect + 48, 0);
        w_u32(effect + 24, value - index * 1000 + 2000);
        w_u32(effect + 28, 16384);
    }
    w_u32(0x800EE0A8 + index * 52, 0xFFFFFFFF);
    return index * 52;
}

void func_8002a19c(uint32 object)
{
    uint32 action;
    uint32 active_action;
    FUNCTION_MARKER(0x8002A19C, "SLUS_004.64");
    action = func_80031954(object);
    active_action = func_80031954(r_u32(0x800EE7EC));
    switch (action)
    {
    case 0:
        if (active_action != 32 && active_action != 34)
            return;
        func_80031b14(object, 31, 1, 0, 0, 0);
        func_800319c0(object, 32, 1, 0, 0, 0);
        func_80032320(object, 32);
        return;
    case 32:
    case 34:
        if (active_action == 32 || active_action == 34)
        {
            func_80031b14(object, 32, 1, 0, 0, 0);
            func_80032320(object, 32);
            return;
        }
        func_80031b14(object, 33, 1, 0, 0, 0);
        break;
    case 17:
        func_80031b14(object, 19, 1, 0, 0, 0);
        break;
    case 18:
        func_80031b14(object, 20, 1, 0, 0, 0);
        break;
    case 21:
        func_80031b14(object, 0, 1, 0, 0, 0);
        func_80032320(object, 0);
        return;
    case 1:
        func_80031b14(object, 2, 1, 0, 0, 90);
        func_800319c0(object, 4, 1, 0, 0, 0);
        break;
    case 2:
        func_80031b14(object, 4, 1, 0, 0, 0);
        break;
    case 3:
        func_80031b14(object, 5, 1, 0, 0, 0);
        break;
    case 6:
        func_80031b14(object, 10, 1, 0, 0, 90);
        func_800319c0(object, 5, 1, 0, 0, 22);
        break;
    case 7:
        func_80031b14(object, 11, 1, 0, 0, 90);
        func_800319c0(object, 4, 1, 0, 0, 22);
        break;
    case 8:
        func_80031b14(object, 10, 1, 0, 0, 90);
        func_800319c0(object, 4, 1, 0, 0, 45);
        break;
    case 9:
        func_80031b14(object, 11, 1, 0, 0, 90);
        func_800319c0(object, 4, 1, 0, 0, 45);
        break;
    default:
        return;
    }
    func_800319c0(object, 0, 1, 0, 0, 0);
    func_80032320(object, 0);
}

uint32 func_8002ac0c(uint32 *queued_action)
{
    uint32 action;
    FUNCTION_MARKER(0x8002AC0C, "SLUS_004.64");
    action = r_u32(0x800CFDAC) + 4;
    func_8003222c(4, action, 1, 0, 0, 0);
    w_u32(0x800819A8, 4);
    if (queued_action != NULL)
        *queued_action = action;
    return 4;
}

void func_8002a8c8(uint32 mode)
{
    uint32 previous;
    uint32 object;
    uint32 address;
    uint32 value;
    uint32 selected;
    uint32 track;
    uint32 resource;
    uint32 position;
    uint32 base;
    uint32 duration;
    uint32 health;
    uint32 capacity;
    uint32 queued_action;
    FUNCTION_MARKER(0x8002A8C8, "SLUS_004.64");
    if (r_u32(0x800CFE24) != 0)
        return;
    previous = r_u32(0x800CF8B4);
    w_u32(0x800CFE34, mode);
    w_u32(0x800CFB24, previous);
    func_80017a74();
    VSync(2);
    DrawSync(0);
    ResetGraph(1);
    object = r_u32(0x800EE7EC);
    if (object != 1)
    {
        w_u32(0x800EE7EC, 1);
        w_u32(0x800EE7F0, object);
    }
    object = r_u32(0x800EE7F0);
    if (object != 0)
    {
        address = 0x80081998 + object * 4;
        value = r_u32(address);
        w_u32(address, 0);
        w_u32(0x800CFE84, value);
    }
    func_80031b14(r_u32(0x800EE7EC), 0, 1, 0, 0, 0);
    func_80032320(r_u32(0x800EE7EC), 0);
    selected = r_u32(0x800CF958);
    w_u32(0x800EDFB4, selected);
    if (selected <= 2)
        w_u32(0x800CFEDC, 2);
    else if (selected == 3)
        w_u32(0x800CFEDC, 1);
    else if (selected == 4)
        w_u32(0x800CFEDC, 0);
    w_u32(0x800CFB6C, 0);
    mode = r_u32(0x800CFE34);
    track = 4;
    resource = 0;
    switch (mode)
    {
    case 1:
        func_8001f4c4(4, 9);
        w_u32(0x800CF900, 200);
        resource = 54;
        w_u32(0x800CFB54, 30);
        break;
    case 2:
        func_8001f4c4(4, 10);
        w_u32(0x800CF900, 300);
        resource = 54;
        w_u32(0x800CFB54, 20);
        break;
    case 3:
        func_8001f4c4(4, 15);
        w_u32(0x800CF900, 400);
        track = 15;
        resource = 55;
        w_u32(0x800CFB54, 10);
        break;
    case 4:
        func_8001f4c4(4, 15);
        w_u32(0x800CF900, 10000);
        track = 11;
        w_u32(0x800CFB6C, 1);
        resource = 55;
        w_u32(0x800CFB54, 10);
        break;
    default:
        break;
    }
    func_8001ef90(53);
    func_8001f0b8(resource);
    func_80031c20(4, 4, 1, 0, 0, 0);
    func_80032320(4, 4);
    position = r_u32(0x800CF908);
    base = r_u32(0x800CF9E8);
    duration = r_u32(0x800CFB54);
    w_u32(0x800CFB18, 0);
    w_u32(0x800CFE24, 1);
    w_u32(0x800CFB58, 0);
    w_u32(0x800CFDAC, base);
    w_u32(0x800CFB50, duration);
    func_80020a48(4, position);
    func_8001e8b4(4);
    w_u32(0x800EE098, 1);
    w_u32(0x800819E8, 0);
    func_80028740(1, 100, 100);
    health = r_u32(0x800CF8F8);
    capacity = r_u32(0x800CF900);
    w_u32(0x800CF904, 0);
    w_u32(0x800CFB28, 0);
    w_u32(0x800CF8F4, health);
    w_u32(0x800CF8FC, capacity);
    func_80032d40(0);
    value = r_u32(0x800CF878);
    w_u32(0x800CF878, 0);
    w_u32(0x800CF914, 1);
    w_u32(0x800CFB20, 0);
    w_u32(0x800CFDF4, value);
    func_8002ac0c(&queued_action);
    func_800178b0((sint32)track, queued_action);
}

uint32 func_8001cdc4(sint32 x0, sint32 z0, sint32 x1, sint32 z1)
{
    uint32 index = 0, count = 0, offset, owner, actor, modes, kind, end;
    sint32 left, top, right, bottom, hit;
    FUNCTION_MARKER(0x8001CDC4, "SLUS_004.64");
    x0 >>= 7;
    z0 >>= 7;
    x1 >>= 7;
    z1 >>= 7;
    while (r_u32(0x8007F064 + index * 44) != 0xFFFFFFFF)
    {
        offset = index * 44;
        owner = r_u32(0x8007F084 + offset);
        actor = r_u32(0x800EE7EC);
        if (owner != actor && r_u32(0x8007F088 + offset) != 0)
        {
            modes = r_u32(0x8007F08C + offset);
            if (modes == 0 || (sint32)(modes & ((uint32)1 << (r_u32(0x800CF908) & 31))) > 0)
            {
                func_8001ba90(index, &left, &top, &right, &bottom);
                left >>= 7;
                top >>= 7;
                right >>= 7;
                bottom >>= 7;
                kind = r_u32(0x8007F068 + offset);
                hit = 0;
                if (kind == 1)
                    hit = func_80036d00(x0, z0, x1, z1, left, top, right, bottom);
                else if (kind == 2)
                    hit = func_80036a84(left, top, right, bottom, x0, z0, x1, z1);
                if (hit != 0)
                {
                    w_u32(0x800B22DC + count * 4, index);
                    ++count;
                }
                if (count >= 31)
                {
                    end = 0x800B22DC + count * 4;
                    w_u32(end, 0xFFFFFFFF);
                    return end;
                }
            }
        }
        ++index;
    }
    w_u32(0x800B22DC + count * 4, 0xFFFFFFFF);
    return 0xFFFFFFFF;
}

uint32 func_8001d064(uint32 collision)
{
    uint32 index, value;
    FUNCTION_MARKER(0x8001D064, "SLUS_004.64");
    for (index = 0; index < 32; ++index)
    {
        value = r_u32(0x800B22DC + index * 4);
        if (value == 0xFFFFFFFF)
            return 0;
        if (value == collision)
            return 1;
    }
    return 0;
}

uint32 func_80023d88(uint32 object)
{
    FUNCTION_MARKER(0x80023D88, "SLUS_004.64");
    return object + r_u32(0x800CF828) - 1;
}

void func_8002b42c(void)
{
    uint32 action, frame, kind = 0, owner, hit_index, value, object, coordinate;
    uint32 yaw, offset_x, offset_z, x, z;
    VECTOR offset;
    FUNCTION_MARKER(0x8002B42C, "SLUS_004.64");
    func_80032568(r_u32(0x800EE7EC), &action, &frame);
    if (action == 40)
        w_u32(0x800CF8F4, 0xFFFFFFFF);
    if (action == r_u32(0x800CFDAC) + 1 && r_u32(0x800CF8F4) == 0)
    {
        func_80031c20(r_u32(0x800EE7EC), action, 1, 0, 0, 0);
        func_80032320(r_u32(0x800EE7EC), r_u32(0x800CFDAC) + 1);
        w_u32(0x800CF8F4, 0xFFFFFFFF);
    }
    if (action == 40 || action == 35)
        return;
    func_80024048(1);
    if (action == 34 && frame == 14)
        func_8002c618(10, 34);
    if (action == r_u32(0x800CFDAC) && frame == 20)
        func_8002c618(15, action);
    if (action == 35 && frame == 10)
        func_8002372c(r_u32(0x800B2F78 + (r_u32(0x800CFEDC) << 6)));
    if (action == 0)
        w_u32(0x800CF914, 1);
    if (r_u32(0x800CFB28) == 0 && r_u32(0x800CF904) == 0)
    {
        if ((action == 31 && frame == 8) || (action == 32 && frame == 6) || (action == 33 && frame == 8))
        {
            if (func_8002c74c(r_u32(0x800EE7EC), action == 33 ? (uint32)-1500 : (uint32)-1000, &owner, &hit_index) == 1)
            {
                value = r_u32(0x800CFB20) + 1;
                w_u32(0x800CFB20, value);
                if ((sint32)value >= 3)
                    w_u32(0x800CFB20, 0);
                value = r_u32(0x800CF828) + 3;
                if (hit_index == value)
                    kind = action - 30;
            }
        }
        if (action == 38 && frame == 4)
        {
            func_8002ad90();
            func_8002ae78();
            object = r_u32(0x800EE7EC);
            coordinate = r_u32(0x800DDD48 + object * 16);
            yaw = r_u16(r_u32(coordinate + 68) + 18);
            func_800366a8(0, 0xD8F0, yaw << 16, 0, &offset);
            value = r_u32(0x800CF904);
            offset_x = (uint32)offset.vx;
            offset_z = (uint32)offset.vz;
            if (value == 0)
            {
                func_80024048(1);
                coordinate = r_u32(0x800DDD48 + r_u32(0x800EE7EC) * 16);
                x = r_u32(coordinate + 24);
                z = r_u32(coordinate + 32);
                func_8001cdc4((sint32)x, (sint32)z, (sint32)(x + offset_x), (sint32)(z + offset_z));
                value = func_80023d88(4);
                if (func_8001d064(value) == 1)
                    kind = 4;
            }
        }
    }
    if (action == 31)
    {
        if (frame == 8)
            func_8002372c(r_u32(0x800B2F74 + (r_u32(0x800CFEDC) << 6)));
        if (action == 31 && frame == 8)
            func_8002372c(r_u32(0x800B2F5C + (r_u32(0x800CFEDC) << 6)));
    }
    if (action == 32 && frame == 10)
        func_8002372c(r_u32(0x800B2F5C + (r_u32(0x800CFEDC) << 6)));
    if (action == 33 && frame == 6)
        func_8002372c(r_u32(0x800B2F64 + (r_u32(0x800CFEDC) << 6)));
    if (action == 38 && frame == 4)
        func_8002372c(r_u32(0x800B2F7C + (r_u32(0x800CFEDC) << 6)));
    if (action == r_u32(0x800CFDAC))
    {
        if (frame == 1)
            func_8002372c(r_u32(0x800B2F58 + (r_u32(0x800CFEDC) << 6)));
        if (action == r_u32(0x800CFDAC) && frame == 20)
            func_8002372c(r_u32(0x800B2F60 + (r_u32(0x800CFEDC) << 6)));
    }
    func_8002c45c(kind);
    func_80024048(0);
}

void func_8002bac0(void)
{
    uint32 player_action, player_frame, action, frame, owner, hit_index;
    uint32 x0, z0, step, divisor, dx, dz, velocity, acceleration, coordinate;
    uint32 value, floor_index, floor_y, base, next, timing, recovery;
    FUNCTION_MARKER(0x8002BAC0, "SLUS_004.64");
    func_80032568(r_u32(0x800EE7EC), &player_action, &player_frame);
    func_80032568(4, &action, &frame);
    func_80024048(1);
    w_u32(0x800CFB70, 0);
    if (action == r_u32(0x800CFDAC) + 13)
    {
        value = r_u32(0x800CFB40);
        x0 = r_u32(0x800CFB38);
        step = r_u32(0x800CFB48);
        dx = (value - x0) * step;
        divisor = r_u32(0x800CFB4C);
        dx = (uint32)geometry_divide(dx, divisor);
        z0 = r_u32(0x800CFB3C);
        value = r_u32(0x800CFB44);
        dz = (uint32)geometry_divide((value - z0) * step, divisor);
        coordinate = r_u32(0x800DDD88);
        velocity = r_u32(0x800CFB2C);
        value = r_u32(coordinate + 28);
        w_u32(coordinate + 28, value - velocity);
        coordinate = r_u32(0x800DDD88);
        w_u32(coordinate + 24, dx + x0);
        floor_index = r_u32(0x800CF908) * 4;
        coordinate = r_u32(0x800DDD88);
        w_u32(coordinate + 32, dz + z0);
        coordinate = r_u32(0x800DDD88);
        acceleration = r_u32(0x800CFB34);
        floor_y = r_u32(0x80081938 + floor_index);
        value = r_u32(coordinate + 28);
        w_u32(0x800CFB48, step + 1);
        w_u32(0x800CFB70, 1);
        w_u32(0x800CFB2C, velocity + acceleration);
        floor_y -= 1700;
        if ((sint32)floor_y < (sint32)value)
        {
            w_u32(coordinate + 28, floor_y);
            value = (uint32)randPSX() & 1;
            base = r_u32(0x800CFDAC);
            next = base + (value == 0 ? 16 : 9);
            func_80031fd0(4, base + 14, next, base + 4);
            coordinate = r_u32(0x800DDD88);
            value = r_u32(0x800CFB40);
            w_u32(coordinate + 24, value);
            coordinate = r_u32(0x800DDD88);
            value = r_u32(0x800CFB44);
            w_u32(coordinate + 32, value);
            coordinate = r_u32(0x800DDD88);
            w_u32(coordinate, 0);
            func_8001b21c(0x800DDD84);
            w_u32(0x800CFB2C, 0);
            w_u32(0x800CFB28, 0);
            w_u32(0x800CFB48, 0);
        }
    }
    floor_index = r_u32(0x800CF908) * 4;
    coordinate = r_u32(0x800DDD88);
    value = r_u32(coordinate + 28);
    floor_y = r_u32(0x80081938 + floor_index);
    value = floor_y - (value + 1700);
    w_u32(0x800819E8, value);
    if ((sint32)value >= 8193)
        w_u32(0x800819E8, 8192);
    value = r_u32(0x800CFE34);
    base = r_u32(0x800CFDAC);
    timing = (sint32)value < 3 ? 10 : 0;
    if (action == base + 9 && frame == timing + 12)
    {
        if (func_8002c74c(4, (uint32)-1000, &owner, &hit_index) == 1)
        {
            value = r_u32(0x800CF828);
            value += r_u32(0x800EE7EC);
            if (hit_index == value - 1)
                func_8002c2a8(player_action, (sint32)r_u32(0x800CFE34) < 3 ? 0 : 1);
        }
    }
    if (action == r_u32(0x800CFDAC) + 16 && frame == timing + 18)
    {
        if (func_8002c74c(4, (uint32)-1000, &owner, &hit_index) == 1)
        {
            value = r_u32(0x800CF828);
            value += r_u32(0x800EE7EC);
            if (hit_index == value - 1)
                func_8002c2a8(player_action, 1);
        }
    }
    if (r_u32(0x800CF8FC) == 0 && r_u32(0x800CF904) == 0 && r_u32(0x800CFB6C) == 0)
    {
        w_u32(0x800CF8E4, 0);
        w_u32(0x800CF904, 1);
        func_80031c20(4, r_u32(0x800CFDAC) + 8, 1, 0, 0, (uint32)-180);
        func_80031ee0(4, r_u32(0x800CFDAC) + 15, 28);
    }
    if (action == 28)
    {
        value = r_u32(0x800CFE34);
        w_u32(0x800EE098, 0);
        w_u32(0x800CF904, 2);
        if ((sint32)value < 3)
            func_8002372c(r_u32(0x800B2F6C + (r_u32(0x800CFEDC) << 6)));
        else
            func_8002372c(62);
    }
    recovery = 0;
    if (action == r_u32(0x800CFDAC) + 8)
    {
        if (frame == 1)
        {
            func_8002c6f4(15);
            if ((sint32)r_u32(0x800CFE34) < 3)
                func_8002372c(r_u32(0x800B2F6C + (r_u32(0x800CFEDC) << 6)));
            else
                func_8002372c(63);
        }
        if (action == r_u32(0x800CFDAC) + 8)
            recovery = 1;
    }
    if (recovery == 0)
    {
        base = r_u32(0x800CFDAC);
        if (action == base + 11 || action == base + 10)
            recovery = 1;
    }
    if (recovery != 0 && r_u32(0x800CF904) == 0 && frame == 5 && (sint32)r_u32(0x800CFE34) >= 3 && (randPSX() & 3) == 0)
    {
        func_80031c20(4, r_u32(0x800CFDAC) + 4, 1, 0, 0, 0);
        func_80031e68(4, r_u32(0x800CFDAC) + 4);
    }
    if (action == r_u32(0x800CFDAC) + 11 && frame == 1)
    {
        func_8002c6f4(10);
        if ((sint32)r_u32(0x800CFE34) < 3)
            func_8002372c(r_u32(0x800B2F6C + (r_u32(0x800CFEDC) << 6)));
        else
            func_8002372c(63);
    }
    if (action == r_u32(0x800CFDAC) + 10 && frame == 1)
    {
        func_8002c6f4(10);
        if ((sint32)r_u32(0x800CFE34) < 3)
            func_8002372c(r_u32(0x800B2F6C + (r_u32(0x800CFEDC) << 6)));
        else
            func_8002372c(64);
    }
    if (action == r_u32(0x800CFDAC) + 14 && frame == 1)
        func_8002372c(r_u32(0x800B290C + ((r_u32(0x800EE038) - 1) << 3)));
    if (action == r_u32(0x800CFDAC) + 12 && frame == 18)
        func_8002372c(r_u32(0x800B2F64 + (r_u32(0x800CFEDC) << 6)));
    if (action == r_u32(0x800CFDAC) + 15 && frame == 30)
        func_8002372c(r_u32(0x800B2F60 + (r_u32(0x800CFEDC) << 6)));
    func_80024048(0);
}

uint32 func_8002c6f4(uint32 damage)
{
    FUNCTION_MARKER(0x8002C6F4, "SLUS_004.64");
    if (r_u32(0x800CFB6C) == 0)
        w_u32(0x800CF8FC, r_u32(0x800CF8FC) - damage);
    if (r_s32(0x800CF8FC) < 0)
        w_u32(0x800CF8FC, 0);
    w_u32(0x800CFB50, 0);
    return r_u32(0x800CF8FC);
}

uint32 func_80031fd0(uint32 object, uint32 first, uint32 second, uint32 final_action)
{
    FUNCTION_MARKER(0x80031FD0, "SLUS_004.64");
    func_8003213c(object, first);
    func_80032030(object, second);
    func_80031d18(object, final_action);
    return func_80032320(object, final_action);
}

uint32 func_80031e68(uint32 object, uint32 action)
{
    FUNCTION_MARKER(0x80031E68, "SLUS_004.64");
    func_80032030(object, action);
    return func_80032320(object, action);
}

void func_80032948(uint32 object, uint32 component, uint32 delta)
{
    uint32 offset, coordinate, transform, address;
    FUNCTION_MARKER(0x80032948, "SLUS_004.64");
    if (object == 0)
        return;
    offset = object << 4;
    if (component <= 8)
    {
        coordinate = r_u32(0x800DDD48 + offset);
        switch (component)
        {
        case 0:
        case 1:
        case 2:
            address = coordinate + 24 + component * 4;
            w_u32(address, delta + r_u32(address));
            break;
        case 3:
        case 4:
        case 5:
            transform = r_u32(coordinate + 68);
            address = transform + (component - 3) * 4;
            w_u32(address, delta + r_u32(address));
            break;
        case 6:
        case 7:
        case 8:
            transform = r_u32(coordinate + 68);
            address = transform + 16 + (component - 6) * 2;
            w_u16(address, r_u16(address) + delta);
            break;
        }
    }
    func_8001b21c(0x800DDD44 + offset);
    coordinate = r_u32(0x800DDD48 + offset);
    w_u32(coordinate, 0);
}
