#include "Nokia_5110_LCD.h"
#include <stdio.h>
#include <stdlib.h>

//Flag value initialization
uint8_t transmit_cplt_b = 0;

NOKIA_5110* NOKIA_5110_ctor(uint8_t V_operation, uint8_t bias_config){
    //GPIO_WritePin(GPIOA, GPIO_PIN_2, 1); 
    NOKIA_5110* const temp_pointer = malloc(sizeof(NOKIA_5110));
    LCD_position_orientation* const LCD_temp_pointer = malloc(sizeof(LCD_position_orientation));

    //Data configuration
    LCD_temp_pointer->X_u8 = 0;
    LCD_temp_pointer->Y_u8 = 0;
    LCD_temp_pointer->data_u8 = 0;

    if(temp_pointer != NULL){
        //Attach the LL peripherals to the current object 
        temp_pointer->bare_metal_config_str.SPI = SPI_1;
        temp_pointer->bare_metal_config_str.Comm_Port = GPIOA;
        temp_pointer->bare_metal_config_str.RS_PIN_u16 = 3;
        temp_pointer->bare_metal_config_str.DC_PIN_u16 = 4;

        //Initial setup for LCD
        temp_pointer->LCD_config_str.V_operation_u8 = V_operation;
        temp_pointer->LCD_config_str.bias_config_u8 = bias_config;
        temp_pointer->LCD_config_str.LCD_ptr = LCD_temp_pointer;
    }

    return temp_pointer;                              
}

void NOKIA_5110_dtor(NOKIA_5110* instance){
    if(instance != NULL) free(instance);
}

void NOKIA_Init(NOKIA_5110* instance){
    /*This is an example of setting up NOKIA LCD, modify it according to your reference*/
    //Initial setup Procedure: 
    /*
        Create signal reset LCD
        Send Command 21H 
        Set VOP
        Set voltage Bias system
        Send Command 20H
        Send command 0CH: select display result in Normal mode
    */
    
    uint8_t LCD_Command_u8 = ENTER_COMMAND_MODE_EX; //entry mode, extended instruction set

    //Reset LCD:
    GPIO_WritePin(instance->bare_metal_config_str.Comm_Port, instance->bare_metal_config_str.RS_PIN_u16, 1);
		
		Delay_ms_tick(1000);
    GPIO_WritePin(instance->bare_metal_config_str.Comm_Port, instance->bare_metal_config_str.RS_PIN_u16, 0);

    //Command mode, D/C pin = 0
    GPIO_WritePin(instance->bare_metal_config_str.Comm_Port, instance->bare_metal_config_str.DC_PIN_u16, 0);

    NOKIA_set_single_data(LCD_Command_u8, instance);

    LCD_Command_u8 = (1<<7)|instance->LCD_config_str.V_operation_u8;
    NOKIA_set_single_data(LCD_Command_u8, instance);

    LCD_Command_u8 = (1<<4)|instance->LCD_config_str.bias_config_u8;
    NOKIA_set_single_data(LCD_Command_u8, instance);
  
    LCD_Command_u8 = ENTER_COMMAND_MODE; //Command set in Basic mode
    NOKIA_set_single_data(LCD_Command_u8, instance);
		
		LCD_Command_u8 = NORMAL_MODE; //NOKIA display in normal mode
    NOKIA_set_single_data(LCD_Command_u8, instance);
}

void NOKIA_set_X(uint8_t X_u8, NOKIA_5110* instance){
    uint8_t is_out_of_bound_b = (X_u8 > 83u); //X address ranges from 0->83
    if(!is_out_of_bound_b){
        instance->LCD_config_str.LCD_ptr->X_u8 = X_u8;
    }
}

void NOKIA_set_Y(uint8_t Y_u8, NOKIA_5110* instance){
    uint8_t is_out_of_bound_b = (Y_u8 > 5u); //Y address ranges from 0->5
    if(!is_out_of_bound_b){
        instance->LCD_config_str.LCD_ptr->Y_u8 = Y_u8;
    }
}

void NOKIA_set_single_data(uint8_t data_u8, NOKIA_5110* instance){
    //setup data and do SPI transmit
    instance->LCD_config_str.LCD_ptr->data_u8 = data_u8;
	  transmit_cplt_b = 1;
    SPI_Write(instance->bare_metal_config_str.SPI, &(instance->LCD_config_str.LCD_ptr->data_u8), 1);

    //Wait until user's flag is reset
    while(transmit_cplt_b){};
}
