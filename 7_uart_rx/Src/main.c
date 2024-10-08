#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOD_EN			(1U<<3)

#define PIN12				(1U<<12)
#define LED_GREEN			PIN12

char key;

int main(void)
{
	/*Enable clock access to the GPIOD*/
	RCC->AHB1ENR |= GPIOD_EN;

	/*Set the PD12 as OUTPUT*/
	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);

	uart2_rxtx_init();

	while(1)
	{
		key = uart2_read();
		if (key == '1')
		{
			GPIOD->ODR |= LED_GREEN;
		}
		else
		{
			GPIOD->ODR &= ~LED_GREEN;
		}
	}
}
