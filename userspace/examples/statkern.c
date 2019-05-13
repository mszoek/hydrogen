#include <syscall.h>
#include <stdio.h>
#include <stat.h>

void _start(void)
{
  const char *s = "kernel.bin";
  struct stat stbuf;

  int r = _syscall(SYSCALL_STAT, (UInt64)s, (UInt64)&stbuf, 0, 0, 0);
  printf("        %d %d    %d    %lu %s\n", stbuf.st_uid, stbuf.st_gid, stbuf.st_size, stbuf.st_mtime, s);
  exit(0);
  // _syscall(SYSCALL_WRITE, (UInt64)buf, 0, 0, 0, 0);
  // _syscall(SYSCALL_EXIT, r, 0, 0, 0, 0);
}
