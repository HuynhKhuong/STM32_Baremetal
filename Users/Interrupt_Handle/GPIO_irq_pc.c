#include "GPIO_irq_pc.h"
#include "stm32f10x.h"
/*
   Define Interrupt handlers declared by system right here
*/


/*Functions' definition*/

#define GPIO_EX_Interrupt_configuration(GPIO_PORT, INTERRUPT_register, pin, edge_detection, priority, callbackfunction) \
  void EX_Interrupt_configurtation_##GPIO_PORT(void){\
        /*GPIO_PORT = A, B, C,D; pin = 1, 2,3 ,4...; INTERRUPT_register = 1, 2, 3, 4*/\
        /*edge_detection: 0 = rising, 1 = falling, 2 = both*/\
        /* Configure AF function as interrupt*/\
        AFIO->EXTICR[pin] |= AFIO_EXTICR##INTERRUPT_register##_EXTI##pin##_P##GPIO_PORT;\
        /*Configure EXTI_IMR: Unmask the required External Interrupt line*/\
        EXTI->IMR |= EXTI_IMR_MR##pin;\
        /*Configure trigger EXTI signal: rising/falling edge*/\
        if(edge_detection == 0){\
          EXTI->RTSR |= EXTI_RTSR_TR##pin;\
        }\
        else if(edge_detection == 1){\
          EXTI->FTSR |= EXTI_FTSR_TR##pin;\
        }\
        else{\
          EXTI->FTSR |= EXTI_FTSR_TR##pin;\
          EXTI->RTSR |= EXTI_RTSR_TR##pin;\
        }\
        /*Register the interrupt with NVIC in CPU*/\
        NVIC_EnableIRQ(EXTI##pin##_IRQn);\
  }


#define INTERRUPT_HANDLE_DEF(GPIO_PORT, NA, pin, NA1, NA2, NA3) \
		/*Exception Handler for EXTI*/\
    /* The procedure of handling Interrupt request is depicted as followed: */\
    /* Reference manual of STM32F103xx */ \
    /* A interrupt signal coming to EXTI pin would trigger a bit in Pending request register*/\
    /* This bit would be set 0 if we set it manually by writing 1 to the according bit in PR register */ \
  void EXTI##pin##_IRQHandler(void){\
    EXTI->PR |= EXTI_PR_PR##pin; \
    /*Invoke user defined functions*/\
    EXTI_##GPIO_PORT##_##pin##_IRQ();\
	}\

	
/*Functions definition*/
EXTI_LIST_CONFIGURE(GPIO_EX_Interrupt_configuration)
EXTI_LIST_CONFIGURE(INTERRUPT_HANDLE_DEF)
