#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "lis3dsh.h"


int16_t x, y, z;
uint8_t rxData[6];
uint8_t who_am_i;
int8_t temp;

int main(void)
{
	lis3dshInit();
    lis3dshRead(LIS3DSH_WHO_AM_I, &who_am_i, 1);


	// Verify communication
	while (who_am_i != 0x3F)
	{
		return -1;  // Initialization failed
	}

    while(1)
    {
    	lis3dshRead(LIS3DSH_OUT_T, &temp, 1);

    	lis3dshRead(LIS3DSH_OUT_X_L, rxData, 6);

    	x = (rxData[1] << 8) | rxData[0];
    	y = (rxData[3] << 8) | rxData[2];
    	z = (rxData[5] << 8) | rxData[4];
    }
}
