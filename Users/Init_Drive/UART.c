#include "UART.h"
#include <stdio.h>
/*
@Author: Huynh Khuong
@Brief: Function's definitions of UART library
*/
/*Data container for all UART instance*/
UART_data_buffer USART1_data_container_str = {NULL, NULL, 0,0,0,0}; 
static UART_data_buffer USART2_data_container_str = {NULL, NULL, 0,0,0,0}; 
static UART_data_buffer USART3_data_container_str = {NULL, NULL, 0,0,0,0}; 
static UART_data_buffer USART4_data_container_str = {NULL, NULL, 0,0,0,0}; 
uint32_t fractional_part_u32, mantisa_part_u32, brr_result_u32;

UART_LIST_CONFIGURE(UART_Configuration)

void UART_init(){
  UART_LIST_CONFIGURE(UART_configure_funcall)
}

/*
UART_Transmitt
@Brief: This function transmit data with explicit data_length
        Its mechanism is to make use of the 2 Interrupt request types: TCE and TXE
        - TXE is used to transmit each byte and is hidden from users
        - TCE is used to announce user that transmission is done
        It would invoke UART_cplt_Trasmitt to do user's task
*/
void UART_Transmitt(USART_TypeDef *UART, uint8_t* data_u8_array, uint8_t data_length_u8){
  //Update UART_buffer_container
  /*First you have to declare UART's data container right here*/
  USART1_data_container_str.transmitt_buffer = data_u8_array;
  USART1_data_container_str.transmitt_buffer_length = data_length_u8;

  /*
    Transmit workflow
    1. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
      At the first time UART transmission is enabled, its TXE bit is set immediately.
      Note:
      The TE bit should not be reset during transmission of data. Resetting the TE bit during the
      transmission will corrupt the data on the TX pin as the baud rate counters will get frozen.
      The current data being transmitted will be lost.
      An idle frame will be sent after the TE bit is enabled

    2. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
      for each data to be transmitted in case of single buffer.

    3. After writing the last data into the USART_DR register, wait until TC=1. This indicates
      that the transmission of the last frame is complete. 

      TC bit is set by hardware if the transmission of a frame containing data is complete (and if TXE is set). 
      
      In addition, an interrupt is generated if TCIE=1 in the USART_CR1 register. 
      It is cleared by a software sequence (a read from the USART_SR register followed by a write to the
      USART_DR register).
      The TC bit can also be cleared by writing a '0' to it. This clearing sequence is recommended only for multibuffer communication.
  */

  UART->CR1 |=  USART_CR1_TE;
  UART->CR1 |=  USART_CR1_TXEIE; //We make use of TXE interrupt to transmit multiple data bytes
}


/*
UART_Receive
@Brief: This function receive data with explicit data_length
        Its mechanism is to make use of the 2 Interrupt request types: RCE and TXE
        - RXNE is used to indicate that the content of shift register is transferred into RDR
        - Clearing RXNE is cleared by a software read to the Data_buffer, it can also be reset by writing a zero to it
        - It must be cleared before the end of the reception of the next character
        RE bit should not be reset while receiving data.
*/
void UART_Receive(USART_TypeDef *UART, uint8_t* data_u8_array, uint8_t data_length_u8){
  //Update UART_buffer_container
  /*First you have to declare UART's data container right here*/
  USART1_data_container_str.receive_buffer = data_u8_array;
  USART1_data_container_str.receive_buffer_length = data_length_u8;

  /*
    Receive workflow
    1. Set the RE bit in USART_CR1. This enables the receiver which begins searching for a start bit.
    2. RXNE is used to indicate that the content of shift register is transferred into RDR
       Clearing RXNE is cleared by a software read to the Data_buffer, it can also be reset by writing a zero to it
  */

  UART->CR1 |=  USART_CR1_RE;
  UART->CR1 |=  USART_CR1_RXNEIE; 
}

/*Interrupt handler*/
  UART_LIST_CONFIGURE(UART_Communication_Handler)

  void USART1_cplt_Transmitt(void){                                                                                 
    /*This function would only be called when the last byte is transmitted*/                                           
    USART1->CR1 &= ~(USART_CR1_TCIE); /*Disable TC interrupt*/                                                          
    USART1->CR1 &= ~(USART_CR1_TE); /*TE reset*/                                                                        

    USART1_data_container_str.transmitt_buffer = NULL;                                                                 
    USART1_data_container_str.transmitt_buffer_index = 0;                                                               
    USART1_data_container_str.transmitt_buffer_length = 0;                                                              

    /*User's code*/

  }
  void USART1_cplt_Receive(void){                                                                                      

    /*This function would only be called when the last byte is transmitted*/                                            
    USART1_data_container_str.receive_buffer = NULL;                                                                    
    USART1_data_container_str.receive_buffer_index = 0;                                                                
    USART1_data_container_str.receive_buffer_length = 0;                                                               

    USART1->CR1 &=  ~(USART_CR1_RE);                                                                                    
    USART1->CR1 &=  ~(USART_CR1_RXNEIE);                                                                                

    /*User's code*/\
    UART_Receive(USART1, &DUMMY_RECEIVE[0], 11);                                                                    
  }                                                                                                                   
                                                         
