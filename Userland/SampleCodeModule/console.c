#include <console.h>
#include <library.h>
#include <system_calls.h>
#include <tron.h>
#include <keyboardPiano.h>

#define ASC_UP    '\200'
#define ASC_DOWN  '\201'
#define ASC_LEFT  '\202'
#define ASC_RIGHT '\203'

//hashcodes de los comandos en mayuscula
#define HELP 2089138798
#define TRON 2089584296
#define CLEAR 216417516
#define BEEP 2088922945
#define ANTHEM 2771458114
#define SNAPSHOT 650087221
#define TIME 2089574420
#define INVOP 223623889
#define DIVCERO 649756593
#define MEMACCESS 1829689142
#define PIANO 231722748
#define UPSIZE 235307403 // "size+"
#define DOWNSIZE 235307405
#define LANG_ES 3115062494 // lange=es
#define LANG_EN 3115062489
#define LANGUAGE 3857633481 // for help
#define SIZE 2089538912 // for help


//BUFFER DE COMANDOS PARA PODER HACER SCROLLING EN HISTORIAL DE EJECUCION
#define MAX_COMMAND_LENGTH 64
#define MAX_COMMANDS 64

char historyBuffer[MAX_COMMANDS][MAX_COMMAND_LENGTH];
unsigned int historyIndex = 0;
unsigned int historyDim = 0;



extern void INVALID_OP_CODE();


char * toUpper(char * string){
	int i = 0;
	while(string[i] != 0){
		if(string[i] >= 'a' && string[i] <= 'z')
			string[i] = string[i] - 32;
		
		i++;
	}
	return string;
}




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
	printInt(aux); 
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

}

void clearScreen(){
	putSquare(0,0,1024,BACKGROUND_COLOR);
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
// pequeña funcion que espera a que se presione una tecla para salir
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
	printColor("BIENVENIDO AL MENU HELP", 0xE9AD0C, 0);
	newline();
	appendstring("EL SISTEMA CUENTA CON LOS SIGUIENTES COMANDOS: <User commands>");
	newline();
	appendstring("- HELP");
	newline();
	appendstring("- TRON");
	newline();
	appendstring("- SNAPSHOT");
	newline();
	appendstring("- MEMACCESS ( MEM ADDRESS )");
	newline();
	printColor("- INVOP", RED, 0);
	newline();
	printColor("- DIVCERO", RED, 0);
	newline();
	appendstring("- BEEP");
	newline();
	appendstring("- TIME");
	newline();
	appendstring("- SIZE(+ o -)");
	newline();
	printColor("- ANTHEM", TERMINAL_BLUE, 0);
	newline();
	printColor("- CLEAR", TERMINAL_BLUE, 0);
	newline();
	printColor("- PIANO", TERMINAL_BLUE, 0);
	newline();
	printColor("- LANGUAGE=(EN o ES) ", TERMINAL_BLUE, 0);
	newline();
	printColor("Para mas informacion, ingrese HELP <command>.\n",0xE9AD0C, 0 );
	appendstring("Presione ");
	printColor("'ESC'", 0xE9AD0C, 0);
	print(" para volver a la consola.\n", 0);
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
	newline();
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
	print("Usted se encuentra frente a un teclado especial.\n\n", 0);
	print("Presione teclas...\n\n", 0);
	appendstring("Para salir presione la 'SPACE' bar.\n\n");

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
void commandDivCero(){
	clearScreen();
	int x=1/0;

}

void commandAnthem(){
	beep(392 ,375 /50); 
	beep(523 ,750 /50); 
	beep(392 ,463 /50); 
	beep(440 ,187 /50); 
	beep(494 ,750 /50); 
	beep(330 ,375 /50); 
	beep(330 ,375 /50); 
	beep(440 ,750 /50); 
	beep(392 ,463 /50); 
	beep(349 ,187 /50); 
	beep(392 ,750 /50); 
	beep(262 ,463 /50); 
	beep(262 ,187 /50); 
	beep(294 ,750 /50); 
	beep(294 ,463 /50); 
	beep(330 ,187 /50); 
	beep(349 ,750 /50); 
	beep(349 ,463 /50); 
	beep(392 ,187 /50); 
	beep(440 ,750 /50); 
	beep(494 ,375 /50); 
	beep(523 ,375 /50); 
	beep(587,1125/50);
}
void commandInvOp(){
	clearScreen();
	INVALID_OP_CODE();
}



// https://stackoverflow.com/questions/4014827/how-can-i-compare-strings-in-c-using-a-switch-statement
const unsigned long hash(unsigned char *str)
{
	unsigned int hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}
void printExitHelp(){
	appendstring("Presione ");
	printColor("'ESC'", 0xE9AD0C, 0);
	print(" para volver a la consola.\n", 0);
}
// CHEQUEAR CUAL ES EL COMANDO Y QUE EL COMANDO EXISTA CON LOS HASHCODES
void checkCommand() {
	char section[64]={0};
	char * command = toUpper(consoleBuffer);
	splitString( command, section, ' ' );
		
	if(section[0]==0){
		switch(hash(command)) {
			case HELP:
				commandHelp();
				break;
			case TRON:
				commandTron();
				break;
			case CLEAR:
				commandClear();
				break;
			case BEEP:
				commandBeep();
				break;
			case ANTHEM:
				commandAnthem();
				break;
			case SNAPSHOT:
				commandSnapshot();
				break;
			case TIME:
				commandTime();
				break;
			case INVOP:
				commandInvOp();
				break;
			case DIVCERO:
				commandDivCero();
				break;
			case PIANO:
				commandPiano();
				break;
			case UPSIZE:
				clearScreen();
				changeFontSize(1);
				break;
			case DOWNSIZE:
				clearScreen();
				changeFontSize(-1);
				break;
			case LANG_ES:
				changelanguage(1);
				break;
			case LANG_EN:
				changelanguage(0);
				break;
			default:
				print("Comando ", command);
				printColor("'%s'", ORANGY,command);
				print(" no es un comando valido.\n");
		}
	}
	else if(streql(consoleBuffer, "HELP") ){
		clearScreen();
		restartCursor();
		switch(hash(section)) {
			case HELP:{
				appendstring("En serio?\n\n");
				printColor("HELP: <User Commands>\n\n", 0x0F66151, 0);
				appendstring("Ayuda.\n");
				appendstring("De no ser seguido por nada, lista los comandos disponibles.\n");
				appendstring("De ser seguido por un comando, da informacion sobre el mismo.\n\n");
				printExitHelp();
				waitForKey(ESC);
				break;}
			case TRON:{
				printColor("TRON: <User Commands>\n\n", 0x0F66151, 0);
				appendstring("Juego de dos jugadores, al mejor de 5.\n");
				appendstring("Pierde quien choque contra si mismo,\nel otro jugador, o los bordes.\n");
				appendstring("El jugador 1 se mueve con las flechas.\n");
				appendstring("El jugador 2 se mueve con las teclas W,A,S y D.\n");
				appendstring("Sorpresa al final :)\n\n");
				printExitHelp();
				waitForKey(ESC);
				break;}	
			case BEEP:{
				printColor("BEEP: <User Commands>\n\n", 0x0F66151, 0);
				appendstring("Emite un beeeeep\n\n");
				beep(440,1);
				printExitHelp();
				waitForKey(ESC);
				}
				break;	
			case ANTHEM:{
				printColor("ANTHEM: <User Commands>\n\n", 0x0F66151, 0);
				appendstring("El himno de mi corazon, \npero no el de los abuelos de la nada.\n\n");
				printExitHelp();
				waitForKey(ESC);
				break;}
			case SNAPSHOT:{
				printColor("SNAPSHOT: <User Commands>\n\n", 0x0F66151, 0);
				appendstring("Imprime en pantalla el valo de los registros\nal momento de ejecucion.\n");
				appendstring("Para realizar una toma de estado, presione alguna de las flechas '<-' o '->'.\n\n");
				printExitHelp();
				waitForKey(ESC);
				break;}
			case TIME:{
				printColor("TIME: <User Commands>\n\n", 0x0F66151, 0);
				appendstring("De encontrarse en una isla desierta \nsin medios para saber la hora,\nuse este comando\n\n");
				printExitHelp();
				waitForKey(ESC);
				break;}
			case INVOP:{
				printColor("INVOP: <User Commands>\n\n", 0x0F66151, 0);
				appendstring("Envia un código de operación invalido.\n");
				appendstring("Que puede salir mal?\n\n");
				printExitHelp();
				waitForKey(ESC);
				break;}
			case DIVCERO:{
				printColor("DIVCERO: <User Commands>\n\n", 0x0F66151, 0);
				appendstring("Divide por cero.\n");
				appendstring("Totalmente inocuo.\n\n");
				printExitHelp();
				waitForKey(ESC);
				break;}
			case PIANO:{
				printColor("PIANO: <User Commands>\n\n", 0x0F66151, 0);
				appendstring("Componga su proxima obra maestra.\n");
				appendstring("Piano de eleccion de: \nPablo Lescano, Paul McCartney y Wolfgang Amadeus Mozart.\n");
				appendstring("Blancas: ASDFGHJ\n");
				appendstring("Negras: WETYUOP\n\n");
				printExitHelp();
				waitForKey(ESC);
				break;}
			case MEMACCESS:{
				printColor("MEMACCESS (MEM ADRESS): <User Commands>\n\n", 0x0F66151, 0);
				appendstring("Imprime por pantalla los 32 bits posteriores\na la direccion de memoria especificada.\n");
				appendstring("Debe ser ingresada la zona de memoria a acceder luego del comando separado por una espacio.\n");
				appendstring("Modo de uso: <memaccess [direccion]>\n\n");
				printExitHelp();
				waitForKey(ESC);
				break;}
			case CLEAR:{
				printColor("CLEAR: <User Commands>\n\n", 0x0F66151, 0);
				appendstring("Limpia la pantalla.\n");
				appendstring("AUSPICIADO POR MR MUSCULO\n");
				appendstring("ANIQUILA LOS GERMENES, SUFRIMIENTO MAXIMO\n\n");
				printExitHelp();
				waitForKey(ESC);
				break;}
			case LANGUAGE:{
				printColor("LANGUAGE: <User Commands>\n\n",0x0F66151, 0);
				appendstring("Cambia el teclado.\n");
				appendstring("Seguido por '=es' -> español\n");
				appendstring("Seguido por '=en' -> ingles\n");
				appendstring("Modo de uso <language=es> o <language=en> \n");
				appendstring("Ruso y Klingon disponibles proximamente.\n\n");
				printExitHelp();
				waitForKey(ESC);
				break;
			}
			case SIZE:{
				printColor("SIZE: <User Commands>\n\n", 0x0F66151, 0);
				appendstring("Agrande o achique el tamaño del texto en pantalla \nsiguiendo el comando con un + o un -,\nrespectivamente.\n");
				appendstring("Modo de uso: <size+>\n\n");
				printExitHelp();
				waitForKey(ESC);
			break;
			}
			default:
				print("Comando ", command);
				printColor("'%s'", ORANGY,command);
				print(" no es un comando valido.\n");

		}
	
	}	
	else if( streql(consoleBuffer, "MEMACCESS"))
	{
		int sectionLength;
		if ( strlen(section) <= 16 && onlyHexChars(section )){
			commandMemAccess(section, sectionLength);
		}
    
    }
	else {
		print("Comando ", command);
		printColor("'%s'", ORANGY,command);
		print(" no es un comando valido.\n");

	}
}

int lastUp = 0;
// CARGA AL HISTORIAL DE COMANDOS
static void loadHistory(const char *s){
	int len = strlen(s);
	if(historyDim > 0 && strcmp(historyBuffer[historyDim-1],s) == 0)
		return;
	strcpy(historyBuffer[historyDim], s);
	historyBuffer[historyDim++][len] = 0;
	historyIndex = historyDim;

}
// SUBE EN EL HISTORIAL A MAS VIEJOS
static char * upHistory(){
	printColor("%d : %d\n", 0x0F66151, historyIndex, historyDim);
	if(historyIndex > 0){
		return historyBuffer[--historyIndex];
	}
	beep(100, 1);
	return "";
}
//BAJA EN EL HISTORIAL A MAS RECIENTES
static char * downHistory(){
	printColor("%d : %d\n", 0x0F66151, historyIndex, historyDim);
	if(historyIndex < historyDim){
		return historyBuffer[historyIndex++];
	}
	beep(100, 1);
	return "";
}
//RESETEA LA LINEA
static void inLineReset(){
	int i = 0;
	while(i <= strlen(consoleBuffer)-1){
		backspace();
		i++;
	}
	clearconsoleBuffer();
}
//FUNCION QUE EJECUTA UP OR DOWN
void upArrow(int arrowUp){
	inLineReset();
	char *aux;
	if(arrowUp){
		aux =  upHistory();
	}
	else{
		aux = downHistory();

	}
	appendstring(aux);
	lastChar =0;
	for(int i = 0; i < strlen(aux); i++){
		consoleBuffer[lastChar++] = aux[i];
	}
}
// RESETEA EL HISTORIAL
void restartHistory(){
	historyDim = historyIndex =0;
}

// SE FIJA QUE TECLA HA SIDO ACCINOADA Y QUE HACER AL RESPECTO...
void checkKey( char c ){
	switch (c)
		{
		case BACKSPACE:{
			if(lastChar != 0){
				backspace();
				consoleBuffer[--lastChar] = 0;

			}else{
				beep(80, 1);
			}
			break;
		}
		case ESC:{
			clearScreen();
			restartCursor();
			restartHistory();
			printColor("user@Qemu:", USER_TEXT_COLOR, 0);
			printColor("> $ ", TERMINAL_BLUE, 0);
			break;
		}
		case ENTER : {
			newline();

			if ( consoleBuffer != 0 && consoleBuffer[0] ){	
				loadHistory(consoleBuffer);

				checkCommand(consoleBuffer);
				clearconsoleBuffer();
			}
			printColor("user@Qemu:", USER_TEXT_COLOR, 0);
			printColor("> $ ", TERMINAL_BLUE, 0);
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
		case ASC_UP:{ //up arrow key ascii
			upArrow(1);
			break;
		}
		case ASC_DOWN:{ // down arrow key ascii
			upArrow(0);
			break;
		}
		case ASC_RIGHT:{ // right arrow key ascii
			getRegisters(snapshotBuffer); 
			break;
		}
		case ASC_LEFT:{ // left arrow key ascii
			getRegisters(snapshotBuffer); 
			break;
		}
		default:{
			consoleBuffer[lastChar++] = c;
			appendchar(c);
			break;
		}
			
	}
}
