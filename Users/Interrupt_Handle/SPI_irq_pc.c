#include "SPI_irq_pc.h"
#include <stdio.h>

//Data container
SPI_Data_buffer SPI1_data_container_str = {NULL, NULL, 0,0,0,0}; 
SPI_Data_buffer SPI2_data_container_str = {NULL, NULL, 0,0,0,0}; 

//Interrupt handler supported by MCU
#define SPI_Communication_Handler(SPI_BLOCK, NA1, NA2, NA3)                           \
                                                                                      \
/*Static function handles the process in the middle of communication*/                \
static void SPI_BLOCK##_TXE_interrupt(void){                                          \
    /*handle if this is the last byte*/                                               \
    uint8_t finished_transmitted_u8 = (SPI_BLOCK##_data_container_str.transmitt_buffer_length == SPI_BLOCK##_data_container_str.transmitt_buffer_index); \
    if(finished_transmitted_u8){                                                      \
      /*finished transmit, call cplt call-back function*/                               \
      /*Complete transmitt Via SPI, disable the communication and interrupt as well*/   \
      uint8_t is_busy_u8 = 1;                                                           \
      while(is_busy_u8){                                                                \
        /*Wait until busy flag is reset*/                                                 \
        is_busy_u8 = (SPI1->SR & SPI_SR_BSY) >> 7; /*7 is bit position of BUSY FLASG*/    \
      }\
      (SPI_BLOCK)->CR1 &= ~(SPI_CR1_SPE);                                                 \
      (SPI_BLOCK)->CR2 &= ~(SPI_CR2_TXEIE);                                               \
      /*Clear data container*/                                                            \
      SPI_BLOCK##_data_container_str.transmitt_buffer = NULL;                              \
      SPI_BLOCK##_data_container_str.transmitt_buffer_length = 0;                         \
      SPI_BLOCK##_data_container_str.transmitt_buffer_index = 0;                          \
      SPI_BLOCK##_cplt_Transmitt();                                                   \
    }                                                                                 \
    else{                                                                             \
      (SPI_BLOCK)->DR =  SPI_BLOCK##_data_container_str.transmitt_buffer[SPI_BLOCK##_data_container_str.transmitt_buffer_index]; \
      SPI_BLOCK##_data_container_str.transmitt_buffer_index++;                        \
    }                                                                                 \
}                                                                                     \
  void SPI_BLOCK##_IRQHandler(void){                                                  \
    /*Check Rx or Tx interrupt*/                                                        \
    uint8_t isTxInterrupt_u8;                                                       \
    uint8_t isRxInterrupt_u8;                                                       \
                                                                                    \
    isTxInterrupt_u8 = ((SPI1->SR) & 0x02) >> 1; /*bit 1 is TXE interrupt*/         \
    isRxInterrupt_u8 = ((SPI1->SR) & 0x01); /*bit 0 is RXNE interrupt*/             \
                                                                                    \
    if(isTxInterrupt_u8){                                                           \
      SPI_BLOCK##_TXE_interrupt();                                                  \
    }                                                                               \
}

SPI_LIST(SPI_Communication_Handler) //Handle interrupt for defined SPI peripherals
