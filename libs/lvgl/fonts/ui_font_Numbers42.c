/*******************************************************************************
 * Size: 42 px
 * Bpp: 2
 * Opts: --bpp 2 --size 42 --font D:\Work\Arduino\PinetimeArduino\assets\Fonts\Mona-Sans-ExtraBold.ttf -o D:\Work\Arduino\PinetimeArduino\assets\Fonts\ui_font_Numbers42.c --format lvgl --symbols 0123456789+-:% --no-compress --no-prefilter
 ******************************************************************************/

#include "lvgl.h"

#ifndef UI_FONT_NUMBERS42
#define UI_FONT_NUMBERS42 1
#endif

#if UI_FONT_NUMBERS42

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0025 "%" */
    0x0, 0x2f, 0xe4, 0x0, 0x0, 0x0, 0x7f, 0xd0,
    0x0, 0xb, 0xff, 0xf8, 0x0, 0x0, 0x3, 0xfe,
    0x0, 0x0, 0x7f, 0xff, 0xf4, 0x0, 0x0, 0x2f,
    0xf0, 0x0, 0x3, 0xff, 0xff, 0xf0, 0x0, 0x1,
    0xff, 0x40, 0x0, 0x2f, 0xf4, 0x7f, 0xd0, 0x0,
    0xf, 0xfc, 0x0, 0x0, 0xff, 0xc0, 0xff, 0x80,
    0x0, 0xbf, 0xc0, 0x0, 0x3, 0xfe, 0x2, 0xff,
    0x0, 0x3, 0xfe, 0x0, 0x0, 0xf, 0xf8, 0xb,
    0xfc, 0x0, 0x3f, 0xf0, 0x0, 0x0, 0x3f, 0xe0,
    0x2f, 0xf0, 0x1, 0xff, 0x40, 0x0, 0x0, 0xff,
    0x80, 0xbf, 0xc0, 0xf, 0xf8, 0x0, 0x0, 0x3,
    0xfe, 0x2, 0xff, 0x0, 0xbf, 0xc0, 0x0, 0x0,
    0xb, 0xfc, 0xf, 0xf8, 0x7, 0xfd, 0x0, 0x0,
    0x0, 0x1f, 0xf4, 0x7f, 0xd0, 0x3f, 0xf0, 0x0,
    0x0, 0x0, 0x3f, 0xff, 0xff, 0x2, 0xff, 0x0,
    0x0, 0x0, 0x0, 0x7f, 0xff, 0xf4, 0xf, 0xf8,
    0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0x40, 0xff,
    0xc0, 0x6, 0xf9, 0x0, 0x0, 0x2f, 0x90, 0x7,
    0xfd, 0x1, 0xff, 0xfe, 0x0, 0x0, 0x0, 0x0,
    0x3f, 0xe0, 0x1f, 0xff, 0xfe, 0x0, 0x0, 0x0,
    0x2, 0xff, 0x0, 0xff, 0xff, 0xfc, 0x0, 0x0,
    0x0, 0x1f, 0xf4, 0x7, 0xfd, 0x1f, 0xf8, 0x0,
    0x0, 0x0, 0xff, 0x80, 0x2f, 0xf0, 0x2f, 0xf0,
    0x0, 0x0, 0xb, 0xfc, 0x0, 0xff, 0x80, 0xbf,
    0xc0, 0x0, 0x0, 0x3f, 0xd0, 0x3, 0xfe, 0x1,
    0xff, 0x0, 0x0, 0x3, 0xff, 0x0, 0xf, 0xf8,
    0x7, 0xfc, 0x0, 0x0, 0x1f, 0xf0, 0x0, 0x3f,
    0xe0, 0x1f, 0xf0, 0x0, 0x0, 0xff, 0x80, 0x0,
    0xbf, 0xc0, 0xbf, 0xc0, 0x0, 0xb, 0xfc, 0x0,
    0x1, 0xff, 0x43, 0xfe, 0x0, 0x0, 0x7f, 0xd0,
    0x0, 0x3, 0xff, 0xff, 0xf4, 0x0, 0x3, 0xfe,
    0x0, 0x0, 0x7, 0xff, 0xff, 0x80, 0x0, 0x2f,
    0xf0, 0x0, 0x0, 0xb, 0xff, 0xf8, 0x0, 0x1,
    0xff, 0x40, 0x0, 0x0, 0x2, 0xfe, 0x40, 0x0,

    /* U+002B "+" */
    0x0, 0x1, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x7f,
    0xf4, 0x0, 0x0, 0x0, 0x1f, 0xfd, 0x0, 0x0,
    0x0, 0x7, 0xff, 0x40, 0x0, 0x0, 0x1, 0xff,
    0xd0, 0x0, 0x0, 0x0, 0x7f, 0xf4, 0x0, 0x0,
    0x0, 0x1f, 0xfd, 0x0, 0x1, 0xaa, 0xaf, 0xff,
    0xaa, 0xa8, 0xbf, 0xff, 0xff, 0xff, 0xff, 0x6f,
    0xff, 0xff, 0xff, 0xff, 0xdb, 0xff, 0xff, 0xff,
    0xff, 0xf6, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xbf,
    0xff, 0xff, 0xff, 0xff, 0x40, 0x0, 0x7f, 0xf4,
    0x0, 0x0, 0x0, 0x1f, 0xfd, 0x0, 0x0, 0x0,
    0x7, 0xff, 0x40, 0x0, 0x0, 0x1, 0xff, 0xd0,
    0x0, 0x0, 0x0, 0x7f, 0xf4, 0x0, 0x0, 0x0,
    0x1f, 0xfd, 0x0, 0x0, 0x0, 0x7, 0xff, 0x40,
    0x0,

    /* U+002D "-" */
    0xbf, 0xff, 0xff, 0xfa, 0xff, 0xff, 0xff, 0xeb,
    0xff, 0xff, 0xff, 0xaf, 0xff, 0xff, 0xfe, 0xbf,
    0xff, 0xff, 0xfa, 0xff, 0xff, 0xff, 0xe0,

    /* U+0030 "0" */
    0x0, 0x0, 0x6f, 0xfa, 0x0, 0x0, 0x0, 0xb,
    0xff, 0xff, 0xe0, 0x0, 0x0, 0x3f, 0xff, 0xff,
    0xfc, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0,
    0x3, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7, 0xff,
    0xff, 0xff, 0xff, 0xe0, 0xf, 0xff, 0xf0, 0xf,
    0xff, 0xf0, 0x1f, 0xff, 0xc0, 0x3, 0xff, 0xf4,
    0x3f, 0xff, 0x40, 0x1, 0xff, 0xfc, 0x3f, 0xff,
    0x0, 0x0, 0xff, 0xfc, 0x7f, 0xfe, 0x0, 0x0,
    0xbf, 0xfd, 0x7f, 0xfe, 0x0, 0x0, 0xbf, 0xfd,
    0xbf, 0xfd, 0x0, 0x0, 0x7f, 0xfe, 0xbf, 0xfd,
    0x0, 0x0, 0x7f, 0xfe, 0xbf, 0xfd, 0x0, 0x0,
    0x7f, 0xfe, 0xbf, 0xfd, 0x0, 0x0, 0x7f, 0xff,
    0xbf, 0xfd, 0x0, 0x0, 0x7f, 0xfe, 0xbf, 0xfd,
    0x0, 0x0, 0x7f, 0xfe, 0xbf, 0xfd, 0x0, 0x0,
    0x7f, 0xfe, 0x7f, 0xfe, 0x0, 0x0, 0xbf, 0xfd,
    0x3f, 0xfe, 0x0, 0x0, 0xbf, 0xfd, 0x3f, 0xff,
    0x0, 0x0, 0xff, 0xfc, 0x2f, 0xff, 0x40, 0x1,
    0xff, 0xfc, 0x1f, 0xff, 0xc0, 0x3, 0xff, 0xf4,
    0xf, 0xff, 0xf4, 0x1f, 0xff, 0xf0, 0x7, 0xff,
    0xff, 0xff, 0xff, 0xe0, 0x3, 0xff, 0xff, 0xff,
    0xff, 0xc0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0,
    0x0, 0x3f, 0xff, 0xff, 0xfc, 0x0, 0x0, 0xb,
    0xff, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x6f, 0xf9,
    0x0, 0x0,

    /* U+0031 "1" */
    0x0, 0x0, 0x3f, 0xfe, 0x0, 0x0, 0x7f, 0xfe,
    0x0, 0x0, 0xbf, 0xfe, 0x0, 0x1, 0xff, 0xfe,
    0x0, 0x7, 0xff, 0xfe, 0x0, 0x6f, 0xff, 0xfe,
    0x3f, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xfe,
    0x3f, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xfe,
    0x3f, 0xff, 0xff, 0xfe, 0x15, 0x55, 0xbf, 0xfe,
    0x0, 0x0, 0x7f, 0xfe, 0x0, 0x0, 0x7f, 0xfe,
    0x0, 0x0, 0x7f, 0xfe, 0x0, 0x0, 0x7f, 0xfe,
    0x0, 0x0, 0x7f, 0xfe, 0x0, 0x0, 0x7f, 0xfe,
    0x0, 0x0, 0x7f, 0xfe, 0x0, 0x0, 0x7f, 0xfe,
    0x0, 0x0, 0x7f, 0xfe, 0x0, 0x0, 0x7f, 0xfe,
    0x0, 0x0, 0x7f, 0xfe, 0x0, 0x0, 0x7f, 0xfe,
    0x0, 0x0, 0x7f, 0xfe, 0x0, 0x0, 0x7f, 0xfe,
    0x0, 0x0, 0x7f, 0xfe, 0x0, 0x0, 0x7f, 0xfe,
    0x0, 0x0, 0x7f, 0xfe, 0x0, 0x0, 0x7f, 0xfe,
    0x0, 0x0, 0x7f, 0xfe,

    /* U+0032 "2" */
    0x0, 0x1, 0xbf, 0xfe, 0x0, 0x0, 0x0, 0x7f,
    0xff, 0xff, 0xc0, 0x0, 0xf, 0xff, 0xff, 0xff,
    0xd0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xd0, 0xb,
    0xff, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff,
    0xff, 0xff, 0x82, 0xff, 0xfe, 0x6, 0xff, 0xff,
    0xf, 0xff, 0xd0, 0x2, 0xff, 0xfc, 0x3f, 0xff,
    0x0, 0x3, 0xff, 0xf5, 0xff, 0xf8, 0x0, 0xf,
    0xff, 0xd2, 0xaa, 0x90, 0x0, 0x3f, 0xff, 0x40,
    0x0, 0x0, 0x1, 0xff, 0xfc, 0x0, 0x0, 0x0,
    0xf, 0xff, 0xf0, 0x0, 0x0, 0x0, 0xff, 0xff,
    0x80, 0x0, 0x0, 0x1f, 0xff, 0xfc, 0x0, 0x0,
    0x2, 0xff, 0xff, 0xd0, 0x0, 0x0, 0x3f, 0xff,
    0xfd, 0x0, 0x0, 0x7, 0xff, 0xff, 0xd0, 0x0,
    0x0, 0xbf, 0xff, 0xfd, 0x0, 0x0, 0xf, 0xff,
    0xff, 0xc0, 0x0, 0x0, 0xff, 0xff, 0xf8, 0x0,
    0x0, 0xb, 0xff, 0xff, 0x40, 0x0, 0x0, 0x7f,
    0xff, 0xf0, 0x0, 0x0, 0x3, 0xff, 0xfe, 0x0,
    0x0, 0x0, 0x1f, 0xff, 0xf4, 0x0, 0x0, 0x0,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff,
    0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x80,

    /* U+0033 "3" */
    0x0, 0x1, 0xbf, 0xfe, 0x40, 0x0, 0x0, 0x1f,
    0xff, 0xff, 0xf8, 0x0, 0x0, 0xff, 0xff, 0xff,
    0xff, 0x0, 0x3, 0xff, 0xff, 0xff, 0xff, 0xc0,
    0xf, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff,
    0xff, 0xff, 0xff, 0xf4, 0x3f, 0xff, 0xe0, 0x1f,
    0xff, 0xf8, 0x3f, 0xff, 0x40, 0x3, 0xff, 0xfc,
    0x7f, 0xff, 0x0, 0x2, 0xff, 0xfc, 0x6a, 0xa9,
    0x0, 0x1, 0xff, 0xf8, 0x0, 0x0, 0x0, 0x2,
    0xff, 0xf8, 0x0, 0x0, 0x0, 0x3, 0xff, 0xf0,
    0x0, 0x0, 0x15, 0x6f, 0xff, 0xe0, 0x0, 0x0,
    0xbf, 0xff, 0xff, 0xc0, 0x0, 0x0, 0xbf, 0xff,
    0xfe, 0x0, 0x0, 0x0, 0xbf, 0xff, 0xfd, 0x0,
    0x0, 0x0, 0xbf, 0xff, 0xff, 0xc0, 0x0, 0x0,
    0xbf, 0xff, 0xff, 0xf0, 0x0, 0x0, 0x0, 0xb,
    0xff, 0xf4, 0x0, 0x0, 0x0, 0x1, 0xff, 0xfc,
    0x0, 0x0, 0x0, 0x0, 0xff, 0xfc, 0x6a, 0xa9,
    0x0, 0x0, 0xff, 0xfc, 0xbf, 0xfe, 0x0, 0x0,
    0xff, 0xfc, 0x7f, 0xff, 0x0, 0x2, 0xff, 0xfc,
    0x3f, 0xff, 0xd0, 0x1f, 0xff, 0xfc, 0x2f, 0xff,
    0xff, 0xff, 0xff, 0xf4, 0xf, 0xff, 0xff, 0xff,
    0xff, 0xf0, 0x7, 0xff, 0xff, 0xff, 0xff, 0xc0,
    0x1, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x2f,
    0xff, 0xff, 0xf4, 0x0, 0x0, 0x1, 0xbf, 0xfe,
    0x40, 0x0,

    /* U+0034 "4" */
    0x0, 0x0, 0x0, 0xbf, 0xff, 0xd0, 0x0, 0x0,
    0x0, 0x1f, 0xff, 0xfd, 0x0, 0x0, 0x0, 0x3,
    0xff, 0xff, 0xd0, 0x0, 0x0, 0x0, 0xbf, 0xff,
    0xfd, 0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0xd0,
    0x0, 0x0, 0x3, 0xff, 0xff, 0xfd, 0x0, 0x0,
    0x0, 0x7f, 0xff, 0xff, 0xd0, 0x0, 0x0, 0xf,
    0xff, 0xff, 0xfd, 0x0, 0x0, 0x2, 0xff, 0xff,
    0xff, 0xd0, 0x0, 0x0, 0x7f, 0xfd, 0xbf, 0xfd,
    0x0, 0x0, 0xf, 0xff, 0xcb, 0xff, 0xd0, 0x0,
    0x2, 0xff, 0xf0, 0xbf, 0xfd, 0x0, 0x0, 0x3f,
    0xfe, 0xb, 0xff, 0xd0, 0x0, 0xf, 0xff, 0xc0,
    0xbf, 0xfd, 0x0, 0x1, 0xff, 0xf4, 0xb, 0xff,
    0xd0, 0x0, 0x3f, 0xfe, 0x0, 0xbf, 0xfd, 0x0,
    0xb, 0xff, 0xc0, 0xb, 0xff, 0xd0, 0x1, 0xff,
    0xf4, 0x0, 0xbf, 0xfd, 0x0, 0x3f, 0xfe, 0x0,
    0xb, 0xff, 0xd0, 0xb, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfc, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xcb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xbf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xcb, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xc0, 0x0, 0x0, 0x0, 0xbf, 0xfd,
    0x0, 0x0, 0x0, 0x0, 0xb, 0xff, 0xd0, 0x0,
    0x0, 0x0, 0x0, 0xbf, 0xfd, 0x0, 0x0, 0x0,
    0x0, 0xb, 0xff, 0xd0, 0x0, 0x0, 0x0, 0x0,
    0xbf, 0xfd, 0x0, 0x0, 0x0, 0x0, 0xb, 0xff,
    0xd0, 0x0,

    /* U+0035 "5" */
    0xb, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf, 0xff,
    0xff, 0xff, 0xff, 0xf0, 0xf, 0xff, 0xff, 0xff,
    0xff, 0xf0, 0xf, 0xff, 0xff, 0xff, 0xff, 0xf0,
    0xf, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf, 0xff,
    0xff, 0xff, 0xff, 0xf0, 0xf, 0xff, 0x80, 0x0,
    0x0, 0x0, 0xf, 0xff, 0x40, 0x0, 0x0, 0x0,
    0xf, 0xff, 0x40, 0x0, 0x0, 0x0, 0xf, 0xff,
    0x40, 0x0, 0x0, 0x0, 0xf, 0xff, 0x46, 0xfe,
    0x80, 0x0, 0xf, 0xff, 0xbf, 0xff, 0xfd, 0x0,
    0xf, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff,
    0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xff,
    0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc,
    0x1f, 0xff, 0xf4, 0xb, 0xff, 0xfc, 0x1f, 0xff,
    0xc0, 0x1, 0xff, 0xfd, 0x1a, 0xaa, 0x0, 0x0,
    0xff, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xfe,
    0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0x2a, 0xaa,
    0x0, 0x0, 0x7f, 0xfe, 0x3f, 0xff, 0x40, 0x0,
    0xff, 0xfe, 0x3f, 0xff, 0xc0, 0x1, 0xff, 0xfd,
    0x2f, 0xff, 0xf5, 0x1b, 0xff, 0xfc, 0xf, 0xff,
    0xff, 0xff, 0xff, 0xf8, 0xb, 0xff, 0xff, 0xff,
    0xff, 0xf0, 0x2, 0xff, 0xff, 0xff, 0xff, 0xd0,
    0x0, 0xbf, 0xff, 0xff, 0xff, 0x0, 0x0, 0x1f,
    0xff, 0xff, 0xf8, 0x0, 0x0, 0x1, 0xbf, 0xfe,
    0x40, 0x0,

    /* U+0036 "6" */
    0x0, 0x0, 0x2f, 0xff, 0x90, 0x0, 0x0, 0x0,
    0xff, 0xff, 0xff, 0x40, 0x0, 0x1, 0xff, 0xff,
    0xff, 0xf8, 0x0, 0x2, 0xff, 0xff, 0xff, 0xff,
    0x80, 0x1, 0xff, 0xff, 0xff, 0xff, 0xf4, 0x0,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x7f, 0xff,
    0xd0, 0x6f, 0xff, 0xd0, 0x3f, 0xff, 0x80, 0x2,
    0xff, 0xf8, 0xf, 0xff, 0xc0, 0x0, 0x2a, 0xa9,
    0x7, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x2, 0xff,
    0xf4, 0x0, 0x0, 0x0, 0x0, 0xff, 0xfc, 0xb,
    0xff, 0xe0, 0x0, 0x3f, 0xff, 0x2f, 0xff, 0xff,
    0x40, 0xf, 0xff, 0xef, 0xff, 0xff, 0xf8, 0x3,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x40, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xf8, 0x7,
    0xff, 0xfd, 0xf, 0xff, 0xf8, 0x0, 0x3f, 0xff,
    0x83, 0xff, 0xfc, 0x0, 0x7, 0xff, 0xf0, 0xff,
    0xfe, 0x0, 0x0, 0xff, 0xfc, 0x3f, 0xff, 0x80,
    0x0, 0x3f, 0xff, 0xb, 0xff, 0xe0, 0x0, 0xf,
    0xff, 0xc1, 0xff, 0xfc, 0x0, 0x7, 0xff, 0xf0,
    0x3f, 0xff, 0x80, 0x3, 0xff, 0xfc, 0xb, 0xff,
    0xf9, 0x7, 0xff, 0xfd, 0x0, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x0, 0x2f, 0xff, 0xff, 0xff, 0xff,
    0x40, 0x3, 0xff, 0xff, 0xff, 0xff, 0x80, 0x0,
    0x2f, 0xff, 0xff, 0xff, 0x80, 0x0, 0x1, 0xff,
    0xff, 0xff, 0x40, 0x0, 0x0, 0x6, 0xff, 0xf9,
    0x0, 0x0,

    /* U+0037 "7" */
    0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff,
    0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe,
    0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff,
    0xff, 0xff, 0xff, 0xfd, 0x3f, 0xf8, 0x0, 0x3,
    0xff, 0xf8, 0x3f, 0xf4, 0x0, 0xb, 0xff, 0xf0,
    0x3f, 0xf4, 0x0, 0x1f, 0xff, 0xd0, 0x3f, 0xf4,
    0x0, 0x3f, 0xff, 0xc0, 0x3f, 0xf4, 0x0, 0x7f,
    0xff, 0x0, 0x0, 0x0, 0x0, 0xff, 0xfe, 0x0,
    0x0, 0x0, 0x2, 0xff, 0xfc, 0x0, 0x0, 0x0,
    0x3, 0xff, 0xf8, 0x0, 0x0, 0x0, 0x7, 0xff,
    0xf0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xf0, 0x0,
    0x0, 0x0, 0xf, 0xff, 0xd0, 0x0, 0x0, 0x0,
    0x2f, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x3f, 0xff,
    0x80, 0x0, 0x0, 0x0, 0x3f, 0xff, 0x40, 0x0,
    0x0, 0x0, 0x7f, 0xff, 0x0, 0x0, 0x0, 0x0,
    0xbf, 0xff, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff,
    0x0, 0x0, 0x0, 0x0, 0xff, 0xfe, 0x0, 0x0,
    0x0, 0x0, 0xff, 0xfd, 0x0, 0x0, 0x0, 0x1,
    0xff, 0xfd, 0x0, 0x0, 0x0, 0x1, 0xff, 0xfd,
    0x0, 0x0, 0x0, 0x1, 0xff, 0xfc, 0x0, 0x0,
    0x0, 0x2, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x2,
    0xff, 0xfc, 0x0, 0x0, 0x0, 0x2, 0xff, 0xfc,
    0x0, 0x0,

    /* U+0038 "8" */
    0x0, 0x1, 0xbf, 0xfe, 0x80, 0x0, 0x0, 0x1f,
    0xff, 0xff, 0xfd, 0x0, 0x0, 0xff, 0xff, 0xff,
    0xff, 0x80, 0x3, 0xff, 0xff, 0xff, 0xff, 0xe0,
    0xb, 0xff, 0xff, 0xff, 0xff, 0xf4, 0xf, 0xff,
    0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xf0, 0x7,
    0xff, 0xfc, 0x2f, 0xff, 0xc0, 0x0, 0xff, 0xfd,
    0x2f, 0xff, 0x80, 0x0, 0xff, 0xfd, 0x2f, 0xff,
    0x80, 0x0, 0xff, 0xfd, 0x1f, 0xff, 0xc0, 0x0,
    0xff, 0xfc, 0xf, 0xff, 0xd0, 0x2, 0xff, 0xfc,
    0xb, 0xff, 0xfe, 0xaf, 0xff, 0xf0, 0x2, 0xff,
    0xff, 0xff, 0xff, 0xd0, 0x0, 0x7f, 0xff, 0xff,
    0xfe, 0x0, 0x0, 0x2f, 0xff, 0xff, 0xfd, 0x0,
    0x1, 0xff, 0xff, 0xff, 0xff, 0xd0, 0xb, 0xff,
    0xff, 0xff, 0xff, 0xf4, 0xf, 0xff, 0xf4, 0x7,
    0xff, 0xfc, 0x2f, 0xff, 0xc0, 0x0, 0xff, 0xfd,
    0x3f, 0xff, 0x40, 0x0, 0xbf, 0xfe, 0x3f, 0xff,
    0x40, 0x0, 0xbf, 0xff, 0x3f, 0xff, 0x40, 0x0,
    0xbf, 0xff, 0x3f, 0xff, 0xc0, 0x0, 0xff, 0xff,
    0x3f, 0xff, 0xf4, 0x7, 0xff, 0xfe, 0x2f, 0xff,
    0xff, 0xff, 0xff, 0xfd, 0xf, 0xff, 0xff, 0xff,
    0xff, 0xfc, 0x7, 0xff, 0xff, 0xff, 0xff, 0xf0,
    0x1, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0, 0x2f,
    0xff, 0xff, 0xfd, 0x0, 0x0, 0x1, 0xbf, 0xfe,
    0x90, 0x0,

    /* U+0039 "9" */
    0x0, 0x1, 0xbf, 0xfe, 0x0, 0x0, 0x0, 0x1f,
    0xff, 0xff, 0xf0, 0x0, 0x0, 0xff, 0xff, 0xff,
    0xfe, 0x0, 0x3, 0xff, 0xff, 0xff, 0xff, 0x80,
    0xb, 0xff, 0xff, 0xff, 0xff, 0xd0, 0x1f, 0xff,
    0xff, 0xff, 0xff, 0xf0, 0x2f, 0xff, 0xf4, 0x1f,
    0xff, 0xf8, 0x3f, 0xff, 0x80, 0x3, 0xff, 0xfc,
    0x3f, 0xff, 0x0, 0x0, 0xff, 0xfc, 0x7f, 0xff,
    0x0, 0x0, 0xff, 0xfd, 0x7f, 0xff, 0x0, 0x0,
    0xff, 0xfe, 0x7f, 0xff, 0x0, 0x0, 0xff, 0xfe,
    0x3f, 0xff, 0x0, 0x0, 0xff, 0xff, 0x3f, 0xff,
    0x80, 0x3, 0xff, 0xff, 0x2f, 0xff, 0xe0, 0x1f,
    0xff, 0xff, 0xf, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x7, 0xff, 0xff, 0xff, 0xff, 0xff, 0x2, 0xff,
    0xff, 0xff, 0xbf, 0xff, 0x0, 0x7f, 0xff, 0xfd,
    0x7f, 0xff, 0x0, 0xb, 0xff, 0xe0, 0x7f, 0xfe,
    0x0, 0x0, 0x0, 0x0, 0x7f, 0xfd, 0x0, 0x0,
    0x0, 0x0, 0xbf, 0xfd, 0x15, 0x55, 0x0, 0x0,
    0xff, 0xfc, 0x3f, 0xff, 0x40, 0x3, 0xff, 0xf8,
    0x2f, 0xff, 0xe4, 0x1f, 0xff, 0xf4, 0xf, 0xff,
    0xff, 0xff, 0xff, 0xf0, 0xb, 0xff, 0xff, 0xff,
    0xff, 0xc0, 0x3, 0xff, 0xff, 0xff, 0xff, 0x40,
    0x0, 0xff, 0xff, 0xff, 0xfd, 0x0, 0x0, 0x1f,
    0xff, 0xff, 0xe0, 0x0, 0x0, 0x1, 0xbf, 0xf9,
    0x0, 0x0,

    /* U+003A ":" */
    0xff, 0xfb, 0xff, 0xef, 0xff, 0xbf, 0xfe, 0xff,
    0xfb, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xff, 0xef,
    0xff, 0xbf, 0xfe, 0xff, 0xfb, 0xff, 0xef, 0xff,
    0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 593, .box_w = 35, .box_h = 31, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 366, .box_w = 21, .box_h = 20, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 377, .adv_w = 269, .box_w = 15, .box_h = 6, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 400, .adv_w = 416, .box_w = 24, .box_h = 31, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 586, .adv_w = 306, .box_w = 16, .box_h = 31, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 710, .adv_w = 405, .box_w = 23, .box_h = 31, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 889, .adv_w = 421, .box_w = 24, .box_h = 31, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1075, .adv_w = 447, .box_w = 26, .box_h = 31, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1277, .adv_w = 427, .box_w = 24, .box_h = 31, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1463, .adv_w = 428, .box_w = 25, .box_h = 31, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1657, .adv_w = 430, .box_w = 24, .box_h = 31, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1843, .adv_w = 427, .box_w = 24, .box_h = 31, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2029, .adv_w = 429, .box_w = 24, .box_h = 31, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2215, .adv_w = 171, .box_w = 7, .box_h = 23, .ofs_x = 2, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_0[] = {
    0, 0, 0, 0, 0, 0, 1, 0,
    2, 0, 0, 3, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 37, .range_length = 22, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = glyph_id_ofs_list_0, .list_length = 22, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    6, 8,
    8, 4,
    8, 5,
    8, 11,
    10, 8,
    10, 11,
    11, 4,
    11, 8,
    11, 12
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -8, 3, -5, -37, 6, -11, -17, -65,
    -17
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 9,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_Numbers42 = {
#else
lv_font_t ui_font_Numbers42 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 31,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_NUMBERS42*/

