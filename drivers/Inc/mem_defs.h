/*
 * mem_defs.h
 *
 *  Created on: Jun 17, 2026
 *  Author: rishabmadhugiri
 */

#ifndef MEM_DEFS_H
#define MEM_DEFS_H


#include <stdint.h>

// BASE ADRESSES


// Base addrs of Flash and SRAM memory - All unsigned ints

#define FLASH_BASEADDR 0x08000000U
#define SRAM1_BASEADDR 0x20000000U
#define SRAM2_BASEADDR 0x10000000U

#define ROM 0x00000000U

#define SRAM 		   SRAM1_BASEADDR

// Peripheral Bus Domain Addr Bases

#define PERIPHERAL_BASE 	0x40000000U // PERIPHERALS BASE
#define APB1_BASEADRR 		PERIPHERAL_BASE
#define APB2_BASEADRR 		0x40010000U
#define AHB1_BASEADRR 		0x40020000U
#define AHB2_BASEADRR 		0x48000000U

// Specific Peripheral Addrs on AHB2 Bus (80 MHz)

#define GPIO_BASEADDR 	0x48000000U // GPIO BASE

#define GPIOA_BASEADDR 	GPIO_BASEADDR
#define GPIOB_BASEADDR 	(GPIO_BASEADDR + 0x0400)
#define GPIOC_BASEADDR 	(GPIO_BASEADDR + 0x0800)
#define GPIOD_BASEADDR 	(GPIO_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR 	(GPIO_BASEADDR + 0x1000)
#define GPIOF_BASEADDR 	(GPIO_BASEADDR + 0x1400)
#define GPIOG_BASEADDR 	(GPIO_BASEADDR + 0x1800)
#define GPIOH_BASEADDR 	(GPIO_BASEADDR + 0x1C00)



#define RCC_BASEADDR (AHB1_BASEADRR + 0x1000) // RCC BASE



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
	volatile uint32_t CR;
	volatile uint32_t ICSCR;
	volatile uint32_t CFGR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t PLLSAI1CFGR;
	volatile uint32_t PLLSAI2CFGR;
	volatile uint32_t CIER;
	volatile uint32_t CIFR;
	volatile uint32_t CICR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;

	volatile uint32_t AHB3RSTR;
	volatile uint32_t APB1RSTR1;
	volatile uint32_t APB1RSTR2;
	volatile uint32_t APB2RSTR;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	volatile uint32_t APB1ENR1;
	volatile uint32_t APB1ENR2;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t APB2ENR;

	volatile uint32_t AHB1SMENR;
	volatile uint32_t AHB2SMENR;
	volatile uint32_t AHB3SMENR;
	volatile uint32_t APB1SMENR1;
	volatile uint32_t APB1SMENR2;
	volatile uint32_t APB2SMENR;
	volatile uint32_t CCIPR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t CRRCR;
	volatile uint32_t CCIPR2;
} RCC_RegDef_t;


typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;

	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RESERVED_0;

	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t RESERVED_1;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;

	volatile uint32_t TIM2_OR1;
	volatile uint32_t TIM3_OR1;
	volatile uint32_t TIM2_OR2;
	volatile uint32_t TIM3_OR2;
} TIM_GEN_PURP_RegDef_t;

// STRUCT INSTANCE CREATION

#define GPIOA ((GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t*) GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t*) GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t*) GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t*) GPIOH_BASEADDR)

#define RCC ((RCC_RegDef_t*) RCC_BASEADDR)

#define TIM2 ((TIM_GEN_PURP_RegDef_t*) TIM2_BASEADDR)




#endif /* MEM_DEFS_H */
