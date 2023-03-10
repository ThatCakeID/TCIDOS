#include "../include/util.h"

void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);             //    dest[i] = source[i]
    }
}

void memory_set(uint8 *dest, uint8 val, uint32 len) {
    uint8 *temp = (uint8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    return str;
}

char* itoa(int val, int base) {

    static char buf[32] = {0};

    int i = 30;

    for(; val && i ; --i, val /= base)

        buf[i] = "0123456789abcdef"[val % base];

    return &buf[i+1];
}

int str_to_int(string ch)
{
	int n = 0;
	int p = 1;
	int strlen = strlength(ch);
	int i;
	for (i = strlen-1;i>=0;i--)
	{
		n += ((int)(ch[i] - '0')) * p;
		p *= 10;
	}
	return n;
}

string str_concat(string data1, string data2, int max_length) {  // Currently not working (duh)
    int data1_length = strlength(data1);
    int data2_length = strlength(data2);
    int a;
    string buffer = (string) malloc(max_length); // Allocate buffer

    // Put the data1 to the buffer
    for(a;a < data1_length;a++) {
        buffer[a] = data1[a];
    }
    a = data1_length - 1;

    // Add the data2 to the buffer (concat)
    for(a; a < data2_length;a++) {
        buffer[a] = data2[a];
    }
    return buffer;
}

string char_multiply(char ch, int length) {  // Currently not working (duh)
    string result;
    while(strlength(result) <= length) {
        string a = malloc(1);
        a[0] = ch;
        result = str_concat(result, a, strlength(result) + 1);
    }
    return result;
}

string append(string src, char add) {
    string buffer = (string) malloc(sizeof(src) + 1);
    uint8 index = 0;
    while (index > sizeof(src)) {
        buffer[index] = src[index];
        index++;
    }
    buffer[index + 1] = add;
    return buffer;
}

void * malloc(int nbytes)
{
	char variable[nbytes];
	return &variable;
}
