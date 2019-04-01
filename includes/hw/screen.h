/*
 * H2 Text-mode Video Driver
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef SCREEN_H
#define SCREEN_H

#define MAX_ROWS 25
#define MAX_COLS 80

// Screen I/O ports
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

#define BG_BLACK   0x00
#define BG_BLUE    0x10
#define BG_GREEN   0x20
#define BG_BROWN   0x30
#define BG_RED     0x40
#define BG_MAGENTA 0x50
#define BG_CYAN    0x60
#define BG_GREY    0x70
#define BG_BOLD    0x80

#define FG_BLACK   0x00
#define FG_BLUE    0x01
#define FG_GREEN   0x02
#define FG_BROWN   0x03
#define FG_RED     0x04
#define FG_MAGENTA 0x05
#define FG_CYAN    0x06
#define FG_GREY    0x07
#define FG_BOLD    0x08

// Text Attributes
#define DEFAULT_TEXT_ATTR (BG_BLACK | FG_GREY)
#define DEFAULT_STATUS_ATTR (BG_MAGENTA | FG_GREY | FG_BOLD)

class ScreenController
{
public:
    static int getOffset(int col, int row);
    static int getOffsetRow(int offset);
    static int getOffsetCol(int offset);

    ScreenController();
    virtual ~ScreenController();

    void putpixel(int x,int y, UInt32 color);

    void clearScreen();
    void clearScreen(const char attr);
    int getCursorOffset();
    void setCursorOffset(int offset);
    char defaultTextAttr(char attr);
    void printBackspace();
    int printChar(char c, int col, int row, char attr);
    char getTextAttr();

private:
    void *framebuffer;
    UInt32 pitch;
    UInt32 width;
    UInt32 height;
    UInt8 bpp;
    UInt8 fbtype;
    char textAttr;
};

// Public kernel API

#endif

