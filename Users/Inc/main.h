#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f10x.h"
/*
  *         CMSIS Cortex-M3 Device Peripheral Access Layer Header File. 
  *          This file contains all the peripheral register's definitions, bits 
  *          definitions and memory mapping for STM32F10x Connectivity line, 
  *          High density, High density value line, Medium density, 
  *          Medium density Value line, Low density, Low density Value line 
  *          and XL-density devices.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The device used in the target application
  *              - To use or not the peripheral’s drivers in application code(i.e. 
  *                code will be based on direct access to peripheral’s registers 
  *                rather than drivers API), this option is controlled by 
  *                "#define USE_STDPERIPH_DRIVER"
  *              - To change few application-specific parameters such as the HSE 
  *                crystal frequency
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral’s registers hardware
*/
//This is the hook including every libraries
//Handle the variant managment 
#include "sys_tick_serv.h"
#include "UART_serv.h"
#include "GPIO_ctrl.h"
#include "SPI_serv.h"

//Initializaiton for GPIO
#define GPIO_CONF(COND)  GPIO_CONF_##COND
#define GPIO_CONF_YES     GPIO_Initialization();
#define GPIO_CONF_NO

//Initializaiton for GPIO
#define UART_CONF(COND)  UART_CONF_##COND
#define UART_CONF_YES     UART_init();
#define UART_CONF_NO

//Initializaiton for GPIO
#define SPI_CONF(COND)  SPI_CONF_##COND
#define SPI_CONF_YES     SPI_init();
#define SPI_CONF_NO

//Initializaiton for GPIO
#define SYS_TICK_CONF(COND)  SYS_TICK_CONF_##COND
#define SYS_TICK_CONF_YES     Systick_Initialization((uint32_t) 0);
#define SYS_TICK_CONF_NO      

//USERs choice
#define USERS_CHOICE(GPIO_ENABLE, SYSTICK_ENABLE, UART_ENABLE, SPI_ENABLE) \
  GPIO_CONF(GPIO_ENABLE) \
  SYS_TICK_CONF(SYSTICK_ENABLE) \
  UART_CONF(UART_ENABLE) \
  SPI_CONF(SPI_ENABLE) \

#endif
