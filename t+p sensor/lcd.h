#ifndef __LCD_H_
#define __LCD_H_

#ifndef ENABLE_BIT_DEFINITIONS
  #define ENABLE_BIT_DEFINITIONS
#endif

#include <avr/io.h>
#include <util/delay.h>

#define LCD_PORT	PORTD	// Port which the LCD is connected
//#define LCD_DDR		DDRB	// Data Direction Register (should be for the port above)

#define LCD_RS					2				// Register Select Pin
#define LCD_ENABLE				3				// Enable Pin
#define LCD_DB4                 4               // DB4 (Data) Pin
#define LCD_DB5                 5               // DB5 (Data) Pin
#define LCD_DB6                 6               // DB6 (Data) Pin
#define LCD_DB7                 7               // DB7 (Data) Pin

// macros
#define SET_E		PORTD |=  (1 << LCD_ENABLE);	//E = 1
#define CLEAR_E		PORTD &= ~(1 << LCD_ENABLE);	//E = 0
#define SET_RS		PORTD |=  (1 << LCD_RS);		//RS = 1
#define CLEAR_RS	PORTD &= ~(1 << LCD_RS);		//RS = 0

#define LCD_PORT_NULL   LCD_PORT &= ~((1 << LCD_DB4) | (1 << LCD_DB5) | (1 << LCD_DB6) | (1 << LCD_DB7));

#define LINE1		0x00
#define LINE2		0x40

typedef unsigned char byte;

void lcd_init();												// initialize display
void lcd_busy();												
void lcd_enable();
void lcd_cls();													// clear display
void lcd_home();												// return to start position
void lcd_goto(unsigned char mesto);								// set cursor to position passed as argument
void lcd_putc(char data);										// display a character
void lcd_puts(char *data);										// display a string
void lcd_putsr(char *data);										// display a string (+ displays a russian characters)
void lcd_printint(unsigned int x);								// display an unsigned number of type unsigned short
void lcd_printlong(unsigned long x);							// display an unsigned number of type unsigned long

//void lcd_setcursor(bool sh; bool blinking);
void lcd_cursor_shift_left();
void lcd_cursor_shift_right();
void lcd_shift_left();
void lcd_shift_right();

#endif
