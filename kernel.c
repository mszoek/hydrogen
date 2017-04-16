void kernel_main(void) {
  char *msg_startup = "H2OS Kernel v0.0.1 Started!";
  char *vidmem = (char*)0xb8000; // Start of video memory
  unsigned int i = 0;
  unsigned int j = 0;
  char *p;

  // Clear the screen (80x25)
  while (j < 80 * 25 * 2)
  {
    vidmem[j] = 'X';
    // Set white on black text
    vidmem[j+1] = 0xf4;
    j = j + 2;
  }

  p = msg_startup;
  while (*p != '\0')
  {
    // write the char to screen
    vidmem[i] = *p;
    ++p;
    // white on black again
    vidmem[i+1] = 0x0f;
    i = i + 2;
  }
  return;
}
