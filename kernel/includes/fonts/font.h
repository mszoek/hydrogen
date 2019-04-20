#ifndef FONT_H
#define FONT_H

#include <hw/types.h>

typedef struct _fontGlyph
{
    UInt8 width;
    UInt32 offset;
} fontGlyph;


#include <fonts/hack16.h>
#include <fonts/hack20.h>
#include <fonts/anon16.h>
#include <fonts/anon20.h>
#include <fonts/plex16.h>
#include <fonts/plex20.h>

typedef struct _fontEntry
{
    const char *fontname;
    const int width;
    const int height;
    const int bpp;
    const fontGlyph *glyphDsc;
    const UInt8 *glyphBitmap;
} fontEntry;

#define FONT_MAX 6
extern fontEntry systemFonts[FONT_MAX];

#endif // FONT_H
