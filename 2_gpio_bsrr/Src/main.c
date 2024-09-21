#include "stm32f4xx.h"




#define GPIOD_EN			(1U<<3)
#define PIN12				(1U<<12)
#define PIN14				(1U<<14)
#define LED_GREEN			PIN12
#define LED_RED				PIN14

void wait(int count);

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
		GPIOD->BSRR |= LED_GREEN;
		wait(100000);

		/*Turn OFF the LED4 (GREEN LED)*/
		GPIOD->BSRR |= GPIO_BSRR_BR12; //(1UL<<12)
		wait(100000);

		/*Turn ON the LED5 (RED LED)*/
		GPIOD->BSRR |= LED_RED;
		wait(100000);

		/*Turn OFF the LED5 (RED LED)*/
		GPIOD->BSRR |= GPIO_BSRR_BR14; //(1U<<14)
		wait(100000);
	}
}

void wait(int count)
{
	volatile int i;
	for (i = 0; i < count; ++i) {}
}





