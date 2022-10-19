#ifndef __NOKIA_5110_LCD_H__
#define __NOKIA_5110_LCD_H__

#include "SPI_serv.h"
#include "GPIO_ctrl.h"
#include "sys_tick_serv.h"
/*
@Author: Huynh Khuong
@Brief: This library is written as an application which makes used of SPI bare-metal driver to communicate with Nokia-5110 LCD
        This library is built based on C-based Object Oriented programming for studying purpose

@Nokia-5110 LCD:
        - 6(banks)*8*84 dots
        - Setup brightness via VOP and Bias system
@Notes:
    a. LCD Voltage:  (V lcd): Adjust how bright your bright pixels are vs the background one. 
        - Many LCD display modules require a voltage that is higher than the logic voltage used to power an LCD. 
        - The LCD bias voltage is used to power the circuits that drive the LCD glass. This voltage sets the contrast level of the LCD. 
        - LCD voltage: Is generated either by LCD-drive IC (ranges from 6.0 - 8.5) or by external source (from 6. -9. V)
    It could be generated by software using VOP values
        - Users power the LCD-drive IC with logic voltage: 2.7 - 3.3V

    b. Bias system & Mutex system:
        - Mutex: 48
        - n factor: 4
        - Bias voltage levels: 1/8
*/

//CONST values initialization (these values are pre-defined on datasheet)
#define BIAS_SYSTEM_CONF        (0x13)
#define ENTER_COMMAND_MODE_EX   (0x21)
#define ENTER_COMMAND_MODE      (0X20)
#define NORMAL_MODE 						(0x0C)

typedef enum{
	false = 0u,
	true  = 1u,
}bool;

//Flags indicating the completion of SPI transmittion
extern uint8_t transmit_cplt_b;

//Low layer initialization
/* 
    Check If related Low Layer peripherals have been Initialized or not?
    pin: 234, 567 (output)
    SPI1 block
*/

struct vtbl{

};

//Specific configurations for Nokia

typedef struct{
    uint8_t X_u8; //length's position
    uint8_t Y_u8; //bank position 
    uint8_t data_u8;
}LCD_position_orientation;

typedef struct{
    SPI_HANDLES SPI;
    GPIO_TypeDef* Comm_Port;
    uint16_t RS_PIN_u16;
    uint16_t DC_PIN_u16;
}NOKIA_5110_hardware_config;

typedef struct{
    uint8_t V_operation_u8; //Brightness
    uint8_t bias_config_u8; //bias configuration
    LCD_position_orientation* LCD_ptr;
}NOKIA_features_config;

//Main object structure
typedef struct{
    //public attributes
    NOKIA_5110_hardware_config bare_metal_config_str;
    NOKIA_features_config LCD_config_str;

    //vector table for polymorphism
    struct vttb* vtptr;
}NOKIA_5110;

//Methods
NOKIA_5110* NOKIA_5110_ctor(uint8_t V_operation, uint8_t bias_config);
void NOKIA_5110_dtor(NOKIA_5110* instance);
void NOKIA_Init(NOKIA_5110* instance);

void NOKIA_set_X(uint8_t X_u8, NOKIA_5110* instance);
void NOKIA_set_Y(uint8_t Y_u8,NOKIA_5110* instance);
void NOKIA_set_single_data(uint8_t data_u8, NOKIA_5110* instance);

#endif 

/*
APPENDIX: 

1. LCD BIAS

- The control signals that drive an LCD are AC in nature. To control LCDs with a larger multiplex ratio, we need to provide 
the waveform generator with multiple bias voltage level points. 
- The resulting waveform sent to the LCD segment/dot control lines and backplane commons will contain a stair-stepped waveform 
that will maintain specific ac voltages across any given segment/dot to keep it in it's "on" or "off" state 

(or in a grayscale module, states between those two points). The LCD Bias number(example: 1/5 bias) will indicate how many voltage 
reference points are created to drive a specific LCD. 

2. MUTEX: Watch for more info "https://www.pacificdisplay.com/lcd_multiplex_drive.html"

*/
