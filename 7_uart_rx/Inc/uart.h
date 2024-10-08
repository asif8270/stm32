/*
 * uart.h
 *
 *  Created on: Sep 24, 2024
 *      Author: Asif
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

void uart2_tx_init(void);
void uart2_rxtx_init(void);
char uart2_read(void);

#endif /* UART_H_ */
