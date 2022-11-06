#include "system_timer.h"

/**
	This file configures the clock source tree for STM32F4
	Due to Author's limited effort for this project, this files covers only essential RCC source to operate 
	components that the author concerns. These components are: 
	- SYSCLOCK
	- HSE src
	- HSI src
	- APB1/APB2/AHB DIV configuration

*/

/*Configure section for PLL clock*/

typedef enum{
	P_2 = 0x0,
	P_4 = RCC_PLLCFGR_PLLP_0,
	P_6 = RCC_PLLCFGR_PLLP_1,
	P_8 = RCC_PLLCFGR_PLLP,
}P_mapping;

//This section would manipulate RCC_CFGR to choose clock source for PLL
#define PLL_HSI_SRC	(RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;)
#define PLL_HSE_SRC (RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;)

#define PLL_CONF(PLL_SRC, PLL_N, PLL_M, PLL_P) \
					PLL_SRC\
					RCC->PLLCFGR |= PLL_P;\
					RCC->PLLCFGR |= PLL_M;\
					RCC->PLLCFGR |= PLL_N;\

/*Configure section for SYSTEM TICK*/
#define SYS_HSI_SRC (RCC->CFGR |= RCC_CFGR_SW_HSI;)
#define SYS_HSE_SRC	(RCC->CFGR |= RCC_CFGR_SW_HSE;)
#define SYS_PLL_SRC	(RCC->CFGR |= RCC_CFGR_SW_PLL;)    