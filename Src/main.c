#include "../Inc/stm32l476xx.h"


#include <stdint.h>
#include <stdbool.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#endif


int main(void)
{
	// Turn on clock for GPIOA and SPI1
	void clock_init(void);

	// Set mode for GPIOA (AF)
	void GPIO_init(void);

	/*
	 * Configure SPI Peripheral
	 */

	// SPI_CR1 Register
	void SPI_CR1_setup(void);
}

// Init Functions

void clock_init(void) {
	// Set both bits to one enabling clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; // Gate clock to GPIO (A)
	RCC->APB2ENR1 |= RCC_APB2ENR_SPI1EN; // Gate clock to SPI1
}

void GPIO_init(void) {
	// Set GPIO Port A pins 5, 6, 7 to AF - Part of SPI bus now
	GPIOA->MODER &= ~(GPIO_MODER_MODE5 | GPIO_MODER_MODE6 | GPIO_MODER_MODE7);
	GPIOA->MODER |= (GPIO_MODER_MODE5_1 | GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);

	// Set these four pins to belong to the SPI1 Peripheral (Will hardcode chip select pin PA4)
	GPIOA->AFR[0] &= ~(0xF << GPIO_AFRL_AFSEL5_Pos | 0xF << GPIO_AFRL_AFSEL6_Pos | 0xF << GPIO_AFRL_AFSEL7_Pos); // Clear for pins 5 6 7

	GPIOA->AFR[0] |= ( (GPIO_AFRL_AFSEL5_0 | GPIO_AFRL_AFSEL5_2) | (GPIO_AFRL_AFSEL6_0 | GPIO_AFRL_AFSEL6_2) | (GPIO_AFRL_AFSEL7_0 | GPIO_AFRL_AFSEL7_2));

	// Set Pin speed for SCK, MISO, and MOSI pins to high for sharp squarish clock edges
	GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED5_1 | GPIO_OSPEEDR_OSPEED6_1 | GPIO_OSPEEDR_OSPEED7_1);


	// Initialize the Chip Select Pin PA4, as a traditional output, will drive high, low when needed


	GPIOA->MODER &= ~(GPIO_MODER_MODE4_Msk);
	GPIOA->MODER |= GPIO_MODER_MODE4_0;

	GPIOA->MODER |= GPIO_BSRR_BS4;
}

void SPI_CR1_setup(void) {
	SPI1->CR1 = 0x0000; // Ensure reset value first

	// Divide Micro-controller clock (4 MHz) by 16 to avoid early hardware related issues
	// Set Baud Rate to 250 kHz
	SPI1->CR1 &= ~(SPI_CR1_BR_Msk);
	SPI1->CR1 |= (SPI_CR1_BR_0 | SPI_CR1_BR_1);


	// Set CPOL to zero -> Clock at 0 when idle
	// Set CPHA to zero -> Data capture occurs on first clock edge (rising edge)
	SPI1->CR1 &= ~(SPI_CR1_CPOL_Msk | SPI_CR1_CPHA_Msk); // Standard for SPI Flash

	// ----*  *~* *~* *~* *~*
	// Software Slave Management and Master Mode
	SPI1->CR1 |= (SPI_CR1_SSM | SPI_CR1_SSI);
	SPI1->CR1 |= SPI_CR1_MSTR;
}
