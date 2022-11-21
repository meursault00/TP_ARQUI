#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

extern char *cpuVendor(char *result);
extern int sys_getTime(int op);

// in de mapa de entrada y salida
extern uint8_t inb( uint16_t port);
// out de mapa de entrada y salida
extern void outb( uint16_t port, uint8_t value);

uint64_t getSP();

uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
#endif

