/*
 * adc.c
 *
 *  Created on: Oct 11, 2024
 *      Author: Asif
 */

#include "stm32f4xx.h"
#include "adc.h"

#define ADC_EN		(1U<<8)
#define ADC_ON		(1U<<0)
#define ADC_CH1		(1U<<0)
#define SR_EOC		(1U<<1)
#define CR2_SWSTART	(1U<<30)
#define CR2_CONT	(1U<<1)

#define GPIOAEN		(1U<<0)

void adcInit(void)
{
	/*Enable clock to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA1 mode as analog*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/*Enable clock to ADC1*/
	RCC->APB2ENR |= ADC_EN;

	/*Start conversion at channel 1*/
	ADC1->SQR3 = ADC_CH1;

	/*Conversion sequence length*/
	ADC1->SQR1 = 0x00;

	/*Enable the ADC1*/
	ADC1->CR2 |= ADC_ON;
}

void startConversion(void)
{
	/*Enbable continuous conversion mode*/
	ADC1->CR2 |= CR2_CONT;

	/*Start conversion*/
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t readADC(void)
{
	/*Wait for the conversion to be complete*/
	while(!(ADC1->SR & SR_EOC)){};

	/*Return the converted value*/
	return (ADC1->DR);
}
