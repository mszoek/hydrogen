#include <syscall.h>

void _start(void)
{
  char *s = "Hello from userspace!\n";
  _syscall(SYSCALL_PRINTF, (UInt64)s, 0, 0, 0, 0);
  _syscall(SYSCALL_EXIT, 0, 0, 0, 0, 0);
}
