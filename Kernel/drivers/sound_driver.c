 
//OS DEV
#include <sound_driver.h>


 //Play sound using built in speaker
static void play_sound(uint32_t nFrequence) {
	uint32_t Div;
	uint8_t tmp;

		//Set the PIT to the desired frequency
	Div = 1193180 / nFrequence;
	outb(0x43, 0xb6);
	outb(0x42, (uint8_t) (Div) );
	outb(0x42, (uint8_t) (Div >> 8));

		//And play the sound using the PC speaker
	tmp = inb(0x61);
	if (tmp != (tmp | 3)) {
		outb(0x61, tmp | 3);
	}
}

//make it shutup
static void nosound() {
	uint8_t tmp = inb(0x61) & 0xFC;

	outb(0x61, tmp);
}


static void timer_wait(uint16_t ticks) {
	for (int i = 0; i < ticks; i++){
		_hlt();
	}
}


//Make a beep
void beep() {
	play_sound(1000);
	timer_wait(10);
	nosound();
		//set_PIT_2(old_frequency);
}

//Make a beeeeeeeeeeoaoeouaioeeeeeeeeeeeep
void beeep(uint16_t nFrequence, uint16_t time) {
	play_sound(nFrequence);
	timer_wait(time);
	nosound();
		//set_PIT_2(old_frequency);
}

void soviet_anthem(){
	beeep(392 ,375 /50); 
	beeep(523 ,750 /50); 
	beeep(392 ,463 /50); 
	beeep(440 ,187 /50); 
	beeep(494 ,750 /50); 
	beeep(330 ,375 /50); 
	beeep(330 ,375 /50); 
	beeep(440 ,750 /50); 
	beeep(392 ,463 /50); 
	beeep(349 ,187 /50); 
	beeep(392 ,750 /50); 
	beeep(262 ,463 /50); 
	beeep(262 ,187 /50); 
	beeep(294 ,750 /50); 
	beeep(294 ,463 /50); 
	beeep(330 ,187 /50); 
	beeep(349 ,750 /50); 
	beeep(349 ,463 /50); 
	beeep(392 ,187 /50); 
	beeep(440 ,750 /50); 
	beeep(494 ,375 /50); 
	beeep(523 ,375 /50); 
	beeep( 587,1125/50);
}