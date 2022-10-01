/* User's Include */
#include "main.h"
#include "GPIO.h"
#include "system_timer.h"
#include "UART.h"
#include "Nokia_5110_LCD.h"
/* Users's private macros */

/* Users's private variable*/
uint8_t DUMMY_TRANSMIT[11] = {'H','E','L','L','O',' ','W','O','R','L','D'};
uint8_t DUMMY_RECEIVE[11] = {0,0,0,0,0,0,0,0,0,0,0};
NOKIA_5110* my_NOKIA_5110;
/* Function declarations*/

/*Main function*/
int main() {
  /*
        Clock configure is set as default:
        HSI and no PLL configuration
  */

  /*Hardware configuration */
  GPIO_Initialization();
	Systick_Initialization(0);
	my_NOKIA_5110 = NOKIA_5110_ctor(0x3F, BIAS_SYSTEM_CONF);
	
	//UART_init();
	//UART_Receive(USART1, &DUMMY_RECEIVE[0], 11);
	
  /* User's Application */
  uint8_t inputpin_u8 = 0; 
	uint8_t output_state = 0;
	/*Users's Application initialization*/
	GPIO_WritePin(GPIOC, 13, 1);
  //NOKIA_Init(my_NOKIA_5110);
	
	while(1){
//    //inputpin_u8 = GPIO_ReadPin(GPIOA, (uint8_t)0);
//		Delay_ms_tick(1000);
//		//UART_Transmitt(USART1, &DUMMY_TRANSMIT[0], 11);
//		output_state = (output_state == 0)?1:0;
//    //if(inputpin_u8 == 1){
//        GPIO_WritePin(GPIOC, 13, output_state);
//    //}
//    //else {
//        //GPIO_WritePin(GPIOC, 13, output_state);
//    //}
  }
  return 0;
}


/* User's function definitions*/

/*
Clock Configuration

1. Configure Clock source: 
	- HSI
	- HSE
	- HLI
	- HLE

2. Configure Clock PLL
3. Configure Bus Clock

RCC has these registers:
 typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t CFGR;
  __IO uint32_t CIR;
  __IO uint32_t APB2RSTR;
  __IO uint32_t APB1RSTR;
  __IO uint32_t AHBENR;
  __IO uint32_t APB2ENR;
  __IO uint32_t APB1ENR;
  __IO uint32_t BDCR;
  __IO uint32_t CSR;
} RCC_TypeDef;

RCC is the peripheral to control clocks
*/
