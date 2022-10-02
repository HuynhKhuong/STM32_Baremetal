#ifndef __SYSTEM_TIMER_H__
#define __SYSTEM_TIMER_H__

/*
  @Author: Huynh Khuong
  @Brief: This is the driver manipulating systick timer of Arm Cortex M3. This driver is built from CMSIS library, which 
  impacts directly to registers  
*/


#include "stm32f10x.h"

/*
  Arm Cortex M3 CPU has its own 24-bit timer which is called System_timer/systick
  That counts down from the reload value to zero, reloads the value of SYST_RVR register on the next clock edge
  This device lib provides API to access to systick 

  There are 4 registers to manipulate the Systick:
  - SYST_CSR
  - SYST_RVR
  - SYST_CVR
  - SYST_CALIB

  For more info: Read Arm Cortex M3 manual reference
  
  Usage hints and tips: 
  - The correct initialization sequence for the Systick counter is: 
    + Program reload value
    + Clear current value
    + Program control and Status register
  
  To configure its source clock, you have to take more time investigating these register:
  - RCC_CR: Which clock source is enable/ready
  - RCC_CFGR: Which clock source is used as SYSCLOCK; its multiplying parameters as well as other functions

  In application: Clock source is used as HSE -> PREDIV1 (= 1) -> PLL_MUL (= 9) = 8*9 = 72MHz

  Note that systick priority is set to -1, means that it cannot be set using NVIC_enable(). Therefore, systick interrupt would always
  be declared with NVIC. 
  
  To disable systick interrupt, use PRIMASK register. It would disable all interrupts with configurable priority.

  Systick register locates in 'core_cm3.h'
*/
/* Function declaration */

void Systick_Initialization(uint32_t reload_val_u32);


#endif
