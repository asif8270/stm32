/*
 * uart.h
 *
 *  Created on: Oct 11, 2024
 *      Author: Asif
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void uart2_tx_init(void);
void uart2_write(int ch);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
int __io_putchar(int ch);

#endif /* UART_H_ */
