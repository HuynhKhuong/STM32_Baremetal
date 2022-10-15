#ifndef __SPI_IRQ_PC_H
#define __SPI_IRQ_PC_H

#include "SPI.h"

/* The scope of this file is to init SPI_interrupt and handle IRQ from bare_metal */
//MACRO instance is defined in SPI.h drive

//Datatype for data container working in low layer when communicating via SPI

#define SPI_IRQ_DECL(SPI_BLOCK, NA1, NA2, NA3) \
  void SPI_BLOCK##_cplt_Transmitt(void);\
  
#endif
