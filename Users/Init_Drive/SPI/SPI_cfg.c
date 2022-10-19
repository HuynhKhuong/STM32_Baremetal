#include "SPI.h"
#include "Nokia_5110_LCD.h"
#include <stdio.h>

#define SPI_MASTER(SPI_BLOCK) \
  /*configure NSS pin: Software mode*/\
  /*Software mode: SSI bit, It drives the SS signal regardless NSS_pin's present I/O value*/\
  /*Hardware mode: is driven using SSOE */\
    (SPI_BLOCK)->CR1 |= SPI_CR1_SSM;\
    (SPI_BLOCK)->CR1 |= SPI_CR1_SSI;\
    /*Enable SPI in master mode*/\
    (SPI_BLOCK)->CR1 |= SPI_CR1_MSTR;\

#define SPI_SLAVE(SPI_BLOCK) \
  /*configure NSS pin: Software mode*/\
  /*Software mode: SSI bit is cleared, SSM bit is set*/\
  /*Hardware mode: is driven using SSOE */\
    (SPI_BLOCK)->CR1 |= SPI_CR1_SSM;\
    (SPI_BLOCK)->CR1 &= ~(SPI_CR1_SSI);\
  /*Disable SPI in master mode*/\
    (SPI_BLOCK)->CR1 &= ~(SPI_CR1_MSTR);\

//MACROs initializing SPI (Master mode ony)
#define SPI_configuration(SPI_BLOCK, BAUDRATE_DIV_FACTOR, CLOCK_PHASE, CLOCK_POLARITY, CLOCK_REG, MASTER_SLAVE) \
  /*SPI Peripherals, Baudrate_mapping, */\
  static void SPI_BLOCK##_Configuration(void){\
      /*Enable Clock register for SPI*/\
      RCC->CLOCK_REG##ENR |= RCC_##CLOCK_REG##ENR_##SPI_BLOCK##EN;\
      /*Common configuration for both sides: Transmitting and Receiving*/\
      uint16_t baudrate_bit_mapping_u8 = ~(SPI_CR1_BR_0 | SPI_CR1_BR_1|SPI_CR1_BR_2);\
      uint8_t baudrate_val_u8 = BAUDRATE_DIV_FACTOR << 3;\
      (SPI_BLOCK)->CR1 &= baudrate_bit_mapping_u8;\
      (SPI_BLOCK)->CR1 |= baudrate_val_u8;\
      /*Data frame: 8-bit length, MSB 1st*/\
      (SPI_BLOCK)->CR1 |= SPI_CR1_DFF;\
      (SPI_BLOCK)->CR1 &= ~(SPI_CR1_LSBFIRST);\
      /*Clock Phase, Polarity Configuration*/\
      if(CLOCK_PHASE == 1){\
        (SPI_BLOCK)->CR1 |= SPI_CR1_CPHA;\
      }\
      if(CLOCK_POLARITY == 1){\
        (SPI_BLOCK)->CR1 |= SPI_CR1_CPOL;\
      }\
      SPI_##MASTER_SLAVE(SPI_BLOCK)  \
                          \
      /*Enable SPI's interrupt mechanism*/\
      __set_PRIMASK(1);\
      NVIC_EnableIRQ(SPI_BLOCK##_IRQ);\
      __set_PRIMASK(0);\
  }


#define SPI_configuration_funcall(SPI_BLOCK, NA1, NA2, NA3, NA4, NA5) \
  SPI_BLOCK##_Configuration();\

//Driver's API

/*
@Brief: Call macro_defined function's definitions 
*/

SPI_LIST(SPI_configuration)

/*
SPI_Init()
@Brief: Call macro-defined functions to initialize SPI peripherals

*/
void SPI_init(void){
  /*Call macro func_call right here*/
  SPI_LIST(SPI_configuration_funcall)
}

