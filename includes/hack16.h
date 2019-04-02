#ifndef HACK16_H
#define HACK16_H

#include <hw/types.h>

#define FONT_FIRST_hack16 32
#define FONT_LAST_hack16 255
#define FONT_GLYPHS_hack16 224
#define FONT_HEIGHT_hack16 16
#define FONT_WIDTH_hack16 12
#define FONT_BPP_hack16 1

typedef struct _fontGlyph
{
    UInt8 width;
    UInt32 offset;
} fontGlyph;

extern const UInt8 hack16_glyph_bitmap[]; 
extern const fontGlyph hack16_glyph_dsc[];

#endif