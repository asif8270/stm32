/*
 * i2c.h
 *
 *  Created on: Sep 24, 2024
 *      Author: Asif
 */

#ifndef I2C_H_
#define I2C_H_

#define GPIOA_EN		(1U<<0)
#define GPIOE_EN		(1U<<4)
#define I2C1_EN			(1U<<21)
#define I2C1_PE			(1U<<0)
#define I2C1_100KHz		80
#define SD_MODE_MAX_TR	17

#define SR2_BUSY		(1U<<1)
#define CR1_START		(1U<<8)
#define SR1_SB			(1U<<0)
#define SR1_ADDR		(1U<<1)
#define SR1_TXE			(1U<<7)
#define CR1_ACK			(1U<<10)
#define SR1_RXNE		(1U<<6)
#define SR2_TRA			(1U<<2)
#define CR1_STOP		(1U<<9)
#define SR1_BTF			(1U<<2)

void GPIO_Init(void);
void I2C1_Init(void);
void I2C1_byteRead(char slv_addr, char reg_addr, char* pdata);
void i2c1_burstRead(char saddr, char maddr, int n, char* data);
void I2C1_burstWrite(char saddr, char maddr, int n, char* data);

#endif /* I2C_H_ */
