#ifndef __UART_IRQ_PC_H__
#define __UART_IRQ_PC_H__

#include "stm32f10x.h"
#include "UART.h"

/* Datatype for lowlayer buffers for transmitting and receiving */
typedef struct{
    uint8_t* transmitt_buffer;
    uint8_t* receive_buffer;
    uint8_t transmitt_buffer_length;
    uint8_t receive_buffer_length;
    uint8_t transmitt_buffer_index;
    uint8_t receive_buffer_index;
}UART_data_buffer;

extern UART_data_buffer USART1_data_container_str; 
extern UART_data_buffer USART2_data_container_str; 
extern UART_data_buffer USART3_data_container_str;  
extern UART_data_buffer USART4_data_container_str;  

/* Interrupt registeration*/
// list is declared in UART.h

#define USERS_IRQ_HANDLE_DECL(UART, NA1, NA2, NA3) \
    void UART##_cplt_Transmitt(void);\
    void UART##_cplt_Receive(void);\

#endif 