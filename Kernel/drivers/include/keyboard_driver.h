#ifndef KEYBOARD_LOADER_H
#define KEYBOARD_LOADER_H

#include <stdint.h>
#include <lib.h>

#define ESC 27
#define MAX_SCANCODE 58

#define ENGLISH 0
#define SPANISH 1
#define MAX_BUFFER 1000
#define SCANCODE_UP_ARROW 72
#define SCANCODE_DOWN_ARROW 80
#define SCANCODE_LEFT_ARROW 75
#define SCANCODE_RIGHT_ARROW 77
#define ASC_UP    '\200'
#define ASC_DOWN  '\201'
#define ASC_LEFT  '\202'
#define ASC_RIGHT '\203'
#define LSHIFT_PRESSED 0x2A          /* Scan codes for shift press, */
#define LSHIFT_RELEASED 0xAA        /* shift release and capslock  */
#define RSHIFT_PRESSED 0x36        /* keys.                       */
#define RSHIFT_RELEASED 0xB6
#define CAPSLOCK 0x3A
#define CAPSLOCK_RELEASED 0xBA 

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