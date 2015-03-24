#include <avr/io.h>
#include "adchelper.h"

void ADC_Init()
{
	ADCSRA = (1 << ADEN);
}

uint16_t ADC_Read(uint8_t command) 
{
	int i;
	ADMUX = 0;
	ADMUX = (1 << REFS0) | command;
	// Wait for stabilization (just to be sure).
	for(i = 0; i < 10; ++i) {
		ADCSRA |= (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
	}
	uint32_t result = 0;
	for(i = 0; i < 4; ++i) {
		ADCSRA |= (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
		result += ADCL;
		result += (ADCH << 8);
	}
	result >>= 2;
  	return result;
}

double ADC_Readd(uint8_t command) 
{
	int i;
	ADMUX = 0;
	ADMUX = (1 << REFS0) | command;
	// Wait for stabilization (just to be sure).
	for(i = 0; i < 10; ++i) {
		ADCSRA |= (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
	}
	double result = 0;
	for(i = 0; i < 512; ++i) {
		ADCSRA |= (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
		result += ADCL;
		result += (ADCH << 8);
	}
	result /= 512.0;
  	return result;
}

uint16_t ADC_ConvertDiff(uint16_t data)
{
	if(data & ADC_SIGN_BIT) {
		data &= ~ADC_SIGN_BIT;
		data = -data;
		data += 512;
		data = -data;
	}
	return data;
}


double ADC_ConvertDiffd(double data)
{
	if(data > 512.0) {
		data -= 1024.0;
	}
	return data;
}
