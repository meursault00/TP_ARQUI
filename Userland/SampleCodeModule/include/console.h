#ifndef CONSOLE_H_
#define CONSOLE_H_

#define BACKSPACE 8
#define ESC 27
#define ENTER 10

extern char* snapshot();

#define MAX_CONSOLE_BUFFER 256
static char consoleBuffer[MAX_CONSOLE_BUFFER] = {0};
static char snapshotBuffer[128] = {0};
static int lastChar = 0;

void memMoveChar( char* array1, char* array2, int charsToMove );
char strcmp2( const char* stringA,const char* stringB);
void checkCommand();
void commandHelp();
void commandSnapshot();
void commandClear();
void commandTron();
void printRegisters();
char toHex( char character );
char *toUpper(char * string);
void clearScreen();
void checkKey( char c );
void printCurrentTime();
void printRTC(int code);
void commandMemAccess( char * memdirHexa);
void printAddress( unsigned char * address );

#endif