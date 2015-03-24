#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ds18b20.h"

unsigned char OWI_InitTransmit()
{
	OW_DDR |= PB_MASK;
	OW_PORT &= ~PB_MASK;
	_delay_us(700);
	cli();

	OW_DDR &= ~PB_MASK;
	OW_PORT |= PB_MASK;
	_delay_us(65);
	sei();
	if ((OW_PIN & PB_MASK) == 0x00)
	{
		_delay_us(500);
		return 1;
	}
	_delay_us(500);
	return 0;
}

void OWI_WriteByte(unsigned char data)
{
	unsigned char i, current_bit;
	unsigned char mask = 0x01;
	
	for(i = 0; i < 8; ++i)
	{
		current_bit = (data & mask);
		cli();
		OW_PORT &= ~PB_MASK;				
		OW_DDR |= PB_MASK;
		if(current_bit) {
			_delay_us(6);
		} else {
			_delay_us(60);
		}
		OW_DDR &= ~PB_MASK;
		OW_PORT |= PB_MASK;
		if(current_bit) {
			_delay_us(64);
		} else {
			_delay_us(10);
		}
		sei();
		data >>= 1;
	}
}

unsigned char OWI_ReadByte()
{
	uint8_t result = 0;
	uint8_t i;
	for(i = 0; i < 8; ++i) {
		cli();
		OW_PORT &= ~PB_MASK;
		OW_DDR |= PB_MASK;

		_delay_us(6);
		OW_DDR &= ~PB_MASK;
		OW_PORT |= PB_MASK;
	
		_delay_us(9);
		if((OW_PIN & PB_MASK))
	    {
	    	result |= (1 << i);
	    }
		_delay_us(60);
		sei();
	}
	return result;
}

void match_ROM(unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4, unsigned char byte5, 
				unsigned char byte6, unsigned char byte7, unsigned char byte8)
{
	OWI_WriteByte(MATCH_ROM);
	OWI_WriteByte(byte1);
	OWI_WriteByte(byte2);
	OWI_WriteByte(byte3);
	OWI_WriteByte(byte4);
	OWI_WriteByte(byte5);
	OWI_WriteByte(byte6);
	OWI_WriteByte(byte7);
	OWI_WriteByte(byte8);
}

double convertTemperature(uint16_t t_value)
{
	return (t_value >> 4) + (t_value & 0x0F) * 0.0625 + 273.15;
}

uint8_t readTemperature(uint16_t *temp)
{	
	*temp = 0;

	if(OWI_InitTransmit()) {
		OWI_WriteByte(SKIP_ROM);
		OWI_WriteByte(READ_SCRATCHPAD);
		*temp =  OWI_ReadByte();
    	*temp |= ((unsigned short)OWI_ReadByte()) << 8;

		OWI_InitTransmit();
		OWI_WriteByte(SKIP_ROM);
		OWI_WriteByte(CONVERT_T);
		return 1;
	} else {
		return 0;
	}
}
