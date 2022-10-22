#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>
#include <video_driver.h>

//retorna el fontColor
int getFontColor();
//Printear caracteres con color default o color especial
void videoPrintChar(char character);
void videoPrintCharWColor(char character,int color);

//Printear palabras con color default o color especial
void videoPrintWord( char * string );
void videoPrintWordWColor( char * string ,int color);

//printear valores diferentes
void videoPrintHex(int value,  int x, int y, int color);
void videoPrintHexa(int value);
void videoPrintDec(uint64_t value);
void videoPrintBin(uint64_t value);
void videoPrintBase(uint64_t value, uint32_t base);

//diferentes funciones que 
void videoBackSpace(); // vuelve una posicion para atras
void drawCursor(); // dibuja el cursor en posicion actual
void videoNewLine(); // salto de linea
void videoPrintTime(); // imprime tiempo
void restartCursor(); // retorna cursor a posicion inicial
void clearScreen(); // clear screen 
#endif