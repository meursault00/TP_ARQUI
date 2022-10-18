#ifndef SYSCALLS_H
#define SYSCALLS_H
#include <naiveConsole.h>
#include <stdint.h>

void sys_write(uint64_t fd,char * buffer, uint64_t length);

#endif