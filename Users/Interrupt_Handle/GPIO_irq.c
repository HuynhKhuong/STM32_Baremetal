#include "GPIO.h"
#include "GPIO_irq_pc.h"

/*
  User-defined functions for handling GPIO External interrupt
*/


void EXTI_A_0_IRQ(void){ //User-defined func
  signal = (signal == 1)?0:1;
}
