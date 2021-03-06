/*
 * H2 Framebuffer Video Driver
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <hw/port_io.h>
#include <hw/screen.h>
#include <kmem.h>
#include <kernel.h>
#include <h2logo.h>

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

    // Remap the framebuffer to a known location
    framebuffer = (void *)vmm->remap(bootinfo.framebufferAddr, pitch*(height+1), FRAMEBUFFER_VMA);
    bootinfo.framebufferAddr = (UInt64)framebuffer;

    xpos = 0;
    ypos = 0;
    color = 0xAFAFAF;
    bgcolor = 0;

    if(width > 1920)
        setFont(5); // 20px
    else
        setFont(4); // 16px
    

    g_controllers[CTRL_SCREEN] = (UInt64)this;
}

ScreenController::~ScreenController()
{
    g_controllers[CTRL_SCREEN] = 0;
}

void ScreenController::setFont(int f)
{
    if(f < 0 || f > (FONT_MAX - 1))
        return;

    fontNumber = f;
    fontWidth = systemFonts[fontNumber].width;
    fontHeight = systemFonts[fontNumber].height;
    fontbpp = systemFonts[fontNumber].bpp;
    glyphDsc = systemFonts[fontNumber].glyphDsc;
    glyphBitmap = systemFonts[fontNumber].glyphBitmap;
}

void ScreenController::putpixel(int x, int y, UInt32 color)
{
    int bytesPerPixel = bpp/8;
    void *where = (void *)((UInt64)framebuffer + x*bytesPerPixel + y*pitch);
    *(UInt32 *)where = color;
}

void ScreenController::printBackspace() 
{
    int newx = xpos - fontWidth;
    int newy = ypos;
    if(newx < 0)
    {
        newx = width - fontWidth;
        newy = ypos - fontHeight;
    }
    if(newy < 0)
    {
        newy = 0;
        newx = 0;
    }

    for(int j = 0; j < fontHeight; ++j)
    {
        memset((char *)((UInt64)framebuffer + newx*(bpp/8) + (newy+j)*pitch), 0,
            fontWidth*(bpp/8));
    }

    xpos = newx;
    ypos = newy;
}

void ScreenController::printChar(UInt8 c)
{
    if (c == '\n')
    {
        ypos += fontHeight;
        xpos = 0;
    } else {
        if(c < 0x20) // unprintable
            return;
        c = c - 0x20;

        int offset = glyphDsc[c].offset;
        int y = ypos;

        for(int j = 0; j < fontHeight; ++j)
        {
            int bit = 7;
            int x = xpos;
            int w = glyphDsc[c].width;

            /* pad to fixed width */
            int pad = (fontWidth - w) / 2;
            while(pad > 0)
            {
                putpixel(x, y, bgcolor);
                ++x;
                --pad;
            }

            /* render the actual character */
            while(w > 0)
            {
                int mask = 0;
                switch(fontbpp)
                {
                    case 4: // anti-aliasing (subpixel rendering)
                    {
                        int g = (glyphBitmap[offset] & (1<<bit--)) ? 0xFF : 0;
                        int b = (glyphBitmap[offset] & (1<<bit--)) ? 0xFF : 0;
                        int r = (glyphBitmap[offset] & (1<<bit--)) ? 0xFF : 0;
                        mask = (r|g|b) ? ((r|0xE0) << 16) | ((g|0xE2) << 8) | (b|0xE0) : 0;
                        break;
                    }

                    default: // 1bpp
                        if(glyphBitmap[offset] & (1<<bit))
                            mask = 0xFFFFFF;
                }

                if(mask)
                    putpixel(x, y, color & mask);
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

            /* pad the other side */
            pad = (fontWidth - w) / 2;
            while(pad > 0)
            {
                putpixel(x, y, bgcolor);
                ++x;
                --pad;
            }
            if(pad*2+w < fontWidth)
                putpixel(x++, y, bgcolor);
            if(bit != 7)
                ++offset;
            ++y;
        }

        /* update 'cursor' position */
        xpos += fontWidth;
        if(xpos >= (width - fontWidth - 1))
        {
            xpos = 0;
            ypos += fontHeight;
        }
    }

    /* scroll if necessary */
    if(ypos > (height - fontHeight))
    {
        memcpy((char *)framebuffer, (char *)((UInt64)framebuffer + fontHeight*pitch),
            (height - fontHeight)*pitch + width*(bpp/8));

        // Blank last line
        memset((char *)((UInt64)framebuffer + (height - fontHeight)*pitch),
            0, fontHeight*pitch);
        ypos = height - fontHeight;
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
    x *= fontWidth;
    y *= fontHeight;

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

void ScreenController::drawLogo()
{
    for(int y = 0; y < gimp_image.height; ++y)
    {
        memcpy((char *)(FRAMEBUFFER_VMA+((y+fontHeight+2)*pitch)),
            (char *)(gimp_image.pixel_data+gimp_image.width*y*gimp_image.bytes_per_pixel),
            gimp_image.width*gimp_image.bytes_per_pixel);
    }
    setXY(0, gimp_image.height+fontHeight+2);
}

int ScreenController::getFBInfo(struct fbInfo *fi)
{
    fi->fb = framebuffer;
    fi->pitch = pitch;
    fi->width = width;
    fi->height = height;
    fi->bpp = bpp;
    return 0;
}
