/*
*   @Author: Huynh Khuong  
*   @Brief: This is the DIY library built for controlling GPIO of STM32F103
*   
*   This libary is built up from scratch based on CMSIS library. It makes use of registers to manipulate GPIO peripherals
*   It contains:
*   1. MACROS for initializing GPIOS
*   2. MACROS for reading and writing Inputs/Outputs
*   This writing styles is inspired from Bosch's Embedded Software 
*/
#include "GPIO.h"
#include "GPIO_irq_pc.h"

#define PIN_CONFIGURE(GPIO_PORT, pin, Control_Register, bit_value, function, Speed_bit_value) \
        /*Configure pin's function in the register*/\
        /*pin: 0,...15*/\
        /*bit_value: pin, pin_0, pin_1, by default: pin_0, which is the reset value of the register*/\
        /*Speed_bit_value: pin, pin_0, pin_1: by default: pin_2, which is the reset value of the register*/\
        /*Reset bit_value*/\
        ((GPIO_PORT)->Control_Register) &=  ~(GPIO_##Control_Register##_CNF##pin);\
        ((GPIO_PORT)->Control_Register) |=  (GPIO_##Control_Register##_CNF##bit_value);\
        /*Reset speed_bit_value*/\
        ((GPIO_PORT)->Control_Register) &=  ~(GPIO_##Control_Register##_MODE##pin);\
        ((GPIO_PORT)->Control_Register) |=  (GPIO_##Control_Register##_MODE##Speed_bit_value);\
				/*For Input mode, If that pin is configured as pull up/down mode, by default it is pull-down mode*/\


#define GPIO_Configuration(GPIO_PORT, AHB_bus, APB_bus, APB_bus_bit_pos, pin_list) \
        /*Procedure: 1. Clock enable for AHB, 2. Clock enable for each port, 3. Pin configuration*/\
        static void GPIO_configure_##GPIO_PORT(void){\
            /*Configure its APB_bus*/\
            RCC->APB_bus##ENR |= APB_bus_bit_pos;  \
            /*Configure its Output Pin*/\
            pin_list(PIN_CONFIGURE) \
        }\

uint8_t signal = 0;

/*  Function's definitions*/
/* Bitwise Operation on Register */ 
/* Convert bit position (uint8_t value) to the real position in the register*/
#define GPOutput_bit_write(GPIO_Port, bit)  SET_BIT(GPIO_Port, bit) 
#define GPOutput_bit_clear(GPIO_Port, bit)  CLEAR_BIT(GPIO_Port, bit)
#define GPOutput_clear_value(GPIO_Port) (GPIO_Port = (uint32_t)0) 
#define GPOutput_set_value(GPIO_Port, val_u32)  (GPIO_Port= val_u32)
#define GPPort_pinread(GPIO_Port, bit_pos) (((GPIO_Port) & (bit_position_val_tbl[bit_pos])) >> bit_pos)

GPIO_LIST_CONFIGURE(GPIO_Configuration)

void GPIO_Initialization(void){
  GPIO_LIST_CONFIGURE(GPIO_Configure_FuncCall)

  #ifdef EXTI_YES
    /*First to configure IRQ, disable all Interrupts via BASEPRI register
      This register controls the priorities for exception processing
      For more info, take a look at: Cortex-M3 Processor

      When it is set to a nonzero value, it prevents the activation of all exceptions with the same or lower priority level as the 
      BASEPRI value
    */
    //__set_BASEPRI((uint32_t)(1<<4)); //At the beginning, no additional Exceptions are configured, therefore the IRQs are from the sytem request 
    __set_PRIMASK(1);
    EXTI_LIST_CONFIGURE(GPIO_EX_Interrupt_FUNC_Call)

    //__set_BASEPRI((uint32_t)(0));
    __set_PRIMASK(0);

  #endif 
}
