/*
 * Keypad.h
 *
 *  Created on: Jan 25, 2023
 *      Author: Omar Anwer
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stm32f103c6.h"
#include "stm32f103c6_gpio.h"

#define KEYPAD_PORT 		GPIOB

#define KEYPAD_NUM_ROWS		(4)
#define KEYPAD_NUM_COLS		(4)

#define KEYPAD_R0			GPIO_PIN_0
#define KEYPAD_R1			GPIO_PIN_1
#define KEYPAD_R2			GPIO_PIN_3
#define KEYPAD_R3			GPIO_PIN_4

#define KEYPAD_C0			GPIO_PIN_5
#define KEYPAD_C1			GPIO_PIN_6
#define KEYPAD_C2			GPIO_PIN_7
#define KEYPAD_C3			GPIO_PIN_8

#define NO_KEY_PRESSED		'@'

void Keypad_Init(void);

uint8 Keypad_GetKey(void);


#endif /* KEYPAD_H_ */
