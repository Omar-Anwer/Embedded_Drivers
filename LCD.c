/*
 * LCD.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Omar Anwer
 */

#include "LCD.h"

static void delay_ms(uint32 time)
{
	uint32 i;
	uint8 j;
	for (i = 0; i < time; i++)
	{
		for (j = 0; j < 255; j++);
	}
}

void LCD_En_Pulse(void)
{
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN_SW, GPIO_PIN_SET);
	//delay_us(1);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN_SW, GPIO_PIN_RESET);
	//delay_us(1);
}


void LCD_GPIO_Init(void)
{
	GPIO_PinConfig_t PinCfg;

	PinCfg.GPIO_Pin = LCD_RS_SW;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_RW_SW;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_EN_SW;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);
	/*-----------------------------------------*/
#if (LCD_MODE == LCD_MODE_EIGHT_BIT)
	PinCfg.GPIO_Pin = LCD_PIN_D0;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_PIN_D1;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_PIN_D2;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_PIN_D3;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);
#endif

	PinCfg.GPIO_Pin = LCD_PIN_D4;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_PIN_D5;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_PIN_D6;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_PIN_D7;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);

	/*-----------------------------------------*/
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN_SW, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS_SW, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW_SW, GPIO_PIN_RESET);
}

void LCD_Init(void)
{
	delay_ms(15);     /* wait to initialize as LCD Power ON delay always >15ms 20ms is fine*/

	LCD_GPIO_Init();

#if (LCD_MODE == LCD_MODE_EIGHT_BIT)
	LCD_Send_Cmd(LCD_FUNCTION_8BIT_2LINES);
#endif

#if (LCD_MODE == LCD_MODE_FOUR_BIT)
	LCD_Send_Cmd(LCD_RETURN_HOME);
	LCD_Send_Cmd(LCD_FUNCTION_4BIT_2LINES);
#endif

	LCD_Send_Cmd(LCD_DISP_ON_CURSOR_BLINK);
	LCD_Send_Cmd(LCD_ENTRY_MODE);
	LCD_Send_Cmd(LCD_BEGIN_AT_FIRST_ROW);

	LCD_Clear_Screen();
}

void LCD_Check_isBusy(void)
{
	GPIO_PinConfig_t PinCfg;

	PinCfg.GPIO_Pin = LCD_PIN_D0;
	PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_DATA_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_PIN_D1;
	PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_DATA_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_PIN_D2;
	PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_DATA_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_PIN_D3;
	PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_DATA_PORT, &PinCfg);
#if (LCD_MODE == LCD_MODE_EIGHT_BIT)

	PinCfg.GPIO_Pin = LCD_PIN_D4;
	PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_DATA_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_PIN_D5;
	PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_DATA_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_PIN_D6;
	PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);

	PinCfg.GPIO_Pin = LCD_PIN_D7;
	PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_DATA_PORT, &PinCfg);
#endif
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW_SW, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS_SW, GPIO_PIN_RESET);

	LCD_En_Pulse();

	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW_SW, GPIO_PIN_RESET);
}


void LCD_Send_Cmd(uint8 cmd)
{
#if (LCD_MODE == LCD_MODE_EIGHT_BIT)
	MCAL_GPIO_WritePort(LCD_CTRL_PORT, cmd);
#endif
#if (LCD_MODE == LCD_MODE_FOUR_BIT)

	uint8 data = (LCD_CTRL_PORT->ODR & 0x0F) | (cmd & 0xF0);
	MCAL_GPIO_WritePort(LCD_CTRL_PORT, data);

	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS_SW, GPIO_PIN_RESET);
	LCD_En_Pulse();

	data = (LCD_CTRL_PORT->ODR & 0x0F) | (cmd << 4);
	MCAL_GPIO_WritePort(LCD_CTRL_PORT, data);
#endif
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS_SW, GPIO_PIN_RESET);
	LCD_En_Pulse();
}



void LCD_Display_Char(uint8 character)
{
#if (LCD_MODE == LCD_MODE_EIGHT_BIT)

	MCAL_GPIO_WritePort(LCD_DATA_PORT, character);

#endif

#if (LCD_MODE == LCD_MODE_FOUR_BIT)

	uint8 data= (LCD_DATA_PORT->ODR & 0x0F) | (character & 0xF0);
	MCAL_GPIO_WritePort(LCD_DATA_PORT, data);

	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_RS_SW, GPIO_PIN_SET);
	LCD_En_Pulse();

	data = (LCD_DATA_PORT->ODR & 0x0F) | (character << 4);
	MCAL_GPIO_WritePort(LCD_DATA_PORT, data);

#endif

	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_RS_SW, GPIO_PIN_SET);
	LCD_En_Pulse();
}


void LCD_Display_String(char* pstr)
{
	uint8 col = 0;
	while (*pstr != '\0')
	{
		LCD_Display_Char(*pstr);
		pstr++;
		col++;
		if (col == 16)
		{
			LCD_Goto_XY(2, 0);
		}
		else if (col == 32)
		{
			LCD_Clear_Screen();
			LCD_Goto_XY(1, 0);
			col = 0;
		}
	}
}

void LCD_Display_Number(sint16 num)
{
	char str[16];

	sprintf(str, "%d", num);

	LCD_Display_String(str);
}

void LCD_Display_Real_Number(float32 num)
{
	char str[16];

	char* sign = "";
	float32 tmpVal = num;

	if(num < 0)
	{
		sign = "-";
		tmpVal = -num;
	}

	sint16 tmpInt1 = tmpVal;            	/* Get the integer part 678 */
	float32 tmpFrac = tmpVal - tmpInt1;		/* Get the fraction 0.0123*/
	sint16 tmpInt2 = tmpFrac * 10000;

	sprintf(str, "%s%d.%04d", sign, tmpInt1, tmpInt2);

	LCD_Display_String(str);
}

void LCD_Clear_Screen(void)
{
	LCD_Send_Cmd(LCD_CLEAR_SCREEN);
}


void LCD_Goto_XY(uint8 line, uint8 position)
{

	if ( (position < 16) && (position >= 0) )
	{
		if (line == 1)
		{
			LCD_Send_Cmd(LCD_BEGIN_AT_FIRST_ROW + position);
		}
		else if (line == 2)
		{
			LCD_Send_Cmd(LCD_BEGIN_AT_SECOND_ROW + position);
		}
	}
}
