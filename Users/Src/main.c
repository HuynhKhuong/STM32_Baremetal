/* User's Include */
#include "main.h"
#include "GPIO_ctrl.h"
//#include "UART_serv.h"
//#include "Nokia_5110_LCD.h"

/* Users's private macros */

/* Users's private variable*/
  uint8_t inputpin_u8 = 0; 
  uint8_t index_u8 = 0;
  uint8_t pin_write_u8 = 0;
/* Function declarations*/

/*Main function*/
int main() {
  /*
        Clock configure is set as default:
        HSI and no PLL configuration
  */

  /*Hardware configuration */
 USERS_CHOICE(YES, NO,NO, NO)
//  
//	UART_Receive(USART1, &DUMMY_RECEIVE[0], 11);
	
  /* User's Application */

	/*Users's Application initialization*/

  GPIO_WritePin(GPIOD, 12, 1);
  GPIO_WritePin(GPIOD, 13, 1);
  GPIO_WritePin(GPIOD, 14, 1);
  GPIO_WritePin(GPIOD, 15, 1);

	while(1){
		inputpin_u8 = GPIO_ReadPin(GPIOA,0);
    
    if(inputpin_u8 != 0){
      index_u8++;
      index_u8 &= 0x03;
    }
    
    for(int i = 0; i < 4; i++){
      if(i != index_u8) GPIO_WritePin(GPIOD, (uint8_t)(i+12),0);
      else GPIO_WritePin(GPIOD, (uint8_t)(i+12),1);
    }
//		UART_Transmitt(USART1, &DUMMY_TRANSMIT[0], 11);
  }
  return 0;
}


/* User's function definitions*/

