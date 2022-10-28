#ifndef SYSCALLS_H
#define SYSCALLS_H
#include <naiveConsole.h>
#include <irqDispatcher.h>
#include <stdint.h>
char sys_getchar();
void sys_write(uint8_t character, uint32_t x, uint32_t y, uint32_t size, uint32_t color);
int sys_tick();
void sys_halt();
void sys_putSquare(uint32_t x , uint32_t y,uint32_t tam, uint32_t color);
int sys_getTime(int op);
char sys_getLastKey();
char* sys_getRegisters();
void sys_beep(int freq, int time);
void sys_sleep(int seconds);
void sys_clearkeybuffer();

#endif