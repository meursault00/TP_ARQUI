#include <irqDispatcher.h>
#include <syscalls.h>
#include <video_driver.h>
extern uint64_t getkey();


static void int_20();
static void int_21();
static void int_80();

static char buffer[80] = {0};
static int lastChar = 0;
static int randomthing = 1;

//static void int_22(uint64_t rdi, uint64_t rsi, uint64_t rdx ,uint64_t rcx, uint64_t r8, uint64_t r9);
void (*fun_inter[256])(uint64_t,uint64_t,char*,uint64_t);
void (*fun_sys[256])(uint64_t,char*,uint64_t);

void clearBuffer ( void ){
	for ( int i = 0; i < 80; i++ )
		buffer[i] = (char)0;
	lastChar = 0;
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
    if(flag==0)  
    	return 1;  
 	return 0;  
}  

void checkCommand( char * command ){
	if ( strcmp(command, "HELP")){
		put_word("DESREFERENCIAR PUNTERO DE LA FUNCION HELP", 500, 500, 2, 0xff00ff);
	}
}
void initialize(){
	(fun_inter[0])=int_20;
	(fun_inter[1])=int_21;
	(fun_inter[0x60])=int_80; // pasasr 60 en el asm
	(fun_sys[1])=sys_write;
}

void irqDispatcher(uint64_t irq, uint64_t rdi, uint64_t rsi, char *  rdx ,uint64_t rcx) {
	(*fun_inter[irq])(rdi,rsi,rdx,rcx);
	return;
}

void int_20() {
	timer_handler();
}

void int_21(){
	uint8_t teclahex=getkey();
	static const uint8_t charHexMap[256] = 
    {       
          0,    0,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  '9',   '0',   '-',  '=',    8,    '    ',
        'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',   'O',  'P',  '[',   ']',  '\n',    0,     'A',       'S',
        'D',  'F',  'G',  'H',  'J',  'K',  'L',  ';',  '\'',    0,    0,  '\\',   'Z',  'X',     'C',       'V',
        'B',  'N',  'M',  ',',  '.',  '/',    0,  '*',     0,  ' ',    0,     0,     0,    0,       0,         0,
    };

	uint8_t aux = charHexMap[teclahex];
	
	
	if(aux!=0){
		if(aux == 8)
			VideoBackSpace();
		else if(aux == '\n'){
			checkCommand(buffer);
			clearBuffer();
			VideoNewLine();

		}
		else{
			VideoPrintChar(aux);
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

void int_80(uint64_t rdi, uint64_t rsi, char *  rdx ,uint64_t rcx){
	(*fun_sys[rdi])(rsi,rdx,rcx);
	return;
}
