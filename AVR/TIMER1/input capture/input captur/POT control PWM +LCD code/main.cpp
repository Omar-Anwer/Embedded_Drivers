#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "LCD.c"
#include <stdlib.h>

void Timer1_Init() //FastPWM_TopOCR1A_Noninverted_Noprescale
{
	TCCR1A = 0;
	TCNT1=0;
	TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag) flag */
	DDRD &= ~(1<<PIND6);

}


int main(void)
{
LCD_init();
Timer1_Init();

unsigned int a,b,c,high,period;

LCD_Char('A');

	while (1)
	{
		

// 		while ((TIFR&(1<<ICF1)) == 0);
// 		a = ICR1;  							/* Take value of capture register */
// 		TIFR = (1<<ICF1);					/* Clear ICF flag */
// 		
// 		TCCR1B = 0x01;  					/* Falling edge, no prescaler */
// 		while ((TIFR&(1<<ICF1)) == 0);
// 		b = ICR1;  							/* Take value of capture register */
// 		TIFR = (1<<ICF1);  					/* Clear ICF flag */
// 		
// 		TCCR1B = 0x41;  					/* Rising edge, no prescaler */
// 		while ((TIFR&(1<<ICF1)) == 0);
// 		c = ICR1;  							/* Take value of capture register */
// 		TIFR = (1<<ICF1);  					/* Clear ICF flag */
				
// 		if (a<b && b<c)
// 		{
// 			high=b-a;
// 			period=c-a;
// 			
// 			long freq= F_CPU/period;									/* Calculate frequency */
// 			float duty_cycle =((float) high /(float)period)*100;	    /* Calculate duty cycle */
// 			
// 			LCD_String("D:");
// 			LCD_float (duty_cycle, 4);
// 			_delay_ms(50);
// 			LCD_Clear();
// 		}
		
	}
	return 0;
}