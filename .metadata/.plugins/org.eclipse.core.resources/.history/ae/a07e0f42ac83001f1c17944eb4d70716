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
	/*PA5 -> SCL
	 *PA7 -> SDA
	 *PE3 -> CS_I2C/SPI */

	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOA_EN;

	/*Set PA5 and PA7 output mode to alternate function*/
	/*Clear the pins PA5 and PA7*/
	GPIOA->MODER &= ~(3U<<10);
	GPIOA->MODER &= ~(3U<<14);

	/*PA5 - alternate function*/
	GPIOA->MODER |=  (2U<<10);

	/*PA7 - alternate function*/
	GPIOA->MODER |=  (2U<<14);

	/*Clear the pins*/
	GPIOA->AFR[0] &= ~(15U<<20);		//1111 1111 0000 1111 1111 1111 1111 1111
	GPIOA->AFR[0] &= ~(15U<<28);		//0000 1111 1111 1111 1111 1111 1111 1111

	/*Set PA5 and PA7 to AF4*/
	GPIOA->AFR[0] |=  (4U<<20);			//0000 0000 0100 0000 0000 0000 0000 0000
	GPIOA->AFR[0] |=  (4U<<28);			//0100 0000 0000 0000 0000 0000 0000 0000

	/*Set PA5 and PA7 pins output to open drain mode*/
	GPIOA->OTYPER |= ((1U<<5)|(1U<<7));

	/*Clear the pins*/
	GPIOA->PUPDR &= ~(3U<<10);
	GPIOA->PUPDR &= ~(3U<<14);

	/*Set pull-up for PB6*/
	GPIOA->PUPDR |=  (1U<<10);			//0000 0000 0000 0000 0000 0100 0000 0000

	/*Set pull-up for PB7*/
	GPIOA->PUPDR |=  (1U<<14);			//0000 0000 0000 0000 0100 0000 0000 0000

	/*Enable clock access to GPIOE*/
	RCC->AHB1ENR |= GPIOE_EN;

	/*Set PE3 to output mode*/
	/*Clear the pin PE3*/
	GPIOE->MODER &= ~(3U<<6);

	/*PA5 - output*/
	GPIOE->MODER |=  (1U<<6);

	/*Set PE3 output to open drain mode*/
	GPIOE->OTYPER |= (1U<<3);

	/*Set pull-up for PE3*/
	GPIOE->PUPDR |= (1U<<6);
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
	I2C1->CCR =  I2C1_100KHz;			//0000 0000 1000 0000

	/*Set I2C rise time*/
	I2C1->TRISE = SD_MODE_MAX_TR;

	/*Enable I2C1 module*/
	I2C1->CR1 |= I2C1_PE;
}

void I2C1_byteRead(char slv_addr, char reg_addr, char* pdata)
{
	volatile int tmp;

	/*Wait until not busy*/
	while((I2C1->SR2 & SR2_BUSY)){}

	/*Generate start*/
	I2C1->CR1 |= CR1_START;

	/*Wait until start flag is set*/
	while(!(I2C1->SR1 & SR1_SB)){}

	/*Transmit slave address + Write*/
	I2C1->DR = (slv_addr << 1);

	/*Wait until addr flag is set*/
	while(!(I2C1->SR1 & SR1_ADDR)){}

	/*Clear addr flag by reading the SR2*/
	tmp = I2C1->SR2;

	/*Wait until transmitter empty*/
	while(!(I2C1->SR1 & SR1_TXE)){}

	/*Send memory address*/
	I2C1->DR = reg_addr;

	/*Wait until transmitter empty*/
	while(!(I2C1->SR1 & SR1_TXE)){}

	/*Generate restart*/
	I2C1->CR1 |= CR1_START;

	/*Wait until start flag is set*/
	while(!(I2C1->SR1 & SR1_SB)){}

	/*Transmit slave address + Read*/
	I2C1->DR = (slv_addr << 1 | 1);

	/*Wait until addr flag is set*/
	while(!(I2C1->SR1 & SR1_ADDR)){}

	/*Disable Acknowledge*/
	I2C1->CR1 &= ~CR1_ACK;

	/*Clear addr flag*/
	tmp = I2C1->SR2;

	/*Generate stop after data received*/
	I2C1->CR1 |= CR1_STOP;

	/*Wait until RXNE flag is set*/
	while(!(I2C1->SR1 & SR1_RXNE)){}

	/*Read data from DR*/
	*pdata++ = I2C1->DR;
}

void i2c1_burstRead(char saddr, char maddr, int n, char* data)
{
	volatile int tmp;

	/*Wait until not busy*/
	while((I2C1->SR2 & SR2_BUSY)){}

	/*Generate start*/
	I2C1->CR1 |= CR1_START;

	/*Wait until start flag is set*/
	while(!(I2C1->SR1 & SR1_SB)){}

	/*Transmit slave address + Write*/
	I2C1->DR = (slv_addr << 1);

	/*Wait until addr flag is set*/
	while(!(I2C1->SR1 & SR1_ADDR)){}

	/*Clear addr flag by reading the SR2*/
	tmp = I2C1->SR2;

	/*Wait until transmitter empty*/
	while(!(I2C1->SR1 & SR1_TXE)){}

	/*Send memory address*/
	I2C1->DR = reg_addr;

	/*Wait until transmitter empty*/
	while(!(I2C1->SR1 & SR1_TXE)){}

	/*Generate restart*/
	I2C1->CR1 |= CR1_START;

	/*Wait until start flag is set*/
	while(!(I2C1->SR1 & SR1_SB)){}

	/*Transmit slave address + Read*/
	I2C1->DR = (slv_addr << 1 | 1);

	/*Wait until addr flag is set*/
	while(!(I2C1->SR1 & SR1_ADDR)){}

	/*Clear addr flag*/
	tmp = I2C1->SR2;

	/*Enable Acknowledge*/
	I2C1->CR1 |= CR1_ACK;

	while(n>0U)
	{
		/*if one byte*/
		if(n == 1U)
		{
			/*Disable Acknowledge*/
			I2C1->CR1 &= ~CR1_ACK;

			/*Generate stop after data received*/
			I2C1->CR1 |= CR1_STOP;

			/*Wait until RXNE flag is set*/
			while(!(I2C1->SR1 & SR1_RXNE)){}

			/*Read data from DR*/
			*pdata++ = I2C1->DR;

			break;
		}
		else
		{
			/*Wait until RXNE flag is set*/
			while(!(I2C1->SR1 & SR1_RXNE)){}

			/*Read data from DR*/
			*pdata++ = I2C1->DR;

			n--;
		}
	}
}

void I2C1_burstWrite(char saddr, char maddr, int n, char* data)
{
	volatile int tmp;

	/*Wait until not busy*/
	while((I2C1->SR2 & SR2_BUSY)){}

	/*Generate start*/
	I2C1->CR1 |= CR1_START;

	/*Wait until start flag is set*/
	while(!(I2C1->SR1 & SR1_SB)){}

	/*Transmit slave address + Write*/
	I2C1->DR = (slv_addr << 1);

	/*Wait until addr flag is set*/
	while(!(I2C1->SR1 & SR1_ADDR)){}

	/*Clear addr flag by reading the SR2*/
	tmp = I2C1->SR2;

	/*Wait until transmitter empty*/
	while(!(I2C1->SR1 & SR1_TXE)){}

	/*Send memory address*/
	I2C1->DR = reg_addr;

	for(int i= 0; i<n; i++)
	{
		/*Wait until data register(transmitter) empty*/
		while(!(I2C1->SR1 & SR1_TXE)){}

		/*Send data to data register*/
		I2C1->DR = *pdata++;
	}
	/*Wait until transfer finished*/
	while(!(I2C1->SR1 & SR1_BTF)){}

	/*Generate stop after data written*/
	I2C1->CR1 |= CR1_STOP;
}
