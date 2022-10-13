#ifndef __SPI_SERV_H__
#define __SPI_SERV_H__

#include "SPI_irq_pc.h"

//This file contains API for users to interact with SPI peripherals

void SPI_Write(SPI_TypeDef* SPI, uint8_t* data_u8_array, uint8_t data_length_u8);
//void SPI_read(SPI_TypeDef* SPI, uint8_t* data_u8_array, uint8_t data_length_u8);
#endif
