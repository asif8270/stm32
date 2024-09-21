#include "stm32f4xx.h"

#define GPIOD_EN			(1U<<3)

#define PIN12				(1U<<12)
#define PIN14				(1U<<14)

#define LED_GREEN			PIN12
#define LED_RED				PIN14

int main(void)
{
	/*Enable clock access to the GPIOD*/
	RCC->AHB1ENR |= GPIOD_EN;

	/*Set the PD12 as OUTPUT*/
	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);

	/*Set the PD14 as OUTPUT*/
	GPIOD->MODER |= (1U<<28);
	GPIOD->MODER &= ~(1U<<29);

	while(1)
	{
		/*Turn ON the LED4 (GREEN LED)*/
		GPIOD->ODR ^= LED_GREEN;
		for (int i = 0; i < 100000; ++i) {}

		/*Turn OFF the LED4 (GREEN LED)*/
		GPIOD->ODR ^= LED_RED;
		for (int i = 0; i < 100000; ++i) {}
	}
}
