#include <syscalls.h>
#include <naiveConsole.h>
#define STDOUT 1
#define STDRED 2

void sys_write(uint64_t fd,char * buffer, uint64_t length){
    switch (fd){
    case STDOUT:
        ncPrint(buffer);
        ncNewline();
        break;
    case STDRED:
        printWColor(buffer,0x04);
        ncNewline();
        break;
    default:
        break;
    }


}