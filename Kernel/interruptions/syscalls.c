#include <syscalls.h>
#include <naiveConsole.h>
#define STDOUT 1
#define STDRED 2
#define MAXBUFFER 500


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

void sys_read(int fd,char * buff,unsigned int count){
    if(fd==STDOUT){
        videoPrintWord("write here->");
        char *aux;
        aux=getBuffer();

        for (int i = 0; i < count; i++){
            buff[i]=aux[i];
        }
        
    }
}


int sys_time(){
    ticks_elapsed();
}