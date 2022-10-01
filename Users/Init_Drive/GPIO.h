#ifndef __GPIO_H__
#define __GPIO_H__
#include "stm32f10x.h"


#define GPIO_PIN_0                        ((uint16_t)0x0001)            /*!< Port output data, bit 0 */
#define GPIO_PIN_1                        ((uint16_t)0x0002)            /*!< Port output data, bit 1 */
#define GPIO_PIN_2                        ((uint16_t)0x0004)            /*!< Port output data, bit 2 */
#define GPIO_PIN_3                        ((uint16_t)0x0008)            /*!< Port output data, bit 3 */
#define GPIO_PIN_4                        ((uint16_t)0x0010)            /*!< Port output data, bit 4 */
#define GPIO_PIN_5                        ((uint16_t)0x0020)            /*!< Port output data, bit 5 */
#define GPIO_PIN_6                        ((uint16_t)0x0040)            /*!< Port output data, bit 6 */
#define GPIO_PIN_7                        ((uint16_t)0x0080)            /*!< Port output data, bit 7 */
#define GPIO_PIN_8                        ((uint16_t)0x0100)            /*!< Port output data, bit 8 */
#define GPIO_PIN_9                        ((uint16_t)0x0200)            /*!< Port output data, bit 9 */
#define GPIO_PIN_10                       ((uint16_t)0x0400)            /*!< Port output data, bit 10 */
#define GPIO_PIN_11                       ((uint16_t)0x0800)            /*!< Port output data, bit 11 */
#define GPIO_PIN_12                       ((uint16_t)0x1000)            /*!< Port output data, bit 12 */
#define GPIO_PIN_13                       ((uint16_t)0x2000)            /*!< Port output data, bit 13 */
#define GPIO_PIN_14                       ((uint16_t)0x4000)            /*!< Port output data, bit 14 */
#define GPIO_PIN_15                       ((uint16_t)0x8000)            /*!< Port output data, bit 15 */
#define GPIO_BSRR_BR0                        ((uint32_t)0x00010000)        /*!< Port x Reset bit 0 */
#define GPIO_BSRR_BR1                        ((uint32_t)0x00020000)        /*!< Port x Reset bit 1 */
#define GPIO_BSRR_BR2                        ((uint32_t)0x00040000)        /*!< Port x Reset bit 2 */
#define GPIO_BSRR_BR3                        ((uint32_t)0x00080000)        /*!< Port x Reset bit 3 */
#define GPIO_BSRR_BR4                        ((uint32_t)0x00100000)        /*!< Port x Reset bit 4 */
#define GPIO_BSRR_BR5                        ((uint32_t)0x00200000)        /*!< Port x Reset bit 5 */
#define GPIO_BSRR_BR6                        ((uint32_t)0x00400000)        /*!< Port x Reset bit 6 */
#define GPIO_BSRR_BR7                        ((uint32_t)0x00800000)        /*!< Port x Reset bit 7 */
#define GPIO_BSRR_BR8                        ((uint32_t)0x01000000)        /*!< Port x Reset bit 8 */
#define GPIO_BSRR_BR9                        ((uint32_t)0x02000000)        /*!< Port x Reset bit 9 */
#define GPIO_BSRR_BR10                       ((uint32_t)0x04000000)        /*!< Port x Reset bit 10 */
#define GPIO_BSRR_BR11                       ((uint32_t)0x08000000)        /*!< Port x Reset bit 11 */
#define GPIO_BSRR_BR12                       ((uint32_t)0x10000000)        /*!< Port x Reset bit 12 */
#define GPIO_BSRR_BR13                       ((uint32_t)0x20000000)        /*!< Port x Reset bit 13 */
#define GPIO_BSRR_BR14                       ((uint32_t)0x40000000)        /*!< Port x Reset bit 14 */
#define GPIO_BSRR_BR15                       ((uint32_t)0x80000000)        /*!< Port x Reset bit 15 */

#define GPIO_CRL_CNF0_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_CNF1_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_CNF2_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_CNF3_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_CNF4_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_CNF5_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_CNF6_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_CNF7_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_CNF8_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_CNF9_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_CNF10_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_CNF11_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_CNF12_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_CNF13_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_CNF14_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_CNF15_2                      ((uint32_t)0x00000000)

#define GPIO_CRL_MODE0_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_MODE1_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_MODE2_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_MODE3_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_MODE4_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_MODE5_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_MODE6_2                      ((uint32_t)0x00000000)
#define GPIO_CRL_MODE7_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_MODE8_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_MODE9_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_MODE10_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_MODE11_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_MODE12_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_MODE13_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_MODE14_2                      ((uint32_t)0x00000000)
#define GPIO_CRH_MODE15_2                      ((uint32_t)0x00000000)

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

extern uint8_t signal;


/*Macro calls*/
GPIO_LIST_CONFIGURE(GPIO_Configure_DELC)

void GPIO_Initialization(void);
uint8_t GPIO_ReadPin(GPIO_TypeDef* GPIO_Port, uint8_t pin_pos_u8);
void GPIO_WritePin(GPIO_TypeDef* GPIO_Port, uint8_t pin_pos_u8, uint8_t value_u8);

#endif
