#include <syscall.h>

void _start(void)
{
  char *s = "Hello from userspace!\n";
  char *retcode = "Got -2 return\n";
  int r = _syscall(SYSCALL_PRINTF, (UInt64)s, 0, 0, 0, 0);
  if(r == -2)
    _syscall(SYSCALL_PRINTF, (UInt64)retcode, 0, 0, 0, 0);
  _syscall(SYSCALL_EXIT, r, 0, 0, 0, 0);
}
