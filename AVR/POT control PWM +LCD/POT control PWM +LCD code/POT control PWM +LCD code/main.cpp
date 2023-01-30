#define F_CPU 1000000UL
#include <avr/io.h>
#include "util/delay.h"
#include <stdlib.h>


#define LCD_Data_Dir DDRB		/* Define LCD data port direction */
#define LCD_Command_Dir DDRC		/* Define LCD command port direction register */
#define LCD_Data_Port PORTB		/* Define LCD data port */
#define LCD_Command_Port PORTC		/* Define LCD data port */
#define RS PC0				/* Define Register Select (data/command reg.)pin */
#define RW PC1				/* Define Read/Write signal pin */
#define EN PC2				/* Define Enable signal pin */

void ADC_Init()
{
	DDRA=0X00; //make ADC as inputs
	ADMUX=0X40; //ADC Channel 0, Vref= AVcc ,Right adjustment ADLAR=0
	ADCSRA=0X83; //ADC Enable ,ADC Prescaler= 8
}

int ADC_analogread(char channel)  //return digital value (0-1023)
{
	ADMUX |= channel ; //set input channel to read
	ADCSRA |= 1<<ADSC;	//Start conversion
	while ( (ADCSRA & (1<<ADIF)) ==0 ); //Wait till conversion is done
	_delay_us(10);
	return ( ADCL + (ADCH<<8) ) ; //return Digital value

}



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
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_Command (0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);		/* Display ON Cursor OFF */
	LCD_Command (0x06);		/* Auto Increment cursor */
	LCD_Command (0x01);		/* Clear display */
	LCD_Command (0x80);		/* Cursor at home position */
}

void LCD_String (char* str)		// Send string to LCD function */
{
int i;
for(i=0;str[i]!='\0';i++)		/* Send each char of string till the NULL */
{
LCD_Char (str[i]);
}
}
void LCD_Clear()
{
LCD_Command (0x01);		/* clear display */
LCD_Command (0x80);		/* cursor at home position */
}

void Timer1_Init() //FastPWM_TopOCR1A_Noninverted_Noprescale
{
TCCR1A= 0X23;
TCCR1B= 0X19;
OCR1A= 1023;
}


int main(void)
{
LCD_Init();
ADC_Init();
Timer1_Init();

int Digital_value=0;
double Analog_value=0;
double Dutycycle=0;
double freq=0;

char Digital_value_string [5]; //5 characters including null
char Analog_value_string [6];
char Dutycycle_string[4]; //3 charcters as if it is 100 plus 1 charcter for null
char freq_string[5];

while (1)
{

Digital_value = ADC_analogread(PINA0);
Analog_value = Digital_value*(5.0/1023);
OCR1B= Digital_value; //By that we control duty cycle of wave generated at OC1B as Duty Cycle = (OCR1B/Top)*100 where Top of counter is OCR1A = 1023.

Dutycycle= ((OCR1B+1.0)/(OCR1A+1))*100.0;
freq=F_CPU/(OCR1A+1.0);


itoa(Digital_value,Digital_value_string,10);
dtostrf(Analog_value,5,3,Analog_value_string);
dtostrf(Dutycycle,3,1,Dutycycle_string);
itoa(freq,freq_string,10);

LCD_String("Dg=");
LCD_String(Digital_value_string);
LCD_String(" A=");
LCD_String(Analog_value_string);
LCD_String("v ");

LCD_Command(0XC0); //next line
LCD_String("D="); //D represents Duty Cycle
LCD_String(Dutycycle_string);
LCD_Command(0XC6);
LCD_String("% ");
LCD_String("F=");
LCD_String(freq_string);
LCD_String("Hz");

_delay_ms(1000);
LCD_Clear();




}
}