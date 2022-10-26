#include <time.h>
#include <naiveConsole.h>
#include <interrupts.h>
static unsigned long ticks = 0;


void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void timer_wait(int ticks) {
	
	for(int i= 0; i < ticks; i++){
		_hlt();
	}
}