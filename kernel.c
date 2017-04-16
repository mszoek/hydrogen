// H2OS Kernel! CodeGrlz rule.

#define TEXTCOLOR 0x17  // white on blue

void kernel_main(void)
{
  char msg_startup[] = "H2OS Kernel v0.0.1 Started!", *p=msg_startup;
  char *vidmem = (char*)0xb8000; // Start of video memory
  unsigned int j = 0;

  // Clear the screen (80x25)
  while (j < 80 * 25 * 2)
  {
    vidmem[j++] = ' ';
    vidmem[j++] = TEXTCOLOR;
  }

  j=0;
  do
  {
    // write the char to screen
    vidmem[j++] = *p++;
    vidmem[j++] = TEXTCOLOR;
  }
  while (*p != 0);

  while(1) ;
}

void _start(void)
{
  kernel_main();
}
