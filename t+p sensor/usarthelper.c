#include <avr/io.h>
#include <inttypes.h>
#include <stdio.h>
#include "usarthelper.h"
#include <util/setbaud.h>

static void USART_Transmit(unsigned char data);

static FILE usart_stdout =
	FDEV_SETUP_STREAM(USART_Transmit, NULL, _FDEV_SETUP_WRITE);

static void USART_Transmit(unsigned char data)
{
	// Wait for empty transmit buffer
	while((UCSRA & 0x20) == 0x00);
	// Put dta into buffer
	UDR = data;
}

void USART_Init()
{
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	//UCSRA = 1 << U2X;
	// Enable receiver and transmiter
	UCSRB = 0x18;
	UCSRC = 0x86;

	stdout = &usart_stdout;
}
