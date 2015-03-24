#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include "stdlib.h"
#include "usarthelper.h"
#include "adchelper.h"
#include "amhelper.h"
#include "ds18b20.h"

#define MAX_FALLING_ITERATIONS 3

uint8_t is_opened = 0;
uint8_t is_parachute_opened = 0;
const int min_light_level = 55;
double delta_h = 300.0;
double last_height = 0.0;
int falling_iterations = 0;
static int current_iteration = 0;
int cycles = 0;

void PORTS_Init()
{
	DDRD  = 0b00001000;
	PORTD = 0b00000000;
}

void updateParachute()
{
	++cycles;
	double height = AM_GetHeight();
	int after_dot = ((int)(height * 100) % 100);
	if(after_dot < 0) {
		after_dot = -after_dot;
	}
	//printf("STATUS: Height: %d.%d\n", (int)(height), after_dot);
	//printf("STATUS: Height: %d\r\n", (int)(height * 100));
	++current_iteration;
	if(current_iteration == 10) {
		current_iteration = 0;
		printf("Height: %d\r\n", (int)(height * 100));
		if(height < last_height) {
			++falling_iterations;
		} else {
			falling_iterations = 0;
		}
		if(falling_iterations > MAX_FALLING_ITERATIONS) {
			is_opened = 1;
		}
		last_height = height;
	}
	if(cycles > 1800) {
		is_opened = 1;
	}
	if((height < delta_h) && is_opened && !is_parachute_opened) {
		PORTD |= 0b00001000;
		is_parachute_opened = 1;
		printf("Parachute is opened!\r\n");
		printf("Height: %d\r\n", (int)(height * 100));
		_delay_ms(3000);
		PORTD &= 0b11110111;
	}
}

void processLightSensor()
{
	uint16_t adc_data = ADC_Read((1 << MUX1));
	is_opened |= (adc_data > min_light_level);
	printf("STATUS: Current light level: %d State: ", adc_data);
	if(is_opened) {
		puts("Opened!");
	} else {
		puts("Closed!");
	}
}

int main()
{
	int i;
	for(i = 0; i < 10; ++i) {
		_delay_ms(1000);
	}
	PORTS_Init();
	USART_Init();
	ADC_Init();
	printf("Starting program...\r\n");
	AM_Init();
	
	while (1) {
		//processLightSensor();
		updateParachute();
		_delay_ms(10);
	}
}
