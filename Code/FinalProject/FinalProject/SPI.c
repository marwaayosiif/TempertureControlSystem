 #include "DIO.h"
 #include "SPI.h"




void SPI_Init(void)
{
    /*Set MOSI, SCK and SS Output*/
    DIO_ChannelDirection((unsigned char)MOSI,(unsigned char)OUT);
    DIO_ChannelDirection((unsigned char)SCK,(unsigned char)OUT);
    DIO_ChannelDirection((unsigned char)SS,(unsigned char)OUT);

     /*Enable SPI Master set clock rate fck/128 data is
     sample at falling edge*/

    /*This justification if we didn't use  avr.h and we talk to memory direct*/
    /* JUSTIFICATION: Mirsa Rule 11.3 => SPCR is And Addres so to access it
     * we should use pointers and on the other side there is data  */

     SPCR = ((unsigned char)(1UL<<SPE))|((unsigned char)(1UL<<MSTR))| ((unsigned char)(1UL<<SPR1))|((unsigned char)(1UL<<SPR0))|((unsigned char)(1UL<<CPHA));


}

void SPI_Transmit(S32 TEMP){


    /*Start the transmission*/

    /*This justification if we didn't use  avr.h and we talk to memory direct*/

    /* JUSTIFICATION: Mirsa Rule 11.3 => SPCR is And Addres so to access it
         * we should use pointers and on the other side there is data  */

    SPDR=(unsigned char)TEMP;

    /*Wait for completion*/

    /*This justification if we didn't use  avr.h and we talk to memory direct*/

    /*JUSTIFICATION: Misra Rule 12.6 => in this line i wait till every bit arrived
     * and then toggle it to leave the while this is the logic
     * so i can't modify this line  */

    /* JUSTIFICATION: Mirsa Rule 11.3 => SPCR is And Addres so to access it
         * we should use pointers and on the other side there is data  */

    while(!(SPSR&((unsigned char)(1UL<<SPIF))) ){
        /*wait*/
        };



}

S32 SPI_Receive(void){

    /*Wait for the SPI buffer's full*/

    /*This justification if we didn't use  avr.h and we talk to memory direct*/

    /*JUSTIFICATION: Misra Rule 12.6 => in this line i wait till every bit arrived
         * and then toggle it to leave the while this is the logic
         * so i can't modify this line  */

    /* JUSTIFICATION: Mirsa Rule 11.3 => SPCR is And Addres so to access it
         * we should use pointers and on the other side there is data  */

    while(!(SPSR&((unsigned char)(1UL<<SPIF))))
    {
        /*wait*/
        };

    /*This justification if we didn't use  avr.h and we talk to memory direct*/

    /* JUSTIFICATION: Mirsa Rule 11.3 => SPCR is And Addres so to access it
         * we should use pointers and on the other side there is data  */

    unsigned char temper = SPDR;
    /*return SPI Buffer*/

    return (S32)temper;
}
