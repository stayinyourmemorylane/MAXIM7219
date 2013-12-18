/*
 * MAX7219.c
 *
 * Created: 2/7/2013 9:31:01 PM
 *  Author: Michael
 */ 

#include "max7219.h"
#include <avr/io.h>

char array[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, //  space
	0x00, 0x00, 0xFD, 0x00, 0x00, //  !
	0x00, 0x00, 0x00, 0x00, 0x00, //   " not done
	0x24, 0xFF, 0x24, 0xFF, 0x24, //  #
	0x12, 0x2A, 0x7F, 0x2A, 0x24, //  $
	0x00, 0x00, 0x00, 0x00, 0x00, //    % not done
	0x76, 0x89, 0x95, 0x62, 0x05, //  &
	0x00, 0x00, 0x00, 0x00, 0x00, //    ' not done
	0x00, 0x3C, 0x42, 0x81, 0x00, //  (
	0x00, 0x81, 0x42, 0x3C, 0x00, //  )
	0x00, 0x00, 0x00, 0x00, 0x00, //  * not done
	0x08, 0x08, 0x3E, 0x08, 0x08, //  "+"
	0x00, 0x00, 0x00, 0x00, 0x00, // , not done
	0x08, 0x08, 0x08, 0x08, 0x08, //  -
	0x00, 0x00, 0x00, 0x00, 0x00, // . period not done
	0x00, 0x00, 0x00, 0x00, 0x00, //      /  not done
	0x7E, 0x89, 0x91, 0xA1, 0x7E, //  0
	0x00, 0x41, 0xFF, 0x01, 0x00, //  1
	0x43, 0x85, 0x89, 0x91, 0x61, //  2
	0x42, 0x81, 0x91, 0x91, 0x6E, //  3
	0x18, 0x28, 0x48, 0xFF, 0x08, //  4
	0xF2, 0x91, 0x91, 0x91, 0x8E, //  5
	0x1E, 0x29, 0x49, 0x89, 0x86, //  6
	0x80, 0x8F, 0x90, 0xA0, 0xC0, //  7
	0x6E, 0x91, 0x91, 0x91, 0x6E, //  8
	0x70, 0x89, 0x89, 0x8A, 0x7C, //  9
	0x00, 0x00, 0x00, 0x00, 0x00, //  : NOT DONE
	0x00, 0x00, 0x00, 0x00, 0x00, //  ;  NOT DONE
	0x08, 0x1C, 0x2A, 0x08, 0x08, //  L arrow
	0x14, 0x14, 0x14, 0x14, 0x14, //  =
	0x10, 0x10, 0x54, 0x38, 0x10, //  R arrow
	0x60, 0x80, 0x8D, 0x90, 0x60, //  ?
	0x66, 0x89, 0x8F, 0x81, 0x7E, //  @
	0x7F, 0x88, 0x88, 0x88, 0x7F, //  A
	0xFF, 0x91, 0x91, 0x91, 0x6E, //  B
	0x7E, 0x81, 0x81, 0x81, 0x42, //  C
	0xFF, 0x81, 0x81, 0x42, 0x3C, //  D
	0xFF, 0x91, 0x91, 0x91, 0x81, //  E
	0xFF, 0x90, 0x90, 0x90, 0x80, //  F
	0x7E, 0x81, 0x89, 0x89, 0x4E, //  G
	0xFF, 0x10, 0x10, 0x10, 0xFF, //  H
	0x81, 0x81, 0xFF, 0x81, 0x81, //  I
	0x06, 0x01, 0x01, 0x01, 0xFE, //  J
	0xFF, 0x18, 0x24, 0x42, 0x81, //  K
	0xFF, 0x01, 0x01, 0x01, 0x01, //  L
	0xFF, 0x40, 0x30, 0x40, 0xFF, //  M
	0xFF, 0x40, 0x30, 0x08, 0xFF, //  N
	0x7E, 0x81, 0x81, 0x81, 0x7E, //  O
	0xFF, 0x88, 0x88, 0x88, 0x70, //  P
	0x7E, 0x81, 0x85, 0x82, 0x7D, //  Q
	0xFF, 0x88, 0x8C, 0x8A, 0x71, //  R
	0x61, 0x91, 0x91, 0x91, 0x8E, //  S
	0x80, 0x80, 0xFF, 0x80, 0x80, //  T
	0xFE, 0x01, 0x01, 0x01, 0xFE, //  U
	0xF0, 0x0C, 0x03, 0x0C, 0xF0, //  V
	0xFF, 0x02, 0x0C, 0x02, 0xFF, //  W
	0xC3, 0x24, 0x18, 0x24, 0xC3, //  X
	0xE0, 0x10, 0x0F, 0x10, 0xE0, //  Y
	0x83, 0x85, 0x99, 0xA1, 0xC1, //  Z
	0x06, 0x29, 0x29, 0x29, 0x1F, //  a
	0xFF, 0x09, 0x11, 0x11, 0x0E, //  b
	0x1E, 0x21, 0x21, 0x21, 0x12, //  c
	0x0E, 0x11, 0x11, 0x09, 0xFF, //  d
	0x0E, 0x15, 0x15, 0x15, 0x0C, //  e
	0x08, 0x7F, 0x88, 0x80, 0x40, //  f
	0x30, 0x49, 0x49, 0x49, 0x7E, //  g
	0xFF, 0x08, 0x10, 0x10, 0x0F, //  h
	0x00, 0x00, 0x5F, 0x00, 0x00, //  i
	0x02, 0x01, 0x21, 0xBE, 0x00, //  j
	0xFF, 0x04, 0x0A, 0x11, 0x00, //  k
	0x00, 0x81, 0xFF, 0x01, 0x00, //  l
	0x3F, 0x20, 0x18, 0x20, 0x1F, //  m
	0x3F, 0x10, 0x20, 0x20, 0x1F, //  n
	0x0E, 0x11, 0x11, 0x11, 0x0E, //  o
	0x3F, 0x24, 0x24, 0x24, 0x18, //  p
	0x10, 0x28, 0x28, 0x18, 0x3F, //  q
	0x1F, 0x08, 0x10, 0x10, 0x08, //  r
	0x09, 0x15, 0x15, 0x15, 0x02, //  s
	0x20, 0xFE, 0x21, 0x01, 0x02, //  t
	0x1E, 0x01, 0x01, 0x02, 0x1F, //  u
	0x1C, 0x02, 0x01, 0x02, 0x1C, //  v
	0x1E, 0x01, 0x0E, 0x01, 0x1E, //  w
	0x11, 0x0A, 0x04, 0x0A, 0x11, //  x
	0x00, 0x39, 0x05, 0x05, 0x3E, //  y
	0x11, 0x13, 0x15, 0x19, 0x11 //  z
};


void writechar(int xcorridnate, char c){
	
		if (xcorridnate >= 0 && xcorridnate <= 3){
		
			for (int x=0; x< 5; x++)
			{
				Send_Max7219((xcorridnate+(x+1)),array[((c-32)*5) + x]);
			}
			Send_Max7219((xcorridnate), 0x00);
			Send_Max7219((xcorridnate+6), 0x00);
		}
		
		
		/// Draw the negative portion of the character
		/// Draw partial char   END<---- 
		if (xcorridnate < 0 && xcorridnate >=-5){
			for (int x=0; x < 5 + xcorridnate; x++)
			{
				Send_Max7219((x+1),array[((c-32)*5) + (x-xcorridnate)]);
			}
			Send_Max7219((xcorridnate+6), 0x00); // only necessary to add space to the right of partial-char
		}

		
		/// Draw the Positive portion of the character
		/// Draw partial char  <---- Start
		if (xcorridnate > 4 && xcorridnate <= 8){
			for (int x=0; x < 9-xcorridnate; x++)
			{
				Send_Max7219((xcorridnate+x),array[((c-32)*5) + (x)]);
			}
		 	Send_Max7219((xcorridnate-1), 0x00); // only necessary to add space to the left of partial-char
		}
		
		
 return 0; 
}

char array2[] = {0xFF};
void writestring(int xcorridnate, char *string){
	while (*string)
	{
		writechar(xcorridnate,*string);
		string++;
		_delay_ms(1000);
	}
}

void writestring_scroll(int xcorridnate, char *string){
	int count=0; 
	while (*string)
	{
		string++;
		count++;
	}
	for (int x=8; x >= (count*(-7)); x--){
	//	writechar()
		
	}	
	
}

void clear_screen(void){
	for (int x=0; x < 8; x++)Send_Max7219(x, 0x00);
}


int main(void)
{
	SPI_MasterInit();  
    Initilize_Max7219();
	clear_screen();

	while (1){ 
			/* for(int x=8; x >= -40; x-- )
			 {
				 writechar(x, 'T');
				 writechar(x+7, 'E');
				 writechar(x+14, 'S');
				 writechar(x+21, 'T');
				 writechar(x+28, '!');
				 writechar(x+35, '!');
				 _delay_ms(1000);
			 }
			 */
			    //   Send_Max7219((1),0x00);
			
				
			for (int x=1; x < 4; x++){
				Send_Max7219((x), 0xFF);
				Send_Max7219((x+1), 0xFF);
				_delay_ms(9000);
				Send_Max7219((x),0x00);
				Send_Max7219((x+1), 0x00);
				}				    
			}	
}
		


		/*

		for(int x=12; x >= -12; x-- )
		{
			writechar(x, 'T');
			_delay_ms(1000);
		}

		 for (int y= 0; y < 90; y++ )
		 {
			 for (int x=0; x< 5; x++)
			 {
				 Send_Max7219((x+1),array[((5*y)+x)]);
			 }
			 Send_Max7219(0x06, 0x00);
			 Send_Max7219(0x07, 0x00);
			 Send_Max7219(0x08, 0x00);
			 _delay_ms(10000);
		 }
		
		
		for (int x=0; x<8; x++ )
		{
			for (int y=1; y< 9; y++)
			{
				Send_Max7219((y),array2[x]);
				_delay_ms(1000);
			}
		}
		
		
	*/