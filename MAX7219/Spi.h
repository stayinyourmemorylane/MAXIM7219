/*
 * Spi.h
 *
 * Created: 12/7/2012 11:55:48 PM
 *  Author: Michael
 */ 
#include <avr/io.h>
#define DD_MOSI PINB3  // Master out slave in //pin 11
#define DD_MISO PINB4  // Master in slave out // pin 12
#define DD_SCK PINB5 // clock  // pin 13 
#define DDR_SPI DDRB   
#define SPI_SS PINB2  // digital pin 10
#define SPI_Pins PORTB // 

void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);

void SPI_MasterInit(void){
	/* set MOSI and SCK out put and all others input */
	DDR_SPI |= (1 << DD_MOSI) | (1<< DD_SCK) | (1 << SPI_SS);
	//DDR_SPI &= ~(1 << DD_MISO);
	/*enable SPI, Master, set clock rate fck/16 */
	//SPSR = 0x01;   // double speed this tends to be troublesome it works most of the time but.... 
	SPCR = (1 << SPE)| (1<< MSTR) | (1<< SPR0) | (1 << SPR1); // pg 173 of data sheet
	SPSR &= (0 << SPI2X);
	// SPE = SPI enable, when high spi is enabled.
	// MSTR = Selects spi master mode when high.
	// SPR0 = SCK frequency = Oscillator Clock Freq/ 16  (see data sheet for more config)
}

void SPI_MasterTransmit(char cData)
{ 
	/* Start Transmission */
	SPDR = cData;    // memory location 0x2E & 0x4E
	// read and write data register used for data transfer. 1 byte max
	/* wait for transmission to complete when transfer is complete flag is set while loop terminates*/
	while (!( SPSR & (1 << SPIF)));
	// SPSR = Spi status register
	/// SPIF when serial transfer is complete the spif flag is set
}
