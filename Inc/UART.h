/**
  ******************************************************************************
  * @file    UART.h
  * @author  Teddy
  * @version v1.0
  * @date    16/10/17 3:18:03 PM
  * @brief        
  ******************************************************************************
  */

#ifndef _UART_H
#define _UART_H

#include "stm32f1xx_hal.h"

#define DATA_SIZE 1024

typedef struct
{
	uint16_t iRead;
	uint16_t iWrite;
	uint16_t DataAvailable;
	uint8_t buffer[DATA_SIZE];
} UART_RX_Typedef;
// UART funtion

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;

extern UART_RX_Typedef RData_UART1;
extern UART_RX_Typedef RData_UART2;
extern UART_RX_Typedef RData_UART3;

extern uint8_t u8RcvData1;
extern uint8_t u8RcvData2;
extern uint8_t u8RcvData3;

void UART_init(UART_HandleTypeDef *uart);
void UART_sendByte(UART_HandleTypeDef* uart,uint8_t bData);
void UART_sendString(UART_HandleTypeDef *uart,uint8_t* sData);
void UART_sendNum(UART_HandleTypeDef *uart,uint16_t u16Num);

void UART_RingBuffInit(UART_HandleTypeDef *uart);
uint8_t UART_RingBuffAvailable(UART_HandleTypeDef *uart);
void UART_RingBuffGetData(UART_HandleTypeDef *uart,uint8_t *buffer,uint16_t length);
void UART_RingPrintfAllData(void);

#endif
