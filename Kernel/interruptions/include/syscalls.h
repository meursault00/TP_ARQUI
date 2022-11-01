#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>
#include <irqDispatcher.h>
#include <keyboard_driver.h>
#include <sound_driver.h>
#include <interrupts.h>
#include <lib.h>
#define STDOUT 1
#define STDRED 2
#define MAXBUFFER 500

char sys_getchar();
void sys_write(uint8_t character, uint32_t x, uint32_t y, uint32_t size, uint32_t color);
int sys_tick();
void sys_halt();
void sys_putSquare(uint32_t x , uint32_t y,uint32_t tam, uint32_t color);
int sys_getTime(int op);
char sys_getLastKey();
void sys_getRegisters(void);
void sys_beep(int freq, int time);
void sys_sleep(int seconds);
void sys_clearkeybuffer();
void sys_changeLanguage(int lan);
void sys_storeRegisters(void);
void sys_memAccess(uint64_t memDir);

#endif