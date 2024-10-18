/*
 * spi.h
 *
 *  Created on: Oct 5, 2024
 *      Author: Asif
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>

void SPI_gpioInit(void);
void SPI1_Config(void);
void SPI1_Transmit(uint8_t *data, uint32_t size);
void SPI1_Receive(uint8_t *data, uint32_t size);
void csLow(void);
void csHigh(void);

#endif /* SPI_H_ */
