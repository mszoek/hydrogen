/*
 * H2 Kernel
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <kernel.h>
#include <kstdio.h>
#include <hw/screen.h>
#include <kstring.h>

void kprint(const char *message)
{
    ScreenController *screen = (ScreenController *)g_controllers[CTRL_SCREEN];
    if(!screen) return;

    int i = 0;
    while(message[i] != 0)
        screen->printChar(message[i++]);
}

int kprintf(const char* str, ...)
{
    ScreenController *screen = (ScreenController *)g_controllers[CTRL_SCREEN];
    if(!screen || !str) return 0;

    int i;
    char buf[16];
	int width = 0;

    va_list	args;
    va_start(args, str);

    for(i = 0; i < strlen((char *)str); i++)
    {
		width = 0;
        switch(str[i])
        {
			case '%':
				if(str[i+1] >= '1' && str[i+1] <= '9')
				{
					width = str[i+1] - '0';
					++i;
				}
				switch (str[i+1])
                {
					case 'c':
                    {
						char c = va_arg(args, int);
						screen->printChar(c);
						i++;
						break;
					}

					case 's':
                    {
						UInt64 c = (int)va_arg(args, char *);
						kprint((char *)c);
						i++;
						break;
					}

					case 'd':
					case 'i':
                    {
						int c = va_arg(args, int);
						itoa(c, 10, buf);
						int q = strlen(buf);
						for(int c = 0; c < width-q; ++c)
							screen->printChar('0');
						kprint(buf);
						i++;
						break;
					}

					case 'X':
					case 'x':
                    {
						int c = va_arg(args, int);
						itoa(c, 16, buf);
						int q = strlen(buf);
						for(int c = 0; c < width-q; ++c)
							screen->printChar('0');
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
				screen->printChar(str[i]);
				break;
		}
	}

	va_end(args);
	return i;
}

void printdata(UInt8* nodedata, int len)
{
  char ascii[20];
  int i,j=0;

  for(i=0,j=0; i<len; ++i)
  {
      if(j==0)
        kprintf("%8x ",i);
      kprintf("%2x ", nodedata[i]);
      ascii[j++] = isprint(nodedata[i]) ? nodedata[i] : '.';
      if(j > 15)
      {
        kprintf("%s\n",ascii);
        j=0;
      }
  }
}
