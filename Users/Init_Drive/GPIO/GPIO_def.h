#ifndef __GPIO_DEF_H__
#define __GPIO_DEF_H__

#include "stm32f407xx.h"

/*Bit position for set/reset BSRR register*/

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
#define GPIO_PIN_16                     ((uint32_t)0x00010000)        /*!< Port x Reset bit 0 */
#define GPIO_PIN_17                     ((uint32_t)0x00020000)        /*!< Port x Reset bit 1 */
#define GPIO_PIN_19                     ((uint32_t)0x00040000)        /*!< Port x Reset bit 2 */
#define GPIO_PIN_20                     ((uint32_t)0x00080000)        /*!< Port x Reset bit 3 */
#define GPIO_PIN_21                     ((uint32_t)0x00100000)        /*!< Port x Reset bit 4 */
#define GPIO_PIN_22                     ((uint32_t)0x00200000)        /*!< Port x Reset bit 5 */
#define GPIO_PIN_23                     ((uint32_t)0x00400000)        /*!< Port x Reset bit 6 */
#define GPIO_PIN_24                     ((uint32_t)0x00800000)        /*!< Port x Reset bit 7 */
#define GPIO_PIN_25                     ((uint32_t)0x01000000)        /*!< Port x Reset bit 8 */
#define GPIO_PIN_26                     ((uint32_t)0x02000000)        /*!< Port x Reset bit 9 */
#define GPIO_PIN_27                    ((uint32_t)0x04000000)        /*!< Port x Reset bit 10 */
#define GPIO_PIN_28                    ((uint32_t)0x08000000)        /*!< Port x Reset bit 11 */
#define GPIO_PIN_29                    ((uint32_t)0x10000000)        /*!< Port x Reset bit 12 */
#define GPIO_PIN_30                    ((uint32_t)0x20000000)        /*!< Port x Reset bit 13 */
#define GPIO_PIN_31                    ((uint32_t)0x40000000)        /*!< Port x Reset bit 14 */
#define GPIO_PIN_32                    ((uint32_t)0x80000000)        /*!< Port x Reset bit 15 */


/*Values configuring GPIO basic register*/
#define GPIO_MODER_MODE0_2                ((uint32_t)0x00000000)
#define GPIO_MODER_MODE1_2                ((uint32_t)0x00000000)
#define GPIO_MODER_MODE2_2                ((uint32_t)0x00000000)
#define GPIO_MODER_MODE3_2                ((uint32_t)0x00000000)                                
#define GPIO_MODER_MODE4_2                ((uint32_t)0x00000000)
#define GPIO_MODER_MODE5_2                ((uint32_t)0x00000000)
#define GPIO_MODER_MODE6_2                ((uint32_t)0x00000000)
#define GPIO_MODER_MODE7_2               ((uint32_t)0x00000000)
#define GPIO_MODER_MODE8_2              ((uint32_t)0x00000000)
#define GPIO_MODER_MODE9_2               ((uint32_t)0x00000000)
#define GPIO_MODER_MODE10_2                ((uint32_t)0x00000000)
#define GPIO_MODER_MODE11_2               ((uint32_t)0x00000000)
#define GPIO_MODER_MODE12_2                ((uint32_t)0x00000000)
#define GPIO_MODER_MODE13_2                ((uint32_t)0x00000000)
#define GPIO_MODER_MODE14_2                ((uint32_t)0x00000000)
#define GPIO_MODER_MODE15_2                ((uint32_t)0x00000000)

#define GPIO_OTYPER_OT0_2                   ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT1_2                   ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT2_2                   ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT3_2                   ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT4_2                   ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT5_2                   ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT6_2                   ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT7_2                   ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT8_2                   ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT9_2                   ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT10_2                  ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT11_2                  ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT12_2                  ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT13_2                  ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT14_2                  ((uint32_t)0x00000000)
#define GPIO_OTYPER_OT15_2                  ((uint32_t)0x00000000)

#define GPIO_OSPEEDER_OSPEED0_2                  ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED1_2                  ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED2_2                  ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED3_2                  ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED4_2                  ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED5_2                  ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED6_2                  ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED7_2                  ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED8_2                  ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED9_2                  ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED10_2                 ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED11_2                 ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED12_2                 ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED13_2                 ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED14_2                 ((uint32_t)0x00000000)
#define GPIO_OSPEEDER_OSPEED15_2                 ((uint32_t)0x00000000)

#define GPIO_PUPDR_PUPD0_2                  ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD1_2                  ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD2_2                  ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD3_2                  ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD4_2                  ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD5_2                  ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD6_2                  ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD7_2                  ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD8_2                  ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD9_2                  ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD10_2                 ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD11_2                 ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD12_2                 ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD13_2                 ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD14_2                 ((uint32_t)0x00000000)
#define GPIO_PUPDR_PUPD15_2                 ((uint32_t)0x00000000)

//Mapping bit index to actual position in register
extern const uint32_t bit_position_val_tbl[32];

#endif
