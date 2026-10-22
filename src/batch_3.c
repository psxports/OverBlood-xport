#include "functions.h"

/* Full original bodies, pending final integration and runtime validation */
void func_800150f8(void)
{
    FUNCTION_MARKER(0x800150F8, "SLUS_004.64");
}

uint32 func_8001b2f8(uint32 object, uint32 value, uint32 output)
{
    uint32 frame;
    uint32 animation;
    uint32 model;
    uint32 resource;
    uint32 coordinate;
    uint32 duration;
    uint32 start;
    FUNCTION_MARKER(0x8001B2F8, "SLUS_004.64");
    if (r_u32(0x800818F8 + 4 * object) != value)
    {
        w_u32(0x800818F8 + 4 * object, value);
        frame = r_u32(0x800E27A4 + 4 * value);
        w_u32(output, frame);
        animation = r_u32(0x800EC480 + 4 * value);
        w_u32(0x800E9830 + 4 * object, animation);
    }
    model = r_u32(0x800EC400 + 4 * object);
    frame = r_u32(output);
    animation = r_u32(0x800E9830 + 4 * object);
    resource = r_u32(0x80081498 + 4 * object);
    animation = func_80035954(frame, animation, 0x80082104 + 12 * object, resource, model, 2);
    w_u32(0x800E9830 + 4 * object, animation);
    frame = r_u32(output);
    w_u32(output, frame + 1);
    coordinate = r_u32(0x800DDD48 + 16 * object);
    w_u32(coordinate, 0);
    func_8001b21c(0x800DDD44 + 16 * object);
    duration = r_u32(0x800EB9F8 + 4 * value);
    start = r_u32(0x800E27A4 + 4 * value);
    frame = r_u32(output);
    if ((sint32)frame < (sint32)(duration + start))
        return 1;
    start = r_u32(0x800E27A4 + 4 * value);
    w_u32(output, start);
    animation = r_u32(0x800EC480 + 4 * value);
    w_u32(0x800E9830 + 4 * object, animation);
    return 0;
}

void func_800228d0(uint32 mode)
{
    uint32 object;
    uint32 coordinate;
    uint32 scale;
    uint32 size;
    uint32 position;
    FUNCTION_MARKER(0x800228D0, "SLUS_004.64");
    w_u32(0x800EDFD0, mode);
    for (object = 1; object < 5; ++object)
    {
        size = r_u32(0x800EDFD0) ? 2048 : 4096;
        coordinate = r_u32(0x800DDD48 + 16 * object);
        scale = r_u32(coordinate + 68);
        w_u32(scale, size);
        coordinate = r_u32(0x800DDD48 + 16 * object);
        scale = r_u32(coordinate + 68);
        w_u32(scale + 4, size);
        coordinate = r_u32(0x800DDD48 + 16 * object);
        scale = r_u32(coordinate + 68);
        w_u32(scale + 8, size);
        position = r_u32(0x800CF908);
        func_80020b7c(object, position);
    }
    func_80022a08();
}

void func_800173d0(void)
{
    uint32 object;
    uint32 offset;
    uint32 scene;
    uint32 previous_scene;
    uint32 coordinate;
    uint32 rotation;
    uint32 value;
    FUNCTION_MARKER(0x800173D0, "SLUS_004.64");
    if (!r_u32(0x800EDFC0))
        return;
    object = r_u32(0x800EDFC4);
    if (!object)
        return;
    offset = 44 * (object - 1);
    scene = r_u32(0x800EE728 + offset);
    previous_scene = r_u32(0x800EE7E4);
    if (scene != previous_scene)
    {
        func_8001e8d8((sint32)object);
        return;
    }
    func_8001e8b4((sint32)object);
    coordinate = r_u32(0x800DDD48 + 16 * object);
    value = r_u32(0x800EE73C + offset);
    w_u32(coordinate + 24, value);
    coordinate = r_u32(0x800DDD48 + 16 * object);
    value = r_u32(0x800EE740 + offset);
    w_u32(coordinate + 28, value);
    coordinate = r_u32(0x800DDD48 + 16 * object);
    value = r_u32(0x800EE744 + offset);
    w_u32(coordinate + 32, value);
    coordinate = r_u32(0x800DDD48 + 16 * object);
    rotation = r_u32(coordinate + 68);
    value = r_u16(0x800EE748 + offset);
    w_u16(rotation + 16, (uint16)value);
    coordinate = r_u32(0x800DDD48 + 16 * object);
    rotation = r_u32(coordinate + 68);
    value = r_u16(0x800EE74C + offset);
    w_u16(rotation + 18, (uint16)value);
    coordinate = r_u32(0x800DDD48 + 16 * object);
    rotation = r_u32(coordinate + 68);
    value = r_u16(0x800EE750 + offset);
    w_u16(rotation + 20, (uint16)value);
    func_8001b21c(0x800DDD44 + 16 * object);
}

void func_8002334c(void)
{
    uint32 object;
    uint32 action;
    uint32 frame;
    sint32 sound;
    sint32 resource;
    uint32 offset;
    FUNCTION_MARKER(0x8002334C, "SLUS_004.64");
    for (object = 1; object < 4; ++object)
    {
        if (!((r_u32(0x800EDFD8) == 2 && r_u32(0x800EE7EC) == object) || r_u32(0x80081978 + 4 * object)))
            continue;
        func_80032568(object, &action, &frame);
        resource = r_s32(0x800EE028 + 4 * object);
        offset = 8 * ((uint32)resource - 1);
        if (resource > 0)
        {
            if (action == 2 && frame == 1)
                func_8002372c(r_u32(0x800B290C + offset));
            if (action == 3 && frame == 1)
                func_8002372c(r_u32(0x800B2910 + offset));
            if (action == 4 && frame == 1)
                func_8002372c(r_u32(0x800B290C + offset));
            if (action == 5 && frame == 1)
                func_8002372c(r_u32(0x800B2910 + offset));
            if (action == 8 && frame == 1)
                func_8002372c(r_u32(0x800B290C + offset));
            if (action == 9 && frame == 1)
                func_8002372c(r_u32(0x800B2910 + offset));
            if (action == 25 && frame == 2)
                func_8002372c(r_u32(0x800B290C + offset));
            if (action == 25 && frame == 4)
                func_8002372c(r_u32(0x800B2910 + offset));
            if (action == 15 && frame == 2)
                func_8002372c(r_u32(0x800B2910 + offset));
            if (action == 21 && frame == 6)
                func_8002372c(r_u32(0x800B290C + offset));
            if (action == 17 && frame == 5)
                func_8002372c(r_u32(0x800B290C + offset));
            if (action == 18 && frame == 5)
                func_8002372c(r_u32(0x800B290C + offset));
        }
        sound = r_s32(0x800CF824);
        if (sound > 0)
        {
            if (action == 17 && frame == 1)
                func_8002372c((uint32)sound);
            if (action == 18 && frame == 1)
                func_8002372c(r_u32(0x800CF824));
        }
    }
}

uint32 func_80032568(uint32 object, uint32 *action, uint32 *frame)
{
    uint32 value;
    FUNCTION_MARKER(0x80032568, "SLUS_004.64");
    value = r_u32(0x800818B8 + 4 * object);
    *action = value;
    value = r_u32(0x800818D8 + 4 * object);
    *frame = value;
    return value;
}

void func_800324cc(uint32 object, sint32 mode, uint32 action, uint32 value0, uint32 value1, uint32 value2)
{
    FUNCTION_MARKER(0x800324CC, "SLUS_004.64");
    if (mode == 0)
        func_80031c20(object, action, 1, value0, value1, value2);
    else if (mode == 1)
        func_80031b14(object, action, 1, value0, value1, value2);
    else if (mode == 2)
        func_800319c0(object, action, 1, value0, value1, value2);
}

uint32 func_80031b14(uint32 object, uint32 action, uint32 enabled, uint32 value0, uint32 value1, uint32 value2)
{
    uint32 offset;
    uint32 cursor;
    uint32 entry;
    FUNCTION_MARKER(0x80031B14, "SLUS_004.64");
    offset = 1040 * object;
    cursor = r_u32(0x800DB6FC + offset) + 1;
    if ((sint32)cursor >= 32)
        cursor = 0;
    w_u32(0x800DB6F0 + offset, 1);
    entry = offset + 32 * cursor;
    w_u32(0x800DB2F0 + entry, action);
    w_u32(0x800DB2F4 + entry, enabled);
    w_u32(0x800DB2F8 + entry, value0);
    w_u32(0x800DB2FC + entry, value1);
    w_u32(0x800DB300 + entry, value2);
    ++cursor;
    if ((sint32)cursor >= 32)
        cursor = 0;
    entry = offset + 32 * cursor;
    w_u32(0x800DB2F0 + entry, 0xFFFFFFFF);
    w_u32(0x800DB6F8 + offset, 0xFFFFFFFF);
    w_u32(0x800DB6F4 + offset, 0xFFFFFFFF);
    return entry;
}

uint32 func_800319c0(uint32 object, uint32 action, uint32 enabled, uint32 value0, uint32 value1, uint32 value2)
{
    uint32 offset;
    uint32 cursor;
    uint32 scanned;
    uint32 entry;
    FUNCTION_MARKER(0x800319C0, "SLUS_004.64");
    offset = 1040 * object;
    cursor = r_u32(0x800DB6FC + offset);
    for (scanned = 0; scanned < 32; ++scanned)
    {
        if (r_u32(0x800DB2F0 + offset + 32 * cursor) == 0xFFFFFFFF)
            break;
        ++cursor;
        if ((sint32)cursor >= 32)
            cursor = 0;
    }
    w_u32(0x800DB6F0 + offset, 1);
    entry = offset + 32 * cursor;
    w_u32(0x800DB2F0 + entry, action);
    w_u32(0x800DB2F4 + entry, enabled);
    w_u32(0x800DB2F8 + entry, value0);
    w_u32(0x800DB2FC + entry, value1);
    w_u32(0x800DB300 + entry, value2);
    ++cursor;
    if ((sint32)cursor >= 32)
        cursor = 0;
    entry = offset + 32 * cursor;
    w_u32(0x800DB2F0 + entry, 0xFFFFFFFF);
    w_u32(0x800DB6F8 + offset, 0xFFFFFFFF);
    w_u32(0x800DB6F4 + offset, 0xFFFFFFFF);
    return entry;
}

uint32 func_8003222c(uint32 object, uint32 action, uint32 enabled, uint32 value0, uint32 value1, uint32 value2)
{
    uint32 offset;
    uint32 cursor;
    uint32 entry;
    FUNCTION_MARKER(0x8003222C, "SLUS_004.64");
    offset = 1040 * object;
    cursor = r_u32(0x800DB6FC + offset);
    entry = offset + 32 * cursor;
    w_u32(0x800DB2F0 + entry, action);
    w_u32(0x800DB2F4 + entry, enabled);
    w_u32(0x800DB2F8 + entry, value0);
    w_u32(0x800DB2FC + entry, value1);
    w_u32(0x800DB300 + entry, value2);
    w_u32(0x800DB6F8 + offset, action);
    w_u32(0x800DB6F4 + offset, 0);
    w_u32(0x800DB6F0 + offset, 1);
    ++cursor;
    if ((sint32)cursor >= 32)
        cursor = 0;
    entry = offset + 32 * cursor;
    w_u32(0x800DB2F0 + entry, 0xFFFFFFFF);
    return entry;
}

uint32 func_80032354(uint32 object, uint32 step, uint32 match)
{
    uint32 offset;
    FUNCTION_MARKER(0x80032354, "SLUS_004.64");
    offset = 1040 * object;
    w_u32(0x800DB6F4 + offset, step);
    w_u32(0x800DB6F8 + offset, match);
    return offset;
}

uint32 func_80031d18(uint32 object, uint32 action)
{
    uint32 offset;
    uint32 cursor;
    uint32 scanned;
    uint32 entry;
    FUNCTION_MARKER(0x80031D18, "SLUS_004.64");
    offset = 1040 * object;
    cursor = r_u32(0x800DB6FC + offset);
    for (scanned = 0; scanned < 32; ++scanned)
    {
        if (r_u32(0x800DB2F0 + offset + 32 * cursor) == 0xFFFFFFFF)
            break;
        ++cursor;
        if ((sint32)cursor >= 32)
            cursor = 0;
    }
    w_u32(0x800DB6F0 + offset, 1);
    entry = offset + 32 * cursor;
    w_u32(0x800DB2F0 + entry, action);
    w_u32(0x800DB2F4 + entry, 1);
    w_u32(0x800DB2F8 + entry, 0);
    w_u32(0x800DB2FC + entry, 0);
    w_u32(0x800DB300 + entry, 0);
    ++cursor;
    if ((sint32)cursor >= 32)
        cursor = 0;
    entry = offset + 32 * cursor;
    w_u32(0x800DB2F0 + entry, 0xFFFFFFFF);
    w_u32(0x800DB6F8 + offset, 0xFFFFFFFF);
    w_u32(0x800DB6F4 + offset, 0xFFFFFFFF);
    return entry;
}

void func_80015984(void)
{
    uint32 step;
    sint32 direction;
    uint32 position;
    sint32 bound;
    FUNCTION_MARKER(0x80015984, "SLUS_004.64");
    if (!r_u32(0x800CF818))
        return;
    step = r_u32(0x800CF810);
    direction = r_s32(0x800CF80C);
    position = r_u32(0x800CF808);
    position += step * (uint32)direction;
    w_u32(0x800CF808, position);
    if (direction > 0)
    {
        bound = r_s32(0x800CF814) >> 1;
        if ((sint32)position > bound)
            w_u32(0x800CF80C, 0xFFFFFFFF);
    }
    else
    {
        bound = r_s32(0x800CF814) >> 1;
        position = r_u32(0x800CF808);
        if ((sint32)position < (sint32)(0 - (uint32)bound))
            w_u32(0x800CF80C, 1);
    }
}

void func_800132b8(void)
{
    uint32 tick;
    FUNCTION_MARKER(0x800132B8, "SLUS_004.64");
    tick = (uint32)VSync(-1);
    w_u32(0x800CF834, tick);
    w_u32(0x800CF838, tick);
    if (r_s32(0x800CF8B4) >= 101)
    {
        func_800388b4();
        w_u32(0x800CF7B4, 15);
    }
}

void func_80013304(void)
{
    uint32 tick;
    uint32 previous;
    uint32 accumulated;
    FUNCTION_MARKER(0x80013304, "SLUS_004.64");
    func_80038938();
    tick = (uint32)VSync(-1);
    previous = r_u32(0x800CF838);
    w_u32(0x800CF834, tick);
    accumulated = r_u32(0x800CF83C);
    w_u32(0x800CF83C, tick - previous + accumulated);
}

void func_80013348(void)
{
    uint32 tick;
    uint32 previous;
    uint32 accumulated;
    FUNCTION_MARKER(0x80013348, "SLUS_004.64");
    tick = (uint32)VSync(-1);
    previous = r_u32(0x800CF838);
    w_u32(0x800CF834, tick);
    accumulated = r_u32(0x800CF83C);
    w_u32(0x800CF83C, tick - previous + accumulated);
    tick = (uint32)VSync(-1);
    w_u32(0x800CF834, tick);
    w_u32(0x800CF838, tick);
}

void func_80014d00(void)
{
    uint32 input;
    uint32 blocked;
    uint32 countdown;
    uint32 state;
    FUNCTION_MARKER(0x80014D00, "SLUS_004.64");
    input = func_80012658();
    blocked = r_u32(0x800CFB84);
    w_u32(0x800CF934, input);
    if (blocked || ((input & 0x800) && (input & 0x20)))
        return;
    if (r_u32(0x800CF8DC) == 100)
        return;
    countdown = r_u32(0x800CF7B4) - 1;
    w_u32(0x800CF7B4, countdown);
    if ((sint32)countdown > 0)
        return;
    input = r_u32(0x800CF934);
    w_u32(0x800CF7B4, 0);
    if (input & 0x20)
        return;
    if (input & 0x800)
    {
        w_u32(0x800CF7B0, 1);
        func_80013394();
        func_80013394();
    }
    if (!r_u32(0x800CF7B0))
        return;
    func_800132b8();
    input = func_80012658();
    w_u32(0x800CF934, input);
    if (!(input & 0x800))
        goto wait_press;
    do
    {
        input = func_80012658();
        state = r_u32(0x800CF8DC);
        w_u32(0x800CF934, input);
    }
    while (state != 100 && (input & 0x800));
    if (r_u32(0x800CF934) & 0x800)
        goto wait_release;
wait_press:
    for (;;)
    {
        input = func_80012658();
        state = r_u32(0x800CF8DC);
        w_u32(0x800CF934, input);
        if (state == 100)
            break;
        if (r_u32(0x800CF7A4) && (input & 2))
        {
            do
            {
                input = func_80012658();
                w_u32(0x800CF934, input);
            }
            while (input & 2);
            w_u32(0x800CF864, 1);
            func_80013348();
            return;
        }
        if (r_u32(0x800CF934) & 0x800)
            break;
    }
    if (!(r_u32(0x800CF934) & 0x800))
        goto resume;
wait_release:
    do
    {
        input = func_80012658();
        state = r_u32(0x800CF8DC);
        w_u32(0x800CF934, input);
    }
    while (state != 100 && (input & 0x800));
resume:
    w_u32(0x800CF7B0, 0);
    w_u32(0x800CF864, 0);
    func_80013304();
}

sint32 func_80012d48(void)
{
    uint32 tick;
    uint32 previous;
    sint32 fields;
    FUNCTION_MARKER(0x80012D48, "SLUS_004.64");
    do
    {
        tick = (uint32)VSync(-1);
        previous = r_u32(0x800CF868);
        w_u32(0x800CF834, tick);
    }
    while ((sint32)(tick - previous) < 2);
    tick = r_u32(0x800CF834);
    previous = r_u32(0x800CF868);
    fields = (sint32)(tick - previous) >> 1;
    if (fields >= 5)
        fields = 4;
    tick = r_u32(0x800CF834);
    w_u32(0x800CF868, tick);
    srandPSX(tick);
    return fields;
}

uint32 func_80036644(const uint32 *origin, const uint32 *reference, const uint32 *point)
{
    uint32 x;
    uint32 z;
    uint32 reference_x;
    uint32 reference_z;
    uint32 point_x;
    uint32 point_z;
    uint32 first;
    uint32 second;
    FUNCTION_MARKER(0x80036644, "SLUS_004.64");
    x = origin[0];
    z = origin[1];
    reference_x = reference[0];
    point_x = point[0];
    point_z = point[1];
    reference_z = reference[1];
    first = (uint32)ratan2((sint32)(reference_x - x), (sint32)(reference_z - z));
    second = (uint32)ratan2((sint32)(point_x - x), (sint32)(point_z - z));
    return first - second;
}

uint32 func_800367f4(uint32 x0, uint32 z0, uint32 x1, uint32 z1)
{
    uint32 dx;
    uint32 dz;
    uint32 square;
    FUNCTION_MARKER(0x800367F4, "SLUS_004.64");
    dx = x1 - x0;
    dz = z1 - z0;
    square = dx * dx + dz * dz;
    if ((sint32)square <= 0)
        return 0;
    return SquareRoot0((sint32)square);
}

uint32 func_80020d74(uint32 *pitch, uint32 *yaw, uint32 *roll)
{
    uint32 origin[2];
    uint32 reference[2];
    uint32 point[2];
    uint32 horizontal;
    uint32 target_y;
    uint32 eye_y;
    uint32 result;
    FUNCTION_MARKER(0x80020D74, "SLUS_004.64");
    origin[0] = r_u32(0x800EF5EC);
    reference[0] = origin[0];
    origin[1] = r_u32(0x800EF5F4);
    reference[1] = origin[1] + 10000;
    point[0] = r_u32(0x800EF5F8);
    point[1] = r_u32(0x800EF600);
    *yaw = 0 - func_80036644(origin, reference, point);
    horizontal = func_800367f4(origin[0], origin[1], point[0], point[1]);
    origin[0] = 0;
    origin[1] = 0;
    reference[0] = 0;
    reference[1] = 10000;
    target_y = r_u32(0x800EF5FC);
    eye_y = r_u32(0x800EF5F0);
    point[1] = horizontal;
    point[0] = target_y - eye_y;
    *pitch = func_80036644(origin, reference, point);
    result = r_u32(0x800EF604);
    *roll = result;
    return result;
}

void func_80012bfc(void)
{
    FUNCTION_MARKER(0x80012BFC, "SLUS_004.64");
    func_80014d00();
    func_80026840();
    if (r_u32(0x800CF864))
        func_80012dc0(1);
    else
        func_80012dc0(r_u32(0x800CF86C));
    func_80013394();
    func_80015984();
}

void func_80012dc0(uint32 count)
{
    uint32 input;
    uint32 object;
    FUNCTION_MARKER(0x80012DC0, "SLUS_004.64");
    input = func_80012658();
    w_u32(0x800CF934, input);
    func_80012fd0((sint32)count);
    func_80013178((sint32)count);
    func_80013124((sint32)count);
    func_8001309c((sint32)count);
    func_800131bc(count);
    func_800130e0(count);
    func_80013058(count);
    object = r_u32(0x800CFA6C);
    if (r_u32(0x800CF8BC + 4 * object))
        func_80032d68(object, 2);
}

void func_80012fd0(sint32 count)
{
    sint32 index;
    FUNCTION_MARKER(0x80012FD0, "SLUS_004.64");
    for (index = 0; index < count; ++index)
        func_80014aa8();
}

void func_80014aa8(void)
{
    sint32 object;
    sint32 mode;
    uint32 hit;
    FUNCTION_MARKER(0x80014AA8, "SLUS_004.64");
    if (r_u32(0x800CF918))
        func_8003026c();
    else
    {
        if (!r_u32(0x800CF910))
        {
            func_80014c74();
            return;
        }
        object = r_s32(0x800EE7EC);
        if (object == 1)
        {
            mode = r_s32(0x800CFDDC);
            if (mode == 1)
                func_80027408(0, r_u32(0x800EE7EC));
            else if (mode == 0 || mode == 2)
                func_800242d4(0, r_u32(0x800EE7EC));
        }
        else if (object == 2)
            func_800242d4(0, r_u32(0x800EE7EC));
        else if (object == 3)
            func_80027d88(0, r_u32(0x800EE7EC));
        else if (object < 3)
            goto update_collision;
    }
    object = r_s32(0x800EE7EC);
update_collision:
    if (object > 0)
    {
        if (object == 3)
            func_8002839c(0, 3);
        else
            func_800254b8(0, r_u32(0x800EE7EC));
    }
    hit = func_8001d480(r_u32(0x800EE7EC), 0);
    w_u32(0x800CFF7C, hit);
}

void func_80014c74(void)
{
    uint32 mask;
    uint32 input;
    FUNCTION_MARKER(0x80014C74, "SLUS_004.64");
    if (!r_u32(0x800CF984))
        return;
    mask = r_u32(0x800CF870);
    if (mask)
    {
        input = r_u32(0x800CF934);
        if (input & mask)
            w_u32(0x800CF934, input & ~mask);
        else
            w_u32(0x800CF870, 0);
    }
    if (r_u32(0x800CF934) & 0x40)
    {
        mask = r_u32(0x800CF870);
        w_u32(0x800CF964, 0);
        w_u32(0x800CFE0C, 0);
        w_u32(0x800CFE1C, 0);
        w_u32(0x800CFF7C, 0);
        w_u32(0x800CF870, mask | 0x40);
    }
}

void func_80029034(void)
{
    uint32 object;
    uint32 mode;
    FUNCTION_MARKER(0x80029034, "SLUS_004.64");
    for (object = 1; object < 5; ++object)
    {
        if (!r_u32(0x80081978 + 4 * object))
            continue;
        mode = r_u32(0x80081998 + 4 * object);
        if (!mode || object == r_u32(0x800EE7EC))
            continue;
        if (mode == 1 || mode == 2)
            func_8002965c(object);
        else if (mode == 3)
            func_8002912c(object);
        else if (mode == 4 && r_u32(0x800CFE24))
            func_8002c8e0(object);
    }
}

sint32 func_8001f8a0(uint32 value0, uint32 value1, uint32 action)
{
    uint32 cursor;
    uint32 offset;
    FUNCTION_MARKER(0x8001F8A0, "SLUS_004.64");
    cursor = r_u32(0x800CF980);
    offset = 12 * cursor;
    w_u32(0x800D85AC + offset, action);
    w_u32(0x800D85B0 + offset, value0);
    w_u32(0x800D85B4 + offset, value1);
    ++cursor;
    w_u32(0x800CF980, cursor);
    if ((sint32)cursor >= 32)
        w_u32(0x800CF980, 0);
    cursor = r_u32(0x800CF980);
    w_u32(0x800D85AC + 12 * cursor, 0xFFFFFFFF);
    return -1;
}

uint32 func_8001f92c(void)
{
    FUNCTION_MARKER(0x8001F92C, "SLUS_004.64");
    w_u32(0x800CF984, 1);
    w_u32(0x800CF964, 0);
    return 1;
}

uint32 func_80035954(uint32 frame, uint32 animation, uint32 object_list, uint32 resource, uint32 model, uint32 mode)
{
    uint32 threshold;
    uint32 count;
    uint32 index;
    FUNCTION_MARKER(0x80035954, "SLUS_004.64");
    threshold = r_u32(animation + 4);
    count = r_u16(animation + 2);
    if (frame >= threshold)
    {
        animation += 8;
        for (index = 0; index < count; ++index)
            animation = func_800359f4(animation, object_list, resource);
    }
    return animation;
}

void func_80014830(void)
{
    uint32 pitch;
    uint32 yaw;
    uint32 roll;
    uint32 object;
    uint32 coordinate;
    uint32 flags;
    uint32 index;
    FUNCTION_MARKER(0x80014830, "SLUS_004.64");
    func_80020d74(&pitch, &yaw, &roll);
    if (r_u32(0x800EDFD8) == 2)
    {
        index = r_u32(0x800EE7EC) * 16;
        object = r_u32(0x800DDD48 + index);
        coordinate = r_u32(object + 0x44);
        pitch += (uint32)r_s16(coordinate + 0x10);
        object = r_u32(0x800DDD48 + index);
        coordinate = r_u32(object + 0x44);
        yaw += (uint32)r_s16(coordinate + 0x12);
    }
    for (index = 0; (sint32)index < r_s32(0x800CFF2C); ++index)
    {
        flags = r_u32(0x800E9B14 + index * 4);
        if (flags != 0)
        {
            if (flags & 1)
            {
                object = r_u32(0x800DDD48 + index * 16);
                coordinate = r_u32(object + 0x44);
                w_u16(coordinate + 0x10, pitch);
            }
            if (flags & 2)
            {
                object = r_u32(0x800DDD48 + index * 16);
                coordinate = r_u32(object + 0x44);
                w_u16(coordinate + 0x12, yaw);
            }
            if (flags & 4)
            {
                object = r_u32(0x800DDD48 + index * 16);
                coordinate = r_u32(object + 0x44);
                w_u16(coordinate + 0x14, roll);
            }
            func_800149cc(0x800DDD44 + index * 16);
        }
    }
}

uint32 func_800149cc(uint32 object)
{
    uint32 coordinate;
    uint32 transform;
    uint32 matrix;
    uint32 value;
    FUNCTION_MARKER(0x800149CC, "SLUS_004.64");
    coordinate = r_u32(object + 4);
    value = r_u32(coordinate + 0x18);
    coordinate = r_u32(object + 4);
    value = r_u32(coordinate + 0x1C);
    coordinate = r_u32(object + 4);
    value = r_u32(coordinate + 0x20);
    coordinate = r_u32(object + 4);
    transform = r_u32(coordinate + 0x44);
    matrix = coordinate + 4;
    value = r_u32(coordinate + 0x18);
    w_u32(transform + 0x18, value);
    coordinate = r_u32(object + 4);
    value = r_u32(coordinate + 0x1C);
    w_u32(transform + 0x1C, value);
    coordinate = r_u32(object + 4);
    value = r_u32(coordinate + 0x20);
    w_u32(transform + 0x20, value);
    RotMatrixYXZ((SVECTOR *)psx_addr(transform + 0x10, 8), (MATRIX *)psx_addr(matrix, sizeof(MATRIX)));
    ScaleMatrix((MATRIX *)psx_addr(matrix, sizeof(MATRIX)), (VECTOR *)psx_addr(transform, 12));
    TransMatrix((MATRIX *)psx_addr(matrix, sizeof(MATRIX)), (VECTOR *)psx_addr(transform + 0x18, 12));
    coordinate = r_u32(object + 4);
    w_u32(coordinate, 0);
    return coordinate;
}

uint32 func_80015b2c(uint32 destination, uint32 source, uint32 index)
{
    uint32 input;
    uint32 output;
    uint32 value;
    uint32 offset;
    FUNCTION_MARKER(0x80015B2C, "SLUS_004.64");
    input = r_u32(source + 4);
    output = r_u32(destination + 4);
    value = r_u32(input + 0x18);
    w_u32(output + 0x18, value);
    output = r_u32(destination + 4);
    value = r_u32(0x80081958 + 4 * index);
    w_u32(output + 0x1C, value);
    input = r_u32(source + 4);
    output = r_u32(destination + 4);
    value = r_u32(input + 0x20);
    w_u32(output + 0x20, value);
    output = r_u32(destination + 4);
    output = r_u32(output + 0x44);
    w_u16(output + 0x10, 0);
    output = r_u32(destination + 4);
    output = r_u32(output + 0x44);
    input = r_u32(source + 4);
    input = r_u32(input + 0x44);
    value = r_u16(input + 0x12);
    w_u16(output + 0x12, value);
    output = r_u32(destination + 4);
    output = r_u32(output + 0x44);
    w_u16(output + 0x14, 0);
    for (offset = 0; offset < 12; offset += 4)
    {
        output = r_u32(destination + 4);
        output = r_u32(output + 0x44);
        input = r_u32(source + 4);
        input = r_u32(input + 0x44);
        value = r_u32(input + offset);
        w_u32(output + offset, value);
    }
    output = r_u32(destination + 4);
    w_u32(output + 0x48, 0);
    return output;
}

sint32 func_8001fac8(void)
{
    uint32 cursor;
    uint32 entry;
    uint32 value;
    sint32 result;
    FUNCTION_MARKER(0x8001FAC8, "SLUS_004.64");
    if (r_u32(0x800CF984) != 0 && r_s32(0x800CF964) <= 0)
    {
        cursor = r_u32(0x800CF97C);
        entry = 0x800D85AC + 12 * cursor;
        if (r_u32(entry) != 0xFFFFFFFF)
        {
            value = r_u32(entry + 4);
            w_u32(0x800CF968, value);
            value = r_u32(entry + 8);
            w_u32(0x800CF96C, value);
            value = r_u32(entry);
            w_u32(0x800CF964, value);
            w_u32(0x800CF960, value);
            ++cursor;
            w_u32(0x800CF97C, cursor);
            if ((sint32)cursor >= 32)
                w_u32(0x800CF97C, 0);
        }
    }
    cursor = r_u32(0x800CF97C);
    result = -1;
    if (r_u32(0x800D85AC + 12 * cursor) == 0xFFFFFFFF)
    {
        result = r_s32(0x800CF964);
        if (result <= 0)
        {
            w_u32(0x800CF984, 0);
            w_u32(0x800CF964, 0);
        }
    }
    return result;
}

void func_800194b4(uint32 ordering_table)
{
    uint32 text;
    uint32 remaining;
    uint32 duration;
    uint32 value;
    FUNCTION_MARKER(0x800194B4, "SLUS_004.64");
    text = r_u32(0x800CF968);
    if ((sint32)text <= 0)
        return;
    remaining = r_u32(0x800CF964);
    if ((sint32)remaining <= 0)
        return;
    duration = r_u32(0x800CF960);
    if (remaining == duration)
    {
        func_800195e4(text);
        duration = r_u32(0x800CF960);
        remaining = r_u32(0x800CF964);
    }
    if (remaining == duration - 2)
    {
        text = r_u32(0x800CF96C);
        if (text != 0)
            func_800196c8(text);
        func_800197d4();
    }
    duration = r_u32(0x800CF960);
    remaining = r_u32(0x800CF964);
    if ((sint32)(duration - 4) >= (sint32)remaining)
    {
        if (r_u32(0x800CF96C) == 0 || r_u32(0x800CF974) != 0)
        {
            w_u16(0x800EC2FA, 20);
            w_u16(0x800EC31E, 20);
            w_u16(0x800EC2F4, 0xFF7C);
            w_u16(0x800EC2F6, 90);
            w_u16(0x800EC318, 0xFFC0);
            w_u16(0x800EC31A, 90);
        }
        GsSortSprite(psx_addr(0x800EC2F0, 36), psx_addr(ordering_table, 20), 0);
        GsSortSprite(psx_addr(0x800EC314, 36), psx_addr(ordering_table, 20), 0);
    }
    value = r_u32(0x800CF964);
    w_u32(0x800CF964, value - 1);
}

void func_800195e4(uint32 text)
{
    uint32 table;
    uint32 parameter;
    uint32 buffer;
    uint32 length;
    const char *input;
    FUNCTION_MARKER(0x800195E4, "SLUS_004.64");
    if ((sint32)text < 1000)
    {
        table = r_u32(0x800CFA50);
        parameter = r_u32(0x800CFA58);
        func_800354b0(0x800EB8C4, table, text, parameter);
    }
    else
    {
        input = guest_c_string(0x800773C4 + 40 * text);
        strcpy((char *)psx_addr(0x800EB8C4, strlen(input) + 1), input);
    }
    w_u32(0x800D771C, 0x800EB8C4);
    w_u32(0x800D7740, 1);
    w_u32(0x800D7730, 0x7FFF);
    w_u32(0x800D7734, 0);
    w_u32(0x800D7720, 943);
    w_u32(0x800D7724, 385);
    w_u32(0x800D7728, 960);
    w_u32(0x800D772C, 496);
    length = (uint32)strlen(guest_c_string(0x800EB8C4));
    w_u32(0x800D7738, length >> 1);
    buffer = r_u32(0x800CFA1C);
    w_u32(0x800D773C, 1);
    w_u32(0x800D7754, buffer);
    w_u32(0x800D7758, buffer + 6880);
    func_8002d700(0x800D771C);
}

void func_800196c8(uint32 text)
{
    uint32 table;
    uint32 parameter;
    uint32 buffer;
    uint32 length;
    const char *input;
    FUNCTION_MARKER(0x800196C8, "SLUS_004.64");
    w_u32(0x800CF974, 0);
    if ((sint32)text < 1000)
    {
        table = r_u32(0x800CFA50);
        parameter = r_u32(0x800CFA58);
        func_800354b0(0x800EB8C4, table, text, parameter);
    }
    else
    {
        input = guest_c_string(0x800773C4 + 40 * text);
        strcpy((char *)psx_addr(0x800EB8C4, strlen(input) + 1), input);
    }
    if (strlen(guest_c_string(0x800EB8C4)) == 0)
    {
        w_u32(0x800CF974, 1);
        return;
    }
    w_u32(0x800D771C, 0x800EB8C4);
    w_u32(0x800D7740, 1);
    w_u32(0x800D7730, 0x7FFF);
    w_u32(0x800D7734, 0);
    w_u32(0x800D7720, 943);
    w_u32(0x800D7724, 405);
    w_u32(0x800D7728, 960);
    w_u32(0x800D772C, 496);
    length = (uint32)strlen(guest_c_string(0x800EB8C4));
    w_u32(0x800D7738, length >> 1);
    buffer = r_u32(0x800CFA1C);
    w_u32(0x800D773C, 1);
    w_u32(0x800D7754, buffer);
    w_u32(0x800D7758, buffer + 6880);
    func_8002d700(0x800D771C);
}

void func_800197d4(void)
{
    uint32 page;
    FUNCTION_MARKER(0x800197D4, "SLUS_004.64");
    w_u32(0x800EC2F0, 64);
    w_u16(0x800EC2F8, 68);
    w_u16(0x800EC2FA, 40);
    w_u16(0x800EC2F4, 0xFF7C);
    w_u16(0x800EC2F6, 80);
    w_u16(0x800EC308, 16);
    w_u16(0x800EC30A, 16);
    page = GetTPage(0, 0, 896, 256);
    w_u16(0x800EC2FC, page);
    w_u8(0x800EC2FE, 0xBC);
    w_u8(0x800EC2FF, 0x81);
    w_u16(0x800EC300, 960);
    w_u16(0x800EC302, 496);
    w_u8(0x800EC304, 0x80);
    w_u8(0x800EC305, 0x80);
    w_u8(0x800EC306, 0x80);
    w_u32(0x800EC310, 0);
    w_u16(0x800EC30C, 4096);
    w_u16(0x800EC30E, 4096);
    w_u32(0x800EC314, 64);
    w_u16(0x800EC31C, 228);
    w_u16(0x800EC31E, 40);
    w_u16(0x800EC318, 0xFFC0);
    w_u16(0x800EC31A, 80);
    w_u16(0x800EC32C, 16);
    w_u16(0x800EC32E, 16);
    page = GetTPage(0, 0, 960, 256);
    w_u16(0x800EC320, page);
    w_u8(0x800EC322, 0);
    w_u8(0x800EC323, 0x81);
    w_u16(0x800EC324, 960);
    w_u16(0x800EC326, 496);
    w_u8(0x800EC328, 0x80);
    w_u8(0x800EC329, 0x80);
    w_u8(0x800EC32A, 0x80);
    w_u32(0x800EC334, 0);
    w_u16(0x800EC330, 4096);
    w_u16(0x800EC332, 4096);
}

uint32 func_800354b0(uint32 destination, uint32 table, uint32 text, uint32 limit)
{
    uint8 hundreds;
    uint8 tens;
    uint8 units;
    uint32 scanned;
    uint32 count;
    uint32 value;
    sint32 number;
    sint32 remainder;
    FUNCTION_MARKER(0x800354B0, "SLUS_004.64");
    number = (sint32)text;
    remainder = number % 100;
    (void)r_u32(0x800CFBE0);
    hundreds = (uint8)((uint32)(number / 100) + 48);
    tens = (uint8)((uint32)(remainder / 10) + 48);
    units = (uint8)((uint32)(remainder % 10) + 48);
    scanned = 0;
    while (r_u8(table) != hundreds || r_u8(table + 1) != tens ||
           r_u8(table + 2) != units || r_u8(table + 3) != ':')
    {
        ++scanned;
        ++table;
        if ((sint32)scanned >= (sint32)limit)
        {
            w_u8(destination, 0);
            return 0;
        }
    }
    table = func_800356c0(table + 4);
    value = r_u8(table);
    count = 0;
    for (;;)
    {
        if (value == 13 && r_u8(table + 1) == 10)
            break;
        if (count >= 129)
            break;
        value = r_u8(table);
        ++table;
        w_u8(destination, value);
        value = r_u8(table);
        ++count;
        ++destination;
        ++table;
        w_u8(destination, value);
        value = r_u8(table);
        ++destination;
    }
    w_u8(destination, 0);
    w_u8(destination + 1, 0);
    return count;
}

uint32 func_800356c0(uint32 text)
{
    uint32 value;
    FUNCTION_MARKER(0x800356C0, "SLUS_004.64");
    for (;;)
    {
        value = r_u8(text);
        if (value != 32 && value != 9)
            return text;
        ++text;
    }
}

static void render_text_core(uint32 descriptor, uint32 *native_descriptor, uint8 *native_text)
{
    PSX_RECT rectangle;
    uint32 palette[2];
    uint32 glyph[16];
    uint8 pixels[304];
    uint32 stride;
    uint32 expanded;
    uint32 packed;
    uint32 cursor;
    uint32 position;
    uint32 character;
    uint32 width;
    uint32 row;
    uint32 column;
    uint32 offset;
    uint32 value;
    sint32 count;
    sint32 cell;
    palette[0] = native_descriptor != 0 ? (uint16)native_descriptor[6] : r_u16(descriptor + 0x18);
    value = native_descriptor != 0 ? (uint16)native_descriptor[5] : r_u16(descriptor + 0x14);
    palette[1] = 0x3DEF;
    palette[0] |= value << 16;
    rectangle.x = native_descriptor != 0 ? (sint16)native_descriptor[3] : (sint16)r_u16(descriptor + 0x0C);
    rectangle.y = native_descriptor != 0 ? (sint16)native_descriptor[4] : (sint16)r_u16(descriptor + 0x10);
    rectangle.w = 4;
    rectangle.h = 1;
    LoadImagePSX(&rectangle, palette);
    value = native_descriptor != 0 ? native_descriptor[1] : r_u32(descriptor + 4);
    stride = (1024 - value) * 4;
    if (native_descriptor != 0)
    {
        native_descriptor[10] = (uint32)((sint32)stride / 4);
        native_descriptor[11] = 20;
    }
    else
    {
        w_u32(descriptor + 0x28, (uint32)((sint32)stride / 4));
        w_u32(descriptor + 0x2C, 20);
    }
    expanded = native_descriptor != 0 ? native_descriptor[14] : r_u32(descriptor + 0x38);
    packed = native_descriptor != 0 ? native_descriptor[15] : r_u32(descriptor + 0x3C);
    for (count = 1719; count >= 0; --count)
        w_u32(expanded + (uint32)count * 4, 0);
    for (count = 1599; count >= 0; --count)
        w_u32(packed + (uint32)count * 4, 0);
    cursor = native_text != 0 ? 0 : (native_descriptor != 0 ? native_descriptor[0] : r_u32(descriptor));
    if (native_descriptor != 0)
        native_descriptor[12] = 0;
    else
        w_u32(descriptor + 0x30, 0);
    character = native_text != 0 ? native_text[cursor] : r_u8(cursor);
    position = 0;
    while (character != 0)
    {
        character = native_text != 0 ? native_text[cursor] : r_u8(cursor);
        if ((sint32)(character - 32) >= 96)
        {
            character = native_text != 0 ? native_text[cursor] : r_u8(cursor);
            if (native_text != 0)
                native_text[cursor] = (uint8)(character + 0xC0);
            else
                w_u8(cursor, character + 0xC0);
        }
        character = native_text != 0 ? native_text[cursor] : r_u8(cursor);
        if ((character == 13 && (native_text != 0 ? native_text[cursor + 1] : r_u8(cursor + 1)) == 10) || character == '|')
            break;
        width = r_u8(0x800B2FF8 + character);
        if (character != 32)
        {
            cell = (sint32)character - 32;
            rectangle.x = (sint16)((cell - (cell / 16) * 16) * 2 + 880);
            character = native_text != 0 ? native_text[cursor] : r_u8(cursor);
            cell = (sint32)character - 32;
            rectangle.y = (sint16)((cell / 16) * 16 + 352);
            rectangle.w = 2;
            rectangle.h = 16;
            StoreImage(&rectangle, glyph);
            DrawSync(0);
            func_8002dbe4(pixels, glyph);
            offset = 0;
            for (row = 0; row < 17; ++row)
            {
                for (column = 0; column < width; ++column)
                    w_u8(expanded + position + column + offset, pixels[row * 17 + column]);
                offset += stride;
            }
        }
        value = native_descriptor != 0 ? native_descriptor[12] : r_u32(descriptor + 0x30);
        ++cursor;
        if (native_descriptor != 0)
            native_descriptor[12] = value + 1;
        else
            w_u32(descriptor + 0x30, value + 1);
        character = native_text != 0 ? native_text[cursor] : r_u8(cursor);
        position += 1 + width;
    }
    func_8002dc84(packed, expanded, 40);
    rectangle.x = native_descriptor != 0 ? (sint16)native_descriptor[1] : (sint16)r_u16(descriptor + 4);
    rectangle.y = native_descriptor != 0 ? (sint16)native_descriptor[2] : (sint16)r_u16(descriptor + 8);
    rectangle.w = (sint16)((sint32)stride / 4);
    rectangle.h = 20;
    LoadImagePSX(&rectangle, (uint32 *)psx_addr(packed, 6400));
    freePSX(packed);
    freePSX(expanded);
}

void func_8002d700(uint32 descriptor)
{
    FUNCTION_MARKER(0x8002D700, "SLUS_004.64");
    render_text_core(descriptor, 0, 0);
}

void render_text_descriptor(uint32 *descriptor)
{
    render_text_core(0, descriptor, 0);
}

void render_guest_text(uint32 descriptor, uint8 *text)
{
    render_text_core(descriptor, 0, text);
}

sint32 func_8002d9e8(uint32 descriptor)
{
    PSX_RECT rectangle;
    FUNCTION_MARKER(0x8002D9E8, "SLUS_004.64");
    rectangle.x = (sint16)r_u16(descriptor + 4);
    rectangle.y = (sint16)r_u16(descriptor + 8);
    rectangle.w = 80;
    rectangle.h = 240;
    return ClearImage(&rectangle, 0, 0, 0);
}

uint32 func_8002da34(uint8 *pixels)
{
    uint32 row;
    uint32 column;
    uint32 previous;
    uint32 current;
    uint32 next;
    uint32 offset;
    FUNCTION_MARKER(0x8002DA34, "SLUS_004.64");
    for (row = 0; row < 17; ++row)
    {
        previous = 0;
        for (column = 0; column < 17; ++column)
        {
            offset = row * 17 + column;
            current = pixels[offset];
            next = column == 16 ? 0 : pixels[offset + 1];
            if (current == 0 && (previous != 0 || next != 0))
                pixels[offset] = 2;
            previous = current;
        }
    }
    for (column = 0; column < 17; ++column)
    {
        previous = 0;
        for (row = 0; row < 17; ++row)
        {
            offset = column + row * 17;
            current = pixels[offset];
            next = row == 16 ? 0 : pixels[offset + 17];
            if (current == 0 && (previous != 0 || next != 0))
                pixels[offset] = 2;
            previous = current;
        }
    }
    return 0;
}

uint32 func_8002db28(uint8 *pixels, const uint8 *glyph)
{
    uint32 index;
    uint32 row;
    sint32 bit;
    uint32 value;
    FUNCTION_MARKER(0x8002DB28, "SLUS_004.64");
    for (index = 0; index < 17; ++index)
        *pixels++ = 0;
    for (row = 0; row < 15; ++row)
    {
        *pixels++ = 0;
        for (bit = 7; bit >= 0; --bit)
        {
            value = (uint32)glyph[0] | ((uint32)glyph[1] << 8);
            *pixels++ = (uint8)((value >> bit) & 1);
        }
        for (bit = 15; bit >= 8; --bit)
        {
            value = (uint32)glyph[0] | ((uint32)glyph[1] << 8);
            *pixels++ = (uint8)((value >> bit) & 1);
        }
        glyph += 2;
    }
    for (index = 0; index < 17; ++index)
        *pixels++ = 0;
    return 0;
}

uint32 func_8002d430(uint32 descriptor)
{
    PSX_RECT rectangle;
    const uint8 *glyph;
    uint32 palette[2];
    uint8 pixels[296];
    uint32 capacity;
    uint32 words;
    uint32 stride;
    uint32 expanded;
    uint32 packed;
    uint32 cursor;
    uint32 second;
    uint32 character;
    uint32 position;
    uint32 value;
    uint32 row;
    uint32 column;
    uint32 offset;
    sint32 count;
    FUNCTION_MARKER(0x8002D430, "SLUS_004.64");
    palette[0] = r_u16(descriptor + 0x18);
    value = r_u16(descriptor + 0x14);
    palette[1] = 0x8000;
    palette[0] |= value << 16;
    rectangle.x = (sint16)r_u16(descriptor + 0x0C);
    rectangle.y = (sint16)r_u16(descriptor + 0x10);
    rectangle.w = 4;
    rectangle.h = 1;
    LoadImagePSX(&rectangle, palette);
    value = r_u32(descriptor + 4);
    stride = (1024 - value) * 4;
    capacity = (uint32)((sint32)stride / 17);
    value = capacity * 17;
    words = (uint32)((sint32)value / 8);
    if (value & 7)
        ++words;
    expanded = r_u32(descriptor + 0x38);
    packed = r_u32(descriptor + 0x3C);
    stride = words * 8;
    w_u32(descriptor + 0x28, words * 2);
    w_u32(descriptor + 0x2C, 20);
    for (count = 1719; count >= 0; --count)
        w_u32(expanded + (uint32)count * 4, 0);
    cursor = r_u32(descriptor);
    w_u32(descriptor + 0x30, 0);
    character = r_u8(cursor);
    position = 0;
    second = cursor + 1;
    while (character != 0)
    {
        character = r_u8(cursor);
        if (character == 13 && r_u8(second) == 10)
            break;
        value = character == 0x81 ? r_u8(second) : 0;
        if (character == 0x81 && value == 0x62)
            break;
        if (character != 0x81 || value != 0x40)
        {
            character = r_u8(cursor);
            value = r_u8(second);
            glyph = Krom2RawAdd2((character << 8) | value);
            func_8002db28(pixels, glyph);
            if (r_u32(descriptor + 0x24) != 0)
                func_8002da34(pixels);
            offset = 0;
            for (row = 0; row < 17; ++row)
            {
                for (column = 0; column < 17; ++column)
                    w_u8(expanded + position + column + offset, pixels[row * 17 + column]);
                offset += stride;
            }
        }
        second += 2;
        value = r_u32(descriptor + 0x30);
        cursor += 2;
        position += 17;
        ++value;
        w_u32(descriptor + 0x30, value);
        if (value == capacity)
            break;
        character = r_u8(cursor);
    }
    func_8002dc84(packed, expanded, (sint32)words);
    rectangle.x = (sint16)r_u16(descriptor + 4);
    rectangle.y = (sint16)r_u16(descriptor + 8);
    rectangle.w = (sint16)(words * 2);
    rectangle.h = 20;
    LoadImagePSX(&rectangle, (uint32 *)psx_addr(packed, words * 80));
    freePSX(packed);
    freePSX(expanded);
    return words * 2;
}

sint32 func_80020e78(sint32 movie, uint32 mode)
{
#ifdef AP_WEB
    /* STR media is excluded from the Web package */
    return 2;
#else
    uint32 descriptor[16];
    uint32 base;
    uint32 offset;
    uint32 value;
    PSX_RECT rectangle;
    sint32 result;
    FUNCTION_MARKER(0x80020E78, "SLUS_004.64");
    DrawSync(0);
    VSync(2);
    ResetGraph(0);
    func_800378e8();
    func_800392e0();
    PadInit(0);
    base = r_u32(0x800CFA28);
    offset = (uint32)movie * 56;
    w_u32(0x800CFA2C, base + 416256);
    descriptor[0] = 0x800B235C + offset;
    descriptor[2] = r_u32(0x800B2384 + offset);
    descriptor[3] = r_u32(0x800B2388 + offset);
    descriptor[4] = r_u32(0x800B237C + offset);
    descriptor[5] = r_u32(0x800B2380 + offset);
    value = r_u32(0x800B238C + offset) * 3;
    descriptor[6] = (uint32)((sint32)value / 2);
    descriptor[7] = r_u32(0x800B2390 + offset);
    value = r_u32(0x800B238C + offset) * 3;
    descriptor[8] = (uint32)((sint32)value / 2);
    value = r_u32(0x800B2390 + offset);
    descriptor[10] = base;
    descriptor[11] = base + 65536;
    descriptor[12] = base + 229376;
    descriptor[13] = base + 393216;
    descriptor[14] = base + 404736;
    descriptor[15] = mode;
    descriptor[9] = value + 240;
    descriptor[1] = 1;
    SetDispMask(0);
    VSync(0);
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 480;
    rectangle.h = 480;
    ClearImage(&rectangle, 0, 0, 0);
    result = func_80030b9c(descriptor);
    VSync(0);
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 480;
    rectangle.h = 480;
    ClearImage(&rectangle, 0, 0, 0);
    DrawSync(0);
    VSync(0);
    GsSwapDispBuff();
    return result;
#endif
}

uint32 func_80026840(void)
{
    uint32 increment;
    uint32 value;
    uint32 direction;
    uint32 index;
    uint32 offset;
    uint32 object;
    uint32 x;
    FUNCTION_MARKER(0x80026840, "SLUS_004.64");
    value = r_u32(0x800EDFF8);
    if (value == 0)
        return value;
    increment = r_u32(0x800EE000);
    value = r_u32(0x800EE004);
    value += increment << 7;
    w_u32(0x800EE004, value);
    if ((sint32)value > 5120)
        w_u32(0x800EE004, 0);
    direction = r_u32(0x800EE008);
    value = r_u32(0x800EE00C);
    value += direction * 4;
    w_u32(0x800EE00C, value);
    if (direction == 1)
    {
        if ((sint32)value >= 65)
            w_u32(0x800EE008, 0xFFFFFFFF);
    }
    else if (r_s32(0x800EE00C) < -64)
        w_u32(0x800EE008, 1);
    for (index = 0; index < 8; ++index)
    {
        offset = index * 52;
        value = r_u32(0x8008197C + (index / 2) * 4);
        w_u32(0x800EE0A8 + offset, value);
        if (value == 0)
            continue;
        object = r_u32(0x800DDD48 + (index / 2 + 1) * 16);
        value = r_u32(object + 0x18);
        w_u32(0x800EE0B8 + offset, value);
        value = r_u32(0x800EDFFC);
        increment = r_u32(0x800EE00C);
        w_u32(0x800EE0BC + offset, value + increment + ((index & 1) << 6));
        object = r_u32(0x800DDD48 + (index / 2 + 1) * 16);
        value = r_u32(object + 0x20);
        w_u32(0x800EE0C0 + offset, value);
        x = r_u32(0x800EE004);
        value = (index & 1) ? 5120 - x + 3072 : x + 3072;
        w_u32(0x800EE0C4 + offset, value);
        x = r_u32(0x800EE004);
        value = (index & 1) ? 5120 - x + 3072 : x + 3072;
        w_u32(0x800EE0CC + offset, value);
    }
    return 16;
}

uint32 func_8003213c(uint32 object, uint32 action)
{
    uint32 offset;
    uint32 cursor;
    uint32 entry;
    FUNCTION_MARKER(0x8003213C, "SLUS_004.64");
    offset = object * 1040;
    cursor = r_u32(0x800DB6FC + offset);
    w_u32(0x800DB6F0 + offset, 1);
    entry = offset + cursor * 32;
    w_u32(0x800DB2F0 + entry, action);
    w_u32(0x800DB2F4 + entry, 1);
    w_u32(0x800DB2F8 + entry, 0);
    w_u32(0x800DB2FC + entry, 0);
    w_u32(0x800DB300 + entry, 0);
    w_u32(0x800DB6F8 + offset, 0xFFFFFFFF);
    w_u32(0x800DB6F4 + offset, 0);
    ++cursor;
    if ((sint32)cursor >= 32)
        cursor = 0;
    entry = offset + cursor * 32;
    w_u32(0x800DB2F0 + entry, 0xFFFFFFFF);
    return entry;
}

uint32 func_80032030(uint32 object, uint32 action)
{
    uint32 offset;
    uint32 cursor;
    uint32 entry;
    FUNCTION_MARKER(0x80032030, "SLUS_004.64");
    offset = object * 1040;
    cursor = r_u32(0x800DB6FC + offset) + 1;
    if ((sint32)cursor >= 32)
        cursor = 0;
    w_u32(0x800DB6F0 + offset, 1);
    entry = offset + cursor * 32;
    w_u32(0x800DB2F0 + entry, action);
    w_u32(0x800DB2F4 + entry, 1);
    w_u32(0x800DB2F8 + entry, 0);
    w_u32(0x800DB2FC + entry, 0);
    w_u32(0x800DB300 + entry, 0);
    ++cursor;
    if ((sint32)cursor >= 32)
        cursor = 0;
    entry = offset + cursor * 32;
    w_u32(0x800DB2F0 + entry, 0xFFFFFFFF);
    w_u32(0x800DB6F8 + offset, 0xFFFFFFFF);
    w_u32(0x800DB6F4 + offset, 0xFFFFFFFF);
    return entry;
}

uint32 func_80031ee0(uint32 object, uint32 first, uint32 second)
{
    FUNCTION_MARKER(0x80031EE0, "SLUS_004.64");
    func_80032030(object, first);
    func_80031d18(object, second);
    return func_80032320(object, second);
}

uint32 func_80031f28(uint32 object, uint32 first, uint32 second)
{
    FUNCTION_MARKER(0x80031F28, "SLUS_004.64");
    func_8003213c(object, first);
    func_80032030(object, second);
    return func_80032320(object, second);
}

uint32 func_8003271c(uint32 bit, uint32 enabled)
{
    uint32 address;
    uint32 value;
    uint32 mask;
    FUNCTION_MARKER(0x8003271C, "SLUS_004.64");
    address = 0x800EECD8 + (bit >> 5) * 4;
    value = r_u32(address);
    mask = (uint32)1 << (bit & 31);
    value = enabled != 0 ? value | mask : value & ~mask;
    w_u32(address, value);
    return value;
}

void func_800287dc(uint32 ordering_table, uint32 red, uint32 green, uint32 blue, uint32 x, uint32 y, uint32 width, uint32 height, uint32 priority)
{
    uint32 box[4];
    FUNCTION_MARKER(0x800287DC, "SLUS_004.64");
    box[0] = 0;
    box[1] = (uint16)x | ((uint32)(uint16)y << 16);
    box[2] = (uint16)width | ((uint32)(uint16)height << 16);
    box[3] = (uint8)red | ((uint32)(uint8)green << 8) | ((uint32)(uint8)blue << 16);
    GsSortBoxFill(box, psx_addr(ordering_table, 20), priority);
}

uint32 func_80028898(uint32 mode)
{
    FUNCTION_MARKER(0x80028898, "SLUS_004.64");
    func_80013394();
    func_80013394();
    DrawSync(0);
    func_80040f0c(128, 0, mode);
    while (func_80041114() != 0)
    {
    }
    w_u32(0x800CF850, 1);
    return 1;
}

sint32 func_80018100(uint32 resource, uint32 value0, uint32 value1)
{
    PSX_RECT rectangle;
    uint32 buffer;
    sint32 result;
    FUNCTION_MARKER(0x80018100, "SLUS_004.64");
    func_80017a74();
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 320;
    rectangle.h = 480;
    ClearImage(&rectangle, 0, 0, 0);
    func_8001eff8();
    func_8003943c(0);
    buffer = r_u32(0x800CF9FC);
    result = func_80039dc4(resource, value0, value1, buffer);
    w_u32(0x800CF8D8, 0);
    return result;
}

void func_80018190(void)
{
    FUNCTION_MARKER(0x80018190, "SLUS_004.64");
    func_8001eff8();
    (void)r_u32(0x800EE7E4);
    func_80022a68();
    func_8001f0ac();
    w_u32(0x800CFA90, 0);
}

uint32 func_80022a68(void)
{
    uint32 action;
    FUNCTION_MARKER(0x80022A68, "SLUS_004.64");
    w_u32(0x800CF87C, 0);
    action = r_u32(0x800EE7E4);
    return func_80022ab0(action, 1, 0, 1, 1, 1, 1, 1);
}

void func_80015fa0(void)
{
    uint32 script;
    uint32 object;
    FUNCTION_MARKER(0x80015FA0, "SLUS_004.64");
    script = r_u32(0x800CFF7C);
    if (script != 0)
    {
        object = r_u32(0x800CFA6C);
        w_u32(0x800EE7D8, 0);
        w_u32(0x800EE7DC, script);
        w_u32(0x800EE7E0, 0);
        func_80032d68(object, script);
        w_u32(0x800EE7E0, 0);
        w_u32(0x800EE7DC, 0);
        w_u32(0x800EE7D8, 0);
        w_u32(0x800CFF7C, 0);
    }
}

void func_80015e28(void)
{
    uint32 first;
    uint32 second;
    uint32 script;
    uint32 object;
    uint32 input;
    FUNCTION_MARKER(0x80015E28, "SLUS_004.64");
    first = r_u32(0x800CFE0C);
    second = r_u32(0x800CFE1C);
    if (first != 0)
    {
        object = r_u32(0x800CFA6C);
        w_u32(0x800EE7D8, 1);
        w_u32(0x800EE7DC, first);
        w_u32(0x800EE7E0, 0);
        func_80032d68(object, first);
        w_u32(0x800EE7E0, 0);
        w_u32(0x800EE7DC, 0);
        w_u32(0x800EE7D8, 0);
    }
    script = r_u32(0x800CFE1C);
    if (script != 0 && r_u32(0x800CFE0C) != script)
    {
        object = r_u32(0x800CFA6C);
        w_u32(0x800EE7D8, 1);
        w_u32(0x800EE7DC, script);
        w_u32(0x800EE7E0, 0);
        func_80032d68(object, script);
        w_u32(0x800EE7E0, 0);
        w_u32(0x800EE7DC, 0);
        w_u32(0x800EE7D8, 0);
    }
    w_u32(0x800CFE0C, 0);
    w_u32(0x800CFE1C, 0);
    if (first == 0 && second == 0)
        return;
    input = func_80012658();
    w_u32(0x800CF934, input);
    while (input & 0x40)
    {
        if (r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0)
            break;
        func_80012bfc();
        script = r_u32(0x800CFF7C);
        if (script != 0)
        {
            object = r_u32(0x800CFA6C);
            w_u32(0x800EE7D8, 0);
            w_u32(0x800EE7DC, script);
            w_u32(0x800EE7E0, 0);
            func_80032d68(object, script);
            w_u32(0x800EE7E0, 0);
            w_u32(0x800EE7DC, 0);
            w_u32(0x800EE7D8, 0);
            w_u32(0x800CFF7C, 0);
        }
        input = r_u32(0x800CF934);
    }
}

void func_80015c74(void)
{
    uint32 script;
    uint32 object;
    uint32 parameter;
    uint32 selected;
    uint32 mask;
    FUNCTION_MARKER(0x80015C74, "SLUS_004.64");
    script = r_u32(0x800CFF6C);
    w_u32(0x800EE804, 0);
    if (script != 0)
    {
        w_u32(0x800EE7D8, 2);
        parameter = r_u32(0x800CF924);
        object = r_u32(0x800CFA6C);
        w_u32(0x800EE7DC, script);
        w_u32(0x800EE7E0, parameter);
        func_80032d68(object, script);
        w_u32(0x800EE7E0, 0);
        w_u32(0x800EE7DC, 0);
        w_u32(0x800EE7D8, 0);
    }
    script = r_u32(0x800CFD9C);
    if (script != 0 && r_u32(0x800CFF6C) != script)
    {
        w_u32(0x800EE7D8, 2);
        parameter = r_u32(0x800CF924);
        object = r_u32(0x800CFA6C);
        w_u32(0x800EE7DC, script);
        w_u32(0x800EE7E0, parameter);
        func_80032d68(object, script);
        w_u32(0x800EE7E0, 0);
        w_u32(0x800EE7DC, 0);
        w_u32(0x800EE7D8, 0);
    }
    if ((r_u32(0x800CFF6C) != 0 || r_u32(0x800CFD9C) != 0) &&
        r_u32(0x800EE804) == 0 && r_s32(0x800EE7EC) > 0)
    {
        if (r_u32(0x800CFE24) == 0)
        {
            func_8001f87c();
            selected = r_u32(0x800EE7EC);
            func_8001f8a0(selected + 1011, 0, 36000);
            func_8001f92c();
            mask = r_u32(0x800CF870);
            w_u32(0x800CFF6C, 0);
            w_u32(0x800CFD9C, 0);
            w_u32(0x800CF870, mask | 0x40);
            func_8001fbcc();
            func_8001fa08();
            func_8001fbd8();
            func_8001f87c();
        }
        else
        {
            func_8001f87c();
            selected = r_u32(0x800EE7EC);
            func_8001f8a0(selected + 1011, 0, 60);
            func_8001f92c();
        }
    }
    w_u32(0x800CFF6C, 0);
    w_u32(0x800CFD9C, 0);
}

void func_80015c44(void)
{
    FUNCTION_MARKER(0x80015C44, "SLUS_004.64");
    func_80015fa0();
    func_80015e28();
    func_80015c74();
}

void func_8001fbcc(void)
{
    FUNCTION_MARKER(0x8001FBCC, "SLUS_004.64");
    w_u32(0x800CF910, 0);
}

uint32 func_8001fbd8(void)
{
    FUNCTION_MARKER(0x8001FBD8, "SLUS_004.64");
    w_u32(0x800CF910, 1);
    return 1;
}

uint32 func_8001fa08(void)
{
    uint32 result;
    uint32 cursor;
    FUNCTION_MARKER(0x8001FA08, "SLUS_004.64");
    for (;;)
    {
        func_80014c74();
        result = r_u32(0x800CF844);
        if (result == 2)
            return result;
        result = r_u32(0x800CF8DC);
        if (result != 0)
            return result;
        result = r_u32(0x800CF8E0);
        if (result != 0)
            return result;
        if (r_s32(0x800CF964) <= 0)
        {
            cursor = r_u32(0x800CF97C);
            result = r_u32(0x800D85AC + cursor * 12);
            if (result == 0xFFFFFFFF)
                return result;
        }
        func_80012c60();
        func_80015fa0();
        w_u32(0x800CF850, 0);
    }
}

void func_800254b8(uint32 mode, uint32 object)
{
    uint32 action;
    uint32 x;
    uint32 y;
    uint32 z;
    uint32 collision;
    uint32 input;
    uint32 shift;
    uint32 count;
    FUNCTION_MARKER(0x800254B8, "SLUS_004.64");
    (void)r_u32(0x800109D0);
    (void)r_u32(0x800109D4);
    (void)r_u32(0x800109D8);
    action = func_80031954(object);
    x = func_8003240c(object);
    y = func_8003244c(object);
    z = func_8003248c(object);
    if (r_u32(0x800CFF3C) == 0 &&
        (action == 37 || action - 2 < 2 || action == 1 || action - 8 < 2 ||
         action - 6 < 2 || action == 21 || action == 34))
        z = 0;
    if (x == 0 && y == 0 && z == 0)
        return;
    if (r_u32(0x800CFE24) != 0)
        func_80023d9c(4, 1);
    collision = r_u32(0x800CFE4C);
    collision = func_80019e24(object, collision, x, y, z, action);
    if (collision == 0)
    {
        if (r_u32(0x800CFE24) == 0)
        {
            input = r_u32(0x800CF934);
            shift = (mode << 4) & 31;
            if ((((uint32)32 << shift) & input) != 0 &&
                (((uint32)4096 << shift) & input) != 0 &&
                action - 16 >= 2 && action != 18 && action - 8 >= 2 &&
                action != 32 && action != 34 && action != 1 &&
                r_u32(0x800EDFCC) != 0)
            {
                func_80031c20(object, 16, 1, 0, 0, 0xFFFFFFEC);
                func_80031b14(object, 17, 1, 0, 0, 60);
                func_800319c0(object, 18, 1, 0, 0, 60);
                func_80032354(object, 1, 18);
            }
        }
    }
    else
    {
        count = r_u32(0x800CFAC4) + 1;
        w_u32(0x800CFAC4, count);
        if ((sint32)count < 13)
            return;
        if (action == 17)
            func_80031ee0(object, 19, 0);
        else if (action == 18)
            func_80031ee0(object, 20, 0);
    }
    w_u32(0x800CFAC4, 0);
}

void func_80025758(uint32 object, uint32 action)
{
    FUNCTION_MARKER(0x80025758, "SLUS_004.64");
    switch (action)
    {
    case 0:
        func_80031c20(object, 1, 1, 0, 0, 0);
        func_80031b14(object, 2, 1, 0, 0, 0);
        func_800319c0(object, 4, 1, 0, 0, 0);
        func_80032354(object, 2, 4);
        break;
    case 17:
        func_80031ee0(object, 19, 0);
        break;
    case 18:
        func_80031ee0(object, 20, 0);
        break;
    case 32:
        if (r_u32(0x800CFE24) == 0)
        {
            func_80031c20(object, 34, 1, 0, 0, 0);
            func_80032320(object, 34);
        }
        break;
    case 36:
        if (r_u32(0x800CFE24) == 0)
        {
            func_80031c20(object, 37, 1, 0, 0, 0);
            func_80031b14(object, 3, 1, 0, 0, 0);
            func_800319c0(object, 5, 1, 0, 0, 0);
            func_800319c0(object, 35, 1, 0, 0, 0);
            func_80032354(object, 3, 35);
        }
        break;
    case 37:
        if (r_u32(0x800CFE24) != 0 && r_u32(0x800CFB1C) == 0)
            func_80031f28(object, 39, 0);
        break;
    default:
        break;
    }
}

void func_80025940(uint32 object, uint32 action, uint32 unused, uint32 transform)
{
    uint32 coordinate;
    uint32 value;
    FUNCTION_MARKER(0x80025940, "SLUS_004.64");
    (void)unused;
    if (action > 2 && action != 4 && action != 36 && action - 43 >= 2 && action - 49 >= 2)
        return;
    func_80031c20(object, 12, 1, 0, 0, 0);
    func_80031b14(object, 13, 1, 0, 0, 0);
    func_800319c0(object, 14, 1, 0, 0, 0);
    func_800319c0(object, 15, 1, 0, 0, 0);
    func_800319c0(object, 0, 1, 0, 0, 0);
    func_80032320(object, 0);
    w_u32(0x800CFF24, 1);
    w_u32(0x800CFE64, 1);
    coordinate = r_u32(transform + 4);
    value = r_u32(coordinate + 0x18);
    w_u32(0x800F02F0 + object * 4, value);
    coordinate = r_u32(transform + 4);
    value = r_u32(coordinate + 0x1C);
    w_u32(0x800F0310 + object * 4, value);
    coordinate = r_u32(transform + 4);
    value = r_u32(coordinate + 0x20);
    w_u32(0x800F0330 + object * 4, value);
}
