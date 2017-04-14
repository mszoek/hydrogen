asm(".code16gcc");
void kernel_main(void) {
  const char *msg_startup = "H2OS Kernel v0.0.1 Started!";
  char *vidmem = (char*)0xb8000; // Start of video memory
  unsigned int i = 0;
  unsigned int j = 0;

  // Clear the screen (80x25)
  while (j < 80 * 25 * 2)
  {
    vidmem[j] = ' ';
    // Set white on black text
    vidmem[j+1] = 0x0f;
    j = j + 2;
  }
  // reset j
  j = 0;

  while (msg_startup[j] != '\0')
  {
    // write the char to screen
    vidmem[i] = msg_startup[j];
    // white on black again
    vidmem[i+1] = 0x0f;
    j++;
    i = i + 2;
  }
  return;
}
