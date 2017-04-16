// H2OS Kernel! CodeGrlz rule.

#include "drivers/video_ports.h"
#include "drivers/screen.h"
#include "kstring.h"
#include "kmem.h"

void kernel_main(void) {
  char msg_startup[] = "H2OS Kernel v0.0.1 Started!";
  clear_screen();
  kprint(msg_startup);

  while(1) ;
}

void _start(void)
{
  kernel_main();
}
