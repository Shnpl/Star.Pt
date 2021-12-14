#ifndef __UART_INIT__
#define __UART_INIT__
#include "main.h"
#include "usart.h"
void USER_UART4_Init(void);
#define UART4_RXBUFFERSIZE 64
extern uint8_t UART4_RX_BUF[UART4_RXBUFFERSIZE];
extern uint8_t  UART4_HAL_RxBuffer[UART4_RXBUFFERSIZE];
#endif