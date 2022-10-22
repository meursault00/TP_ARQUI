#include <naiveConsole.h>
#include <stdio.h>
#include <video_driver.h>

#define FONTSIZE 1
#define FONTCOLOR 0xFFFFCC

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };

static int cursorX = 1024;
static int cursorY = 16 * FONTSIZE ;
static const uint32_t width = 80;
static const uint32_t height = 25;

extern uint64_t timeUTC(char mode);
extern int getkey();

#define IN_BOUNDS ((cursorX+FONTSIZE*8)/1024)*16*FONTSIZE < 736 // no termino de entender porque con 768 se pasa, REVISAR

int isupdateinfprogress(){
	return timeUTC(0x0A) & 0x80;
}

int getFontColor(){
	return FONTCOLOR;
}

void videoPrintCharWColor(char character,int color){
	if(IN_BOUNDS){
		drawCursor(0x000000);
		//static int cursorX=0;
		int aux;
		aux = put_letter(character,cursorX,cursorY,FONTSIZE,color);
		cursorX = aux ;
		cursorY = (cursorX / 1024)*16*FONTSIZE;
		//put_letter('A',cursorX,10,1,0xFFFFFF);
		drawCursor(FONTCOLOR);
	}
}

void videoPrintChar(char character){
	videoPrintCharWColor(character,FONTCOLOR);
}



void videoBackSpace(){
	if(cursorX != 1024){
		drawCursor(0x000000);
		cursorX -= FONTSIZE * 8;
		cursorY = (cursorX / 1024)*16*FONTSIZE;
		put_square(cursorX,cursorY,FONTSIZE*8,0x000000);
		put_square(cursorX,cursorY+FONTSIZE*8,FONTSIZE*8,0x000000);
		drawCursor(FONTCOLOR);
	}
}

void videoPrintWord( char * string ){
	for ( int i = 0; string[i] != 0; i++ ){
		videoPrintChar(string[i]);
	}
}

void videoPrintWordWColor( char * string ,int color){
	for(int i=0;string[i]!='\0';i++){
		videoPrintCharWColor(string[i],color);
	}
}

// shit may be scuffed es medio dificil testear, inaki deberia revisar esto

void clearScreen(){
	put_square(0, 16*FONTSIZE, 2000, 0x000000);//put_square(0, 16*FONTSIZE, 1280, 0x000000);
	restartCursor();
}


void drawCursor(int color){
	/* cursor editor de texto
	for(int i=0; i<8; i++){
		put_square(cursorX+fontSize*2,cursorY+fontSize*2*i,fontSize*2,color);
	*/
	// CURSOR TERMINAL
	put_square(cursorX,cursorY,FONTSIZE*8,color);
	put_square(cursorX,cursorY+FONTSIZE*8,FONTSIZE*8,color);	
}

void videoNewLine(){
		int aux = cursorY;
		do
		{
			videoPrintChar(' ');
		}
		while(cursorY == aux && IN_BOUNDS);
}

void videoPrintTime(int seconds, int minutes, int hours){
    for(int i=0; i<8; i++){
        put_square(FONTSIZE*8*i,0,FONTSIZE*8,0x000000);
        put_square(FONTSIZE*8*i,FONTSIZE*8,FONTSIZE*8,0x000000);
    }
    while (isupdateinfprogress());

    if(timeUTC(0x04) < 10){
        videoPrintHex(0, 0, 0,0x00FF00 );
        videoPrintHex(timeUTC(0x04), 16, 0,0x00FF00 );    
    }
    else{
        videoPrintHex(timeUTC(0x04), 0, 0,0x00FF00 );
    }
    put_letter(':',FONTSIZE*16,0,FONTSIZE,0x00FF00);
    if(timeUTC(0x02) < 10){
        videoPrintHex(0, FONTSIZE*24, 0,0x00FF00 );
        videoPrintHex(timeUTC(0x02), FONTSIZE *32, 0,0x00FF00 );    
    }
    else{
        videoPrintHex(timeUTC(0x02), FONTSIZE*24, 0,0x00FF00 );
    }
    put_letter(':',FONTSIZE*40,0,FONTSIZE,0x00FF00);
    if(timeUTC(0x00) < 10){
        videoPrintHex(0, FONTSIZE*48, 0,0x00FF00 );
        videoPrintHex(timeUTC(0x00), FONTSIZE*56, 0,0x00FF00 );
    }
    else{
        videoPrintHex(timeUTC(0x00), FONTSIZE*48, 0,0x00FF00 );
    }
}

void videoPrintHex(int value, int x, int y, int color){
	uintToBase(value,buffer,16);
	put_word(buffer,x,y,FONTSIZE,color);
}



void videoPrintHexa(int value){
	videoPrintHex(value,cursorX,cursorY,FONTCOLOR);
}

void videoPrintDec(uint64_t value)
{
	videoPrintBase(value, 10);
}


void videoPrintBin(uint64_t value)
{
	videoPrintBase(value, 2);
}

void videoPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    videoPrintWord(buffer);
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

void restartCursor(){
	cursorX = 1024;
	cursorY = 16*FONTSIZE;
}
