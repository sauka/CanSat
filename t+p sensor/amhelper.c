#include <stdio.h>
#include <math.h>
#include <avr/io.h>
#include "adchelper.h"
#include "amhelper.h"
#include "ds18b20.h"

double start_pressure = 0.0;
const double v_ref = 5.0;
const double v_neg = 3.93;
static int current_iteration = 0;

double convertHeight(double p, double t)
{
	//int tmp = p * 100;
	//printf("STATUS: Presssure: %d\n", tmp);
    return log(p / start_pressure) * t * -29.24;
}

double convertPressure(int v)
{
    double vout = v_neg + (v * 0.5) / 512.0;
    return (vout / v_ref + 0.095) / 0.009;
}

double convertPressured(double v)
{
    double vout = v_neg + (v * 0.5) / 512.0;
    return (vout / v_ref + 0.095) / 0.009;
}

double AM_GetHeight()
{
	/*uint16_t temperature;
	uint16_t adc_data = ADC_Read((1 << MUX0) | (1 << MUX3));
	adc_data = ADC_ConvertDiff(adc_data);
	printf("STATUS: ADC pressure: %d\n", adc_data);
	double cur_pressure = convertPressure(adc_data);
	if(readTemperature(&temperature)) {
		printf("STATUS: Current sensor value: %u, temperature: %u\n", temperature, temperature >> 4);
		double cur_temperature = convertTemperature(temperature);
		return convertHeight(cur_pressure, cur_temperature);
	} else {
		puts("ERROR: Sensor not found!");
		return 0.0;
	}*/
	uint16_t temperature;
	double adc_data = ADC_Readd((1 << MUX0) | (1 << MUX3));
	adc_data = ADC_ConvertDiffd(adc_data);
	int after_dot = ((int)(adc_data * 100) % 100);
	if(after_dot < 0) {
		after_dot = -after_dot;
	}
	++current_iteration;
	if(current_iteration == 10) {
		current_iteration = 0;
		printf("STATUS: ADC pressure: %d\r\n", (int)(adc_data * 100));
	}
	double cur_pressure = convertPressured(adc_data);
	if(readTemperature(&temperature)) {
		//printf("STATUS: Current sensor value: %u, temperature: %u\n", temperature, temper1ature >> 4);
		double cur_temperature = convertTemperature(temperature);
		return convertHeight(cur_pressure, cur_temperature);
	} else {
		puts("ERROR: Sensor not found!\r");
		return 0.0;
	}
}

void AM_Init()
{
	//uint16_t adc_data = ADC_Read((1 << MUX0) | (1 << MUX3));
	//adc_data = ADC_ConvertDiff(adc_data);
	double adc_data = ADC_Readd((1 << MUX0) | (1 << MUX3));
	adc_data = ADC_ConvertDiffd(adc_data);
	start_pressure = convertPressured(adc_data);
	int tmp = start_pressure * 100;
	printf("STATUS: Start presssure: %d\r\n", tmp);
}
