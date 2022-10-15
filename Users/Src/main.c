/* User's Include */
#include "main.h"
#include "Nokia_5110_LCD.h"
/* Users's private macros */

/* Users's private variable*/
uint8_t DUMMY_TRANSMIT[11] = {'H','E','L','L','O',' ','W','O','R','L','D'};
uint8_t DUMMY_RECEIVE[11] = {0,0,0,0,0,0,0,0,0,0,0};
NOKIA_5110* my_NOKIA5110;
/* Function declarations*/

/*Main function*/
int main() {
  /*
        Clock configure is set as default:
        HSI and no PLL configuration
  */

  /*Hardware configuration */
  USERS_CHOICE(YES, YES,YES, NO)
  
	UART_Receive(USART1, &DUMMY_RECEIVE[0], 11);
	
  /* User's Application */
  uint8_t inputpin_u8 = 0; 
	uint8_t output_state = 0;
	
	/*Users's Application initialization*/
	GPIO_WritePin(GPIOC, 13, 1);
  my_NOKIA5110 = NOKIA_5110_ctor(0x20, 0x13);
	
	while(1){
		Delay_ms_tick(1000);
		UART_Transmitt(USART1, &DUMMY_TRANSMIT[0], 11);
  }
  return 0;
}


/* User's function definitions*/

