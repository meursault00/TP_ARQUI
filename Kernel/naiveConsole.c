#include <naiveConsole.h>
#include <stdio.h>
#include <video_driver.h>

#define fontSize 2
#define fontColor 0xFFFFCC

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t  *  video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static int cursorX = 1024;
static int cursorY = 16 * fontSize ;
static const uint32_t width = 80;
static const uint32_t height = 25;

extern uint64_t timeUTC(char mode);
extern int getkey();

#define IN_BOUNDS ((cursorX+fontSize*8)/1024)*16*fontSize < 736 // no termino de entender porque con 768 se pasa, REVISAR

int isupdateinfprogress(){
	return timeUTC(0x0A) & 0x80;
}

int getFontColor(){
	return fontColor;
}

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
	if(IN_BOUNDS){
		drawCursor(0x000000);
		//static int cursorX=0;
		int aux;
		aux = put_letter(character,cursorX,cursorY,fontSize,0xFFFFCC);
		cursorX = aux ;
		cursorY = (cursorX / 1024)*16*fontSize;
		//put_letter('A',cursorX,10,1,0xFFFFFF);
		drawCursor(fontColor);
	}
}

void VideoBackSpace(){
	if(cursorX != 1024){
		drawCursor(0x000000);
		cursorX -= fontSize * 8;
		cursorY = (cursorX / 1024)*16*fontSize;
		put_square(cursorX,cursorY,fontSize*8,0x000000);
		put_square(cursorX,cursorY+fontSize*8,fontSize*8,0x000000);
		drawCursor(fontColor);
	}
}

void videoPrintWord( char * string ){
	for ( int i = 0; string[i] != 0; i++ ){
		VideoPrintChar(string[i]);
	}
}

// shit may be scuffed es medio dificil testear, inaki deberia revisar esto
void clearScreen(){
	cursorX = 1024;
	cursorY = 16*fontSize;
	drawCursor;
	for ( int i = 0; i < 1024 ; i++)
		for ( int j = 0; j < 768; j++ ){
			while ( IN_BOUNDS ){
				 put_letter(' ',cursorX,cursorY,fontSize,0xFFFFCC);
			}
		}
}	

void drawCursor(int color){
	/* cursor editor de texto
	for(int i=0; i<8; i++){
		put_square(cursorX+fontSize*2,cursorY+fontSize*2*i,fontSize*2,color);
	*/
	// CURSOR TERMINAL
	put_square(cursorX,cursorY,fontSize*8,color);
	put_square(cursorX,cursorY+fontSize*8,fontSize*8,color);	
}

void VideoNewLine(){
		int aux = cursorY;
		do
		{
			VideoPrintChar(' ');
		}
		while(cursorY == aux && IN_BOUNDS);
}

void VideoPrintTime(int seconds, int minutes, int hours){
	for(int i=0; i<8; i++){
		put_square(fontSize*8*i,0,fontSize*8,0x000000);
		put_square(fontSize*8*i,fontSize*8,fontSize*8,0x000000);
	}
	while (isupdateinfprogress());
	VideoPrintHex(timeUTC(0x04),0,0,0x00FF00);
	put_letter(':',fontSize*16,0,fontSize,0x00FF00);
	VideoPrintHex(timeUTC(0x02),fontSize*24,0,0x00FF00);
	put_letter(':',fontSize*40,0,fontSize,0x00FF00);
	VideoPrintHex(timeUTC(0x00),fontSize*48,0,0x00FF00);
}

void VideoPrintHex(int value, int x, int y, int color){
	uintToBase(value,buffer,16);
	put_word(buffer,x,y,fontSize,color);
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
