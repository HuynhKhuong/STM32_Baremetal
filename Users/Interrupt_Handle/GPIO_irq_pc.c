#include "GPIO_irq_pc.h"
#include "stm32f407xx.h"
/*
   Define Interrupt handlers declared by system right here
*/


/*Functions' definition*/

#define GPIO_EX_Interrupt_configuration(GPIO_PORT, LINE, EDGE_DETECT) \
  void EX_Interrupt_configurtation_##GPIO_PORT(void){\
        /*Configure EXTI_IMR: mask the required External Interrupt line*/\
        EXTI->IMR |= EXTI_IMR_MR##LINE;\
        /*Configure trigger EXTI signal: rising/falling edge/both*/\
				EDGE_DETECT(LINE)\
				/*Enable software interrupt*/\
				EXTI->SWIER |=	EXTI_SWIER_SWIER##LINE;\
        /*Register the interrupt with NVIC in CPU*/\
        NVIC_EnableIRQ(EXTI##LINE##_IRQn);\
  }


#define INTERRUPT_HANDLE_DEF(GPIO_PORT, LINE, NA) \
		/*Exception Handler for EXTI*/\
    /* The procedure of handling Interrupt request is depicted as followed: */\
    /* Reference manual of STM32F407xx */ \
    /* A interrupt signal coming to EXTI pin would trigger a bit in Pending request register*/\
    /* This bit would be set 0 if we set it manually by writing 1 to the according bit in PR register */ \
  void EXTI##LINE##_IRQHandler(void){\
    EXTI->PR |= EXTI_PR_PR##LINE; \
    /*Invoke user defined functions*/\
    EXTI_##GPIO_PORT##_##LINE##_IRQ();\
	}\

	
/*Functions definition*/
EXTI_LIST_CONFIGURE(GPIO_EX_Interrupt_configuration)
EXTI_LIST_CONFIGURE(INTERRUPT_HANDLE_DEF)
