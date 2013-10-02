/**
 * @file bayer.c
 *
 * @copyright Copyright (C) 2013 The Imaging Source GmbH; Edgar Thier <edgarthier@gmail.com>
 */

#include "bayer.h"


tBY8Pattern next_pixel (tBY8Pattern pattern)
{
    switch (pattern)
    {
        case BG:    return GB;
        case GB:    return BG;
        case GR:    return RG;
        case RG:    return GR;
    };
    return BG;
}


tBY8Pattern next_line (tBY8Pattern pattern)
{
    switch (pattern)
    {
        case BG:    return GR;
        case GB:    return RG;
        case GR:    return BG;
        case RG:    return GB;
    };
    return BG;
}


char* bayer_to_string (tBY8Pattern pattern)
{
    switch (pattern)
    {
        case BG:    return "bggr";
        case GB:    return "gbrg";
        case GR:    return "grbg";
        case RG:    return "rggb";
    };
    return "bggr";
}


unsigned int initial_offset (tBY8Pattern pattern, unsigned int line_width, unsigned int bytes_per_pixel)
{
    unsigned int first_line_offset = 0;

    /* bayer8; aravis currently does not support 16 and other */
    int bytes_per_line = bytes_per_pixel * line_width / 8;

    switch (pattern)
    {
        case BG:
            first_line_offset += 1;
            break;
        case GB:
            first_line_offset += 0;
            break;
        case GR:
            first_line_offset += bytes_per_line + 1;
            break;
        case RG:
            first_line_offset += bytes_per_line;
            break;
        default:
            break;
    }
    return first_line_offset;
}
