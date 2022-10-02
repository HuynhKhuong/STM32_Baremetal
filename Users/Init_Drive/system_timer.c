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
