#include "sys_tick_serv.h"

//static variable 
uint32_t wait_tick_u32 = 0;

static uint32_t get_Systick(void){
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


/*
  @brief: This function would return once the systick counts to 1ms. 
          The timing would be calculated based on input clock speed and reload value
          (Via Systick exception handler)
*/
void Delay_ms_tick(uint32_t num_of_ms_u32){
    wait_tick_u32 = num_of_ms_u32;
    while(wait_tick_u32 > 0); 
}
