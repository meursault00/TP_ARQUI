#include <irqDispatcher.h>
#include <syscalls.h>
extern uint64_t getkey();


static void int_20();
static void int_21();
static void int_80();
//static void int_22(uint64_t rdi, uint64_t rsi, uint64_t rdx ,uint64_t rcx, uint64_t r8, uint64_t r9);
void (*fun_inter[256])(uint64_t,uint64_t,char*,uint64_t);
void (*fun_sys[256])(uint64_t,char*,uint64_t);


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
	static const uint8_t charHexMap[256] = 
    {       
          0,    0,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  '9',   '0',   '-',  '=',    0xF0,    '    ',
        'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',   'O',  'P',  '[',   ']',  '\n',    0,     'A',       'S',
        'D',  'F',  'G',  'H',  'J',  'K',  'L',  ';',  '\'',    0,    0,  '\\',   'Z',  'X',     'C',       'V',
        'B',  'N',  'M',  ',',  '.',  '/',    0,  '*',     0,  ' ',    0,     0,     0,    0,       0,         0,
    };

	int teclahex=getkey();
		if(charHexMap[ teclahex]=='\n')
				ncNewline();
		else if(charHexMap[ teclahex]!=0)
			ncPrintChar (charHexMap[ teclahex]);
	
}

void int_80(uint64_t rdi, uint64_t rsi, char *  rdx ,uint64_t rcx){
	(*fun_sys[rdi])(rsi,rdx,rcx);
	return;
}
