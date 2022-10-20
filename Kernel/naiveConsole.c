#include <naiveConsole.h>
#include <stdio.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t  *  video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static int cursorX=0;
static int cursorY=0;
static const uint32_t width = 80;
static const uint32_t height = 25;
extern uint64_t timeUTC(char mode);
extern int getkey();

#define fontSize 2


void ncPrint(const char * string)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		ncPrintChar(string[i]);
}
void printWColor(char* str,char colorcode){
	int i;

	for (i = 0; str[i] != 0; i++){
		*currentVideo++ = str[i];
		*currentVideo++ =colorcode;
	}
		
	
}
void VideoPrintChar(char character){
	//static int cursorX=0;
	int aux;
	aux = put_letter(character,cursorX,cursorY,fontSize,0xFFFFCC);
	cursorX = aux ;
	cursorY = (cursorX / 1024)*16*fontSize;
	//put_letter('A',cursorX,10,1,0xFFFFFF);
}

void ncPrintChar(char character)
{
	*currentVideo = character;
	currentVideo += 2; // salteaa el caracter y el byte de los colores
}

void ncNewline()
{
	do
	{
		ncPrintChar(' ');
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void ncPrintDec(uint64_t value)
{
	ncPrintBase(value, 10);
}

void ncPrintHex(uint64_t value)
{
	ncPrintBase(value, 16);
}

void ncPrintBin(uint64_t value)
{
	ncPrintBase(value, 2);
}

void ncPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    ncPrint(buffer);
}

void ncClear()
{
	int i;

	for (i = 0; i < height * width; i++)
		video[i * 2] = ' ';
	currentVideo = video;
}


int isupdateinfprogress(){
	return timeUTC(0x0A) & 0x80;
}

void printTime(){
	while (isupdateinfprogress());
	ncPrintHex(timeUTC(0x04));
	ncPrintChar(':');
	ncPrintHex(timeUTC(0x02));
	ncPrintChar(':');
	ncPrintHex(timeUTC(0x00));
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}
