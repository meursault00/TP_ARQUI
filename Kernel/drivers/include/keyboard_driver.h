#ifndef KEYBOARD_LOADER_H
#define KEYBOARD_LOADER_H

#include <stdint.h>
#define ESC 27

extern unsigned char getkeyScancode();
extern int keyboardActive();


int storeKey();

int isShiftActivated();

int isCapsActivated();

char getKey();


#endif