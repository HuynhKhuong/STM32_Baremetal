#ifndef __SPI_H__
#define __SPI_H__

/*
@Author: Huynh Khuong
@Brief: This library is made for researching purpose
        This library is coded bare-metal. With the support CMSIS library for defining registers and peripherals 
  Specifically, This library initializes SPI peripherals and supports communication in Master side.
  For further development, It would have additional features such as communication as a slave. 

@Reference: To understand SPI, I recommend these documents: 

*/
#include "stm32f10x.h"

/*
Brief introduction about SPI architecture:
- 4 pins: MISO, MOSI (data lines); CLK (for synchronous transmission); NSS (slave select pin, this is optional)
- Configure CLK: configure when to latch data and clock speed via Baud rate configuration
- MISO, MOSI

- Data transmitting and receiving is done via a shift register only. Data flow would be transferred into Rx buffer - Tx buffer to/from 
data line.  

- SPI supports multiple interrupt lines. However, we focus on mainly 2 interrupt lines: TXE and RXNE
*/

/*
  To initialize SPI, GPIO and peripherals clock must be configured!
  Refer to GPIO.h
*/

/*
  Enums and Struct supporting drivers mechanism
*/

typedef enum{
  DIV_2  = 0,
  DIV_4  = 1,
  DIV_8  = 2,
  DIV_16 = 3,
  DIV_32 = 4,
  DIV_64 = 5,
  DIV_128 = 6,
  DIV_256 = 7,
}Baudrate_mapping;


typedef struct{
    uint8_t* transmitt_buffer;
    uint8_t* receive_buffer;
    uint8_t transmitt_buffer_length;
    uint8_t receive_buffer_length;
    uint8_t transmitt_buffer_index;
    uint8_t receive_buffer_index;
}SPI_Data_buffer;

//MACROs initializing SPI (Master mode ony)
#define SPI_configuration(SPI_BLOCK, BAUDRATE_DIV_FACTOR, CLOCK_PHASE, CLOCK_POLARITY) \
  /*SPI Peripherals, Baudrate_mapping, */\
  static void SPI_BLOCK##_Configuration(void){\
      /*Common configuration for both sides: Transmitting and Receiving*/\
      uint16_t baudrate_bit_mapping_u8 = ~(SPI_CR1_BR_0 | SPI_CR1_BR_1|SPI_CR1_BR_2);\
      uint8_t baudrate_val_u8 = BAUDRATE_DIV_FACTOR << 3;\
      (SPI_BLOCK)->CR1 &= baudrate_bit_mapping_u8;\
      (SPI_BLOCK)->CR1 |= baudrate_val_u8;\
      /*Data frame: 8-bit length, MSB 1st*/\
      (SPI_BLOCK)->CR1 |= SPI_CR1_DFF;\
      (SPI_BLOCK)->CR1 &= ~(SPI_CR1_LSBFIRST);\
      /*configure NSS pin: Software mode*/\
      /*Software mode: SSI bit, It drives the SS signal regardless regardless NSS_pin present I/O value*/\
      /*Hardware mode: is driven using SSOE */\
      (SPI_BLOCK)->CR1 |= SPI_CR1_SSM;\
      (SPI_BLOCK)->CR1 |= SPI_CR1_SSI;\
      /*Clock Phase, Polarity Configuration*/\
      if(CLOCK_PHASE == 1){\
        (SPI_BLOCK)->CR1 |= SPI_CR1_CPHA;\
      }\
      if(CLOCK_POLARITY == 1){\
        (SPI_BLOCK)->CR1 |= SPI_CR1_CPOL;\
      }\
      /*Enable SPI in master mode*/\
      (SPI_BLOCK)->CR1 |= SPI_CR1_MSTR;\
      /*Enable SPI's interrupt mechanism*/\
      __set_PRIMASK(1);\
      NVIC_EnableIRQ(SPI_BLOCK##_IRQ);\
      __set_PRIMASK(0);\
  }

#define SPI_configuration_funcall(SPI_BLOCK, NA1, NA2, NA3) \
  SPI_BLOCK##_Configuration();\

#define SPI_configuration_DECL(SPI_BLOCK, NA1, NA2, NA3) \
  void SPI_BLOCK##_Configuration(void);\
  void SPI_BLOCK##_cplt_Transmitt(void);\
  void SPI_BLOCK##_cplt_Received(void);\

//SPI peripherals setup

#define SPI_LIST(ENTRY_LIST) \
  /*SPI_peripherals_name*/ \
  /*clock frequency is 0MHz < < 4MHz*/ \
  /*By default, clock speed is 36MHz*/ \
  /*CPHA = 1, CPOL = 1*/ \
  ENTRY_LIST(SPI1, DIV_16, 1, 1)

/*Function's declarations*/ 
SPI_LIST(SPI_configuration_DECL)

void SPI_init(void);
void SPI_Write(SPI_TypeDef* SPI, uint8_t* data_u8_array, uint8_t data_length_u8);
//void SPI_read(SPI_TypeDef* SPI, uint8_t* data_u8_array, uint8_t data_length_u8);

#endif
