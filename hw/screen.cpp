/*
 * H2 Text-mode Video Driver
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <hw/port_io.h>
#include <hw/screen.h>
#include <kmem.h>
#include <kernel.h>

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

int ScreenController::printChar(char c, int col, int row, char attr)
{
    unsigned char *vidmem = (unsigned char*) framebuffer;
    if (!attr) attr = 0x0f;

    // Error: print red 'E' if coords aren't correct.
    if (col >= MAX_COLS || row >= MAX_ROWS)
    {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = (BG_RED | FG_GREY | FG_BOLD);
        return getOffset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = getOffset(col, row);
    else offset = getCursorOffset();

    if (c == '\n')
    {
        row = getOffsetRow(offset);
        offset = getOffset(0, row+1);
    } else {
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }

    // Video scrolling
    if (offset >= MAX_ROWS * MAX_COLS * 2)
    {
        int i;
        for (i = 1; i < MAX_ROWS; i++)
        {
            memcpy(getOffset(0, i-1) + (unsigned char*)framebuffer,
              getOffset(0, i) + (unsigned char*)framebuffer, MAX_COLS * 2);
        }

        // Blank last line
        char *last_line = getOffset(0, MAX_ROWS-1) + (unsigned char*)framebuffer;
        for (i = 0; i < MAX_COLS * 2; i++)
        {
            last_line[i] = 0;
        }

        offset -= 2 * MAX_COLS;
    }
    setCursorOffset(offset);
    return offset;
}

int ScreenController::getCursorOffset()
{
    /* Use the VGA ports to get the current cursor position
      * 1. Ask for high byte of the cursor offset (data 14)
      * 2. Ask for low byte (data 15)
      */
    portByteOut(REG_SCREEN_CTRL, 14);
    int offset = portByteIn(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    portByteOut(REG_SCREEN_CTRL, 15);
    offset += portByteIn(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

void ScreenController::setCursorOffset(int offset)
{
    /* Similar to getCursorOffset, but instead of reading we write data */
    offset /= 2;
    portByteOut(REG_SCREEN_CTRL, 14);
    portByteOut(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    portByteOut(REG_SCREEN_CTRL, 15);
    portByteOut(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void ScreenController::clearScreen()
{
    clearScreen(this->textAttr);
}

void ScreenController::clearScreen(const char attr)
{
    char *vidmem = (char*)framebuffer; // Start of video memory
    unsigned int j = 0;

    while (j < MAX_COLS * MAX_ROWS * 2)
    {
        vidmem[j++] = ' ';
        vidmem[j++] = (attr ? attr : (BG_BLACK | FG_GREY));
    }
    setCursorOffset(0); // no need to calc - it is always zero :)
}

char ScreenController::getTextAttr()
{
    return textAttr;
}

static int ScreenController::getOffset(int col, int row) { return 2 * (row * MAX_COLS + col); }
static int ScreenController::getOffsetRow(int offset) { return offset / (2 * MAX_COLS); }
static int ScreenController::getOffsetCol(int offset) { return (offset - (getOffsetRow(offset)*2*MAX_COLS))/2; }