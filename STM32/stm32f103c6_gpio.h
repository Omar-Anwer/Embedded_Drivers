/*
 * stm32f103c6_gpio.h
 *
 *  Created on: Jan 18, 2023
 *      Author: Omar Anwer
 */

#ifndef STM32F103C6_GPIO_H_
#define STM32F103C6_GPIO_H_

/*-----------------------------
 * Includes
 * -----------------------------
 */
#include "stm32f103c6.h"

/*-----------------------------
 * User type definitions (structures)
 * -----------------------------
 */
typedef struct
{
	uint16 GPIO_Pin;   /* Specifies the GPIO pins to be configured.
						 This parameter can be any value of @ref GPIO_PIN_define */
	uint8  GPIO_Mode;  /* Specifies the operating mode for the selected pins.
                          This parameter can be a value of @ref GPIO_Mode_define */
	uint8  GPIO_Speed; /* Specifies the speed for the selected pins.
    					  This parameter can be a value of @ref GPIO_Speed_define */

}GPIO_PinConfig_t;

/*-----------------------------
 * Macros Configuration References
 * -----------------------------
 */

/*@ref GPIO_Pin_State*/
typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET = 1U
}GPIO_PinState;

typedef enum
{
  GPIO_PIN_LOCK_ERROR = 0U,
  GPIO_PIN_LOCK_ENABLED = 1U
}GPIO_LockState;


/*@ref GPIO_Pins_define*/
#define GPIO_PIN_0			((uint16) 0x0001)	/* PIN 0 is selected */
#define GPIO_PIN_1			((uint16) 0x0002)	/* PIN 1 is selected */
#define GPIO_PIN_2			((uint16) 0x0004)	/* PIN 2 is selected */
#define GPIO_PIN_3			((uint16) 0x0008)	/* PIN 3 is selected */
#define GPIO_PIN_4			((uint16) 0x0010)	/* PIN 4 is selected */
#define GPIO_PIN_5			((uint16) 0x0020)	/* PIN 5 is selected */
#define GPIO_PIN_6			((uint16) 0x0040)	/* PIN 6 is selected */
#define GPIO_PIN_7			((uint16) 0x0080)	/* PIN 7 is selected */
#define GPIO_PIN_8			((uint16) 0x0100)	/* PIN 8 is selected */
#define GPIO_PIN_9			((uint16) 0x0200)	/* PIN 9 is selected */
#define GPIO_PIN_10			((uint16) 0x0400)	/* PIN 10 is selected */
#define GPIO_PIN_11			((uint16) 0x0800)	/* PIN 11 is selected */
#define GPIO_PIN_12			((uint16) 0x1000)	/* PIN 12 is selected */
#define GPIO_PIN_13			((uint16) 0x2000)	/* PIN 13 is selected */
#define GPIO_PIN_14			((uint16) 0x4000)	/* PIN 14 is selected */
#define GPIO_PIN_15			((uint16) 0x8000)	/* PIN 15 is selected */
#define GPIO_PIN_ALL		((uint16) 0xFFFF)	/* All PINS are selected */

#define GPIO_PIN_MASK		0x0000FFFFU			/* PIN Mask */


/*@ref GPIO_Mode_define*/
/*
0: Analog mode
1: Floating input (reset state)
2: Input with pull-up
3: Input with pull-down
4: General purpose output push-pull
5: General purpose output Open-drain
6: Alternate function output Push-pull
7: Alternate function output Open-drain
*/
#define GPIO_MODE_ANALOG				(0U)	/* Analog Mode*/

#define GPIO_MODE_INPUT_FLOATING		(1U)	/* Input Floating*/
#define GPIO_MODE_INPUT_PULLUP			(2U) 	/* Input with pull-up*/
#define GPIO_MODE_INPUT_PULLDOWN		(3U) 	/* Input with pull-down*/

#define GPIO_MODE_OUTPUT_PUSHPULL		(4U) 	/* General purpose output push-pull*/
#define GPIO_MODE_OUTPUT_OPENDRAIN		(5U) 	/* General purpose output Open-drain*/

#define GPIO_MODE_AF_OUTPUT_PUSHPULL	(6U) 	/* Alternate function output Push-pull*/
#define GPIO_MODE_AF_OUTPUT_OPENDRAIN	(7U) 	/* Alternate function output Open-drain*/
#define GPIO_MODE_AF_INPUT				(8U) 	/* Alternate function input */


/*@ref GPIO_Speed_define*/
/*
1: Output mode, Max speed 10 MHz.
2: Output mode, Max speed 2 MHz.
3: Output mode, Max speed 50 MHz.
*/
#define GPIO_SPEED_MEDIUM_FREQ_10MHz	(1U)	/*Output mode, Max speed 10 MHz*/
#define GPIO_SPEED_LOW_FREQ_2MHz		(2U) 	/*Output mode, Max speed 2 MHz*/
#define GPIO_SPEED_HIGH_FREQ_50MHz		(3U)	/*Output mode, Max speed 50 MHz*/


/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/
void MCAL_GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_PinConfig_t* PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx);

GPIO_PinState MCAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16 GPIO_Pin);
uint16 MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16 GPIO_Pin, uint8 Value);
void MCAL_GPIO_WritePort(GPIO_TypeDef* GPIOx, uint16 Value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16 GPIO_Pin);
void MCAL_GPIO_TogglePort(GPIO_TypeDef* GPIOx);

GPIO_LockState MCAL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16 GPIO_Pin);


#endif /* STM32F103C6_GPIO_H_ */
