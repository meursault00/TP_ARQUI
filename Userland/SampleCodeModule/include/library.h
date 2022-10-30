#ifndef LIB_H_
#define LIB_H_


#include <system_calls.h>
#include <stdint.h>
#include <system_calls.h>
#include <stdarg.h>

#define BACKGROUND_COLOR 0x002B36
#define USER_TEXT_COLOR 0x95CD28
#define TERMINAL_BLUE 0x12488B
#define ORANGY 0xF66151
#define RED 0xC01C28
static int fontcolor = 0xBFECF1;
static int currentCursorColor = 0x002B36;

static int fontsize = 2;
static char buffer[64] = {0};

static int cursorX = 4; 				// por que estaba la hora
static int cursorY = 4; 			// 16 que es la cantidad de bits * fontsize

void scanf(char * format, void * parameters[]);
void setCursor( int x, int y );
int lastEnter();

unsigned char inthextoa( unsigned char a );
unsigned char atointhex( unsigned char a);
void putchar(char c);
void putcharSpecifics( char character, int x, int y, int size,int color);
void putstringSpecifics(char * string, int x, int y, int size, int color);
void putword( int fd, char * string );
void printf(  char * foundation, void * parameters[]);
void printInt(uint64_t );
void printHex(uint64_t );
void println(char * string);
void print (char * foundation, ...);
void printColor(char * foundation, int color, ...);

char * strrev (char *str);
char * itoa(int i, char *strout, int base);
void strcpy( char * destination, char * origin );
void appendchar( char character );
int countDigits( int number );
void numLoader( int number, char * buffer, int digits );
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
void intToString( int number, char * buffer, int digits );
void floatToString( float number, char * buffer, int digits  );

void rollLeft();
void putnewline( void );
void newline();
void backspace();
void changeFontSize(int newSize);
char streql( const char * str1,const char * str2 );
int strcmp(const char* s1, const char* s2);
int strlen(const char *str);

void appendstring( char * string );
void appendstringColor(char * string, int color);
char isHexChar( char character );
char onlyHexChars( char * string );
void splitString( char * original, char * firstSplit, char splitter );
void drawCursor(int color);
void restartCursor();
void refreshCursor();
int pow(int base, unsigned int exp);
uint64_t hexstringToInt(char * s);
unsigned char hexToChar( unsigned char a, unsigned char b );
void memCopy( char * pointer1, char * pointer2, int chars );
int scan (char * str, ...);

#endif