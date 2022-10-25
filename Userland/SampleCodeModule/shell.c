
#include <library.h>
#include <system_calls.h>
#include <tron.h>


#define ESC 27
#define BACKSPACE 8

static void commandTron();


// printTime
/*
void printTime(int timeCode, int utc){
    int aux;
    switch(timeCode){
        case 0x00:  // segundos
            uintToBase(getTime(0x00), buffer, 10);
            break;
        case 0x02: // minutos
            uintToBase(getTime(0x02), buffer, 10);
            break;
        case 0x04: // horas
            aux = getTime(0x04);
            if(aux <)


    }
}

*/

char buffer[256] = {0};
char lastChar = 0;

int isRunning();
void commandHelp();
void checkCommand(char * command);
static char * toUPPER(char * string);

void initialize_shell(){
	int i = 0;
	appendstring("DALE BOCAAA");
	while(1){
		halt();
		refreshCursor();
		char c = getchar();
		appendchar(c);

		//putchar( c, i+=8, 100, 1, 0xffff00);
	}

	while (isRunning()){
		checkCommand(buffer);
		// setCursorPos(0,0);
		
	}

}


int isRunning(){
	char c;
	while((c = getchar()) != '\n'){
		halt();
		refreshCursor();
		switch (c)
		{
		case BACKSPACE: // USA DEFINES!!!!!!!!!!!!!!!!!!!!!!! definime esta (1cm) ya estaba asi
			backspace();
			// tiene que ser reemplazada
			buffer[lastChar--] = 0;
			break;
		
		case ESC:
			clearScreen();
			//restartCursor();
			//	appendstring("escape");

		case '=':
			//char* aux = snapshot(); 
			//memMoveChar(snapshotBuffer, aux, 128); 
			//	appendstring("snapshot");
		
		default:
			appendchar(c);
			buffer[lastChar++] = c;
			break;
		}
			
	}
	newline();
	return 1;

}

void clearScreen(){
	putSquare(0,0,1100,0x000000);
}

void commandHelp(){
	clearScreen();
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

static char * toUPPER(char * string){
	int i = 0;
	while(string[i] != 0){
		if(string[i] >= 'a' && string[i] <= 'z'){
			string[i] = string[i] - 32;
		}
		i++;
	}
	return string;
}
void checkCommand( char * string ){
	char * command = toUPPER(string);
	if(strcmp(command, "HELP") || strcmp(command, "- HELP") ){
		commandHelp();
	}else if(strcmp(command, "TRON") || strcmp(command, "- TRON") ){
		//commandTron();
	}else if(strcmp(command, "CLEAR") || strcmp(command, "- CLEAR") ){
		// commandClear();
	}else if(strcmp(command, "BEEP") || strcmp(command, "- BEEP") ){
		// beep();
	}else if(strcmp(command, "ANTHEM") || strcmp(command, "- ANTHEM") ){
		// soviet_anthem();
	}else if( strcmp(command,"SNAPSHOT")|| strcmp(command, "- SNAPSHOT")){
		// commandSnapshot();
	}
	/*
	else if(strcmp(command, "SNAPSHOT") || strcmp(command, "- SNAPSHOT") ){
		snapshot();
	}
	else if(strcmp(command, "MEMACCESS") || strcmp(command, "- MEMACCESS") ){
		memaccess();
	}*/
	

}

void commandTron(){
	playTron();
	restartCursor();
}


//int a = 21;
	//float b = 3.6;
	//void* parameters[] = {"Joaquin", &a, &b};
	//char * foundation = "Hola me llamo %s, mi edad es %d y mi ojo ( version atp ) mide %f cm" ;
	//printf("Hola me llamo %s, mi edad es %d y mi ojo ( version atp ) mide %f cm", parameters);
	//char c;
	//while ( ( c = getchar()) ){
	//	if(c == 8){
	//		// videoBackSpace();
	//		// tiene que ser reemplazada
	//		buffer[lastChar--] = 0;
	//	}
	//	else if(c == '\n'){
	//		if ( buffer != 0 && buffer[0] != 0 )
	//			checkCommand(buffer);
	//		// clearBuffer();
	//		putnewline();
	//		/	appendstring(1,"enter");
//
//
	//	}
	//	else if(c == 27){ //escape
	//		//clearScreen();
	//		//restartCursor();
	//		/	appendstring(1,"escape");
	//	}
	//	else if ( c == '=' ){ // tecla para hacer un snapshot en un momento arbitrario
	//		//char* aux = snapshot(); 
	//		//memMoveChar(snapshotBuffer, aux, 128); 
	//		/	appendstring(1,"snapshot");
//
	//	}
	//	else{
	//		putchar(1,c);
	//		buffer[lastChar++] = c;
	//	}	
	//}