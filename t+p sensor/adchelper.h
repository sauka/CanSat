#ifndef ADCHELPER_H
#define ADCHELPER_H

#include <inttypes.h>

#define ADC_SIGN_BIT (1 << 9)

void ADC_Init(void);
uint16_t ADC_Read(uint8_t command);
double ADC_Readd(uint8_t command);
uint16_t ADC_ConvertDiff(uint16_t data);
double ADC_ConvertDiffd(double data);

#endif
