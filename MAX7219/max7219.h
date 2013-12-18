/*
 * max7219.h
 *
 * Created: 2/7/2013 9:33:59 PM
 *  Author: Michael
 */ 


#ifndef MAX7219_H_
#define MAX7219_H_
#include "Spi.h"
#include <util/delay.h>
 #define F_CPU 16000000UL 
#define DECODEMODE  9
#define INTENSITY   10
#define SCANLIMIT   11
#define SHUTDOWN    12
#define DISPLAYTEST 15


#define SPI_CS PORTB2 // Pin10 Chip Select 
#define MAX7219_PINS PORTB

void Initilize_Max7219(void);
void Send_Max7219(char command, char data); // command register,  corresponding data 
void Led_On(char row, char column); /// 7 Segment   binary order (DP,A,B,C,D,E,F,G) 


void Send_Max7219(char command, char data){
	_delay_us(100);
	MAX7219_PINS = (0 << SPI_CS);  // pull CS low 
	SPI_MasterTransmit(command);
	SPI_MasterTransmit(data);
	MAX7219_PINS = (1 << SPI_CS); //pull high
}


void Initilize_Max7219(){  
	Send_Max7219(SHUTDOWN,0x00); // enter shutdown mode
	_delay_ms(1);
	Send_Max7219(SHUTDOWN,0x01); // exit shutdown mode
	_delay_us(250);
	Send_Max7219(INTENSITY, 0x00); // turn on intensity low 2/16 (leds are fucking bright)
	Send_Max7219(DECODEMODE, 0x00); // turn off the decode mode 8x8 led array (no 7 seg)	
	Send_Max7219(SCANLIMIT, 0x07); // Scan limit register sets how many digits are displayed at a time (pg 9) //default is dig 0 only
}


#endif /* MAX7219_H_ */