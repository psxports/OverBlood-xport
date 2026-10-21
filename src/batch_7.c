#include "functions.h"
#include <string.h>
#include <stdlib.h>

/* Full original bodies, pending final integration and runtime validation */
void func_8003bf5c(void)
{
    uint32 input, state, selected, result;
    FUNCTION_MARKER(0x8003BF5C, "SLUS_004.64");
    input = func_8003d034();
    state = r_u32(0x800CFCB0);
    if (state == 0)
    {
        func_8003c18c(1, 1);
        if (input == 3)
        {
            selected = r_u32(0x800CFC1C);
            if ((sint32)selected > 0)
                w_u32(0x800CFC1C, selected - 1);
        }
        else if (input == 4)
        {
            selected = r_u32(0x800CFC1C);
            if ((sint32)selected < 3)
                w_u32(0x800CFC1C, selected + 1);
        }
        else if (input == 5)
        {
            w_u32(0x800EE818, 0xFFFFFFFF);
            w_u32(0x800CFCB0, 1);
        }
        else if (input == 6)
        {
            func_8002372c(20);
            func_8003c388(r_u32(0x800CFC1C));
        }
    }
    else if (state == 1)
    {
        result = r_u32(0x800EE81C);
        if (result == 1)
        {
            w_u32(0x800CFC18, 3);
            w_u32(0x800CFCC8, 32);
        }
        else if (result == 0xFFFFFFFF)
        {
            w_u32(0x800CFCB0, 0);
            w_u32(0x800EE818, 0);
            w_u32(0x800EE81C, 0);
        }
        func_8003c18c(1, 1);
    }
    else if (state == 2)
    {
        result = r_u32(0x800EE81C) + 3;
        switch (result)
        {
        case 1:
            func_8003c18c(0, 1);
            break;
        case 2:
            w_u32(0x800CFCB0, 0);
            w_u32(0x800EE818, 0);
            w_u32(0x800EE81C, 0);
            break;
        case 4:
            w_u32(0x800CFC18, 3);
            w_u32(0x800CFCC8, 32);
            w_u32(0x800CFCB0, 0xFFFFFFFF);
            break;
        case 5:
            w_u32(0x800CFC18, 3);
            w_u32(0x800CFCC8, 32);
            w_u32(0x800CFCB0, 0);
            break;
        default:
            break;
        }
    }
}

void func_8003b770(void)
{
    uint32 input, state, selected, result, timer, config[7];
    FUNCTION_MARKER(0x8003B770, "SLUS_004.64");
    input = func_8003d034();
    state = r_u32(0x800CFCB0);
    switch (state)
    {
    case 0:
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
        w_u32(0x800EE818, 0);
        w_u32(0x800EE81C, 0);
        if (input == 3)
        {
            if (r_s32(0x800CFC1C) > 0)
            {
                w_u32(0x800CFCD8, 63);
                w_u32(0x800CFCB0, 11);
            }
        }
        else if (input == 4)
        {
            if (r_s32(0x800CFC1C) < 2)
            {
                w_u32(0x800CFCD8, 63);
                w_u32(0x800CFCB0, 12);
            }
        }
        else if (input == 5)
        {
            w_u32(0x800EE818, 0xFFFFFFFF);
            w_u32(0x800CFCB0, 1);
        }
        else if (input == 6)
        {
            selected = r_u32(0x800CFC1C);
            if (selected == 0)
            {
                func_8003beb0(18);
                func_8003beb0(19);
            }
            else if (selected == 1 || selected == 2)
            {
                if (selected == 1)
                    func_8003beb0(18);
                func_8003beb0(19);
                func_8003beb0(20);
            }
            else
                break;
            w_u32(0x800EE818, 1);
            w_u32(0x800CFCB0, 1);
            func_8002372c(20);
        }
        break;
    case 1:
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
        result = r_u32(0x800EE81C);
        if (result == 1)
        {
            w_u32(0x800CFC18, 3);
            w_u32(0x800CFCC8, 32);
        }
        else if (result == 0xFFFFFFFF)
        {
            w_u32(0x800CFCB0, 0);
            w_u32(0x800EE818, 0);
            w_u32(0x800EE81C, 0);
        }
        break;
    case 2:
        func_8003bb34(0);
        if (r_u32(0x800EE81C) != 0)
        {
            w_u32(0x800CFCB0, 0);
            w_u32(0x800EE818, 0);
            w_u32(0x800EE81C, 0);
        }
        break;
    case 11:
        config[1] = 120;
        config[2] = 0;
        config[3] = 0x300;
        config[4] = 0;
        config[5] = 0;
        config[6] = 0;
        timer = r_u32(0x800CFCD8);
        selected = r_u32(0x800CFC1C);
        timer -= 10;
        w_u32(0x800CFCD8, timer);
        config[0] = (selected << 6) + timer;
        func_8003a980(config);
        func_8003bb34(1);
        if (r_s32(0x800CFCD8) < 10)
        {
            selected = r_u32(0x800CFC1C);
            w_u32(0x800CFCB0, 0);
            w_u32(0x800CFC1C, selected - 1);
        }
        break;
    case 12:
        config[1] = 120;
        config[2] = 0;
        config[3] = 0x300;
        config[4] = 0;
        config[5] = 0;
        config[6] = 0;
        timer = r_u32(0x800CFCD8);
        selected = r_u32(0x800CFC1C);
        timer -= 10;
        w_u32(0x800CFCD8, timer);
        config[0] = (selected << 6) + 128 - timer;
        func_8003a980(config);
        func_8003bb34(1);
        if (r_s32(0x800CFCD8) < 10)
        {
            selected = r_u32(0x800CFC1C);
            w_u32(0x800CFCB0, 0);
            w_u32(0x800CFC1C, selected + 1);
        }
        break;
    default:
        break;
    }
}

uint32 func_8003beb0(uint32 index)
{
    uint32 address, value;
    FUNCTION_MARKER(0x8003BEB0, "SLUS_004.64");
    address = 0x800EE7D8 + (index << 2);
    value = r_u32(address);
    w_u32(address, value == 0 ? 1 : 0);
    return 1;
}

uint32 func_8003c388(uint32 selected)
{
    uint32 table, index, value;
    FUNCTION_MARKER(0x8003C388, "SLUS_004.64");
    table = 0x800B4D04 + (selected << 4);
    for (index = 0; index < 4; ++index)
    {
        value = r_u32(table);
        table += 4;
        func_8003c3e8(index, value);
    }
    w_u32(0x800EE824, 1);
    return 1;
}

uint32 func_8003c3e8(uint32 index, uint32 value)
{
    uint32 address, previous;
    FUNCTION_MARKER(0x8003C3E8, "SLUS_004.64");
    address = 0x800EE820 + (index << 2);
    previous = r_u32(address);
    w_u32(address, previous != value ? 1 : 0);
    return 1;
}

void func_8003aa98(void)
{
    uint32 input, state, column, row, value, count, timer, page, product, config[7];
    FUNCTION_MARKER(0x8003AA98, "SLUS_004.64");
    input = func_8003d034();
    state = r_u32(0x800CFCB0);
    if (state == 0 || state == 2)
    {
        column = r_u32(0x800CFC1C);
        if (column != 3)
        {
            row = r_u32(0x800CFC20);
            config[0] = column * 22 + 90;
            config[2] = 8;
            config[4] = 0;
            config[5] = 0;
            config[6] = 0;
            config[1] = (row << 4) + 125;
        }
        else
        {
            config[0] = 156;
            config[1] = 162;
            config[2] = 8;
            config[4] = 0;
            config[5] = 0;
            config[6] = 0;
        }
        config[3] = r_u32(0x800EE854) != 0 ? 0x380 : 0x300;
        func_8003a980(config);
        if (state == 0)
        {
            switch (input)
            {
            case 1:
                if (r_s32(0x800CFC20) > 0 && r_u32(0x800CFC1C) != 3)
                {
                    w_u32(0x800CFCD8, 16);
                    w_u32(0x800CFCB0, 11);
                }
                break;
            case 2:
                if (r_s32(0x800CFC20) < 3 && r_u32(0x800CFC1C) != 3)
                {
                    w_u32(0x800CFCD8, 16);
                    w_u32(0x800CFCB0, 12);
                }
                break;
            case 3:
                column = r_u32(0x800CFC1C);
                if ((sint32)column > 0)
                {
                    w_u32(0x800CFCD8, 22);
                    w_u32(0x800CFCB0, column == 3 ? 16 : 13);
                }
                break;
            case 4:
                column = r_u32(0x800CFC1C);
                w_u32(0x800CFCD8, 22);
                if ((sint32)column < 2)
                    w_u32(0x800CFCB0, 14);
                else if (column == 2)
                    w_u32(0x800CFCB0, 15);
                break;
            case 5:
                count = r_u32(0x800CFCE8);
                if ((sint32)count > 0)
                {
                    value = (uint32)(r_s32(0x800CFCE0) / 10);
                    w_u32(0x800CFCE8, count - 1);
                    w_u32(0x800CFCE0, value);
                }
                break;
            case 6:
                row = r_u32(0x800CFC20);
                column = r_u32(0x800CFC1C);
                value = r_u32(0x800B4C5C + (row << 4) + (column << 2));
                if (value <= 9)
                {
                    count = r_u32(0x800CFCE8);
                    if ((sint32)count < 8)
                    {
                        w_u32(0x800CFCE8, count + 1);
                        value = r_u32(0x800CFCE0);
                        row = r_u32(0x800CFC20);
                        column = r_u32(0x800CFC1C);
                        count = r_u32(0x800B4C5C + (row << 4) + (column << 2));
                        value *= 10;
                        w_u32(0x800CFCE0, value);
                        value += count;
                        w_u32(0x800CFCE0, value);
                        func_8002372c(column + 20);
                    }
                }
                else if (value == 10)
                {
                    func_8002372c(20);
                    w_u32(0x800CFCB0, 2);
                }
                else if (value == 11)
                {
                    count = r_u32(0x800CFCE8);
                    if ((sint32)count > 0)
                    {
                        value = (uint32)(r_s32(0x800CFCE0) / 10);
                        w_u32(0x800CFCE8, count - 1);
                        w_u32(0x800CFCE0, value);
                        func_8002372c(21);
                    }
                }
                else if (value == 12)
                {
                    w_u32(0x800CFCE0, 0);
                    w_u32(0x800CFCE8, 0);
                    func_8002372c(22);
                }
                break;
            default:
                break;
            }
            w_u32(0x800EE818, 0);
            w_u32(0x800EE81C, 0);
            w_u32(0x800EE820, 0);
        }
        else
        {
            value = r_u32(0x800CFCE0);
            count = r_u32(0x800EE81C);
            w_u32(0x800EE818, 1);
            w_u32(0x800EE820, value);
            if (count == 1)
            {
                w_u32(0x800CFC18, 3);
                w_u32(0x800CFCC8, 32);
                w_u32(0x800EE818, 0);
                w_u32(0x800EE81C, 0);
                w_u32(0x800EE820, 0);
            }
            else if (count == 0xFFFFFFFF)
            {
                w_u32(0x800CFCB0, 0);
                w_u32(0x800CFCE0, 0);
                w_u32(0x800CFCE8, 0);
                w_u32(0x800CFC1C, 0);
                w_u32(0x800CFC20, 0);
                w_u32(0x800EE818, 0);
                w_u32(0x800EE81C, 0);
                w_u32(0x800EE820, 0);
            }
        }
    }
    else if (state == 11 || state == 12)
    {
        timer = r_u32(0x800CFCD8);
        column = r_u32(0x800CFC1C);
        config[2] = 8;
        config[4] = 0;
        config[5] = 0;
        config[6] = 0;
        timer -= 5;
        w_u32(0x800CFCD8, timer);
        row = r_u32(0x800CFC20);
        config[0] = column * 22 + 90;
        page = r_u32(0x800EE854);
        config[1] = state == 11 ? (row << 4) + timer + 109 : (row << 4) - timer + 141;
        config[3] = page != 0 ? 0x380 : 0x300;
        func_8003a980(config);
        if (r_s32(0x800CFCD8) < 5)
        {
            row = r_u32(0x800CFC20);
            w_u32(0x800CFCB0, 0);
            w_u32(0x800CFC20, state == 11 ? row - 1 : row + 1);
        }
    }
    else if (state == 13 || state == 14)
    {
        timer = r_u32(0x800CFCD8);
        column = r_u32(0x800CFC1C);
        config[2] = 8;
        config[4] = 0;
        config[5] = 0;
        config[6] = 0;
        timer -= 6;
        w_u32(0x800CFCD8, timer);
        row = r_u32(0x800CFC20);
        config[0] = state == 13 ? column * 22 + timer + 68 : column * 22 - timer + 112;
        page = r_u32(0x800EE854);
        config[1] = (row << 4) + 125;
        config[3] = page != 0 ? 0x380 : 0x300;
        func_8003a980(config);
        if (r_s32(0x800CFCD8) < 6)
        {
            column = r_u32(0x800CFC1C);
            w_u32(0x800CFCB0, 0);
            w_u32(0x800CFC1C, state == 13 ? column - 1 : column + 1);
        }
    }
    else if (state == 15)
    {
        timer = r_u32(0x800CFCD8) - 6;
        row = r_u32(0x800CFC20) << 4;
        product = (37 - row) * (22 - timer);
        value = (uint32)((sint32)product / 22);
        config[4] = 0;
        config[5] = 0;
        config[6] = 0;
        w_u32(0x800CFCD8, timer);
        config[2] = 8;
        config[0] = 156 - timer;
        page = r_u32(0x800EE854);
        config[1] = row + value + 125;
        config[3] = page != 0 ? 0x380 : 0x300;
        func_8003a980(config);
        if (r_s32(0x800CFCD8) < 6)
        {
            w_u32(0x800CFCB0, 0);
            w_u32(0x800CFC1C, 3);
        }
    }
    else if (state == 16)
    {
        timer = r_u32(0x800CFCD8);
        row = r_u32(0x800CFC20) << 4;
        count = timer - 6;
        product = (37 - row) * (22 - count);
        value = (uint32)((sint32)product / 22);
        page = r_u32(0x800EE854);
        config[4] = 0;
        config[5] = 0;
        config[6] = 0;
        w_u32(0x800CFCD8, count);
        config[0] = timer + 128;
        config[2] = 8;
        config[1] = 162 - value;
        config[3] = page != 0 ? 0x380 : 0x300;
        func_8003a980(config);
        if (r_s32(0x800CFCD8) < 6)
        {
            w_u32(0x800CFCB0, 0);
            w_u32(0x800CFC1C, 2);
        }
    }
    func_8003b460(r_u32(0x800CFCE0));
    func_8003b69c(1);
}

uint32 func_8003b508(uint32 index, uint32 value)
{
    uint32 offset, sprite, u;
    FUNCTION_MARKER(0x8003B508, "SLUS_004.64");
    offset = index * 36;
    sprite = 0x800D7958 + offset;
    w_u32(sprite, 0x0A000000);
    w_u16(sprite + 12, GetTPage(2, 0, 640, 0));
    w_u16(sprite + 8, 8);
    w_u16(sprite + 10, 16);
    w_u16(sprite + 4, (index << 3) - 32);
    w_u16(sprite + 6, -26);
    u = value != 0 ? (value - 1) << 3 : 72;
    w_u8(sprite + 14, u);
    w_u8(sprite + 15, 0);
    return offset;
}

uint32 func_8003b460(uint32 value)
{
    sint32 exponent, quotient;
    uint32 power, product;
    FUNCTION_MARKER(0x8003B460, "SLUS_004.64");
    for (exponent = 7; exponent >= 0; --exponent)
    {
        power = func_8003d378(10, exponent);
        quotient = (sint32)value / (sint32)power;
        func_8003b508(7 - exponent, (uint32)quotient);
        product = (uint32)quotient * power;
        value -= product;
    }
    return product;
}

void func_800393f0(uint32 left, uint32 right)
{
    FUNCTION_MARKER(0x800393F0, "SLUS_004.64");
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, (sint16)left, (sint16)right);
}

uint32 func_80039320(uint32 body, uint32 table)
{
    uint32 offset;
    FUNCTION_MARKER(0x80039320, "SLUS_004.64");
    w_u32(0x800CFC98, body);
    configure_sequence_table();
    w_u16(0x800EC2E4, 99);
    w_u32(0x800EC2E8, 99);
    for (offset = 0; offset < 256; offset += 8)
    {
        w_u32(0x800EC1E8 + offset, 0xFFFFFFFF);
        w_u16(0x800EC1E4 + offset, 0xFFFF);
    }
    return 0;
}

uint32 func_8003c7e8(void)
{
    FUNCTION_MARKER(0x8003C7E8, "SLUS_004.64");
    w_u32(0x800D7958, 0x0A000000);
    w_u16(0x800D7964, GetTPage(2, 0, 640, 0));
    w_u16(0x800D7960, 256);
    w_u16(0x800D7962, 240);
    w_u8(0x800D7966, 0);
    w_u8(0x800D7967, 0);
    w_u16(0x800D795C, -160);
    w_u16(0x800D795E, -120);
    w_u32(0x800D797C, 0x0A000000);
    w_u16(0x800D7988, GetTPage(2, 0, 896, 0));
    w_u16(0x800D7984, 64);
    w_u16(0x800D7986, 240);
    w_u8(0x800D798A, 0);
    w_u8(0x800D798B, 0);
    w_u16(0x800D7980, 96);
    w_u16(0x800D7982, -120);
    return 96;
}

uint32 func_8003c9c4(void)
{
    uint32 page;
    FUNCTION_MARKER(0x8003C9C4, "SLUS_004.64");
    w_u32(0x800D7958, 0x0A000000);
    w_u16(0x800D7964, GetTPage(2, 0, 320, 0));
    w_u16(0x800D7960, 256);
    w_u16(0x800D7962, 240);
    w_u8(0x800D7966, 0);
    w_u8(0x800D7967, 0);
    w_u16(0x800D795C, -160);
    w_u16(0x800D795E, -120);
    w_u32(0x800D797C, 0x0A000000);
    w_u16(0x800D7988, GetTPage(2, 0, 576, 0));
    w_u16(0x800D7984, 64);
    w_u16(0x800D7986, 240);
    w_u8(0x800D798A, 0);
    w_u8(0x800D798B, 0);
    w_u16(0x800D7980, 96);
    w_u16(0x800D7982, -120);
    w_u32(0x800D79A0, 0x0A000000);
    w_u16(0x800D79AC, GetTPage(2, 0, 640, 0));
    w_u16(0x800D79A8, 256);
    w_u16(0x800D79AA, 240);
    w_u8(0x800D79AE, 0);
    w_u8(0x800D79AF, 0);
    w_u16(0x800D79A4, -160);
    w_u16(0x800D79A6, -120);
    w_u32(0x800D79C4, 0x0A000000);
    page = GetTPage(2, 0, 896, 0);
    w_u16(0x800D79D0, page);
    w_u16(0x800D79CC, 64);
    w_u16(0x800D79CE, 240);
    w_u8(0x800D79D2, 0);
    w_u8(0x800D79D3, 0);
    w_u16(0x800D79C8, 96);
    w_u16(0x800D79CA, -120);
    return page;
}

uint32 func_8003bcd0(void)
{
    uint32 index, sprite, offset, x, v;
    FUNCTION_MARKER(0x8003BCD0, "SLUS_004.64");
    for (index = 0; index < 3; ++index)
    {
        sprite = 0x800D7958 + (index + 1) * 36;
        w_u32(sprite, 0x0A000000);
        w_u16(sprite + 12, GetTPage(2, 0, 640, 0));
        w_u16(sprite + 8, 53);
        w_u16(sprite + 10, 22);
        w_u16(sprite + 4, index * 63 - 90);
        w_u16(sprite + 6, -44);
        w_u8(sprite + 14, 0);
        w_u8(sprite + 15, index * 23);
    }
    offset = 144;
    x = (uint32)-84;
    v = 69;
    for (index = 0; index < 3; ++index)
    {
        sprite = 0x800D7958 + offset;
        w_u32(sprite, 0x0A000000);
        w_u16(sprite + 12, GetTPage(2, 0, 640, 0));
        w_u16(sprite + 8, 42);
        w_u16(sprite + 10, 31);
        w_u16(sprite + 4, x);
        w_u16(sprite + 6, -17);
        w_u8(sprite + 14, 0);
        w_u8(sprite + 15, v);
        v += 32;
        offset += 36;
        x += 63;
    }
    return 0;
}

uint32 func_8003c498(void)
{
    uint32 offset, table, sprite, y;
    FUNCTION_MARKER(0x8003C498, "SLUS_004.64");
    w_u32(0x800D7958, 0x0A000000);
    w_u16(0x800D7964, GetTPage(2, 0, 640, 0));
    w_u16(0x800D7960, 26);
    w_u16(0x800D7962, 20);
    w_u8(0x800D7966, 37);
    w_u8(0x800D7967, 188);
    w_u32(0x800D797C, 0x0A000000);
    w_u16(0x800D7988, GetTPage(2, 0, 640, 0));
    w_u16(0x800D7984, 7);
    w_u16(0x800D7986, 7);
    w_u8(0x800D798A, 0);
    w_u8(0x800D798B, 188);
    table = 0;
    for (offset = 72; offset < 216; offset += 36)
    {
        sprite = 0x800D7958 + offset;
        w_u32(sprite, 0x0A000000);
        w_u16(sprite + 12, GetTPage(2, 0, 640, 0));
        w_u16(sprite + 4, r_u16(0x800B4CE4 + table) - 160);
        y = r_u16(0x800B4CE8 + table);
        w_u16(sprite + 8, 7);
        w_u16(sprite + 10, 7);
        w_u8(sprite + 14, 7);
        w_u8(sprite + 15, 188);
        w_u16(sprite + 6, y - 120);
        table += 8;
    }
    y = (uint32)-87;
    for (offset = 216; offset < 360; offset += 36)
    {
        sprite = 0x800D7958 + offset;
        w_u32(sprite, 0x0A000000);
        w_u16(sprite + 12, GetTPage(2, 0, 640, 0));
        w_u16(sprite + 4, 82);
        w_u16(sprite + 6, y);
        w_u16(sprite + 8, 23);
        w_u16(sprite + 10, 2);
        w_u8(sprite + 14, 14);
        w_u8(sprite + 15, 188);
        y += 20;
    }
    w_u32(0x800D7AC0, 0x0A000000);
    w_u16(0x800D7ACC, GetTPage(2, 0, 640, 0));
    w_u16(0x800D7AC4, -118);
    w_u16(0x800D7AC6, -95);
    w_u16(0x800D7AC8, 235);
    w_u16(0x800D7ACA, 188);
    w_u8(0x800D7ACE, 0);
    w_u8(0x800D7ACF, 0);
    return 188;
}

uint32 func_80032b7c(uint32 index, uint32 property)
{
    uint32 object, coordinate;
    FUNCTION_MARKER(0x80032B7C, "SLUS_004.64");
    if (property > 8)
        return 0;
    object = r_u32(0x800DDD48 + (index << 4));
    switch (property)
    {
    case 0:
        return r_u32(object + 0x18);
    case 1:
        return r_u32(object + 0x1C);
    case 2:
        return r_u32(object + 0x20);
    case 3:
        coordinate = r_u32(object + 0x44);
        return r_u32(coordinate);
    case 4:
        coordinate = r_u32(object + 0x44);
        return r_u32(coordinate + 4);
    case 5:
        coordinate = r_u32(object + 0x44);
        return r_u32(coordinate + 8);
    case 6:
        coordinate = r_u32(object + 0x44);
        return (uint32)r_s16(coordinate + 0x10);
    case 7:
        coordinate = r_u32(object + 0x44);
        return (uint32)r_s16(coordinate + 0x12);
    case 8:
        coordinate = r_u32(object + 0x44);
        return (uint32)r_s16(coordinate + 0x14);
    }
    return 0;
}

uint32 func_8003671c(uint32 *x, uint32 *y, uint32 *z, uint32 rotation_x, uint32 rotation_y, uint32 rotation_z)
{
    uint16 input_x, input_y, input_z;
    VECTOR output;
    FUNCTION_MARKER(0x8003671C, "SLUS_004.64");
    memcpy(&input_x, x, sizeof(input_x));
    memcpy(&input_y, y, sizeof(input_y));
    memcpy(&input_z, z, sizeof(input_z));
    func_800366a8(input_x | ((uint32)input_y << 16), input_z, (uint16)rotation_x | ((uint32)(uint16)rotation_y << 16), (uint16)rotation_z, &output);
    *x = (uint32)output.vx;
    *y = (uint32)output.vy;
    *z = (uint32)output.vz;
    return (uint32)output.vz;
}

uint32 func_80020be0(void)
{
    uint32 index, mode, object, floor, value;
    FUNCTION_MARKER(0x80020BE0, "SLUS_004.64");
    for (index = 1; index < 5; ++index)
    {
        mode = r_u32(0x800EDFD0);
        object = r_u32(0x800DDD48 + (index << 4));
        floor = r_u32(0x800CF908);
        value = r_u32(0x80081938 + (floor << 2));
        value -= mode == 0 ? 1700 : 850;
        w_u32(object + 0x1C, value);
        object = r_u32(0x800DDD48 + (index << 4));
        w_u32(object, 0);
        func_8001b21c(0x800DDD44 + (index << 4));
    }
    return 0;
}

uint32 func_80020cb8(uint32 parent, uint32 child)
{
    uint32 target, value;
    FUNCTION_MARKER(0x80020CB8, "SLUS_004.64");
    target = r_u32(0x800DDD48 + (child << 4));
    if (parent != 0)
    {
        value = r_u32(0x800DDD48 + (parent << 4));
        w_u32(target + 0x48, value);
        return value;
    }
    w_u32(target + 0x48, 0);
    return target;
}

uint32 func_80020d0c(uint32 group, uint32 index, uint32 child)
{
    uint32 target, value;
    FUNCTION_MARKER(0x80020D0C, "SLUS_004.64");
    target = r_u32(0x800DDD48 + (child << 4));
    if (group != 0)
    {
        value = r_u32(0x800EA708 + ((group * 35 + index) << 4));
        w_u32(target + 0x48, value);
        return value;
    }
    w_u32(target + 0x48, 0);
    return target;
}

void func_800210f8(void)
{
    FUNCTION_MARKER(0x800210F8, "SLUS_004.64");
    VSyncCallback(func_800214b4);
    ResetGraph(1);
    SetGraphDebug(0);
}

uint32 func_80022880(void)
{
    FUNCTION_MARKER(0x80022880, "SLUS_004.64");
    w_u32(0x800CF87C, 0);
    return func_80022ab0(r_u32(0x800EE7E4), 0, 0, 0, 0, 0, 0, 0);
}

void func_800211bc(sint32 movie)
{
    FUNCTION_MARKER(0x800211BC, "SLUS_004.64");
    if (r_u32(0x800CF7CC) != 0)
    {
        func_80020e78(movie, 0);
        func_800210f8();
    }
}

void func_8002841c(void)
{
    FUNCTION_MARKER(0x8002841C, "SLUS_004.64");
    func_80028898(2);
    func_80017a74();
    if (r_u32(0x800EE808) == 0)
        func_800211bc(22);
    else
        func_800211bc(25);
}

uint32 func_80023768(uint32 resource, uint32 volume)
{
    FUNCTION_MARKER(0x80023768, "SLUS_004.64");
    if (resource == 0)
        return func_800237e8();
    return func_80038dc8(resource, r_s16(0x800CF81C), 1, volume);
}

void func_800237a4(uint32 resource, uint32 volume)
{
    FUNCTION_MARKER(0x800237A4, "SLUS_004.64");
    if (resource != 0)
        func_80038f30(resource, volume);
}

void func_80038f30(uint32 resource, uint32 volume)
{
    uint32 slot = 0x800EC1E4, sequence_bits;
    sint16 sentinel, level = (sint16)volume;
    FUNCTION_MARKER(0x80038F30, "SLUS_004.64");
    for (;;)
    {
        sequence_bits = r_u16(slot);
        sentinel = r_s16(slot);
        if (sentinel == 99)
            return;
        if (r_u32(slot + 4) == resource && (uint16)SsIsEos((sint16)sequence_bits, 0) != 0)
        {
            SsSeqSetVol(r_s16(slot), level, level);
            return;
        }
        slot += 8;
    }
}

uint32 func_800237c8(uint32 resource)
{
    FUNCTION_MARKER(0x800237C8, "SLUS_004.64");
    return func_80038fd4(resource);
}

void func_80023808(sint32 track)
{
    FUNCTION_MARKER(0x80023808, "SLUS_004.64");
    func_800178b0(track, 1);
}

uint32 func_8002389c(uint32 resource)
{
    FUNCTION_MARKER(0x8002389C, "SLUS_004.64");
    return func_8002372c(resource);
}

void func_80023324(uint32 index, uint32 value)
{
    FUNCTION_MARKER(0x80023324, "SLUS_004.64");
    w_u32(0x800EE028 + (index << 2), value);
}

void func_80028838(uint32 ordering_table, uint32 attribute, uint32 red, uint32 green, uint32 blue, uint32 x, uint32 y, uint32 width, uint32 height, uint32 priority)
{
    uint32 box[4];
    FUNCTION_MARKER(0x80028838, "SLUS_004.64");
    box[0] = attribute;
    box[1] = (uint16)x | ((uint32)(uint16)y << 16);
    box[2] = (uint16)width | ((uint32)(uint16)height << 16);
    box[3] = (uint8)red | ((uint32)(uint8)green << 8) | ((uint32)(uint8)blue << 16);
    GsSortBoxFill(box, psx_addr(ordering_table, 20), priority);
}

void func_80026b24(uint32 enabled)
{
    uint32 value, object, target, index;
    FUNCTION_MARKER(0x80026B24, "SLUS_004.64");
    if (enabled != 0)
    {
        w_u32(0x800EE7F0, 2);
        value = r_u32(0x800CF958);
        w_u32(0x800EE7EC, 1);
        w_u32(0x800EDFB4, value);
        func_80023b2c(2);
        func_8001ef90(59);
        w_u32(0x800CFAF4, r_u32(0x800CF878));
        object = r_u32(0x800DDD48 + (r_u32(0x800EE7EC) << 4));
        w_u32(object + 0x18, 0);
        object = r_u32(0x800DDD48 + (r_u32(0x800EE7EC) << 4));
        w_u32(object + 0x1C, -500);
        object = r_u32(0x800DDD48 + (r_u32(0x800EE7EC) << 4));
        w_u32(0x800CF878, 0);
        w_u32(object + 0x20, -27800);
        func_8001e8b4(2);
        w_u32(0x800819A0, 0);
        index = r_u32(0x800EE7EC);
        target = r_u32(0x800DDD68);
        object = r_u32(0x800DDD48 + (index << 4));
        w_u32(target + 0x48, object);
        w_u32(r_u32(0x800DDD68) + 0x18, 0);
        w_u32(r_u32(0x800DDD68) + 0x1C, 0);
        w_u32(r_u32(0x800DDD68) + 0x20, 800);
        w_u16(r_u32(r_u32(0x800DDD68) + 0x44) + 0x10, 0);
        w_u16(r_u32(r_u32(0x800DDD68) + 0x44) + 0x12, 0);
        w_u16(r_u32(r_u32(0x800DDD68) + 0x44) + 0x14, 0);
        func_8001b21c(0x800DDD64);
        w_u32(r_u32(0x800DDE78) + 0x48, 0);
        index = r_u32(0x800EE7EC);
        target = r_u32(0x800DDE88);
        object = r_u32(0x800DDD48 + (index << 4));
        w_u32(target + 0x48, object);
        w_u32(r_u32(0x800DDE88) + 0x18, 0);
        w_u32(r_u32(0x800DDE88) + 0x1C, -250);
        w_u32(r_u32(0x800DDE88) + 0x20, 0);
        w_u16(r_u32(r_u32(0x800DDE88) + 0x44) + 0x10, 0);
        w_u16(r_u32(r_u32(0x800DDE88) + 0x44) + 0x12, 0);
        w_u16(r_u32(r_u32(0x800DDE88) + 0x44) + 0x14, 0);
        func_8001b21c(0x800DDE84);
        w_u32(0x800CFACC, 50);
        w_u32(0x800CFAD0, 0);
        w_u32(0x800CFAD4, 1);
        w_u32(0x800CFAD8, 5);
        w_u32(0x800CFADC, 0);
        func_80026e64();
        func_8001b21c(0x800DDD44 + (r_u32(0x800EE7EC) << 4));
        func_80031c20(r_u32(0x800EE7EC), 31, 1, 0, 0, 0);
        func_80032320(r_u32(0x800EE7EC), 31);
        func_80031c20(2, 31, 1, 0, 0, 0);
        func_80032320(2, 31);
        w_u32(0x800CF854, 1);
        w_u32(0x800CFDDC, 1);
    }
    else
    {
        func_800237e8();
        value = r_u32(0x800CFAF4);
        index = r_u32(0x800EDFB4);
        w_u32(0x800CFDDC, 0);
        w_u32(0x800CF878, value);
        w_u32(0x800EE0A8, 0xFFFFFFFF);
        func_80023b2c(index);
        func_8001ef90(52);
        func_800273f4();
        w_u32(0x800CF854, 0);
    }
}

uint32 func_8002cd34(uint32 object)
{
    uint32 action, difference, sound, target, speed, base, x, z, output_x, output_z, order;
    FUNCTION_MARKER(0x8002CD34, "SLUS_004.64");
    action = func_80031954(object);
    func_80031954(r_u32(0x800EE7EC));
    difference = action - r_u32(0x800CFDAC);
    if (difference != 4 && difference != 6)
        return 6;
    if (r_s32(0x800CFE34) < 3)
    {
        sound = r_u32(0x800B2F68 + (r_u32(0x800CFEDC) << 6));
        w_u32(0x800CFB30, 1200);
        w_u32(0x800CFB34, -100);
        w_u32(0x800CFB4C, 26);
        func_8002372c(sound);
    }
    else
    {
        w_u32(0x800CFB30, 500);
        w_u32(0x800CFB34, -30);
        w_u32(0x800CFB4C, 30);
        func_8002372c(62);
    }
    w_u32(0x800CFB28, 1);
    target = r_u32(0x800DDD88);
    speed = r_u32(0x800CFB30);
    base = r_u32(0x800CFDAC);
    x = r_u32(target + 0x18);
    w_u32(0x800CFB48, 0);
    w_u32(0x800CFB2C, speed);
    z = r_u32(target + 0x20);
    w_u32(0x800CFB38, x);
    w_u32(0x800CFB3C, z);
    func_80031f28(object, base + 12, base + 13);
    func_80024048(1);
    order = (uint32)randPSX() & 7;
    if (func_8002a60c(r_u32(0x800EE7EC), object, &output_x, &output_z, 1800, order) == 0)
    {
        w_u32(0x800CFB40, output_x);
        w_u32(0x800CFB44, output_z);
    }
    return func_80024048(0);
}

uint32 func_8002a60c(uint32 actor, uint32 object, uint32 *output_x, uint32 *output_z, uint32 distance, uint32 order)
{
    static const uint8 direction_order[8][8] = {
        {6, 4, 5, 3, 2, 1, 7, 0},
        {4, 5, 3, 6, 2, 7, 1, 0},
        {0, 7, 1, 6, 2, 5, 3, 4},
        {6, 7, 5, 0, 4, 1, 3, 2},
        {2, 1, 3, 0, 4, 7, 5, 6},
        {0, 4, 2, 6, 1, 3, 5, 7},
        {7, 1, 5, 3, 0, 6, 4, 2},
        {4, 5, 3, 6, 2, 7, 1, 0}
    };
    static const sint8 x_direction[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    static const sint8 z_direction[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    uint32 entry, rotation_x, rotation_y, rotation_z, trial, direction;
    uint32 x_bits, z_bits, target, count, x, z;
    VECTOR offset;
    FUNCTION_MARKER(0x8002A60C, "SLUS_004.64");
    entry = 0x800DDD44 + (actor << 4);
    rotation_x = r_u16(r_u32(r_u32(entry + 4) + 0x44) + 0x10);
    rotation_y = r_u16(r_u32(r_u32(entry + 4) + 0x44) + 0x12);
    rotation_z = r_u16(r_u32(r_u32(entry + 4) + 0x44) + 0x14);
    for (trial = 0; trial < 8; ++trial)
    {
        direction = direction_order[order][trial];
        x_bits = distance * (uint32)(sint32)x_direction[direction];
        z_bits = distance * (uint32)(sint32)z_direction[direction];
        func_800366a8((uint16)x_bits, (uint16)z_bits, rotation_x | (rotation_y << 16), rotation_z, &offset);
        target = r_u32(entry + 4);
        count = r_u32(0x800CF828);
        x = r_u32(target + 0x18);
        z = r_u32(target + 0x20);
        x += (uint32)offset.vx;
        z += (uint32)offset.vz;
        if (func_8002a5d0(x, z, object, object + count - 1) == 0)
        {
            *output_x = x;
            *output_z = z;
            return 0;
        }
    }
    *output_x = 0;
    *output_z = 0;
    return 1;
}

void func_8002c8e0(uint32 object)
{
    uint32 actor_entry, entry, actor_data, object_data, old_x, old_z;
    uint32 origin[2], reference[2], point[2], timer, choice, distance;
    uint32 speed_x, speed_z, angle, coordinate, turn, count, x, z;
    FUNCTION_MARKER(0x8002C8E0, "SLUS_004.64");
    if (r_u32(0x800CF904) != 0)
        return;
    actor_entry = 0x800DDD44 + (r_u32(0x800EE7EC) << 4);
    entry = 0x800DDD44 + (object << 4);
    actor_data = r_u32(actor_entry + 4);
    object_data = r_u32(entry + 4);
    origin[0] = r_u32(actor_data + 0x18);
    old_x = r_u32(object_data + 0x18);
    old_z = r_u32(object_data + 0x20);
    (void)r_u32(r_u32(actor_entry + 4) + 0x1C);
    origin[1] = r_u32(r_u32(actor_entry + 4) + 0x20);
    func_80024048(1);
    if (func_800299c8(object, old_x, old_z) != 0)
    {
        func_8002d268(object);
        timer = r_u32(0x800CFB18) + 1;
        w_u32(0x800CFB18, timer);
        if ((sint32)timer >= 61)
        {
            func_8002cd34(object);
            w_u32(0x800CFB18, 0);
        }
    }
    else
    {
        timer = r_u32(0x800CFB50);
        w_u32(0x800CFB18, 0);
        --timer;
        w_u32(0x800CFB50, timer);
        if ((sint32)timer < 0)
        {
            w_u32(0x800CFB50, r_u32(0x800CFB54));
            choice = (uint32)randPSX() & 7;
            switch (choice)
            {
            case 0:
                if (r_s32(0x800CFE34) < 2)
                    func_8002cff8(object);
                else
                    func_8002d0f8(object);
                break;
            case 1:
                if (r_s32(0x800CFE34) >= 2)
                    func_8002cff8(object);
                break;
            case 2:
                if (r_s32(0x800CFE34) >= 3)
                    func_8002cff8(object);
                break;
            case 3:
            case 4:
                if (r_s32(0x800CFE34) < 3)
                    func_8002ceac(object, 1);
                else
                    func_8002cf64(object, 1);
                break;
            case 5:
                func_8002ceac(object, 0xFFFFFFFF);
                break;
            case 6:
                func_8002cd34(object);
                break;
            case 7:
                func_8002ceac(object, 1);
                break;
            }
        }
        reference[0] = r_u32(r_u32(entry + 4) + 0x18);
        reference[1] = r_u32(r_u32(entry + 4) + 0x20);
        distance = func_800367f4(origin[0], origin[1], reference[0], reference[1]);
        distance <<= r_u32(0x800EDFD0) & 31;
        if ((sint32)distance >= 6001)
            func_8002cd34(object);
        else if ((sint32)distance >= 3001)
            func_8002d268(object);
        else
            func_8002d388(object);
        speed_z = func_8003248c(object);
        speed_z = (uint32)((sint32)speed_z >> (r_u32(0x800EDFD0) & 31));
        speed_x = func_8003240c(object);
        speed_x = (uint32)((sint32)speed_x >> (r_u32(0x800EDFD0) & 31));
        func_8001a34c(object, speed_x, 0, 0 - speed_z);
    }
    origin[0] = r_u32(r_u32(entry + 4) + 0x18);
    origin[1] = r_u32(r_u32(entry + 4) + 0x20);
    reference[0] = r_u32(r_u32(entry + 4) + 0x18);
    reference[1] = r_u32(r_u32(entry + 4) + 0x20);
    point[0] = r_u32(r_u32(actor_entry + 4) + 0x18);
    point[1] = r_u32(r_u32(actor_entry + 4) + 0x20);
    angle = 2048 - func_80036644(origin, reference, point);
    coordinate = r_u32(r_u32(entry + 4) + 0x44);
    if (func_8002a4a4((uint32)(sint32)r_s16(coordinate + 0x12), angle, 128) == 0)
    {
        coordinate = r_u32(r_u32(entry + 4) + 0x44);
        turn = (uint32)func_8002a570((uint32)(sint32)r_s16(coordinate + 0x12), angle);
        coordinate = r_u32(r_u32(entry + 4) + 0x44);
        turn = r_u16(coordinate + 0x12) + (turn << 7);
        w_u16(coordinate + 0x12, turn);
    }
    object_data = r_u32(entry + 4);
    count = r_u32(0x800CF828);
    x = r_u32(object_data + 0x18);
    z = r_u32(object_data + 0x20);
    if (func_8002a5d0(x, z, object, object + count - 1) == 1)
    {
        w_u32(r_u32(entry + 4) + 0x18, old_x);
        w_u32(r_u32(entry + 4) + 0x20, old_z);
        w_u32(r_u32(entry + 4), 0);
        func_8001b21c(entry);
    }
    func_80024048(0);
}

void func_8002f4a4(uint32 first_text, uint32 second_text)
{
    uint32 state, index, text, descriptor_y, sprite, length, buffer, flags;
    const char *input;
    FUNCTION_MARKER(0x8002F4A4, "SLUS_004.64");
    state = r_u32(0x800CF91C);
    if (state > 10)
        return;
    if (state == 0)
    {
        for (index = 4; index != 0; --index)
            w_u32(0x800EB9D4 + (index - 1) * 4, 0);
        w_u32(0x800D771C, 0x800CFBB8);
        w_u32(0x800D7740, 1);
        w_u32(0x800D7730, 0xFFFF);
        w_u32(0x800D7734, 0);
        w_u32(0x800D7720, 960);
        w_u32(0x800D7724, 385);
        w_u32(0x800D7728, 896);
        w_u32(0x800D772C, 496);
        length = (uint32)strlen(guest_c_string(0x800CFBB8));
        state = r_u32(0x800CF91C);
        w_u32(0x800D7738, length >> 1);
        w_u32(0x800D773C, 4);
        w_u32(0x800CF91C, state + 1);
    }
    else if (state == 6 || state == 8)
    {
        text = state == 6 ? first_text : second_text;
        if ((sint32)text < 1000)
        {
            buffer = r_u32(0x800CFA50);
            length = r_u32(0x800CFA58);
            func_800354b0(0x800EB8C4, buffer, text, length);
        }
        else
        {
            input = guest_c_string(0x80078364 + text * 36);
            strcpy((char *)psx_addr(0x800EB8C4, strlen(input) + 1), input);
        }
        buffer = r_u32(0x800CFA1C);
        w_u32(0x800D771C, 0x800EB8C4);
        w_u32(0x800D7720, 960);
        descriptor_y = state == 6 ? 385 : 405;
        w_u32(0x800D7724, descriptor_y);
        w_u32(0x800D7754, buffer);
        w_u32(0x800D7758, buffer + 6880);
        length = (uint32)strlen(guest_c_string(0x800EB8C4));
        w_u32(0x800D7738, length >> 1);
        func_8002d700(0x800D771C);
        index = state == 6 ? 0 : 1;
        func_8002f7c0(index);
        sprite = state == 6 ? 0x800E9C18 : 0x800E9C3C;
        w_u16(sprite + 6, state == 6 ? 80 : 100);
        w_u32(0x800D775C + index * 8, -70);
        flags = r_u32(sprite);
        state = r_u32(0x800CF91C);
        w_u32(sprite, flags & 0xFFFFFFBF);
        w_u32(0x800CF91C, state + 1);
    }
    else
        w_u32(0x800CF91C, r_u32(0x800CF91C) + 1);
}

void func_8002f1c4(void)
{
    MATRIX light, screen;
    uint32 coordinate, flags, selected, index, offset, value, limit;
    FUNCTION_MARKER(0x8002F1C4, "SLUS_004.64");
    func_8002e8c8();
    func_8004cf4c(0x800F0290);
    func_8001ab94();
    selected = r_u32(0x800CFEE4);
    value = r_u32(0x800CFEEC);
    func_8002f4a4(selected, value);
    if (r_s32(0x800CFB80) <= 0)
    {
        flags = r_u32(0x800EA364);
        coordinate = r_u32(0x800EA368);
        w_u32(0x800EA364, flags & 0xFFFFF1FF);
        func_8004e5c8(coordinate, &light, &screen);
        GsSetLightMatrix(&light);
        func_8004c8b8(r_u32(0x800EA368), &screen);
        SetRotMatrix(&screen);
        SetTransMatrix(&screen);
        func_8004b4f0(0x800EA364, 0x800EC750 + r_u32(0x800CFDEC) * 20, 5, 0x1F800000);
    }
    selected = r_u32(0x800CFB74);
    coordinate = r_u32(0x800EA368);
    if (selected == 0)
    {
        w_u8(0x800E9C2C, 192);
        w_u8(0x800E9C2D, 64);
        w_u8(0x800E9C2E, 0);
        w_u8(0x800E9C50, 128);
        w_u8(0x800E9C51, 128);
        w_u8(0x800E9C52, 128);
        w_u32(coordinate + 24, -5600);
        coordinate = r_u32(0x800EA368);
        value = 4200;
    }
    else
    {
        w_u8(0x800E9C2C, 128);
        w_u8(0x800E9C2D, 128);
        w_u8(0x800E9C2E, 128);
        w_u8(0x800E9C50, 192);
        w_u8(0x800E9C51, 64);
        w_u8(0x800E9C52, 0);
        w_u32(coordinate + 24, -5600);
        coordinate = r_u32(0x800EA368);
        value = 5400;
    }
    w_u32(coordinate + 28, value);
    coordinate = r_u32(0x800EA368);
    w_u32(coordinate + 32, 14000);
    func_8002ea08();
    func_8001afcc();
    func_8004cf4c(0x800EF5EC);
    for (index = 0; index < 2; ++index)
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
            if (index > 0)
            {
                func_8001e894(0x800EA364);
                w_u32(0x800CFB78, 1);
            }
        }
        GsSortSprite(psx_addr(0x800E9C18 + offset, 36), psx_addr(0x800EC750 + r_u32(0x800CFDEC) * 20, 20), 0);
    }
}

uint32 func_8001ace8(uint32 index, uint32 x, uint32 y, uint32 z)
{
    uint32 offset = index * 28;
    FUNCTION_MARKER(0x8001ACE8, "SLUS_004.64");
    w_u32(0x80080F98 + offset, x);
    w_u32(0x80080F9C + offset, y);
    w_u32(0x80080FA0 + offset, z);
    return offset;
}

void func_8001ad2c(uint32 first, uint32 second, uint32 third)
{
    FUNCTION_MARKER(0x8001AD2C, "SLUS_004.64");
    w_u32(0x800CFF94, first);
    w_u32(0x800CFF74, second);
    w_u32(0x800CFF64, third);
}

uint32 func_8001ad4c(uint32 first, uint32 second, uint32 third, uint32 fourth, uint32 fifth)
{
    FUNCTION_MARKER(0x8001AD4C, "SLUS_004.64");
    w_u32(0x800CFE9C, first);
    w_u32(0x800CFE44, second);
    w_u32(0x800CFF94, third);
    w_u32(0x800CFF74, fourth);
    w_u32(0x800CFF64, fifth);
    return fifth;
}

void func_80014edc(uint32 index, uint32 value)
{
    FUNCTION_MARKER(0x80014EDC, "SLUS_004.64");
    w_u32(0x800EE014 + (index << 2), value);
}

void func_8001596c(uint32 first, uint32 second, uint32 third)
{
    FUNCTION_MARKER(0x8001596C, "SLUS_004.64");
    w_u32(0x800CF818, first);
    w_u32(0x800CF814, second);
    w_u32(0x800CF810, third);
    w_u32(0x800CF808, 0);
}

uint32 func_80012bbc(void)
{
    uint32 first, second, result;
    FUNCTION_MARKER(0x80012BBC, "SLUS_004.64");
    first = r_u32(0x800CFFBC);
    second = r_u32(0x800CFEAC);
    result = first - second;
    w_u32(0x800CFE04, result);
    if ((sint32)result < 0)
        w_u32(0x800CFE04, 0);
    return r_u32(0x800CFE04);
}

uint32 func_80012f6c(uint32 index, uint32 *first, uint32 *second, uint32 *third, uint32 *fourth)
{
    uint32 offset = index << 2, value;
    FUNCTION_MARKER(0x80012F6C, "SLUS_004.64");
    *first = r_u32(0x800E9A58 + offset);
    *second = r_u32(0x800F02F0 + offset);
    *third = r_u32(0x800F0310 + offset);
    value = r_u32(0x800F0330 + offset);
    *fourth = value;
    return value;
}

uint32 func_8001325c(void)
{
    uint32 first, second, value;
    FUNCTION_MARKER(0x8001325C, "SLUS_004.64");
    first = r_u32(0x800CF834);
    second = r_u32(0x800CF83C);
    first -= second;
    value = r_u32(0x800CF840) - first;
    if ((sint32)value < 0)
        value = 0;
    return (uint32)((sint32)value / 60);
}

uint32 *func_800379d8(uint32 *destination, uint32 first, uint32 second, uint32 third, uint32 fourth, uint32 fifth)
{
    FUNCTION_MARKER(0x800379D8, "SLUS_004.64");
    destination[0] = first;
    destination[1] = second;
    destination[2] = third;
    destination[3] = fourth;
    destination[4] = fifth;
    return destination;
}

uint32 func_8001e91c(uint32 group, uint32 index, uint32 hidden)
{
    uint32 object;
    FUNCTION_MARKER(0x8001E91C, "SLUS_004.64");
    if ((sint32)group >= 8)
        return 0;
    object = 0x800EA704 + group * 560 + (index << 4);
    if (hidden == 0)
        return func_8001e878(object);
    return func_8001e894(object);
}

void func_8001aa20(void)
{
    FUNCTION_MARKER(0x8001AA20, "SLUS_004.64");
}

void func_80012cc4(void)
{
    FUNCTION_MARKER(0x80012CC4, "SLUS_004.64");
    func_80026840();
    if (r_u32(0x800CF864) == 0)
        func_80012dc0(r_u32(0x800CF86C));
    else
        func_80012dc0(1);
    func_80013394();
    func_80015984();
}

sint32 func_800358ec(const char *path)
{
    FILE *file;
    sint32 length;
    FUNCTION_MARKER(0x800358EC, "SLUS_004.64");
    file = open_resource(path);
    if (file == NULL)
        return -1;
    length = fseek(file, 0, SEEK_END) == 0 ? (sint32)ftell(file) : -1;
    fclose(file);
    return length;
}

void func_800289a8(uint32 step)
{
    uint32 increment, value;
    FUNCTION_MARKER(0x800289A8, "SLUS_004.64");
    w_u32(0x800EE7FC, 1);
    w_u32(0x800EE800, 0);
    increment = step << 1;
    do
    {
        func_80012bfc();
        value = r_u32(0x800EE800) + increment;
        w_u32(0x800EE800, value);
    } while ((sint32)value < 256);
    w_u32(0x800EE800, 255);
    func_80012bfc();
}

void func_80028a20(uint32 step)
{
    uint32 decrement, value;
    FUNCTION_MARKER(0x80028A20, "SLUS_004.64");
    w_u32(0x800EE7FC, 1);
    w_u32(0x800EE800, 255);
    decrement = step << 1;
    do
    {
        func_80012bfc();
        value = r_u32(0x800EE800) - decrement;
        w_u32(0x800EE800, value);
    } while ((sint32)value > 0);
    w_u32(0x800EE800, 0);
    func_80012bfc();
}

void func_80022644(uint32 selector, uint32 room, uint32 parameter)
{
    uint32 previous, actor, floor, index, scale;
    FUNCTION_MARKER(0x80022644, "SLUS_004.64");
    if (room == 0)
        return;
    func_80024090();
    w_u32(0x800CFA68, 1 - selector);
    func_80017a74();
    w_u32(0x800CF87C, parameter);
    if (func_80022ab0(room, 0, 0, 0, 0, 0, 0, 0) != 1)
    {
        w_u32(0x800CF87C, 0);
        return;
    }
    w_u32(0x800EE7F8, 0);
    w_u32(0x800EE7FC, 0);
    w_u32(0x800EE800, 0);
    w_u32(0x800EE858, 0);
    w_u32(0x800CF864, 0);
    func_80023c18();
    func_800228d0(0);
    previous = r_u32(0x800EE7E4);
    w_u32(0x800EE7E4, room);
    w_u32(0x800EE7E8, previous);
    func_8001afcc();
    func_800346a0(r_u32(0x800CFA68));
    actor = r_u32(0x800EE7EC);
    floor = r_u32(0x800CF908);
    func_80020a48(actor, floor);
    actor = r_u32(0x800EE7EC);
    floor = r_u32(0x800CF908);
    func_80020b7c(actor, floor);
    func_800150f8();
    func_80035414(r_u32(0x800EE7E4));
    w_u32(0x800CFA6C, r_u32(0x800CFA68));
    func_80023b9c((uint32)-2000, 2000);
    for (index = 1; index < 5; ++index)
    {
        scale = r_u32(0x800EDFD0) != 0 ? 2048 : 4096;
        w_u32(r_u32(r_u32(0x800DDD48 + (index << 4)) + 0x44), scale);
        w_u32(r_u32(r_u32(0x800DDD48 + (index << 4)) + 0x44) + 4, scale);
        w_u32(r_u32(r_u32(0x800DDD48 + (index << 4)) + 0x44) + 8, scale);
        func_80020b7c(index, r_u32(0x800CF908));
    }
    func_8001dc98();
    func_80016690();
    func_80022a08();
    func_800315ec();
    w_u32(0x800CF87C, 0);
}

uint32 func_800391a0(uint8 *header, uint8 *body)
{
    sint16 bank, result;
    FUNCTION_MARKER(0x800391A0, "SLUS_004.64");
    bank = (sint16)func_8006f3d4(header, -1);
    result = SsVabTransBody(body, bank);
    while (SsVabTransCompleted(0) != 1)
        ;
    return (uint32)(sint32)result;
}

sint32 func_8006f3d4(uint8 *header, sint16 requested_bank)
{
    FUNCTION_MARKER(0x8006F3D4, "SLUS_004.64");
    return (sint16)func_8006f470(header, requested_bank, 0, 0);
}

uint32 func_80034e98(uint32 index)
{
    uint32 offset, values[9], component, value, object;
    FUNCTION_MARKER(0x80034E98, "SLUS_004.64");
    offset = index << 6;
    values[0] = r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x18);
    values[1] = r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x1C);
    values[2] = r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x20);
    values[3] = r_u32(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44));
    values[4] = r_u32(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 4);
    values[5] = r_u32(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 8);
    values[6] = (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 0x10);
    values[7] = (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 0x12);
    values[8] = (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 0x14);
    /* Room records select position, scale or angle and one of three axes */
    component = 3 * r_u32(0x8007E06C + offset);
    component += r_u32(0x8007E070 + offset);
    values[component] = r_u32(0x8007E08C + offset);
    value = r_u32(0x8007E078 + offset);
    w_u32(0x8007E078 + offset, value);
    w_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x18, values[0]);
    w_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x1C, values[1]);
    w_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x20, values[2]);
    w_u32(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44), values[3]);
    w_u32(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 4, values[4]);
    w_u32(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 8, values[5]);
    w_u16(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 0x10, (uint16)values[6]);
    w_u16(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 0x12, (uint16)values[7]);
    w_u16(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 0x14, (uint16)values[8]);
    object = r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4));
    w_u32(object, 0);
    return object;
}

uint32 func_80021514(void)
{
    uint32 values[9], index, offset, component, state, factor, speed;
    uint32 lower, upper, value, owner, count;
    FUNCTION_MARKER(0x80021514, "SLUS_004.64");
    for (index = 0; index < 9; ++index)
        values[index] = r_u32(0x80010814 + (index << 2));
    index = 0;
    if (r_u32(0x800CF918) != 0)
        func_8002e67c();
    if (r_s32(0x800CFEA4) <= 0)
        return 0;
    do
    {
        offset = index << 6;
        state = r_u32(0x8007E064 + offset);
        if (state == 0xFFFFFFFF)
            return 0;
        if (state == 0)
            goto next_record;
        values[0] = r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x18);
        values[1] = r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x1C);
        values[2] = r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x20);
        values[3] = r_u32(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44));
        values[4] = r_u32(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 4);
        values[5] = r_u32(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 8);
        values[6] = (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 0x10);
        values[7] = (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 0x12);
        values[8] = (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 0x14);
        component = 3 * r_u32(0x8007E06C + offset);
        component += r_u32(0x8007E070 + offset);
        if (r_u32(0x8007E064 + offset) == 2)
        {
            if (r_u32(0x8007E090 + offset) == 0xFFFFFFFF)
                values[component] = r_u32(0x8007E07C + offset);
            else
                values[component] = r_u32(0x8007E080 + offset);
            w_u32(0x8007E064 + offset, 0);
            w_u32(0x8007E0A0 + offset, 0);
            goto write_values;
        }
        value = r_u32(0x8007E0A0 + offset) - 1;
        w_u32(0x8007E0A0 + offset, value);
        if (r_s32(0x8007E0A0 + offset) > 0)
            goto next_record;
        factor = r_u32(0x8007E074 + offset);
        speed = r_u32(0x8007E078 + offset);
        value = factor * speed;
        w_u32(0x8007E0A0 + offset, 0);
        values[component] += value;
        speed = r_u32(0x8007E078 + offset);
        if ((sint32)speed >= 0)
        {
            upper = r_u32(0x8007E080 + offset);
            if ((sint32)values[component] <= (sint32)upper)
                goto write_values;
            if (r_u32(0x8007E084 + offset) != 0)
            {
                if (r_u32(0x8007E088 + offset) != 0)
                {
                    w_u32(0x8007E078 + offset, 0 - speed);
                    values[component] = r_u32(0x8007E080 + offset);
                }
                else
                {
                    value = values[component];
                    value -= r_u32(0x8007E080 + offset);
                    value += r_u32(0x8007E07C + offset);
                    values[component] = value;
                }
            }
            else
            {
                values[component] = r_u32(0x8007E080 + offset);
                w_u32(0x8007E064 + offset, 0);
            }
        }
        else
        {
            lower = r_u32(0x8007E07C + offset);
            if ((sint32)values[component] >= (sint32)lower)
                goto write_values;
            if (r_u32(0x8007E084 + offset) != 0)
            {
                if (r_u32(0x8007E088 + offset) != 0)
                {
                    speed = r_u32(0x8007E078 + offset);
                    w_u32(0x8007E078 + offset, 0 - speed);
                    values[component] = r_u32(0x8007E07C + offset);
                }
                else
                {
                    value = lower - values[component];
                    values[component] = r_u32(0x8007E080 + offset) - value;
                }
            }
            else
            {
                values[component] = r_u32(0x8007E07C + offset);
                w_u32(0x8007E064 + offset, 0);
            }
        }
        owner = r_u32(0x8007E094 + offset);
        if (owner != 0xFFFFFFFF)
            func_80021e14(owner, r_u32(0x8007E09C + offset));
write_values:
        w_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x18, values[0]);
        w_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x1C, values[1]);
        w_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x20, values[2]);
        w_u32(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44), values[3]);
        w_u32(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 4, values[4]);
        w_u32(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 8, values[5]);
        w_u16(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 0x10, (uint16)values[6]);
        w_u16(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 0x12, (uint16)values[7]);
        w_u16(r_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)) + 0x44) + 0x14, (uint16)values[8]);
        func_8001b21c(0x800DDD44 + (r_u32(0x8007E068 + offset) << 4));
        w_u32(r_u32(0x800DDD48 + (r_u32(0x8007E068 + offset) << 4)), 0);
next_record:
        count = r_u32(0x800CFEA4);
        ++index;
    } while ((sint32)index < (sint32)count);
    return 0;
}

uint32 func_800142b4(void)
{
    sint32 seconds, remainder;
    uint32 index, digit, ordering_table, sprite;
    FUNCTION_MARKER(0x800142B4, "SLUS_004.64");
    seconds = (sint32)func_8001325c();
    if (seconds == 0)
    {
        func_800286bc(0, 0, 0);
        func_80028408(0);
        w_u32(0x800CF844, 2);
    }
    w_u32(0x8008148C, (uint32)(seconds / 100));
    remainder = seconds % 100;
    w_u32(0x80081490, (uint32)(remainder / 10));
    w_u32(0x80081494, (uint32)(remainder % 10));
    w_u16(0x800EA0CC, 100);
    w_u16(0x800EA0CE, 88);
    for (index = 0; index < 3; ++index)
    {
        digit = r_u32(0x8008148C + (index << 2));
        w_u16(0x800E9E68 + 36 * (digit + 6), (uint16)(13 * index + 100));
        digit = r_u32(0x8008148C + (index << 2));
        w_u16(0x800E9E6A + 36 * (digit + 6), 88);
        digit = r_u32(0x8008148C + (index << 2));
        ordering_table = 0x800EBD14 + 20 * r_u32(0x800CFDEC);
        sprite = 0x800E9F3C + 36 * digit;
        GsSortSprite(psx_addr(sprite, 36), psx_addr(ordering_table, 20), 0);
    }
    return 0;
}

void func_8001446c(void)
{
    uint32 level, mode, attribute, ordering_table;
    FUNCTION_MARKER(0x8001446C, "SLUS_004.64");
    level = r_u32(0x800EE800);
    mode = r_u32(0x800EE7FC);
    if (mode == 1)
        attribute = 0x60000000;
    else if (mode == 2)
        attribute = 0x50000000;
    else
        return;
    ordering_table = 0x800EBD14 + 20 * r_u32(0x800CFDEC);
    func_80028838(ordering_table, attribute, level, level, level, (uint32)-160, (uint32)-120, 320, 240, 0);
}

void func_80014520(void)
{
    uint32 mode, attribute, ordering_table, red, green, blue;
    FUNCTION_MARKER(0x80014520, "SLUS_004.64");
    mode = r_u32(0x800EE868);
    if ((sint32)mode >= 4)
        mode = 3;
    if (mode == 2)
        attribute = 0x40000000;
    else if (mode == 1)
        attribute = 0x70000000;
    else if (mode == 3)
        attribute = 0;
    else
        return;
    ordering_table = 0x800EBD14 + 20 * r_u32(0x800CFDEC);
    blue = r_u32(0x800EE864);
    red = r_u32(0x800EE85C);
    green = r_u32(0x800EE860);
    func_80028838(ordering_table, attribute, red, green, blue, (uint32)-160, (uint32)-120, 320, 240, 0);
}

uint32 func_800146c0(uint32 object, uint32 flags, uint32 pitch, uint32 yaw, uint32 roll)
{
    uint32 camera_pitch, camera_yaw, camera_roll, actor_offset;
    FUNCTION_MARKER(0x800146C0, "SLUS_004.64");
    func_80020d74(&camera_pitch, &camera_yaw, &camera_roll);
    if (r_u32(0x800EDFD8) == 2)
    {
        actor_offset = r_u32(0x800EE7EC) << 4;
        camera_pitch += (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + actor_offset) + 0x44) + 0x10);
        camera_yaw += (uint32)(sint32)r_s16(r_u32(r_u32(0x800DDD48 + actor_offset) + 0x44) + 0x12);
    }
    w_u16(r_u32(r_u32(object + 4) + 0x44) + 0x10, (uint16)((flags & 1) != 0 ? camera_pitch : pitch));
    w_u16(r_u32(r_u32(object + 4) + 0x44) + 0x12, (uint16)((flags & 2) != 0 ? camera_yaw : yaw));
    w_u16(r_u32(r_u32(object + 4) + 0x44) + 0x14, (uint16)roll);
    w_u32(r_u32(object + 4), 0);
    return func_800149cc(object);
}

uint32 func_80015a50(uint32 destination, uint32 source)
{
    uint32 source_object, destination_object, value;
    FUNCTION_MARKER(0x80015A50, "SLUS_004.64");
    source_object = r_u32(source + 4);
    destination_object = r_u32(destination + 4);
    value = r_u32(source_object + 0x18);
    w_u32(destination_object + 0x18, value);
    source_object = r_u32(source + 4);
    destination_object = r_u32(destination + 4);
    value = r_u32(source_object + 0x1C);
    w_u32(destination_object + 0x1C, value);
    source_object = r_u32(source + 4);
    destination_object = r_u32(destination + 4);
    value = r_u32(source_object + 0x20);
    w_u32(destination_object + 0x20, value);
    destination_object = r_u32(r_u32(destination + 4) + 0x44);
    value = r_u16(r_u32(r_u32(source + 4) + 0x44) + 0x10);
    w_u16(destination_object + 0x10, (uint16)value);
    destination_object = r_u32(r_u32(destination + 4) + 0x44);
    value = r_u16(r_u32(r_u32(source + 4) + 0x44) + 0x12);
    w_u16(destination_object + 0x12, (uint16)value);
    destination_object = r_u32(r_u32(destination + 4) + 0x44);
    value = r_u16(r_u32(r_u32(source + 4) + 0x44) + 0x14);
    w_u16(destination_object + 0x14, (uint16)value);
    w_u32(r_u32(destination + 4), 0);
    return func_8001b21c(destination);
}

uint32 func_80019378(uint32 object, uint32 action)
{
    uint32 selected;
    FUNCTION_MARKER(0x80019378, "SLUS_004.64");
    selected = action;
    if (object != 3)
    {
        if (action == 32 || action == 34)
            selected = 32;
        else if (action - 1 < 26 || action - 35 < 2 || action - 37 < 2 || action == 39)
            selected = 0;
    }
    else if (r_u32(0x800819A4) != 0)
        selected = 26;
    func_80031c20(object, selected, 1, 0, 0, 0);
    return func_80032320(object, selected);
}

uint32 func_8001e9a0(uint32 group, uint32 hidden)
{
    uint32 index, base;
    FUNCTION_MARKER(0x8001E9A0, "SLUS_004.64");
    func_8001e8b4((sint32)group);
    base = 560 * group;
    for (index = 0; index < 2; ++index)
    {
        if (hidden != 0)
            func_8001e894(0x800EA704 + base + (index << 4));
        else
            func_8001e878(0x800EA704 + base + (index << 4));
        w_u32(r_u32(0x800EA708 + base + (index << 4)), 0);
    }
    return 0;
}

uint32 func_8001e124(void)
{
    uint32 mode, offset, floor, height, x, y, z, target_x, target_y, target_z;
    FUNCTION_MARKER(0x8001E124, "SLUS_004.64");
    mode = r_u32(0x800CF88C);
    if (mode == 0)
        return 0;
    if (mode == 2)
    {
        if (r_u32(0x800CF890) != 0)
            return 1;
        if (r_u32(0x800CF894) != 0)
            return 1;
        return r_u32(0x800CF898) != 0;
    }
    if (mode != 1)
        return (sint32)mode < 2 ? 1 : 2;
    offset = 56 * r_u32(0x800CF884);
    x = r_u32(0x800801A4 + offset);
    floor = r_u32(0x800801A0 + offset);
    y = r_u32(0x800801A8 + offset);
    z = r_u32(0x800801AC + offset);
    target_x = r_u32(0x800801B0 + offset);
    height = r_u32(0x80081938 + (floor << 2));
    target_y = r_u32(0x800801B4 + offset);
    target_z = r_u32(0x800801B8 + offset);
    y += height;
    target_y += height;
    x -= r_u32(0x800EF5EC);
    y -= r_u32(0x800EF5F0);
    z -= r_u32(0x800EF5F4);
    target_x -= r_u32(0x800EF5F8);
    target_y -= r_u32(0x800EF5FC);
    target_z -= r_u32(0x800EF600);
    if (r_u32(0x800CF888) != 0)
    {
        target_x = 0;
        target_y = 0;
        target_z = 0;
    }
    return ((sint32)x >> 4) != 0 || ((sint32)y >> 4) != 0 || ((sint32)z >> 4) != 0
        || ((sint32)target_x >> 4) != 0 || ((sint32)target_y >> 4) != 0 || ((sint32)target_z >> 4) != 0;
}

uint32 func_8003fb70(void)
{
    FUNCTION_MARKER(0x8003FB70, "SLUS_004.64");
    for (;;)
    {
        if (TestEvent((sint32)r_u32(0x800CFCF0)) == 1)
            return 0;
        if (TestEvent((sint32)r_u32(0x800CFCF8)) == 1)
            return 1;
        if (TestEvent((sint32)r_u32(0x800CFD00)) == 1)
            return 2;
        if (TestEvent((sint32)r_u32(0x800CFD08)) == 1)
            return 3;
    }
}

uint32 func_8003fbf0(void)
{
    FUNCTION_MARKER(0x8003FBF0, "SLUS_004.64");
    for (;;)
    {
        if (TestEvent((sint32)r_u32(0x800CFD10)) == 1)
            return 0;
        if (TestEvent((sint32)r_u32(0x800CFD18)) == 1)
            return 1;
        if (TestEvent((sint32)r_u32(0x800CFD20)) == 1)
            return 2;
        if (TestEvent((sint32)r_u32(0x800CFD28)) == 1)
            return 3;
    }
}

sint32 func_8003fcc8(void)
{
    FUNCTION_MARKER(0x8003FCC8, "SLUS_004.64");
    TestEvent((sint32)r_u32(0x800CFD10));
    TestEvent((sint32)r_u32(0x800CFD18));
    TestEvent((sint32)r_u32(0x800CFD20));
    return TestEvent((sint32)r_u32(0x800CFD28));
}

uint32 func_8003ef50(const uint32 *data, uint32 slot)
{
    sint32 seconds, minutes, hours;
    uint32 offset, live_minutes, live_hours, value;
    FUNCTION_MARKER(0x8003EF50, "SLUS_004.64");
    w_u32(0x800D00B4 + (slot << 2), data[3]);
    seconds = (sint32)data[2] / 60;
    minutes = seconds / 60;
    hours = minutes / 60;
    offset = slot * 12;
    w_u32(0x800D0088 + offset, (uint32)minutes);
    live_minutes = r_u32(0x800D0088 + offset);
    w_u32(0x800D008C + offset, (uint32)seconds);
    w_u32(0x800D0084 + offset, (uint32)hours);
    value = r_u32(0x800D008C + offset);
    live_hours = r_u32(0x800D0084 + offset);
    w_u32(0x800D008C + offset, value - 60 * live_minutes);
    value = r_u32(0x800D0088 + offset);
    w_u32(0x800D0088 + offset, value - 60 * live_hours);
    return 60 * live_hours;
}
