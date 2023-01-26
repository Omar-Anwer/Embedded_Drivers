/*
 * Keypad.c
 *
 *  Created on: Jan 25, 2023
 *      Author: Omar Anwer
 */
#include "Keypad.h"

uint16 KEYPAD_ROWS[] = {KEYPAD_R0, KEYPAD_R1, KEYPAD_R2, KEYPAD_R3};
uint16 KEYPAD_COLS[] = {KEYPAD_C3, KEYPAD_C2, KEYPAD_C1, KEYPAD_C0};

uint8 KEYPAD[KEYPAD_NUM_ROWS][KEYPAD_NUM_COLS] =  {	{'/','9','8','7'},
													{'*','6','5','4'},
													{'-','3','2','1'},
													{'+','=','0','?'} };
void Keypad_Init(void)
{
	GPIO_PinConfig_t PinCfg;

	PinCfg.GPIO_Pin = KEYPAD_R0;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_Pin = KEYPAD_R1;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_Pin = KEYPAD_R2;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_Pin = KEYPAD_R3;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_Pin = KEYPAD_C0;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_Pin = KEYPAD_C1;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_Pin = KEYPAD_C2;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_Pin = KEYPAD_C3;
	PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_Speed = GPIO_SPEED_MEDIUM_FREQ_10MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	MCAL_GPIO_WritePort(KEYPAD_PORT, 0xFF);
}

uint8 Keypad_GetKey(void)
{
	uint8 r;
	uint8 c;
	for (c = 0; c < KEYPAD_NUM_COLS; c++)
	{
		MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_COLS[c], GPIO_PIN_RESET);

		for (r = 0; r < KEYPAD_NUM_ROWS; r++)
		{
			if (MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_ROWS[r]) == GPIO_PIN_RESET)
			{
				/* Wait for key to be released single press*/
				while(MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_ROWS[r]) == GPIO_PIN_RESET);

				return KEYPAD[r][c];
			}
		}
		MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_COLS[c], GPIO_PIN_SET);
	}
	return NO_KEY_PRESSED;
}
