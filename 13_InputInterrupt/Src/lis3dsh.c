/*
 * lis302dl.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Asif
 */

#include <lis3dsh.h>

void lis3dshRead(uint8_t regAddress, uint8_t *rxdata, uint8_t size)
{
    /*Combine address and read bit*/
    regAddress |= LIS3DSH_Read_Flag;

    csLow();

    /*Send address to read from*/
    SPI1_Transmit(&regAddress, 1);

    /*Read data*/
    SPI1_Receive(rxdata, size);

    csHigh();
}

void lis3dshWrite(uint8_t regAddress, uint8_t value)
{
	uint8_t data[2];

	/*Enable multi-byte, place address into buffer*/
	data[0] = regAddress;

	/*Place data into buffer*/
	data[1] = value;

	//CS low
    csLow();

    /*Transmit data and address*/
    SPI1_Transmit(data, 2);

    //CS high
    csHigh();
}

void lis3dshInit(void)
{
	/*Enable SPI GPIO*/
	SPI_gpioInit();

	/*Enable SPI*/
	SPI1_Config();

	/*Set data format range to +-2g, 100Hz*/
	lis3dshWrite(LIS3DSH_CTRL_REG4, LIS3DSH_ODR_100HZ);
}











