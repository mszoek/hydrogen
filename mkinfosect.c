#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
  int fd;
  char *fname = "/kernel";
  unsigned char data[] = { 'H', '2', 'O', 'S', 3, 0, 24, 0 };

  fd = open("infosect.bin", O_CREAT|O_RDWR);
  write(fd, data, 8);
  write(fd, fname, strlen(fname)+1); // include terminating null
  close(fd);
}
