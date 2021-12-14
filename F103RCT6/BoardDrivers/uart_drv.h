#ifndef __UART_DRV__
#define __UART_DRV__
#include "main.h"
#include "usart.h"

#define UART4_RXBUFFERSIZE 64

extern uint8_t UART4_RX_Buffer[UART4_RXBUFFERSIZE];
extern uint8_t UART4_RX_Ready;
extern uint8_t UART4_RX_Num;

void USER_UART4_Init(void);
void USER_UART4_IRQHandler(void);
void USER_UART4_IRQHandler_Post(void);
void UART4_ResetFlags(void);

#endif
