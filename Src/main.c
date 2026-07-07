#include "../Inc/stm32l476xx.h"


#include <stdint.h>
#include <stdbool.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#endif

/*
 * FUNCTION DECLARATIONS
 */

// Turn on clock for GPIOA and SPI1
void clock_init(void);

// Set mode for GPIOA (AF)
void GPIO_init(void);

/*
 * Configure SPI Peripheral
 */

// SPI_CR1 Register Configuration
void SPI_CR1_setup(void);

// SPI_CR2 Register Configuration
void SPI_CR2_setup(void);

uint8_t SPI_SEND_BYTE(void);


int main(void)
{
	clock_init();
	GPIO_init();
	SPI_CR1_setup();
	SPI_CR2_setup();

	volatile uint8_t echo_reg = 0;

	for (;;) {
		echo_reg = SPI_SEND_BYTE(); // Should hold 0x24

		// Delay between sends

		for(volatile int i = 0; i < 20000; i++);
	}


	(void) echo_reg; // Keep js to avoid compiler wrng
}
// Init Functions

void clock_init(void) {
	// Set both bits to one enabling clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; // Gate clock to GPIO (A)
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // Gate clock to SPI1
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

	GPIOA->ODR |= (1U << 4);
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

void SPI_CR2_setup(void) {
	// Set Data Length to eight bits
	SPI1->CR2 &= ~(SPI_CR2_DS_Msk);
	SPI1->CR2 |= (0x7U << SPI_CR2_DS_Pos);

	// RXNE flag triggered when FIFO level >= 8 bits
	SPI1->CR2 |= SPI_CR2_FRXTH;

	// Also just set enable bit here instead of another function
	SPI1->CR1 |= SPI_CR1_SPE;
}



uint8_t SPI_SEND_BYTE(void) {
	// Pull chip select low, to indicate communication
	GPIOA->ODR &= ~(1U << 4);

	// while TX buffer not empty, keep polling
	// once empty give it byte

	// Check if bit 1 is ~1
	while (!(SPI1->SR & SPI_SR_TXE));

	*(__IO uint8_t *)&SPI1->DR = 0x84; // Sample Data to send 0x84 | 0b 1000 0100
	while (!(SPI1->SR & SPI_SR_RXNE));

	GPIOA->ODR |= (1U << 4);

	return *(__IO uint8_t *)&SPI1->DR;
}
