#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "lis3dsh.h"
#include "adc.h"
#include "systick.h"
#include "uart.h"

#define GPIOD_EN			(1U<<3)

#define PIN12				(1U<<12)
#define LED_GREEN			PIN12

int main(void)
{
	uart2_tx_init();

	/*Enable clock access to the GPIOD*/
	RCC->AHB1ENR |= GPIOD_EN;

	/*Set the PD12 as OUTPUT*/
	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);

	while(1)
	{
		/*Turn ON the LED4 (GREEN LED)*/
		GPIOD->ODR ^= LED_GREEN;

		printf("A second just pass. \n\r");
		systickDelayMs(1000);
	}
}
