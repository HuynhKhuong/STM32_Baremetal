#include "Nokia_5110_LCD.h"
#include "system_timer.h"
#include <stdio.h>
#include <stdlib.h>

//Flag value initialization
uint8_t transmit_cplt_b = 0;


#define PIN_CONFIGURE(GPIO_PORT, pin, Control_Register, bit_value, function, Speed_bit_value) \
        /*Configure pin's function in the register*/\
        /*pin: 0,...15*/\
        /*bit_value: pin, pin_0, pin_1, by default: pin_0, which is the reset value of the register*/\
        /*Speed_bit_value: pin, pin_0, pin_1: by default: pin_2, which is the reset value of the register*/\
        /*Reset bit_value*/\
        ((GPIO_PORT)->Control_Register) &=  ~(GPIO_##Control_Register##_CNF##pin);\
        ((GPIO_PORT)->Control_Register) |=  (GPIO_##Control_Register##_CNF##bit_value);\
        /*Reset speed_bit_value*/\
        ((GPIO_PORT)->Control_Register) &=  ~(GPIO_##Control_Register##_MODE##pin);\
        ((GPIO_PORT)->Control_Register) |=  (GPIO_##Control_Register##_MODE##Speed_bit_value);\
				/*For Input mode, If that pin is configured as pull up/down mode, by default it is pull-down mode*/


#define GPIO_Configuration(GPIO_PORT, AHB_bus, APB_bus, APB_bus_bit_pos, pin_list) \
        /*Procedure: 1. Clock enable for AHB, 2. Clock enable for each port, 3. Pin configuration*/\
        static void GPIO_configure_##GPIO_PORT(void){\
            /*Configure its APB_bus*/\
            RCC->APB_bus##ENR |= APB_bus_bit_pos;  \
            /*Configure its Output Pin*/\
            pin_list(PIN_CONFIGURE) \
        }



//Low layer peripherals initialization
COMM_LIST(SPI_configuration)
//PORT_LIST()
GPIO_Configuration(GPIOA, AHB1, APB2, RCC_APB2ENR_IOPAEN, COMM_PIN_LIST)			

NOKIA_5110* NOKIA_5110_ctor(uint8_t V_operation, uint8_t bias_config){
    //LL configuration

    COMM_LIST(SPI_configuration_funcall)
    PORT_LIST(GPIO_Configure_FuncCall)

    //GPIO_WritePin(GPIOA, GPIO_PIN_2, 1); 
    NOKIA_5110* temp_pointer = malloc(sizeof(NOKIA_5110));
    LCD_position_orientation* LCD_temp_pointer = malloc(sizeof(LCD_position_orientation));

    //Data configuration
    LCD_temp_pointer->X_u8 = 0;
    LCD_temp_pointer->Y_u8 = 0;
    LCD_temp_pointer->data_u8 = 0;

    if(temp_pointer != NULL){
        //Attach the LL peripherals to the current object 
        temp_pointer->bare_metal_config_str.SPI = SPI1;
        temp_pointer->bare_metal_config_str.Comm_Port = GPIOA;
        temp_pointer->bare_metal_config_str.RS_PIN_u16 = GPIO_PIN_3;
        temp_pointer->bare_metal_config_str.DC_PIN_u16 = GPIO_PIN_4;

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
    Delay_ms_tick(10);
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
    SPI_Write(SPI1, &(instance->LCD_config_str.LCD_ptr->data_u8), 1);

    //Wait until user's flag is reset
    transmit_cplt_b = 1;
    while(transmit_cplt_b){};
}
