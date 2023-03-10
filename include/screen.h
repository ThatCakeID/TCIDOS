#ifndef SCREEN_H
#define SCREEN_H
#include "system.h"
#include "string.h"
int cursorX , cursorY;
const uint8 sw ,sh ,sd ;
                                                    //We define the screen width, height, and depth.
void clearLine(uint8 from,uint8 to);

void updateCursor();

void clearScreen();

void scrollUp(uint8 lineNumber);

void newLineCheck();

void printch(char c);

void print (string ch);
void set_screen_color_from_color_code(int color_code);
void set_screen_color(int text_color,int bg_color);
void print_colored(string ch,int text_color,int bg_color);
int int_color_to_hex(int fg, int bg);
void write_pos(char ch, int y, int x);
void write_pos_colored(char ch, int y, int x, int colorcode);
void print_pos(string data, int y, int x);
void print_pos_colored(string data, int y, int x, int colorcode);
void set_header(string text);


#endif
