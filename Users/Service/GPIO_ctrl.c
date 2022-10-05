#include "GPIO_ctrl.h"

/* Bitwise Operation on Register */ 
/* Convert bit position (uint8_t value) to the real position in the register*/
#define GPOutput_bit_write(GPIO_Port, bit)  SET_BIT(GPIO_Port, bit) 
#define GPOutput_bit_clear(GPIO_Port, bit)  CLEAR_BIT(GPIO_Port, bit)
#define GPOutput_clear_value(GPIO_Port) (GPIO_Port = (uint32_t)0) 
#define GPOutput_set_value(GPIO_Port, val_u32)  (GPIO_Port= val_u32)
#define GPPort_pinread(GPIO_Port, bit_pos) (((GPIO_Port) & (bit_position_val_tbl[bit_pos])) >> bit_pos)

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
      GPOutput_set_value(GPIO_Port->BSRR, bit_position_val_tbl[pin_pos_u8]);
    }
    else { //set bit Output to 0
      GPOutput_set_value(GPIO_Port->BSRR, bit_position_val_tbl[reset_pos_u8]);
    }
}

