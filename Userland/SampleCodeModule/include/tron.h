#ifndef TRON_H_
#define TRON_H_

#include <system_calls.h>
#include <library.h>
#include <console.h>

#define BESTOF 3
#define ESC 27
#define SQUARE_SIDE 8 //largo del lado del cuadrado con el cual se dibujan las lineas

#define BOARD_WIDTH 119 // 1000 (ancho seccion pantalla usada para el juego) / SQUARE_SIDE
#define BOARD_HEIGHT 87 // 744 (alto seccion pantalla usada para el juego) / SQUARE_SIDE

// para que se imprima en la porrcion de pantalla elegida
// estaria centrada y los margenes (para poner menu y etc) serian de 12 pixeles
#define OFFSET_X 36
#define OFFSET_Y 36


#define P1_STARTING_X 60
#define P1_STARTING_Y 10
#define P2_STARTING_X 60
#define P2_STARTING_Y 70

#define P1_COLOR 0x333652 //azul
#define P2_COLOR 0xFAD02C //amarillo

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define ASC_UP    '\200'
#define ASC_DOWN  '\201'
#define ASC_LEFT  '\202'
#define ASC_RIGHT '\203'

void playTron(); //prende el tron, despues se borra

#endif