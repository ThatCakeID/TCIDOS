#ifndef SYSTEM_H
#define SYSTEM_H
#include "types.h"
#include "util.h"
uint8 inportb (uint16 _port);

unsigned char second;
unsigned char minute;
unsigned char hour;
unsigned char day;
unsigned char month;
unsigned int year;

void outportb (uint16 _port, uint8 _data);
unsigned char get_RTC_register(int reg);
int get_update_in_progress_flag();
void read_rtc();
int count_ram();
int detect_cpu(void);

#endif
