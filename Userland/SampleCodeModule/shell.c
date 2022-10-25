
#include <library.h>
#include <system_calls.h>


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


void commandHelp(){
	 //clearScreen();
	putword(1,"BIENVENIDO AL MENU HELP");
	//videoNewLine();
	putword(1,"EL SISTEMA CUENTA CON LOS SIGUIENTES COMANDOS:");
	//videoNewLine();
	putword(1,"- HELP");
	//videoNewLine();
	putword(1,"- TRON");
	//videoNewLine();
	putword(1,"- SNAPSHOT");
	//videoNewLine();
	putword(1,"- MEMACCESS ( MEM ADDRESS )");
	//videoNewLine();
	putword(1,"- CLEAR");
	//videoNewLine();
	putword(1,"- BEEP");
	//videoNewLine();
	putword(1,"- ANTHEM");
	//videoNewLine();
	putword(1,"PRESIONE ESC PARA VOLVER AL MENU PRINCIPAL");
}

void checkCommand( char * command ){

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




void initialize_shell(){
    char character = 'j';
	int x = 100 ;
	int y = 100 ;
	int size = 3;
	int color = 0xFF0000;
	putSquare(100,100,100, 0xffffff);

	write(character, x, y, size, color);

	int a = 21;
	float b = 3.6;
	void* parameters[] = {"Joaquin", &a, &b};
	char * foundation = "Hola me llamo %s, mi edad es %d y mi ojo ( version atp ) mide %f cm" ;
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
	//		putword(1,"enter");
//
//
	//	}
	//	else if(c == 27){ //escape
	//		//clearScreen();
	//		//restartCursor();
	//		putword(1,"escape");
	//	}
	//	else if ( c == '=' ){ // tecla para hacer un snapshot en un momento arbitrario
	//		//char* aux = snapshot(); 
	//		//memMoveChar(snapshotBuffer, aux, 128); 
	//		putword(1,"snapshot");
//
	//	}
	//	else{
	//		putchar(1,c);
	//		buffer[lastChar++] = c;
	//	}	
	//}
	//
	while (1);

    
}
