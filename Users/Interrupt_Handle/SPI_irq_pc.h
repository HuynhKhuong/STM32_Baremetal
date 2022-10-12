#ifndef __SPI_IRQ_PC_H
#define __SPI_IRQ_PC_H

#include "SPI.h"

/* The scope of this file is to init SPI_interrupt and handle IRQ from bare_metal */
//MACRO instance is defined in SPI.h drive

//Datatype for data container working in low layer when communicating via SPI
typedef struct{
    uint8_t* transmitt_buffer;
    uint8_t* receive_buffer;
    uint8_t transmitt_buffer_length;
    uint8_t receive_buffer_length;
    uint8_t transmitt_buffer_index;
    uint8_t receive_buffer_index;
}SPI_Data_buffer;

extern SPI_Data_buffer SPI1_data_container_str = {NULL, NULL, 0,0,0,0}; 
extern SPI_Data_buffer SPI2_data_container_str = {NULL, NULL, 0,0,0,0}; 

#define SPI_IRQ_DECL(SPI_BLOCK, NA1, NA2, NA3) \
  void SPI_BLOCK##_cplt_Transmitt(void);\
=======
#ifndef __SPI_IRQ_PC_H__
#define __SPI_IRQ_PC_H__

/*  Declare functions for 
    - initializing SPI's interrupt handler 
    - handle logics for interrupt handler
*/

#include "SPI.h"

#define 
>>>>>>> master

#endif
