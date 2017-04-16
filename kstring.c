/* H2OS Kernel string handling
 * Zoe Knox 2017
 */

int strlen(char *s)
{
  char *p=s;
  while(*p != 0) ++p;
  return p-s;
}
