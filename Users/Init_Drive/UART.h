#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"
#include "GPIO.h"
/*
    @Author: Huynh Khuong
    @Brief: This is the driver manipulating basic functions of UART peripheral of STM32. This driver controls UART via directly 
    register configurations

    This project is done aiming to get a thorough understanding about STM32 architecture
*/

/*
    STM32's UART architecture

    To configure UART (as well as other peripherals that communicate with the outside world), preliminarily, We have to configure the GPIO pins corresponding with
    UART. For better pinout layout visualization, I recommend using STM32CubeMX rather than Datasheet. 

    To configure its GPIO, make use of my GPIO driver 

    //Configure UART specs:
    - Enable clock for UART peripherals
    - Remapping (AFIO)


    UART initialization workflow: (referenced in Reference manual)

    1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
    2. Program the M bit in USART_CR1 to define the word length.
    3. Program the number of stop bits in USART_CR2.
(this step is not madatory at this time)    4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
    place. Configure the DMA register as explained in multibuffer communication. 

    5. Select the desired baud rate using the USART_BRR register.

    9. You must active UART interrupt in NVIC

    Tx and Rx sides have their own register. However, DR register is the only entry point to access these registers.
    A read from DR read Rx's register
    A write from DR write Tx's register 
*/

/*Instance list*/
#define UART_LIST_CONFIGURE(ENTRY_LIST) \
        /*UART_Name, RCC_clockenable_reg, word_l, stop_bit_num*/\
        /*word_l = 0,1; stop_bit_num = 1*/\
        ENTRY_LIST(USART1, APB2, 0, 1)\

/* Functions declaration*/

#define UART_configure_DELC(UART, NA1, NA2, NA3) \
        static void UART_configure_##UART(void);\

/*Functions declaration*/
UART_LIST_CONFIGURE(UART_configure_DELC)

void UART_init(void);

/*extern variables*/
extern	uint8_t DUMMY_RECEIVE[11];
#endif
