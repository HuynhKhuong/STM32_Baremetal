#ifndef __SPI_DEF_H__
#define __SPI_DEF_H__

#include "stm32f10x.h"

/*
    This file declares enums, defines, constants used for configuring SPI peripherals for STM32f1
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

#endif
