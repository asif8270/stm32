#include "stm32f4xx.h"

#define GPIOD_EN			(1U<<3)
#define GPIOA_EN			(1U<<0)

#define PIN14				(1U<<14)
#define PIN0				(1U<<0)

#define LED_RED				PIN14
#define BTN_PIN				PIN0


int main(void)
{
	/*Enable clock access to the GPIOA and GPIOD*/
	RCC->AHB1ENR |= GPIOA_EN;
	RCC->AHB1ENR |= GPIOD_EN;

	/*Set the PD14 as OUTPUT*/
	GPIOD->MODER |= (1U<<28);
	GPIOD->MODER &= ~(1U<<29);

	/*Set the PA0 as INPUT*/
	GPIOA->MODER &= ~(1U<<0);
	GPIOA->MODER &= ~(1U<<1);

	while(1)
	{
		/*Check if button is pressed*/
		if (GPIOA->IDR & BTN_PIN)
		{
			/*Turn OFF the LED*/
			GPIOD->BSRR |= GPIO_BSRR_BR14; //(1U<<30)
		}
		else
		{
			/*Turn ON the LED*/
			GPIOD->BSRR |= LED_RED; //(1U<<14)
		}
	}
}






