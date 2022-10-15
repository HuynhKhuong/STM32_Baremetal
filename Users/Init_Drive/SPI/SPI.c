#include "SPI_.h"

//Declare SPI hardware configurations for Lowlayer process 

SPI_LL_conf_st SPI_hardware_conf[2] = {
  /* SPI1 handle */
  {
    SPI1, //SPI1 instance handled by hardware
    SPI1_data_container_str//Initialization for data container for lowerlayer
  },

  /* SPI2 handle */
  {
    SPI2,
    SPI2_data_container_str//Initialization for data container for lowerlayer
  }
};
