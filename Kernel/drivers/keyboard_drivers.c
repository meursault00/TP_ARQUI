#include <keyboard_driver.h>
#include <naiveConsole.h>
#define MAX_SCANCODE 58


static char asccode[MAX_SCANCODE][2] ={
    {   0,0   },
    {ESC , ESC}, 
    { '1','!' }, 
    { '2','@' },
    { '3','#' },
    { '4','$' }, 
    { '5','%' }, 
    { '6','^' },
    { '7','&' },
    { '8','*' }, 
    { '9','(' }, 
    { '0',')' },
    { '-','_' },
    { '=','+' }, 
    {'\b','\b'}, 
    {'\t','\t'},
    { 'q','Q' },
    { 'w','W' }, 
    { 'e','E' }, 
    { 'r','R' },
    { 't','T' },
    { 'y','Y' }, 
    { 'u','U' }, 
    { 'i','I' },
    { 'o','O' },
    { 'p','P' }, 
    { '[','{' }, 
    { ']','}' },
    {'\n','\n'},
    {   0,0   }, 
    { 'a','A' }, 
    { 's','S' },
    { 'd','D' },
    { 'f','F' }, 
    { 'g','G' }, 
    { 'h','H' },
    { 'j','J' },
    { 'k','K' }, 
    { 'l','L' }, 
    { ';',':' },
    {'\'','\"'},
    { '`','~' }, 
    {   0,0   }, 
    { '\\','|'},
    { 'z','Z' },
    { 'x','X' }, 
    { 'c','C' }, 
    { 'v','V' },
    { 'b','B' },
    { 'n','N' }, 
    { 'm','M' }, 
    { ',','<' },
    { '.','>' },
    { '/','?' }, 
    {   0,0   }, 
    {   0,0   },
    {   0,0   },
    { ' ',' ' },
};
static int shiftActivated = 0;
static int capsActivated = 0;

#define MAX_BUFFER 1000
static char keyBuffer[MAX_BUFFER];
static int bufferCount = 0;

void clearKeyBuffer ( void );

static char popBuffer(){
    char key = keyBuffer[0];
    for(int i = 0; i < bufferCount; i++){
        keyBuffer[i] = keyBuffer[i+1];
    }
    bufferCount--;
    return key;
}
char getKey(){
    if(bufferCount <= 0)
        return 0;
    
    return popBuffer();
}


static int isValidScancode(int scancode){
    return scancode > 0 && scancode < MAX_SCANCODE;
}

static int isLetter(int scancode){
    char ascii = asccode[scancode][0];
    return  ascii >= 'a' && ascii <= 'z';
}

int storeKey(){
    int scancode  = getkeyScancode();

    if(scancode == 42 || scancode == 54){
        shiftActivated = 1;
    }
    else if(scancode == 170 || scancode == 182){
        shiftActivated = 0;
    }
    else if(scancode == 58){
        capsActivated = !capsActivated;
    }
    if(isValidScancode(scancode) && bufferCount < MAX_BUFFER){
        if( isLetter(scancode) && capsActivated ){
            keyBuffer[bufferCount] = asccode[scancode][1];
        }
        else{
            keyBuffer[bufferCount] = asccode[scancode][shiftActivated ? 1: 0];   
        }
        bufferCount++;
        write(keyBuffer[bufferCount-1]); // ESTE WRITE DEBERIA SER DE SHELL.c EN USERLAND
        return 1;
    }
    
    return 0;
    
}



void write(int aux){ // escritura usando funciones de video
	if(aux!=0){
		if(aux == 8){
			videoBackSpace();
			keyBuffer[bufferCount--] = 0;
		}
		else if(aux == '\n'){
			//if ( buffer != 0 && keyBuffer[0] != 0 )
			//	checkCommand(buffer);
			clearKeyBuffer();
			videoNewLine();

		}
		else if(aux == 27){ //escape
			clearScreen();
			restartCursor();
		}
		//else if ( aux == '=' ){ // tecla para hacer un snapshot en un momento arbitrario
		//	char* aux = snapshot(); 
		//	memMoveChar(snapshotBuffer, aux, 128); 
		//}
		else{
			videoPrintChar(aux);
			keyBuffer[bufferCount] = aux;
			bufferCount+=1;
		}
	}
}

void clearKeyBuffer ( void ){
	for ( int i = 0; i < MAX_BUFFER; i++ )
		keyBuffer[i] = (char)0;
	bufferCount= 0;
}




























/*
    else if(scancode == 14){
        if(bufferCount > 0){
            bufferCount--;
            keyBuffer[bufferCount] = 0;
        }
    }
    else if(scancode == 28){
        keyBuffer[bufferCount] = 0;
        bufferCount = 0;
        if(strcmp(keyBuffer, "tron") == 0){
            tronOn();
        }
        else if(strcmp(keyBuffer, "help") == 0){
            help();
        }
        else if(strcmp(keyBuffer, "clear") == 0){
            clear();
        }
        else if(strcmp(keyBuffer, "date") == 0){
            date();
        }
        else if(strcmp(keyBuffer, "time") == 0){
            time();
        }
        else if(strcmp(keyBuffer, "echo") == 0){
            echo();
        }
        else if(strcmp(keyBuffer, "ls") == 0){
            ls();
        }
        else if(strcmp(keyBuffer, "cat") == 0){
            cat();
        }
        else if(strcmp(keyBuffer, "mkdir") == 0){
            mkdir();
        }
        else if(strcmp(keyBuffer, "rmdir") == 0){
            rmdir();
        }
        else if(strcmp(keyBuffer, "rm") == 0){
            rm();
        }
        else if(strcmp(keyBuffer, "touch") == 0){
            touch();
        }
        else if(strcmp(keyBuffer, "cp") == 0){
            cp();
        }
        else if(strcmp(keyBuffer, "mv") == 0){
            mv();
        }
        else if(strcmp(keyBuffer, "cd") == 0){
            cd();
        }
        else if(strcmp(keyBuffer, "pwd") == 0){
            pwd();
        }
        else if(strcmp(keyBuffer, "info") == 0){
            info();
        }
        else if(strcmp(keyBuffer, "ps") == 0){
            ps();
        }
        else if(strcmp(keyBuffer, "kill") == 0){
            kill();
        }
        else if(strcmp(keyBuffer
        */