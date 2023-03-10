#include "../include/shell.h"
#include "../include/system.h"

const int BUILD_NUMBER = 5;

// !! IMPORTANT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ! SHELL INI CUMA BUAT DEMO, NANTI GW BIKIN  !
// ! SHELL SENDIRI.                            !
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int stack_[512];
int codeindex = 0;
string codedata[10][300][50];  // 10: How much codedata, 100: How much line per codedata

void launch_shell(int n)
{
	string ch = (string) malloc(200); // util.h
	int counter = 0;
	do
	{
        //print_pos_colored("                                  TCIDOS 0.1                                    ", 0, 0, 0, 15);
        //set_header("Test");
        //print_pos_colored("Forked from IKnow/NIDOS, Modifided by Iyxan23                                   ", 24, 0, 0, 15);
        if (n != 0) {
            print_pos_colored("RECURSIVE-", cursorY, 68, 0b01110000);
            print_pos_colored(itoa(n, 10), cursorY, 78, 0b01110000);
        }
        //print_pos_colored("                                  TCIDOS 0.1                                    ", 0, 0, 0, 15);
        //set_header("Test");
        //print_pos_colored("Forked from IKnow/NIDOS, Modifided by Iyxan23/NurIhsan                          ", 24, 0, 0, 15);
        ch = input("0.1-TCIDOS > ");
        ToLower(&ch);
        typed_index++;
        memory_copy(&ch, &typed_commands[typed_index - 1], (int) strlength(ch));
        if(strEql(ch,"cmd"))
        {
            print("\nYou are allready in cmd. A new recursive shell is opened\n");
            launch_shell(n+1);
        }
        else if(strEql(ch,"clear"))
        {
            clearScreen();
            print("\n");
        }
        else if(strEql(ch,"sum"))
        {
            sum();
        }
        else if(strEql(ch,"exit"))
        {
            print("\nKilling recursive cmd index ");
            print(itoa(n, 10));
            print("\n\n");
            break;
        }
        else if(strEql(ch,"echo"))
        {
            echo();
        }
        else if(strEql(ch,"sort"))
        {
            sort();
        }
        else if(strEql(ch,"fibonaci"))
        {
            fibonaci();
        }
        else if(strEql(ch,"gcd"))
        {
            gcd();
        }
        else if(strEql(ch,"help"))
        {
            help();
        }
        else if(strEql(ch,"color"))
        {
            set_background_color();
        }
        else if(strEql(ch,"multiply"))
        {
            multiply();
        }
        else if(strEql(ch, "halt"))
        {
            clearScreen();
            print("\nCPU Halted");
            asm("hlt");
        }
        else if(strEql(ch, "about") || strEql(ch, "info"))
        {
            about();
        }
        else if(strEql(ch, "set"))
        {
            set();
        }
        else if(strEql(ch, "read"))
        {
            read();
        }
        else if(strEql(ch, "get"))
        {
            get();
        }
        else if(strEql(ch, "readlong"))
        {
            readlong();
        }
        else if(strEql(ch, "time"))
        {
            get_time();
        }
        else if(strEql(ch, "cpuid"))
        {
            print("\n");
            detect_cpu();
        }
        else if(strEql(ch, "code"))
        {
            code();
        }
        else if (strEql(ch, "shutdown"))
        {
            break;
        }
        else if (strEql(ch, "debug-mode"))
        {
            // Switch to debug screen
            clearScreen();
            //debug_screen();
        }
        else if (strEql(ch, "list"))
        {
            code_list();
        }
        else
        {
            print("\nCommand not Found!\n");
        }
        print_pos_colored("                                  TCIDOS 0.1                                    ", 0, 0, 0b01110000);
        //set_header("Test");
        print_pos_colored("                                                                                ", 24, 0, 0x80);
        print_pos_colored(" CMD-1 ", 24, 1, 0x70);
	} while (!strEql(ch, "dbg_exit_232323"));
}



void sum()
{
	print("\nHow many numbers: ");
	int n = str_to_int(input(""));
	int i =0;
	print("\n");
	int arr[n];
	fill_array(arr,n);
	int s = sum_array(arr,n);
	print("Result: ");
	print(itoa(s, 10));
	print("\n");
}
void echo()
{
	print("\n");
	string str = input("");
	print("\n");
	print(str);
	print("\n");
}
void sort()
{
	int arr[100];
	print("\nArray size: ");
	int n = str_to_int(input(""));
	print("\n");
	fill_array(arr,n);
	print("Before sorting:\n");
	print_array(arr,n);
	print("\nOrder: (1 for increassing/ 0 for decreassing): ");
	int ordre = str_to_int(input(" "));
	insertion_sort(arr,n,ordre);
	print("\nAfter sorting:\n");
	print_array(arr,n);
}

void fill_array(int arr[],int n)
{
	int i = 0;
	for (i = 0;i<n;i++)
	{
		print("ARR[");
		print(itoa(i, 10));
		print("]: ");
		arr[i] = str_to_int(input(" "));
		print("\n");
	}
}
void print_array(int arr[],int n)
{
	int i = 0;
	for (i = 0;i<n;i++)
	{
		/*print("ARR[");
		print(int_to_string(i));
		print("]: ");*/
		print(itoa(arr[i], 10));
		print("   ");
	}
	print("\n");
}
void insertion_sort(int arr[],int n,int ordre) //1 is increassing, 0 is descreassing
{
	int i = 0;
	for (i = 1;i<n;i++)
	{
		int aux = arr[i];
		int j = i;
		while((j > 0) && ((aux < arr[j-1]) && ordre ))
		{
			arr[j] = arr[j-1];
			j = j -1;
		}
		arr[j] = aux;
	}
}
int sum_array(int arr[],int n)
{
	int i = 0;
	int s = 0;
	for (i = 0;i<n;i++)
	{
		s += arr[i];
	}
	return s;
}
void fibonaci()
{
	print("\nHow many Elements: ");
	int n = str_to_int(input(" "));
	print("\n");
	int res = 1;
	int i = 0;
	for(i =0;i<n;i++)
	{
		print("Fibo ");
		print(itoa(i, 10));
		print(" : ");
		print(itoa(res, 10));
		res += res;
		print("\n");
	}

}
int gcd_couple(int a,int b)
{
	if(b == 0)
		return 1;
	if(a % b ==0)
		return b;
	else
		return gcd_couple(b,a % b);
}
void gcd()
{
	print("\nHow many numbers: ");
	int n = str_to_int(input(" "));
	int i =0;
	print("\n");
	int arr[n];
	int matrix[n][n];
	fill_array(arr,n);
	for (i = 0;i<n;i++)
	{
		matrix[0][i] = arr[i];
	}
	int j = 0;
	for (i =1;i<n;i++)
	{
		for (j=0;j<n-1;j++)
		{
			matrix[i][j] = gcd_couple(matrix[i-1][j] , matrix[i-1][j+1]);
		}
	}
	print("Result: ");
	print(itoa(matrix[n-1][0], 10));
	print("\n");
}
void print_matrix(int matrix[][100],int rows,int cols)
{
	int i =0;
	int j = 0;
	for (i = 0;i<rows;i++)
	{
		for(j =0;j<cols;j++)
		{
			print(itoa(matrix[i][j], 10));
			print("   ");
		}
		print("\n");
	}
}
void set_background_color()
{
	print("\nColor codes : ");
	print("\n0 : black");
	print_colored("\n1 : blue",1,0);   // screen.h
	print_colored("\n2 : green",2,0);
	print_colored("\n3 : cyan",3,0);
	print_colored("\n4 : red",4,0);
	print_colored("\n5 : purple",5,0);
	print_colored("\n6 : orange",6,0);
	print_colored("\n7 : grey",7,0);
	print_colored("\n8 : dark grey",8,0);
	print_colored("\n9 : blue light",9,0);
	print_colored("\n10 : green light",10,0);
	print_colored("\n11 : blue lighter",11,0);
	print_colored("\n12 : red light",12,0);
	print_colored("\n13 : rose",13,0);
	print_colored("\n14 : yellow",14,0);
	print_colored("\n15 : white",15,0);

	print("\n\n Text color ? : ");
	int text_color = str_to_int(input(" "));
	print("\n\n Background color ? : ");
	int bg_color = str_to_int(input(" "));
	set_screen_color(text_color,bg_color);
	clearScreen();
}

void multiply()
{
	print("\nNum 1 :");
	int num1 = str_to_int(input(" "));
	print("\nNum 2 :");
	int num2 = str_to_int(input(" "));
	print("\nResult : ");
	print(itoa(num1*num2, 10)); // util.h
	print("\n");
}

void about() {
    print("\n _____ ___ ___ ___   ___  ___ \n");
    print("|_   _/ __|_ _|   \\ / _ \\/ __|\n");
    print("  | || (__ | || |) | (_) \\__ \\  \n");
    print("  |_| \\___|___|___/ \\___/|___/  \n");
    print("\n=============================================================");
    print("\n TCIDOS v0.1 build");
    print(itoa(BUILD_NUMBER, 10));
    print("\n Forked from IKnow/NIDOS and Modifided by Iyxan23/NurIhsan\n");
    print("\n= CPU INFO ==================================================\n");
    detect_cpu();
    print("\n= OTHER =====================================================\n");
    print("MEMSIZE ");
    print(itoa(count_ram(), 10));
    print(" KB");
    print("\n\n");
}

void set() {
    string idx = input("\nSet stack index (int): ");
    string val = input("\nSet stack value (int): ");
    int *pointer_stack = &stack_[0];
    pointer_stack[str_to_int(idx)] = str_to_int(val);
    print("\n\n");
}

void get() {
    string idx = input("\nGet index (int): ");
    print("\n");
    int *pointer_stack = &stack_[0];
    print(itoa(pointer_stack[str_to_int(idx)], 10));
    print("\n");
}

void read() {
    string addr = input("\nSpecify address (int): ");
    print("\nData at ");
    print(addr);
    print(" : ");
    char value = *(char*)str_to_int(addr);
    char* pointer = str_to_int(addr);
    value = *pointer;
    print(itoa(value, 10));
    print("\n");
}

void readlong() {
    int addr = str_to_int(input("\nSpecify address (int): "));
    int len = str_to_int(input("\nLength: "));
    int a = 0;
    print("\n");
    while (a < len) {
        print(itoa(addr + a, 10));
        print(" : ");
        char value = *(char*)addr + a;
        char* pointer = addr + a;
        value = *pointer;
        print(itoa(value, 10));
        // print("   : ");
        // char buf[1];
        // buf[0] = value;
        // print(buf);
        print("\n");
        a++;
    }
    print("\n");
}

int dayofweek(int d, int m, int y)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

int charToInt(char c){
    return c - '0';
}

void get_time() {
    char day_to_date[7][10] = {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };
    print("\n");
    string date = day_to_date[dayofweek(day, month, year) - 1];
    print(date);
    print(" ");
    print(itoa(day, 10));
    print(", ");
    print(itoa(month, 10));
    print("-");
    print(itoa(year, 10));
    print("  ");
    print(itoa(hour, 10));
    print(":");
    print(itoa(minute, 10));
    print(":");
    print(itoa(second, 10));
    print("\n\n");
}

void code() {
    string index_input = input("\nInput code index: ");
    int index_wanted = str_to_int(index_input);
    if (index_wanted >= 10) {
        print("\nMust not be higher than 10");
        return;
    }
    print("\nRunning code on code index ");
    print(itoa(codeindex, 10));
    print("\nType \",q\" to quit, and Type \",j\" to jump to other line\n");
    int line = 0;
    while (1) {
        print("\n");
        print(itoa(line, 10));
        print(": ");
        string data = input("");
        if (strEql(data, ",q")) {
            break;
        }
        if (strEql(data, ",j")) {
            string jump_line_raw = input("\nJUMP: ");
            int jump_line = str_to_int(jump_line_raw) - 1;
            if (jump_line >= 300 || jump_line < 0) {
                print("\nJump Location must not be ");
                print(jump_line >= 300 ? "higher than 300.\n" : "below 0.\n");
            } else {
                line = jump_line;
            }
        }
        int *pointer = &codedata[codeindex][line];
        *pointer = data;
        line++;
    }
    codeindex++;
    print("\nCode saved successfully!\n\n");
}

void code_list() {
    print("\nPlease enter an code index: ");
    string index_raw = input("");
    int index_input = str_to_int(index_raw);
    if (index_input < 9 && index_input > -1) {
        print("\nListing codes in the index..\n");
        int index_loop = 0;
        while (index_loop != 22) {
            print(itoa(index_loop, 10));
            print(" : ");
            print(codedata[index_input][index_loop]);
            print("\n");
            index_loop++;
        }
        print("\n");
    } else {
        print("\nPlease do not enter number ");
        print(index_input > 9 ? "higher than 10 (Max limit).\n\n" : "Below 0.\n\n");
    }
}

/*
void debug_screen() {   // Implemented soon
    string command = (string) malloc(50);
    int command_index = 0;
    string prompt = "TCIDOS-DEBUG ] ";
    int prompt_len = strlength(prompt);
    cursorY = 24;
    while (1) {
        print_pos("                                                          ", 24, 0);
        print_pos(prompt, 24, 0);
        while (1) {
            cursorX = command_index + prompt_len;
            updateCursor();
            print_pos_colored("                              TCIDOS-DEBUG 0.1                          ", 0, 0, 0b01110000);
            char piece_of_command = ' ';
            piece_of_command = get_char();
            if (piece_of_command == '\b' && command_index != 0) {
                command_index--;
            } else if (piece_of_command == '\n') {
                break;
            } else {
                command = append(command, piece_of_command);
                printch(piece_of_command);
            }
        }
        // Proccess the command

        if (strEql(command, "q") || strEql(command, "quit") || strEql(command, "exit")) {
            break;
        }
    }
    clearScreen();
}*/

void help()
{
	print("\ncmd        : Launch a new recursive Shell");
	print("\nclear      : Clears the screen");
	print("\nsum        : Computes the sum of n numbers");
	print("\necho       : Reprint a given text");
	print("\nsort       : Sorts a given n numbers");
	print("\nexit       : Quits the current shell");
	print("\ncolor      : Changes the colors of the terminal");
	print("\nset        : Set global variable for running applications");
	print("\ncode       : Code an application");
	print("\nmcode      : Code manager");
	print("\nlist       : List the application you wrote on `code`");
	print("\nrun        : Run the application you wrote on `code`");
	print("\nget        : Get/Read global variable for running applications");
	print("\nread       : Read data at a specified address");
	print("\nreadlong   : Read data as array at a specified address");
	print("\ntime       : Get the current time");
	print("\ncpuid      : Get Information about the CPU");
	print("\nhalt       : Halt the CPU");
	print("\nabout/info : About this OS");

	print("\n\n");
}

