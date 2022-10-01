#ifndef __GPIO_IRQ_PC_H__
#define __GPIO_IRQ_PC_H__

/*
  Base code for handling interrupt under platform, application would only make use functions from GPIO_irq.c 
*/

#define EXTI_YES

/*-------------------------------------------------------------------------------------------------------*/
/*This is the section for External Interrupt configuration
  The concept of External Interrupt:
    A_pinx/B_pinx/C_pinx/... are connected to the same interrupt signal line x
    Hence once a pin number x from a port is configured, pin from other ports with the same number x cannot be configured as
    external interrupt
    To configure External Interrupt: 
    - Configure GPIO pin as AF function
    - Configure that AF function
    - Interrupt declaration in the interrupt mask
    - Interrupt signal type
    - Callback function
*/

/*External Interrupt list declaration*/
#define EXTI_LIST_CONFIGURE(ENTRY_FUNC) \
        /*GPIO_PORT = A, B, C,D; pin = 1, 2,3 ,4...; INTERRUPT_register = 1, 2, 3, 4*/\
        /*edge_detection: 0 = rising, 1 = falling, 2 = both*/\
        ENTRY_FUNC(A, 1, 0, 0, NA, NA2)



/*Functions' declaration*/
#define GPIO_EX_Interrupt_DELC(GPIO_PORT, NA1, NA2, NA3, NA4, NA5) \
  void EX_Interrupt_configurtation_##GPIO_PORT(void);\

#define GPIO_EX_Interrupt_FUNC_Call(GPIO_PORT, NA1, NA2, NA3, NA4, NA5) \
        EX_Interrupt_configurtation_##GPIO_PORT();

/*Functions' declaration*/
EXTI_LIST_CONFIGURE(GPIO_EX_Interrupt_DELC)
    
void EXTI_A_1_IRQ(void); //User-defined func

#endif
