#ifndef SYSTEM_CALLS_H
#define SYSTEM_CALLS_H


extern void write(char character, int x, int y, int size, int color);
extern char getchar();
extern int gettick();
extern void halt();
extern void putSquare(int x,int y,int tam,int color);
extern int getTime(int code);
extern char getLastKey();
extern void getRegisters(char * registers);
extern void beep(int freq, int time);
extern void sleep(int seconds);
extern void clearkeybuffer();
extern void changelanguage(int lan);
#endif