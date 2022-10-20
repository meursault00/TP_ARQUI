#include <time.h>
#include <naiveConsole.h>

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

void timer_handler() {
	ticks++;

	cursor_handler();

	clock_handler();
	
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void cursor_handler(){
	if(ticks == cursorTicks){
		if(actualColor == getFontColor())
			actualColor = 0x000000;
		else
			actualColor = getFontColor();
		drawCursor(actualColor);
		cursorTicks += 9;	
	}
}

void clock_handler(){
	if(seconds_elapsed() > actualSeconds){
		VideoPrintTime();
		actualSeconds = seconds_elapsed();
	}
}
