#include "SPI_serv.h"

/*NOTE: MAKE an array of objects:
  SPI
  local_buffers
  these objects are indexed by enum
*/

/*
  Instances are obtained locally inside function
*/
/*
SPI_Write()
@Brief: function handles transmit info from Master to Slave using Interrupt mechanism
*/
void SPI_Write(const SPI_hardware_conf SPI_index, uint8_t* data_u8_array, uint8_t data_length_u8){
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
  SPI_typdef* const SPI_conf = SPI_hardware_conf[SPI_index].SPI; 
  SPI_Data_buffer* const data_container_str = SPI_hardware_conf[SPI_index].SPI_data_containter_str; 

  data_container_str.transmitt_buffer = data_u8_array;
  data_container_str.transmitt_buffer_length = data_length_u8;
  data_container_str.transmitt_buffer_index = 0;

  /*
    Enable SPI's SPI transmission and Transmit interrupt  
  */
  SPI_conf->CR1 |= SPI_CR1_SPE;
  SPI_conf->CR2 |= SPI_CR2_TXEIE;
}
