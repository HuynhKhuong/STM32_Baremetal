#ifndef __SYS_TICK_SERV_H__
#define __SYS_TICK_SERV_H__

#include "system_timer.h"
#include "sys_tick_irq.h"

void Delay_ms_tick(uint32_t num_of_ms_u32);

//These functions should not be visible as using it carelessly would make system vulnerable
static void set_Systick(uint32_t set_val_u32);
static uint32_t get_Systick(void);

#endif 