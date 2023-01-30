#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

//PCF8574A EEPROM_address_Write 0X70
//PCF8574 EEPROM_address_Write 0X40
#define EEPROM_address_Write 0X70   //4 is a Fixed address for slave EEPROM PCF8574 , 0 to write. 0 is constant to Write in most EEPROMs while 4 is variable from one EEPROM to another.


void TWI_Init(void)
{
	TWBR=0X08; //SCL_Freq = 100K Hz
	TWCR |= 1<<TWEN; //Enable TWI
}

void TWI_Start(char EEPROM_address)
{
	TWCR |= 1<<TWINT | 1<<TWSTA ; //clear TWI Interrupt Flag and Enable Start
	while( (TWCR & 1<<TWINT) ==0);  //delay till current job has finished
	TWDR=EEPROM_address;  //Send Slave address with R/~W bit
	TWCR |= 1<<TWINT;   //clear TWI Interrupt Flag
	
}
void TWI_Stop(void)
{
	TWCR |= 1<<TWINT | 1<<TWSTO ; //clear TWI Interrupt Flag and enable Stop
	while( (TWCR & 1<<TWSTO) ==0);  //delay till current job has finished
	
}

void TWI_Write(char data)
{
	_delay_us(100);
	TWDR=data;
	TWCR |= 1<<TWINT;   //clear TWI Interrupt Flag
	while( (TWCR & 1<<TWINT) ==0);  //delay till current job has finished
}

char TWI_Read()
{
	TWCR |= 1<<TWINT ;   //clear TWI Interrupt Flag
	while( (TWCR & 1<<TWINT) ==0);  //delay till current job has finished
	return TWDR;
}


int main(void)
{
	
	TWI_Init();
	

	//Sending data
	TWI_Start(EEPROM_address_Write); //EEPROM Address with W-bit
	TWI_Write(0X00); //Memory location in EEPROM
	TWI_Write(0XAA); //Send data
	TWI_Stop();
	
}