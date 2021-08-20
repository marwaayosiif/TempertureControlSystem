
#include "TC72.h"


S32 Temperature;

void TC72_Intit(void){

    DIO_ChannelWrite((unsigned char)SS,(unsigned char)HIGH);

    /*Select Control Register*/

    SPI_Transmit(TC72_CONTROL_WRITE);

    /*Select Continuous temperature Conversion*/

    SPI_Transmit(CONTINOUS_TEMP);

    DIO_ChannelWrite((unsigned char)SS,(unsigned char)LOW);

}

S32 Read_Temperature(void)
 {

    DIO_ChannelWrite((unsigned char)SS,(unsigned char)HIGH);

    /*Read the MSB*/

    SPI_Transmit(MSB);

    /*Issue one more clock frame
    to force data out*/

    SPI_Transmit(TC72_CONTROL_READ);

    DIO_ChannelWrite((unsigned char)SS,(unsigned char)LOW);

    Temperature = SPI_Receive();
  
    return Temperature;
 }
  
  
  
    
