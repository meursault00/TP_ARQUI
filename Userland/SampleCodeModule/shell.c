
#include <library.h>
#include <system_calls.h>
#include <tron.h>
#include <console.h>


void initialize_shell(){
	appendstring("#USER > ");
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
	beep( 587,1125/50);
	print("%c %d %o %x %s", 'A', 10, 100, 1000, "Hello from printf!");
	while(1){
		
		drawCursor(fontcolor);
		char c = getchar();
		checkKey(c);

	}
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