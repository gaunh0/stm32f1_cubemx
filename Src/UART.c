/**
  ******************************************************************************
  * @file    UART.c
  * @author  Teddy
  * @version v1.0
  * @date    16/10/17 3:17:57 PM
  * @brief        
  ******************************************************************************
  */
	
#include <stdio.h>
#include "string.h"
#include "UART.h"
	
	#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

uint8_t u8RcvData1 = '\000';
uint8_t u8RcvData2 = '\000';
uint8_t u8RcvData3 = '\000';
uint8_t i;
UART_RX_Typedef RData_UART1;
UART_RX_Typedef RData_UART2;
UART_RX_Typedef RData_UART3;


void UART_init(UART_HandleTypeDef *uart)
{
	__HAL_UART_FLUSH_DRREGISTER(uart);
	switch ((uint32_t)uart->Instance)
	{
		case ((uint32_t) USART1):
			HAL_UART_Receive_DMA(uart,&u8RcvData1,1);
			break;
			
		case ((uint32_t) USART2):
			HAL_UART_Receive_DMA(uart,&u8RcvData2,1);
			break;

		case ((uint32_t) USART3):
			HAL_UART_Receive_DMA(uart,&u8RcvData3,1);
			break;
		default:
			break;
	}
}

void UART_sendByte(UART_HandleTypeDef* uart,uint8_t bData)
{
	HAL_UART_Transmit(uart,&bData,1,0xFFFF);
}
void UART_sendString(UART_HandleTypeDef *uart,uint8_t* sData)
{
  HAL_UART_Transmit(uart ,sData,strlen(sData),2000);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	switch((uint32_t)huart->Instance)
	{
		case ((uint32_t) USART1):
			RData_UART1.buffer[RData_UART1.iWrite] = u8RcvData1;
			__HAL_UART_FLUSH_DRREGISTER(huart);
			RData_UART1.iWrite=(RData_UART1.iWrite+1)% DATA_SIZE; 
			if (++RData_UART1.DataAvailable == DATA_SIZE) 
				RData_UART1.DataAvailable=0;			
			break;
			
		case ((uint32_t) USART2):
			RData_UART2.buffer[RData_UART2.iWrite] = u8RcvData2;
			__HAL_UART_FLUSH_DRREGISTER(huart);
			RData_UART2.iWrite=(RData_UART2.iWrite+1)% DATA_SIZE; 
			if (++RData_UART2.DataAvailable == DATA_SIZE) 
				RData_UART2.DataAvailable=0;	
			break;

		case ((uint32_t) USART3):
			RData_UART3.buffer[RData_UART3.iWrite] = u8RcvData3;
			__HAL_UART_FLUSH_DRREGISTER(huart);
			RData_UART3.iWrite=(RData_UART3.iWrite+1)% DATA_SIZE; 
			if (++RData_UART3.DataAvailable == DATA_SIZE) 
				RData_UART3.DataAvailable=0;	
			break;
		default: 
			break;
  }
}
void UART_RingBuffInit(UART_HandleTypeDef * uart)
{
	switch ((uint32_t)uart->Instance)
	{
		case (uint32_t) USART1:
			RData_UART1.iRead = 0;
			RData_UART1.iWrite = 0;
		  RData_UART1.DataAvailable = 0;
			memset(RData_UART1.buffer,0,DATA_SIZE);
			break;
			
		case (uint32_t) USART2:
			RData_UART2.iRead = 0;
			RData_UART2.iWrite = 0;
		  RData_UART2.DataAvailable = 0;
			memset(RData_UART2.buffer,0,DATA_SIZE);
			break;

		case (uint32_t) USART3:
			RData_UART3.iRead = 0;
			RData_UART3.iWrite = 0;
		  RData_UART3.DataAvailable = 0;
			memset(RData_UART3.buffer,0,DATA_SIZE);
			break;
		default: 
			break;
	}

}
uint8_t UART_RingBuffAvailable(UART_HandleTypeDef * uart)
{
	uint8_t u8ReturnValue;
	switch ((uint32_t)uart->Instance)
	{
		case (uint32_t) USART1:
			u8ReturnValue = RData_UART1.DataAvailable;
			break;

		case (uint32_t) USART2:
			u8ReturnValue = RData_UART2.DataAvailable;
			break;

		case (uint32_t) USART3:
			u8ReturnValue = RData_UART3.DataAvailable;
			break;
		default: 
			u8ReturnValue = 0;
		  break;
	}	
	return RData_UART2.DataAvailable;;
}
void UART_RingBuffGetData(UART_HandleTypeDef * uart, uint8_t * buffer, uint16_t length)
{
	uint16_t tmp_length=0;
	switch ( (uint32_t)uart->Instance )
	{
		case (uint32_t)USART1:
			while (tmp_length< length)
			{
				*(buffer + tmp_length) = RData_UART1.buffer[RData_UART1.iRead];
				RData_UART1.DataAvailable--;
				RData_UART1.iRead = (RData_UART1.iRead+ 1) % DATA_SIZE;
				if (RData_UART1.iRead == RData_UART1.iWrite)
				{
					RData_UART1.DataAvailable = 0;
					break;
				}
				tmp_length++;
			}
			break;
		case (uint32_t)USART2:
			while (tmp_length< length)
			{
				*(buffer + tmp_length) = RData_UART2.buffer[RData_UART2.iRead];
				RData_UART2.DataAvailable--;
				RData_UART2.iRead = (RData_UART2.iRead+ 1) % DATA_SIZE;
				if (RData_UART2.iRead == RData_UART2.iWrite)
				{
					RData_UART2.DataAvailable = 0;
					break;
				}
				tmp_length++;
			}
			break;
		case (uint32_t)USART3:
			while (tmp_length< length)
			{
				*(buffer + tmp_length) = RData_UART3.buffer[RData_UART3.iRead];
				RData_UART3.DataAvailable--;
				RData_UART3.iRead = (RData_UART3.iRead+ 1) % DATA_SIZE;
				if (RData_UART3.iRead == RData_UART3.iWrite)
				{
					RData_UART3.DataAvailable = 0;
					break;
				}
				tmp_length++;
			}
			break;
		default:
			break;
	}
}

