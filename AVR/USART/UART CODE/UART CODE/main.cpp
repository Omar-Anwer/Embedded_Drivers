/*
 * UART CODE.cpp
 *
 * Created: 1/7/2020 3:03:26 AM
 * Author : Omar Anwer
 */ 

#define F_CPU  8000000UL		// 8 MHz crystal clock rate 
#include <avr/io.h>
#include <util/delay.h>




void USART_init(long BAUDRATE, int mode)
{
	long BAUD_PRESCALE;
	if(mode == 0)
	{              
		BAUD_PRESCALE = (((F_CPU/(BAUDRATE*16UL)))-1);                // Asynchronous normal mode   
	}
	else
	{
		UCSRC |= (1<<UMSEL);										 // Synchronous normal mode
		BAUD_PRESCALE = (((F_CPU/(BAUDRATE*2UL)))-1);
	}
	
	UBRRL = BAUD_PRESCALE;									   // Load lower 8-bits of the baud rate
	UBRRH = (BAUD_PRESCALE >> 8);							  // Load upper 8-bits
	UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);		     // Use 8-bit char size 
	UCSRB |= (1<<RXEN) | (1<<TXEN);							// Turn on transmission and reception 	
}
/******************************************************************************
	 [Function Name]:    USART_init
	 [Description]:      Function to initiate transmitter and receiver
	                     - SYNCHRONOUS / ASYNCHRONOUS MODE
	                     - Disabled Parity Mode
	                     - 1-Stop bit
	                     - Output of TXD at rising edge, receiving on RXD at falling edge
	                     - Baud rate 9600 bits/sec 
	 [Arguments]:        None
	 [returns]:          None
	 ******************************************************************************/


void Transmit(char data)      
{
	while (!(UCSRA & (1<<UDRE)));		// Wait until buffer is empty 
	UDR = data ;
}
/******************************************************************************
 [Function Name]:    Transmit
 [Description]:      Function to Transmit data
 [Arguments]:        Data
 [returns]:          None
 ******************************************************************************/

unsigned char Recieve()
{
	while ((UCSRA & (1 << RXC)) == 0);	// Wait until buffer is empty 
	return(UDR);						// Return the byte
}
/******************************************************************************
 [Function Name]:    Receive
 [Description]:      Function to Receive data
 [Arguments]:        None
 [returns]:          Data received from transmitter
 ******************************************************************************/


void Transmit_String(char *str)
{
	unsigned char i = 0;
	while (str[i]!= '0')					// Send string till null
	{
		Transmit(str[i]);
		++i;
	}
}

// char* UART_Recieve_String( int String_length)
// {
// 	char* word ="";
// 	for(int i=0;i<String_length;i++)
// 	{
// 		while ( !(UCSRA & 1<< RXC ));
// 		word += UDR ;
// 	}
// 	return word;
// }
//////////////////////////////////////////////////////////////////////////////////




int main(void)
{
	USART_init(9600, 0);	
    while (1) 
    {
		Transmit_String("Test Message!! ");
		_delay_ms(1000);
    }
}

