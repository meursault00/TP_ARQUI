#include <syscalls.h>
#include <naiveConsole.h>
#include <keyboard_driver.h>
#include <interrupts.h>
#include <lib.h>
#define STDOUT 1
#define STDRED 2
#define MAXBUFFER 500

extern int sys_getTime(int op);

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

char sys_getchar(){
    char ret=getKey();
    while (ret==0)
    {
        _hlt();
        ret=getKey();
    }

    return ret;
}

char sys_getLastKey(){
    return getLastChar();
}


int sys_tick(){
    ticks_elapsed();
}

int sys_putSquare(uint32_t x , uint32_t y,uint32_t tam, uint32_t color){
    put_square(x,y,tam,color);
}

void sys_halt(){
    _hlt();
}

