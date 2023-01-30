#define F_CPU 1000000UL
#include <avr/io.h>
#include "util/delay.h"
#include <stdlib.h>

#define SS      PINB4
#define MOSI    PINB5
#define MISO    PINB6
#define SCK     PINB7

#define LCD_Data_Dir DDRD		   /* Define LCD data port direction */
#define LCD_Command_Dir DDRC	   /* Define LCD command port direction register */
#define LCD_Data_Port PORTD		   /* Define LCD data port */
#define LCD_Command_Port PORTC	   /* Define LCD data port */
#define RS PC0				       /* Define Register Select (data/command reg.)pin */
#define RW PC1				       /* Define Read/Write signal pin */
#define EN PC2				       /* Define Enable signal pin */


void LCD_Command(unsigned char cmnd)
{
	LCD_Data_Port= cmnd;
	LCD_Command_Port &= ~(1<<RS);	/* RS=0 command reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 Write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(3);
}

void LCD_Char (unsigned char char_data)	/* LCD data write function */
{
	LCD_Data_Port= char_data;
	LCD_Command_Port |= (1<<RS);	/* RS=1 Data reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable Pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}

void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_Command_Dir = 0xFF;		/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0xFF;		/* Make LCD data port direction as o/p */
	_delay_ms(20);			    /* LCD Power ON delay always >15ms */
	
	LCD_Command (0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);		/* Display ON Cursor OFF */
	LCD_Command (0x06);		/* Auto Increment cursor */
	LCD_Command (0x01);		/* Clear display */
	LCD_Command (0x80);		/* Cursor at home position */
}

void LCD_String (char* str)		/* Send string to LCD function */
{
for(int i = 0 ; str[i]!= '\0' ; i++)		/* Send each char of string till the NULL */
{
LCD_Char (str[i]);
}
}
void LCD_Clear()
{
LCD_Command (0x01);		/* clear display */
LCD_Command (0x80);		/* cursor at home position */
}

void SPI_InitSlave(void)
{
DDRB |=  (1 << MISO); //SS,MOSI,SCK as input & MISO as output
SPCR |= 1<<SPE;  //Enable SPI , Slave Mode
}

char SPI_receiveByte(void)
{

while( (SPSR & 1<<SPIF) ==0);
char access_variable;
access_variable=SPDR; //clear flag
return(SPDR);
}

char* SPI_Recieve_String( int String_length)
{
char* word ="";
for(int i=0;i<String_length;i++)
{
while( (SPSR & 1<<SPIF) ==0);
word += SPDR ;
}
return word;
}



int main(void)
{


DDRD=0XFF;
SPI_InitSlave();
PORTD= SPI_receiveByte();

}