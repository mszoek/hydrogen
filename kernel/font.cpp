#include <fonts/font.h>

fontEntry systemFonts[FONT_MAX] = 
{
    {
        "Anonymous Pro 16px",
        FONT_WIDTH_anon16,
        FONT_HEIGHT_anon16,
        FONT_BPP_anon16,
        anon16_glyph_dsc,
        anon16_glyph_bitmap
    },
    {
        "Anonymous Pro 20px",
        FONT_WIDTH_anon20,
        FONT_HEIGHT_anon20,
        FONT_BPP_anon20,
        anon20_glyph_dsc,
        anon20_glyph_bitmap
    },
    {
        "Hack 16px",
        FONT_WIDTH_hack16,
        FONT_HEIGHT_hack16,
        FONT_BPP_hack16,
        hack16_glyph_dsc,
        hack16_glyph_bitmap
    },
    {
        "Hack 20px",
        FONT_WIDTH_hack20,
        FONT_HEIGHT_hack20,
        FONT_BPP_hack20,
        hack20_glyph_dsc,
        hack20_glyph_bitmap
    },
    {
        "IBM Plex 16px",
        FONT_WIDTH_plex16,
        FONT_HEIGHT_plex16,
        FONT_BPP_plex16,
        plex16_glyph_dsc,
        plex16_glyph_bitmap
    },
    {
        "IBM Plex 20px",
        FONT_WIDTH_plex20,
        FONT_HEIGHT_plex20,
        FONT_BPP_plex20,
        plex20_glyph_dsc,
        plex20_glyph_bitmap
    }
};
