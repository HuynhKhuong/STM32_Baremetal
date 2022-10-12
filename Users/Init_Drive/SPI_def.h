#ifndef __SPI_DEF_H__
#define __SPI_DEF_H__

#include "stm32f10x.h"


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



#endif
