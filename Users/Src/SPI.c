#include "SPI.h"
#include "Nokia_5110_LCD.h"
#include <stdio.h>
//Data container

static SPI_Data_buffer SPI1_data_container_str = {NULL, NULL, 0,0,0,0}; 
static SPI_Data_buffer SPI2_data_container_str = {NULL, NULL, 0,0,0,0}; 

//Driver's API
/*
SPI_Init()
@Brief: Call macro-defined functions to initialize SPI peripherals

*/
void SPI_init(void){
  /*Call macro func_call right here*/
  SPI_LIST(SPI_configuration_funcall)
}

/*
@Brief: Call macro_defined function's definitions 
*/

SPI_LIST(SPI_configuration)


/*
SPI_Write()
@Brief: function handles transmit info from Master to Slave using Interrupt mechanism
*/
void SPI_Write(SPI_TypeDef* SPI, uint8_t* data_u8_array, uint8_t data_length_u8){
  /*
    Master transmit sequence:
    - The transmit sequence begins when a byte is written in the Tx Buffer.
    - The data byte is parallel-loaded into the shift register (from the internal bus) 
    - During the first bit transmission and then shifted out serially to the MOSI pin MSB first or LSB first
    - The TXE flag is set on the transfer of data from the Tx Buffer to the shift register 
    - The TXE flag is set off when Tx Buffer is written with data

    Software has to follow this procedure for transmitting data:
    1. Enable the SPI by setting the SPE bit to 1.
    2. Write the first data item to be transmitted into the SPI_DR register (this clears the TXE
    flag).
    3. Wait until TXE=1 and write the second data item to be transmitted. Then wait until
    RXNE=1 and read the SPI_DR to get the first received data item (this clears the RXNE
    bit). Repeat this operation for each data item to be transmitted/received until the n–1
    received data.
    4. Wait until RXNE=1 and read the last received data.
    5. Wait until TXE=1 and then wait until BSY=0 before disabling the SPI.
  */
  SPI1_data_container_str.transmitt_buffer = data_u8_array;
  SPI1_data_container_str.transmitt_buffer_length = data_length_u8;
  SPI1_data_container_str.transmitt_buffer_index = 0;

  /*
    Enable SPI's SPI transmission and Transmit interrupt  
  */
  SPI->CR1 |= SPI_CR1_SPE;
  SPI->CR2 |= SPI_CR2_TXEIE;
}

//Interrupt handler
static void SPI1_TXE_interrupt(void){
    /*handle if this is the last byte*/                                                                                 
    uint8_t finished_transmitted_u8 = (SPI1_data_container_str.transmitt_buffer_length == SPI1_data_container_str.transmitt_buffer_index);                                       
                                                                                                                        
    if(finished_transmitted_u8){                                              
        //finished transmit, call cplt call-back function
      SPI1_cplt_Transmitt();
    }                                                                                                                   
    else{
      SPI1->DR =  SPI1_data_container_str.transmitt_buffer[SPI1_data_container_str.transmitt_buffer_index];         
      SPI1_data_container_str.transmitt_buffer_index++;                                                                                  
    }
}

void SPI1_IRQHandler(void){
  /*Check Rx or Tx interrupt*/
  uint8_t isTxInterrupt_u8;
  uint8_t isRxInterrupt_u8;

  isTxInterrupt_u8 = ((SPI1->SR) & 0x02) >> 1; //bit 1 is TXE interrupt
  isRxInterrupt_u8 = ((SPI1->SR) & 0x01); //bit 0 is RXNE interrupt

  if(isTxInterrupt_u8){
    SPI1_TXE_interrupt();
  }
} 

void SPI1_cplt_Transmitt(void){
  //Complete transmitt Via SPI, disable the communication and interrupt as well
  uint8_t is_busy_u8 = 1;
  
  while(is_busy_u8){ 
    /*Wait until busy flag is reset*/
    is_busy_u8 = (SPI1->SR & SPI_SR_BSY) >> 7; //7 is bit position of BUSY FLASG
  }

  SPI1->CR1 &= ~(SPI_CR1_SPE);
  SPI1->CR2 &= ~(SPI_CR2_TXEIE);

  //Clear data container
  SPI1_data_container_str.transmitt_buffer = NULL;
  SPI1_data_container_str.transmitt_buffer_length = 0;
  SPI1_data_container_str.transmitt_buffer_index = 0;

  /*User's application*/
	transmit_cplt_b = 0;
}
