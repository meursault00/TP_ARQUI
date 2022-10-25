#include <irqDispatcher.h>
#include <syscalls.h>
#include <sound_driver.h>
#include <video_driver.h>
#include <interrupts.h>
#include <naiveConsole.h>
#include <keyboard_driver.h>


#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3


static void int_20();
static void int_21();
static uint64_t int_80(uint64_t rdi, uint64_t rsi, uint64_t  rdx ,uint64_t rcx,uint64_t r8,uint64_t r9);

static void write();
//static void tron(int);

static char snapshotBuffer[128]; 
static char buffer[500] = {0};
static int lastChar = 0;

//static void int_22(uint64_t rdi, uint64_t rsi, uint64_t rdx ,uint64_t rcx, uint64_t r8, uint64_t r9);
void (*fun_inter[256])(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
uint64_t (*fun_sys[256])(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);

void clearBuffer ( void ){
	for ( int i = 0; i < 80; i++ )
		buffer[i] = (char)0;
	lastChar = 0;
}

/*
void commandSnapshot(){
	clearScreen();
		printRegisters();
		videoNewLine();
		videoPrintWord("PRESIONE ESC PARA SALIR");
}
*/

void commandTron(){
	//clearScreen();
	//initialize_players();
	//tronMotherfucker(1);
	
}

void commandClear(){
	clearScreen();
	restartCursor();
}



void initialize(){
	(fun_inter[0])=int_20;
	(fun_inter[1])=int_21;
	(fun_inter[0x60])=int_80; // pasasr 60 en el asm

	//agreago syscalls
	(fun_sys[0])=sys_getchar;
	(fun_sys[1])=sys_write;
	(fun_sys[2])=sys_tick;
	(fun_sys[3])=sys_halt;
	(fun_sys[4])=sys_putSquare;
	(fun_sys[5])=sys_getTime;
	(fun_sys[6])=sys_getLastKey;
	(fun_sys[7])=sys_getRegisters;

}

void irqDispatcher(uint64_t irq, uint64_t rdi, uint64_t rsi, uint64_t  rdx ,uint64_t rcx,uint64_t r8,uint64_t r9) {
	(*fun_inter[irq])(rdi,rsi,rdx,rcx,r8,r9);
	return;
}

void int_20() {
	timer_handler();
}

void int_21(){
	storeKey();
	//write(getKey());
/*	char key=getKey();
	
	if(tronOn()){
		tron(key);

	} //chequeo en que modo estoy y envio el char obtenido a la funcion apropiada
	else{
		write(key);
	}
	*/
}

uint64_t int_80(uint64_t rdi, uint64_t rsi, uint64_t  rdx ,uint64_t rcx,uint64_t r8,uint64_t r9){
	return (*fun_sys[rdi])(rsi,rdx,rcx,r8,r9);
}
/*
void write(int aux){ // escritura usando funciones de video
	if(aux!=0){
		if(aux == 8){
			videoBackSpace();
			buffer[lastChar--] = 0;
		}
		else if(aux == '\n'){
			if ( buffer != 0 && buffer[0] != 0 )
				checkCommand(buffer);
			clearBuffer();
			videoNewLine();

		}
		else if(aux == 27){ //escape
			clearScreen();
			restartCursor();
		}
		else if ( aux == '=' ){ // tecla para hacer un snapshot en un momento arbitrario
			char* aux = snapshot(); 
			//memMoveChar(snapshotBuffer, aux, 128); 
		}
		else{
			videoPrintChar(aux);
			buffer[lastChar] = aux;
			lastChar+=1;
		}
	}
	

}
*/