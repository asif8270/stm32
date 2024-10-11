/*
 * adc.h
 *
 *  Created on: Oct 11, 2024
 *      Author: Asif
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adcInit(void);
void startConversion(void);
uint32_t readADC(void);

#endif /* ADC_H_ */
