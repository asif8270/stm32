#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "lis3dsh.h"
#include "adc.h"
#include "systick.h"
#include "uart.h"
#include "exti.h"

#define GPIOD_EN			(1U<<3)

#define PIN12				(1U<<12)
#define LED_GREEN			PIN12

void EXTI0_IRQHandler(void);

int main(void)
{
	pa0_exti_init();
	uart2_tx_init();

	/*Enable clock access to the GPIOD*/
	RCC->AHB1ENR |= GPIOD_EN;

	/*Set the PD12 as OUTPUT*/
	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &= ~(1U<<25);

	while(1)
	{

	}
}

void extiCallback(void)
{
	systickDelayMs(20);
	/*Turn ON the LED4 (GREEN LED)*/
	GPIOD->ODR ^= LED_GREEN;

	printf("Button is pressed. \n\r");
}

void EXTI0_IRQHandler(void)
{
	/*Clear the PR*/
	if((EXTI->PR & (1U<<0)) != 0)
	{
		EXTI->PR |= (1U<<0);
	}

	/*Callback function*/
	extiCallback();
}
