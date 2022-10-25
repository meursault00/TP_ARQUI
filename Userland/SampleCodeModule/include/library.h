#ifndef LIB_H_
#define LIB_H_


#include <stdint.h>

uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
void putchar( int fd, char character);
void putword( int fd, char * string );
void printf( char * foundation, void ** parameters);
int countDigits( int number );
void numLoader( int number, char * buffer, int digits );
void intToString( int number, char * buffer, int digits );
void floatToString( float number, char * buffer, int digits  );
void putnewline( void );

#endif