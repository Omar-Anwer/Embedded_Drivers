/*
 * stm32f103c6_gpio.c
 *
 *  Created on: Jan 18, 2023
 *      Author: Omar Anwer
 */
#include "stm32f103c6_gpio.h"


uint8 Get_CRLH_pos(uint16 GPIO_Pin)
{
	uint8 pos = 0;

	switch(GPIO_Pin)
	{
	case(GPIO_PIN_0):
	case(GPIO_PIN_8):
	pos  = 0;
	break;

	case(GPIO_PIN_1):
	case(GPIO_PIN_9):
	pos  = 4;
	break;

	case(GPIO_PIN_2):
	case(GPIO_PIN_10):
	pos  = 8;
	break;

	case(GPIO_PIN_3):
	case(GPIO_PIN_11):
	pos  = 12;
	break;

	case(GPIO_PIN_4):
	case(GPIO_PIN_12):
	pos  = 16;
	break;

	case(GPIO_PIN_5):
	case(GPIO_PIN_13):
	pos  = 20;
	break;

	case(GPIO_PIN_6):
	case(GPIO_PIN_14):
	pos  = 24;
	break;

	case(GPIO_PIN_7):
	case(GPIO_PIN_15):
	pos  = 28;
	break;
	}
	return pos;
}
/**================================================================
 * @Fn			- MCAL_GPIO_Init
 * @brief 		- Initializes the GPIOx PINy according to the specified parameters in the PinConfig
 * @param [in] 	- GPIOx, where x can be (A...G depends on used device) to select GPIO peripherals
 * @param [in] 	- PinConfig, pointer to GPIO_PinConfig_t structure
 * 				  that contains the configuration for the specified GPIOx Pin
 * @retval 		- none
 * Note			- STM32F103C6 MCU has GPIO A..G modules
 *                 but LQFP48 Package has different modules
 */
void MCAL_GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_PinConfig_t* PinConfig)
{
	uint16 pin = PinConfig->GPIO_Pin;

	uint8 mode = PinConfig->GPIO_Mode;

	uint8 speed = PinConfig->GPIO_Speed;

	uint8 pos = Get_CRLH_pos(pin);		/* Get pin CRL/CRH position, pos= 0..28 */

	uint8 pin_cfg;

	/* Port configuration register low (GPIOx_CRL) Pin y (y= 0 .. 7)
	 * Port configuration register high (GPIOx_CRH) Pin y (y= 8 .. 15)
	 * */
	volatile uint32* confReg = (pin < GPIO_PIN_8) ? &GPIOx->CRL : &GPIOx->CRH;

	/* Clear CNFy[1:0] MODEy[1:0] bits */
	(*confReg) &= ~(0xF << pos);

	/* pin is output*/
	if(mode == GPIO_MODE_OUTPUT_PUSHPULL || mode == GPIO_MODE_OUTPUT_OPENDRAIN || mode == GPIO_MODE_AF_OUTPUT_PUSHPULL || mode == GPIO_MODE_AF_OUTPUT_OPENDRAIN)
	{
		/* Set CNFy[1:0] MODEy[1:0] bits */
		pin_cfg =  ( ((mode - 4) << 2) | (speed) ) & (0x0F) ;
	}
	else
	{
		/* pin is input floating or Analog*/
		if(mode == GPIO_MODE_INPUT_FLOATING || mode == GPIO_MODE_ANALOG)
		{
			pin_cfg =  (mode << 2) & (0x0F);
		}
		else if(mode == GPIO_MODE_AF_INPUT)
		{
			pin_cfg =  (GPIO_MODE_INPUT_FLOATING << 2) & (0x0F);
		}
		else
		{
			/* pin is input PU or PU*/
			pin_cfg = (GPIO_MODE_INPUT_PULLUP << 2)  & (0x0F);

			if(mode == GPIO_MODE_INPUT_PULLUP)
			{
				GPIOx->ODR |=  pin;
			}
			else
			{
				GPIOx->ODR &= ~pin;
			}
		}
	}
	/* Write on CRL/CRH for Pin y (y= 0 .. 15) */
	(*confReg) |= (pin_cfg << pos);

}

/**================================================================
 * @Fn			- MCAL_GPIO_DeInit
 * @brief 		- Resets all GPIOx registers
 * @param [in] 	- GPIOx: where x can be (A...G depends on used device) to select GPIO peripherals
 * @retval 		- none
 * Note			- none
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
	if (GPIOx == GPIOA)
	{
		SET_BIT(RCC->APB2RSTR, 2);
		CLEAR_BIT(RCC->APB2RSTR, 2);
	}
	else if(GPIOx == GPIOB)
	{
		SET_BIT(RCC->APB2RSTR, 3);
		CLEAR_BIT(RCC->APB2RSTR, 3);
	}
	else if(GPIOx == GPIOC)
	{
		SET_BIT(RCC->APB2RSTR, 4);
		CLEAR_BIT(RCC->APB2RSTR, 4);
	}
	else if(GPIOx == GPIOD)
	{
		SET_BIT(RCC->APB2RSTR, 5);
		CLEAR_BIT(RCC->APB2RSTR, 5);
	}
	else if(GPIOx == GPIOE)
	{
		SET_BIT(RCC->APB2RSTR, 6);
		CLEAR_BIT(RCC->APB2RSTR, 6);
	}
	else if(GPIOx == GPIOF)
	{
		SET_BIT(RCC->APB2RSTR, 7);
		CLEAR_BIT(RCC->APB2RSTR, 7);
	}
	else if(GPIOx == GPIOG)
	{
		SET_BIT(RCC->APB2RSTR, 8);
		CLEAR_BIT(RCC->APB2RSTR, 8);
	}
	else
	{
		/*GPIOx is not selected correctly*/
	}
}

/**================================================================
 * @Fn			- MCAL_GPIO_ReadPin
 * @brief 		- Read GPIOx specific pin state
 * @param [in] 	- GPIOx, where x can be (A...E depends on used device) to select GPIO peripherals
 * @param [in] 	- GPIO_Pin: set pin number according to the @ref GPIO_Pins_define
 * @retval 		- Pin value
 * Note			- none
 */
GPIO_PinState MCAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16 GPIO_Pin)
{
	GPIO_PinState bitstatus;

	if((GPIOx->IDR & GPIO_Pin) != (uint32)GPIO_PIN_RESET)
	{
		bitstatus = GPIO_PIN_SET;
	}
	else
	{
		bitstatus = GPIO_PIN_RESET;
	}
	return bitstatus;
}
/**================================================================
 * @Fn			- MCAL_GPIO_ReadPort
 * @brief 		- Read GPIOx port value
 * @param [in] 	- GPIOx, where x can be (A...E depends on used device) to select GPIO peripherals
 * @retval 		- Port value
 * Note			- none
 */
uint16 MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOx)
{
	return ((uint16)(GPIOx->IDR));
}

/**================================================================
 * @Fn			- MCAL_GPIO_WritePin
 * @brief 		- Write specific pin  with specific value
 * @param [in] 	- GPIOx, where x can be (A...E depends on used device) to select GPIO peripherals
 * @param [in]  - GPIO_Pin: set pin number according to the @ref GPIO_Pins_define
 * @param [in]  - Value: value to be written on pin 0 or 1
 * @retval 		- none
 * Note			- none
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16 GPIO_Pin, uint8 Value)
{
	if(Value != GPIO_PIN_RESET)
	{
		GPIOx->ODR |= GPIO_Pin;
		/*GPIOx->BSRR = GPIO_Pin;*/
	}
	else
	{
		GPIOx->ODR &= ~GPIO_Pin;
		/*GPIOx->BRR = GPIO_Pin;*/
	}
}

/**================================================================
 * @Fn			- MCAL_GPIO_WritePort
 * @brief 		- Write specific port with specific value
 * @param [in] 	- GPIOx, where x can be (A...E depends on used device) to select GPIO peripherals
 * @param [in]  - Value: value to be written on port 0 to 0xFFFF
 * @retval 		- none
 * Note			- none
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef* GPIOx, uint16 Value)
{
	GPIOx->ODR = (uint32)Value;
}

/**================================================================
 * @Fn			- MCAL_GPIO_TogglePin
 * @brief 		- Toggle specific pin
 * @param [in] 	- GPIOx, where x can be (A...E depends on used device) to select GPIO peripherals
 * @param [in]  - GPIO_Pin: set pin number according to the @ref GPIO_Pins_define
 * @retval 		- none
 * Note			- none
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16 GPIO_Pin)
{
	GPIOx->ODR ^= GPIO_Pin;
}

/**================================================================
 * @Fn			- MCAL_GPIO_TogglePort
 * @brief 		- Toggle specific port
 * @param [in] 	- GPIOx, where x can be (A...E depends on used device) to select GPIO peripherals
 * @retval 		- none
 * Note			- none
 */
void MCAL_GPIO_TogglePort(GPIO_TypeDef* GPIOx)
{
	GPIOx->ODR ^= (uint32)(0xFFFF);
}

/**================================================================
 * @Fn			- MCAL_GPIO_LockPin
 * @brief 		- Toggle specific port
 * @param [in] 	- GPIOx, where x can be (A...E depends on used device) to select GPIO peripherals
 * @param [in]  - GPIO_Pin: set pin number according to the @ref GPIO_Pins_define
 * @retval 		- GPIO_LockState
 * Note			- none
 */
GPIO_LockState MCAL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16 GPIO_Pin)
{
	GPIO_LockState lock;
	/*
	LOCK key writing sequence:
	Write 1
	Write 0
	Write 1
	Read 0
	Read 1 (this read is optional but confirms that the lock is active)
	*/

	/* Set LCKK[16]*/
	volatile uint32 tmp = (uint32) (1 << 16);

	/*Set the LCKy*/
	tmp |= GPIO_Pin;

	/*write 1*/
	GPIOx->LCKR = tmp;

	/*write 0*/
	GPIOx->LCKR = GPIO_Pin;

	/*write 1*/
	GPIOx->LCKR = tmp;

	/*read 0*/
	tmp = GPIOx->LCKR;

	/*read 1*/
	if((uint32) ( GPIOx->LCKR & (1<<16) ) )
	{
		lock = GPIO_PIN_LOCK_ENABLED;
	}
	else
	{
		lock = GPIO_PIN_LOCK_ERROR;
	}
	return lock;
}
