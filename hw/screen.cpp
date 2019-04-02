/*
 * H2 Text-mode Video Driver
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

char ScreenController::defaultTextAttr(char attr)
{
    char a = textAttr;
    textAttr = attr;
    return a;
}

void ScreenController::printBackspace() 
{
    int offset = getCursorOffset() - 2;
    if(offset < 0)
    {
      offset = 0;
    }
    *(char *)(framebuffer + offset) = ' ';
    setCursorOffset(offset);
}

void ScreenController::fontdemo()
{
    int color = 0xFFFFFFFF;

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

int ScreenController::printChar(UInt8 c, int col, int row, char attr)
{
    int color = 0xFFFFFFFF;

    // if (col >= (width - FONT_WIDTH_hack16) || row >= (height - FONT_HEIGHT_hack16))
    //     return getOffset(width - FONT_WIDTH_hack16, height - FONT_HEIGHT_hack16);

    // int offset;
    // if (col >= 0 && row >= 0) offset = getOffset(col, row);
    // else offset = getCursorOffset();

    if (c == '\n')
    {
        // row = getOffsetRow(offset);
        // offset = getOffset(0, row + FONT_HEIGHT_hack16);
        ypos += FONT_HEIGHT_hack16;
        xpos = 0;
    } else {
        if(c < 0x20) // unprintable
            return 0; //getCursorOffset();
        c = c - 0x20;

        int offset = hack16_glyph_dsc[c].offset;
        int y = ypos;

        for(int j = 0; j < FONT_HEIGHT_hack16; ++j)
        {
            int bit = 7;
            int x = xpos;
            int w = hack16_glyph_dsc[c].width;
            while(w > 0)
            {
                if(hack16_glyph_bitmap[offset] & (1<<bit))
                    putpixel(x, y, color);
                ++x;
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
            0, FONT_HEIGHT_hack16*pitch /*+ width*(bpp/8)*/);
        ypos = height - FONT_HEIGHT_hack16;
        xpos = 0;
    }
    // setCursorOffset(offset);
    // return offset;
    return 0;
}

int ScreenController::getCursorOffset()
{
    return cursorOffset;
    // /* Use the VGA ports to get the current cursor position
    //   * 1. Ask for high byte of the cursor offset (data 14)
    //   * 2. Ask for low byte (data 15)
    //   */
    // portByteOut(REG_SCREEN_CTRL, 14);
    // int offset = portByteIn(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    // portByteOut(REG_SCREEN_CTRL, 15);
    // offset += portByteIn(REG_SCREEN_DATA);
    // return offset * 2; /* Position * size of character cell */
}

void ScreenController::setCursorOffset(int offset)
{
    cursorOffset = offset;
    // /* Similar to getCursorOffset, but instead of reading we write data */
    // offset /= 2;
    // portByteOut(REG_SCREEN_CTRL, 14);
    // portByteOut(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    // portByteOut(REG_SCREEN_CTRL, 15);
    // portByteOut(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void ScreenController::clearScreen()
{
    clearScreen(this->textAttr);
}

void ScreenController::clearScreen(const char attr)
{
    char *framebuffer = (char*)framebuffer; // Start of video memory
    unsigned int j = 0;

    while (j < MAX_COLS * MAX_ROWS * 2)
    {
        framebuffer[j++] = ' ';
        framebuffer[j++] = (attr ? attr : (BG_BLACK | FG_GREY));
    }
    setCursorOffset(0); // no need to calc - it is always zero :)
}

char ScreenController::getTextAttr()
{
    return textAttr;
}

int ScreenController::getOffset(int col, int row)
{
    return (row*pitch + col*(bpp/8));
}

int ScreenController::getOffsetRow(int offset)
{
    return (offset - width*(bpp/8)) / pitch;
}

int ScreenController::getOffsetCol(int offset)
{
    return (offset - getOffsetRow(offset)*pitch) / (bpp/8);
}