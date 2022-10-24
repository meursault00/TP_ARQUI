#ifndef SYSCALLS_H
#define SYSCALLS_H
#include <naiveConsole.h>
#include <irqDispatcher.h>
#include <stdint.h>
#include <time.h>

void sys_write(uint64_t fd,char * buffer, uint64_t length);
char sys_getchar();
int sys_time();

#endif