#include "functions.h"

typedef struct RESOURCE
{
    const char *path;
    uint32 first_sector;
    uint32 bytes;
    uint32 sector_bytes;
} RESOURCE;

static const RESOURCE resources[] = {
#include "resource_catalog.inc"
};

static const RESOURCE *resource_by_name(const char *name)
{
    char key[512];
    size_t index, length = 0;
    if (strncmp(name, "i:\\pax\\ob\\", 10) == 0 || strncmp(name, "I:\\PAX\\OB\\", 10) == 0)
        name += 10;
    while (*name == '/' || *name == '\\')
        ++name;
    while (*name && *name != ';')
    {
        if (length + 1 >= sizeof(key))
            return NULL;
        key[length++] = *name == '\\' ? '/' : *name;
        ++name;
    }
    key[length] = 0;
    for (index = 0; index < sizeof(resources) / sizeof(resources[0]); ++index)
        if (_strnicmp(key, resources[index].path, sizeof(key)) == 0)
            return &resources[index];
    return NULL;
}

static const RESOURCE *resource_by_sector(uint32 sector)
{
    size_t index;
    uint32 count;
    for (index = 0; index < sizeof(resources) / sizeof(resources[0]); ++index)
    {
        count = (resources[index].bytes + 2047) / 2048;
        if (sector >= resources[index].first_sector && sector - resources[index].first_sector < count)
            return &resources[index];
    }
    return NULL;
}

typedef struct STREAM_SOURCE
{
    const RESOURCE *resource;
    FILE *file;
} STREAM_SOURCE;

static STREAM_SOURCE stream_source;

static void close_resource_source(void *context)
{
    STREAM_SOURCE *source = (STREAM_SOURCE *)context;
    if (source->file != NULL)
        fclose(source->file);
    source->file = NULL;
    source->resource = NULL;
}

static sint32 read_resource_sector(void *context, uint32 sector, uint8 buffer[2352], uint32 *sector_bytes)
{
    STREAM_SOURCE *source = (STREAM_SOURCE *)context;
    const RESOURCE *resource = resource_by_sector(sector);
    uint32 relative, bytes, offset;
    uint8 *output;
    if (resource == NULL)
        return 0;
    if (source->file == NULL || source->resource != resource)
    {
        close_resource_source(source);
        source->file = open_resource(resource->path);
        if (source->file == NULL)
            return 0;
        source->resource = resource;
    }
    relative = sector - resource->first_sector;
    offset = relative * resource->sector_bytes;
    if (offset > INT32_MAX || fseek(source->file, (long)offset, SEEK_SET) != 0)
        return 0;
    output = resource->sector_bytes == 2352 ? buffer : buffer + 24;
    bytes = resource->sector_bytes == 2352 ? 2352 : resource->bytes - relative * 2048;
    if (bytes > resource->sector_bytes)
        bytes = resource->sector_bytes;
    if (fread(output, 1, bytes, source->file) != bytes)
        return 0;
    if (bytes < resource->sector_bytes)
        memset(output + bytes, 0, resource->sector_bytes - bytes);
    *sector_bytes = resource->sector_bytes;
    return 1;
}

static CdlFILE *search_resource_source(void *context, CdlFILE *result, const char *path)
{
    (void)context;
    return find_extracted_resource(result, path);
}

sint32 mount_resource_source(void)
{
    const RESOURCE *last = &resources[sizeof(resources) / sizeof(resources[0]) - 1];
    XPORT_CD_SOURCE source;
    source.context = &stream_source;
    source.sectors = last->first_sector + (last->bytes + 2047) / 2048;
    source.read_sector = read_resource_sector;
    source.search_file = search_resource_source;
    source.close = close_resource_source;
    return xport_cd_mount_source(&source);
}

CdlFILE *find_extracted_resource(CdlFILE *result, const char *filename)
{
    const RESOURCE *resource = resource_by_name(filename);
    const char *basename;
    FILE *file;
    if (resource == NULL || (file = open_resource(resource->path)) == NULL)
        return NULL;
    fclose(file);
    memset(result, 0, sizeof(*result));
    CdIntToPos((sint32)resource->first_sector, &result->pos);
    result->size = resource->bytes;
    basename = strrchr(resource->path, '/');
    basename = basename == NULL ? resource->path : basename + 1;
    strncpy(result->name, basename, sizeof(result->name));
    return result;
}

CdlFILE *find_movie_resource(CdlFILE *result, uint32 filename)
{
    return find_extracted_resource(result, guest_c_string(filename));
}

sint32 read_resource_blocks(uint32 location, void *destination, uint32 count)
{
    CdlLOC position;
    const RESOURCE *resource, *opened_resource = NULL;
    FILE *file = NULL;
    uint8 *output = (uint8 *)destination;
    uint32 sector, relative, file_offset, bytes, index;
    sint32 success = 0;
    memcpy(&position, &location, sizeof(position));
    sector = (uint32)CdPosToInt(&position);
    if (count > UINT32_MAX / 2048 || destination == NULL)
        return 0;
    for (index = 0; index < count; ++index)
    {
        resource = resource_by_sector(sector + index);
        if (resource == NULL)
            goto finished;
        if (resource != opened_resource)
        {
            if (file != NULL)
                fclose(file);
            file = open_resource(resource->path);
            opened_resource = resource;
            if (file == NULL)
                goto finished;
        }
        relative = sector + index - resource->first_sector;
        file_offset = relative * resource->sector_bytes;
        if (resource->sector_bytes == 2352)
            file_offset += 24;
        if (file_offset > INT32_MAX || fseek(file, (long)file_offset, SEEK_SET) != 0)
            goto finished;
        bytes = resource->bytes - relative * 2048;
        if (bytes > 2048)
            bytes = 2048;
        if (fread(output + index * 2048, 1, bytes, file) != bytes)
            goto finished;
        if (bytes < 2048)
            memset(output + index * 2048 + bytes, 0, 2048 - bytes);
    }
    success = 1;
finished:
    if (file != NULL)
        fclose(file);
    return success;
}

sint32 read_resource_native(const char *filename, uint8 *destination, sint32 source_mode)
{
    FILE *file;
    long length;
    size_t received, chunk;
    uint32 remaining;
    if (source_mode != 0)
        return read_whole_resource(filename, 0, destination);
    file = open_resource(filename);
    if (file == NULL)
    {
        func_800360d4(filename);
        return 0;
    }
    if (fseek(file, 0, SEEK_END) != 0 || (length = ftell(file)) < 0 || length > INT32_MAX || fseek(file, 0, SEEK_SET) != 0)
    {
        fclose(file);
        func_800360d4(filename);
        return 0;
    }
    remaining = (uint32)length;
    do
    {
        chunk = remaining > 0xFFFE ? 0xFFFE : remaining;
        received = fread(destination, 1, chunk, file);
        remaining -= (uint32)received;
        if (received == 0)
            break;
        destination += received;
    } while (remaining != 0);
    fclose(file);
    memset(destination, 0, 2048);
    return (sint32)length;
}

void dispatch_resource_callback(uint32 callback, uint32 value)
{
    switch (callback)
    {
    case 0x80012BFC: func_80012bfc(); break;
    case 0x80015FF8: func_80015ff8(); break;
    case 0x80041114: func_80041114(); break;
    default:
#ifndef NDEBUG
        fprintf(stderr, "OBL: Unknown resource callback %08X\n", callback);
#endif
        abort();
    }
    (void)value;
}

uint32 poll_resource_callback(uint32 callback, uint32 *value)
{
    (void)value;
    switch (callback)
    {
    case 0x80015FF8: return func_80015ff8();
    case 0x80041114: return func_80041114();
    default:
#ifndef NDEBUG
        fprintf(stderr, "OBL: Unknown resource callback %08X\n", callback);
#endif
        abort();
    }
}

sint32 bind_krom_font(void)
{
    static uint8 pixels[0x1B8DE];
    size_t bytes;
    if (!xport_file_read("DATA/KROM15.BIN", pixels, sizeof(pixels), &bytes) || bytes != sizeof(pixels))
        return 0;
    return krom_bind_font(pixels, (uint32)bytes, 0x2000, 0x5D68);
}
