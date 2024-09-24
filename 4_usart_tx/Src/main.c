#include "stm32f4xx.h"

#define GPIOA_EN			(1U<<0)
#define USART_EN			(1U<<17)

#define PIN14				(1U<<14)
#define PIN0				(1U<<0)

void gpio_init(void);
void uart_init(void);

int main(void)
{
	/*Enable clock access to the GPIOA*/
	RCC->AHB1ENR |= GPIOA_EN;
	RCC->APB1ENR |= USART_EN;



	while(1)
	{
	}
}

void gpio_init(void)
{
	/*Set the PA2 as Alternate Function*/
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*Configuring the Alternate Function-AF7*/
	GPIOA->AFR   |= (1U<<8);
	GPIOA->AFR   |= (1U<<9);
	GPIOA->AFR   |= (1U<<10);
	GPIOA->AFR   &= ~(1U<<11);

}

void uart_init(void)
{

}





