#ifndef MODULELOADER_H
#define MODULELOADER_H

#include <lib.h>
#include <stdint.h>

void loadModules(void * payloadStart, void ** moduleTargetAddress);

#endif