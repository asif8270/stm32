#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

int main(void)
{
	uart2_tx_init();
	while(1)
	{
		printf("Assalam o alaikum from STM32F4.....\r\n");
		for (int i = 0; i < 1000000; ++i) {}
	}
}
