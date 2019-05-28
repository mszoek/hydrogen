#include <syscall.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
  const char *s = "kernel.bin";
  struct stat stbuf;

  stat(s, &stbuf);
  printf("        %d %d    %d    %lu %s\n", stbuf.st_uid, stbuf.st_gid, stbuf.st_size, stbuf.st_mtime, s);
  exit(0);
}
