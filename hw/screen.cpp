/*
 * H2 Framebuffer Video Driver
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <hw/port_io.h>
#include <hw/screen.h>
#include <kmem.h>
#include <kernel.h>
#include <hack16.h>

ScreenController::ScreenController()
{
    if(bootinfo.flags & 0x1000)
    {
        framebuffer = (void *)bootinfo.framebufferAddr;
        pitch = bootinfo.framebufferPitch;
        width = bootinfo.framebufferWidth;
        height = bootinfo.framebufferHeight;
        bpp = bootinfo.framebufferBPP;
        fbtype = bootinfo.framebufferType;
    }

    xpos = 0;
    ypos = 0;
    color = 0xFFFFFF;
    bgcolor = 0;

    g_controllers[CTRL_SCREEN] = (UInt32)this;
}

ScreenController::~ScreenController()
{
    g_controllers[CTRL_SCREEN] = 0;
}

void ScreenController::putpixel(int x, int y, UInt32 color)
{
    int bytesPerPixel = bpp/8;
    void *where = (void *)((UInt32)framebuffer + x*bytesPerPixel + y*pitch);
    *(UInt32 *)where = color;
}

void ScreenController::printBackspace() 
{
    int newx = xpos - FONT_WIDTH_hack16;
    int newy = ypos;
    if(newx < 0)
    {
        newx = width - FONT_WIDTH_hack16;
        newy = ypos - FONT_HEIGHT_hack16;
    }
    if(newy < 0)
    {
        newy = 0;
        newx = 0;
    }

    for(int j = 0; j < FONT_HEIGHT_hack16; ++j)
    {
        memset((char *)((UInt32)framebuffer + newx*(bpp/8) + (newy+j)*pitch), 0,
            FONT_WIDTH_hack16*(bpp/8));
    }

    xpos = newx;
    ypos = newy;
}

void ScreenController::fontdemo()
{
    char *msg = "H2OS Kernel! ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";
    for(int pos = 0; msg[pos] != 0; ++pos)
    {
        UInt8 ch = msg[pos];
        if(ch < 0x20)
            continue;
        ch = ch - 0x20;
        int offset = hack16_glyph_dsc[ch].offset;
        int row = 120;

        for(int j = 0; j < 16; ++j)
        {
            int bit = 7;
            int col = pos*FONT_WIDTH_hack16;
            int w = hack16_glyph_dsc[ch].width;
            while(w > 0)
            {
                if(hack16_glyph_bitmap[offset] & (1<<bit))
                    putpixel(col, row, color);
                else
                    putpixel(col, row, bgcolor);
                
                ++col;
                --bit;
                --w;
                if(bit < 0)
                {
                    bit = 7;
                    ++offset;
                }
            }
            if(bit != 7)
                ++offset;
            ++row;
        }
    }
}

void ScreenController::printChar(UInt8 c)
{
    if (c == '\n')
    {
        ypos += FONT_HEIGHT_hack16;
        xpos = 0;
    } else {
        if(c < 0x20) // unprintable
            return;
        c = c - 0x20;

        int offset = hack16_glyph_dsc[c].offset;
        int y = ypos;

        for(int j = 0; j < FONT_HEIGHT_hack16; ++j)
        {
            int bit = 7;
            int x = xpos;
            int w = hack16_glyph_dsc[c].width;
            int pad = (FONT_WIDTH_hack16 - w) / 2;
            while(pad > 0)
            {
                putpixel(x, y, bgcolor);
                ++x;
                --pad;
            }
            while(w > 0)
            {
                if(hack16_glyph_bitmap[offset] & (1<<bit))
                    putpixel(x, y, color);
                else
                    putpixel(x, y, bgcolor);
                
                ++x;
                --bit;
                --w;
                if(bit < 0)
                {
                    bit = 7;
                    ++offset;
                }
            }
            pad = (FONT_WIDTH_hack16 - w) / 2;
            while(pad > 0)
            {
                putpixel(x, y, bgcolor);
                ++x;
                --pad;
            }
            if(pad*2+w < FONT_WIDTH_hack16)
                putpixel(x++, y, bgcolor);
            if(bit != 7)
                ++offset;
            ++y;
        }

        xpos += FONT_WIDTH_hack16;
        if(xpos >= (width - FONT_WIDTH_hack16 - 1))
        {
            xpos = 0;
            ypos += FONT_HEIGHT_hack16;
        }
    }

    // Video scrolling
    if(ypos > (height - FONT_HEIGHT_hack16))
    {
        memcpy((char *)framebuffer, (char *)((UInt32)framebuffer + FONT_HEIGHT_hack16*pitch),
            (height - FONT_HEIGHT_hack16)*pitch + width*(bpp/8));

        // Blank last line
        memset((char *)((UInt32)framebuffer + (height - FONT_HEIGHT_hack16)*pitch),
            0, FONT_HEIGHT_hack16*pitch);
        ypos = height - FONT_HEIGHT_hack16;
        xpos = 0;
    }
    return;
}

UInt32 ScreenController::getX()
{
    return xpos;
}

UInt32 ScreenController::getY()
{
    return ypos;
}

UInt32 ScreenController::getColor()
{
    return color;
}

UInt32 ScreenController::getBackColor()
{
    return bgcolor;
}

void ScreenController::setXY(UInt32 x, UInt32 y)
{
    if(x > width || y > height)
        return;
    xpos = x;
    ypos = y;
}

void ScreenController::setXYChars(UInt32 x, UInt32 y)
{
    x *= FONT_WIDTH_hack16;
    y *= FONT_HEIGHT_hack16;

    if(x > width || y > height)
        return;
    xpos = x;
    ypos = y;
}

void ScreenController::setColor(UInt32 c)
{
    color = c;
}

void ScreenController::setBackColor(UInt32 c)
{
    bgcolor = c;
}

void ScreenController::clearScreen()
{
    memset((UInt32 *)framebuffer, bgcolor, width*height);
    xpos = ypos = 0;
}