#ifndef __GPIO_H__
#define __GPIO_H__

#include "GPIO_def.h"


/*-------------------------------------------------------------------------------------------------------*/
/*List declaration*/
#define PINLIST_C(ENTRYLIST) \
        /*GPIO_PORT, pin, Control_Register, bit_value, OUTPUT, Speed_bit_value*/\
        ENTRYLIST(GPIOC, 13_2, CRH, 13_0, OUTPUT, 13) 

#define PINLIST_A(ENTRYLIST) \
        /*GPIO_PORT, pin, Control_Register, CFN, OUTPUT, Mode_value*/\
        ENTRYLIST(GPIOA, 0, CRL, 0_1, INPUT,  0_2) \
        /*UART, output open-drain, max speed, input, floating*/ \
        ENTRYLIST(GPIOA, 10, CRH, 10_0, INPUT,  10_2) \
        ENTRYLIST(GPIOA, 9, CRH, 9, INPUT,  9)\
        /*SPI*/ \
        /*Output: open-drain, maxspeed, Input: floating*/\
        ENTRYLIST(GPIOA, 5, CRL, 5, OUTPUT, 5) \
        ENTRYLIST(GPIOA, 6, CRL, 6_0, OUTPUT, 6_2 ) \
        ENTRYLIST(GPIOA, 7, CRL, 7, OUPUT, 7) \
        /*Output: Push-pull, maxspeed*/\
        ENTRYLIST(GPIOA, 3, CRL, 3_2,OUTPUT, 3) \
        ENTRYLIST(GPIOA, 4, CRL, 4_2,OUTPUT, 4) \
        ENTRYLIST(GPIOA, 2, CRL, 2_2,OUTPUT, 2) \


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


#define GPIO_Configure_DELC(GPIO_PORT, NA1, NA2, NA3, NA4) \
        static void GPIO_configure_##GPIO_PORT(void);\

#define GPIO_Configure_FuncCall(GPIO_PORT, NA1, NA2, NA3, NA4) \
        GPIO_configure_##GPIO_PORT();\
				
extern uint8_t signal;


/*Macro calls*/
GPIO_LIST_CONFIGURE(GPIO_Configure_DELC)

void GPIO_Initialization(void);

#endif
