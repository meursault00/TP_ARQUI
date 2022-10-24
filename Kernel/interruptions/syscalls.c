#include <syscalls.h>
#include <naiveConsole.h>
#include <keyboard_driver.h>
#define STDOUT 1
#define STDRED 2
#define MAXBUFFER 500


void sys_write(uint64_t fd,char * buffer, uint64_t length){
    switch (fd){
    case STDOUT:
        videoPrintWord(buffer);
        break;
    case STDRED:
        videoPrintWordWColor(buffer,0xFF0000);
        break;
    default:
        break;
    }
}

char sys_getchar(int fd,char * buff,unsigned int count){
    char ret=getKey();
    while (ret==0)
    {
        _hlt();
        ret=getKey();
    }

    return ret;
}


int sys_time(){
    ticks_elapsed();
}