#ifndef UTIL_H
#define UTIL_H

#include "types.h"

void memory_copy(char *source, char *dest, int nbytes);
void memory_set(uint8 *dest, uint8 val, uint32 len);
void int_to_ascii(int n, char str[]);
int str_to_int(string ch);
void * malloc(int nbytes);
string str_concat(string data1, string data2, int max_length);
string char_multiply(char ch, int length);
string append(string src, char add);
string itoa(int val, int base);

#endif
