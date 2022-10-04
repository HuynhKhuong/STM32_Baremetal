#include "UART_irq.h"


/*Data container for all UART instance*/
UART_data_buffer USART1_data_container_str = {NULL, NULL, 0,0,0,0}; 
UART_data_buffer USART2_data_container_str = {NULL, NULL, 0,0,0,0}; 
UART_data_buffer USART3_data_container_str = {NULL, NULL, 0,0,0,0}; 
UART_data_buffer USART4_data_container_str = {NULL, NULL, 0,0,0,0}; 


#define UART_Communication_Handler(UART, NA1, NA2, NA3) \
    static void UART##_TXE_interrupt(void){                                                                              \
                                                                                                                        \
    /*handle if this is the last byte*/                                                                                 \
    uint8_t last_byte_u8 = UART##_data_container_str.transmitt_buffer_length - 1;                                       \
                                                                                                                        \
    if( last_byte_u8 == UART##_data_container_str.transmitt_buffer_index){                                              \
        /*last byte, reset TXE interrupt*/                                                                              \
        /*set TC interrupt*/                                                                                            \
        (UART)->CR1 &= ~(USART_CR1_TXEIE);                                                                              \
        (UART)->CR1 |= USART_CR1_TCIE;                                                                                  \
    }                                                                                                                   \
    (UART)->DR =  UART##_data_container_str.transmitt_buffer[UART##_data_container_str.transmitt_buffer_index];         \
    UART##_data_container_str.transmitt_buffer_index++;                                                                                   \
    }\
\
    static void UART##_RXE_interrupt(void){                                                                              \
    UART##_data_container_str.receive_buffer[UART##_data_container_str.receive_buffer_index] = (UART)->DR;              \
    UART##_data_container_str.receive_buffer_index++;                                                                   \
\
    if(UART##_data_container_str.receive_buffer_index == UART##_data_container_str.receive_buffer_length){              \
        UART##_data_container_str.receive_buffer = NULL;                                                                 \
        UART##_data_container_str.receive_buffer_index = 0;                                                             \
        UART##_data_container_str.receive_buffer_length = 0;                                                            \
\
        (UART)->CR1 &=  ~(USART_CR1_RE);                                                                                 \
        (UART)->CR1 &=  ~(USART_CR1_RXNEIE);                                                                             \
\
        UART##_cplt_Receive();                                                                                           \
    }                                                                                                                   \
    }                                                                                                                   \
\
    void UART##_IRQHandler(void){                                                                                       \
    uint8_t is_TXE_interrupt_u8;                                                                                        \
    uint8_t is_TC_interrupt_u8;                                                                                         \
    uint8_t is_RXNE_interrupt_u8;                                                                                       \
\
    is_TXE_interrupt_u8 = ((UART)->CR1 & USART_CR1_TXEIE) >> 7; /*7 is TXE bit position*/                               \
    is_TXE_interrupt_u8 &= ((UART)->SR & USART_SR_TXE) >> 7; /*7 is the TXE bit position*/                              \
\
    is_TC_interrupt_u8 = ((UART)->CR1 & USART_CR1_TCIE) >> 6; /*6 is TC bit position*/                                  \
    is_TC_interrupt_u8 &= ((UART)->SR & USART_SR_TC) >> 6; /*6 is TC bit positio*/                                      \
\
    is_RXNE_interrupt_u8 = ((UART)->SR & USART_SR_RXNE) >> 5; /*5 is the RXNE bit position*/                            \
    \
    if(is_TXE_interrupt_u8){                                                                                            \
        UART##_TXE_interrupt();                                                                                         \
    }                                                                                                                   \
    if(is_TC_interrupt_u8){                                                                                             \
        (UART)->CR1 &= ~(USART_CR1_TCIE); /*Disable TC interrupt*/                                                      \
        (UART)->CR1 &= ~(USART_CR1_TE); /*TE reset*/                                                                    \
        USART##_data_container_str.transmitt_buffer = NULL;                                                              \
        USART##_data_container_str.transmitt_buffer_index = 0;                                                           \
        USART##_data_container_str.transmitt_buffer_length = 0;                                                          \
        UART##_cplt_Transmitt();                                                                                        \
    }                                                                                                                   \
\
    if(is_RXNE_interrupt_u8){                                                                                           \
        UART##_RXE_interrupt();                                                                                         \
    }                                                                                                                   \
}\

UART_LIST_CONFIGURE(UART_Communication_Handler) //Functions definition
