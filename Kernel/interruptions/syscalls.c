#include <syscalls.h>
#include <naiveConsole.h>
#include <keyboard_driver.h>
#include <sound_driver.h>
#include <interrupts.h>
#include <lib.h>
#define STDOUT 1
#define STDRED 2
#define MAXBUFFER 500

extern int getTime(int op);
static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static regsBuffer[128] = {0};
void sys_write(uint8_t character, uint32_t x, uint32_t y, uint32_t size, uint32_t color){
    put_letter(character, x, y, size, color );
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
    //sys_halt();
    return ticks_elapsed();
}

void sys_putSquare(uint32_t x , uint32_t y,uint32_t tam, uint32_t color){
    put_square(x,y,tam,color);
}

void sys_halt(){
    _hlt();
}

void sys_getRegisters(){
    char registers[16][4] = { "RAX", "RBX", "RDX", "RCX", "RSI", "RDI", "RBP", "RSP", " R8", " R9", "R10", "R11", "R12", "R13", "R14", "R15"};
    char buffer[50];
    for ( int i = 0; i < 16; i++ ){
        put_word(registers[i],0,32+i*16*2,2,0xf66151);
        uintToBase(*(regsBuffer+i),buffer,16);
        put_word(buffer,32*3,32+i*16*2,2,0xf6b351);
	}
    put_word("Presione ESC para salir",0,32+16*16*2,2,0xf65194);
}

int sys_getTime(int op){
    return getTime(op);
}

void sys_beep(int freq, int time){
    beeep(freq,time);
}

void sys_sleep(int seconds) {
    int start = seconds_elapsed();
    while (seconds_elapsed() - start < seconds) _hlt();
}

void sys_clearkeybuffer(){
    clearKeyBuffer();
}

void sys_changeLanguage(int lan){
    changeLanguage(lan);
}

void sys_storeRegisters(){
    char * regs = snapshot();
    memcpy(regsBuffer,regs,128);
}

void sys_memAccess( uint64_t memDir ){
    char buffer[50];


    put_word("Direccion Introducida : ",0,32,2,0xf66151);
    uintToBase(memDir,buffer,16);
    put_word(buffer,0,64,2,0xf65194);

    put_word("Direccion Accedida : ",0,96,2,0xf66151);
    uintToBase(memDir - (memDir%16),buffer,16);
    put_word(buffer,0,120,2,0xf65194);
    
    unsigned char * realAddress = (unsigned char*) (memDir - (memDir%16)) ;

    for ( int i = 0; i < 4; i++ ){
        for ( int j = 0; j < 8; j++ ){
            uintToBase(*(realAddress+8*i+j), buffer, 16);
            put_word(buffer,64*j,  180 + i*16*2   ,2,0xf6b351);
        }
	}
    put_word("Presione ESC para salir",0,212+4*16*2,2,0xf65194);
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base){
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}