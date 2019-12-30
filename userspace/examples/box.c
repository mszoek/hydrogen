#include <syscall.h>

struct fbInfo
{
    void *fb;
    UInt32 pitch;
    UInt32 width;
    UInt32 height;
    UInt8 bpp;
} fbi;
void putpixel(int x, int y, unsigned int color);

int main(int argc, char **argv)
{
    int r = _syscall(SYSCALL_FBINFO, (UInt64)&fbi, 0, 0, 0, 0);
    printf("r=%d fb at %lx %dx%d\n",r,fbi.fb,fbi.width,fbi.height);
    int x1 = 200, x2 = 1720, y1 = 400, y2 = 800;

    int color = 0x407000;
    while(y2 > y1)
    {
        for(int x = x1; x < x2; ++x)
        {
            putpixel(x, y1, color);
            putpixel(x, y2, color);
        }

        for(int y = y1; y < y2; ++y)
        {
            putpixel(x1, y, color);
            putpixel(x2, y, color);
        }

        x1 += 4;
        x2 -= 4;
        y1 += 4;
        y2 -= 4;
        color += 0x0408;
    }

    return 0;
}

void putpixel(int x, int y, unsigned int color)
{
    int bytesPerPixel = fbi.bpp/8;
    void *where = (void *)((unsigned long long)fbi.fb + x*bytesPerPixel + y*fbi.pitch);
    *(unsigned int *)where = color;
}

