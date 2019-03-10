/* H2OS Kernel string handling
 * Zoe Knox 2017-2019
 */

int strlen(char *s)
{
  char *p=s;
  while(*p != 0) ++p;
  return p-s;
}

int strcmp(char *a, char *b)
{
  if(strlen(a) != strlen(b)) return 1;
  char *p = a;
  char *q = b;
  while(*p && *q)
  {
    if(*p < *q)
    {
      return -1;
    }
    else if(*p > *q)
    {
      return 1;
    }
    ++p;
    ++q;
  }
  return 0;
}

int atoi(char *str)
{
    int res = 0; // Initialize result

    // Iterate through all characters of input string and
    // update result
    for (int i = 0; str[i] != '\0'; ++i)
        res = res*10 + str[i] - '0';

    // return result.
    return res;
}

/* A utility function to reverse a string  */
void reverse(char str[])
{
    int c, i, j;
    for (i = 0, j = strlen(str)-1; i < j; i++, j--)
    {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

void append(char s[], char n)
{
	int len = strlen(s);
	s[len] = n;
	s[len+1] = '\0';
}

void backspace(char s[])
{
	int len = strlen(s);
	s[len-1] = '\0';
}

void itoa(unsigned n, unsigned base, char str[])
{
  int i = 0;
  char basechars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

  if(base > 16 || n == 0)
  {
    str[0] = '0';
    str[1] = 0;
    return;
  }

  do
  {
    str[i++] = basechars[n % base];
  } while ((n /= base) > 0);

  str[i] = '\0';
  reverse(str);
}
