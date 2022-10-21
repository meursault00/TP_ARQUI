#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>

int getFontColor();
void ncPrint(const char * string);
void printWColor(char* str,char colorcode);
void VideoPrintChar(char character);
void VideoBackSpace();
void videoPrintWord( char * string );
void drawCursor();
void VideoNewLine();
void VideoPrintTime();
void VideoPrintHex(int value,  int x, int y, int color);
void ncPrintChar(char character);
void ncNewline();
void printTime();
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncClear();
void restartCursor(); // retorna cursor a posicion inicial
void clearScreen();
#endif