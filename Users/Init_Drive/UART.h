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

/*Datatype for containing buffers for transmitting and receiving*/
typedef struct{
    uint8_t* transmitt_buffer;
    uint8_t* receive_buffer;
    uint8_t transmitt_buffer_length;
    uint8_t receive_buffer_length;
    uint8_t transmitt_buffer_index;
    uint8_t receive_buffer_index;
}UART_data_buffer;

/*UART configuration for each instance */
/*Note that before in-depth UART configuration, GPIO pin and clock must be configured first */
#define UART_Configuration(UART, CLOCK_REG, WORD_L,STOP_BIT ) \
        static void UART_configure_##UART(void){\
        /*Procedure: 1. Clock enable for UART peripheral*/\
            RCC->##CLOCK_REG##ENR |= RCC_##CLOCK_REG##ENR_##UART##EN;\
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

#define UART_Communication_Handler(UART, NA1, NA2, NA3) \
    static void UART##_TXE_interrupt(void){                                                                              \
                                                                                                                        \
    /*handle if this is the last byte*/                                                                                 \
    uint8_t last_byte_u8 = UART##_data_container_str.transmitt_buffer_length - 1;                                       \
                                                                                                                        \
    if( last_byte_u8 == UART##_data_container_str.transmitt_buffer_index){                                              \
        /*last byte, reset TXE interrupt*/                                                                              \
        /*set TC interrupt*/                                                                                            \
        (UART)->CR1 &= ~(USART_CR1_TXEIE);                                                                              \
        (UART)->CR1 |= USART_CR1_TCIE;                                                                                  \
    }                                                                                                                   \
    (UART)->DR =  UART##_data_container_str.transmitt_buffer[UART##_data_container_str.transmitt_buffer_index];         \
    UART##_data_container_str.transmitt_buffer_index++;                                                                                   \
    }\
\
    static void UART##_RXE_interrupt(void){                                                                              \
    UART##_data_container_str.receive_buffer[UART##_data_container_str.receive_buffer_index] = (UART)->DR;              \
    UART##_data_container_str.receive_buffer_index++;                                                                   \
\
    if(UART##_data_container_str.receive_buffer_index == UART##_data_container_str.receive_buffer_length){              \
        UART##_cplt_Receive();                                                                                           \
    }                                                                                                                   \
    }                                                                                                                   \
\
    void UART##_IRQHandler(void){                                                                                       \
    uint8_t is_TXE_interrupt_u8;                                                                                        \
    uint8_t is_TC_interrupt_u8;                                                                                         \
    uint8_t is_RXNE_interrupt_u8;                                                                                       \
\
    is_TXE_interrupt_u8 = ((UART)->CR1 & USART_CR1_TXEIE) >> 7; /*7 is TXE bit position*/                               \
    is_TXE_interrupt_u8 &= ((UART)->SR & USART_SR_TXE) >> 7; /*7 is the TXE bit position*/                              \
\
    is_TC_interrupt_u8 = ((UART)->CR1 & USART_CR1_TCIE) >> 6; /*6 is TC bit position*/                                  \
    is_TC_interrupt_u8 &= ((UART)->SR & USART_SR_TC) >> 6; /*6 is TC bit positio*/                                      \
\
    is_RXNE_interrupt_u8 = ((UART)->SR & USART_SR_RXNE) >> 5; /*5 is the RXNE bit position*/                            \
    \
    if(is_TXE_interrupt_u8){                                                                                            \
        UART##_TXE_interrupt();                                                                                         \
    }                                                                                                                   \
    if(is_TC_interrupt_u8){                                                                                             \
        UART##_cplt_Transmitt();                                                                                        \
    }                                                                                                                   \
\
    if(is_RXNE_interrupt_u8){                                                                                           \
        UART##_RXE_interrupt();                                                                                         \
    }                                                                                                                   \
}\

/*Instance list*/
#define UART_LIST_CONFIGURE(ENTRY_LIST) \
        /*UART_Name, RCC_clockenable_reg, word_l, stop_bit_num*/\
        /*word_l = 0,1; stop_bit_num = 1*/\
        ENTRY_LIST(USART1, APB2, 0, 1)\

#define UART_configure_funcall(UART, NA1, NA2, NA3) \
        UART_configure_##UART();

#define UART_configure_DELC(UART, NA1, NA2, NA3) \
        static void UART_configure_##UART(void);\
        void UART##_cplt_Transmitt(void);\
        void UART##_cplt_Receive(void);\

/*extern variables*/
extern	uint8_t DUMMY_RECEIVE[11];

/*Functions declaration*/
UART_LIST_CONFIGURE(UART_configure_DELC)
void UART_init(void);
void UART_Transmitt(USART_TypeDef *UART, uint8_t* data_u8_array, uint8_t data_length_u8);
void UART_Receive(USART_TypeDef *UART, uint8_t* data_u8_array, uint8_t data_length_u8);

#endif
