#ifndef SOUND_LOADER_H
#define SOUND_LOADER_H

#include <lib.h>
#include <stdint.h>
#include <interrupts.h>

void beep();
void beeep(uint16_t nFrequence, uint16_t time);
#endif