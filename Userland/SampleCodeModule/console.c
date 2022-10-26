#include <console.h>
#include <library.h>
#include <system_calls.h>
#include <tron.h>



// INVIERTE POR UN TEMA DE LITTLE ENDIAN, Y COMO NO PUEDO TRABAJAR OCN LAS DIRECCIONES DE MEMORIA HAGO UN MEMCOPY
void memMoveChar( char* array1, char* array2, int charsToMove  ){ 
	for ( int i = 0; i < charsToMove/8; i++){
		for ( int j = 0; j < 8; j++ ){
			array1[7-j+8*i] = array2[j+8*i];
		}
	}
}

void clearconsoleBuffer(){
	for ( int i = 0; i < lastChar; i++ )
		consoleBuffer[i] = 0;
	lastChar=0;
}

void clearScreen(){
	putSquare(0,0,1100,0x000000);
	restartCursor();
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
			appendstring("RAX   ");
			break;
		case 8:
			newline();
			appendstring("RBX   ");
			break;
		case 16:
			newline();
			appendstring("RDX   ");
			break;
		case 24:
			newline();
			appendstring("RCX   ");
			break;
		case 32:
			newline();
			appendstring("RSI   ");
			break;
		case 40:
			newline();
			appendstring("RDI   ");
			break;
		case 48:
			newline();
			appendstring("RBP   ");
			break;
		case 56:
			newline();
			appendstring("RSP   ");
			break;
		case 64:
			newline();
			appendstring("R8    ");
			break;
		case 72:
			newline();
			appendstring("R9    ");
			break;
		case 80:
			newline();
			appendstring("R10   ");
			break;
		case 88:
			newline();
			appendstring("R11   ");
			break;
		case 96:
			newline();
			appendstring("R12   ");
			break;
		case 104:
			newline();
			appendstring("R13   ");
			break;
		case 112:
			newline();
			appendstring("R14   ");
			break;
		case 120:
			newline();
			appendstring("R15   ");
			break;
		default:
			break;
		}
		appendchar(toHex((snapshotBuffer[i]&0xF0)>>4));
		appendchar(toHex((snapshotBuffer[i]&0x0F)));


	}
}

void commandHelp(){
	clearScreen();
	restartCursor();
	appendstring("BIENVENIDO AL MENU HELP");
	newline();
	appendstring("EL SISTEMA CUENTA CON LOS SIGUIENTES COMANDOS:");
	newline();
	appendstring("- HELP");
	newline();
	appendstring("- TRON");
	newline();
	appendstring("- SNAPSHOT");
	newline();
	appendstring("- MEMACCESS ( MEM ADDRESS )");
	newline();
	appendstring("- CLEAR");
	newline();
	appendstring("- BEEP");
	newline();
	appendstring("- ANTHEM");
	newline();	
	appendstring("PRESIONE ESC PARA VOLVER AL MENU PRINCIPAL");
}

void commandClear(){
	clearScreen();
	restartCursor();
}

void commandSnapshot(){
	clearScreen();
	printRegisters();
	newline();
	appendstring("PRESIONE ESC PARA SALIR");
}

void commandTron(){
	playTron();
	restartCursor();
}

void checkCommand( char * string ){
	char * command = toUpper(consoleBuffer); 
	// SPLITEAR EL BUFFER Y COMPARAR CANTIDAD DE PALABRAS Y ETC
	if(strcmp2(command, "HELP") || strcmp2(command, "- HELP") ){
		commandHelp();
	}else if(strcmp2(command, "TRON") || strcmp2(command, "- TRON") ){
		commandTron();
	}else if(strcmp2(command, "CLEAR") || strcmp2(command, "- CLEAR") ){
		commandClear();
	}else if(strcmp2(command, "BEEP") || strcmp2(command, "- BEEP") ){
		// beep();
	}else if(strcmp2(command, "ANTHEM") || strcmp2(command, "- ANTHEM") ){
		// soviet_anthem();
	}else if( strcmp2(command,"SNAPSHOT")|| strcmp2(command, "- SNAPSHOT")){
		commandSnapshot();
	}
	/*
	else if(strcmp2(command, "SNAPSHOT") || strcmp2(command, "- SNAPSHOT") ){
		snapshot();
	}
	else if(strcmp2(command, "MEMACCESS") || strcmp2(command, "- MEMACCESS") ){
		memaccess();
	}*/
	
}

void checkKey( char c ){
	switch (c)
		{
		case BACKSPACE:{
			backspace();
			consoleBuffer[lastChar--] = 0;
			break;
		}
		case ESC:{
			clearScreen();
			restartCursor();
			break;
		}
		case ENTER : {
			newline();
			if ( consoleBuffer != 0 && consoleBuffer[0] ){				
				checkCommand(consoleBuffer);
				clearconsoleBuffer();
			}
		}
		case '=':{
			char* aux = getRegisters(); 
			memMoveChar(snapshotBuffer, aux, 128); 
			break;
		}
		default:{
			consoleBuffer[lastChar++] = c;
			appendchar(c);
			break;
		}
			
	}
}

char * toUpper(char * string){
	int i = 0;
	while(string[i] != 0){
		if(string[i] >= 'a' && string[i] <= 'z'){
			string[i] = string[i] - 32;
		}
		i++;
	}
	return string;
}

