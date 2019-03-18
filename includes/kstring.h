/*
 * H2 Kernel string functions
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef _STRING_H
#define _STRING_H

int strlen(char *s);
int strcmp(char *a, char *b);
int strcpy(char *dst, char *src);
int atoi(char *str);
void reverse(char str[]);
void append(char s[], char n);
void backspace(char s[]);
void itoa(unsigned n, unsigned base, char str[]);
int atoi(char *str);

#endif
