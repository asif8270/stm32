/*
 * uart.c
 *
 *  Created on: Oct 11, 2024
 *      Author: Asif
 */

#include "stm32f4xx.h"
#include "uart.h"

#define GPIOA_EN			(1U<<0)
#define UART2_EN			(1U<<17)

#define SYS_FREQ			16000000
#define APB1_CLK			SYS_FREQ
#define UART_BAUDRATE		115200

#define UART_TE				(1U<<3)
#define UART_UE				(1U<<13)

#define SR_TXE				(1U<<7)

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

void uart2_tx_init(void)
{
	/********** Configuring the GPIOA **********/

	/*Enable clock access to the GPIOA*/
	RCC->AHB1ENR |= GPIOA_EN;

	/*Set the PA2 mode as Alternate Function*/
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*Set PA2 the Alternate Function type to UART_TX (AF07) */
	GPIOA->AFR[0]   |= (1U<<8);
	GPIOA->AFR[0]   |= (1U<<9);
	GPIOA->AFR[0]   |= (1U<<10);
	GPIOA->AFR[0]   &= ~(1U<<11);

	/********** Configuring the UART **********/

	/*Enable clock access to the UART module*/
	RCC->APB1ENR |= UART2_EN;

	/*Configure the UART module baud rate*/
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/*Configure the UART module direction*/
	USART2->CR1  = UART_TE;

	/*Enable the UART module*/
	USART2->CR1 |= UART_UE;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

void uart2_write(int ch)
{
	/*Make sure transmit data register empty*/
	while(!(USART2->SR & SR_TXE)){}
	/*Write data to the data register*/
	USART2->DR = (ch & 0xFF);
}
