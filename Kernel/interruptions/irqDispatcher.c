#include <irqDispatcher.h>
#include <syscalls.h>
#include <sound_driver.h>
#include <video_driver.h>
#include <tron.h>
#include <interrupts.h>
#include <naiveConsole.h>
#include <keyboard_driver.h>

extern char* snapshot();

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3


static void int_20();
static void int_21();
static uint64_t int_80();

static void write();
static void tron(int);

static char snapshotBuffer[128]; 
static char buffer[500] = {0};
static int lastChar = 0;

//static void int_22(uint64_t rdi, uint64_t rsi, uint64_t rdx ,uint64_t rcx, uint64_t r8, uint64_t r9);
void (*fun_inter[256])(uint64_t,uint64_t,uint64_t,uint64_t);
uint64_t (*fun_sys[256])(uint64_t,uint64_t,uint64_t);

void clearBuffer ( void ){
	for ( int i = 0; i < 80; i++ )
		buffer[i] = (char)0;
	lastChar = 0;
}

char toHex( char character ){ // de la forma 0000 XXXX
	switch (character)
	{
	case 15:
		return 'F';
		break;
	case 14:
		return 'E';
		break;
	case 13:
		return 'D';
		break;
	case 12:
		return 'C';
		break;
	case 11:
		return 'B';
		break;
	case 10:
		return 'A';
		break;
    case 9:
		return '9';
		break;
	case 8:
		return '8';
		break;
	case 7:
		return '7';
		break;
	case 6:
		return '6';
		break;
	case 5:
		return '5';
		break;
	case 4:
		return '4';
		break;
    case 3:
		return '3';
		break;
	case 2:
		return '2';
		break;
	case 1:
		return '1';
		break;
	case 0:
		return '0';
		break;
	
	default:
		return character;
	}
}

void printRegisters(){
	for ( int i = 0; i < 128; i++ ){ 
		switch (i)
		{
		case 0:
			videoPrintWord("RAX   ");
			break;
		case 8:
			videoNewLine();
			videoPrintWord("RBX   ");
			break;
		case 16:
			videoNewLine();
			videoPrintWord("RDX   ");
			break;
		case 24:
			videoNewLine();
			videoPrintWord("RCX   ");
			break;
		case 32:
			videoNewLine();
			videoPrintWord("RSI   ");
			break;
		case 40:
			videoNewLine();
			videoPrintWord("RDI   ");
			break;
		case 48:
			videoNewLine();
			videoPrintWord("RBP   ");
			break;
		case 56:
			videoNewLine();
			videoPrintWord("RSP   ");
			break;
		case 64:
			videoNewLine();
			videoPrintWord("R8    ");
			break;
		case 72:
			videoNewLine();
			videoPrintWord("R9    ");
			break;
		case 80:
			videoNewLine();
			videoPrintWord("R10   ");
			break;
		case 88:
			videoNewLine();
			videoPrintWord("R11   ");
			break;
		case 96:
			videoNewLine();
			videoPrintWord("R12   ");
			break;
		case 104:
			videoNewLine();
			videoPrintWord("R13   ");
			break;
		case 112:
			videoNewLine();
			videoPrintWord("R14   ");
			break;
		case 120:
			videoNewLine();
			videoPrintWord("R15   ");
			break;
		default:
			break;
		}
		videoPrintChar(toHex((snapshotBuffer[i]&0xF0)>>4));
		videoPrintChar(toHex((snapshotBuffer[i]&0x0F)));
		

	}
}

// INVIERTE POR UN TEMA DE LITTLE ENDIAN, Y COMO NO PUEDO TRABAJAR OCN LAS DIRECCIONES DE MEMORIA HAGO UN MEMCOPY
void memMoveChar( char* array1, char* array2, int charsToMove  ){ 
	for ( int i = 0; i < charsToMove/8; i++){
		for ( int j = 0; j < 8; j++ ){
			array1[7-j+8*i] = array2[j+8*i];
		}
	}
}

char strcmp( const char* stringA,const char* stringB)  
{  
    char flag = 0;
	int i = 0;
    while(stringA[i]!='\0' && stringB[i]!='\0')  {  
       if(stringA[i]!=stringB[i])  
       {  
           flag=1;  
           break;  
       }  
       i++;  
    }  
	if(stringA[i] != 0 || stringB[i] != 0){
		return 0;
	}
    if(flag==0)  
    	return 1;  
 	return 0;  
}  

void commandSnapshot(){
	clearScreen();
		printRegisters();
		videoNewLine();
		videoPrintWord("PRESIONE ESC PARA SALIR");
}

void commandHelp(){
	clearScreen();
	videoPrintWord("BIENVENIDO AL MENU HELP");
	videoNewLine();
	videoPrintWord("EL SISTEMA CUENTA CON LOS SIGUIENTES COMANDOS:");
	videoNewLine();
	videoPrintWord("- HELP");
	videoNewLine();
	videoPrintWord("- TRON");
	videoNewLine();
	videoPrintWord("- SNAPSHOT");
	videoNewLine();
	videoPrintWord("- MEMACCESS ( MEM ADDRESS )");
	videoNewLine();
	videoPrintWord("- CLEAR");
	videoNewLine();
	videoPrintWord("- BEEP");
	videoNewLine();
	videoPrintWord("- ANTHEM");
	videoNewLine();
	videoPrintWord("PRESIONE ESC PARA VOLVER AL MENU PRINCIPAL");
}

void commandTron(){
	clearScreen();
	initialize_players();
	tronMotherfucker(1);
	
}

void commandClear(){
	clearScreen();
	restartCursor();
}

void checkCommand( char * command ){

	if(strcmp(command, "HELP") || strcmp(command, "- HELP") ){
		commandHelp();
	}else if(strcmp(command, "TRON") || strcmp(command, "- TRON") ){
		commandTron();
	}else if(strcmp(command, "CLEAR") || strcmp(command, "- CLEAR") ){
		commandClear();
	}else if(strcmp(command, "BEEP") || strcmp(command, "- BEEP") ){
		beep();
	}else if(strcmp(command, "ANTHEM") || strcmp(command, "- ANTHEM") ){
		soviet_anthem();
	}else if( strcmp(command,"SNAPSHOT")|| strcmp(command, "- SNAPSHOT")){
		commandSnapshot();
	}
	/*
	else if(strcmp(command, "SNAPSHOT") || strcmp(command, "- SNAPSHOT") ){
		snapshot();
	}
	else if(strcmp(command, "MEMACCESS") || strcmp(command, "- MEMACCESS") ){
		memaccess();
	}*/
	

}

void initialize(){
	(fun_inter[0])=int_20;
	(fun_inter[1])=int_21;
	(fun_inter[0x60])=int_80; // pasasr 60 en el asm

	//agreago syscalls
	(fun_sys[0])=sys_getchar;
	(fun_sys[1])=sys_write;
	(fun_sys[2])=sys_time;
}

void irqDispatcher(uint64_t irq, uint64_t rdi, uint64_t rsi, char *  rdx ,uint64_t rcx) {
	(*fun_inter[irq])(rdi,rsi,rdx,rcx);
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

uint64_t int_80(uint64_t rdi, uint64_t rsi, char *  rdx ,uint64_t rcx){
	return (*fun_sys[rdi])(rsi,rdx,rcx);
}

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
			memMoveChar(snapshotBuffer, aux, 128); 
		}
		else{
			videoPrintChar(aux);
			buffer[lastChar] = aux;
			lastChar+=1;
		}
	}
	
	//int teclahex=getkey();
	//	if(charHexMap[ teclahex]=='\n')
	//			ncNewline();
	//	else if(charHexMap[ teclahex]!=0)
	//		ncPrintChar (charHexMap[ teclahex]);
	//
}




void tron(int aux){
	// asigno WASD para el jugador 1 y IJKL para el jugador 2
	switch(aux){
		case ESC:
			//gameSwitch(0);
			tronMotherfucker(0);
			clearScreen();
			restartCursor();

		/*
		case ' ':
			gameSwitch(1); // al apretar la barra espaciadora se inicia el juego
			break;
		*/
		case 'w':
			changePlayerDirection(1,UP);
			break;
		case 'a':
			changePlayerDirection(1,LEFT);
			break;
		case 's':
			changePlayerDirection(1,DOWN);
			break;
		case 'd':
			changePlayerDirection(1,RIGHT);
			break;
		
		case 'i':
			changePlayerDirection(2,UP);
			break;
		case 'j':
			changePlayerDirection(2,LEFT);
			break;
		case 'k':
			changePlayerDirection(2,DOWN);
			break;
		case 'l':
			changePlayerDirection(2,RIGHT);
			break;
		default:
			break;
	}
}