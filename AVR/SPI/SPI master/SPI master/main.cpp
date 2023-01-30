/*
 * SPI master.cpp
 *
 * Created: 18/7/2020 10:13:02 AM
 * Author : STAR
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SS      PINB4
#define MOSI    PINB5
#define MISO    PINB6
#define SCK     PINB7


void SPI_InitMaster(void)
{
	DDRB |= (1 << SS) | (1 << MOSI) | (1 << SCK);					 //SS,MOSI,SCK as output & MISO as input
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);	 //Enable SPI , Master Mode , SCK Freq = Fosc/128
}


void SPI_SendByte(char data)
{

	SPDR= data;
	while( (SPSR & 1<<SPIF) ==0);
	
}

void SPI_String(char* str)
{
	unsigned char i=0;
	while(str[i] != '\0')
	{
		
		SPI_SendByte(str[i]);
		i++;
	}
}


int main(void)
{
	SPI_InitMaster();

	SPI_SendByte(1);
	SPI_SendByte(10);
}

