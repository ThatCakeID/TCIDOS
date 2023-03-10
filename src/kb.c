#include "../include/kb.h"
#include "../include/system.h"

string typed_commands[48];
unsigned int typed_index = 0;
uint8 show_log = 0;

string input(const string prompt)
{
    print(prompt);                                              // Print the prompt
    const uint16 prompt_length = (uint16) strlength(prompt);    // For detecting if the cursor index x is at 0
    //char buff;
    string buffstr = (string) malloc(70);
    uint8 i = 0;
    uint8 reading = 1;
    uint8 special_char = 0;                                     // 1 when 0xE0 Occurred
    uint8 capital_mode = 0;                                     // 1 when 0x2A Occurred (Left Shift pressed), And 0 When 0xAA Occurred (Left shift released)
    while(reading)
    {
        print_pos_colored("                                  TCIDOS 0.1                            ", 0, 0, 0b01110000);
        update_time();
        //set_header("Test");
        //print_pos_colored("Forked from IKnow/NIDOS, Modifided by Iyxan23                                   ", 24, 0, 0, 15);

        if(inportb(0x64) & 0x1)
        {
            switch(inportb(0x60))
            {
      /*case 1:
                printch('(char)27);           Escape button
                buffstr[i] = (char)27;
                i++;
                break;*/
        case 2:
            if (capital_mode) {
                printch('!');
                buffstr[i] = '!';
            } else {
                printch('1');
                buffstr[i] = '1';
            }
            i++;
            break;
        case 3:
            if (capital_mode) {
                printch('@');
                buffstr[i] = '@';
            } else {
                printch('2');
                buffstr[i] = '2';
            }
            i++;
            break;
        case 4:
            if (capital_mode) {
                printch('#');
                buffstr[i] = '#';
            } else {
                printch('3');
                buffstr[i] = '3';
            }
            i++;
            break;
        case 5:
            if (capital_mode) {
                printch('$');
                buffstr[i] = '$';
            } else {
                printch('4');
                buffstr[i] = '4';
            }
            i++;
            break;
        case 6:
            if (capital_mode) {
                printch('%');
                buffstr[i] = '%';
            } else {
                printch('5');
                buffstr[i] = '5';
            }
            i++;
            break;
        case 7:
            if (capital_mode) {
                printch('^');
                buffstr[i] = '^';
            } else {
                printch('6');
                buffstr[i] = '6';
            }
            i++;
            break;
        case 8:
            if (capital_mode) {
                printch('&');
                buffstr[i] = '&';
            } else {
                printch('7');
                buffstr[i] = '7';
            }
            i++;
            break;
        case 9:
            if (capital_mode) {
                printch('*');
                buffstr[i] = '*';
            } else {
                printch('8');
                buffstr[i] = '8';
            }
            i++;
            break;
        case 10:
            if (capital_mode) {
                printch('(');
                buffstr[i] = '(';
            } else {
                printch('9');
                buffstr[i] = '9';
            }
            i++;
            break;
        case 11:
            if (capital_mode) {
                printch(')');
                buffstr[i] = ')';
            } else {
                printch('0');
                buffstr[i] = '0';
            }
            i++;
            break;
        case 12:
            if (capital_mode) {
                printch('_');
                buffstr[i] = '_';
            } else {
                printch('-');
                buffstr[i] = '-';
            }
            i++;
            break;
        case 13:
            if (capital_mode) {
                printch('+');
                buffstr[i] = '+';
            } else {
                printch('=');
                buffstr[i] = '=';
            }
            i++;
            break;
        case 14:
                if (i > 0) {
                    printch('\b');
                    i--;
                    if(i < 0)
                    {
                        i = 1;
                    }
                    buffstr[i+1] = 0;
                    buffstr[i] = 0;
                }
                break;
       /* case 15:
                printch('\t');          Tab button
                buffstr[i] = '\t';
                i++;
                break;*/
        case 16:
            printch('q');
            buffstr[i] = 'q';
            i++;
            break;
        case 17:
                printch('w');
                buffstr[i] = 'w';
                i++;
                break;
        case 18:
                printch('e');
                buffstr[i] = 'e';
                i++;
                break;
        case 19:
                printch('r');
                buffstr[i] = 'r';
                i++;
                break;
        case 20:
                printch('t');
                buffstr[i] = 't';
                i++;
                break;
        case 21:
                printch('y');
                buffstr[i] = 'y';
                i++;
                break;
        case 22:
                printch('u');
                buffstr[i] = 'u';
                i++;
                break;
        case 23:
                printch('i');
                buffstr[i] = 'i';
                i++;
                break;
        case 24:
                printch('o');
                buffstr[i] = 'o';
                i++;
                break;
        case 25:
                printch('p');
                buffstr[i] = 'p';
                i++;
                break;
        case 26:
            if (capital_mode) {
                printch('{');
                buffstr[i] = '{';
            } else {
                printch('[');
                buffstr[i] = '[';
            }
            i++;
            break;
        case 27:
            if (capital_mode) {
                printch('}');
                buffstr[i] = '}';
            } else {
                printch(']');
                buffstr[i] = ']';
            }
            i++;
            break;
        case 28:
               // printch('\n');
               // buffstr[i] = '\n';
                  i++;
               reading = 0;
                break;
      /*  case 29:
                printch('q');           Left Control
                buffstr[i] = 'q';
                i++;
                break;*/
        case 30:
                printch('a');
                buffstr[i] = 'a';
                i++;
                break;
        case 31:
                printch('s');
                buffstr[i] = 's';
                i++;
                break;
        case 32:
                printch('d');
                buffstr[i] = 'd';
                i++;
                break;
        case 33:
                printch('f');
                buffstr[i] = 'f';
                i++;
                break;
        case 34:
                printch('g');
                buffstr[i] = 'g';
                i++;
                break;
        case 35:
                printch('h');
                buffstr[i] = 'h';
                i++;
                break;
        case 36:
                printch('j');
                buffstr[i] = 'j';
                i++;
                break;
        case 37:
                printch('k');
                buffstr[i] = 'k';
                i++;
                break;
        case 38:
                printch('l');
                buffstr[i] = 'l';
                i++;
                break;
        case 39:
            if (capital_mode) {
                printch(':');
                buffstr[i] = ':';
            } else {
                printch(';');
                buffstr[i] = ';';
            }
            i++;
            break;
        case 40:
            if (capital_mode) {
                printch('"');
                buffstr[i] = '"';
            } else {
                printch('\'');               //   Single quote (')
                buffstr[i] = '\'';
            }
            i++;
            break;
        case 41:
            if (capital_mode) {
                printch('~');
                buffstr[i] = '~';
            } else {
                printch('`');               // Back tick (`)
                buffstr[i] = '`';
            }
            i++;
            break;
     /* case 42:                                 Left shift
                printch('q');
                buffstr[i] = 'q';
                i++;
                break;
        case 43:                                 \ (< for somekeyboards)
                printch((char)92);
                buffstr[i] = 'q';
                i++;
                break;*/
        case 44:
                printch('z');
                buffstr[i] = 'z';
                i++;
                break;
        case 45:
                printch('x');
                buffstr[i] = 'x';
                i++;
                break;
        case 46:
                printch('c');
                buffstr[i] = 'c';
                i++;
                break;
        case 47:
                printch('v');
                buffstr[i] = 'v';
                i++;
                break;
        case 48:
                printch('b');
                buffstr[i] = 'b';
                i++;
                break;
        case 49:
                printch('n');
                buffstr[i] = 'n';
                i++;
                break;
        case 50:
                printch('m');
                buffstr[i] = 'm';
                i++;
                break;
        case 51:
            if (capital_mode) {
                printch('<');
                buffstr[i] = '<';
            } else {
                printch(',');
                buffstr[i] = ',';
            }
            i++;
            break;
        case 52:
            if (capital_mode) {
                printch('>');
                buffstr[i] = '>';
            } else {
                printch('.');
                buffstr[i] = '.';
            }
            i++;
            break;
        case 53:
            if (capital_mode) {
                printch('?');
                buffstr[i] = '?';
            } else {
                printch('/');
                buffstr[i] = '/';
            }
            i++;
            break;
        case 54:
            if (capital_mode) {
                printch('>');
                buffstr[i] = '>';
            } else {
                printch('.');
                buffstr[i] = '.';
            }
            i++;
            break;
        case 55:
            if (capital_mode) {
                printch('?');
                buffstr[i] = '?';
            } else {
                printch('/');
                buffstr[i] = '/';
            }
            i++;
            break;
      /*case 56:
                printch(' ');           Right shift
                buffstr[i] = ' ';
                i++;
                break;*/
        case 57:
                printch(' ');
                buffstr[i] = ' ';
                i++;
                break;

        // SPECIAL CHARS
        case 0x48:      // Up arrow
            if (special_char) {
                special_char = 0;
                if (typed_index != 0 || !strEql(typed_commands[typed_index - 1], "")) {
                    typed_index--;
                    print_pos("                                                                                ", cursorY, 0);
                    cursorX = (int) prompt_length;
                    print_pos(prompt, cursorY, 0);
                    memory_copy(&typed_commands[typed_index], &buffstr, (int) strlength(typed_commands[typed_index]));
                    print(typed_commands[typed_index]);
                    i = strlength(typed_commands[typed_index]);
                }
            }
            break;

        case 0x50:      // Down arrow
            if (special_char) {
                special_char = 0;
                if (typed_index != 47 || !strEql(typed_commands[typed_index + 1], "")) {
                    typed_index++;
                    print_pos("                                                                                ", cursorY, 0);
                    cursorX = (int) prompt_length;
                    print_pos(prompt, cursorY, 0);
                    memory_copy(&typed_commands[typed_index], &buffstr, (int) strlength(typed_commands[typed_index]));
                    print(typed_commands[typed_index]);
                    i = strlength(typed_commands[typed_index]);
                }
            }
            break;

        case 0x2A:
            // Left shift Pressed
            capital_mode = 1;
            break;

        case 0xAA:
            // Left shift released
            capital_mode = 0;
            break;

        case 0xE0:
            // SPECIAL CHARACTER
            special_char = 1;
            break;

        case 0xFF:
            print_colored("\n\nKEYBOARD ERROR\n", 0x4, 0x0);
            break;
            }
        }
    }
    //print(buffstr); // DEBUG
    buffstr[i-1] = 0;
    return buffstr;
}

/*
char get_char() {
    char buffstr[2] = {' ', ' '};
    uint8 i = 0;
    uint8 capital_mode = 0;                                     // 1 when 0x2A Occurred (Left Shift pressed), And 0 When 0xAA Occurred (Left shift released)
    update_time();
    //set_header("Test");
    //print_pos_colored("Forked from IKnow/NIDOS, Modifided by Iyxan23                                   ", 24, 0, 0, 15);

    if(inportb(0x64) & 0x1)
    {
        switch(inportb(0x60))
        {
  /*case 1:
            printch('(char)27);           Escape button
            buffstr[i] = (char)27;
            i++;
            break;
    case 2:
        if (capital_mode) {
            buffstr[i] = '!';
        } else {
            buffstr[i] = '1';
        }
        i++;
        break;
    case 3:
        if (capital_mode) {
            buffstr[i] = '@';
        } else {
            buffstr[i] = '2';
        }
        i++;
        break;
    case 4:
        if (capital_mode) {
            buffstr[i] = '#';
        } else {
            buffstr[i] = '3';
        }
        i++;
        break;
    case 5:
        if (capital_mode) {
            buffstr[i] = '$';
        } else {
            buffstr[i] = '4';
        }
        i++;
        break;
    case 6:
        if (capital_mode) {
            buffstr[i] = '%';
        } else {
            buffstr[i] = '5';
        }
        i++;
        break;
    case 7:
        if (capital_mode) {
            buffstr[i] = '^';
        } else {
            buffstr[i] = '6';
        }
        i++;
        break;
    case 8:
        if (capital_mode) {
            buffstr[i] = '&';
        } else {
            buffstr[i] = '7';
        }
        i++;
        break;
    case 9:
        if (capital_mode) {
            buffstr[i] = '*';
        } else {
            buffstr[i] = '8';
        }
        i++;
        break;
    case 10:
        if (capital_mode) {
            buffstr[i] = '(';
        } else {
            buffstr[i] = '9';
        }
        i++;
        break;
    case 11:
        if (capital_mode) {
            buffstr[i] = ')';
        } else {
            buffstr[i] = '0';
        }
        i++;
        break;
    case 12:
            buffstr[i] = '-';
            i++;
            break;
    case 13:
            buffstr[i] = '=';
            i++;
            break;
    case 14:
            buffstr[i] = '\b';
            break;
   /* case 15:
            printch('\t');          Tab button
            buffstr[i] = '\t';
            i++;
            break;
    case 16:
            buffstr[i] = 'q';
            i++;
            break;
    case 17:
            buffstr[i] = 'w';
            i++;
            break;
    case 18:
            buffstr[i] = 'e';
            i++;
            break;
    case 19:
            buffstr[i] = 'r';
            i++;
            break;
    case 20:
            buffstr[i] = 't';
            i++;
            break;
    case 21:
            buffstr[i] = 'y';
            i++;
            break;
    case 22:
            buffstr[i] = 'u';
            i++;
            break;
    case 23:
            buffstr[i] = 'i';
            i++;
            break;
    case 24:
            buffstr[i] = 'o';
            i++;
            break;
    case 25:
            buffstr[i] = 'p';
            i++;
            break;
    case 26:
            buffstr[i] = '[';
            i++;
            break;
    case 27:
            buffstr[i] = ']';
            i++;
            break;
    case 28:
           // printch('\n');
            buffstr[i] = '\n';
            break;
  /*  case 29:
            printch('q');           Left Control
            buffstr[i] = 'q';
            i++;
            break;
    case 30:
            buffstr[i] = 'a';
            i++;
            break;
    case 31:
            buffstr[i] = 's';
            i++;
            break;
    case 32:
            buffstr[i] = 'd';
            i++;
            break;
    case 33:
            buffstr[i] = 'f';
            i++;
            break;
    case 34:
            buffstr[i] = 'g';
            i++;
            break;
    case 35:
            buffstr[i] = 'h';
            i++;
            break;
    case 36:
            buffstr[i] = 'j';
            i++;
            break;
    case 37:
            buffstr[i] = 'k';
            i++;
            break;
    case 38:
            buffstr[i] = 'l';
            i++;
            break;
    case 39:
            buffstr[i] = ';';
            i++;
            break;
    case 40:
            buffstr[i] = '\'';
            i++;
            break;
    case 41:
            buffstr[i] = '`';
            i++;
            break;
 /* case 42:                                 Left shift
            printch('q');
            buffstr[i] = 'q';
            i++;
            break;
    case 43:                                 \ (< for somekeyboards)
            printch((char)92);
            buffstr[i] = 'q';
            i++;
            break;
    case 44:
            buffstr[i] = 'z';
            i++;
            break;
    case 45:
            buffstr[i] = 'x';
            i++;
            break;
    case 46:
            buffstr[i] = 'c';
            i++;
            break;
    case 47:
            buffstr[i] = 'v';
            i++;
            break;
    case 48:;
            buffstr[i] = 'b';
            i++;
            break;
    case 49:
            buffstr[i] = 'n';
            i++;
            break;
    case 50:
            buffstr[i] = 'm';
            i++;
            break;
    case 51:
            buffstr[i] = ',';
            i++;
            break;
    case 52:
            buffstr[i] = '.';
            i++;
            break;
    case 53:
            buffstr[i] = '/';
            i++;
            break;
    case 54:
            buffstr[i] = '.';
            i++;
            break;
    case 55:
            buffstr[i] = '/';
            i++;
            break;
  /*case 56:
            printch(' ');           Right shift
            buffstr[i] = ' ';
            i++;
            break;
    case 57:
            buffstr[i] = ' ';
            i++;
            break;

    case 0x2A:
        // Left shift Pressed
        capital_mode = 1;
        break;

    case 0xAA:
        // Left shift released
        capital_mode = 0;
        break;

    case 0xFF:
        print_colored("\n\nKEYBOARD ERROR\n", 0x4, 0x0);
        asm("hlt");
        break;

    return buffstr[i];
        }
        return buffstr[i];
    }
}
*/

uint8 is_pressed(char key) {
    uint8 i = 0;
    uint8 capital_mode = 0;
    char buffstr[2] = {' ', ' '};
    if(inportb(0x64) & 0x1) {
        switch(inportb(0x60)) {
  /*case 1:
            printch('(char)27);           Escape button
            buffstr[i] = (char)27;
            i++;
            break;*/
    case 2:
        buffstr[i] = '1';
        i++;
        break;
    case 3:
        buffstr[i] = '2';
        i++;
        break;
    case 4:
        if (capital_mode) {
            buffstr[i] = '#';
        } else {
            buffstr[i] = '3';
        }
        i++;
        break;
    case 5:
        if (capital_mode) {
            buffstr[i] = '$';
        } else {
            buffstr[i] = '4';
        }
        i++;
        break;
    case 6:
        if (capital_mode) {
            buffstr[i] = '%';
        } else {
            buffstr[i] = '5';
        }
        i++;
        break;
    case 7:
        if (capital_mode) {
            buffstr[i] = '^';
        } else {
            buffstr[i] = '6';
        }
        i++;
        break;
    case 8:
        if (capital_mode) {
            buffstr[i] = '&';
        } else {
            buffstr[i] = '7';
        }
        i++;
        break;
    case 9:
        if (capital_mode) {
            buffstr[i] = '*';
        } else {
            buffstr[i] = '8';
        }
        i++;
        break;
    case 10:
        if (capital_mode) {
            buffstr[i] = '(';
        } else {
            buffstr[i] = '9';
        }
        i++;
        break;
    case 11:
        if (capital_mode) {
            buffstr[i] = ')';
        } else {
            buffstr[i] = '0';
        }
        i++;
        break;
    case 12:
            buffstr[i] = '-';
            i++;
            break;
    case 13:
            buffstr[i] = '=';
            i++;
            break;
    case 14:
            buffstr[i] = '\b';
            break;
   /* case 15:
            printch('\t');          Tab button
            buffstr[i] = '\t';
            i++;
            break;*/
    case 16:
            buffstr[i] = 'q';
            i++;
            break;
    case 17:
            buffstr[i] = 'w';
            i++;
            break;
    case 18:
            buffstr[i] = 'e';
            i++;
            break;
    case 19:
            buffstr[i] = 'r';
            i++;
            break;
    case 20:
            buffstr[i] = 't';
            i++;
            break;
    case 21:
            buffstr[i] = 'y';
            i++;
            break;
    case 22:
            buffstr[i] = 'u';
            i++;
            break;
    case 23:
            buffstr[i] = 'i';
            i++;
            break;
    case 24:
            buffstr[i] = 'o';
            i++;
            break;
    case 25:
            buffstr[i] = 'p';
            i++;
            break;
    case 26:
            buffstr[i] = '[';
            i++;
            break;
    case 27:
            buffstr[i] = ']';
            i++;
            break;
    case 28:
           // printch('\n');
            buffstr[i] = '\n';
            break;
  /*  case 29:
            printch('q');           Left Control
            buffstr[i] = 'q';
            i++;
            break;*/
    case 30:
            buffstr[i] = 'a';
            i++;
            break;
    case 31:
            buffstr[i] = 's';
            i++;
            break;
    case 32:
            buffstr[i] = 'd';
            i++;
            break;
    case 33:
            buffstr[i] = 'f';
            i++;
            break;
    case 34:
            buffstr[i] = 'g';
            i++;
            break;
    case 35:
            buffstr[i] = 'h';
            i++;
            break;
    case 36:
            buffstr[i] = 'j';
            i++;
            break;
    case 37:
            buffstr[i] = 'k';
            i++;
            break;
    case 38:
            buffstr[i] = 'l';
            i++;
            break;
    case 39:
            buffstr[i] = ';';
            i++;
            break;
    case 40:
            buffstr[i] = '\'';
            i++;
            break;
    case 41:
            buffstr[i] = '`';
            i++;
            break;
 /* case 42:                                 Left shift
            printch('q');
            buffstr[i] = 'q';
            i++;
            break;*/
    case 43:
            buffstr[i] = 'q';
            i++;
            break;
    case 44:
            buffstr[i] = 'z';
            i++;
            break;
    case 45:
            buffstr[i] = 'x';
            i++;
            break;
    case 46:
            buffstr[i] = 'c';
            i++;
            break;
    case 47:
            buffstr[i] = 'v';
            i++;
            break;
    case 48:;
            buffstr[i] = 'b';
            i++;
            break;
    case 49:
            buffstr[i] = 'n';
            i++;
            break;
    case 50:
            buffstr[i] = 'm';
            i++;
            break;
    case 51:
            buffstr[i] = ',';
            i++;
            break;
    case 52:
            buffstr[i] = '.';
            i++;
            break;
    case 53:
            buffstr[i] = '/';
            i++;
            break;
    case 54:
            buffstr[i] = '.';
            i++;
            break;
    case 55:
            buffstr[i] = '/';
            i++;
            break;
  /*case 56:
            printch(' ');           Right shift
            buffstr[i] = ' ';
            i++;
            break; */
    case 57:
            buffstr[i] = ' ';
            i++;
            break;
        }
        return buffstr[i - 1] == key ? 1 : 0;
    }
    return 0;
}
