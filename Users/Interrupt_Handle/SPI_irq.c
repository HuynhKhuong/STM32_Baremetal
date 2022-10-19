#include "SPI_irq_pc.h"
#include "Nokia_5110_LCD.h"
//Callback functions visable for users at the end of the transmission
void SPI1_cplt_Comm(void){
  /*User's application*/
	transmit_cplt_b = 0;
}

void SPI2_cplt_Comm(void){
  /*User's application*/
	transmit_cplt_b = 0;
}
