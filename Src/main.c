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
	void GPIO_mode_init(void);



    /* Loop forever */
	for(;;) {
		// For all comms to and from the board from PC, processor has SWO pin from the core to the ST Link V2 Debug Circuitery, which allows connection to pc, printf flows over this SWO pin
		// SWO pin is connect to ST Link Cicuitery on the board, and that connects to ITM unit in core, which is a buffer for incoming data



		// First, we know that we want to turn on the LD2 light
		// We find which pin it is connected to: PA5
		// Now look in the memory map(memory organization) and see what address in the CPUs address space controls Port A
		// We look through GPIOA and find that the base address is 0x48000000
		// There is no electricity flowing to port A, so opening the gate there won't do anything, because the clock is not on, go to Reset and Clock Control (RCC)
		// Again in the memory map(Where peripherals are placed in memory), look for RCC, its base is 0x40021000
		// Go to the RCC section and look at the list of registers, find the one that controls Port A / GPIOA, it is RCC_AHB2ENR (AHB2 Peripheral Clock Enable Register), with an offset of base + 0x4C
		// That specific peripheral register Base(0x40021000) + Offset(0x4C) is a word size register to control power to Port A
		// In the documentation for this, it says, of the 32 bits at PA5 RCC Register (0x4002104C) setting bit 0 to 1 enables the clock for Port A, so go to the offset, set bit zero, and power starts flowing(the clock)
		// Now we have to tell Port A 5 specifically, what it is doing, input, output, etc.  Lets go to Chapter 8 GPIO Section, and find GPIO port mode register (GPIOx_MODER), there we see offset for port A is 0x00
		// This address lets you configure the mode of each specific register in Port A, so we set PA5 to General Purpose Output Mode, by setting bits 11 and 10 to 01
		// Finally scroll down a bit to find GPIO port output data register (GPIOx_ODR), which tells us how to send power to PA5, GPIOA Base (0x48000000) + 0x14 = 0x48000014, and then we just set bit 5 to 1 to send power there.

		// 1. Turn on the clock grid for Port A (Set Bit 0 to 1)
		*RCC_AHB2ENR |= (1 << 0);

		// 2. Clear bits 11 and 10 of MODER to 00, then set them to 01
		*GPIOA_MODER &= ~(3 << 10); // Clear
		*GPIOA_MODER |= (1 << 10);  // Set bit 10 to '1' -> makes it 01

		// 3. Set Bit 5 of ODR to 1 to blast 3.3V to the LED
		*GPIOA_ODR &= ((0xFF) & ~(1 << 5));

		// Now make light come on with blue push-button

		// B1 connected to I/O PC13 (pin 2), so this is GPIOC Pin 13

		// Just get the base, so that you can apply later offsets:
		// Look at the memory organization sheet, GPIO C starts at 0x4800 0800

		// Get the mode setter, so you can tell the button what it is doing
		// 															  (input)

		// The mode setter has an offset of 0x00, so we just need to change
		// the value at 0x4800 0800, in that 32 bit address, of bit 26 and 27
		// to 00

		// Now turn on RCC clock for the button at offset 0x4C, at that offset
		// Change bit two to be one






		// AHB2 -> GPIOC -> Base: 4800 0800 -> Set Input Mode(Bits 26 27 00)
		// AHB1 -> RCC -> Base: 4002 1000 -> Offset (4C) -> Set Bit 2 to 1

		*RCC_AHB2ENR |= 4U; // Always set the clock first, otherwise you can not read or write to any of the registers of that peripheral
		*GPIOC_BASE_AND_MODER &= ~(3U << 26);



		while(1) {
			// Loop forever keeping the light on
			if (*GPIOC_IDR & (1U << 13)) { // button pushed in
				*GPIOA_ODR &= ~(1U << 5);
			} else {
				*GPIOA_ODR |= (1U << 5);
			}
		}

	}
}

// Init Functions

void clock_init(void) {
	// Set both bits to one enabling clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; // Gate clock to GPIO (A)
	RCC->APB2ENR1 |= RCC_APB2ENR_SPI1EN; // Gate clock to SPI1
}

void GPIO_mode_init(void) {
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
