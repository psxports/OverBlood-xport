#include "functions.h"
#include "psx_gpu.h"
#include "psx_press.h"

void bind_gs_subdivision_controls(void)
{
    sint32 distance = r_s32(0x800C81A8);
    sint16 width = r_s16(0x800C81AC);
    sint16 height = r_s16(0x800C81AE);
    gs_set_subdivision_controls(distance, width, height);
}

void dispatch_debug_menu_callback(uint32 callback, uint32 selection)
{
    switch (callback)
    {
    case 0x80023808: func_80023808((sint32)selection); break;
    case 0x80023828: func_80023828((sint32)selection); break;
    case 0x8002389C: func_8002389c(selection); break;
    default:
#ifndef NDEBUG
        fprintf(stderr, "OBL: Unknown debug menu callback %08X\n", callback);
#endif
        abort();
    }
}

void func_8004cf4c(uint32 view)
{
    GsSetRefView2(view);
}

uint32 func_80042450(uint32 channel)
{
    return _card_clear(channel);
}

void func_8004c8b8(uint32 coordinate, MATRIX *screen)
{
    GsGetLs(coordinate, screen);
}

void func_8004e5c8(uint32 coordinate, MATRIX *world, MATRIX *screen)
{
    GsGetLws(coordinate, world, screen);
}

void load_resource_header(const char *path, uint32 destination)
{
    func_8003ccac(path, destination);
}

void load_resource_rectangle(const char *path, uint32 destination, uint32 offset, uint32 length, uint32 enabled, uint32 rect_xy, uint32 rect_wh)
{
    func_8003cdd4(path, destination, offset, length, enabled, rect_xy, rect_wh);
}

uint32 read_sequence_event(sint16 sequence, sint16 separation)
{
    return spu_sequence_scheduler_dispatch_event(&spu_sequence_scheduler, sequence, separation, &spu_sequence_handlers, func_80077634, func_800772e0);
}

uint32 play_sequence_tick(sint16 sequence, sint16 separation)
{
    return spu_sequence_scheduler_play_tick(&spu_sequence_scheduler, sequence, separation, read_sequence_event);
}

static void sequence_tempo_tick(sint16 sequence, sint16 separation)
{
    spu_sequence_scheduler_tempo_ramp(&spu_sequence_scheduler, sequence, separation);
}

static uint32 sequence_pause_tick(sint16 sequence, sint16 separation)
{
    return spu_sequence_scheduler_pause(&spu_sequence_scheduler, sequence, separation, func_80073654);
}

static uint32 sequence_meta_tick(sint16 sequence, sint16 separation)
{
    return func_800772e0(sequence, separation, 0x51);
}

void bind_sequence_runtime(void)
{
    const SpuSequencePumpOps ops = {func_80072328, play_sequence_tick, func_80078dfc, func_80078808, sequence_tempo_tick, sequence_pause_tick, func_80078ab8, func_80078154};
    spu_sequence_bind_pump(&ops);
    spu_sequence_handlers.note_on = func_80075d10;
    spu_sequence_handlers.program_change = func_80075e04;
    spu_sequence_handlers.pitch_bend = func_80077230;
    spu_sequence_handlers.meta_event = sequence_meta_tick;
    spu_sequence_handlers.control_change = func_80075e80;
    spu_sequence_handlers.data_entry = func_800769c0;
    spu_sequence_handlers.volume = sequence_channel_volume;
    spu_sequence_handlers.pan = sequence_channel_pan;
    spu_sequence_handlers.expression = sequence_channel_expression;
    spu_sequence_handlers.parameter_lsb = func_8007664c;
    spu_sequence_handlers.parameter_msb = func_80076780;
    spu_sequence_handlers.registered_parameter_lsb = func_800768c8;
    spu_sequence_handlers.registered_parameter_msb = func_80076944;
    spu_sequence_handlers.reverb_depth = sequence_channel_reverb;
    spu_sequence_handlers.reset_controllers = func_80076580;
    spu_sequence_handlers.damper = sequence_channel_damper;
    spu_sequence_handlers.portamento = func_80076418;
}

void configure_sequence_table(void)
{
    static SpuSequenceSchedulerTrack tracks[32];
    spu_sequence_scheduler_set_table(&spu_sequence_scheduler, tracks, 32, 1);
    bind_sequence_runtime();
}

uint32 func_800417c0(uint32 destination, uint32 source, uint32 bytes)
{
    if (bytes != 0)
        memcpy(psx_addr(destination, bytes), psx_addr(source, bytes), bytes);
    return destination;
}

uint32 func_80041820(uint32 destination, uint32 source, uint32 bytes)
{
    return memmovePSX(destination, source, (sint32)bytes);
}

void func_80046940(sint32 stream)
{
    SetDumpFnt(stream);
}

void func_80075480(uint32 serial, uint16 *volume)
{
    SsGetSerialVol((uint8)serial, volume);
}

void func_80042600(uint32 pixels, sint32 mode)
{
    uint32 bytes = 4 + (uint32)r_u16(pixels) * 4;
    DecDCTin((uint32 *)psx_addr(pixels, bytes), mode);
}

void func_8004267c(uint32 pixels, sint32 size)
{
    if (size <= 0 || (uint32)size > 0x3FFFFFFF)
        abort();
    DecDCTout((uint32 *)psx_addr(pixels, (uint32)size * 4), size);
}

sint32 func_800443d4(PSX_RECT *rectangle, uint32 pixels)
{
    uint32 bytes;
    if (rectangle->w < 0 || rectangle->h < 0)
        abort();
    bytes = (uint32)rectangle->w * (uint32)rectangle->h * 2;
    return LoadImagePSX(rectangle, (uint32 *)psx_addr(pixels, bytes));
}

void func_8004c75c(uint32 model)
{
    GsMapModelingData(model);
}

void func_8004d864(uint32 model, uint32 object, uint32 index)
{
    GsLinkObject4(model, object, index);
}

void func_8004c7d4(uint32 tim_body, uint32 *info)
{
    GpuTimImage image;
    const uint8 *body;
    uint32 physical = tim_body & 0x1FFFFFFF;
    uint32 available;
    if (physical >= PSX_DRAM_SIZE)
        abort();
    available = PSX_DRAM_SIZE - physical;
    body = (const uint8 *)psx_addr(tim_body, available);
    if (!gpu_decode_tim_body(body, available, &image))
        abort();
    info[0] = image.mode;
    info[1] = (uint16)image.pixels.x | ((uint32)(uint16)image.pixels.y << 16);
    info[2] = (uint16)image.pixels.w | ((uint32)(uint16)image.pixels.h << 16);
    info[3] = tim_body + (uint32)(image.pixel_data - body);
    if ((image.mode & 8) != 0)
    {
        info[4] = (uint16)image.clut.x | ((uint32)(uint16)image.clut.y << 16);
        info[5] = (uint16)image.clut.w | ((uint32)(uint16)image.clut.h << 16);
        info[6] = tim_body + (uint32)(image.clut_data - body);
    }
}

static uint32 sequence_tone_command_0(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 0, value);
}

static uint32 sequence_tone_command_1(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 1, value);
}

static uint32 sequence_tone_command_2(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 2, value);
}

static uint32 sequence_tone_command_3(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 3, value);
}

static uint32 sequence_tone_command_4(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 4, value);
}

static uint32 sequence_tone_command_5(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 5, value);
}

static uint32 sequence_tone_command_6(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 6, value);
}

static uint32 sequence_tone_command_7(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 7, value);
}

static uint32 sequence_tone_command_8(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 8, value);
}

static uint32 sequence_tone_command_9(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 9, value);
}

static uint32 sequence_tone_command_10(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 10, value);
}

static uint32 sequence_tone_command_11(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 11, value);
}

static uint32 sequence_tone_command_12(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 12, value);
}

static uint32 sequence_tone_command_13(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 13, value);
}

static uint32 sequence_tone_command_14(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 14, value);
}

static uint32 sequence_tone_command_15(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 15, value);
}

static uint32 sequence_tone_command_16(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 16, value);
}

static uint32 sequence_tone_command_17(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 17, value);
}

static uint32 sequence_tone_command_18(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 18, value);
}

static uint32 sequence_tone_command_19(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 19, value);
}

static uint32 sequence_tone_command_20(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 20, value);
}

static uint32 sequence_tone_command_21(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 21, value);
}

static uint32 sequence_tone_command_22(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 22, value);
}

static uint32 sequence_tone_command_23(sint16 bank, sint16 program, sint16 tone, VagAtr attributes, uint8 value)
{
    return func_80076f64(bank, program, tone, 23, value);
}

const SpuToneCommand sequence_data_entry_commands[128] =
{
    {sequence_tone_command_0, 0},
    {sequence_tone_command_1, 0},
    {sequence_tone_command_2, 0},
    {sequence_tone_command_3, 0},
    {sequence_tone_command_4, 0},
    {sequence_tone_command_5, 0},
    {sequence_tone_command_6, 0},
    {sequence_tone_command_7, 0},
    {sequence_tone_command_8, 0},
    {sequence_tone_command_9, 0},
    {sequence_tone_command_10, 0},
    {sequence_tone_command_11, 0},
    {sequence_tone_command_12, 0},
    {sequence_tone_command_13, 0},
    {sequence_tone_command_14, 0},
    {sequence_tone_command_15, 0},
    {sequence_tone_command_16, 0},
    {sequence_tone_command_17, 0},
    {sequence_tone_command_18, 0},
    {sequence_tone_command_19, 0},
    {sequence_tone_command_20, 0},
    {sequence_tone_command_21, 0},
    {sequence_tone_command_22, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
    {sequence_tone_command_23, 0},
};

void func_8007cc3c(void)
{
    SpuStInit();
}

uint32 func_80041700(uint32 device_path)
{
    return (uint32)format(guest_c_string(device_path));
}
