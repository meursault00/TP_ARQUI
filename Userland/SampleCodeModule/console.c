#include <console.h>
#include <library.h>
#include <system_calls.h>
#include <tron.h>

#include <keyboardPiano.h>
static int changingSize = 0;

/**
 *  HELP NO SE EJECUTA APRETANDO BACKSPACE
 * 	NO DEJAR ESCRIBIR CUADNO SE EJECUTA UN COMANDO
 *  IMPRIMIR TIEMPO Y LUEGO SEGUIR ESCRIBIENDO
 *  
 * 
 */
 extern void INVALID_OP_CODE();


void toUpper(char * string){
	int i = 0;
	while(string[i] != 0){
		if(string[i] >= 'a' && string[i] <= 'z')
			string[i] = string[i] - 32;
		
		i++;
	}
}

/**
 *  HELP NO SE EJECUTA APRETANDO BACKSPACE
 * 	NO DEJAR ESCRIBIR CUADNO SE EJECUTA UN COMANDO
 *  IMPRIMIR TIEMPO Y LUEGO SEGUIR ESCRIBIENDO
 *  
 * 
 */




// INVIERTE POR UN TEMA DE LITTLE ENDIAN, Y COMO NO PUEDO TRABAJAR OCN LAS DIRECCIONES DE MEMORIA HAGO UN MEMCOPY
void memMoveChar( char* array1, char* array2, int charsToMove  ){ 
	for ( int i = 0; i < charsToMove/8; i++){
		for ( int j = 0; j < 8; j++ ){
			array1[7-j+8*i] = array2[j+8*i];
		}
	}
}


// funcion que convierte un bcd en decimal
static int bcdToDec(int bcd){
	return ((bcd/16)*10 + (bcd%16));
}

void printCurrentTime(){
	int aux = bcdToDec(getTime(0x04));
	if(aux < 3){
		aux += aux+24-3;
	}
	else{
		aux -= 3;
	}
	printInt(aux); // checkear
	putchar(':');
	printInt(bcdToDec(getTime(0x02)));
	putchar(':');
	printInt(bcdToDec(getTime(0x00)));
	putchar('\n');
}


void clearconsoleBuffer(){
	for ( int i = 0; i < lastChar; i++ )
		consoleBuffer[i] = 0;
	lastChar=0;
	appendstring("#USER > ");

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

void waitForKey(char key){
	while(1){
		if(getchar() == key){
			break;
		}
	}
	//and restart
	clearScreen();
	restartCursor();
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
	appendstring("- TIME");
	newline();	
	appendstring("- BEEP");
	newline();
	appendstring("- SIZE");
	newline();
	appendstring("- INVOP");
	newline();
	appendstring("- DIVCERO");
	newline();
	appendstring("- PIANO");
	newline();
	appendstring("Presione ESC para volver a la consola.");
	waitForKey(ESC);
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
void commandTime(){
	printCurrentTime();
}

void commandTron(){
	playTron();
	commandClear();
}
void commandPiano(){
	appendstring("Usted se encuentra frente a un teclado especial.");
	newline();
	appendstring("-al presionar \'a\' sonara la nota DO y asi consecutivamente.");
	newline();
	appendstring("-tambien encontrara las octavas en w, e, t,y,u,");
	newline();
	newline();
	appendstring("<Para salir presione la barra espaciadora>");

	playPiano();
	commandClear();
}

void commandBeep(){
	beep(1000, 100);	
}

commandSize(){
	changingSize = 1;
	clearScreen();
	appendstring("CAMBIAR FONT SIZE");
	newline();
	appendstring("+ INCREMENTAR");
	newline();
	appendstring("- DECREMENTAR");
	newline();
	
}
 static void div_cero(){
	int x=1/0;
 }


void checkCommand(){
	char section[64]={0};
	splitString( consoleBuffer, section, ' ' );
	toUpper(consoleBuffer);

	if ( section[0] == 0 ){ // no tiene segundo parametro
		if(streql(consoleBuffer, "HELP") || streql(consoleBuffer, "- HELP") )
			commandHelp();
		else if(streql(consoleBuffer, "TRON") || streql(consoleBuffer, "- TRON") )
			commandTron();
		else if(streql(consoleBuffer, "CLEAR") || streql(consoleBuffer, "- CLEAR") )
			commandClear();
		else if(streql(consoleBuffer, "BEEP") || streql(consoleBuffer, "- BEEP") ){
			
			commandBeep();
		}
		else if(streql(consoleBuffer, "ANTHEM") || streql(consoleBuffer, "- ANTHEM") ){

		}
			//soviet_anthem();
		else if( streql(consoleBuffer,"SNAPSHOT")|| streql(consoleBuffer, "- SNAPSHOT"))
			commandSnapshot();
		else if(streql(consoleBuffer, "TIME") || streql(consoleBuffer, "-TIME"))
			commandTime();
		else if(streql(consoleBuffer, "INVOP") || streql(consoleBuffer, "-INVOP")){
			clearScreen();
			INVALID_OP_CODE();
		}
		else if(streql(consoleBuffer, "DIVCERO") || streql(consoleBuffer, "-DIVCERO")){
			clearScreen();
			div_cero();
		}
		else if(streql(consoleBuffer, "SIZE") || streql(consoleBuffer, "- SIZE")){
			commandSize();
		}
		else if(changingSize){
			if(streql(consoleBuffer, "+"))
				changeFontSize(2);
			else if(streql(consoleBuffer, "-"))
				changeFontSize(-2);
			changingSize = 0;
			clearScreen();
		}
		else if(streql(consoleBuffer, "PIANO")){
			commandPiano();
		}
	
	}else{
		if(streql(consoleBuffer, "MEMACCESS") || streql(consoleBuffer, "- MEMACCESS") ){
			if ( strlen(section) <= 16 && onlyHexChars(section )){
				newline();
				appendstring("Se introdujo MEMACCESS y una direccion valida");
				newline();
				//commandMemaccess();
			}
		}
		// deberiamos agregar la de size aca porque tambien recibe un parametro
	}
	
}

void checkKey( char c ){
	switch (c)
		{
		case BACKSPACE:{
			if(lastChar != 0){
				backspace();
				consoleBuffer[lastChar--] = 0;				
			}
			break;
		}
		case ESC:{
			clearScreen();
			restartCursor();
			changingSize = 0;
			appendstring("#USER > ");
			break;
		}
		case ENTER : {
			newline();

			if ( consoleBuffer != 0 && consoleBuffer[0] ){	

				checkCommand(consoleBuffer);
				clearconsoleBuffer();
			}else{
				appendstring("#USER > ");
			}
			break;
		}
		case '=':{
			char* aux = getRegisters(); 
			memMoveChar(snapshotBuffer, aux, 128); 
			break;
		}
		case '\t':{
			appendstring("    ");
			for(int i=0;i<4;i++){
				consoleBuffer[lastChar+i] =' ';
			}
			lastChar+=4;
			break;
		}
		default:{
			consoleBuffer[lastChar++] = c;
			appendchar(c);
			break;
		}
			
	}
}
