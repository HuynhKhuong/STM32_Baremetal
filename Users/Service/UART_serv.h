#ifndef __UART_SERV_H__
#define __UART_SERV_H__

#include "UART_irq_pc.h"

void UART_Transmitt(USART_TypeDef *UART, uint8_t* data_u8_array, uint8_t data_length_u8);
void UART_Receive(USART_TypeDef *UART, uint8_t* data_u8_array, uint8_t data_length_u8);

#endif 