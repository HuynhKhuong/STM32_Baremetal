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

//SPI peripherals declare

#define SPI_LIST(ENTRY_LIST) \
  /*SPI_peripherals_name*/ \
  /*clock frequency is 0MHz < < 4MHz*/ \
  /*By default, clock speed is 36MHz*/ \
  /*CPHA = 1, CPOL = 1*/ \
  ENTRY_LIST(SPI1, DIV_16, 1, 1)
  
#define SPI_configuration_DECL(SPI_BLOCK, NA1, NA2, NA3) \
  void SPI_BLOCK##_Configuration(void);\
  void SPI_BLOCK##_cplt_Transmitt(void);\
  void SPI_BLOCK##_cplt_Received(void);\

/*Function's declarations*/ 
SPI_LIST(SPI_configuration_DECL)

void SPI_init(void);
void SPI_Write(SPI_TypeDef* SPI, uint8_t* data_u8_array, uint8_t data_length_u8);
//void SPI_read(SPI_TypeDef* SPI, uint8_t* data_u8_array, uint8_t data_length_u8);

#endif
