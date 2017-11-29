#ifndef _DEBUG_PC_H
#define _DEBUG_PC_H

#include "stm32f1xx_hal.h"
#define uart_debug huart2

void DEBUG_SendByte(uint8_t u8byte);
void DEBUG_SendString(uint8_t *u8String);
void DEBUG_BufferAvailable(void);
void DEBUG_GetBuffer( uint8_t *buffer, uint16_t length);

#endif
