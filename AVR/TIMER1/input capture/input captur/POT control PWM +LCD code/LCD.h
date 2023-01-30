#ifndef LCD
#define LCD

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>   // for itoa ,dtostrf , log() , abs()

// 16x2 LCD
#define LCD_mode 8								    /* choose 4 for 4-bit mode or 8 for 8-bit mode */

#define RS PC0									    /* Register Select signal pin (make LCD know you send command or data on Digital pins)*/
#define EN PC1										/* Enable signal pin (after sending data you will need to latch the data to the LCD )*/

#define LCD_Command_Dir DDRC						/* LCD command port direction register */
#define LCD_Command_Port PORTC						/* LCD data port */
#define LCD_Data_Dir DDRB							/* LCD data port direction */
#define LCD_Data_Port PORTB							/* LCD data port */

#define RS_Low  LCD_Command_Port &= ~(1<<RS)
#define RS_High LCD_Command_Port |= (1<<RS)
#define En_High LCD_Command_Port |= (1<<EN)
#define En_Low  LCD_Command_Port &= ~(1<<EN)


void En_pulse(void);
void LCD_init (void);
void LCD_Command(uint8_t cmnd);
void LCD_Char (uint8_t data);
void LCD_String (char *str);
void LCD_integer (int value);
void LCD_float (float value , uint8_t precision);
void LCD_float_2 (float value, unsigned char size, uint8_t precision);
void LCD_setCursor(uint8_t row , uint8_t col);
void LCD_Clear(void);
/****************************************************************************************************
								LCD commands

				0x28        16X2  2 line, 5*7 matrix in 4-bit mode
				0x38		16x2  2 line, 5*7 matrix in 8-bit mode
				0x33        LCD 4 bit mode

				0x08		Display OFF , Cursor OFF
				0x0C		Display ON , Cursor OFF      (A)
				0x0E		Display ON , Cursor ON       (A_)
				0x0F		Display ON , Cursor blinking

				0x80        initialize the cursor to the first position

				0x01		Clear Display Screen
				0x02		Return Home position

				0x04        Entry mode -> shift cursor left after each character (auto increment)
				0x06        Entry mode -> shift cursor right after each character (auto increment)

				0x14		Move cursor to right by one character (cursor++)
				0x10		Move cursor to left by one character  (cursor--)

								Move cursor to a certain position
				________________________________________________________________________________
				|0x80|0x81|0x82|0x83|0x84|0x85|0x86|0x87|0x88|0x89|0x8A|0x8B|0x8C|0x8D|0x8E|0x8F|
				|0xC0|0xC1|0xc2|0xC3|0xC4|0xC5|0xC6|0xC7|0xC8|0xC9|0xCA|0xCB|0xCC|0xCD|0xCE|0xCF|
				---------------------------------------------------------------------------------
*****************************************************************************************************/

#endif
