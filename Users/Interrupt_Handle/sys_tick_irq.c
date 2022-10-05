#include "system_timer.h"
#include "sys_tick_irq.h"

//Exception handler
void SysTick_Handler(void){
  /*Systick_Handler would be invoked every time systick counts to 0*/
  /*Meaning it would be set every 1ms*/
  wait_tick_u32 = (wait_tick_u32 == 0)? 0 : (wait_tick_u32 - 1);
}
