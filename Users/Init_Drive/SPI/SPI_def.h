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

typedef struct{
    uint8_t* transmitt_buffer;
    uint8_t* receive_buffer;
    uint8_t transmitt_buffer_length;
    uint8_t receive_buffer_length;
    uint8_t transmitt_buffer_index;
    uint8_t receive_buffer_index;
}SPI_Data_buffer;


typedef struct{
  SPI_TypeDef* const SPI;
  SPI_Data_buffer* const SPI_data_containter_str;
}SPI_LL_conf_st;

//Specific for STM32F103
typedef enum{
  SPI_1 = 0,
  SPI_2 = 1,
  MAX_SPI,
}SPI_HANDLES;

/// Hardware Configurations
extern SPI_LL_conf_st SPI_hardware_conf[MAX_SPI];

extern SPI_Data_buffer SPI1_data_container_str; 
extern SPI_Data_buffer SPI2_data_container_str; 

#endif
