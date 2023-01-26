/*
 * LCD.h
 *
 *  Created on: Jan 24, 2023
 *      Author: Omar Anwer
 */

#ifndef LCD_H_
#define LCD_H_

/*
* ===============================================
* Includes
* ===============================================
*/
#include "stm32f103c6.h"
#include "stm32f103c6_gpio.h"
#include <stdio.h>

/*
* ===============================================
* Macros Configuration References
* ===============================================
*/
#define LCD_CTRL_PORT						GPIOA					/* LCD command port */
#define LCD_DATA_PORT						GPIOA					/* LCD command port */

#define LCD_RS_SW							GPIO_PIN_8				/* Register Select */
#define LCD_RW_SW							GPIO_PIN_9				/* Read Write Switch*/
#define LCD_EN_SW							GPIO_PIN_10

#define LCD_PIN_D0							GPIO_PIN_0
#define LCD_PIN_D1							GPIO_PIN_1
#define LCD_PIN_D2							GPIO_PIN_2
#define LCD_PIN_D3							GPIO_PIN_3
#define LCD_PIN_D4							GPIO_PIN_4
#define LCD_PIN_D5							GPIO_PIN_5
#define LCD_PIN_D6							GPIO_PIN_6
#define LCD_PIN_D7							GPIO_PIN_7

#define LCD_MODE_EIGHT_BIT					(0)
#define LCD_MODE_FOUR_BIT					(4)
#define LCD_MODE							LCD_MODE_FOUR_BIT
#define DATA_SHIFT 							LCD_MODE

/*
* ===============================================
* LCD COMMANDS
* ===============================================
*/
#define LCD_CLEAR_SCREEN					(0x01)			/* Clear display screen */
#define LCD_RETURN_HOME						(0x02)  		/* Return home */

#define LCD_ENTRY_DEC   					(0x04)			/* Decrement cursor (shift cursor to left) */
#define LCD_ENTRY_DEC_SHIFT   				(0x05)			/* Shift display right */
#define LCD_ENTRY_INC   					(0x06)			/* Increment cursor (shift cursor to right) */
#define LCD_ENTRY_INC_SHIFT   				(0x07)			/* Shift display left */

#define LCD_ENTRY_MODE						LCD_ENTRY_INC

#define LCD_DISP_OFF_CURSOR_OFF   			(0x08)			/* Display off, cursor off */
#define LCD_DISP_OFF_CURSOR_ON   			(0x0A)			/* Display off, cursor on */
#define LCD_DISP_ON_CURSOR_OFF   			(0x0C)			/* Display on, cursor off ex. (A)*/
#define LCD_DISP_ON_CURSOR_ON   			(0x0E)			/* Display on, cursor on ex. (A_)*/
#define LCD_DISP_ON_CURSOR_BLINK   			(0x0F)			/* Display on, cursor blinking */

#define LCD_MOVE_CURSOR_LEFT 	  			(0x10)			/* Shift cursor position to the left */
#define LCD_MOVE_CURSOR_RIGHT   			(0x14)			/* Shift the cursor position to the right */
#define LCD_MOVE_DISP_LEFT   				(0x18)			/* Shift the entire display to the left */
#define LCD_MOVE_DISP_RIGHT       			(0x1C)			/* Shift the entire display to the right */

#define LCD_FUNCTION_4BIT_1LINES   			(0x20)			/* 16X1  1 line, 5*7 matrix in 4-bit mode*/
#define LCD_FUNCTION_4BIT_2LINES   			(0x28)			/* 16X2  2 line, 5*7 matrix in 4-bit mode*/
#define LCD_FUNCTION_8BIT_1LINES   			(0x30)			/* 16X1  1 line, 5*7 matrix in 8-bit mode*/
#define LCD_FUNCTION_8BIT_2LINES   			(0x38)			/* 16x2  2 line, 5*7 matrix in 8-bit mode */

#define LCD_BEGIN_AT_FIRST_ROW				(0x80)			/* Force cursor to the beginning ( 1st line) */
#define LCD_BEGIN_AT_SECOND_ROW				(0xC0)			/* Force cursor to the beginning ( 2nd line) */

/*
* ===============================================
* APIs Supported by "HAL LCD Module Driver"
* ===============================================
*/

void LCD_Check_isBusy(void);

void LCD_GPIO_Init(void);

void LCD_Init(void);

void LCD_Send_Cmd(uint8 cmd);

void LCD_Display_Char(uint8 character);

void LCD_Display_String(char* pstr);

void LCD_Display_Number(sint16 num);

void LCD_Display_Real_Number(float32 num);

void LCD_En_Pulse(void);

void LCD_Clear_Screen(void);

void LCD_Goto_XY(uint8 line, uint8 position);



#endif /* LCD_H_ */
