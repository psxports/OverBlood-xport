#include "functions.h"
#include <stdlib.h>
#include <string.h>

/* Full original bodies, pending final integration and runtime validation */
void func_80034e04(uint32 index, uint32 value)
{
    uint32 offset = index << 6;
    FUNCTION_MARKER(0x80034E04, "SLUS_004.64");
    w_u32(0x8007E064 + offset, value);
    w_u32(0x8007E0A0 + offset, 0);
}

void func_80034c78(uint32 value)
{
    FUNCTION_MARKER(0x80034C78, "SLUS_004.64");
    w_u32(0x800EDFD8, value);
}

uint32 func_800353c0(uint32 index, uint32 base, uint32 enabled)
{
    FUNCTION_MARKER(0x800353C0, "SLUS_004.64");
    return func_8003271c((index << 6) + base + 200, enabled);
}

void func_80034e4c(uint32 index)
{
    FUNCTION_MARKER(0x80034E4C, "SLUS_004.64");
    if ((sint32)index < r_s32(0x800CFEA4))
    {
        uint32 address = 0x8007E064 + (index << 6);
        if (r_u32(address) != 0xFFFFFFFF)
            w_u32(address, 2);
    }
}

void func_8002965c(uint32 object)
{
    uint32 player, actor, coordinate, original_x, original_z, mode = 0, collision;
    uint32 x, y, z, value, distance, speed, shift, angle, transform, direction;
    uint32 origin[2], reference[2], point[2];
    FUNCTION_MARKER(0x8002965C, "SLUS_004.64");
    player = 0x800DDD44 + (r_u32(0x800EE7EC) << 4);
    actor = 0x800DDD44 + (object << 4);
    func_80024048(1);
    func_80023d9c(4, 0);
    if (r_u32(0x800EDFD8) == 2)
        func_80023ec8(r_u32(0x800EE7EC), 1);
    coordinate = r_u32(actor + 4);
    original_x = r_u32(coordinate + 24);
    original_z = r_u32(coordinate + 32);
    collision = func_800299c8(object, original_x, original_z);
    if (collision != 0)
        mode = 1;
    func_80024048(0);
    x = r_u32(r_u32(player + 4) + 24);
    y = r_u32(r_u32(player + 4) + 28);
    z = r_u32(r_u32(player + 4) + 32);
    if (collision == 0)
    {
        reference[0] = r_u32(r_u32(actor + 4) + 24);
        reference[1] = r_u32(r_u32(actor + 4) + 32);
        distance = func_800367f4(x, z, reference[0], reference[1]);
        shift = r_u32(0x800EDFD0) & 31;
        value = distance << shift;
        if ((sint32)value >= 4001)
        {
            speed = func_8003248c(object);
            mode = 2;
        }
        else if ((sint32)value >= 2001)
        {
            speed = func_8003248c(object);
            mode = 1;
        }
        else
        {
            speed = 0;
            mode = 0;
        }
        if (mode != 0)
        {
            shift = r_u32(0x800EDFD0) & 31;
            value = (uint32)((sint32)speed >> shift);
            func_8001a34c(object, 0, 0, 0 - value);
        }
    }
    origin[0] = r_u32(r_u32(actor + 4) + 24);
    origin[1] = r_u32(r_u32(actor + 4) + 32);
    reference[0] = r_u32(r_u32(actor + 4) + 24);
    reference[1] = r_u32(r_u32(actor + 4) + 32);
    point[0] = r_u32(r_u32(player + 4) + 24);
    point[1] = r_u32(r_u32(player + 4) + 32);
    angle = 2048 - func_80036644(origin, reference, point);
    coordinate = r_u32(actor + 4);
    transform = r_u32(coordinate + 68);
    value = (uint32)r_s16(transform + 18);
    if (func_8002a4a4(value, angle, 128) == 0)
    {
        coordinate = r_u32(actor + 4);
        transform = r_u32(coordinate + 68);
        value = (uint32)r_s16(transform + 18);
        direction = (uint32)func_8002a570(value, angle);
        coordinate = r_u32(actor + 4);
        transform = r_u32(coordinate + 68);
        value = r_u16(transform + 18);
        mode = 0;
        w_u16(transform + 18, value + (direction << 7));
    }
    func_80024048(1);
    func_80023d9c(4, 0);
    func_80023d9c(r_u32(0x800EE7EC), 0);
    coordinate = r_u32(actor + 4);
    value = r_u32(0x800CF828);
    x = r_u32(coordinate + 24);
    z = r_u32(coordinate + 32);
    if (func_8002a5d0(x, z, object, object + value - 1) == 1)
    {
        coordinate = r_u32(actor + 4);
        w_u32(coordinate + 24, original_x);
        coordinate = r_u32(actor + 4);
        mode = 0;
        w_u32(coordinate + 32, original_z);
        func_8001b21c(actor);
    }
    func_80024048(0);
    if (mode == 0)
        func_8002a19c(object);
    else if (mode == 1)
        func_80029d00(object);
    else if (mode == 2)
        func_80029ab8(object);
}

void func_80029ab8(uint32 object)
{
    uint32 action = func_80031954(object);
    FUNCTION_MARKER(0x80029AB8, "SLUS_004.64");
    func_80031954(r_u32(0x800EE7EC));
    switch (action)
    {
    case 0:
        func_80031c20(object, 27, 1, 0, 0, 45);
        func_80031b14(object, 8, 1, 0, 0, 230);
        func_800319c0(object, 9, 1, 0, 0, 230);
        func_80032354(object, 1, 9);
        break;
    case 1:
        func_80031b14(object, 2, 1, 0, 0, 90);
        func_800319c0(object, 6, 1, 0, 0, 90);
        func_800319c0(object, 8, 1, 0, 0, 230);
        func_800319c0(object, 9, 1, 0, 0, 230);
        func_80032354(object, 1, 9);
        break;
    case 2:
        func_80031b14(object, 6, 1, 0, 0, 90);
        func_800319c0(object, 8, 1, 0, 0, 230);
        func_800319c0(object, 9, 1, 0, 0, 230);
        func_80032354(object, 1, 9);
        break;
    case 3:
        func_80031b14(object, 7, 1, 0, 0, 90);
        func_800319c0(object, 9, 1, 0, 0, 230);
        func_800319c0(object, 8, 1, 0, 0, 230);
        func_80032354(object, 1, 8);
        break;
    case 36:
        func_80031c20(object, 37, 1, 0, 0, 45);
        func_80031b14(object, 2, 1, 0, 0, 90);
        func_800319c0(object, 3, 1, 0, 0, 90);
        func_80032320(object, 3);
        break;
    default:
        break;
    }
}

void func_80029d00(uint32 object)
{
    uint32 action = func_80031954(object);
    uint32 player_action = func_80031954(r_u32(0x800EE7EC));
    uint32 first;
    FUNCTION_MARKER(0x80029D00, "SLUS_004.64");
    switch (action)
    {
    case 0:
        if (player_action == 32 || player_action == 34)
        {
            func_80031b14(object, 31, 1, 0, 0, 90);
            goto append_attack;
        }
        func_80031c20(object, 1, 1, 0, 0, 90);
        func_80031b14(object, 2, 1, 0, 0, 90);
        goto append_third;
    case 1:
        if (player_action == 32 || player_action == 34)
        {
            func_80031b14(object, 4, 1, 0, 0, 45);
            goto append_attack_pair;
        }
        if (func_8003248c(object) != 0)
            return;
        func_80031b14(object, 2, 1, 0, 0, 90);
        goto append_third;
    case 2:
    case 3:
        if (player_action != 32 && player_action != 34)
            return;
        func_80031b14(object, action == 2 ? 4 : 5, 1, 0, 0, 90);
        goto append_attack_pair;
    case 4:
    case 5:
        if (player_action == 32 || player_action == 34)
            return;
        func_80031b14(object, 1, 1, 0, 0, 90);
        goto append_second_third;
    case 8:
        func_80031b14(object, 10, 1, 0, 0, 90);
        func_800319c0(object, 2, 1, 0, 0, 90);
        func_800319c0(object, 3, 1, 0, 0, 90);
        func_80032354(object, 1, 2);
        return;
    case 9:
        func_80031b14(object, 11, 1, 0, 0, 90);
        func_800319c0(object, 3, 1, 0, 0, 90);
        func_800319c0(object, 2, 1, 0, 0, 90);
        func_80032354(object, 1, 3);
        return;
    case 17:
    case 18:
        first = action == 17 ? 19 : 20;
        goto queue_idle;
    case 21:
        func_80031b14(object, 0, 1, 0, 0, 0);
        func_800319c0(object, 1, 1, 0, 0, 90);
        goto append_second_third;
    case 32:
    case 34:
        if (player_action == 32 || player_action == 34)
        {
            func_80031c20(object, 34, 1, 0, 0, 40);
            func_80032320(object, 34);
            return;
        }
        first = 33;
        goto queue_idle;
    case 36:
        func_80031c20(object, 37, 1, 0, 0, 45);
        func_80031b14(object, 3, 1, 0, 0, 90);
        func_800319c0(object, 2, 1, 0, 0, 90);
        func_80032354(object, 1, 2);
        return;
    default:
        return;
    }
queue_idle:
    func_80031b14(object, first, 1, 0, 0, 0);
    func_800319c0(object, 0, 1, 0, 0, 0);
    func_80032320(object, 0);
    return;
append_attack_pair:
    func_800319c0(object, 31, 1, 0, 0, 90);
append_attack:
    func_800319c0(object, 34, 1, 0, 0, 90);
    func_80032354(object, 1, 34);
    return;
append_second_third:
    func_800319c0(object, 2, 1, 0, 0, 90);
append_third:
    func_800319c0(object, 3, 1, 0, 0, 90);
    func_80032354(object, 1, 3);
}

void func_8002eae4(void)
{
    MATRIX light, screen;
    uint32 selected, record, flags, coordinate, index, offset, value, limit;
    FUNCTION_MARKER(0x8002EAE4, "SLUS_004.64");
    func_8002e8c8();
    func_8004cf4c(0x800F0290);
    func_8001ab94();
    func_8002fe68(r_u32(0x800EE010));
    if (r_s32(0x800CFB80) <= 0)
    {
        selected = r_u32(0x800EE010);
        record = 0x800EA704 + (r_u32(0x800B30BC + selected * 24) << 4);
        if (r_u32(record + 0xAFC) != 0xFFFFFFFF && r_u32(record + 0xAF8) != 0)
        {
            flags = r_u32(record + 0xAF0);
            coordinate = r_u32(record + 0xAF4);
            w_u32(record + 0xAF0, flags & 0xFFFFF1FF);
            func_8004e5c8(coordinate, &light, &screen);
            GsSetLightMatrix(&light);
            func_8004c8b8(r_u32(record + 0xAF4), &screen);
            SetRotMatrix(&screen);
            SetTransMatrix(&screen);
            func_8004b4f0(record + 0xAF0, 0x800EC750 + r_u32(0x800CFDEC) * 20, 5, 0x1F800000);
        }
        w_u32(0x800EA364, r_u32(0x800EA364) & 0xFFFFF1FF);
        func_8004e5c8(r_u32(0x800EA368), &light, &screen);
        GsSetLightMatrix(&light);
        func_8004c8b8(r_u32(0x800EA368), &screen);
        SetRotMatrix(&screen);
        SetTransMatrix(&screen);
        func_8004b4f0(0x800EA364, 0x800EC750 + r_u32(0x800CFDEC) * 20, 5, 0x1F800000);
    }
    value = r_u32(0x800CFB74);
    coordinate = r_u32(0x800EA368);
    if (value == 0)
    {
        w_u8(0x800E9C74, 192);
        w_u8(0x800E9C75, 64);
        w_u8(0x800E9C76, 0);
        w_u8(0x800E9C98, 128);
        w_u8(0x800E9C99, 128);
        w_u8(0x800E9C9A, 128);
        w_u32(coordinate + 24, (uint32)-5600);
        coordinate = r_u32(0x800EA368);
        value = 4200;
    }
    else
    {
        w_u8(0x800E9C74, 128);
        w_u8(0x800E9C75, 128);
        w_u8(0x800E9C76, 128);
        w_u8(0x800E9C98, 192);
        w_u8(0x800E9C99, 64);
        w_u8(0x800E9C9A, 0);
        w_u32(coordinate + 24, (uint32)-5600);
        coordinate = r_u32(0x800EA368);
        value = 5400;
    }
    w_u32(coordinate + 28, value);
    coordinate = r_u32(0x800EA368);
    w_u32(coordinate + 32, 14000);
    func_8002ea08();
    func_8001afcc();
    func_8004cf4c(0x800EF5EC);
    for (index = 0; index < 4; ++index)
    {
        if (r_u32(0x800EB9D4 + index * 4) == 0)
            continue;
        offset = index * 36;
        value = r_u16(0x800E9C1C + offset) + 20;
        w_u16(0x800E9C1C + offset, value);
        limit = r_u32(0x800D775C + index * 8);
        if ((sint32)limit < (sint16)value)
        {
            value = r_u16(0x800D775C + index * 8);
            w_u16(0x800E9C1C + offset, value);
            if (index >= 3)
            {
                func_8001e894(0x800EA364);
                w_u32(0x800CFB78, 1);
            }
        }
        GsSortSprite(psx_addr(0x800E9C18 + offset, 36), psx_addr(0x800EC750 + r_u32(0x800CFDEC) * 20, 20), 0);
    }
}

void func_8002ee8c(void)
{
    MATRIX light, screen;
    uint32 selected, record, coordinate, flags, index, offset, value;
    uint32 first, second, third, fourth;
    FUNCTION_MARKER(0x8002EE8C, "SLUS_004.64");
    func_8002fa84(r_u32(0x800EE010));
    if (r_s32(0x800CFB80) <= 0)
    {
        func_8004cf4c(0x800F0290);
        func_8001ab94();
        selected = r_u32(0x800EE010);
        record = 0x800EA704 + (r_u32(0x800B30BC + selected * 24) << 4);
        if (r_u32(record + 0xAFC) != 0xFFFFFFFF && r_u32(record + 0xAF8) != 0)
        {
            flags = r_u32(record + 0xAF0);
            coordinate = r_u32(record + 0xAF4);
            w_u32(record + 0xAF0, flags & 0xFFFFF1FF);
            func_8004e5c8(coordinate, &light, &screen);
            GsSetLightMatrix(&light);
            func_8004c8b8(r_u32(record + 0xAF4), &screen);
            SetRotMatrix(&screen);
            SetTransMatrix(&screen);
            func_8004b4f0(record + 0xAF0, 0x800EC750 + r_u32(0x800CFDEC) * 20, 5, 0x1F800000);
        }
        func_8001afcc();
        func_8004cf4c(0x800EF5EC);
    }
    for (index = 0; index < 4; ++index)
    {
        if (r_u32(0x800EB9D4 + index * 4) == 0)
            continue;
        offset = index * 36;
        value = r_u16(0x800E9C1C + offset) + 20;
        w_u16(0x800E9C1C + offset, value);
        if ((sint16)value >= -129)
            w_u16(0x800E9C1C + offset, (uint32)-130);
        GsSortSprite(psx_addr(0x800E9C18 + offset, 36), psx_addr(0x800EC750 + r_u32(0x800CFDEC) * 20, 20), 0);
    }
    first = r_u16(0x800DEF6E);
    second = r_u16(0x800DEF92);
    third = r_u16(0x800EC39A);
    fourth = r_u16(0x800EC3BE);
    first -= 5;
    w_u16(0x800DEF6E, first);
    second -= 5;
    w_u16(0x800DEF92, second);
    third -= 5;
    w_u16(0x800EC39A, third);
    fourth -= 5;
    w_u16(0x800EC3BE, fourth);
    if ((sint16)first < 70)
        w_u16(0x800DEF6E, 70);
    if ((sint16)second < 92)
        w_u16(0x800DEF92, 92);
    if ((sint16)third < 70)
        w_u16(0x800EC39A, 70);
    if ((sint16)fourth < 92)
        w_u16(0x800EC3BE, 92);
    GsSortSprite(psx_addr(0x800DEF68, 36), psx_addr(0x800EC750 + r_u32(0x800CFDEC) * 20, 20), 0);
    GsSortSprite(psx_addr(0x800DEF8C, 36), psx_addr(0x800EC750 + r_u32(0x800CFDEC) * 20, 20), 0);
    GsSortSprite(psx_addr(0x800EC394, 36), psx_addr(0x800EC750 + r_u32(0x800CFDEC) * 20, 20), 0);
    GsSortSprite(psx_addr(0x800EC3B8, 36), psx_addr(0x800EC750 + r_u32(0x800CFDEC) * 20, 20), 0);
}

uint32 func_8001820c(const uint32 *data)
{
    uint32 sum = 0, index;
    FUNCTION_MARKER(0x8001820C, "SLUS_004.64");
    for (index = 0; index < 0x57E; ++index)
        sum += data[index];
    return sum == data[0x57E];
}

uint32 func_8001de3c(uint32 camera, uint32 mode, uint32 parameter, uint32 duration)
{
    uint32 offset, floor, index, divisor, first_step, step, value;
    uint32 target[6];
    FUNCTION_MARKER(0x8001DE3C, "SLUS_004.64");
    w_u32(0x800EDFD8, 3);
    w_u32(0x800CF88C, mode);
    w_u32(0x800CF884, camera);
    w_u32(0x800CF8A8, duration);
    w_u32(0x800CF888, parameter);
    if (mode == 0)
        return 3;
    if ((sint32)mode < 0)
        return 1;
    if (mode >= 3)
        return 0;
    if (duration == 0)
        w_u32(0x800CF8A8, 1);
    offset = r_u32(0x800CF884) * 56;
    index = r_u32(0x800801A0 + offset);
    target[0] = r_u32(0x800801A4 + offset);
    target[1] = r_u32(0x800801A8 + offset);
    floor = r_u32(0x80081938 + index * 4);
    target[2] = r_u32(0x800801AC + offset);
    target[3] = r_u32(0x800801B0 + offset);
    target[4] = r_u32(0x800801B4 + offset);
    target[5] = r_u32(0x800801B8 + offset);
    target[1] += floor;
    target[4] += floor;
    value = r_u32(0x800EF5EC);
    divisor = r_u32(0x800CF8A8);
    first_step = (uint32)geometry_divide(target[0] - value, divisor);
    for (index = 1; index < 6; ++index)
    {
        value = r_u32(0x800EF5EC + index * 4);
        step = (uint32)geometry_divide(target[index] - value, divisor);
        if (index < 5)
            w_u32(0x800CF890 + index * 4, step);
    }
    w_u32(0x800CF890, first_step);
    w_u32(0x800CF8A4, step);
    if (first_step == 0)
        w_u32(0x800EF5EC, target[0]);
    for (index = 1; index < 6; ++index)
    {
        value = r_u32(0x800CF890 + index * 4);
        if (value == 0)
            w_u32(0x800EF5EC + index * 4, target[index]);
    }
    return value;
}

void func_8001f168(uint32 value)
{
    FUNCTION_MARKER(0x8001F168, "SLUS_004.64");
    w_u32(0x800CF85C, value);
}

void func_800228c4(uint32 value)
{
    FUNCTION_MARKER(0x800228C4, "SLUS_004.64");
    w_u32(0x800CF820, value);
}

uint32 func_800287cc(void)
{
    FUNCTION_MARKER(0x800287CC, "SLUS_004.64");
    return r_u32(0x800CF8F4);
}

uint32 func_800385e8(void)
{
    FUNCTION_MARKER(0x800385E8, "SLUS_004.64");
    return r_u32(0x800CF95C);
}

void func_8002912c(uint32 object)
{
    uint32 timer, action, choice, player, actor, coordinate, collision_index;
    uint32 original_x, original_z, escape_x, escape_z, x, z, value, speed;
    uint32 rx, ry, rz, target_x, target_z, angle, transform, direction;
    uint32 origin[2], reference[2], point[2];
    sint32 dx, dz;
    VECTOR offset;
    FUNCTION_MARKER(0x8002912C, "SLUS_004.64");
    timer = r_u32(0x800CFAF8) - 1;
    w_u32(0x800CFAF8, timer);
    if ((sint32)timer < 0)
    {
        action = func_80031954(object);
        choice = (uint32)randPSX() & 1;
        func_8002372c(choice == 0 ? 57 : 59);
        if (action == 26)
        {
            func_80031c20(object, choice == 0 ? 41 : 40, 1, 0, 0, 0);
            func_80031b14(object, 26, 1, 0, 0, 0);
            func_80032320(object, 26);
        }
        w_u32(0x800CFAF8, (uint32)randPSX() & 0x1FF);
    }
    player = 0x800DDD44 + (r_u32(0x800EE7EC) << 4);
    actor = 0x800DDD44 + (object << 4);
    func_80024048(1);
    if (r_u32(0x800EDFD8) == 2)
        func_80023ec8(r_u32(0x800EE7EC), 1);
    collision_index = r_u32(0x800CF828);
    coordinate = r_u32(actor + 4);
    original_x = r_u32(coordinate + 24);
    original_z = r_u32(coordinate + 32);
    if (func_8002a5d0(original_x, original_z, object, object + collision_index - 1) == 1)
    {
        if (func_8002a60c(r_u32(0x800EE7EC), object, &escape_x, &escape_z, 1800, 0) == 0)
        {
            speed = 220 >> (r_u32(0x800EDFD0) & 31);
            coordinate = r_u32(actor + 4);
            x = r_u32(coordinate + 24);
            z = r_u32(coordinate + 32);
            dx = (sint32)(escape_x - x) >> 4;
            dz = (sint32)(escape_z - z) >> 4;
            if ((sint32)speed < dx)
                dx = (sint32)speed;
            if ((sint32)speed < dz)
                dz = (sint32)speed;
            w_u32(coordinate + 24, x + (uint32)dx);
            coordinate = r_u32(actor + 4);
            z = r_u32(coordinate + 32);
            w_u32(coordinate + 32, z + (uint32)dz);
        }
    }
    func_80024048(0);
    origin[0] = r_u32(r_u32(player + 4) + 24);
    origin[1] = r_u32(r_u32(player + 4) + 32);
    reference[0] = r_u32(r_u32(actor + 4) + 24);
    reference[1] = r_u32(r_u32(actor + 4) + 32);
    value = func_800367f4(origin[0], origin[1], reference[0], reference[1]);
    speed = (sint32)value < 1501 ? 0 : 220 >> (r_u32(0x800EDFD0) & 31);
    if (speed != 0)
    {
        rx = r_u16(r_u32(r_u32(player + 4) + 68) + 16);
        ry = r_u16(r_u32(r_u32(player + 4) + 68) + 18);
        rz = r_u16(r_u32(r_u32(player + 4) + 68) + 20);
        func_800366a8(0, 1000, rx | (ry << 16), rz, &offset);
        coordinate = r_u32(player + 4);
        target_x = (uint32)offset.vx + r_u32(coordinate + 24);
        coordinate = r_u32(player + 4);
        offset.vy = (sint32)((uint32)offset.vy + r_u32(coordinate + 28));
        coordinate = r_u32(player + 4);
        target_z = (uint32)offset.vz + r_u32(coordinate + 32);
        coordinate = r_u32(actor + 4);
        x = r_u32(coordinate + 24);
        z = r_u32(coordinate + 32);
        dx = (sint32)(target_x - x) >> 4;
        dz = (sint32)(target_z - z) >> 4;
        if ((sint32)speed < dx)
            dx = (sint32)speed;
        if ((sint32)speed < dz)
            dz = (sint32)speed;
        w_u32(coordinate + 24, x + (uint32)dx);
        coordinate = r_u32(actor + 4);
        z = r_u32(coordinate + 32);
        w_u32(coordinate + 32, z + (uint32)dz);
    }
    origin[0] = r_u32(r_u32(actor + 4) + 24);
    origin[1] = r_u32(r_u32(actor + 4) + 32);
    reference[0] = r_u32(r_u32(actor + 4) + 24);
    reference[1] = r_u32(r_u32(actor + 4) + 32) + 10000;
    point[0] = r_u32(r_u32(player + 4) + 24);
    point[1] = r_u32(r_u32(player + 4) + 32);
    angle = 2048 - func_80036644(origin, reference, point);
    transform = r_u32(r_u32(actor + 4) + 68);
    value = (uint32)r_s16(transform + 18);
    if (func_8002a4a4(value, angle, 64) == 0)
    {
        transform = r_u32(r_u32(actor + 4) + 68);
        value = (uint32)r_s16(transform + 18);
        direction = (uint32)func_8002a570(value, angle);
        transform = r_u32(r_u32(actor + 4) + 68);
        value = r_u16(transform + 18);
        w_u16(transform + 18, value + (direction << 6));
    }
    func_80024048(1);
    func_80023d9c(r_u32(0x800EE7EC), 0);
    coordinate = r_u32(actor + 4);
    collision_index = r_u32(0x800CF828);
    x = r_u32(coordinate + 24);
    z = r_u32(coordinate + 32);
    if (func_8002a5d0(x, z, object, object + collision_index - 1) == 1)
    {
        w_u32(r_u32(actor + 4) + 24, original_x);
        w_u32(r_u32(actor + 4) + 32, original_z);
        func_8001b21c(actor);
    }
    func_80024048(0);
}

uint32 func_8001d0b0(uint32 object, uint32 distance, uint32 steering, uint32 *output_owner)
{
    uint32 actor, coordinate, rx, ry, rz, x, z, event, owner, hit_index;
    uint32 left_x, left_z, right_x, right_z, transform, turn, result;
    VECTOR offset;
    FUNCTION_MARKER(0x8001D0B0, "SLUS_004.64");
    actor = 0x800DDD44 + (object << 4);
    *output_owner = 0;
    rx = r_u16(r_u32(r_u32(actor + 4) + 68) + 16);
    ry = r_u16(r_u32(r_u32(actor + 4) + 68) + 18);
    rz = r_u16(r_u32(r_u32(actor + 4) + 68) + 20);
    func_800366a8(0, distance & 0xFFFF, rx | (ry << 16), rz, &offset);
    coordinate = r_u32(actor + 4);
    x = r_u32(coordinate + 24);
    z = r_u32(coordinate + 32);
    result = func_8001be34((sint32)((uint32)offset.vx + x), (sint32)((uint32)offset.vz + z), 650, &event, &owner, &hit_index, 0xFFFFFFFF, r_u32(0x800EE7EC));
    if (result == 0)
    {
        *output_owner = owner;
        return 0;
    }
    if (steering == 0)
        return 1;
    rx = r_u16(r_u32(r_u32(actor + 4) + 68) + 16);
    ry = (r_u16(r_u32(r_u32(actor + 4) + 68) + 18) - 800) & 0xFFFF;
    rz = r_u16(r_u32(r_u32(actor + 4) + 68) + 20);
    func_800366a8(0, distance & 0xFFFF, rx | (ry << 16), rz, &offset);
    left_x = (uint32)offset.vx;
    left_z = (uint32)offset.vz;
    rx = r_u16(r_u32(r_u32(actor + 4) + 68) + 16);
    ry = (r_u16(r_u32(r_u32(actor + 4) + 68) + 18) + 800) & 0xFFFF;
    rz = r_u16(r_u32(r_u32(actor + 4) + 68) + 20);
    func_800366a8(0, distance & 0xFFFF, rx | (ry << 16), rz, &offset);
    coordinate = r_u32(actor + 4);
    right_x = (uint32)offset.vx;
    x = r_u32(coordinate + 24);
    z = r_u32(coordinate + 32);
    right_z = (uint32)offset.vz;
    result = func_8001be34((sint32)(left_x + x), (sint32)(left_z + z), 650, &event, &owner, &hit_index, 0xFFFFFFFF, r_u32(0x800EE7EC));
    if (result == 0)
    {
        transform = r_u32(r_u32(actor + 4) + 68);
        turn = r_u16(transform + 18) - 60;
    }
    else
    {
        coordinate = r_u32(actor + 4);
        x = r_u32(coordinate + 24);
        z = r_u32(coordinate + 32);
        result = func_8001be34((sint32)(right_x + x), (sint32)(right_z + z), 650, &event, &owner, &hit_index, 0xFFFFFFFF, r_u32(0x800EE7EC));
        if (result != 0)
            return 1;
        transform = r_u32(r_u32(actor + 4) + 68);
        turn = r_u16(transform + 18) + 60;
    }
    w_u16(transform + 18, turn);
    w_u32(r_u32(actor + 4), 0);
    func_8001b21c(actor);
    *output_owner = owner;
    return 1;
}

void func_80027d88(uint32 mode, uint32 object)
{
    uint32 actor, action, blocked, keys, shift, vertical = 0;
    uint32 coordinate, transform, value, change, limit, height;
    FUNCTION_MARKER(0x80027D88, "SLUS_004.64");
    actor = 0x800DDD44 + (object << 4);
    action = func_80031954(object);
    blocked = r_u32(0x800CF870);
    w_u32(0x800CFEBC, 0);
    w_u32(0x800CFEC4, 0);
    w_u32(0x800CFED4, 0);
    shift = (mode << 4) & 31;
    if (blocked != 0)
    {
        keys = r_u32(0x800CF934);
        if ((keys & (blocked << shift)) != 0)
            w_u32(0x800CF934, keys & ~blocked);
        else
            w_u32(0x800CF870, 0);
    }
    keys = r_u32(0x800CF934);
    if ((keys & ((uint32)0x800 << shift)) != 0 && (keys & ((uint32)0x20 << shift)) != 0)
        func_800265ec(0);
    if ((r_u32(0x800CF934) & ((uint32)4 << shift)) != 0)
    {
        func_8002372c(1);
        func_80014ef8(1);
        w_u32(0x800CF870, r_u32(0x800CF870) | 4);
        return;
    }
    if ((r_u32(0x800CF934) & ((uint32)8 << shift)) != 0)
    {
        func_80025374();
        return;
    }
    if ((r_u32(0x800CF934) & ((uint32)0x100 << shift)) != 0)
    {
        func_8002540c();
        w_u32(0x800CF870, r_u32(0x800CF870) | 0x100);
        return;
    }
    if (r_u32(0x800CF7A4) != 0)
        func_800252ec();
    if ((r_u32(0x800CF934) & ((uint32)0x8000 << shift)) != 0)
    {
        transform = r_u32(r_u32(actor + 4) + 68);
        w_u16(transform + 18, r_u16(transform + 18) - 60);
    }
    if ((r_u32(0x800CF934) & ((uint32)0x2000 << shift)) != 0)
    {
        transform = r_u32(r_u32(actor + 4) + 68);
        w_u16(transform + 18, r_u16(transform + 18) + 60);
    }
    keys = r_u32(0x800CF934);
    if ((keys & ((uint32)1 << shift)) != 0)
    {
        if ((keys & ((uint32)0x4000 << shift)) != 0)
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
                change = r_u32(0x800CF9D8);
                value += change;
                limit = r_u32(0x800EDFE4);
                w_u32(0x800CF9D4, value);
                if ((sint32)limit < (sint32)value)
                    w_u32(0x800CF9D4, limit);
                coordinate = r_u32(actor + 4);
                height = r_u32(0x800CF9D0);
                value = r_u32(coordinate + 28) + height;
                value += r_u32(0x800CF9D4);
                w_u32(0x800EF5F0, value);
            }
            vertical = 1;
        }
        keys = r_u32(0x800CF934);
        if ((keys & ((uint32)1 << shift)) != 0 && (keys & ((uint32)0x1000 << shift)) != 0)
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
                change = r_u32(0x800CF9D8);
                value -= change;
                limit = r_u32(0x800EDFE8);
                w_u32(0x800CF9D4, value);
                if ((sint32)value < (sint32)limit)
                    w_u32(0x800CF9D4, limit);
                coordinate = r_u32(actor + 4);
                height = r_u32(0x800CF9D0);
                value = r_u32(coordinate + 28) + height;
                value += r_u32(0x800CF9D4);
                w_u32(0x800EF5F0, value);
            }
            vertical = 1;
        }
    }
    if (vertical == 0)
    {
        if ((r_u32(0x800CF934) & ((uint32)0x1000 << shift)) != 0)
            w_u32(0x800CFED4, 150);
        if ((r_u32(0x800CF934) & ((uint32)0x4000 << shift)) != 0)
            w_u32(0x800CFED4, (uint32)-150);
        keys = r_u32(0x800CF934);
        if ((keys & ((uint32)0x20 << shift)) != 0 && (keys & ((uint32)0x1000 << shift)) != 0)
            w_u32(0x800CFED4, 220);
    }
    if ((r_u32(0x800CF934) & ((uint32)0x10 << shift)) != 0 && action == 26)
    {
        func_80031c20(object, 40, 1, 0, 0, 0);
        func_80031b14(object, 26, 1, 0, 0, 0);
        func_80032320(object, 26);
    }
    if ((r_u32(0x800CF934) & ((uint32)0x80 << shift)) != 0 && action == 26)
    {
        func_80031c20(object, 41, 1, 0, 0, 0);
        func_80031b14(object, 26, 1, 0, 0, 0);
        func_80032320(object, 26);
    }
    if ((r_u32(0x800CF934) & ((uint32)0x40 << shift)) != 0)
    {
        if (r_u32(0x800CFE0C) == 0)
        {
            value = func_8001d480(object, 0);
            w_u32(0x800CFE0C, value);
        }
        if (r_u32(0x800CFE1C) == 0)
        {
            value = func_8001d480(object, 0xFF4C);
            w_u32(0x800CFE1C, value);
        }
    }
}

uint32 func_8001d88c(uint32 object, uint32 distance, uint32 ignored_index, uint32 *hit_index)
{
    uint32 actor, radius, rx, ry, rz, coordinate, x, z, event, owner;
    VECTOR offset;
    FUNCTION_MARKER(0x8001D88C, "SLUS_004.64");
    actor = 0x800DDD44 + (object << 4);
    radius = r_u32(0x800EDFD0) == 0 ? 650 : 325;
    rx = r_u16(r_u32(r_u32(actor + 4) + 68) + 16);
    ry = r_u16(r_u32(r_u32(actor + 4) + 68) + 18);
    rz = r_u16(r_u32(r_u32(actor + 4) + 68) + 20);
    func_800366a8(0, distance & 0xFFFF, rx | (ry << 16), rz, &offset);
    coordinate = r_u32(actor + 4);
    x = r_u32(coordinate + 24);
    z = r_u32(coordinate + 32);
    func_8001be34((sint32)((uint32)offset.vx + x), (sint32)((uint32)offset.vz + z), (sint32)radius, &event, &owner, hit_index, ignored_index, r_u32(0x800EE7EC));
    return owner;
}

uint32 func_8001d9e4(uint32 object, uint32 distance, uint32 ignored_index)
{
    uint32 actor, radius, rx, ry, rz, coordinate, x, z, event, owner, hit_index;
    VECTOR offset;
    FUNCTION_MARKER(0x8001D9E4, "SLUS_004.64");
    actor = 0x800DDD44 + (object << 4);
    radius = r_u32(0x800EDFD0) == 0 ? 650 : 325;
    rx = r_u16(r_u32(r_u32(actor + 4) + 68) + 16);
    ry = r_u16(r_u32(r_u32(actor + 4) + 68) + 18);
    rz = r_u16(r_u32(r_u32(actor + 4) + 68) + 20);
    func_800366a8(0, distance & 0xFFFF, rx | (ry << 16), rz, &offset);
    coordinate = r_u32(actor + 4);
    x = r_u32(coordinate + 24);
    z = r_u32(coordinate + 32);
    return func_8001be34((sint32)((uint32)offset.vx + x), (sint32)((uint32)offset.vz + z), (sint32)radius, &event, &owner, &hit_index, ignored_index, r_u32(0x800EE7EC));
}

uint32 func_80019e24(uint32 object, uint32 collision, uint32 x, uint32 y, uint32 z, uint32 action)
{
    uint32 actor, distance, result = 1, output_owner, owner, hit_index, blocked;
    uint32 coordinate, rx, ry, rz, axis, flags, delta, value, moved;
    uint32 original[3], original_other[3], step[3];
    VECTOR offset;
    FUNCTION_MARKER(0x80019E24, "SLUS_004.64");
    w_u32(0x800CF824, 0);
    distance = 0 - z;
    actor = 0x800DDD44 + (object << 4);
    if (action - 16 < 2 || action - 18 < 2 || action == 20)
        collision = 0;
    else
        w_u32(0x800CF824, 0);
    if (r_u32(0x800EDFD0) != 0)
    {
        x = (uint32)((sint32)x >> 1);
        y = (uint32)((sint32)y >> 1);
        distance = (uint32)((sint32)distance >> 1);
    }
    if (x != 0 || distance != 0)
    {
        if (func_8001d0b0(object, distance, collision, &output_owner) == 0)
        {
            func_8001a34c(object, 0, 0, distance);
            result = 1;
        }
        else
        {
            if (action - 17 < 2)
            {
                /* The preceding call preserves the caller's movement result in the reused index slot */
                hit_index = result;
                owner = func_8001d88c(object, distance, 0xFFFFFFFF, &hit_index);
                blocked = func_8001d9e4(object, distance, hit_index);
                if (blocked == 0 && owner != 0 && r_u32(0x800EC030 + owner * 4) != 0)
                {
                    coordinate = r_u32(actor + 4);
                    original[0] = r_u32(coordinate + 24);
                    original[1] = r_u32(coordinate + 28);
                    original[2] = r_u32(coordinate + 32);
                    coordinate = r_u32(0x800DDD48 + (owner << 4));
                    original_other[0] = r_u32(coordinate + 24);
                    original_other[1] = r_u32(coordinate + 28);
                    original_other[2] = r_u32(coordinate + 32);
                    rx = r_u16(r_u32(r_u32(actor + 4) + 68) + 16);
                    ry = r_u16(r_u32(r_u32(actor + 4) + 68) + 18);
                    rz = r_u16(r_u32(r_u32(actor + 4) + 68) + 20);
                    func_800366a8(0, distance & 0xFFFF, rx | (ry << 16), rz, &offset);
                    step[0] = (uint32)offset.vx;
                    step[1] = (uint32)offset.vy;
                    step[2] = (uint32)offset.vz;
                    moved = 0;
                    for (axis = 0; axis < 3; ++axis)
                    {
                        flags = r_u32(0x800EC030 + owner * 4);
                        if (((flags >> axis) & 1) != 0)
                        {
                            coordinate = r_u32(0x800DDD48 + (owner << 4));
                            delta = step[axis];
                            value = r_u32(coordinate + 24 + axis * 4);
                            w_u32(coordinate + 24 + axis * 4, value + delta);
                            coordinate = r_u32(actor + 4);
                            value = r_u32(coordinate + 24 + axis * 4);
                            moved = 1;
                            w_u32(coordinate + 24 + axis * 4, value + delta);
                        }
                    }
                    if (func_8001c510(hit_index, 0, 0, &output_owner, 0xFFFFFFFF, object) == 1)
                    {
                        for (axis = 0; axis < 3; ++axis)
                        {
                            coordinate = r_u32(0x800DDD48 + (owner << 4));
                            if (axis == 2)
                                moved = 0;
                            w_u32(coordinate + 24 + axis * 4, original_other[axis]);
                        }
                    }
                    if (func_8001d9e4(object, 0, 0xFFFFFFFF) == 1)
                    {
                        for (axis = 0; axis < 3; ++axis)
                            w_u32(r_u32(actor + 4) + 24 + axis * 4, original[axis]);
                    }
                    value = 0;
                    if (moved != 0)
                        value = r_u32(0x800EC604 + owner * 4);
                    w_u32(0x800CF824, value);
                    if (moved != 0)
                        func_8001b21c(0x800DDD44 + (owner << 4));
                }
                w_u32(0x800CF8C4, owner);
            }
            result = 0;
        }
    }
    w_u32(r_u32(actor + 4), 0);
    func_8001b21c(actor);
    return result;
}

uint32 func_8001bc50(uint32 index, sint32 *x0, sint32 *z0, sint32 *x1, sint32 *z1, uint32 offset_x, uint32 offset_z)
{
    uint32 offset, result;
    sint32 transform, first_x, first_y, first_z, second_x, second_y, second_z;
    FUNCTION_MARKER(0x8001BC50, "SLUS_004.64");
    offset = index * 44;
    transform = r_s32(0x8007F084 + offset);
    if (transform == 0 || transform >= r_s32(0x800CFF2C))
    {
        *x0 = (sint32)(offset_x + r_u32(0x8007F06C + offset));
        *z0 = (sint32)(offset_z + r_u32(0x8007F070 + offset));
        *x1 = (sint32)(offset_x + r_u32(0x8007F074 + offset));
        result = offset_z + r_u32(0x8007F078 + offset);
    }
    else
    {
        first_x = (sint32)(offset_x + r_u32(0x8007F06C + offset));
        first_y = 0;
        first_z = (sint32)(offset_z + r_u32(0x8007F070 + offset));
        second_x = (sint32)(offset_x + r_u32(0x8007F074 + offset));
        second_y = 0;
        second_z = (sint32)(offset_z + r_u32(0x8007F078 + offset));
        func_8001b6cc(transform, &first_x, &first_y, &first_z, &second_x, &second_y, &second_z);
        *x0 = first_x;
        *z0 = first_z;
        *x1 = second_x;
        result = (uint32)second_z;
    }
    *z1 = (sint32)result;
    return result;
}

sint32 func_80036da4(sint32 x0, sint32 z0, sint32 x1, sint32 z1, sint32 left, sint32 top, sint32 right, sint32 bottom)
{
    uint32 diameter, center_x, center_z, radius;
    FUNCTION_MARKER(0x80036DA4, "SLUS_004.64");
    diameter = func_80036858((uint32)x0, (uint32)z0, (uint32)x1, (uint32)z1);
    center_x = (uint32)((sint32)((uint32)x0 + (uint32)x1) >> 1);
    center_z = (uint32)((sint32)((uint32)z0 + (uint32)z1) >> 1);
    radius = (uint32)((sint32)diameter >> 1);
    return func_8003716c(center_x, center_z, radius, (uint32)left, (uint32)top, (uint32)right, (uint32)bottom) != 0;
}

sint32 func_80036e48(sint32 x0, sint32 z0, sint32 x1, sint32 z1, sint32 left, sint32 top, sint32 right, sint32 bottom)
{
    uint32 diameter, center_x, center_z, radius;
    FUNCTION_MARKER(0x80036E48, "SLUS_004.64");
    diameter = func_80036858((uint32)x0, (uint32)z0, (uint32)x1, (uint32)z1);
    center_x = (uint32)((sint32)((uint32)x0 + (uint32)x1) >> 1);
    center_z = (uint32)((sint32)((uint32)z0 + (uint32)z1) >> 1);
    radius = (uint32)((sint32)diameter >> 1);
    return func_80037200(center_x, center_z, radius, (uint32)left, (uint32)top, (uint32)right, (uint32)bottom) != 0;
}

sint32 func_800368ac(sint32 x0, sint32 z0, sint32 x1, sint32 z1, sint32 left, sint32 top, sint32 right, sint32 bottom)
{
    sint32 first_left, first_right, first_top, first_bottom;
    sint32 second_left, second_right, second_top, second_bottom;
    FUNCTION_MARKER(0x800368AC, "SLUS_004.64");
    first_left = x1 < x0 ? x1 : x0;
    first_right = x1 < x0 ? x0 : x1;
    first_top = z1 < z0 ? z1 : z0;
    first_bottom = z1 < z0 ? z0 : z1;
    second_left = right < left ? right : left;
    second_right = right < left ? left : right;
    second_top = bottom < top ? bottom : top;
    second_bottom = bottom < top ? top : bottom;
    if (second_left >= first_left && first_right >= second_left && second_top >= first_top && first_bottom >= second_top)
        return 1;
    if (second_right >= first_left && first_right >= second_right && second_bottom >= first_top && first_bottom >= second_bottom)
        return 1;
    if (second_left >= first_left && first_right >= second_left && second_bottom >= first_top && first_bottom >= second_bottom)
        return 1;
    if (second_right >= first_left && first_right >= second_right && second_top >= first_top && first_bottom >= second_top)
        return 1;
    if (first_left >= second_left && second_right >= first_left && first_top >= second_top && second_bottom >= first_top)
        return 1;
    if (first_right >= second_left && second_right >= first_right && first_bottom >= second_top && second_bottom >= first_bottom)
        return 1;
    if (first_left >= second_left && second_right >= first_left && first_bottom >= second_top && second_bottom >= first_bottom)
        return 1;
    if (first_right >= second_left && second_right >= first_right && first_top >= second_top && second_bottom >= first_top)
        return 1;
    return 0;
}

uint32 func_8001c510(uint32 index, uint32 x, uint32 z, uint32 *owner, uint32 ignored_index, uint32 ignored_owner)
{
    sint32 x0, z0, x1, z1, left, top, right, bottom, hit;
    uint32 kind, candidate_kind, scan = 0, offset, candidate_owner, modes;
    FUNCTION_MARKER(0x8001C510, "SLUS_004.64");
    func_8001bc50(index, &x0, &z0, &x1, &z1, x, z);
    x0 >>= 7;
    z0 >>= 7;
    x1 >>= 7;
    z1 >>= 7;
    kind = r_u32(0x8007F068 + index * 44);
    while (r_u32(0x8007F064 + scan * 44) != 0xFFFFFFFF)
    {
        if (scan == ignored_index || scan == index)
            goto next_candidate;
        offset = scan * 44;
        if (r_u32(0x8007F088 + offset) == 0)
            goto next_candidate;
        candidate_owner = r_u32(0x8007F084 + offset);
        if (candidate_owner == ignored_owner && ignored_owner != 0xFFFFFFFF)
            goto next_candidate;
        modes = r_u32(0x8007F08C + offset);
        if (modes != 0 && (sint32)(modes & ((uint32)1 << (r_u32(0x800CF908) & 31))) <= 0)
            goto next_candidate;
        func_8001ba90(scan, &left, &top, &right, &bottom);
        left >>= 7;
        top >>= 7;
        right >>= 7;
        bottom >>= 7;
        *owner = scan;
        if (kind > 2)
            goto next_candidate;
        candidate_kind = r_u32(0x8007F068 + offset);
        if (candidate_kind > 2)
            goto next_candidate;
        if (kind == 0)
        {
            if (candidate_kind == 0)
                hit = func_80036ca0(x0, z0, x1, z1, left, top, right, bottom);
            else if (candidate_kind == 1)
                hit = func_80036d00(x0, z0, x1, z1, left, top, right, bottom);
            else
                hit = func_80036a84(left, top, right, bottom, x0, z0, x1, z1);
        }
        else if (kind == 1)
        {
            if (candidate_kind == 0)
                hit = func_80036d00(x0, z0, x1, z1, left, top, right, bottom);
            else if (candidate_kind == 1)
                hit = func_80036da4(x0, z0, x1, z1, left, top, right, bottom);
            else
                hit = func_80036e48(x0, z0, x1, z1, left, top, right, bottom);
        }
        else
        {
            if (candidate_kind == 0)
                hit = func_80036a84(x0, z0, x1, z1, left, top, right, bottom);
            else if (candidate_kind == 1)
                hit = func_80036e48(left, top, right, bottom, x0, z0, x1, z1);
            else
                hit = func_800368ac(x0, z0, x1, z1, left, top, right, bottom);
        }
        if (hit != 0)
            return 1;
next_candidate:
        ++scan;
    }
    *owner = 0;
    return 0;
}

void func_80016bf8(void)
{
    uint32 selected, object, old_object, next_object, offset, coordinate, transform;
    uint32 level, position, enabled, action, value, root, axis, message;
    FUNCTION_MARKER(0x80016BF8, "SLUS_004.64");
    if (r_u32(0x800EDFC0) == 0)
    {
        selected = r_u32(0x800EE7F0);
        offset = selected * 4;
        if (r_u32(0x80081978 + offset) == 0)
            goto unavailable;
        if (r_u32(0x800EE068 + offset) == 0)
            goto unavailable;
        func_8002372c(1);
        if (r_u32(0x800EE7EC) != 3)
        {
            func_80031b14(r_u32(0x800EE7EC), 0, 1, 0, 0, 0);
            func_80032320(r_u32(0x800EE7EC), 0);
        }
        else
        {
            func_80031b14(r_u32(0x800EE7EC), 26, 1, 0, 0, 0);
            func_80032320(r_u32(0x800EE7EC), 26);
        }
        next_object = r_u32(0x800EE7F0);
        old_object = r_u32(0x800EE7EC);
        w_u32(0x800EE7EC, next_object);
        w_u32(0x800EE7F0, old_object);
        func_8001e8b4(old_object);
        if (r_u32(0x800EDFD8) == 2)
            func_8001e8d8(r_u32(0x800EE7EC));
        value = r_u32(0x800EE7F0);
        action = value - 1 < 2 ? 1 : 3;
        selected = r_u32(0x800EE7F0);
        w_u32(0x80081998 + selected * 4, action);
        func_8001dc98();
        func_80015100();
        func_80032d68(r_u32(0x800CFA6C), 8);
        func_80014ffc();
        return;
    }
    selected = r_u32(0x800EDFC4);
    if (r_u32(0x800EE068 + selected * 4) == 0)
        goto unavailable;
    selected = r_u32(0x800EDFC4);
    object = r_u32(0x800EE7EC);
    offset = (selected - 1) * 44;
    level = r_u32(0x800EE728 + offset);
    position = r_u32(0x800EE72C + offset);
    offset = (object - 1) * 44;
    value = r_u32(0x800CF908);
    w_u32(0x800EE72C + offset, value);
    value = r_u32(0x800EE7E4);
    w_u32(0x800EE728 + offset, value);
    value = r_u32(0x80081978 + object * 4);
    w_u32(0x800EE738 + offset, value);
    for (axis = 0; axis < 3; ++axis)
    {
        coordinate = r_u32(0x800DDD48 + (object << 4));
        value = r_u32(coordinate + 24 + axis * 4);
        w_u32(0x800EE73C + offset + axis * 4, value);
    }
    for (axis = 0; axis < 3; ++axis)
    {
        coordinate = r_u32(0x800DDD48 + (object << 4));
        transform = r_u32(coordinate + 68);
        if (axis == 2)
            enabled = r_u32(0x800CF910);
        value = (uint32)r_s16(transform + 16 + axis * 2);
        w_u32(0x800EE748 + offset + axis * 4, value);
    }
    object = r_u32(0x800EE7EC);
    w_u32(0x800CF910, 0);
    action = func_80031954(object);
    action = action == 32 || action == 34 ? 32 : 36;
    func_8003222c(r_u32(0x800EE7EC), action, 1, 0, 0, 0);
    w_u32(0x800CFE0C, 0);
    w_u32(0x800CFE1C, 0);
    func_8002372c(0);
    func_8002372c(1);
    if (level != r_u32(0x800EE7E4))
    {
        func_80017a74();
        if (r_u32(0x800EDFC0) != 0)
            w_u32(0x800814B8, 0);
        w_u32(0x800CFA90, 1);
        func_80024090();
        root = r_u32(0x800CFA6C);
        if (r_u32(0x800CF8BC + root * 4) != 0)
            func_80032d68(root, 3);
        w_u32(0x800EE7F0, 0);
        old_object = r_u32(0x800EE7EC);
        next_object = r_u32(0x800EDFC4);
        root = r_u32(0x800CFA6C);
        w_u32(0x800EE7EC, next_object);
        w_u32(0x800EDFC4, old_object);
        func_800223b8(root, level, 1);
        w_u32(0x800CFA90, 0);
    }
    else
    {
        old_object = r_u32(0x800EE7EC);
        next_object = r_u32(0x800EDFC4);
        w_u32(0x800EE7F0, 0);
        w_u32(0x800EE7EC, next_object);
        w_u32(0x800EDFC4, old_object);
    }
    w_u32(0x800EE7EC, next_object);
    w_u32(0x800EE7F0, 0);
    func_80031c20(r_u32(0x800EE7EC), r_u32(0x800EDFC8), 1, 0, 0, 0);
    func_80032320(r_u32(0x800EE7EC), r_u32(0x800EDFC8));
    w_u32(0x800EDFC8, action);
    selected = r_u32(0x800EE7EC);
    w_u32(0x80081998 + selected * 4, 0);
    selected = r_u32(0x800EDFC4);
    w_u32(0x80081998 + selected * 4, 0);
    object = r_u32(0x800EE7EC);
    offset = (object - 1) * 44;
    for (axis = 0; axis < 3; ++axis)
    {
        coordinate = r_u32(0x800DDD48 + (object << 4));
        value = r_u32(0x800EE73C + offset + axis * 4);
        w_u32(coordinate + 24 + axis * 4, value);
    }
    for (axis = 0; axis < 3; ++axis)
    {
        coordinate = r_u32(0x800DDD48 + (object << 4));
        transform = r_u32(coordinate + 68);
        value = r_u16(0x800EE748 + offset + axis * 4);
        w_u16(transform + 16 + axis * 2, value);
    }
    func_80020a48(object, position);
    func_80020b7c(object, position);
    object = r_u32(0x800EE7EC);
    w_u32(0x800CF908, position);
    func_8001e8b4(object);
    object = r_u32(0x800EDFC4);
    value = r_u32(0x800EE728 + (object - 1) * 44);
    if (value != r_u32(0x800EE7E4))
        func_8001e8d8(object);
    else
        func_8001e8b4(r_u32(0x800EDFC4));
    func_8001dc98();
    func_80032d68(r_u32(0x800CFA6C), 6);
    w_u32(0x800CFE0C, 0);
    w_u32(0x800CFE1C, 0);
    w_u32(0x800CF910, enabled);
    func_80014ffc();
    return;
unavailable:
    func_8001f87c();
    object = r_u32(0x800EE7EC);
    selected = r_u32(0x800EE7F0);
    message = object + 1021;
    if (selected != 0)
    {
        selected = r_u32(0x800EE7F0);
        if (r_u32(0x80081978 + selected * 4) != 0)
            goto show_message;
    }
    message = r_u32(0x800EE7EC) + 1025;
show_message:
    func_8001f8a0(message, 0, 60);
    func_8001f92c();
}

void func_80034c68(uint32 value)
{
    FUNCTION_MARKER(0x80034C68, "SLUS_004.64");
    w_u32(0x800EDFD4, value);
}

uint32 func_80034d04(uint32 x, uint32 y, uint32 z)
{
    FUNCTION_MARKER(0x80034D04, "SLUS_004.64");
    w_u32(0x800EF5EC, x);
    w_u32(0x800EF5F0, y);
    w_u32(0x800EF5F4, z);
    return 0x800EF5EC;
}

uint32 func_80034d1c(uint32 *x, uint32 *y, uint32 *z)
{
    uint32 value;
    FUNCTION_MARKER(0x80034D1C, "SLUS_004.64");
    value = r_u32(0x800EF5EC);
    *x = value;
    value = r_u32(0x800EF5F0);
    *y = value;
    value = r_u32(0x800EF5F4);
    *z = value;
    return value;
}

uint32 func_80034d48(uint32 x, uint32 y, uint32 z)
{
    FUNCTION_MARKER(0x80034D48, "SLUS_004.64");
    w_u32(0x800EF5F8, x);
    w_u32(0x800EF5FC, y);
    w_u32(0x800EF600, z);
    return 0x800EF5F8;
}

uint32 func_80034d60(uint32 *x, uint32 *y, uint32 *z)
{
    uint32 value;
    FUNCTION_MARKER(0x80034D60, "SLUS_004.64");
    value = r_u32(0x800EF5F8);
    *x = value;
    value = r_u32(0x800EF5FC);
    *y = value;
    value = r_u32(0x800EF600);
    *z = value;
    return value;
}

uint32 func_80032d20(uint32 selected)
{
    FUNCTION_MARKER(0x80032D20, "SLUS_004.64");
    return func_8002e2ac(selected);
}

uint32 func_80032624(uint32 object, uint32 x, uint32 z)
{
    uint32 address = 0x800DDD48 + (object << 4);
    FUNCTION_MARKER(0x80032624, "SLUS_004.64");
    w_u32(r_u32(address) + 24, x);
    w_u32(r_u32(address) + 32, z);
    w_u32(r_u32(address), 0);
    return func_8001b21c(0x800DDD44 + (object << 4));
}

uint32 func_80031f70(uint32 object, uint32 first, uint32 second, uint32 final_action)
{
    FUNCTION_MARKER(0x80031F70, "SLUS_004.64");
    func_80032030(object, first);
    func_80031d18(object, second);
    func_80031d18(object, final_action);
    return func_80032320(object, final_action);
}

uint32 func_8002ad80(void)
{
    FUNCTION_MARKER(0x8002AD80, "SLUS_004.64");
    return r_u32(0x800CFE24);
}

void func_80028470(uint32 value)
{
    FUNCTION_MARKER(0x80028470, "SLUS_004.64");
    w_u32(0x800CF8E0, value);
}

sint32 func_80039234(uint32 resource, sint32 bank, uint32 volume)
{
    uint32 base, second_base, offset, entry, bytes;
    sint16 sequence;
    FUNCTION_MARKER(0x80039234, "SLUS_004.64");
    entry = (resource - 1) * 40;
    base = r_u32(0x800CFC98);
    second_base = r_u32(0x800CFC98);
    offset = r_u32(base + 36 + entry);
    bytes = r_u32(base + 40 + entry);
    sequence = (sint16)func_80075880(offset + second_base, (sint16)bank, bytes);
    SsSeqSetVol(sequence, (sint16)volume, (sint16)volume);
    return sequence;
}

uint32 func_80038dc8(uint32 mode, sint32 value, uint32 enabled, uint32 volume)
{
    uint32 slot = 0x800EC1E4, found = 0, sequence_bits, resource;
    sint16 sequence, sentinel;
    FUNCTION_MARKER(0x80038DC8, "SLUS_004.64");
    sequence_bits = r_u16(slot);
    sentinel = r_s16(slot);
    if (sentinel != 99)
    {
        for (;;)
        {
            resource = r_u32(slot + 4);
            if (resource == mode && (uint16)SsIsEos((sint16)sequence_bits, 0) == 0)
            {
                found = 1;
                break;
            }
            slot += 8;
            sentinel = r_s16(slot);
            sequence_bits = r_u16(slot);
            if (sentinel == 99)
                break;
        }
    }
    if (found == 0)
    {
        slot = 0x800EC1E4;
        for (;;)
        {
            sequence = r_s16(slot);
            if (sequence == -1)
                break;
            if (sequence == 99)
            {
                slot = 0x800EC1E4;
                func_80078db4(r_s16(slot));
                break;
            }
            if ((uint16)SsIsEos(sequence, 0) == 0)
            {
                func_80078db4(r_s16(slot));
                break;
            }
            slot += 8;
        }
        w_u32(slot + 4, mode);
        sequence = (sint16)func_80039234(mode, (sint16)value, (uint32)(sint32)(sint16)volume);
        w_u16(slot, sequence);
    }
    return SsSeqPlay(r_s16(slot), 1, (sint16)enabled);
}

uint32 func_80078db4(sint16 sequence)
{
    FUNCTION_MARKER(0x80078DB4, "SLUS_004.64");
    return func_80078c38(sequence);
}

uint32 func_800392bc(sint16 sequence)
{
    FUNCTION_MARKER(0x800392BC, "SLUS_004.64");
    return func_80078db4(sequence);
}

uint32 func_80038fd4(uint32 resource)
{
    uint32 slot = 0x800EC1E4, sequence_bits;
    sint16 sentinel;
    FUNCTION_MARKER(0x80038FD4, "SLUS_004.64");
    for (;;)
    {
        sequence_bits = r_u16(slot);
        sentinel = r_s16(slot);
        if (sentinel == 99)
            return 99;
        if (r_u32(slot + 4) == resource && (sint16)SsIsEos((sint16)sequence_bits, 0) == 1)
            SsSeqStop(r_s16(slot));
        slot += 8;
    }
}

uint32 func_800385b4(void)
{
    uint32 index;
    FUNCTION_MARKER(0x800385B4, "SLUS_004.64");
    for (index = 0; index < 10; ++index)
        w_u8(0x800CFBF8 + index, 1);
    return 1;
}

uint32 func_8003e1e4(uint32 card, uint32 *slots, const uint32 *cards)
{
    uint32 slot, result = 0;
    const char *name;
    FUNCTION_MARKER(0x8003E1E4, "SLUS_004.64");
    if (cards[card] != 1)
        return 0;
    w_u32(0x800CFD40, card);
    for (slot = 0; slot < 4; ++slot)
    {
        if (slots[slot] == 0xFFFFFFFF)
        {
            name = (const char *)psx_addr(0x800B4D44 + slot * 21, 16);
            if (func_80040920(name) == 0)
                slots[slot] = 0xFFFFFFFE;
            else
                result = 1;
            func_8004087c(name);
        }
        else
            result = 1;
    }
    return result;
}

uint32 func_8003e2a0(const uint8 *entries, sint32 count, uint32 *slots)
{
    uint32 entry = 0, offset = 0, slot, matches = 0;
    sint32 index;
    FUNCTION_MARKER(0x8003E2A0, "SLUS_004.64");
    for (index = 3; index >= 0; --index)
        slots[index] = 0xFFFFFFFF;
    do
    {
        for (slot = 0; slot < 4; ++slot)
        {
            if (strncmp((const char *)entries + offset, (const char *)psx_addr(0x800B4D44 + slot * 21, 16), 16) == 0)
            {
                slots[slot] = entry;
                ++matches;
            }
        }
        ++entry;
        offset += 24;
    } while ((sint32)entry < count);
    return matches;
}

sint32 func_8003e390(uint32 *data, const uint32 *slots, uint32 slot, uint32 *work)
{
    uint32 status;
    const char *name;
    FUNCTION_MARKER(0x8003E390, "SLUS_004.64");
    status = slots[slot];
    if (status == 0xFFFFFFFF || status == 999 || status == 0xFFFFFFFE)
    {
        func_8002372c(2);
        return 0;
    }
    name = (const char *)psx_addr(0x800B4D44 + slot * 21, 16);
    if (func_80040748(name, data, slot, work) == 0)
        return -1;
    return func_8001820c(data) != 0 ? 1 : -1;
}

uint32 func_8003e43c(uint32 *data, const uint32 *slots, uint32 slot, uint8 *header)
{
    uint32 status;
    const char *name;
    FUNCTION_MARKER(0x8003E43C, "SLUS_004.64");
    status = slots[slot];
    name = (const char *)psx_addr(0x800B4D44 + slot * 21, 16);
    if (status == 0xFFFFFFFF && func_80040920(name) == 0)
        return 0;
    return func_800409e4(name, data, slot, header) != 0;
}

uint32 func_8003cb7c(void)
{
    FUNCTION_MARKER(0x8003CB7C, "SLUS_004.64");
    if (r_u32(0x800CFC18) != 1)
        return 3;
    w_u32(0x800CFC18, 3);
    w_u32(0x800CFCC8, 32);
    return 32;
}

uint32 func_8003cba4(void)
{
    FUNCTION_MARKER(0x8003CBA4, "SLUS_004.64");
    return r_u32(0x800CFC18);
}

uint32 func_8003a5f0(void)
{
    uint32 timer, buffer, color;
    FUNCTION_MARKER(0x8003A5F0, "SLUS_004.64");
    timer = r_u32(0x800CFCC8);
    buffer = r_u32(0x800CFDEC);
    color = 256 - (timer << 3);
    w_u8(0x800EC1E0, (uint8)color);
    w_u8(0x800EC1E1, (uint8)color);
    w_u8(0x800EC1E2, (uint8)color);
    GsSortBoxFill(psx_addr(0x800EC1D4, 16), psx_addr(0x800EC778 + buffer * 20, 20), 0);
    timer = r_u32(0x800CFCC8) - 1;
    w_u32(0x800CFCC8, timer);
    if (timer == 0)
        w_u32(0x800CFC18, 0);
    return timer;
}

sint32 func_8003fc70(void)
{
    FUNCTION_MARKER(0x8003FC70, "SLUS_004.64");
    TestEvent((sint32)r_u32(0x800CFCF0));
    TestEvent((sint32)r_u32(0x800CFCF8));
    TestEvent((sint32)r_u32(0x800CFD00));
    return TestEvent((sint32)r_u32(0x800CFD08));
}

uint32 func_80040e60(uint8 *text, sint32 value)
{
    sint32 tens, ones;
    FUNCTION_MARKER(0x80040E60, "SLUS_004.64");
    tens = value / 10;
    ones = value % 10;
    text[0] = 0x82;
    text[2] = 0x82;
    text[1] = (uint8)(tens + 0x4F);
    text[3] = (uint8)(ones + 0x4F);
    return 0x82;
}

uint32 func_80040d24(sint32 ticks, uint8 *text)
{
    sint32 seconds, minutes, hours;
    uint8 first, second, third;
    FUNCTION_MARKER(0x80040D24, "SLUS_004.64");
    seconds = ticks / 60;
    minutes = seconds / 60;
    hours = minutes / 60;
    seconds -= minutes * 60;
    minutes -= hours * 60;
    func_80040e60(text, hours);
    first = (uint8)r_s8(0x800CFC58);
    second = (uint8)r_s8(0x800CFC59);
    third = (uint8)r_s8(0x800CFC5A);
    text[4] = first;
    text[5] = second;
    text[6] = third;
    func_80040e60(text + 6, minutes);
    first = (uint8)r_s8(0x800CFC58);
    second = (uint8)r_s8(0x800CFC59);
    third = (uint8)r_s8(0x800CFC5A);
    text[10] = first;
    text[11] = second;
    text[12] = third;
    return func_80040e60(text + 12, seconds);
}

void func_8003a4d8(void)
{
    uint32 buffer;
    FUNCTION_MARKER(0x8003A4D8, "SLUS_004.64");
    buffer = r_u32(0x800CFDEC);
    GsSortFastSprite(psx_addr(0x800E9A78, 36), psx_addr(0x800EC778 + buffer * 20, 20), 1);
    buffer = r_u32(0x800CFDEC);
    GsSortFastSprite(psx_addr(0x800EBE04, 36), psx_addr(0x800EC778 + buffer * 20, 20), 1);
}

uint32 func_8003a54c(void)
{
    uint32 timer, buffer, color;
    FUNCTION_MARKER(0x8003A54C, "SLUS_004.64");
    timer = r_u32(0x800CFCC8);
    buffer = r_u32(0x800CFDEC);
    color = (timer << 3) - 1;
    w_u8(0x800EC1E0, (uint8)color);
    w_u8(0x800EC1E1, (uint8)color);
    w_u8(0x800EC1E2, (uint8)color);
    GsSortBoxFill(psx_addr(0x800EC1D4, 16), psx_addr(0x800EC778 + buffer * 20, 20), 0);
    timer = r_u32(0x800CFCC8) - 1;
    w_u32(0x800CFCC8, timer);
    if (timer == 0)
    {
        timer = r_u32(0x800CFCB8);
        w_u32(0x800CFC18, 1);
        w_u32(0x800CFCC8, timer);
    }
    return 1;
}

void func_8003a688(void)
{
    uint32 state, mode, input, timer;
    FUNCTION_MARKER(0x8003A688, "SLUS_004.64");
    GsClearOt(0, 0, psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20));
    state = r_u32(0x800CFC18);
    if (state == 1)
    {
        mode = r_u32(0x800CFCA8);
        if (mode == 22 || mode == 23)
            func_8003aa98();
        else if (mode == 32)
            func_8003b770();
        else if (mode == 57)
            func_8003bf5c();
        else if (mode == 777)
            func_8003c760();
        else if (mode == 778)
            func_8003c8d8();
        else
        {
            input = func_8003d034();
            if (r_u32(0x800CFCC0) == 1 && input - 5 < 2)
            {
                w_u32(0x800CFC18, 3);
                w_u32(0x800CFCC8, 32);
            }
            if (r_u32(0x800CFCB8) != 0)
            {
                timer = r_u32(0x800CFCC8) - 1;
                w_u32(0x800CFCC8, timer);
                if (timer == 0)
                {
                    w_u32(0x800CFC18, 3);
                    w_u32(0x800CFCC8, 32);
                }
            }
        }
    }
    else if (state == 2)
    {
        func_8003a54c();
        mode = r_u32(0x800CFCA8);
        if (mode == 22 || mode == 23)
            func_8003b614();
        else if (mode == 32)
            func_8003bf3c();
        else if (mode == 57)
            func_8003c450();
        else if (mode == 777)
            func_8003c760();
        else if (mode == 778)
            func_8003c8d8();
    }
    else if (state == 3)
    {
        func_8003a5f0();
        mode = r_u32(0x800CFCA8);
        if (mode == 22 || mode == 23)
            func_8003b67c();
        else if (mode == 32)
            func_8003bee4();
        else if (mode == 57)
            func_8003c41c();
        else if (mode == 777)
            func_8003c760();
        else if (mode == 778)
            func_8003c8d8();
    }
    else
        return;
    func_8003a4d8();
}

uint32 func_8003c954(void)
{
    uint32 height, extent, alpha;
    FUNCTION_MARKER(0x8003C954, "SLUS_004.64");
    height = r_u16(0x800EE818);
    extent = 240 - height;
    w_u16(0x800D7962, extent);
    w_u16(0x800D7986, extent);
    alpha = r_u8(0x800EE818);
    w_u16(0x800D79AA, 480 - extent);
    w_u16(0x800D79CE, 480 - extent);
    extent += 0xFF88;
    w_u16(0x800D79A6, extent);
    w_u16(0x800D79CA, extent);
    w_u8(0x800D7967, alpha);
    w_u8(0x800D798B, alpha);
    return 0xFF88;
}

uint32 func_8003c760(void)
{
    uint32 sprite;
    FUNCTION_MARKER(0x8003C760, "SLUS_004.64");
    if (r_u32(0x800EE818) != 1)
        return 1;
    for (sprite = 0x800D7958; sprite != 0x800D79A0; sprite += 36)
        GsSortFastSprite(psx_addr(sprite, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
    return 0;
}

uint32 func_8003c8d8(void)
{
    uint32 sprite;
    FUNCTION_MARKER(0x8003C8D8, "SLUS_004.64");
    func_8003c954();
    for (sprite = 0x800D7958; sprite != 0x800D79E8; sprite += 36)
        GsSortFastSprite(psx_addr(sprite, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
    return 0;
}

uint32 func_8003a980(const uint32 *config)
{
    uint32 index, x, y, page_x, page_y, u, v, sprite;
    FUNCTION_MARKER(0x8003A980, "SLUS_004.64");
    index = config[2];
    x = config[0];
    y = config[1];
    page_x = config[3];
    page_y = config[4];
    u = config[5];
    v = config[6];
    sprite = 0x800D7958 + index * 36;
    w_u32(sprite, 0x0A000000);
    w_u16(sprite + 12, GetTPage(2, 0, (sint32)page_x, (sint32)page_y));
    w_u16(sprite + 8, 92);
    w_u16(sprite + 10, 184);
    w_u16(sprite + 4, x - 160);
    w_u16(sprite + 6, y - 120);
    w_u8(sprite + 14, u);
    w_u8(sprite + 15, v);
    return 184;
}

void func_8003b614(void)
{
    uint32 config[7], selected;
    FUNCTION_MARKER(0x8003B614, "SLUS_004.64");
    selected = r_u32(0x800EE854);
    config[0] = 90;
    config[1] = 125;
    config[2] = 8;
    config[4] = 0;
    config[5] = 0;
    config[6] = 0;
    config[3] = selected != 0 ? 0x380 : 0x300;
    func_8003a980(config);
    func_8003b69c(0);
}

void func_8003b67c(void)
{
    FUNCTION_MARKER(0x8003B67C, "SLUS_004.64");
    func_8003b69c(1);
}

void func_8003b69c(uint32 enabled)
{
    uint32 index, counter, sprite;
    FUNCTION_MARKER(0x8003B69C, "SLUS_004.64");
    if (enabled != 0)
    {
        index = 8 - r_u32(0x800CFCE8);
        if ((sint32)index < 8)
        {
            counter = index * 9;
            sprite = 0x800D7958 + counter * 4;
            do
            {
                counter += 9;
                GsSortFastSprite(psx_addr(sprite, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
                sprite += 36;
            } while ((sint32)counter < 72);
        }
    }
    GsSortFastSprite(psx_addr(0x800D7A78, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
}

void func_8003bee4(void)
{
    uint32 config[7], selected;
    FUNCTION_MARKER(0x8003BEE4, "SLUS_004.64");
    selected = r_u32(0x800CFC1C);
    config[1] = 120;
    config[2] = 0;
    config[3] = 0x300;
    config[4] = 0;
    config[5] = 0;
    config[6] = 0;
    config[0] = (selected + 1) << 6;
    func_8003a980(config);
    func_8003bb34(1);
}

void func_8003bf3c(void)
{
    FUNCTION_MARKER(0x8003BF3C, "SLUS_004.64");
    func_8003bb34(0);
}

void func_8003bb34(uint32 selected)
{
    FUNCTION_MARKER(0x8003BB34, "SLUS_004.64");
    if (r_u32(0x800EE820) == 1)
    {
        GsSortFastSprite(psx_addr(0x800D797C, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
        GsSortFastSprite(psx_addr(0x800D79E8, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
    }
    if (r_u32(0x800EE824) == 1)
    {
        GsSortFastSprite(psx_addr(0x800D79A0, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
        GsSortFastSprite(psx_addr(0x800D7A0C, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
    }
    if (r_u32(0x800EE828) == 1)
    {
        GsSortFastSprite(psx_addr(0x800D79C4, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
        GsSortFastSprite(psx_addr(0x800D7A30, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
    }
    if (selected != 0)
        GsSortFastSprite(psx_addr(0x800D7958, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
}

void func_8003c41c(void)
{
    FUNCTION_MARKER(0x8003C41C, "SLUS_004.64");
    if (r_u32(0x800CFCB0) != 0xFFFFFFFF)
        func_8003c18c(0, 1);
}

void func_8003c450(void)
{
    uint32 selected;
    FUNCTION_MARKER(0x8003C450, "SLUS_004.64");
    selected = r_u32(0x800EE81C);
    func_8003c18c(0, selected == 0xFFFFFFFF ? 1 : 0);
}

void func_8003c18c(uint32 cursor, uint32 options)
{
    uint32 index, buffer, first, second, table;
    FUNCTION_MARKER(0x8003C18C, "SLUS_004.64");
    if (r_u32(0x800EE834) == 1)
        GsSortFastSprite(psx_addr(0x800D7AC0, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
    if (cursor != 0)
    {
        table = r_u32(0x800CFC1C) << 3;
        buffer = r_u32(0x800CFDEC);
        w_u16(0x800D795C, r_u16(0x800B4CE4 + table) - 160);
        w_u16(0x800D795E, r_u16(0x800B4CE8 + table) - 120);
        GsSortFastSprite(psx_addr(0x800D7958, 36), psx_addr(0x800EC778 + buffer * 20, 20), 0);
    }
    if (options != 0)
    {
        table = r_u32(0x800EE830) << 3;
        buffer = r_u32(0x800CFDEC);
        w_u16(0x800D7980, r_u16(0x800B4C9C + table) - 160);
        w_u16(0x800D7982, r_u16(0x800B4CA0 + table) - 120);
        GsSortFastSprite(psx_addr(0x800D797C, 36), psx_addr(0x800EC778 + buffer * 20, 20), 0);
        first = 0x800D79A0;
        second = 0x800D7A30;
        for (index = 0; index < 4; ++index)
        {
            if (r_u32(0x800EE820 + index * 4) != 0)
            {
                GsSortFastSprite(psx_addr(first, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
                GsSortFastSprite(psx_addr(second, 36), psx_addr(0x800EC778 + r_u32(0x800CFDEC) * 20, 20), 0);
            }
            second += 36;
            first += 36;
        }
    }
}

uint32 func_8003d034(void)
{
    uint32 buttons, state, timer;
    FUNCTION_MARKER(0x8003D034, "SLUS_004.64");
    buttons = PadRead(0);
    if ((buttons & 0x20) != 0)
    {
        if (r_u8(0x800CFC2C) == 0)
        {
            w_u8(0x800CFC2C, 1);
            return 5;
        }
    }
    else
        w_u8(0x800CFC2C, 0);
    if ((buttons & 0x40) != 0)
    {
        if (r_u8(0x800CFC2D) == 0)
        {
            w_u8(0x800CFC2D, 1);
            return 6;
        }
    }
    else
        w_u8(0x800CFC2D, 0);
    if ((buttons & 0x1000) != 0)
    {
        state = r_u8(0x800CFC28);
        if (state == 0)
        {
            w_u8(0x800CFC28, 1);
            w_u32(0x800CFC30, 5);
            return 1;
        }
        if (state == 1)
        {
            timer = r_u32(0x800CFC30) - 1;
            w_u32(0x800CFC30, timer);
            if (timer == 0)
                w_u8(0x800CFC28, 2);
        }
        else if (state == 2)
        {
            timer = r_u32(0x800CFC30);
            if (timer == 0)
            {
                w_u32(0x800CFC30, 4);
                return 1;
            }
            w_u32(0x800CFC30, timer - 1);
        }
    }
    else
        w_u8(0x800CFC28, 0);
    if ((buttons & 0x4000) != 0)
    {
        state = r_u8(0x800CFC29);
        if (state == 0)
        {
            w_u8(0x800CFC29, 1);
            w_u32(0x800CFC30, 5);
            return 2;
        }
        if (state == 1)
        {
            timer = r_u32(0x800CFC30) - 1;
            w_u32(0x800CFC30, timer);
            if (timer == 0)
                w_u8(0x800CFC29, 2);
        }
        else if (state == 2)
        {
            timer = r_u32(0x800CFC30);
            if (timer == 0)
            {
                w_u32(0x800CFC30, 4);
                return 2;
            }
            w_u32(0x800CFC30, timer - 1);
        }
    }
    else
        w_u8(0x800CFC29, 0);
    if ((buttons & 0x8000) != 0)
    {
        state = r_u8(0x800CFC2A);
        if (state == 0)
        {
            w_u8(0x800CFC2A, 1);
            w_u32(0x800CFC30, 5);
            return 3;
        }
        if (state == 1)
        {
            timer = r_u32(0x800CFC30) - 1;
            w_u32(0x800CFC30, timer);
            if (timer == 0)
                w_u8(0x800CFC2A, 2);
        }
        else if (state == 2)
        {
            timer = r_u32(0x800CFC30);
            if (timer == 0)
            {
                w_u32(0x800CFC30, 4);
                return 3;
            }
            w_u32(0x800CFC30, timer - 1);
        }
    }
    else
        w_u8(0x800CFC2A, 0);
    if ((buttons & 0x2000) == 0)
    {
        w_u8(0x800CFC2B, 0);
        return 0;
    }
    state = r_u8(0x800CFC2B);
    if (state == 0)
    {
        w_u8(0x800CFC2B, 1);
        w_u32(0x800CFC30, 5);
        return 4;
    }
    if (state == 1)
    {
        timer = r_u32(0x800CFC30) - 1;
        w_u32(0x800CFC30, timer);
        if (timer == 0)
            w_u8(0x800CFC2B, 2);
    }
    else if (state == 2)
    {
        timer = r_u32(0x800CFC30);
        if (timer == 0)
        {
            w_u32(0x800CFC30, 4);
            return 4;
        }
        w_u32(0x800CFC30, timer - 1);
    }
    return 0;
}
