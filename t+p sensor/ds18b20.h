#ifndef DS18B20_H
#define DS18B20_H

#include <inttypes.h>

#define OW_PORT PORTD
#define OW_DDR  DDRD
#define OW_PIN  PIND

#define OW_BUS  PD5

#define PB_MASK (1 << OW_BUS)

#define SKIP_ROM  0xCC
#define CONVERT_T 0x44
#define MATCH_ROM 0x55
#define READ_SCRATCHPAD 0xBE

uint8_t OWI_InitTransmit();
void OWI_WriteByte(unsigned char data);
uint8_t OWI_ReadByte();

double convertTemperature(uint16_t t_value);
uint8_t readTemperature(uint16_t *temp);

#endif
