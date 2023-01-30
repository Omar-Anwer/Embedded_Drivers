#define F_CPU 8000000UL                  // 8MHz crystal clock rate

#include <avr/io.h>
#include <util/delay.h>

void Timer1_PWM(void)
{
	TCCR1A |= (1<<WGM11)|(1<<WGM10);
	TCCR1B |= (1<<WGM12);                      // fast PWM mode @10-bit
	TCCR1A |= (1<<COM1A1)| (1<<COM1B1);	      // Non-inverted mode
	TCCR1B |= (1<<CS12);                      // Start with No Prescaler
	DDRB   |= (1<<PIND4)|(1<<PIND5);	         // OCR1A,OCR1B PIN is OUTPUT
}


int main(void)
{
	OCR1A = (50/100.0 * 1024) - 1;   
	OCR1B = (80/100.0 * 1024) - 1;  
	Timer1_PWM ();
	
	// Generate 25% Duty Cycle on OCR1A and 75% on OCR1B Pins
}

