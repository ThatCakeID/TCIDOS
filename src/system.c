#include "../include/system.h"
#include "../include/screen.h"
#define CURRENT_YEAR        2020                            // Change this each year!

int century_register = 0x00;                                // Set by ACPI table parsing code if possible

unsigned char second;
unsigned char minute;
unsigned char hour;
unsigned char day;
unsigned char month;
unsigned int year;

uint8 inportb (uint16 _port)
{
    uint8 rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (uint16 _port, uint8 _data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

// https://wiki.osdev.org/CMOS#Reading_All_RTC_Time_and_Date_Registers
enum {
      cmos_address = 0x70,
      cmos_data    = 0x71
};

int get_update_in_progress_flag() {
      outportb(cmos_address, 0x0A);
      return (inportb(cmos_data) & 0x80);
}

unsigned char get_RTC_register(int reg) {
      outportb(cmos_address, reg);
      return inportb(cmos_data);
}

void read_rtc() {
      unsigned char century;
      unsigned char last_second;
      unsigned char last_minute;
      unsigned char last_hour;
      unsigned char last_day;
      unsigned char last_month;
      unsigned char last_year;
      unsigned char last_century;
      unsigned char registerB;

      // Note: This uses the "read registers until you get the same values twice in a row" technique
      //       to avoid getting dodgy/inconsistent values due to RTC updates

      while (get_update_in_progress_flag());                // Make sure an update isn't in progress
      second = get_RTC_register(0x00);
      minute = get_RTC_register(0x02);
      hour = get_RTC_register(0x04);
      day = get_RTC_register(0x07);
      month = get_RTC_register(0x08);
      year = get_RTC_register(0x09);
      if(century_register != 0) {
            century = get_RTC_register(century_register);
      }

      do {
            last_second = second;
            last_minute = minute;
            last_hour = hour;
            last_day = day;
            last_month = month;
            last_year = year;
            last_century = century;

            while (get_update_in_progress_flag());           // Make sure an update isn't in progress
            second = get_RTC_register(0x00);
            minute = get_RTC_register(0x02);
            hour = get_RTC_register(0x04);
            day = get_RTC_register(0x07);
            month = get_RTC_register(0x08);
            year = get_RTC_register(0x09);
            if(century_register != 0) {
                  century = get_RTC_register(century_register);
            }
      } while( (last_second != second) || (last_minute != minute) || (last_hour != hour) ||
               (last_day != day) || (last_month != month) || (last_year != year) ||
               (last_century != century) );

      registerB = get_RTC_register(0x0B);

      // Convert BCD to binary values if necessary

      if (!(registerB & 0x04)) {
            second = (second & 0x0F) + ((second / 16) * 10);
            minute = (minute & 0x0F) + ((minute / 16) * 10);
            hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
            day = (day & 0x0F) + ((day / 16) * 10);
            month = (month & 0x0F) + ((month / 16) * 10);
            year = (year & 0x0F) + ((year / 16) * 10);
            if(century_register != 0) {
                  century = (century & 0x0F) + ((century / 16) * 10);
            }
      }

      // Convert 12 hour clock to 24 hour clock if necessary

      if (!(registerB & 0x02) && (hour & 0x80)) {
            hour = ((hour & 0x7F) + 12) % 24;
      }

      // Calculate the full (4-digit) year

      if(century_register != 0) {
            year += century * 100;
      } else {
            year += (CURRENT_YEAR / 100) * 100;
            if(year < CURRENT_YEAR) year += 100;
      }
}

void update_time() {
    // Print time
    read_rtc();
    print_pos_colored(itoa((int) hour, 10), 0, 72, 0b01110000);
    print_pos_colored(":", 0, 74, 0b01110000);
    print_pos_colored(itoa((int) minute, 10), 0, 75, 0b01110000);
    print_pos_colored(":", 0, 77, 0b01110000);
    print_pos_colored("  ", 0, 78, 0b01110000);
    print_pos_colored(itoa((int) second, 10), 0, 78, 0b01110000);
}


int count_ram() {
    unsigned int total;
    unsigned char lowmem, highmem;

    outportb(0x70, 0x30);
    lowmem = inportb(0x71);
    outportb(0x70, 0x31);
    highmem = inportb(0x71);

    total = (int) lowmem | (int) highmem << 8;
    return (int) total;
}

/*
void shutdown_bios() {
    __asm
    {
      mov ax, 0x1000
      mov ax, ss
      mov sp, 0xf000
      mov ax, 0x5307
      mov bx, 0x0001
      mov cx, 0x0003
      int 0x15
    }

    // FAILED TO SHUTDOWN
    clearScreen();
    print_pos_colored("ERROR: CANNOT SHUTDOWN USING BIOS", 12, 20, 0x40);
    print_pos_colored("HALTING CPU", 13, 20, 0x40);
    asm("hlt");
}
*/

// CPUID Code from : https://forum.osdev.org/viewtopic.php?t=11998
// ====================================================================
/* CPUID Code
 * Copyright (c) 2006-2007 -  http://brynet.biz.tm - <brynet@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* You need to include a file with fairly(ish) compliant print prototype, Decimal and String support like %s and %d and this is truely all you need! */
//#include <stdio.h> /* for print(); */

/* Required Declarations */
int do_intel(void);
int do_amd(void);
void printregs(int eax, int ebx, int ecx, int edx);

#define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

/* Simply call this function detect_cpu(); */
int detect_cpu(void) { /* or main() if your trying to port this as an independant application */
	unsigned long ebx, unused;
	cpuid(0, unused, ebx, unused, unused);
	switch(ebx) {
		case 0x756e6547: /* Intel Magic Code */
            do_intel();
            break;
		case 0x68747541: /* AMD Magic Code */
            do_amd();
            break;
		default:
            print("Unknown x86 CPU Detected\n");
            break;
	}
	return 0;
}

/* Intel Specific brand list */
char *Intel[] = {
	"Brand ID Not Supported.",
	"Intel(R) Celeron(R) processor",
	"Intel(R) Pentium(R) III processor",
	"Intel(R) Pentium(R) III Xeon(R) processor",
	"Intel(R) Pentium(R) III processor",
	"Reserved",
	"Mobile Intel(R) Pentium(R) III processor-M",
	"Mobile Intel(R) Celeron(R) processor",
	"Intel(R) Pentium(R) 4 processor",
	"Intel(R) Pentium(R) 4 processor",
	"Intel(R) Celeron(R) processor",
	"Intel(R) Xeon(R) Processor",
	"Intel(R) Xeon(R) processor MP",
	"Reserved",
	"Mobile Intel(R) Pentium(R) 4 processor-M",
	"Mobile Intel(R) Pentium(R) Celeron(R) processor",
	"Reserved",
	"Mobile Genuine Intel(R) processor",
	"Intel(R) Celeron(R) M processor",
	"Mobile Intel(R) Celeron(R) processor",
	"Intel(R) Celeron(R) processor",
	"Mobile Geniune Intel(R) processor",
	"Intel(R) Pentium(R) M processor",
	"Mobile Intel(R) Celeron(R) processor"
};

/* This table is for those brand strings that have two values depending on the processor signature. It should have the same number of entries as the above table. */
char *Intel_Other[] = {
	"Reserved",
	"Reserved",
	"Reserved",
	"Intel(R) Celeron(R) processor",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Intel(R) Xeon(R) processor MP",
	"Reserved",
	"Reserved",
	"Intel(R) Xeon(R) processor",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

/* Intel-specific information */
int do_intel(void) {
	print("Intel Specific Features:\n");
	unsigned long eax, ebx, ecx, edx, max_eax, signature, unused;
	int model, family, type, brand, stepping, reserved;
	int extended_family = -1;
	cpuid(1, eax, ebx, unused, unused);
	model = (eax >> 4) & 0xf;
	family = (eax >> 8) & 0xf;
	type = (eax >> 12) & 0x3;
	brand = ebx & 0xff;
	stepping = eax & 0xf;
	reserved = eax >> 14;
	signature = eax;
	print("Type ");
	print(itoa(type, 10));
	print(" - ");
	switch(type) {
		case 0:
		print("Original OEM");
		break;
		case 1:
		print("Overdrive");
		break;
		case 2:
		print("Dual-capable");
		break;
		case 3:
		print("Reserved");
		break;
	}
	print("\n");
	print("Family ");
	print(itoa(family, 10));
	print(" - ");
	switch(family) {
		case 3:
		print("i386");
		break;
		case 4:
		print("i486");
		break;
		case 5:
		print("Pentium");
		break;
		case 6:
		print("Pentium Pro");
		break;
		case 15:
		print("Pentium 4");
	}
	print("\n");
	if(family == 15) {
		extended_family = (eax >> 20) & 0xff;
		print("Extended family ");
		print(itoa(extended_family, 10));
		print("\n");
	}
	print("Model ");
	print(itoa(model, 10));
	print(" - ");
	switch(family) {
		case 3:
		break;
		case 4:
		switch(model) {
			case 0:
			case 1:
			print("DX");
			break;
			case 2:
			print("SX");
			break;
			case 3:
			print("487/DX2");
			break;
			case 4:
			print("SL");
			break;
			case 5:
			print("SX2");
			break;
			case 7:
			print("Write-back enhanced DX2");
			break;
			case 8:
			print("DX4");
			break;
		}
		break;
		case 5:
		switch(model) {
			case 1:
			print("60/66");
			break;
			case 2:
			print("75-200");
			break;
			case 3:
			print("for 486 system");
			break;
			case 4:
			print("MMX");
			break;
		}
		break;
		case 6:
		switch(model) {
			case 1:
			print("Pentium Pro");
			break;
			case 3:
			print("Pentium II Model 3");
			break;
			case 5:
			print("Pentium II Model 5/Xeon/Celeron");
			break;
			case 6:
			print("Celeron");
			break;
			case 7:
			print("Pentium III/Pentium III Xeon - external L2 cache");
			break;
			case 8:
			print("Pentium III/Pentium III Xeon - internal L2 cache");
			break;
		}
		break;
		case 15:
		break;
	}
	print("\n");
	cpuid(0x80000000, max_eax, unused, unused, unused);
	/* Quok said: If the max extended eax value is high enough to support the processor brand string
	(values 0x80000002 to 0x80000004), then we'll use that information to return the brand information.
	Otherwise, we'll refer back to the brand tables above for backwards compatibility with older processors.
	According to the Sept. 2006 Intel Arch Software Developer's Guide, if extended eax values are supported,
	then all 3 values for the processor brand string are supported, but we'll test just to make sure and be safe. */
	if(max_eax >= 0x80000004) {
		print("Brand: ");
		if(max_eax >= 0x80000002) {
			cpuid(0x80000002, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		if(max_eax >= 0x80000003) {
			cpuid(0x80000003, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		if(max_eax >= 0x80000004) {
			cpuid(0x80000004, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		print("\n");
	} else if(brand > 0) {
		print("Brand ");
		print(itoa(brand, 10));
		print(" - ");
		if(brand < 0x18) {
			if(signature == 0x000006B1 || signature == 0x00000F13) {
				print(Intel_Other[brand]);
			} else {
				print(Intel[brand]);
			}
			print("\n");
		} else {
			print("Reserved\n");
		}
	}
	print("Stepping: ");
	print(itoa(stepping, 10));
	print(" Reserved: ");
	print(itoa(reserved, 10));
	print("\n\n");
	return 0;
}

/* Print Registers */
void printregs(int eax, int ebx, int ecx, int edx) {
	int j;
	char string[17];
	string[16] = '\0';
	for(j = 0; j < 4; j++) {
		string[j] = eax >> (8 * j);
		string[j + 4] = ebx >> (8 * j);
		string[j + 8] = ecx >> (8 * j);
		string[j + 12] = edx >> (8 * j);
	}
	print(string);
}

/* AMD-specific information */
int do_amd(void) {
	print("AMD Specific Features:\n");
	unsigned long extended, eax, ebx, ecx, edx, unused;
	int family, model, stepping, reserved;
	cpuid(1, eax, unused, unused, unused);
	model = (eax >> 4) & 0xf;
	family = (eax >> 8) & 0xf;
	stepping = eax & 0xf;
	reserved = eax >> 12;
	print("Family: ");
	print(itoa(family, 10));
	print(" Model: ");
	print(itoa(model, 10));
	print(" [");
	switch(family) {
		case 4:
            print("486 Model ");
            print(itoa(model, 10));
            break;
		case 5:
		switch(model) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 6:
			case 7:
                print("K6 Model ");
                print(itoa(model, 10));
                break;
			case 8:
                print("K6-2 Model 8");
                break;
			case 9:
                print("K6-III Model 9");
                break;
			default:
                print("K5/K6 Model ");
                print(itoa(model, 10));
                break;
		}
		break;
		case 6:
		switch(model) {
			case 1:
			case 2:
			case 4:
                print("Athlon Model ");
                print(model);
                break;
			case 3:
                print("Duron Model 3");
                break;
			case 6:
                print("Athlon MP/Mobile Athlon Model 6");
                break;
			case 7:
                print("Mobile Duron Model 7");
                break;
			default:
                print("Duron/Athlon Model ");
                print(model);
                break;
		}
		break;
	}
	print("]\n");
	cpuid(0x80000000, extended, unused, unused, unused);
	if(extended == 0) {
		return 0;
	}
	if(extended >= 0x80000002) {
		unsigned int j;
		print("Detected Processor Name: ");
		for(j = 0x80000002; j <= 0x80000004; j++) {
			cpuid(j, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		print("\n");
	}
	if(extended >= 0x80000007) {
		cpuid(0x80000007, unused, unused, unused, edx);
		if(edx & 1) {
			print("Temperature Sensing Diode Detected!\n");
		}
	}
	print("Stepping: ");
	print(itoa(stepping, 10));
	print(" Reserved: ");
	print(itoa(reserved, 10));
	print("\n\n");
	return 0;
}
