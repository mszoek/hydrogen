#include <syscall.h>

int main(int argc, char **argv)
{
  char *s = "Hello from userspace!\n";
  int r = _syscall(SYSCALL_WRITE, (UInt64)s, 0, 0, 0, 0);
  _syscall(SYSCALL_EXIT, r, 0, 0, 0, 0);
}
