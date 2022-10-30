#ifndef KEYBOARD_LOADER_H
#define KEYBOARD_LOADER_H

#include <stdint.h>
#define ESC 27

extern unsigned char getkeyScancode();
extern int keyboardActive();


void storeKey();

int isShiftActivated();

int isCapsActivated();

char getKey();

char getLastChar();

void clearKeyBuffer();

void changeLanguage(int lan);

#endif