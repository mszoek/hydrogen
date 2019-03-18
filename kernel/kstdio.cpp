#include <kernel.h>
#include <kstdio.h>
#include <hw/screen.h>
#include <kstring.h>

void kprintAt(const char *message, int col, int row, char attr)
{
    ScreenController *screen = (ScreenController *)g_controllers[CTRL_SCREEN];
    if(!screen)
        return;

    int offset;
    if (col >= 0 && row >= 0)
    {
        offset = ScreenController::getOffset(col, row);
    } else {
        offset = screen->getCursorOffset();
        row = ScreenController::getOffsetRow(offset);
        col = ScreenController::getOffsetCol(offset);
    }

    int i = 0;
    while(message[i] != 0)
    {
        offset = screen->printChar(message[i++], col, row, attr);
        row = ScreenController::getOffsetRow(offset);
        col = ScreenController::getOffsetCol(offset);
    }
}

void kprint(const char *message)
{
    ScreenController *screen = (ScreenController *)g_controllers[CTRL_SCREEN];
    if(!screen) return;
    kprintAt(message, -1, -1, screen->getTextAttr());
}


int kprintf(const char* str, ...)
{
    ScreenController *screen = (ScreenController *)g_controllers[CTRL_SCREEN];
    if(!screen || !str) return 0;

    int i;
    char buf[16];

    va_list	args;
    va_start(args, str);

    for(i = 0; i < strlen((char *)str); i++)
    {
        switch(str[i])
        {
			case '%':
				switch (str[i+1])
                {
					case 'c':
                    {
						char c = va_arg(args, int);
						screen->printChar(c, -1, -1, screen->getTextAttr());
						i++;
						break;
					}

					case 's':
                    {
						UInt32 c = (int)va_arg(args, char *);
						kprint((char *)c);
						i++;
						break;
					}

					case 'd':
					case 'i':
                    {
						int c = va_arg(args, int);
						itoa(c, 10, buf);
						kprint(buf);
						i++;
						break;
					}

					case 'X':
					case 'x':
                    {
						int c = va_arg(args, int);
						itoa(c, 16, buf);
                        kprint(buf);
						i++;
						break;
					}

					default:
						va_end(args);
						return 1;
				}
				break;

			default:
				screen->printChar(str[i], -1, -1, screen->getTextAttr());
				break;
		}
	}

	va_end(args);
	return i;
}
