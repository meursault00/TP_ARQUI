#include <syscalls.h>
#include <naiveConsole.h>
#define STDOUT 1
#define STDRED 2

void sys_write(uint64_t fd,char * buffer, uint64_t length){
    switch (fd){
    case STDOUT:
        videoPrintWord(buffer);
        videoNewLine();
        break;
    case STDRED:
        videoPrintWordWColor(buffer,0xFF0000);
        videoNewLine();
        break;
    default:
        break;
    }


}