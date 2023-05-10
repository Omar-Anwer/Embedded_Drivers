/*
 * stm32f103c6.h
 *
 *  Created on: Jan 18, 2023
 *      Author: Omar Anwer
 */

#ifndef STM32F103C6_H_
#define STM32F103C6_H_

//-----------------------------
//Includes
//-----------------------------
#include "Std_Types.h"
#include "Utils.h"

//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_MEMORY_BASE							0x08000000UL
#define SYSTEM_MEMORY_BASE							0x1FFFF000UL
#define SRAM_MEMORY_BASE							0x20000000UL
#define PHERIPHERALS_BASE							0x40000000UL
#define CORTEX_M3_INTERNAL_PHERIPHERALS_BASE		0xE0000000UL

//--------------------------------------
//Base addresses for AHB BUS Peripherals
//--------------------------------------

/*RCC*/
#define RCC_BASE									0x40021000UL


//---------------------------------------
//Base addresses for APB2 BUS Peripherals
//---------------------------------------

/*AFIO*/
#define AFIO_BASE									0x40010000UL


/*EXTI*/
#define EXTI_BASE									0x40010400UL


/*GPIO*/
#define GPIOA_BASE									0x40010800UL
#define GPIOB_BASE									0x40010C00UL
#define GPIOC_BASE									0x40011000UL
#define GPIOD_BASE									0x40011400UL
#define GPIOE_BASE									0x40011800UL
#define GPIOF_BASE									0x40011C00UL
#define GPIOG_BASE									0x40012000UL

//---------------------------------------
//Base addresses for APB1 BUS Peripherals
//---------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32 CRL;
	volatile uint32 CRH;
	volatile uint32 IDR;
	volatile uint32 ODR;
	volatile uint32 BSRR;
	volatile uint32 BRR;
	volatile uint32 LCKR;
}GPIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32 CR;
	volatile uint32 CFGR;
	volatile uint32 CIR;
	volatile uint32 APB2RSTR;
	volatile uint32 APB1RSTR;
	volatile uint32 AHBENR;
	volatile uint32 APB2ENR;
	volatile uint32 APB1ENR;
	volatile uint32 BDCR;
	volatile uint32 CSR;
}RCC_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32 EVCR;
	volatile uint32 MAPR;
	volatile uint32 EXTICR1;
	volatile uint32 EXTICR2;
	volatile uint32 EXTICR3;
	volatile uint32 EXTICR4;
	         uint32 RESERVED;
	volatile uint32 MAPR2;
}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32 IMR;
	volatile uint32 EMR;
	volatile uint32 RSTR;
	volatile uint32 FSTR;
	volatile uint32 SWIER;
	volatile uint32 PR;
}EXTI_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA		((GPIO_TypeDef*) GPIOA_BASE)
#define GPIOB		((GPIO_TypeDef*) GPIOB_BASE)
#define GPIOC		((GPIO_TypeDef*) GPIOC_BASE)
#define GPIOD		((GPIO_TypeDef*) GPIOD_BASE)
#define GPIOE		((GPIO_TypeDef*) GPIOE_BASE)
#define GPIOF		((GPIO_TypeDef*) GPIOF_BASE)
#define GPIOG		((GPIO_TypeDef*) GPIOG_BASE)

#define RCC			((RCC_TypeDef*) RCC_BASE)

#define AFIO		((AFIO_TypeDef*) AFIO_BASE)

#define EXTI		((EXTI_TypeDef*) EXTI_BASE)


//-*-*-*-*-*-*-*-*-*-*-*-
//clock Enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define AFIO_CLK_ENABLE()	( SET_BIT(RCC->APB2ENR, 0) )

#define GPIOA_CLK_ENABLE()	( SET_BIT(RCC->APB2ENR, 2) )
#define GPIOB_CLK_ENABLE()	( SET_BIT(RCC->APB2ENR, 3) )
#define GPIOC_CLK_ENABLE()	( SET_BIT(RCC->APB2ENR, 4) )
#define GPIOD_CLK_ENABLE()	( SET_BIT(RCC->APB2ENR, 5) )
#define GPIOE_CLK_ENABLE()	( SET_BIT(RCC->APB2ENR, 6) )
#define GPIOF_CLK_ENABLE()	( SET_BIT(RCC->APB2ENR, 7) )
#define GPIOG_CLK_ENABLE()	( SET_BIT(RCC->APB2ENR, 8) )

//-*-*-*-*-*-*-*-*-*-*-*-
//clock Disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define AFIO_CLK_DISABLE()	( CLEAR_BIT(RCC->APB2ENR, 0) )

#define GPIOA_CLK_DISABLE()	( CLEAR_BIT(RCC->APB2ENR, 2) )
#define GPIOB_CLK_DISABLE()	( CLEAR_BIT(RCC->APB2ENR, 3) )
#define GPIOC_CLK_DISABLE()	( CLEAR_BIT(RCC->APB2ENR, 4) )
#define GPIOD_CLK_DISABLE()	( CLEAR_BIT(RCC->APB2ENR, 5) )
#define GPIOE_CLK_DISABLE()	( CLEAR_BIT(RCC->APB2ENR, 6) )
#define GPIOF_CLK_DISABLE()	( CLEAR_BIT(RCC->APB2ENR, 7) )
#define GPIOG_CLK_DISABLE()	( CLEAR_BIT(RCC->APB2ENR, 8) )

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#endif /* STM32F103C6_H_ */
