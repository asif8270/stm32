#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "lis3dsh.h"
#include "adc.h"

uint32_t analogData;

int main(void)
{
	adcInit();
	startConversion();
    while(1)
    {
    	analogData = readADC();
		printf("ADC values: %d \n\r", (int)analogData);
    }
}
