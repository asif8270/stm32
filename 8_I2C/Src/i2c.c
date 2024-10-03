/*
 * i2c.c
 *
 *  Created on: Sep 24, 2024
 *      Author: Asif
 */

#include <stdint.h>
#include "stm32f4xx.h"
#include "i2c.h"

void GPIO_Init(void)
{
	/*PB6 -> SCL
	 *PB7 -> SDA */

	/*Enable clock access to GPIOB*/
	RCC->AHB1ENR |= GPIOB_EN;

	/*Set PB6 and PB7 output mode to alternate function*/
	/*Clear the pins PB6 and PB7*/
	GPIOB->MODER &= ~(3U<<12);
	GPIOB->MODER &= ~(3U<<14);

	/*PB6 - alternate function*/
	GPIOB->MODER |=  (2U<<12);

	/*PB7 - alternate function*/
	GPIOB->MODER |=  (2U<<14);

	/*Clear the pins*/
	GPIOB->AFR[0] &= ~(15U<<24);		//1111 0000 1111 1111 1111 1111 1111 1111
	GPIOB->AFR[0] &= ~(15U<<28);		//0000 1111 1111 1111 1111 1111 1111 1111

	/*Set PB6 and PB7 to AF4*/
	GPIOB->AFR[0] |=  (4U<<24);			//0000 0100 0000 0000 0000 0000 0000 0000
	GPIOB->AFR[0] |=  (4U<<28);			//0100 0000 0000 0000 0000 0000 0000 0000

	/*Set PB6 and PB7 pins output to open drain mode*/
	GPIOB->OTYPER |= ((1U<<6)|(1U<<7));

	/*Clear the pins*/
	GPIOB->PUPDR &= ~(3U<<12);
	GPIOB->PUPDR &= ~(3U<<14);

	/*Set pull-up for PB6*/
	GPIOB->PUPDR |=  (1U<<12);			//0000 0000 0000 0000 0001 0000 0000 0000

	/*Set pull-up for PB7*/
	GPIOB->PUPDR |=  (1U<<14);			//0000 0000 0000 0000 0100 0000 0000 0000
}

void I2C1_Init(void)
{
	/*Enable clock access to I2C1*/
	RCC->APB1ENR |= I2C1_EN;

	/*Enter reset mode*/
	I2C1->CR1 |= (1U<<15);

	/*Come out of reset mode*/
	I2C1->CR1 &= ~(1U<<15);

	/*Set peripheral clock frequency*/
	I2C1->CR2 &= ~(63U);
	I2C1->CR2 |=  (16U);

	/*Set I2C to standard mode, 100KHz clock*/
	I2C1->CCR =  (0x80);			//0000 0000 1000 0000

	/*Set I2C rise time*/
	I2C1->TRISE = (0x17);

	/*Enable I2C1 module*/
	I2C1->CR1 |= (0x0001);
}
