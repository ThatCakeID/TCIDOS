kmain()
{
    // Things to remember:
    // 80 = Max WIDTH
    // 25 = Max Height

	isr_install();
	clearScreen();
	print("Loading TCIDOS...");
	#include "../include/kb.h"
    #include "../include/isr.h"
    #include "../include/idt.h"
    #include "../include/util.h"
    #include "../include/shell.h"
    #include "../include/log.h"
    print("\nWelcome!\n");
    clearScreen();
	print("\nWelcome To TCIDOS v0.1!\n\n");
	print_pos_colored("                                  TCIDOS 0.1                                    ", 0, 0, 0b01110000);
	//set_header("Test");
	print_pos_colored("                                                                                ", 24, 0, 0x80);
    print_pos_colored(" CMD-1 ", 24, 1, 0x70);
	//write_pos_colored('E', 24, 0, 0x0, 0xF);
    launch_shell(0);
    clearScreen();
}
