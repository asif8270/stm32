/*
 * systick.c
 *
 *  Created on: Oct 11, 2024
 *      Author: Asif
 */

#include "stm32f4xx.h"
#include "systick.h"

#define SYSTICK_LOAD_VAL	16000
#define SYSTICK_EN			(1U<<0)
#define SYSTICK_CLK_SRC		(1U<<2)
#define SYSTICK_COUNT_FLAG	(1U<<16)

void systickDelayMs(int delay)
{
	/*Load the reload value register with cycles in 1ms*/
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/*Clear the current value register*/
	SysTick->VAL = 0;

	/*Enable clock source*/
	SysTick->CTRL |= SYSTICK_CLK_SRC;

	/*Enable the systick*/
	SysTick->CTRL |= SYSTICK_EN;

	for (int i = 0; i < delay; i++)
	{
		/*Wait until the count flag is set*/
		while(!(SysTick->CTRL & SYSTICK_COUNT_FLAG)){}
	}
	SysTick->CTRL = 0;
}
