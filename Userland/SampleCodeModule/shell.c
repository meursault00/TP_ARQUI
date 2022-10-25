
#include <library.h>
#include <system_calls.h>
#include <tron.h>
#include <console.h>


void initialize_shell(){
	while(1){
		//halt();
		// refreshCursor();
		drawCursor(fontcolor);
		char c = getchar();
		checkKey(c);
	}
}



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