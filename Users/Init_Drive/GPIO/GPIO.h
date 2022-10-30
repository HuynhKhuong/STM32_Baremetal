#ifndef __GPIO_H__
#define __GPIO_H__

#include "GPIO_def.h"


/*-------------------------------------------------------------------------------------------------------*/
//MODE configuration
#define INPUT(CONFIGURE_REG,PIN) GPIO_##CONFIGURE_REG##_MODER##PIN##_2
#define OUTPUT(CONFIGURE_REG,PIN) GPIO_##CONFIGURE_REG##_MODER##PIN##_0
#define ALT_FUNCTION(CONFIGURE_REG,PIN)	GPIO_##CONFIGURE_REG##_MODER##PIN##_1
#define INPUT_ANALOG(CONFIGURE_REG,PIN) GPIO_##CONFIGURE_REG##_MODER##PIN

//OUTPUT_TYPE configuration
#define OUTPUT_PUSHPULL(CONFIGURE_REG,PIN)	GPIO_##CONFIGURE_REG##_OT##PIN##_2
#define OUTPUT_OPENDRAIN(CONFIGURE_REG,PIN)	GPIO_##CONFIGURE_REG##_OT##PIN

//SPEED configuration
#define OUTPUTMODE_2MHZ(CONFIGURE_REG,PIN)	GPIO_##CONFIGURE_REG##_OSPEED##PIN##_2
#define OUTPUTMODE_10MHZ(CONFIGURE_REG,PIN)	GPIO_##CONFIGURE_REG##_OSPEED##PIN##_0
#define OUTPUTMODE_50MHZ(CONFIGURE_REG,PIN)	GPIO_##CONFIGURE_REG##_OSPEED##PIN##_1
#define OUTPUTMODE_100MHZ(CONFIGURE_REG,PIN)    GPIO_##CONFIGURE_REG##_OSPEED##PIN

//PULLUP-PULLDOWN configuration
#define INPUT_PULLUP(CONFIGURE_REG, PIN)        GPIO_##CONFIGURE_REG##_PUPD##PIN##_0
#define INPUT_PULLDOWN(CONFIGURE_REG, PIN)      GPIO_##CONFIGURE_REG##_PUPD##PIN##_1
#define FLOATING(CONFIGURE_REG, PIN)            GPIO_##CONFIGURE_REG##_PUPD##PIN##_2

//Reset bit in reg
#define RESET_MODE_BITS(CONFIGURE_REG, PIN) GPIO_##CONFIGURE_REG##_MODER##PIN
#define RESET_OUTPUT_TYPE_BITS(CONFIGURE_REG, PIN) GPIO_##CONFIGURE_REG##_OT##PIN
#define RESET_SPEED_BITS(CONFIGURE_REG, PIN) GPIO_##CONFIGURE_REG##_OSPEED##PIN
#define RESET_PUPD_BITS(CONFIGURE_REG, PIN) GPIO_##CONFIGURE_REG##_PUPD##PIN

#define DIRECT_OUT(GPIO_PORT, NA, OSPEED, OT, pin) \
        (GPIO_PORT)->OSPEEDR |= OSPEED(OSPEEDR, pin) ;\
        (GPIO_PORT)->OTYPER   |= OT(OTYPER, pin) ;\

#define DIRECT_IN(GPIO_PORT, PUPD, NA1, NA2, pin) \
        (GPIO_PORT)->PUPDR   |= PUPDR(OTYPER, pin) ;\

/*-------------------------------------------------------------------------------------------------------*/
/*List declaration*/
#define PINLIST_D(ENTRYLIST) \
        /*GPIO_PORT, pin, DIR, MODE, PUPDR, OSPEED, OT */ \
        ENTRYLIST(GPIOD, 12, OUT, OUTPUT, NA, OUTPUTMODE_50MHZ, OUTPUT_PUSHPULL) \
        ENTRYLIST(GPIOD, 13, OUT, OUTPUT, NA, OUTPUTMODE_50MHZ, OUTPUT_PUSHPULL) \
        ENTRYLIST(GPIOD, 14, OUT, OUTPUT, NA, OUTPUTMODE_50MHZ, OUTPUT_PUSHPULL) \
        ENTRYLIST(GPIOD, 15, OUT, OUTPUT, NA, OUTPUTMODE_50MHZ, OUTPUT_PUSHPULL) \


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

/*port list declaration*/
#define GPIO_LIST_CONFIGURE(ENTRY_FUNCTION) \
        /*GPIO_PORT, AHB_bus, pin_list*/\
        ENTRY_FUNCTION(GPIOD, AHB1, PINLIST_D) \


#define GPIO_Configure_DELC(GPIO_PORT, NA1, NA2) \
        static void GPIO_configure_##GPIO_PORT(void);\

#define GPIO_Configure_FuncCall(GPIO_PORT, NA1, NA2) \
        GPIO_configure_##GPIO_PORT();\
				
extern uint8_t signal;


/*Macro calls*/
GPIO_LIST_CONFIGURE(GPIO_Configure_DELC)

void GPIO_Initialization(void);

#endif
