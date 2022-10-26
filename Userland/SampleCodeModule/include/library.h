#ifndef LIB_H_
#define LIB_H_


#include <stdint.h>

static int currentCursorColor = 0;
static int fontcolor = 0x00ff44;
static int fontsize = 2;
static char buffer[64] = {0};

static int cursorX = 0; 				// por que estaba la hora
static int cursorY = 0; 			// 16 que es la cantidad de bits * fontsize

void putchar( char character, int x, int y, int size,int color);
void putword( int fd, char * string );
void printf(  char * foundation, void * parameters[]);
void print (char * foundation, ...);
char *_strrev (char *str);
char * _itoa(int i, char *strout, int base);
void strcpy( char * destination, char * origin );
void appendchar( char character );
void printInt(uint64_t integer );
int countDigits( int number );
void numLoader( int number, char * buffer, int digits );
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
void intToString( int number, char * buffer, int digits );
void floatToString( float number, char * buffer, int digits  );

void putnewline( void );
void newline();
void backspace();
void changeFontSize(int newSize);
char streql( const char * str1,const char * str2 );
int strcmp(const char* s1, const char* s2);
int strlen(const char *str);

void appendstring( char * string );

void drawCursor(int color);
void restartCursor();
void refreshCursor();

#endif