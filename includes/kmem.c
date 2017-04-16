/* H2OS Kernel memory management
 * Zoe Knox 2017
 */

void memcpy(char *src, char *dst, unsigned int len)
{
  int i;
  for(i=0; i<len; ++i)
  {
    *(dst+i) = *(src+i);
  }
}

void memset(char *dst, char val, int len)
{
  char *tmp=dst;
  for(;len > 0; --len)
  {
    *tmp++ = val;
  }
}
