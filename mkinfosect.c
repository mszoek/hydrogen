#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
  int fd, pos=0;
  unsigned char null=0;
  char *fname = "/kernel";
  unsigned char data[] = { 'H', '2', 'O', 'S', 3, 0, 2, 0 };

  fd = open("infosect.bin", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
  pos += write(fd, data, 8);
  pos += write(fd, fname, strlen(fname)+1); // include terminating null

  // pad to sector size
  for(; pos < 512; ++pos)
  {
      write(fd, &null, 1);
  }

  close(fd);
}
