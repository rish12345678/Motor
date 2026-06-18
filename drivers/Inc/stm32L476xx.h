/*
 * stm32L476xx.h
 *
 *  Created on: Jun 17, 2026
 *      Author: rishabmadhugiri
 */

#ifndef INC_STM32L476XX_H_
#define INC_STM32L476XX_H_


#include <stdint.h>

// BASE ADRESSES


// Base addrs of Flash and SRAM memory - All unsigned ints

#define FLASH_BASEADDR 0x08000000U
#define SRAM1_BASEADDR 0x20000000U
#define SRAM2_BASEADDR 0x10000000U

#define ROM 0x00000000U

#define SRAM 		   SRAM1_BASEADDR

// Peripheral Bus Domain Addr Bases

#define PERIPHERAL_BASE 	0x40000000U
#define APB1_BASEADRR 		PERIPHERAL_BASE
#define APB2_BASEADRR 		0x40010000U
#define AHB1_BASEADRR 		0x40020000U
#define AHB2_BASEADRR 		0x48000000U

// Specific Peripheral Addrs on AHB2 Bus (80 MHz)

#define GPIO_BASEADDR 	0x48000000U

#define GPIOA_BASEADDR 	GPIO_BASEADDR
#define GPIOB_BASEADDR 	(GPIO_BASEADDR + 0x0400)
#define GPIOC_BASEADDR 	(GPIO_BASEADDR + 0x0800)
#define GPIOD_BASEADDR 	(GPIO_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR 	(GPIO_BASEADDR + 0x1000)
#define GPIOF_BASEADDR 	(GPIO_BASEADDR + 0x1400)
#define GPIOG_BASEADDR 	(GPIO_BASEADDR + 0x1800)
#define GPIOH_BASEADDR 	(GPIO_BASEADDR + 0x1C00)



#define RCC_BASEADDR (AHB1_BASEADRR + 0x1000)



// STRUCT DEFINITIONS


typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2]; // index 0 - AFRL, index 1 - AFRH
	volatile uint32_t BRR;
	volatile uint32_t ASCR;
} GPIO_RegDef_t;

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2]; // index 0 - AFRL, index 1 - AFRH
	volatile uint32_t BRR;
	volatile uint32_t ASCR;
} RCC_RegDef_t;

// STRUCT INSTANCE CREATION

#define GPIOA ((GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t*) GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t*) GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t*) GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t*) GPIOH_BASEADDR)




#endif /* INC_STM32L476XX_H_ */
