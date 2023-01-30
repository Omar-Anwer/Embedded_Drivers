#include "ADC.h"

void ADC_Init(void)
{	 
	/*
	Internal AREF=2.56V       step size = 2.56/1023 = 2.5 mV.  (more accuracy)
	External AREF=AVCC=5V	  step size = 5/1023 = 4.88 mV.    (less accuracy)   
  */
	ADMUX  |= (1<<REFS0);                 // External AREF = AVCC 
 // ADMUX  |= (1<<ADLAR)                   //@(ADLAR=0)/(10-bit 0-1023)->return(ADC) ADC=ADCL|(ADCH<<8)  
										   //@(ADLAR=1)/(8-bit 0-255)->return(ADCH)
	ADCSRA |= (1<<ADPS0)|(1<< ADPS1) ;	  // Prescaler = 8, Freq/8
	ADCSRA |= (1<<ADIE);                  // Enable Interrupt
	ADCSRA |= (1<<ADEN);			      // Enable ADC Module
	ADCSRA |= (1<<ADSC);                  // Start conversion
	_delay_us(10);                        // wait 10us
}
///////////////////////////////////////////////////////////////////////////////////////////
int ADC_AnalogRead(char channel)                
{
 	channel%=8;                                  // Make Channel value always from PINA0 to PINA07
 	DDRA  &= ~(1<<channel);                      // Set ADC channel as INPUT
	ADMUX  = (ADMUX & 0xE0) | (channel & 0x1F);  // 0xE0 is 11100000(Keep first bits)  0x1F is 00011111 (mask the channels)
	_delay_us(10);                               // wait some time for channel to be selected
 	ADCSRA |= (1<<ADSC);	                     // Start Conversion (SC)
	while ((ADCSRA & (1<<ADIF)) == 0);           // Wait till Conversion is done
	return (ADC) ;                               // Return digital value
	// @(ADLAR=0)/(10-bit 0-1023)->return(ADC) ADC=ADCL|(ADCH<<8)  @(ADLAR=1)/(8-bit 0-255)->return(ADCH)
}
///////////////////////////////////////////////////////////////////////////////////////////