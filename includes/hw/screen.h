/*
 * H2 Text-mode Video Driver
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <fonts/font.h>

class ScreenController
{
public:
    ScreenController();
    virtual ~ScreenController();

    void putpixel(int x,int y, UInt32 color);

    void clearScreen();
    void printBackspace();
    void printChar(UInt8 c);
    UInt32 getColor();
    UInt32 getBackColor();
    UInt32 getX();
    UInt32 getY();
    void setXY(UInt32 x, UInt32 y);
    void setXYChars(UInt32 x, UInt32 y);
    void setColor(UInt32 c);
    void setBackColor(UInt32 c);
    void setFont(int f);
    void drawLogo();

private:
    void *framebuffer;
    UInt32 pitch;
    UInt32 width;
    UInt32 height;
    UInt8 bpp;
    UInt8 fbtype;
    UInt32 xpos;
    UInt32 ypos;
    UInt32 color;
    UInt32 bgcolor;
    int fontNumber; // current font number
    int fontWidth;
    int fontHeight;
    int fontbpp;
    const fontGlyph *glyphDsc;
    const UInt8 *glyphBitmap;
};

#endif

