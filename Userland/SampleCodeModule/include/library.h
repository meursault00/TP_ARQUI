#ifndef LIB_H_
#define LIB_H_


#include <system_calls.h>
#include <stdint.h>
#include <stdarg.h>

#define BACKGROUND_COLOR 0x002B36
#define USER_TEXT_COLOR 0x95CD28
#define TERMINAL_BLUE 0x12488B
#define ORANGY 0xF66151
#define RED 0xC01C28
#define FONTCOLOR 0xBFECF1
#define CURRENT_CURSOR_COLOR 0x002B36

// stdio
int scan (char * str, ...);
void print (char * foundation, ...);
void printColor(char * foundation, int color, ...);
void printf(  char * foundation, void * parameters[]);
void putchar(char c);
void println(char * string);
void putcharSpecifics( char character, int x, int y, int size,int color);
void putstringSpecifics(char * string, int x, int y, int size, int color);
void putword( int fd, char * string );
void printInt(uint64_t );
void printHex(uint64_t );
void appendchar( char character );
void appendstring( char * string );
void appendstringColor(char * string, int color);

// string
void strcpy( char * destination,const char * origin );
char streql( const char * str1,const char * str2 );
int strcmp(const char* s1, const char* s2);
int strlen(const char *str);
char * strrev (char *str);
void splitString( char * original, char * firstSplit, char splitter );
void memCopy( char * pointer1, char * pointer2, int chars );


// stdlib
unsigned char inthextoa( unsigned char a );
unsigned char atointhex( unsigned char a);
char * itoa(int i, char *strout, int base);
int countDigits( int number );
void numLoader( int number, char * buffer, int digits );
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
void intToString( int number, char * buffer, int digits );
void floatToString( float number, char * buffer, int digits  );
uint64_t hexstringToInt(char * s);
unsigned char hexToChar( unsigned char a, unsigned char b );
int pow(int base, unsigned int exp);
char onlyHexChars( char * string );
char isHexChar( char character );

// consoleControl
int canWrite();
void setCursor( int x, int y );
int lastEnter();
void rollLeft();
void putnewline( void );
void newline();
void backspace();
void changeFontSize(int newSize);
void drawCursor(int color);
void restartCursor();
void refreshCursor();



#endif