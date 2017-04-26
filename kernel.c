// H2OS Kernel! CodeGrlz rule.

#include "includes/isr.h"
#include "includes/idt.h"
#include "drivers/video_ports.h"
#include "drivers/screen.h"
#include "kstring.h"
#include "kmem.h"

void kernel_main(void)
{
  char msg_startup[] = "H2OS Kernel v0.0.1 Started!\n";
  clear_screen();
  kprint(msg_startup);

  char the_char[] = "A\n";
  int x = 0;

  char reversed[] = "Hello World!";
  reverse(reversed);
  kprint(reversed);

  // for (int i = 0; i < 50; i++)
  // {
  //   kprint(the_char);
  //   the_char[0]++;
  //   do { x++; } while(x < 150000000);
  //   x = 0;
  //   if (the_char[0] > 'Z') { the_char[0] = 'A'; }
  // }

  isr_install();
  /* Test the interrupts */
  //asm volatile("int $2");
  //asm volatile("int $3");

  while(1) ;
}

void _start(void) {
  kernel_main();
}
