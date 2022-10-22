#include <time.h>
#include <naiveConsole.h>
#include <tron.h>

static unsigned long ticks = 0;
static unsigned long cursorTicks = 9;
static int actualColor = 0x000000;
static int actualSeconds = -1;

#define SECONDS 0
#define MINUTES 2
#define HOURS 4

extern timeUTC(int op);

static void cursor_handler();
static void clock_handler();
static void tron_handler();

void timer_handler() {
	ticks++;

	if(tronOn())
		tron_handler();
	else{ // si no esta prendido el tron habilito terminal como vista hasta ahora
		clock_handler();
			cursor_handler();
	}
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void cursor_handler(){
	// doy la ilusion de titilacion al imprimir el cursor negro y blanco en intervalos alternantes
	if(ticks == cursorTicks){
		if(actualColor == getFontColor())
			actualColor = 0x000000;
		else
			actualColor = getFontColor();
		drawCursor(actualColor);
		cursorTicks += 9; // 0,5 segundos
	}
}

void clock_handler(){
	if(seconds_elapsed() > actualSeconds){ //reimprimo el reloj cada segundo
		videoPrintTime();
		actualSeconds = seconds_elapsed();
	}
}

void tron_handler(){
	if(ticks % 9 == 0) // dictara la velocidad
		movePlayers();
} // aca me tira dos errores pero lo mas probable es que sea un bug del visual
