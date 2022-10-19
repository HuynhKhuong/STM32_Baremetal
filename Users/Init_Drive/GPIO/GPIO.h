#ifndef __GPIO_H__
#define __GPIO_H__

#include "GPIO_def.h"

/*-------------------------------------------------------------------------------------------------------*/
//CNF configuration
#define INPUT_PULLUP_DOWN(CONFIGURE_REG,PIN) GPIO_##CONFIGURE_REG##_CNF##PIN##_1
#define FLOATING_INPUT(CONFIGURE_REG,PIN) GPIO_##CONFIGURE_REG##_CNF##PIN##_0
#define INPUT_ANALOG(CONFIGURE_REG,PIN) GPIO_##CONFIGURE_REG##_CNF##PIN##_2

#define OUTPUT_PUSHPULL(CONFIGURE_REG,PIN)	GPIO_##CONFIGURE_REG##_CNF##PIN##_2
#define OUTPUT_OPENDRAIN(CONFIGURE_REG,PIN)	GPIO_##CONFIGURE_REG##_CNF##PIN##_0
#define ALT_PUSHPULL(CONFIGURE_REG,PIN)	GPIO_##CONFIGURE_REG##_CNF##PIN##_1
#define ALT_OPENDRAIN(CONFIGURE_REG,PIN) GPIO_##CONFIGURE_REG##_CNF##PIN

//MODE configuration
#define INPUTMODE(CONFIGURE_REG,PIN) GPIO_##CONFIGURE_REG##_MODE##PIN##_2
#define OUTPUTMODE_10MHZ(CONFIGURE_REG,PIN)	GPIO_##CONFIGURE_REG##_MODE##PIN##_0
#define OUTPUTMODE_2MHZ(CONFIGURE_REG,PIN)	GPIO_##CONFIGURE_REG##_MODE##PIN##_1
#define OUTPUTMODE_50MHZ(CONFIGURE_REG,PIN)	GPIO_##CONFIGURE_REG##_MODE##PIN

//Reset bit in reg
#define RESET_MODE_BITS(CONFIGURE_REG, PIN) GPIO_##CONFIGURE_REG##_MODE##PIN
#define RESET_CNF_BITS(CONFIGURE_REG, PIN) GPIO_##CONFIGURE_REG##_CNF##PIN

/*-------------------------------------------------------------------------------------------------------*/
/*List declaration*/
#define PINLIST_C(ENTRYLIST) \
        /*GPIO_PORT, pin, Control_Register, MODE, CNF*/\
        ENTRYLIST(GPIOC, 13, CRH, OUTPUTMODE_50MHZ,OUTPUT_PUSHPULL) 

#define PINLIST_A(ENTRYLIST) \
        /*GPIO_PORT, pin, Control_Register, MODE, CNF*/\
        /*UART, output open-drain, max speed, input, floating*/ \
        ENTRYLIST(GPIOA, 10, CRH, INPUTMODE,  FLOATING_INPUT) \
        ENTRYLIST(GPIOA, 9, CRH, OUTPUTMODE_50MHZ, ALT_OPENDRAIN)\
        /*SPI1*/ \
        /*Output: Alternative push-pull, maxspeed*/\
        ENTRYLIST(GPIOA, 5, CRL, OUTPUTMODE_50MHZ, ALT_PUSHPULL) \
        ENTRYLIST(GPIOA, 6, CRL, INPUTMODE, FLOATING_INPUT) \
        ENTRYLIST(GPIOA, 7, CRL, OUTPUTMODE_50MHZ, ALT_PUSHPULL) \

#define PINLIST_B(ENTRYLIST) \
        /*SPI2*/\
        /*Output: open-drain, maxspeed*/\
        /*Intput: floating, maxspeed*/\
        ENTRYLIST(GPIOB, 13, CRH, INPUTMODE, FLOATING_INPUT) /*Clock pin*/ \
        ENTRYLIST(GPIOB, 14, CRH, OUTPUTMODE_50MHZ, ALT_PUSHPULL) /*MISO pin*/\
				ENTRYLIST(GPIOB, 15, CRH, INPUTMODE, FLOATING_INPUT) /*MOSI pin*/\

/*For APB_bus_bit position: 
#define  RCC_APB2ENR_AFIOEN                  ((uint32_t)0x00000001)         //Alternate Function I/O clock enable 
#define  RCC_APB2ENR_IOPAEN                  ((uint32_t)0x00000004)         //I/O port A clock enable 
#define  RCC_APB2ENR_IOPBEN                  ((uint32_t)0x00000008)         //I/O port B clock enable 
#define  RCC_APB2ENR_IOPCEN                  ((uint32_t)0x00000010)         //I/O port C clock enable 
#define  RCC_APB2ENR_IOPDEN                  ((uint32_t)0x00000020)         //I/O port D clock enable 
#define  RCC_APB2ENR_ADC1EN                  ((uint32_t)0x00000200)         //ADC 1 interface clock enable 
*/

/*port list declaration*/
#define GPIO_LIST_CONFIGURE(ENTRY_FUNCTION) \
        /*GPIO_PORT, AHB_bus, APB_bus, APB_bus_bit_pos, pin_list*/\
        ENTRY_FUNCTION(GPIOC, AHB1, APB2, RCC_APB2ENR_IOPCEN, PINLIST_C) \
        ENTRY_FUNCTION(GPIOA, AHB1, APB2, RCC_APB2ENR_IOPAEN, PINLIST_A) \
        ENTRY_FUNCTION(GPIOB, AHB1, APB2, RCC_APB2ENR_IOPBEN, PINLIST_B) \


#define GPIO_Configure_DELC(GPIO_PORT, NA1, NA2, NA3, NA4) \
        static void GPIO_configure_##GPIO_PORT(void);\

#define GPIO_Configure_FuncCall(GPIO_PORT, NA1, NA2, NA3, NA4) \
        GPIO_configure_##GPIO_PORT();\
				
extern uint8_t signal;


/*Macro calls*/
GPIO_LIST_CONFIGURE(GPIO_Configure_DELC)

void GPIO_Initialization(void);

#endif
