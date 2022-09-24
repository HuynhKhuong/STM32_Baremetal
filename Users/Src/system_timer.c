#include "system_timer.h"


void Systick_Initialization(uint32_t reload_val_u32){
    /*
        + Program reload value
        + Clear current value
        + Program control and Status register
    */
    
    //by default, Systick would count 1ms
    //Meaning that counter would count: 72MHz/1kHz = 72000 ticks
    //SysTick->LOAD = ((reload_val_u32)&0x00FFFFFF);
    uint32_t temp_reload_val_u32 = (uint32_t)71999;
    SysTick->LOAD = ((temp_reload_val_u32)&0x00FFFFFF);
    SysTick->VAL = 0;

    //Program control
    /*Disable counter*/
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE) ;

    /*Disable interrupt*/
    __set_PRIMASK(1);

    /*Enable Interrupt request*/
    SysTick->CTRL |= SysTick_CTRL_TICKINT ;

    /*Choose Internal clock source*/
    /*Note that external clock source = AHB/8*/
    /*Internal clock source = AHB*/

    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE ;

    /*Enable counter*/
    __set_PRIMASK(0);
    SysTick->CTRL |= SysTick_CTRL_ENABLE ;
}

uint32_t get_Systick(void){
  return ((SysTick->VAL) & 0x00FFFFFF);
}

static void set_Systick(uint32_t set_val_u32){
  /*Disable counter*/
  SysTick->CTRL &= ~(SysTick_CTRL_ENABLE) ;

  /*Update counter*/
  SysTick->LOAD = ((set_val_u32)&0x00FFFFFF);
  SysTick->VAL = 0;

  /*Enable counter */
  SysTick->CTRL |= SysTick_CTRL_ENABLE;
}

uint32_t wait_tick_u32;

/*
  @brief: This function would return once the systick counts to 1ms. 
          The timing would be calculated based on input clock speed and reload value
          (Via Systick exception handler)
*/
void Delay_ms_tick(uint32_t num_of_ms_u32){
    wait_tick_u32 = num_of_ms_u32;
    while(wait_tick_u32 > 0);
}

//Exception handler

void SysTick_Handler(void){
  /*Systick_Handler would be invoked every time systick counts to 0*/
  /*Meaning it would be set every 1ms*/
  wait_tick_u32 = (wait_tick_u32 == 0)? 0 : (wait_tick_u32 - 1);
}
