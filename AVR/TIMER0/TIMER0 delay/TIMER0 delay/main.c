/*
 * TIMER0.c
 *
 * Created: 7/10/2020 2:40:27 PM
 * Author : STAR
 */ 

#define F_CPU 8000000UL            // 8 MHz crystal clock rate

#include <avr/io.h>           
#include <util/delay.h>          // for _delay_ms()  and  _delay_us()
#include <avr/interrupt.h>      // for interrupt


volatile unsigned int timer0_Overflow_Count = 0;     // global variable to count the number of overflows
volatile unsigned int timer0_Compare_Count = 0;     // global variable to count the number of compare matches

// initialize timer0 in normal Overflow mode
void Timer0_Overflow_Init(void)
{
	TCNT0 = 0;                             // initialize counter
	TCCR0 = (1 << CS02) | (1 << CS00) ;   // TIMER0, normal mode(overflow), Prescaler = 1024
	OCR0 = 255;                           //Compare value
}

// initialize timer0 in external counter mode
void Timer0_Counter_Init(void)
{
	TCNT0 = 0;                                                           // initialize counter
	TCCR0 = (1 << CS02) | (1 << CS01) | (1 << CS00) ;		            // TIMER0, External clock source on T0 pin (Rising edge)
	DDRB = ~(1 << PINB0);                                              // T0 pin is input
	
// 	if(TCNT0 == 5)                 // press the button for 5 times
// 	{
// 		PORTB |= (1 << PINB1);
// 		_delay_ms(1000);
// 		PORTB &= ~(1 << PINB1);
// 		TCNT0 = 0;
// 	}
}

// initialize timer0 in fast PWM mode
void Timer0_PWM_Init(void)
{
	TCNT0 = 0;                                                                  // initialize counter
	TCCR0  = (1 << WGM01 ) | (1 << WGM00 ) | (1 << COM01 ) | (1 << CS00 ) ;    // TIMER0, PWM fast mode, non-inverted mode, no Prescaler;
	DDRB |= (1<<PINB3);														  // OC0 pin is output
}

// initialize timer0 in Clear Time on Compare match mode
void Timer0_CTC_Init (void) 
{
	TCNT0 = 0;                                                                            // initialize counter
	// TIMER0, CTC mode, toggle OC0 on compare match, Prescaler = 1024
	TCCR0  = (1 << WGM01 ) | (1 << COM00 )| (1 << CS02 ) | (1 << CS00 ) ; 
	DDRB |= (1<<PINB3);                                                                  // OC0 pin is output                                                                 
	OCR0 = 200;                                                                         // Compare value
}

// Stop timer0 
void Timer0_Stop(void)
{
	TCCR0 = 0x00;
}


void Timer0_delay_ms (float delay_time)                              // for example we want to delay for x ms
{
	Timer0_Overflow_Init();
	unsigned int prescaler = 1024;
	float overflow_time = (255.0)*(prescaler)/F_CPU;                 // overflow_time = (255)*(1024)/8MHz = 32.64ms
	
	if(delay_time < overflow_time )  // for small delays less than max delay
	{
		 TCNT0 = ceil(256  - (F_CPU/prescaler)*(delay_time/1000));   
		 while ((TIFR & 0x01) == 0);						       // Wait till TOV0 Overflow flag is SET
		 TIFR  |= (1 << TOV0); 						              // Clear TOV0 Overflow  flag
	}
	else                             // for large delays more than max delay
	{
		Timer0_Overflow_Init();
		unsigned int overflow_counts  = delay_time / (overflow_time*1000);    // no_counts = (delay_time/max_delay_time) = (5000ms / 32.64ms) = 153 counts
		unsigned int count = 0;
		while (count < overflow_counts)
		{
			TCNT0 =	0;										  // Clear register
			while ((TIFR & 0x01) == 0);						 // Wait till TOV0 Overflow flag is SET
			TIFR  |= (1 << TOV0); 						    // Clear TOV0 Overflow  flag
			++count;                                       // increment the count
		}
		Timer0_Stop();
	}
	
	TCCR0 = 0; // stop the timer
}

void Timer0_PWM (float duty_cycle)
{
	Timer0_PWM_Init();
	OCR0 = ceil(duty_cycle/100.0 * 255);           //  duty_cycle = x %
}


int main(void)
{
	DDRA = 0xFF;              // LEDs OUTPUT
	DDRB = 0xFF;             // LEDs OUTPUT
	DDRB &= ~(1 << PINB0);  // SWITCH
	
	sei();                      // Enable Global interrupts
	TIMSK |= (1 << TOIE0);     // Enable Timer0 overflow interrupt 
	TIMSK |= (1 << OCIE0);    // Enable Timer0 compare interrupt
	
	 Timer0_Overflow_Init();
	 
	while (1)
	{
	}
	
}
/*************************************************** T I M E R 0 *********************************************/
// to do a periodic task
ISR(TIMER0_OVF_vect)             
{
	++timer0_Overflow_Count;
	if (timer0_Overflow_Count >= 31)   // 1sec / 32.64ms = 31 counts
	{
		PORTA ^= (1 << PINA0);
		_delay_ms(50);
		timer0_Overflow_Count = 0;
	}
}

ISR(TIMER0_COMP_vect)
{
// 	++timer0_Compare_Count;
// 	if (timer0_Compare_Count >= 154)   // 5sec / 32.64ms = 154 counts
// 	{
// 		PORTA ^= (1 << PINA1);
// 		_delay_ms(60);
// 		timer0_Compare_Count = 0;
// 	}
	
}
	


