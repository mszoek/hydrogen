/*
 * H2 Kernel string functions
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <hw/types.h>
#include <kmem.h>
#include <kstdio.h>

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

int strncmp(char *a, char *b, int len)
{
  int pos = 0;
  char *p = a;
  char *q = b;
  while(*p && *q && pos < len)
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
    ++pos;
  }
  return 0;
}

/* Turn a byte into two hex ASCII digits */
UInt16 hexdigit(UInt8 byte)
{
  UInt16 result = 0;

  UInt8 nibble = byte & 0xF;
  result = (nibble <= 9 ? nibble + '0' : nibble - 10 + 'A') << 8;
  nibble = byte >> 4;
  result |= (nibble <= 9 ? nibble + '0' : nibble - 10 + 'A');

  return result;
}

int strcpy(char *dst, char *src)
{
  char *p=src;
  char *q=dst;
  while(*p != 0)
  {
    *q = *p;
    ++p;
    ++q;
  }
  *q = 0;
  return (q - dst);
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

// TODO: implement strstr(), strchr()

char *strcat(char *dest, const char *src)
{
  if(!dest || !src) return 0;

  UInt32 i, j;
  for(i = 0; dest[i] != '\0'; ++i);
  for(j = 0; src[j] != '\0'; ++i)
    dest[i+j] = src[j];
  dest[i+j] = '\0';
  return dest;
}

/* Thread safe version - pass in a pointer to index var, which must hold 0
 * Destroys the original string in 'src' so make a copy if you need it!
 */
char *strtok(char *src, char *del, int *index)
{
  if(!src || !del || src[*index] == '\0') return 0;

  // find first delimiter in src after index
  int i = *index, j;
  char *tok = &src[*index];

  while(src[i] != '\0')
  {
    j = 0;
    while(del[j] != '\0')
    {
      if(src[i] == del[j])
      {
        src[i] = 0; // terminate string here
        *index = i + 1; // save next start position
        return tok;
      }
      ++j;
    }
    ++i;
  }

  *index = i;
  return tok;
}
