/*
 * exti.c
 *
 *  Created on: Oct 17, 2024
 *      Author: Asif
 */

#include "exti.h"

#define GPIOA_EN		(1U<<0)

void pa0_exti_init(void)
{
	/*Disable global interrupts*/
	__disable_irq();

	/*Enable clock access for GPIOA*/
	RCC->AHB1ENR |= GPIOA_EN;

	/*Set PA0 as input*/
	GPIOA->MODER &= ~(1U<<0);
	GPIOA->MODER &= ~(1U<<1);

	/*Enable clock access for SYSCFG*/
	RCC->APB2ENR |= (1U<<14);

	/*Select PORTA for EXTI0 (SYSCFG)*/
	SYSCFG->EXTICR[0] = 0;

	/*Unmask EXTI0 (EXTI_IMR)*/
	EXTI->IMR |= (1U<<0);

	/*Select falling edge trigger (EXTI_FTSR)*/
	EXTI->FTSR |= (1U<<0);

	/*Enable EXTI0 line in NVIC*/
	NVIC_EnableIRQ(EXTI0_IRQn);

	/*Enable global interrupts*/
	__enable_irq();
}
