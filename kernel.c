// H2OS Kernel! CodeGrlz rule.

#include "drivers/video_ports.h"
#define TEXTCOLOR 0x0f  // white on black

void kernel_main(void) {

  // Define variables
  char msg_startup[] = "H2OS Kernel v0.0.1 Started!", *p=msg_startup;
  char *vidmem = (char*)0xb8000; // Start of video memory
  unsigned int j = 0;

  // Clear the screen (80x25)
  while (j < 80 * 25 * 2)
  {
    vidmem[j++] = ' ';
    vidmem[j++] = TEXTCOLOR;
  }

  // Set cursor position
  port_byte_out(0x3d4, 14);
  int cursor_pos = port_byte_in(0x3d5);
  cursor_pos = cursor_pos << 8;
  port_byte_out(0x3d4, 15);
  cursor_pos += port_byte_in(0x3d5);

  // reset j and draw the text

  j=cursor_pos*2;
  do
  {
    // write the char to screen
    vidmem[j++] = *p++;
    vidmem[j++] = TEXTCOLOR;
  }
  while (*p != 0);

  while(1) ;
}
