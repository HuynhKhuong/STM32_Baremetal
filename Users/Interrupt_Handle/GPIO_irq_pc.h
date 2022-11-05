#ifndef __GPIO_IRQ_PC_H__
#define __GPIO_IRQ_PC_H__

#include "stm32f407xx.h"
/*
  Base code for handling interrupt under platform, application would only make use functions from GPIO_irq.c 
*/

#define EXTI_YES

/*-------------------------------------------------------------------------------------------------------*/
/*
	This is the section for External Interrupt configuration
  The concept of External Interrupt:
    A_pinx/B_pinx/C_pinx/... are connected to the same interrupt signal line x
    Hence once a pin number x from a port is configured, pin from other ports with the same number x cannot be configured as
    external interrupt
		
		Procedure of EXT configuration in STM32F4 series: 
    To configure External Interrupt: 
    - Configure GPIO pin as input
		- Configure the mask bits of interrupt/event lines (EXTI_IMR, EXTI_EMR)
		- Set the required bit in the software interrupt register (EXTI_SWIER)
		- Configure the callback function
    - Callback function
*/

/*-------------------SUPPORTING MACROS-----------------------------*/
#define RISING(PIN) \
				EXTI->RTSR |= EXTI_RTSR_TR##PIN;

#define FALLING(PIN) \
				EXTI->FTSR |= EXTI_FTSR_TR##PIN;
				 
#define BOTH(PIN) \
				EXTI->FTSR |= EXTI_FTSR_TR##PIN;\
        EXTI->RTSR |= EXTI_RTSR_TR##PIN;
				 
/*External Interrupt list declaration*/
#define EXTI_LIST_CONFIGURE(ENTRY_FUNC) \
				/*GPIO_PORT, LINE, RISING/FALLING EDGE*/\
        ENTRY_FUNC(GPIOA, 0, RISING)



/*Functions' declaration*/
#define GPIO_EX_Interrupt_DELC(GPIO_PORT, NA1, NA2) \
  void EX_Interrupt_configurtation_##GPIO_PORT(void);\

#define GPIO_EX_Interrupt_FUNC_Call(GPIO_PORT, NA1, NA2) \
        EX_Interrupt_configurtation_##GPIO_PORT();

/*Functions' declaration*/
EXTI_LIST_CONFIGURE(GPIO_EX_Interrupt_DELC)
    
void EXTI_GPIOA_0_IRQ(void); //User-defined func

#endif
