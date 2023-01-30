#include "LCD.h"

void En_pulse(void)
{
	En_High;						/* EN = 1 for HIGH to LOW pulse */
	_delay_us(1);					/* wait to make Enable wide */
	En_Low;							/* EN = 0 for HIGH to LOW pulse */
	_delay_us(200);					/* wait to make Enable wide */
}
/**********************************/
/* 1 - Initializing the	LCD */
void LCD_init (void)
{
	LCD_Command_Dir = 0xFF;			/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0xFF;			/* Make LCD data port direction as o/p */
	_delay_ms(20);					/* wait to initialize as LCD Power ON delay always >15ms */

	if(LCD_mode == 4)   // 4-bit mode
	{
		LCD_Command(0x33);          /*Go into 4-bit operating mode*/
		LCD_Command(0x02);			/* return home  */
		LCD_Command(0x28);          /* 2 line, 5*7 matrix in 4-bit mode */
	}

	else   //8-bit mode
	{
		LCD_Command (0x38);			/* 2 line, 5*7 matrix in 8-bit mode */
	}
	
		LCD_Command (0x0C);			/* Display ON Cursor OFF */
		LCD_Command (0x06);			/* Auto Increment cursor */
		LCD_Command (0x01);			/* Clear display screen */
		_delay_ms(2);				/* wait for clear */
		LCD_Command (0x80);			/* Move cursor to  1st row  1st col */

}
//*****************************************************************************
/* 2 - Sending commands to LCD*/
void LCD_Command(uint8_t cmnd)
{
	RS_Low;							/* RS = 0 for sending command */
	if(LCD_mode == 4)  // 4-bit mode
	{
		LCD_Data_Port = (LCD_Data_Port & 0x0F) | (cmnd & 0xF0);     /* Sending upper nibble */
		En_pulse();
		LCD_Data_Port = (LCD_Data_Port & 0x0F) | (cmnd << 4);		/* shift then Sending lower nibble */
	}
	else   //8-bit mode
	{
		LCD_Data_Port= cmnd;            /* Send command to data port */
	}
		En_pulse();
}
//*****************************************************************************
/* 3 - Sending data to LCD */
void LCD_Char (uint8_t data)
{
	RS_High;						/* RS = 1 for sending Data */
	if(LCD_mode == 4)
	{
		LCD_Data_Port = (LCD_Data_Port & 0x0F) | (data & 0xF0);     /* Sending upper nibble */
		En_pulse();
		LCD_Data_Port = (LCD_Data_Port & 0x0F) | (data << 4);		/* shift then Sending lower nibble */
	}
	else
	{
		LCD_Data_Port= data;       /* takes Char to ACII then Send data to data port */
	}
		En_pulse();
}
//*****************************************************************************
/* Send string to LCD function */
void LCD_String (char *str)
{
	for(int i=0 ; str[i]!= '\0' ; i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}
//*****************************************************************************
/* Send string to LCD function */
void LCD_integer (int value)
{
// 	uint8_t digits = 0;
// 	if (value != 0) digits = ceil(log(abs(value))+1) ;
// 	else			digits = 1;

	char value_str[16]; //no of digits of value
	//you can easily make value_str[16] because lcd can max print 16 character
	itoa(value,value_str,10); // 10 is for decimal Base 10
	LCD_String(value_str);
}


void LCD_float (float value , uint8_t precision)
{
// 	unsigned char digits = 1;
// 	if(value != 0) digits = ceil(log(abs(value))) ;
// 		
// 	char value_str[digits+precision];
// 	//you can easily make value_str[16] because lcd can max print 16 character
// 	dtostrf(value, digits + precision, precision, value_str);
// 	LCD_String(value_str);
   unsigned char d = log(abs(value))+ 1 + precision ;
   char buffer[d];
   dtostrf(value, d, precision, buffer);
   LCD_String(buffer);
}
//*****************************************************************************
void LCD_float_2 (float value, unsigned char size, uint8_t precision)
{
	char buffer[size];
	dtostrf(value, size, precision, buffer);
	LCD_String(buffer);
}
//*****************************************************************************

// LCD_setCursor(Line,column)
void LCD_setCursor(uint8_t row , uint8_t col)
{
	// row 0 ~ 1  and col 0 ~ 15
	uint8_t Address = 0;
	if      (row == 0) Address = 0x80;
	else if (row == 1) Address = 0xC0;

	if (col > 0 && col < 16) Address += col;
	LCD_Command(Address);
}
//*****************************************************************************

/*Clear LCD Screen*/
void LCD_Clear(void)
{
	LCD_Command (0x01);		/* clear display screen */
	_delay_ms(2);
	LCD_Command (0x80);		/* Move cursor to  1st row  1st col */
}
/***********************************************************************************/