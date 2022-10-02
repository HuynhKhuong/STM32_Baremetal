#ifndef __GPIO_CTRL_H__
#define __GPIO_CTRL_H__

#include "GPIO.h"
#include "GPIO_irq_pc.h"

uint8_t GPIO_ReadPin(GPIO_TypeDef* GPIO_Port, uint8_t pin_pos_u8);
void GPIO_WritePin(GPIO_TypeDef* GPIO_Port, uint8_t pin_pos_u8, uint8_t value_u8);

#endif 