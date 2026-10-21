#include "functions.h"
#include <string.h>
#include <assert.h>

/* Full original bodies, pending final integration and runtime validation */
void func_8002e030(void)
{
    char format[32], message[128];
    uint8 number[16];
    uint32 words[3];
    uint32 index, value, clut_x, clut_y;
    FUNCTION_MARKER(0x8002E030, "SLUS_004.64");
    for (index = 0; index < 3; ++index)
    {
        r_u32(0x80011028 + index * 4);
        words[index] = r_u32(0x80011028 + index * 4);
    }
    memcpy(format, words, 12);
    for (index = 0; index < 2; ++index)
    {
        r_u32(0x80011034 + index * 4);
        words[index] = r_u32(0x80011034 + index * 4);
    }
    memcpy(format + 12, words, 8);
    format[20] = (char)r_s8(0x8001103C);
    memset(format + 21, 0, 11);
    w_u32(0x800D7740, 1);
    w_u32(0x800D7730, 0xFFFF);
    w_u32(0x800D7734, 0);
    w_u32(0x800D7720, 960);
    w_u32(0x800D7724, 256);
    w_u32(0x800D7728, 896);
    w_u32(0x800D772C, 496);
    w_u32(0x800D7720, 960);
    func_8002df08(number, 45);
    message[0] = 0;
    sprintf(message, format, (char *)number);
    value = (uint32)strlen(message);
    w_u32(0x800D7738, value >> 1);
    w_u32(0x800D773C, 6);
    w_u32(0x800D7724, 485);
    value = r_u32(0x800CFA1C);
    w_u32(0x800D7754, value);
    w_u32(0x800D7758, value + 0x1AE0);
    render_guest_text(0x800D771C, (uint8 *)message);
    clut_x = r_u32(0x800D7728);
    clut_y = r_u32(0x800D772C);
    func_8002f9b0(0x800DEF68, 960, 256, 0, 229, 76, 150, 44, 20, clut_x, clut_y);
    clut_x = r_u32(0x800D7728);
    clut_y = r_u32(0x800D772C);
    func_8002f9b0(0x800DEF8C, 960, 256, 52, 229, 76, 192, 48, 20, clut_x, clut_y);
    func_8001aa28(0x800E9F18, 0x800EC394, 0, 20, 20, 20);
    func_8001aa28(0x800E9F18, 0x800EC3B8, 0, 40, 20, 20);
    w_u16(0x800EC398, 56);
    w_u16(0x800EC39A, 150);
    w_u16(0x800EC3BC, 56);
    w_u16(0x800EC3BE, 192);
}

void func_8002fe68(uint32 item)
{
    char message[128];
    uint32 state, value, scratch, name, flags;
    sint32 index;
    FUNCTION_MARKER(0x8002FE68, "SLUS_004.64");
    state = r_u32(0x800CF91C);
    switch (state)
    {
    case 0:
        for (index = 3; index >= 0; --index)
            w_u32(0x800EB9D4 + (uint32)index * 4, 0);
        w_u32(0x800D771C, 0x800CFBB8);
        w_u32(0x800D7740, 1);
        w_u32(0x800D7730, 0xFFFF);
        w_u32(0x800D7734, 0);
        w_u32(0x800D7720, 960);
        w_u32(0x800D7724, 385);
        w_u32(0x800D7728, 896);
        w_u32(0x800D772C, 496);
        value = (uint32)strlen(guest_c_string(0x800CFBB8));
        state = r_u32(0x800CF91C);
        w_u32(0x800D7738, value >> 1);
        w_u32(0x800D773C, 4);
        w_u32(0x800CF91C, state + 1);
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
    case 10:
        state = r_u32(0x800CF91C);
        w_u32(0x800CF91C, state + 1);
        break;
    case 2:
        value = r_u32(0x800EE010);
        name = 0x800B3590 + value * 160;
        sprintf(message, guest_c_string(0x800CFBBC), guest_c_string(name));
        value = (uint32)strlen(message);
        value = ((320 - (value << 3)) >> 1) - 160;
        w_u32(0x800D775C, value);
        scratch = r_u32(0x800CFA1C);
        w_u32(0x800D7720, 960);
        w_u32(0x800D7724, 385);
        w_u32(0x800D7754, scratch);
        w_u32(0x800D7758, scratch + 0x1AE0);
        value = (uint32)strlen(message);
        w_u32(0x800D7738, value >> 1);
        render_guest_text(0x800D771C, (uint8 *)message);
        func_8002f7c0(0);
        state = r_u32(0x800CF91C);
        w_u16(0x800E9C1E, 0xFFC4);
        w_u32(0x800CF91C, state + 1);
        break;
    case 4:
        scratch = r_u32(0x800CFA1C);
        w_u32(0x800D771C, 0x800CFBC0);
        w_u32(0x800D7720, 960);
        w_u32(0x800D7724, 405);
        w_u32(0x800D7754, scratch);
        w_u32(0x800D7758, scratch + 0x1AE0);
        value = (uint32)strlen(guest_c_string(0x800CFBC0));
        w_u32(0x800D7738, value >> 1);
        func_8002d700(0x800D771C);
        func_8002f7c0(1);
        state = r_u32(0x800CF91C);
        w_u16(0x800E9C42, 0xFFD8);
        w_u32(0x800D7764, 0xFFFFFFEC);
        w_u32(0x800CF91C, state + 1);
        break;
    case 6:
        scratch = r_u32(0x800CFA1C);
        w_u32(0x800D771C, 0x800CFBC8);
        w_u32(0x800D7720, 960);
        w_u32(0x800D7724, 425);
        w_u32(0x800D7754, scratch);
        w_u32(0x800D7758, scratch + 0x1AE0);
        value = (uint32)strlen(guest_c_string(0x800CFBC8));
        w_u32(0x800D7738, value >> 1);
        func_8002d700(0x800D771C);
        func_8002f7c0(2);
        w_u16(0x800E9C66, 80);
        w_u32(0x800D776C, 0xFFFFFFBA);
        flags = r_u32(0x800E9C60);
        state = r_u32(0x800CF91C);
        w_u32(0x800E9C60, flags & 0xFFFFFFBF);
        w_u32(0x800CF91C, state + 1);
        break;
    case 8:
        scratch = r_u32(0x800CFA1C);
        w_u32(0x800D771C, 0x800CFBD0);
        w_u32(0x800D7720, 960);
        w_u32(0x800D7724, 445);
        w_u32(0x800D7754, scratch);
        w_u32(0x800D7758, scratch + 0x1AE0);
        value = (uint32)strlen(guest_c_string(0x800CFBD0));
        w_u32(0x800D7738, value >> 1);
        func_8002d700(0x800D771C);
        func_8002f7c0(3);
        w_u16(0x800E9C8A, 100);
        w_u32(0x800D7774, 0xFFFFFFBA);
        state = r_u32(0x800CF91C);
        flags = r_u32(0x800E9C84);
        w_u32(0x800CF91C, state + 1);
        w_u32(0x800E9C84, flags & 0xFFFFFFBF);
        break;
    default:
        break;
    }
}

uint32 *func_80037a30(uint32 *result, uint32 table, uint32 mode)
{
    PSX_RECT rectangle;
    uint32 count, cursor, visible, last, scroll_limit, row;
    uint32 selected, scroll, label, input, choice, entry, value;
    FUNCTION_MARKER(0x80037A30, "SLUS_004.64");
    func_800385b4();
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 320;
    rectangle.h = 480;
    ClearImage(&rectangle, 0, 0, 0);
    count = 0;
    if (r_u32(table + 4) != 0xFFFFFFFF)
    {
        cursor = table;
        do
        {
            cursor += 20;
            value = r_u32(cursor + 4);
            ++count;
        } while (value != 0xFFFFFFFF);
    }
    FntLoad(960, 256);
    SetDumpFnt(FntOpen(-80, -40, 160, 80, 1, 512));
    visible = (sint32)count < 7 ? count : 7;
    last = visible - 1;
    scroll_limit = count - visible;
    for (;;)
    {
        FntPrint(guest_c_string(0x800114F0));
        cursor = table;
        for (row = 0; (sint32)row < (sint32)visible; ++row)
        {
            selected = r_u32(0x800CFBEC);
            scroll = r_u32(0x800CFBF0);
            label = r_u32(cursor + 20 * scroll + 4);
            FntPrint(guest_c_string(selected == row ? 0x800CFC04 : 0x800CFC0C), guest_c_string(label));
            cursor += 20;
        }
        input = func_8003816c();
        if (input == 6)
        {
            selected = r_u32(0x800CFBEC);
            scroll = r_u32(0x800CFBF0);
            choice = func_80037df8(table + 20 * selected + 20 * scroll, selected + scroll);
            if (choice != 0xFFFFFFFF)
            {
                selected = r_u32(0x800CFBEC);
                scroll = r_u32(0x800CFBF0);
                entry = table + 20 * selected + 20 * scroll;
                value = r_u32(entry);
                if (value == 0)
                {
                    cursor = r_u32(entry + 12);
                    value = r_u32(cursor + (choice << 2));
                }
                else
                    value = choice;
                result[0] = selected + scroll;
                result[1] = choice;
                result[2] = value;
                return result;
            }
        }
        if (input == 1)
        {
            selected = r_u32(0x800CFBEC) - 1;
            w_u32(0x800CFBEC, selected);
            if ((sint32)selected < 0)
            {
                scroll = r_u32(0x800CFBF0);
                if (scroll != 0)
                    w_u32(0x800CFBF0, scroll - 1);
                w_u32(0x800CFBEC, 0);
            }
        }
        if (input == 2)
        {
            selected = r_u32(0x800CFBEC) + 1;
            w_u32(0x800CFBEC, selected);
            if ((sint32)last < (sint32)selected)
            {
                scroll = r_u32(0x800CFBF0);
                if (scroll != scroll_limit)
                    w_u32(0x800CFBF0, scroll + 1);
                w_u32(0x800CFBEC, last);
            }
        }
        if (input == 3)
        {
            scroll = r_u32(0x800CFBF0);
            w_u32(0x800CFBF0, (sint32)scroll < (sint32)visible ? 0 : scroll - visible);
        }
        if (input == 4)
        {
            selected = r_u32(0x800CFBEC);
            scroll = r_u32(0x800CFBF0);
            value = selected - (visible << 1) + 1;
            w_u32(0x800CFBF0, (sint32)value < (sint32)scroll ? scroll_limit : visible + scroll);
        }
        if (input == 9)
        {
            w_u32(0x800CFBF0, 0);
            w_u32(0x800CFBEC, 0);
        }
        if (input == 10)
        {
            w_u32(0x800CFBF0, scroll_limit);
            w_u32(0x800CFBEC, last);
        }
        if (input == 5 && mode != 0)
        {
            /* Cancellation has no defined payload */
            result[0] = 0xFFFFFFFF;
            return result;
        }
        FntFlush(-1);
        DrawSync(0);
        VSync(0);
        GsSwapDispBuff();
    }
}

sint32 func_80069b68(const uint8 *position)
{
    CdlLOC location;
    FUNCTION_MARKER(0x80069B68, "SLUS_004.64");
    location.minute = position[0];
    location.second = position[1];
    location.sector = position[2];
    return CdPosToInt(&location);
}

void func_80047dec(uint32 value)
{
    FUNCTION_MARKER(0x80047DEC, "SLUS_004.64");
    SetGeomScreen((sint32)value);
}

void func_8004e5a4(uint32 ordering_table)
{
    uint32 tag;
    FUNCTION_MARKER(0x8004E5A4, "SLUS_004.64");
    tag = r_u32(ordering_table + 16);
    DrawOTag((uint32 *)psx_addr(tag, 4));
}

sint32 func_8006ed60(void)
{
    FUNCTION_MARKER(0x8006ED60, "SLUS_004.64");
    return SpuSetReverb(1);
}

sint32 func_800416a0(void)
{
    FUNCTION_MARKER(0x800416A0, "SLUS_004.64");
    return EnterCriticalSectionPSX();
}

void func_80041750(void)
{
    FUNCTION_MARKER(0x80041750, "SLUS_004.64");
    ExitCriticalSection();
}

void func_8007b714(void)
{
    FUNCTION_MARKER(0x8007B714, "SLUS_004.64");
    SpuInit();
}

void func_8006f184(void)
{
    FUNCTION_MARKER(0x8006F184, "SLUS_004.64");
    spu_sequence_start_timer(1);
}

void func_8006f8b0(uint32 mode)
{
    FUNCTION_MARKER(0x8006F8B0, "SLUS_004.64");
    SsSetTickMode((sint32)mode);
}

void func_800393a0(void)
{
    FUNCTION_MARKER(0x800393A0, "SLUS_004.64");
    func_8007cc3c();
    func_8006eb20();
    func_8006f8b0(0x1000);
    SpuInitMalloc(64, (char *)psx_addr(0x800E9850, 520));
    func_8006f184();
    func_800392e0();
}

uint32 func_80042490(uint32 mode)
{
    FUNCTION_MARKER(0x80042490, "SLUS_004.64");
    return xport_bios_init_card(mode);
}

uint32 func_800424a0(void)
{
    FUNCTION_MARKER(0x800424A0, "SLUS_004.64");
    return xport_bios_start_card();
}

sint32 func_800416f0(const char *path)
{
    FUNCTION_MARKER(0x800416F0, "SLUS_004.64");
    return erase(path);
}

void *func_80041770(const char *pattern, void *entry)
{
    FUNCTION_MARKER(0x80041770, "SLUS_004.64");
    return firstfile(pattern, entry);
}

void func_8007594c(sint16 sequence, sint16 separation)
{
    FUNCTION_MARKER(0x8007594C, "SLUS_004.64");
    play_sequence_tick(sequence, separation);
}

void func_80078c0c(sint16 sequence, sint16 separation)
{
    FUNCTION_MARKER(0x80078C0C, "SLUS_004.64");
    func_8007594c(sequence, separation);
}

uint32 func_80073654(sint16 sequence)
{
    FUNCTION_MARKER(0x80073654, "SLUS_004.64");
    spu_sequence_vm_sequence_key_off(sequence);
    /* The original exits with a zero loop comparison */
    return 0;
}

uint32 func_80078154(sint16 sequence, sint16 separation)
{
    FUNCTION_MARKER(0x80078154, "SLUS_004.64");
    return spu_sequence_scheduler_stop(&spu_sequence_scheduler, sequence, separation, func_80073654);
}

uint32 func_80078c38(sint16 sequence)
{
    FUNCTION_MARKER(0x80078C38, "SLUS_004.64");
    return spu_sequence_scheduler_close(&spu_sequence_scheduler, sequence, func_80073058, func_80073654);
}

uint32 func_8007353c(sint16 sequence, uint16 *left, uint16 *right)
{
    FUNCTION_MARKER(0x8007353C, "SLUS_004.64");
    return spu_sequence_vm_get_sequence_volume(&spu_sequence_scheduler, sequence, left, right);
}

uint32 func_80078dd8(sint16 sequence)
{
    FUNCTION_MARKER(0x80078DD8, "SLUS_004.64");
    return func_80078c38(sequence);
}

uint32 func_80073058(sint16 sequence, sint16 left, sint16 right, sint16 mode)
{
    FUNCTION_MARKER(0x80073058, "SLUS_004.64");
    return spu_sequence_vm_set_sequence_volume(&spu_sequence_scheduler, sequence, left, right, mode);
}

uint32 func_8007babc(const void *source, uint32 bytes)
{
    FUNCTION_MARKER(0x8007BABC, "SLUS_004.64");
    return SpuWrite(source, bytes);
}

uint32 func_80077634(sint16 sequence, sint16 separation)
{
    FUNCTION_MARKER(0x80077634, "SLUS_004.64");
    return spu_sequence_scheduler_read_delta(&spu_sequence_scheduler, sequence, separation);
}

uint32 func_80075e04(sint16 sequence, sint16 separation, uint8 program)
{
    FUNCTION_MARKER(0x80075E04, "SLUS_004.64");
    return spu_sequence_scheduler_program_change(&spu_sequence_scheduler, sequence, separation, program, func_80077634);
}

void func_80075a60(sint16 sequence, sint16 separation)
{
    FUNCTION_MARKER(0x80075A60, "SLUS_004.64");
    read_sequence_event(sequence, separation);
}

uint32 func_8006fb40(void)
{
    FUNCTION_MARKER(0x8006FB40, "SLUS_004.64");
    return spu_sequence_vm_allocate();
}

uint32 func_800702cc(void)
{
    FUNCTION_MARKER(0x800702CC, "SLUS_004.64");
    return spu_sequence_vm_prepare_voice();
}

uint32 func_80075d10(sint16 sequence, sint16 separation, uint8 note, uint8 velocity)
{
    FUNCTION_MARKER(0x80075D10, "SLUS_004.64");
    return spu_sequence_scheduler_note_on(&spu_sequence_scheduler, sequence, separation, note, velocity, func_800726ec, func_80072d18);
}

uint32 func_80077230(sint16 sequence, sint16 separation)
{
    FUNCTION_MARKER(0x80077230, "SLUS_004.64");
    return spu_sequence_scheduler_pitch_bend(&spu_sequence_scheduler, sequence, separation, func_80072238, func_80077634);
}

uint32 func_80072d18(sint16 sequence, sint16 bank, sint16 program, uint16 note)
{
    FUNCTION_MARKER(0x80072D18, "SLUS_004.64");
    return spu_sequence_vm_key_off(sequence, bank, program, note);
}

void func_8003474c(uint32 descriptor, SCRIPT_OPERAND *operand, uint32 *literal)
{
    static const uint32 bases[14] = {0, 0x800814B8, 0x800EE8D8, 0x800EE7D8, 0x8007E064, 0x8007F064, 0x80080194, 0x80080F94, 0x800EF754, 0x800EC030, 0x800EE088, 0x8007DCE4, 0x800EE0A8, 0x800DF0C4};
    static const uint32 source_widths[14] = {0, 1, 1, 1, 16, 11, 14, 7, 1, 1, 1, 7, 13, 1};
    uint32 strides[32];
    uint32 index, kind, field, source, add, value, offset;
    FUNCTION_MARKER(0x8003474C, "SLUS_004.64");
    for (index = 0; index < 32; index += 4)
    {
        strides[index] = r_u32(0x80011390 + index * 4);
        strides[index + 1] = r_u32(0x80011394 + index * 4);
        strides[index + 2] = r_u32(0x80011398 + index * 4);
        strides[index + 3] = r_u32(0x8001139C + index * 4);
    }
    kind = r_u8(descriptor);
    field = r_u8(descriptor + 1);
    source = r_u8(descriptor + 2);
    add = r_u8(descriptor + 3);
    value = r_u32(descriptor + 4);
    /* Frozen MAC inputs establish the descriptor type domain */
    assert(kind < 14);
    if (kind == 0)
    {
        *literal = value;
        operand->native_value = literal;
        return;
    }
    assert(source < 14);
    if (field == 255)
        field = 0;
    if (source != 0)
    {
        switch (source)
        {
        case 4:
        case 5:
        case 6:
        case 7:
        case 11:
        case 12:
            offset = value * source_widths[source];
            if (add != 255)
                offset += add;
            value = r_u32(bases[source] + (offset << 2));
            break;
        default:
            value = r_u32(bases[source] + (value << 2));
            if (add != 255)
                value += add;
            break;
        }
    }
    operand->guest_address = bases[kind] + ((value * strides[kind]) << 2) + (field << 2);
    operand->native_value = 0;
}
void func_80032d68(uint32 object, uint32 mode)
{
    SCRIPT_OPERAND operands[16];
    uint32 literals[16], returns[32], values[7];
    uint32 header, code_base, pc, initial_pc, index, opcode, count;
    uint32 running, depth, equal, greater_equal, value, offset, counter;
    FUNCTION_MARKER(0x80032D68, "SLUS_004.64");
    if (r_u32(0x800CF8BC + (object << 2)) == 0)
        return;
    if (r_u32(0x800816B8 + (mode << 2)) == 0)
        return;
    header = r_u32(0x800CFA5C + (object << 2));
    code_base = header + (r_u32(header + 0x14) << 2);
    value = r_u32(header + (mode << 2) + 0x20);
    pc = code_base + (value << 2);
    initial_pc = pc;
    if (value == 0)
        return;
    running = 1;
    depth = 0;
    /* Frozen MAC control flow defines flags before every use */
    do
    {
        if (r_u32(0x800CF8DC) == 100)
            return;
        w_u32(0x800CFF8C, (uint32)((sint32)(pc - initial_pc) >> 2));
        w_u32(0x800CFF54, r_u32(pc));
        opcode = r_u16(pc);
        count = r_u16(pc + 2);
        pc += 4;
        assert(count <= 16);
        for (index = 0; index < count; ++index)
        {
            func_8003474c(pc, &operands[index], &literals[index]);
            pc += 8;
        }
        switch (opcode)
        {
        case 0x00:
            running = 0;
            break;
        case 0x01:
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            if (operands[0].native_value)
                *operands[0].native_value = values[1];
            else
                w_u32(operands[0].guest_address, values[1]);
            break;
        case 0x02:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            if (operands[0].native_value)
                *operands[0].native_value = values[0] + values[1];
            else
                w_u32(operands[0].guest_address, values[0] + values[1]);
            break;
        case 0x03:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            if (operands[0].native_value)
                *operands[0].native_value = values[0] - values[1];
            else
                w_u32(operands[0].guest_address, values[0] - values[1]);
            break;
        case 0x0E:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            if (operands[0].native_value)
                *operands[0].native_value = values[0] * values[1];
            else
                w_u32(operands[0].guest_address, values[0] * values[1]);
            break;
        case 0x68:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            if (operands[0].native_value)
                *operands[0].native_value = values[0] & values[1];
            else
                w_u32(operands[0].guest_address, values[0] & values[1]);
            break;
        case 0x69:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            if (operands[0].native_value)
                *operands[0].native_value = values[0] | values[1];
            else
                w_u32(operands[0].guest_address, values[0] | values[1]);
            break;
        case 0x6A:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            if (operands[0].native_value)
                *operands[0].native_value = values[0] ^ values[1];
            else
                w_u32(operands[0].guest_address, values[0] ^ values[1]);
            break;
        case 0x04:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            equal = values[0] == values[1];
            greater_equal = (sint32)values[0] >= (sint32)values[1];
            break;
        case 0x05:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            pc = code_base + (values[0] << 2);
            break;
        case 0x06:
            if (equal != 0)
            {
                values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
                pc = code_base + (values[0] << 2);
            }
            break;
        case 0x07:
            if (equal == 0)
            {
                values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
                pc = code_base + (values[0] << 2);
            }
            break;
        case 0x08:
            if (greater_equal != 0)
            {
                values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
                pc = code_base + (values[0] << 2);
            }
            break;
        case 0x09:
            if (greater_equal == 0)
            {
                values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
                pc = code_base + (values[0] << 2);
            }
            break;
        case 0x0A:
            assert(depth < 32);
            returns[depth] = pc;
            ++depth;
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            pc = code_base + (values[0] << 2);
            break;
        case 0x0B:
            if (depth != 0)
            {
                --depth;
                pc = returns[depth];
            }
            break;
        case 0x0C:
            greater_equal = 1;
            break;
        case 0x0D:
            greater_equal = 0;
            break;
        case 0x0F:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            value = (uint32)geometry_divide(values[0], values[1]);
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x10:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            values[3] = operands[3].native_value ? *operands[3].native_value : r_u32(operands[3].guest_address);
            func_8003259c(values[0], values[1], values[2], values[3]);
            break;
        case 0x13:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80020834(values[0]);
            break;
        case 0x14:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_8002e2ac(values[0]);
            break;
        case 0x17:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_8002dda8(values[0]);
            break;
        case 0x19:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80032d40(values[0]);
            break;
        case 0x1A:
            func_8001f87c();
            break;
        case 0x1B:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_8001f8a0(values[0], values[1], values[2]);
            break;
        case 0x1C:
            func_8001f92c();
            break;
        case 0x1F:
            func_8001fbcc();
            break;
        case 0x20:
            func_8001fbd8();
            break;
        case 0x21:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_8003271c(values[0], values[1]);
            break;
        case 0x23:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_800327a0(values[0], values[1], values[2]);
            break;
        case 0x25:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_80032948(values[0], values[1], values[2]);
            break;
        case 0x26:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80034c68(values[0]);
            break;
        case 0x27:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80034c88(values[0], values[1]);
            break;
        case 0x28:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_80034d04(values[0], values[1], values[2]);
            break;
        case 0x2A:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_80034d48(values[0], values[1], values[2]);
            break;
        case 0x2C:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80034d8c(values[0], values[1]);
            break;
        case 0x2D:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_8001e91c(values[0], values[1], values[2]);
            break;
        case 0x2E:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80034e04(values[0], values[1]);
            break;
        case 0x30:
            assert(count != 0);
            func_80034e98(r_u32(pc - 4));
            break;
        case 0x37:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_80032354(values[0], values[1], values[2]);
            break;
        case 0x3D:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_800353c0(values[0], values[1], values[2]);
            break;
        case 0x41:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            values[3] = operands[3].native_value ? *operands[3].native_value : r_u32(operands[3].guest_address);
            func_8001de3c(values[0], values[1], values[2], values[3]);
            break;
        case 0x42:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80016b3c(values[0], values[1]);
            break;
        case 0x46:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            values[3] = operands[3].native_value ? *operands[3].native_value : r_u32(operands[3].guest_address);
            func_8001aca4(values[0], values[1], values[2], values[3]);
            break;
        case 0x47:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            values[3] = operands[3].native_value ? *operands[3].native_value : r_u32(operands[3].guest_address);
            func_8001ace8(values[0], values[1], values[2], values[3]);
            break;
        case 0x48:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_8001ad2c(values[0], values[1], values[2]);
            break;
        case 0x4B:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_80018100(values[0], values[1], values[2]);
            break;
        case 0x4D:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80034c78(values[0]);
            break;
        case 0x4E:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_8002a84c(values[0], values[1]);
            break;
        case 0x51:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_8001f028(values[0]);
            break;
        case 0x53:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_8002372c(values[0]);
            break;
        case 0x54:
        case 0x72:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80028898(values[0]);
            break;
        case 0x55:
        case 0x73:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_800288f4(values[0]);
            break;
        case 0x56:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80028408(values[0]);
            break;
        case 0x58:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_800286bc(values[0], values[1], values[2]);
            break;
        case 0x59:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_800287ac(values[0]);
            break;
        case 0x5A:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80014edc(values[0], values[1]);
            break;
        case 0x5B:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80023308(values[0]);
            break;
        case 0x5D:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_800237c8(values[0]);
            break;
        case 0x5F:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80020b7c(values[0], values[1]);
            break;
        case 0x61:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80020cb8(values[0], values[1]);
            break;
        case 0x62:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_80020d0c(values[0], values[1], values[2]);
            break;
        case 0x66:
            func_8003cb7c();
            break;
        case 0x6F:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_800228d0(values[0]);
            break;
        case 0x70:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80023b2c(values[0]);
            break;
        case 0x71:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_800228c4(values[0]);
            break;
        case 0x74:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80023b9c(values[0], values[1]);
            break;
        case 0x77:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80016748(values[0]);
            break;
        case 0x78:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80020a48(values[0], values[1]);
            break;
        case 0x7C:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_8002a8c8(values[0]);
            break;
        case 0x7E:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_8001322c(values[0], values[1]);
            break;
        case 0x80:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_8001596c(values[0], values[1], values[2]);
            break;
        case 0x81:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80023324(values[0], values[1]);
            break;
        case 0x82:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80026a6c(values[0]);
            break;
        case 0x83:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80026620(values[0], values[1]);
            break;
        case 0x84:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80026b24(values[0]);
            break;
        case 0x85:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_8001f168(values[0]);
            break;
        case 0x89:
            func_8002ac54();
            break;
        case 0x8A:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80028470(values[0]);
            break;
        case 0x8C:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80023768(values[0], values[1]);
            break;
        case 0x8D:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_800237a4(values[0], values[1]);
            break;
        case 0x18:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            value = func_8002ddf0(values[0]);
            if (operands[1].native_value)
                *operands[1].native_value = value;
            else
                w_u32(operands[1].guest_address, value);
            break;
        case 0x22:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            value = func_80032778(values[0]);
            if (operands[1].native_value)
                *operands[1].native_value = value;
            else
                w_u32(operands[1].guest_address, value);
            value = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            equal = value == 0;
            break;
        case 0x24:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            value = func_80032b7c(values[0], values[1]);
            if (operands[2].native_value)
                *operands[2].native_value = value;
            else
                w_u32(operands[2].guest_address, value);
            break;
        case 0x2F:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            value = func_80034e30(values[0]);
            if (operands[1].native_value)
                *operands[1].native_value = value;
            else
                w_u32(operands[1].guest_address, value);
            value = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            equal = value == 0;
            break;
        case 0x3E:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            value = func_800353ec(values[0], values[1]);
            if (operands[2].native_value)
                *operands[2].native_value = value;
            else
                w_u32(operands[2].guest_address, value);
            value = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            equal = value == 0;
            break;
        case 0x63:
            value = func_800287cc();
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x64:
            value = func_800385e8();
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x7D:
            value = func_8002ad80();
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x7F:
            value = func_8001325c();
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x8F:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            values[3] = operands[3].native_value ? *operands[3].native_value : r_u32(operands[3].guest_address);
            value = func_80036858(values[0], values[1], values[2], values[3]);
            if (operands[4].native_value)
                *operands[4].native_value = value;
            else
                w_u32(operands[4].guest_address, value);
            break;
        case 0x91:
            value = func_80012bbc();
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x33:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            w_u32(0x800EE7EC, values[0]);
            break;
        case 0x5C:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            w_u32(0x800CF880, values[0]);
            break;
        case 0x67:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            w_u32(0x800EDFCC, values[0]);
            break;
        case 0x79:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            w_u32(0x800CF878, values[0]);
            break;
        case 0x88:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            w_u32(0x800CF874, values[0]);
            break;
        case 0x90:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            w_u32(0x800EDFF4, values[0]);
            break;
        case 0x34:
            value = r_u32(0x800EE7EC);
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x44:
            value = r_u32(0x800CF908);
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x4F:
            value = r_u32(0x800CF9E4);
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x50:
            value = r_u32(0x800CF9E8);
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x86:
            value = r_u32(0x800CF808);
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x11:
            w_u32(0x800EE0A8, 0xFFFFFFFF);
            values[1] = r_u32(0x800CF820);
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80022320(object, values[0], values[1]);
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_8003537c(values[0]);
            break;
        case 0x12:
            w_u32(0x800EE0A8, 0xFFFFFFFF);
            values[1] = r_u32(0x800CF820);
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80022320(object, values[0], values[1]);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80020834(values[1]);
            values[0] = r_u32(0x800EE7EC);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            values[3] = operands[3].native_value ? *operands[3].native_value : r_u32(operands[3].guest_address);
            func_80032624(values[0], values[2], values[3]);
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_8003537c(values[0]);
            break;
        case 0x5E:
            w_u32(0x800EE0A8, 0xFFFFFFFF);
            values[1] = r_u32(0x800CF820);
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80022320(object, values[0], values[1]);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80020834(values[1]);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            values[0] = r_u32(0x800EE7EC);
            offset = values[2] * 28;
            values[1] = r_u32(0x8007DCE8 + offset);
            values[2] = r_u32(0x8007DCF0 + offset);
            func_80032624(values[0], values[1], values[2]);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            values[0] = r_u32(0x800EE7EC);
            offset = values[2] * 28;
            values[1] = r_u32(0x8007DCF4 + offset);
            values[2] = r_u32(0x8007DCF8 + offset);
            values[3] = r_u32(0x8007DCFC + offset);
            func_80032694(values[0], values[1], values[2], values[3]);
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_8003537c(values[0]);
            break;
        case 0x6D:
            w_u32(0x800EE0A8, 0xFFFFFFFF);
            values[1] = r_u32(0x800CF820);
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80022644(object, values[0], values[1]);
            break;
        case 0x15:
            do
            {
                if (mode != 4 && (r_u32(0x800CF844) == 2 || r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0))
                    break;
                func_80012bfc();
            } while (r_u32(0x800CF918) != 0);
            value = r_u32(0x800CF928);
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x7B:
            do
            {
                if (mode != 4 && (r_u32(0x800CF844) == 2 || r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0))
                    break;
                func_80012bfc();
            } while (r_u32(0x800CF918) != 0);
            value = r_u32(0x800CF92C);
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x16:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_8002dd84(values[0]);
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_800353a0(values[0]);
            break;
        case 0x1D:
            for (;;)
            {
                if (mode != 4 && (r_u32(0x800CF844) == 2 || r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0))
                    break;
                if (r_s32(0x800CF964) <= 0)
                {
                    offset = r_u32(0x800CF97C) * 12;
                    if (r_u32(0x800D85AC + offset) == 0xFFFFFFFF)
                        break;
                }
                func_80012bfc();
            }
            break;
        case 0x1E:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            counter = 0;
            if ((sint32)values[0] > 0)
            {
                do
                {
                    if (mode != 4 && (r_u32(0x800CF844) == 2 || r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0))
                        break;
                    ++counter;
                    func_80012bfc();
                    values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
                } while ((sint32)counter < (sint32)values[0]);
            }
            break;
        case 0x29:
            func_80034d1c((operands[0].native_value ? operands[0].native_value : (uint32 *)psx_addr(operands[0].guest_address, 4)), (operands[1].native_value ? operands[1].native_value : (uint32 *)psx_addr(operands[1].guest_address, 4)), (operands[2].native_value ? operands[2].native_value : (uint32 *)psx_addr(operands[2].guest_address, 4)));
            break;
        case 0x2B:
            func_80034d60((operands[0].native_value ? operands[0].native_value : (uint32 *)psx_addr(operands[0].guest_address, 4)), (operands[1].native_value ? operands[1].native_value : (uint32 *)psx_addr(operands[1].guest_address, 4)), (operands[2].native_value ? operands[2].native_value : (uint32 *)psx_addr(operands[2].guest_address, 4)));
            break;
        case 0x36:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80032568(values[0], (operands[1].native_value ? operands[1].native_value : (uint32 *)psx_addr(operands[1].guest_address, 4)), (operands[2].native_value ? operands[2].native_value : (uint32 *)psx_addr(operands[2].guest_address, 4)));
            break;
        case 0x3F:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            values[3] = operands[3].native_value ? *operands[3].native_value : r_u32(operands[3].guest_address);
            func_800238bc(values[0], values[1], values[2], values[3], (operands[4].native_value ? operands[4].native_value : (uint32 *)psx_addr(operands[4].guest_address, 4)), (operands[5].native_value ? operands[5].native_value : (uint32 *)psx_addr(operands[5].guest_address, 4)), (operands[6].native_value ? operands[6].native_value : (uint32 *)psx_addr(operands[6].guest_address, 4)));
            break;
        case 0x40:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80012f6c(values[0], (operands[1].native_value ? operands[1].native_value : (uint32 *)psx_addr(operands[1].guest_address, 4)), (operands[2].native_value ? operands[2].native_value : (uint32 *)psx_addr(operands[2].guest_address, 4)), (operands[3].native_value ? operands[3].native_value : (uint32 *)psx_addr(operands[3].guest_address, 4)), (operands[4].native_value ? operands[4].native_value : (uint32 *)psx_addr(operands[4].guest_address, 4)));
            break;
        case 0x31:
            func_8003943c(0);
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_8001f4c4(values[0], values[1]);
            break;
        case 0x32:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_8001aa20();
            break;
        case 0x35:
            values[4] = operands[4].native_value ? *operands[4].native_value : r_u32(operands[4].guest_address);
            values[5] = operands[5].native_value ? *operands[5].native_value : r_u32(operands[5].guest_address);
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            values[3] = operands[3].native_value ? *operands[3].native_value : r_u32(operands[3].guest_address);
            func_800324cc(values[0], values[1], values[2], values[3], values[4], values[5]);
            break;
        case 0x49:
            values[4] = operands[4].native_value ? *operands[4].native_value : r_u32(operands[4].guest_address);
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            values[3] = operands[3].native_value ? *operands[3].native_value : r_u32(operands[3].guest_address);
            func_8001ad4c(values[0], values[1], values[2], values[3], values[4]);
            break;
        case 0x38:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            w_u32(0x800DB6F0 + values[0] * 0x410, values[1]);
            break;
        case 0x3B:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            w_u32(0x800EE068 + (values[0] << 2), values[1]);
            break;
        case 0x39:
            func_80017a74();
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80021130(values[0]);
            func_8001afcc();
            break;
        case 0x8B:
            func_80017a74();
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_800211ec(values[0], values[1]);
            func_8001afcc();
            break;
        case 0x8E:
            func_80017a74();
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_80021288(values[0], values[1], values[2], object);
            break;
        case 0x4A:
            func_8001afcc();
            break;
        case 0x3A:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_800178b0(values[0], 0);
            break;
        case 0x57:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80017aa0(values[0], 0);
            break;
        case 0x3C:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            func_80034e4c(values[0]);
            func_80021514();
            break;
        case 0x43:
            value = r_u32(0x800EE7EC);
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            value = r_u32(0x800EE7F0);
            if (operands[1].native_value)
                *operands[1].native_value = value;
            else
                w_u32(operands[1].guest_address, value);
            break;
        case 0x45:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            value = r_u32(0x80081938 + (values[0] << 2));
            if (operands[1].native_value)
                *operands[1].native_value = value;
            else
                w_u32(operands[1].guest_address, value);
            break;
        case 0x4C:
            for (;;)
            {
                value = func_8003cba4();
                if (value == 0 && r_u32(0x800CF8D8) == 2)
                    break;
                if (mode != 4 && (r_u32(0x800CF844) == 2 || r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0))
                    break;
                func_80012bfc();
            }
            break;
        case 0x52:
            for (;;)
            {
                values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
                if (r_u32(0x800DB6F0 + values[0] * 0x410) == 0)
                    break;
                if (mode != 4 && (r_u32(0x800CF844) == 2 || r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0))
                    break;
                func_80012bfc();
            }
            break;
        case 0x65:
            for (;;)
            {
                value = func_800385e8();
                if (value == 0)
                    break;
                if (mode != 4 && (r_u32(0x800CF844) == 2 || r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0))
                    break;
                func_80012bfc();
            }
            break;
        case 0x6E:
            for (;;)
            {
                value = func_8001e124();
                if (value != 1)
                    break;
                if (mode != 4 && (r_u32(0x800CF844) == 2 || r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0))
                    break;
                func_80012bfc();
            }
            break;
        case 0x92:
            for (;;)
            {
                value = func_80012bbc();
                values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
                if ((sint32)value >= (sint32)values[0])
                    break;
                if (mode != 4 && (r_u32(0x800CF844) == 2 || r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0))
                    break;
                func_80012bfc();
            }
            break;
        case 0x6B:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            if (operands[0].native_value)
                *operands[0].native_value = ~values[0];
            else
                w_u32(operands[0].guest_address, ~values[0]);
            break;
        case 0x6C:
            value = func_80012658();
            if (operands[0].native_value)
                *operands[0].native_value = value;
            else
                w_u32(operands[0].guest_address, value);
            break;
        case 0x75:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            func_800324cc(values[0], values[1], values[2], 0, 0, 0);
            break;
        case 0x76:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            counter = 0;
            if ((sint32)values[0] > 0)
            {
                do
                {
                    VSync(0);
                    values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
                    ++counter;
                } while ((sint32)counter < (sint32)values[0]);
            }
            break;
        case 0x7A:
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_8002e3a0(values[0], values[1], 0);
            break;
        case 0x87:
            values[2] = operands[2].native_value ? *operands[2].native_value : r_u32(operands[2].guest_address);
            values[0] = operands[0].native_value ? *operands[0].native_value : r_u32(operands[0].guest_address);
            values[1] = operands[1].native_value ? *operands[1].native_value : r_u32(operands[1].guest_address);
            func_80032948(values[0], values[1], 0 - values[2]);
            break;
        case 0x60:
        default:
            break;
        }
        if (mode != 4 && (r_u32(0x800CF844) == 2 || r_u32(0x800CF8DC) != 0 || r_u32(0x800CF8E0) != 0))
            running = 0;
    } while (running != 0);
}

uint32 func_8006e0a8(uint32 type, uint32 destination)
{
    FUNCTION_MARKER(0x8006E0A8, "SLUS_004.64");
    return PAD_init2(type, destination);
}

uint32 func_8006e098(void)
{
    FUNCTION_MARKER(0x8006E098, "SLUS_004.64");
    return xport_bios_stop_pad();
}

sint32 func_8006e94c(sint32 handle)
{
    FUNCTION_MARKER(0x8006E94C, "SLUS_004.64");
    return PCclose(handle);
}

sint32 func_80077c24(void)
{
    FUNCTION_MARKER(0x80077C24, "SLUS_004.64");
    return SpuSetReverb(0);
}

uint32 func_80077c44(void)
{
    FUNCTION_MARKER(0x80077C44, "SLUS_004.64");
    spu_vm_state()->release_offset = 2;
    return 2;
}

void func_80077eac(void)
{
    FUNCTION_MARKER(0x80077EAC, "SLUS_004.64");
    spu_vm_state()->release_offset = 0;
}

uint32 func_8007bb1c(uint32 mode)
{
    FUNCTION_MARKER(0x8007BB1C, "SLUS_004.64");
    return spu_sequence_vm_transfer_mode(mode);
}

uint32 func_8007bb48(void)
{
    FUNCTION_MARKER(0x8007BB48, "SLUS_004.64");
    return spu_native_transfer_state->completion == 0;
}



void func_8006d5cc(uint32 mask, uint32 start, uint32 end)
{
    FUNCTION_MARKER(0x8006D5CC, "SLUS_004.64");
    StSetMask(mask, start, end);
}

void func_8004df4c(uint32 x0, uint32 y0, uint32 x1, uint32 y1)
{
    FUNCTION_MARKER(0x8004DF4C, "SLUS_004.64");
    GsDefDispBuff(x0, y0, x1, y1);
}

void func_8006f1a4(void)
{
    FUNCTION_MARKER(0x8006F1A4, "SLUS_004.64");
    spu_sequence_start_timer(0);
}

uint32 func_8007301c(sint16 bank, sint16 program, uint16 note)
{
    FUNCTION_MARKER(0x8007301C, "SLUS_004.64");
    return func_80072d18(33, bank, program, note);
}

uint32 func_800782e8(sint16 sequence, sint16 separation)
{
    FUNCTION_MARKER(0x800782E8, "SLUS_004.64");
    return func_80078154(sequence, separation);
}

void func_8006e898(void)
{
    FUNCTION_MARKER(0x8006E898, "SLUS_004.64");
    /* Both original entry paths skip the constant zero constructor count */
}

sint32 func_8006ea1c(sint32 handle, uint32 count, uint32 buffer)
{
    FUNCTION_MARKER(0x8006EA1C, "SLUS_004.64");
    return PCread(handle, (char *)psx_addr(buffer, count), (sint32)count);
}

sint32 func_8006ea34(sint32 handle, uint32 count, uint32 buffer)
{
    FUNCTION_MARKER(0x8006EA34, "SLUS_004.64");
    return PCwrite(handle, (char *)psx_addr(buffer, count), (sint32)count);
}

sint32 func_8006e698(sint32 handle, uint32 buffer, uint32 count)
{
    uint32 total = 0, chunk;
    sint32 actual;
    FUNCTION_MARKER(0x8006E698, "SLUS_004.64");
    while (count != 0)
    {
        chunk = count > 0x8000 ? 0x8000 : count;
        actual = func_8006ea1c(handle, chunk, buffer);
        total += (uint32)actual;
        if (actual == -1)
            return -1;
        buffer += (uint32)actual;
        count -= (uint32)actual;
        if (actual < (sint32)chunk)
            break;
    }
    return (sint32)total;
}

sint32 func_8006e95c(sint32 handle, uint32 buffer, uint32 count)
{
    uint32 total = 0, chunk;
    sint32 actual;
    FUNCTION_MARKER(0x8006E95C, "SLUS_004.64");
    while (count != 0)
    {
        chunk = count > 0x8000 ? 0x8000 : count;
        actual = func_8006ea34(handle, chunk, buffer);
        total += (uint32)actual;
        if (actual == -1)
            return -1;
        buffer += (uint32)actual;
        count -= (uint32)actual;
        if (actual < (sint32)chunk)
            break;
    }
    return (sint32)total;
}

sint32 func_8006f408(uint8 *header, sint16 bank, uint32 address)
{
    FUNCTION_MARKER(0x8006F408, "SLUS_004.64");
    return (sint16)func_8006f470(header, bank, 1, address);
}

sint32 func_8006f43c(uint8 *header, sint16 bank, uint32 address)
{
    FUNCTION_MARKER(0x8006F43C, "SLUS_004.64");
    return (sint16)func_8006f470(header, bank, 1, address);
}

sint32 func_8006f470(uint8 *header, sint16 requested_bank, uint32 mode, uint32 address)
{
    VabHdr attributes;
    uint32 capacity, bytes;
    sint16 bank;
    FUNCTION_MARKER(0x8006F470, "SLUS_004.64");
    if (func_8007bb48() == 1)
        return -1;
    func_8007bb1c(1);
    if ((uint16)mode == 0)
        bank = SsVabOpenHead(header, requested_bank);
    else
    {
        /* Describe the original header span at the native resource boundary */
        memcpy(&attributes, header, sizeof(attributes));
        capacity = ((uint32)attributes.form & 255) == 112 && attributes.ver >= 5 ? 128 : 64;
        bytes = 32 + capacity * 16 + (uint32)attributes.ps * 512 + 512;
        bank = spu_vab_open_head_sticky(header, bytes, requested_bank, address);
    }
    if (bank == -1)
        func_8007bb1c(0);
    return bank;
}

sint32 func_80074ca4(uint16 voice, sint16 left, sint16 right)
{
    FUNCTION_MARKER(0x80074CA4, "SLUS_004.64");
    return SsUtSetDetVVol(voice, left, right);
}

sint32 func_80074dac(uint16 voice, sint16 left, sint16 right)
{
    FUNCTION_MARKER(0x80074DAC, "SLUS_004.64");
    if (voice >= 24)
        return -1;
    return SsUtSetDetVVol(voice, (sint16)(left * 129), (sint16)(right * 129));
}

sint32 func_80074e48(uint16 voice, sint16 from, sint16 to, sint16 ticks)
{
    FUNCTION_MARKER(0x80074E48, "SLUS_004.64");
    if (voice >= 24)
        return -1;
    func_80070f30((sint16)voice, from, to, ticks);
    return 0;
}

sint32 func_80074e9c(uint16 voice, sint16 from, sint16 to, sint16 ticks)
{
    FUNCTION_MARKER(0x80074E9C, "SLUS_004.64");
    if (voice >= 24)
        return -1;
    func_8007149c((sint16)voice, from, to, ticks);
    return 0;
}

uint32 func_800768c8(sint16 sequence, sint16 separation, uint8 value)
{
    FUNCTION_MARKER(0x800768C8, "SLUS_004.64");
    return spu_sequence_scheduler_rpn_lsb(&spu_sequence_scheduler, sequence, separation, value, func_80077634);
}

uint32 func_80076944(sint16 sequence, sint16 separation, uint8 value)
{
    FUNCTION_MARKER(0x80076944, "SLUS_004.64");
    return spu_sequence_scheduler_rpn_msb(&spu_sequence_scheduler, sequence, separation, value, func_80077634);
}

void func_80078ab8(sint16 sequence, sint16 separation)
{
    FUNCTION_MARKER(0x80078AB8, "SLUS_004.64");
    spu_sequence_scheduler_resume(&spu_sequence_scheduler, sequence, separation);
}

static uint32 sequence_reverb_enable(uint32 mode)
{
    return (uint32)SpuSetReverb((sint32)mode);
}

uint32 func_80076580(sint16 sequence, sint16 separation)
{
    FUNCTION_MARKER(0x80076580, "SLUS_004.64");
    return spu_sequence_scheduler_reset_controllers(&spu_sequence_scheduler, sequence, separation, sequence_reverb_enable, func_80077634);
}

uint32 func_80076780(sint16 sequence, sint16 separation, uint8 value)
{
    FUNCTION_MARKER(0x80076780, "SLUS_004.64");
    return spu_sequence_scheduler_nrpn_msb(&spu_sequence_scheduler, sequence, separation, value, func_80077634);
}

uint32 func_800761a0(sint16 sequence, sint16 separation, uint8 value)
{
    SpuSequenceSchedulerTrack *record;
    ProgAtr program;
    VagAtr attributes;
    uint32 channel, result;
    sint16 bank, program_index, tone;
    FUNCTION_MARKER(0x800761A0, "SLUS_004.64");
    record = spu_sequence_scheduler.tracks[(sint32)sequence] + (sint32)separation;
    channel = record->channel;
    bank = (sint16)record->bank;
    program_index = record->channel_program[channel];
    SsUtGetProgAtr(bank, program_index, &program);
    for (tone = 0; tone < program.tones; ++tone)
    {
        bank = (sint16)record->bank;
        program_index = record->channel_program[channel];
        SsUtGetVagAtr(bank, program_index, tone, &attributes);
        attributes.vibW = value;
        bank = (sint16)record->bank;
        program_index = record->channel_program[channel];
        SsUtSetVagAtr(bank, program_index, tone, &attributes);
    }
    result = func_80077634(sequence, separation);
    record->delta = result;
    return result;
}

uint32 func_800762dc(sint16 sequence, sint16 separation, uint8 value)
{
    SpuSequenceSchedulerTrack *record;
    ProgAtr program;
    VagAtr attributes;
    uint32 channel, result;
    sint16 bank, program_index, tone;
    FUNCTION_MARKER(0x800762DC, "SLUS_004.64");
    record = spu_sequence_scheduler.tracks[(sint32)sequence] + (sint32)separation;
    channel = record->channel;
    bank = (sint16)record->bank;
    program_index = record->channel_program[channel];
    SsUtGetProgAtr(bank, program_index, &program);
    for (tone = 0; tone < program.tones; ++tone)
    {
        bank = (sint16)record->bank;
        program_index = record->channel_program[channel];
        SsUtGetVagAtr(bank, program_index, tone, &attributes);
        attributes.porT = value;
        bank = (sint16)record->bank;
        program_index = record->channel_program[channel];
        SsUtSetVagAtr(bank, program_index, tone, &attributes);
    }
    result = func_80077634(sequence, separation);
    record->delta = result;
    return result;
}

uint32 func_80076418(sint16 sequence, sint16 separation, uint8 value)
{
    SpuSequenceSchedulerTrack *record;
    ProgAtr program;
    VagAtr attributes;
    uint32 channel, result;
    sint16 bank, program_index, tone;
    FUNCTION_MARKER(0x80076418, "SLUS_004.64");
    record = spu_sequence_scheduler.tracks[(sint32)sequence] + (sint32)separation;
    channel = record->channel;
    bank = (sint16)record->bank;
    program_index = record->channel_program[channel];
    SsUtGetProgAtr(bank, program_index, &program);
    for (tone = 0; tone < program.tones; ++tone)
    {
        bank = (sint16)record->bank;
        program_index = record->channel_program[channel];
        SsUtGetVagAtr(bank, program_index, tone, &attributes);
        if (value < 64)
            attributes.mode = 2;
        else if (value < 128)
            attributes.mode = 0;
        bank = (sint16)record->bank;
        program_index = record->channel_program[channel];
        SsUtSetVagAtr(bank, program_index, tone, &attributes);
    }
    result = func_80077634(sequence, separation);
    record->delta = result;
    return result;
}

uint32 func_80075554(sint16 sequence, sint16 bank, const uint8 *data)
{
    FUNCTION_MARKER(0x80075554, "SLUS_004.64");
    return spu_sequence_scheduler_initialize_track(&spu_sequence_scheduler, sequence, bank, data, func_80077634);
}

uint32 func_80075880(uint32 data, sint16 bank, uint32 bytes)
{
    FUNCTION_MARKER(0x80075880, "SLUS_004.64");
    return spu_sequence_scheduler_open(&spu_sequence_scheduler, (const uint8 *)psx_addr(data, bytes), bytes, bank, func_80075554, &spu_sequence_handlers, &spu_sequence_handlers, spu_tone_commands, spu_tone_commands);
}

uint32 func_80072328(void)
{
    FUNCTION_MARKER(0x80072328, "SLUS_004.64");
    return spu_sequence_vm_flush();
}

uint32 func_800719fc(uint8 voices)
{
    FUNCTION_MARKER(0x800719FC, "SLUS_004.64");
    return spu_sequence_vm_initialize(voices);
}

void func_8006eb20(void)
{
    FUNCTION_MARKER(0x8006EB20, "SLUS_004.64");
    SsInitHot();
}

PsxInterruptCallback func_800440bc(PsxInterruptCallback callback)
{
    FUNCTION_MARKER(0x800440BC, "SLUS_004.64");
    return DrawSyncCallback(callback);
}

uint32 func_8007664c(sint16 sequence, sint16 separation, uint8 value)
{
    FUNCTION_MARKER(0x8007664C, "SLUS_004.64");
    return spu_sequence_scheduler_nrpn_lsb(&spu_sequence_scheduler, sequence, separation, value, spu_sequence_dispatch_mark, func_80077634);
}

uint32 func_8007381c(sint16 bank, sint16 program)
{
    ProgAtr attributes;
    FUNCTION_MARKER(0x8007381C, "SLUS_004.64");
    if (SsUtGetProgAtr(bank, program, &attributes) != 0)
        return (uint32)-1;
    return attributes.mvol;
}

uint32 func_800738e4(sint16 bank, sint16 program)
{
    ProgAtr attributes;
    FUNCTION_MARKER(0x800738E4, "SLUS_004.64");
    if (SsUtGetProgAtr(bank, program, &attributes) != 0)
        return (uint32)-1;
    return attributes.mpan;
}

void func_80070f30(sint16 voice, sint16 from, sint16 to, sint16 ticks)
{
    FUNCTION_MARKER(0x80070F30, "SLUS_004.64");
    spu_sequence_vm_volume_modulation_start(voice, from, to, ticks);
}

void func_80071100(uint32 voice)
{
    FUNCTION_MARKER(0x80071100, "SLUS_004.64");
    spu_sequence_vm_volume_modulation_tick((uint32)(sint32)(sint16)voice);
}

void func_8007149c(sint16 voice, sint16 from, sint16 to, sint16 ticks)
{
    FUNCTION_MARKER(0x8007149C, "SLUS_004.64");
    spu_sequence_vm_pan_modulation_start(voice, from, to, ticks);
}

void func_8007166c(uint32 voice)
{
    FUNCTION_MARKER(0x8007166C, "SLUS_004.64");
    spu_sequence_vm_pan_modulation_tick((uint32)(sint32)(sint16)voice);
}

uint32 func_80072f30(sint16 bank, sint16 program, uint16 note, uint16 left, uint16 right)
{
    uint16 volume, pan;
    FUNCTION_MARKER(0x80072F30, "SLUS_004.64");
    if (left == right)
    {
        volume = left;
        pan = 64;
    }
    else if (right < left)
    {
        volume = left;
        pan = (uint16)(((uint32)right << 6) / left);
    }
    else
    {
        volume = right;
        pan = (uint16)(127 - ((uint32)left << 6) / right);
    }
    return func_800726ec(33, bank, program, note, volume, pan);
}

uint32 func_80078808(sint16 sequence, sint16 separation)
{
    FUNCTION_MARKER(0x80078808, "SLUS_004.64");
    return spu_sequence_scheduler_decrescendo(&spu_sequence_scheduler, sequence, separation, func_8007353c, func_80073058);
}

uint32 func_80078dfc(sint16 sequence, sint16 separation)
{
    FUNCTION_MARKER(0x80078DFC, "SLUS_004.64");
    return spu_sequence_scheduler_crescendo(&spu_sequence_scheduler, sequence, separation, func_8007353c, func_80073058);
}

static uint32 sequence_next_separation(sint16 sequence, sint16 separation)
{
    return spu_sequence_scheduler_next_separation(&spu_sequence_scheduler, sequence, separation);
}

uint32 func_800772e0(sint16 sequence, sint16 separation, uint8 event)
{
    FUNCTION_MARKER(0x800772E0, "SLUS_004.64");
    if (event == 0x2F)
        return spu_sequence_scheduler_end_of_track(&spu_sequence_scheduler, sequence, separation, sequence_next_separation, func_80073654);
    if (event == 0x51)
        return spu_sequence_scheduler_meta_event(&spu_sequence_scheduler, sequence, separation, func_80077634);
    return 0x51;
}

uint32 func_8006fddc(uint32 layers, sint16 pitch)
{
    FUNCTION_MARKER(0x8006FDDC, "SLUS_004.64");
    return spu_sequence_vm_key_on_now(&spu_sequence_scheduler, layers, pitch);
}

uint32 func_80072010(sint16 voice, sint16 sequence, sint16 bank, sint16 program, uint16 bend)
{
    FUNCTION_MARKER(0x80072010, "SLUS_004.64");
    return spu_sequence_vm_voice_bend(voice, sequence, bank, program, bend);
}

uint32 func_800726ec(sint16 sequence, sint16 bank, sint16 program, uint16 note, uint16 velocity, uint16 pan)
{
    FUNCTION_MARKER(0x800726EC, "SLUS_004.64");
    return spu_sequence_vm_key_on(&spu_sequence_scheduler, sequence, bank, program, note, velocity, pan);
}

uint32 func_80044568(uint32 table, sint32 count)
{
    FUNCTION_MARKER(0x80044568, "SLUS_004.64");
    ClearOTag((uint32 *)psx_addr(table, (uint32)count * 4), count);
    return table + ((uint32)count - 1) * 4;
}

uint16 func_80070ba4(void)
{
    FUNCTION_MARKER(0x80070BA4, "SLUS_004.64");
    return spu_sequence_vm_note_pitch();
}

uint16 func_80070c60(uint16 note, uint16 fraction)
{
    FUNCTION_MARKER(0x80070C60, "SLUS_004.64");
    return spu_sequence_vm_tone_pitch(note, fraction);
}

uint32 func_800737a8(sint16 bank, sint16 program, uint8 value)
{
    FUNCTION_MARKER(0x800737A8, "SLUS_004.64");
    return spu_vab_set_program_volume(bank, program, value);
}
