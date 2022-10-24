#ifndef SYSTEM_CALLS_H
#define SYSTEM_CALLS_H


extern void sys_write(int fd,char * buffer, int length);
extern char getchar();
extern int sys_time();

#endif