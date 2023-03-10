#ifndef KB_H
#define KB_H
#include "screen.h"
#include "util.h"

string typed_commands[48];
unsigned int typed_index;
uint8 debug_mode;
string input();
char get_char();

#endif
