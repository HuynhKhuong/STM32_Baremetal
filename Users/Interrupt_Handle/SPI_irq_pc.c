#include "SPI_irq_pc.h"
#include <stdio.h>

//Data container
SPI_Data_buffer SPI1_data_container_str = {NULL, NULL, 0,0,0,0}; 
SPI_Data_buffer SPI2_data_container_str = {NULL, NULL, 0,0,0,0}; 
static uint8_t first_received_time_u8 = 1;
//Interrupt handler supported by MCU
#define SPI_Communication_Handler(SPI_BLOCK, NA1, NA2, NA3, NA4, NA5)                           \
                                                                                      \
/*Static function handles the process in the middle of communication*/                \
static void SPI_BLOCK##_TXE_interrupt(void){                                          \
    /*handle if this is the last byte*/                                               \
    uint8_t finished_transmitted_u8 = (SPI_BLOCK##_data_container_str.transmitt_buffer_length == SPI_BLOCK##_data_container_str.transmitt_buffer_index); \
    if(finished_transmitted_u8){                                                      \
      /*finished transmit, call cplt call-back function*/                               \
      /*Complete transmitt Via SPI, disable the communication and interrupt as well*/   \
      uint8_t is_busy_u8 = 1;                                                           \
      while(is_busy_u8){                                                                \
        /*Wait until busy flag is reset*/                                                 \
        is_busy_u8 = (SPI1->SR & SPI_SR_BSY) >> 7; /*7 is bit position of BUSY FLASG*/    \
      }\
      (SPI_BLOCK)->CR1 &= ~(SPI_CR1_SPE);                                                 \
      (SPI_BLOCK)->CR2 &= ~(SPI_CR2_TXEIE);                                               \
      /*Clear data container*/                                                            \
      SPI_BLOCK##_data_container_str.transmitt_buffer = NULL;                              \
      SPI_BLOCK##_data_container_str.transmitt_buffer_length = 0;                         \
      SPI_BLOCK##_data_container_str.transmitt_buffer_index = 0;                          \
      SPI_BLOCK##_cplt_Comm();                                                   \
    }                                                                                 \
    else{                                                                             \
      (SPI_BLOCK)->DR =  SPI_BLOCK##_data_container_str.transmitt_buffer[SPI_BLOCK##_data_container_str.transmitt_buffer_index]; \
      SPI_BLOCK##_data_container_str.transmitt_buffer_index++;                        \
    }                                                                                 \
}                                                                                     \
/*Static function handles the process in the middle of communication*/                \
static void SPI_BLOCK##_RXE_interrupt(void){                                          \
		SPI_BLOCK##_data_container_str.receive_buffer[SPI_BLOCK##_data_container_str.receive_buffer_index] =(SPI_BLOCK)->DR;  \
    /*handle if this is the last byte*/                                               \
    uint8_t finished_received_u8 = (SPI_BLOCK##_data_container_str.receive_buffer_length == (SPI_BLOCK##_data_container_str.receive_buffer_index +1)); \
		if(finished_received_u8){                                                      \
      /*finished receive, call cplt call-back function*/                               \
      /*Clear data container*/                                                            \
      SPI_BLOCK##_data_container_str.receive_buffer = NULL;                              \
      SPI_BLOCK##_data_container_str.receive_buffer_length = 0;                         \
      SPI_BLOCK##_data_container_str.receive_buffer_index = 0;                          \
      SPI_BLOCK##_cplt_Comm();                                                   \
    }                                                                                 \
    else{                                                                             \
      /*The read from DR register clears RXNE flag*/\
      SPI_BLOCK##_data_container_str.receive_buffer_index++;                        \
    }                                                                                 \
}                                                                                     \
\
  void SPI_BLOCK##_IRQHandler(void){                                                  \
    /*Check Rx or Tx interrupt*/                                                        \
    uint8_t isTxInterrupt_u8;                                                       \
    uint8_t isRxInterrupt_u8;                                                       \
                                                                                    \
    isTxInterrupt_u8 = ((SPI_BLOCK)->SR & 0x02) >> 1; /*bit 1 is TXE interrupt*/     \
		isTxInterrupt_u8 &= ((SPI_BLOCK)->CR2 & 0x80) >> 7; /*bit 6 is TXE enable*/       \
    isRxInterrupt_u8 = ((SPI_BLOCK)->SR & 0x01); /*bit 0 is RXNE interrupt*/           \
    isRxInterrupt_u8 &= ((SPI_BLOCK)->CR2 & 0x40) >> 6; /*bit 0 is RXNE interrupt*/     \
		\
    if(isTxInterrupt_u8){                                                           \
      SPI_BLOCK##_TXE_interrupt();                                                  \
    }                                                                               \
    if(isRxInterrupt_u8){                                                           \
      SPI_BLOCK##_RXE_interrupt();                                                  \
    }                                                                               \
}


#define SPI_1_LIST(ENTRY_LIST) \
	ENTRY_LIST(SPI1, NA1, NA2, NA3, NA4, NA5)

//SPI_LIST(SPI_Communication_Handler) 

//SPI_1_LIST(SPI_Communication_Handler) //Handle interrupt for defined SPI peripherals

/*Static function handles the process in the middle of communication*/                
static void SPI2_TXE_interrupt(void){                                          
    /*handle if this is the last byte*/                                               
    uint8_t finished_transmitted_u8 = (SPI2_data_container_str.transmitt_buffer_length == SPI2_data_container_str.transmitt_buffer_index); 
    if(finished_transmitted_u8){                                                      
      /*finished transmit, call cplt call-back function*/                               
      /*Complete transmitt Via SPI, disable the communication and interrupt as well*/   
      uint8_t is_busy_u8 = 1;                                                           
      while(is_busy_u8){                                                                
        /*Wait until busy flag is reset*/                                                 
        is_busy_u8 = (SPI1->SR & SPI_SR_BSY) >> 7; /*7 is bit position of BUSY FLASG*/    
      }
      (SPI2)->CR1 &= ~(SPI_CR1_SPE);                                                 
      (SPI2)->CR2 &= ~(SPI_CR2_TXEIE);                                               
      /*Clear data container*/                                                            
      SPI2_data_container_str.transmitt_buffer = NULL;                              
      SPI2_data_container_str.transmitt_buffer_length = 0;                         
      SPI2_data_container_str.transmitt_buffer_index = 0;                          
      SPI2_cplt_Comm();                                                   
    }                                                                                 
    else{                                                                             
      (SPI2)->DR =  SPI2_data_container_str.transmitt_buffer[SPI2_data_container_str.transmitt_buffer_index]; 
      SPI2_data_container_str.transmitt_buffer_index++;                        
    }                                                                                 
}  

/*Static function handles the process in the middle of communication*/                
static void SPI2_RXE_interrupt(void){
		
		SPI2_data_container_str.receive_buffer[SPI2_data_container_str.receive_buffer_index] =(SPI2)->DR;  
    /*handle if this is the last byte*/                                               
    uint8_t finished_received_u8 = (SPI2_data_container_str.receive_buffer_length == (SPI2_data_container_str.receive_buffer_index +1)); 
		if(finished_received_u8){                                                      
      /*finished receive, call cplt call-back function*/                               
      /*Clear data container*/           
			if(!first_received_time_u8){
				SPI2_data_container_str.receive_buffer = NULL;                              
				SPI2_data_container_str.receive_buffer_length = 0;                         
				SPI2_data_container_str.receive_buffer_index = 0;                          
				SPI2_cplt_Comm();       
			}				
			first_received_time_u8 = 0;
    }                                                                                 
    else{                                                                             
      /*The read from DR register clears RXNE flag*/
      SPI2_data_container_str.receive_buffer_index++;                        
    }              
	}

void SPI2_IRQHandler(void){
    /*Check Rx or Tx interrupt*/                                                        
    uint8_t isTxInterrupt_u8;                                                       
    uint8_t isRxInterrupt_u8;                                                       
                                                                                    
    isTxInterrupt_u8 = ((SPI2)->SR & 0x02) >> 1; /*bit 1 is TXE interrupt*/         
		isTxInterrupt_u8 &= ((SPI2)->CR2 & 0x80) >> 7; /*bit 6 is TXE enable*/         
    isRxInterrupt_u8 = ((SPI2)->SR & 0x01); /*bit 0 is RXNE interrupt*/             
    isRxInterrupt_u8 &= ((SPI2)->CR2 & 0x40) >> 6; /*bit 0 is RXNE interrupt*/                                                                        
    if(isTxInterrupt_u8){                                                           
      SPI2_TXE_interrupt();                                                  
    }                                                                               
    if(isRxInterrupt_u8){                                                           
      SPI2_RXE_interrupt();                                                  
    }            
}


/*Static function handles the process in the middle of communication*/                
static void SPI1_TXE_interrupt(void){                                          
    /*handle if this is the last byte*/                                               
    uint8_t finished_transmitted_u8 = (SPI1_data_container_str.transmitt_buffer_length == SPI1_data_container_str.transmitt_buffer_index); 
    if(finished_transmitted_u8){                                                      
      /*finished transmit, call cplt call-back function*/                               
      /*Complete transmitt Via SPI, disable the communication and interrupt as well*/   
      uint8_t is_busy_u8 = 1;                                                           
      while(is_busy_u8){                                                                
        /*Wait until busy flag is reset*/                                                 
        is_busy_u8 = (SPI1->SR & SPI_SR_BSY) >> 7; /*7 is bit position of BUSY FLASG*/    
      }
      (SPI1)->CR1 &= ~(SPI_CR1_SPE);                                                 
      (SPI1)->CR2 &= ~(SPI_CR2_TXEIE);                                               
      /*Clear data container*/                                                            
      SPI1_data_container_str.transmitt_buffer = NULL;                              
      SPI1_data_container_str.transmitt_buffer_length = 0;                         
      SPI1_data_container_str.transmitt_buffer_index = 0;                          
      SPI1_cplt_Comm();                                                   
    }                                                                                 
    else{                                                                             
      (SPI1)->DR =  SPI1_data_container_str.transmitt_buffer[SPI1_data_container_str.transmitt_buffer_index]; 
      SPI1_data_container_str.transmitt_buffer_index++;                        
    }                                                                                 
}  

/*Static function handles the process in the middle of communication*/                
static void SPI1_RXE_interrupt(void){                                          
		SPI1_data_container_str.receive_buffer[SPI1_data_container_str.receive_buffer_index] =(SPI1)->DR;  
    /*handle if this is the last byte*/                                               
    uint8_t finished_received_u8 = (SPI1_data_container_str.receive_buffer_length == (SPI1_data_container_str.receive_buffer_index +1)); 
		if(finished_received_u8){                                                      
      /*finished receive, call cplt call-back function*/                               
      /*Clear data container*/                                                            
      SPI1_data_container_str.receive_buffer = NULL;                              
      SPI1_data_container_str.receive_buffer_length = 0;                         
      SPI1_data_container_str.receive_buffer_index = 0;                          
      SPI1_cplt_Comm();                                                   
    }                                                                                 
    else{                                                                             
      /*The read from DR register clears RXNE flag*/
      SPI1_data_container_str.receive_buffer_index++;                        
    }              
	}

void SPI1_IRQHandler(void){
    /*Check Rx or Tx interrupt*/                                                        
    uint8_t isTxInterrupt_u8;                                                       
    uint8_t isRxInterrupt_u8;                                                       
                                                                                    
    isTxInterrupt_u8 = ((SPI1)->SR & 0x02) >> 1; /*bit 1 is TXE interrupt*/         
		isTxInterrupt_u8 &= ((SPI1)->CR2 & 0x80) >> 7; /*bit 6 is TXE enable*/         
    isRxInterrupt_u8 = ((SPI1)->SR & 0x01); /*bit 0 is RXNE interrupt*/             
    isRxInterrupt_u8 &= ((SPI1)->CR2 & 0x40) >> 6; /*bit 0 is RXNE interrupt*/                                                                        
    if(isTxInterrupt_u8){                                                           
      SPI1_TXE_interrupt();                                                  
    }                                                                               
    if(isRxInterrupt_u8){                                                           
      SPI1_RXE_interrupt();                                                  
    }            
}
