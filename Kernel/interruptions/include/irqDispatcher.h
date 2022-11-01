#ifndef IRQDISPATCHER_H
#define IRQDISPATCHER_H

#include <stdarg.h>
#include <syscalls.h>
#include <stdint.h>
#include <keyboard_driver.h>
#include <sound_driver.h>
#include <video_driver.h>
#include <interrupts.h>
#include <time.h>


#define SYS_GETCHAR_ID 0
#define SYS_WRITE_ID 1
#define SYS_TICK_ID 2
#define SYS_HALT_ID 3
#define SYS_PUTSQUARE_ID 4
#define SYS_GETTIME_ID 5
#define SYS_GETLASTKEY_ID 6
#define SYS_GETREGISTERS_ID 7
#define SYS_BEEP_ID 8
#define SYS_SLEEP_ID 9
#define SYS_CLEARKEYBUFFER_ID 10
#define SYS_CHANGELANGUAGE_ID 11
#define SYS_STOREREGISTERS_ID 12
#define SYS_MEMACCESS_ID 13

void initialize();
char * getBuffer();

#endif