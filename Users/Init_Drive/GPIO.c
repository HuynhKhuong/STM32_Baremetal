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

const uint32_t pin_lookup_tbl[32] ={
    GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7,
    GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15,
    GPIO_BSRR_BR0,GPIO_BSRR_BR1,GPIO_BSRR_BR2,GPIO_BSRR_BR3,GPIO_BSRR_BR4,GPIO_BSRR_BR5,GPIO_BSRR_BR6,
    GPIO_BSRR_BR7,GPIO_BSRR_BR8,GPIO_BSRR_BR9,GPIO_BSRR_BR10,GPIO_BSRR_BR11,GPIO_BSRR_BR12,GPIO_BSRR_BR13,
    GPIO_BSRR_BR14,GPIO_BSRR_BR15
};

uint8_t signal = 0;

/* Bitwise Operation on Register */ 
/* Convert bit position (uint8_t value) to the real position in the register*/
#define GPOutput_bit_write(GPIO_Port, bit)  SET_BIT(GPIO_Port, bit) 
#define GPOutput_bit_clear(GPIO_Port, bit)  CLEAR_BIT(GPIO_Port, bit)
#define GPOutput_clear_value(GPIO_Port) (GPIO_Port = (uint32_t)0) 
#define GPOutput_set_value(GPIO_Port, val_u32)  (GPIO_Port= val_u32)
#define GPPort_pinread(GPIO_Port, bit_pos) (((GPIO_Port) & (pin_lookup_tbl[bit_pos])) >> bit_pos)

/*  Function's definitions*/
GPIO_LIST_CONFIGURE(GPIO_Configuration)
EXTI_LIST_CONFIGURE(GPIO_EX_Interrupt_configuration)

uint8_t GPIO_ReadPin(GPIO_TypeDef* GPIO_Port, uint8_t pin_pos_u8){
    uint8_t ret_val_u8 = 0;
    ret_val_u8 = GPPort_pinread(GPIO_Port->IDR, pin_pos_u8);

    return ret_val_u8;
}

/*
@Prief: GPIO_WritePin would control output port via BSRR register. 
@Params: pin_pos_u8 ranges: 0-31
*/
void GPIO_WritePin(GPIO_TypeDef* GPIO_Port, uint8_t pin_pos_u8, uint8_t value_u8){
    uint8_t reset_pos_u8 = pin_pos_u8 + 16;
    if(value_u8 == 1){ //set bit Output to 1
      GPOutput_set_value(GPIO_Port->BSRR, pin_lookup_tbl[pin_pos_u8]);
    }
    else { //set bit Output to 0
      GPOutput_set_value(GPIO_Port->BSRR, pin_lookup_tbl[reset_pos_u8]);
    }
}

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

void EXTI0_IRQHandler(void){
  /*Exception Handler for EXTI0*/
  /*
    The procedure of handling Interrupt request is depicted as followed: 
    Reference manual of STM32F103xx 
    
    After a bunch of configurations declaring and setting interrupt request signal, It would trigger a bit in Pending request register
    This bit would be set 0 if we set it manually by writing 1 to the according bit in PR register 
  */
  EXTI->PR |= EXTI_PR_PR0;
	signal = (signal == 0)?1:0;
}
