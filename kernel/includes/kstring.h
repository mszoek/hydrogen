/*
 * H2 Kernel string functions
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef _STRING_H
#define _STRING_H

#include <hw/types.h>

char isprint(unsigned char c);
int toupper(int c);
UInt16 hexdigit(UInt8 byte);
int strlen(char *s);
int strcmp(char *a, char *b);
int strncmp(char *a, char *b, int len);
int strcpy(char *dst, char *src);
UInt64 atoi(char *str);
UInt64 atoi16(char *s);
void reverse(char str[]);
void append(char s[], char n);
void backspace(char s[]);
void itoa(UInt64 n, unsigned base, char str[]);
char *strcat(char *dest, const char *src);
char *strtok(char *src, char *del, int *index);

#endif
