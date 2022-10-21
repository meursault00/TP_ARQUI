#ifndef VIDEO_LOADER_H
#define VIDEO_LOADER_H

#include <stdint.h>

void put_pixel(uint32_t x , uint32_t y, uint32_t color);
int put_letter( char letter, uint32_t x , uint32_t y,uint32_t tam, uint32_t color);
void put_square(uint32_t x , uint32_t y,uint32_t tam, uint32_t color);
void put_word( char * string, uint32_t x , uint32_t y,uint32_t tam, uint32_t color);
void VideoClearScreen();

#endif