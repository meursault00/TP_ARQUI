#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <video_driver.h>
#include <interrupts.h>
#include <lib.h>

#include <stdint.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_EXCEPTION_ID 6
#define MESSAGE_COLOR 0xFFFFFF
#define MESSAGE_BACKROUND 0xFF0000
#define MESSAGE_SHADOW  0x0a0a0a

void exceptionsBackupValues(uint64_t ipAdress, uint64_t stackAdress);

#endif