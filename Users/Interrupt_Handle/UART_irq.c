#include "UART_irq_pc.h"


void USART1_cplt_Transmitt(void){                                                                                 
  /*This function would only be called when the last byte is transmitted*/                                           
  /*User's code*/

}
void USART1_cplt_Receive(void){                                                                                      

  /*This function would only be called when the last byte is transmitted*/                                            
  /*User's code*/
  //UART_Receive(USART1, &DUMMY_RECEIVE[0], 11);                                                                    
}        
