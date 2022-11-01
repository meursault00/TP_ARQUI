#ifndef CONSOLE_H_
#define CONSOLE_H_


#include <library.h>
#include <system_calls.h>
#include <tron.h>
#include <keyboardPiano.h>

extern char* snapshot();


//BUFFER DE COMANDOS PARA PODER HACER SCROLLING EN HISTORIAL DE EJECUCION
#define MAX_COMMAND_LENGTH 512
#define MAX_COMMANDS 512
#define MAX_CONSOLE_BUFFER 512

//TECLAS
#define BACKSPACE 8
#define ESC 27
#define ENTER 10
#define ASC_UP    '\200'
#define ASC_DOWN  '\201'
#define ASC_LEFT  '\202'
#define ASC_RIGHT '\203'

//hashcodes de los strings comandos en mayuscula
#define HELP 2089138798
#define TRON 2089584296
#define CLEAR 216417516
#define BEEP 2088922945
#define ANTHEM 2771458114
#define SNAPSHOT 650087221
#define TIME 2089574420
#define INVOP 223623889
#define DIVCERO 649756593
#define MEMACCESS 1829689142
#define PIANO 231722748
#define UPSIZE 235307403 // "size+"
#define DOWNSIZE 235307405
#define LANG_ES 3115062494 // lange=es
#define LANG_EN 3115062489
#define LANGUAGE 3857633481 // for help
#define SIZE 2089538912 // for help
#define INFOREG 2989276335


void checkCommand();
void checkKey( char c );

#endif