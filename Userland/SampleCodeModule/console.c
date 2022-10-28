#include <console.h>
#include <library.h>
#include <system_calls.h>
#include <tron.h>

#include <keyboardPiano.h>

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
	appendstring("- SIZE (+ o -))");
	newline();
	appendstring("- INVOP");
	newline();
	appendstring("- DIVCERO");
	newline();
	appendstring("- PIANO");
	newline();
	appendstring("- LANGUAGE (EN o ES) ");
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
	//bufferOn = 0;
	playTron();
	restartCursor();
	getchar();
	//clearkeybuffer();
	clearScreen();
	//bufferOn = 1;
}

void commandPiano(){
	appendstring("Usted se encuentra frente a un teclado especial.");
	newline();
	appendstring("Presione teclas...");
	newline();
	newline();
	appendstring("Para salir presione la SPACE bar.");

	playPiano();
	commandClear();
}

void commandBeep(){
	beep(1000, 10);	
}

void printAddress( unsigned char * address ){
	for ( int i = 0; i < 8 ; i++ ){
		unsigned char a = toHex( ( ( address[i] >> 4 ) & 0x0F ) );
		unsigned char b = toHex( ( address[i] & 0x0F ) );
		appendchar(a);
		appendchar(b);
	}
}

void commandMemAccess( char * memdirHexa, int stringlen ){
	// a esta altura ya se que es valida la memdir, o sea que tiene 16 caracteres como maximo

	// EJEMPLO : memdirHexa = "403A1" 
	// primero tengo que pasar esto para que cada char ocupe solo 4 bits como deberia ser
	
	// estos son 20 bits y puedo leer como maximo de a chars 
	// entonces tengo que redondear a 24
	// o sea a chars

	int lenchar = ((stringlen+1)/2); // de esta forma se me redondea a chars
	// si recibo strlen de 5 se redondea a 3 chars ( 24 bits ),
	// si recibo strlen de 4 se queda en 2 chars ( 16 bits )
	// test de hextochar
	//char* a = "41";
	//print("hex to char %c",hexToChar(a[0],a[1]));
	
	// DEBERIA HABER UN CHEQUEO DE QUE LA DIR DE MEMORIA ESTE DENTRO 
	// DEL GIGABYTE ASIGANDO AL OS

	
	unsigned char finalMemDir[8]; // las direcciones de memoria son de 64 bits 8 * 8bits(char)
	
	int i= 0, j = 0;
	for (; i < 8; i++ ){
		// tengo en memDirHexa = "403A1" ( podria haber algo de hasta 16 hexas que representan 64 bits)
		// en en finalMemDir = 0x 0000 0000 0000 0000 = "0000 0000";
		if ( i >= ( 8 - lenchar) ){
			if ( (lenchar*2) > stringlen ){ // se fixio el tamaño de la direccion enviada
				finalMemDir[i] = hexToChar('\0', memdirHexa[j++]); // tengo que rellenar para que mi funciocn pueda traducir
				lenchar--; // decremento para que no ocurra de nuevo
			}
			else {
				unsigned char a  = memdirHexa[j++];
				unsigned char b  = memdirHexa[j++];
				finalMemDir[i] = hexToChar(a,b); // tomo los dos hexa y los traduzco
			}
		}
		else{
			finalMemDir[i] = 0;
		}
	}
	// para eso tengo que siempre poner los ultimos 4 bits en 0
	// entonces 00000000000403A1 -> 00000000000403A0
	// ALINEAR CON UNA MASCARA
	finalMemDir[i-1] = finalMemDir[i-1] & 0xF0;
	newline();
	appendstring("Memoria Introducida : ");
	print("%s", memdirHexa); 	
	newline();
	appendstring("Memoria Accedida : ");
	printAddress(finalMemDir);
	newline();
	int num=hexstringToInt(memdirHexa);

	// finalMemDir apunta a una direccion de memoria de 64 bits que contiene una direccion de memoria valida e alineada
	unsigned char deposit[32] = {0};
    unsigned char * realAddress = (unsigned char*) num - ( num % 16 );

	//memAccess(realAddress, deposit);
	appendstring("32 bytes : ");
	newline();
	for(int i=0;i<4;i++){
		for(int j=0;j<8;j++){
			uintToBase(*(realAddress+8*i+j),deposit,16);
			print(deposit);
			putchar(' ');
		}
		newline();
	}	
	//newline();
	//printAddress(deposit);
	//newline();
	//printAddress(deposit+8);
	//newline();
	//printAddress(deposit+16);
	//newline();
	//printAddress(deposit+24);
	//newline();


	//for ( int k = 0; k < 32; k++ ){
	//	if ( !(k % 4) )
	//		newline();
	//	appendchar(toHex(((deposit[i])>>4)&0x0F));
	//	appendchar( toHex(deposit[i]&0x0F));
//
	//}
}

 static void div_cero(){
	
	int x=1/0;
 }

// hexa to int


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
		else if(streql(consoleBuffer, "PIANO")){
			commandPiano();
		}
	
	}else{
		if(streql(consoleBuffer, "MEMACCESS") || streql(consoleBuffer, "- MEMACCESS") ){
			int sectionLength;
			if ( strlen(section) <= 16 && onlyHexChars(section )){
				commandMemAccess(section, sectionLength);
			}
		}
		// deberiamos agregar la de size aca porque tambien recibe un parametro
		else if(streql(consoleBuffer, "SIZE") || streql(consoleBuffer, "- SIZE")){
			if(streql(section,"+")){
				changeFontSize(1);
				clearScreen();
			}
			else if(streql(section,"-"))
				changeFontSize(-1);
				clearScreen();
		}
		else if(streql(consoleBuffer, "LANGUAGE") || streql(consoleBuffer, "- LANGUAGE")){
			if(streql(section,"EN")||streql(section,"en")){
				changelanguage(0);
			}
			else if(streql(section,"ES"),streql(section,"es"))
				changelanguage(1);
		}
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
			getRegisters(snapshotBuffer); 
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
