#include "main.h"
#include "UART.h"
#include "string.h"
#include "DEBUG_PC.h"


void DEBUG_SendByte(uint8_t u8byte)
{
	UART_sendByte(&uart_debug,u8byte);
}
void DEBUG_SendString(uint8_t *u8String)
{
  UART_sendString(&uart_debug,u8String);
}
void DEBUG_SendNum(uint16_t _number)
{
	if (_number >= 10000) { 	// 5 char
		DEBUG_SendByte((_number/10000) + '0' );
		DEBUG_SendByte(((_number/1000) % 10 )+ '0' );
		DEBUG_SendByte(((_number/100) % 10 )+ '0' );
		DEBUG_SendByte(((_number/10) % 10 )+ '0' );
		DEBUG_SendByte((_number % 10 )+ '0' );
	}
	else if (_number >= 1000) { 	// 4 char
		DEBUG_SendByte(((_number/1000))+ '0' );
		DEBUG_SendByte(((_number/100) % 10 )+ '0' );
		DEBUG_SendByte(((_number/10) % 10 )+ '0' );
		DEBUG_SendByte((_number % 10 )+ '0' );
	}
	else if (_number >= 100) {	 // 3 char
		DEBUG_SendByte(((_number/100) )+ '0' );
		DEBUG_SendByte(((_number/10) % 10 )+ '0' );
		DEBUG_SendByte((_number % 10 )+ '0' );
	}
	else if (_number >= 10) { 	// 2 char
		DEBUG_SendByte(((_number/10))+ '0' );
		DEBUG_SendByte((_number % 10 )+ '0' );
	}
	else {					// 1 char
		DEBUG_SendByte(_number+ '0' );
	}
}
void DEBUG_BufferAvailable(void)
{
  UART_RingBuffAvailable(&uart_debug);
}
void DEBUG_GetBuffer( uint8_t *buffer, uint16_t length)
{
  UART_RingBuffGetData(&uart_debug,buffer,length);
}