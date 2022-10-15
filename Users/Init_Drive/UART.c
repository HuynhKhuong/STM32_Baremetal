#include "UART_irq_pc.h"

#include <stdio.h>
/*
@Author: Huynh Khuong
@Brief: Function's definitions of UART library
*/

uint32_t fractional_part_u32, mantisa_part_u32, brr_result_u32;

/*UART configuration for each instance */
/*Note that before in-depth UART configuration, GPIO pin and clock must be configured first */
#define UART_Configuration(UART, CLOCK_REG, WORD_L,STOP_BIT ) \
        static void UART_configure_##UART(void){\
        /*Procedure: 1. Clock enable for UART peripheral*/\
            RCC->CLOCK_REG##ENR |= RCC_##CLOCK_REG##ENR_##UART##EN;\
            /*Note that its clock speed source is AHB clock speed, which is extracted from System clock speed*/\
            /*2. Enable USART communication*/\
            (UART)->CR1 |= USART_CR1_UE; \
            /*3. Define word length*/\
            /*By default, word length is 0, if you want to configure word length to 1, set flag WORD_L*/\
            if(WORD_L == 1){\
            (UART)->CR1 |= USART_CR1_M;\
            }\
            /*4. select number of stop bit*/\
            (UART)->CR2 |= USART_CR2_STOP_##STOP_BIT;\
            /*5. Set baudrate*/\
            /*BRR clock speed is taken from bus clock speed APB2*/\
            /*By default clock speed APB2 = 72MHz*/\
            /*Baudrate = APB2/16/BRR(value)*/\
            /*To set baudrate = 115200 , BRR(value) = 39.0625 */\
            mantisa_part_u32 = (uint32_t)39;\
            fractional_part_u32 = (uint32_t)(0.625*16);\
            brr_result_u32 = ((mantisa_part_u32 << 4)|(fractional_part_u32)) & 0x0000FFFF;\
            (UART)->BRR |= brr_result_u32;\
            /*7. Add interrupt request to NVIC*/\
            __set_PRIMASK(1);\
            NVIC_EnableIRQ(UART##_IRQ);\
            __set_PRIMASK(0);\
        }\

#define UART_configure_funcall(UART, NA1, NA2, NA3) \
        UART_configure_##UART();

UART_LIST_CONFIGURE(UART_Configuration)

void UART_init(){
  UART_LIST_CONFIGURE(UART_configure_funcall)
}


