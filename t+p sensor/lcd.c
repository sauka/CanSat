
#include "lcd.h"

const char rus_table[] = {'A', 0xA0, 'B', 0xA1, 0xE0, 'E', 0xA3, 0xA4, 0xA5,
                                  0xA6, 'K', 0xA7, 'M', 'H', 'O', 0xA8, 'P', 'C', 'T', 0xA9,
                                  0xAA, 'X', 0xE1, 0xAB, 0xAC, 0xE2, 0xAD, 0xAE, 'b', 0xAF,
                                  0xB0, 0xB1, 'a', 0xB2, 0xB3, 0xB4, 0xE3, 'e', 0xB6,
                                  0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 'o', 0xBE, 'p',
                                  'c', 0xBF, 'y', 0xE4, 'x', 0xE5, 0xC0, 0xC1, 0xE6, 0xC2,
                                  0xC3, 0xC4, 0xC5, 0xC6, 0xC7};

void lcd_comm(unsigned char comm)
{
  lcd_busy();
  LCD_PORT_NULL;
  /*if (comm & 0x80)
   LCD_PORT |= (1 << LCD_DB7);
  if (comm & 0x40)
   LCD_PORT |= (1 << LCD_DB6);
  if (comm & 0x20)
   LCD_PORT |= (1 << LCD_DB5);
  if (comm & 0x10)
   LCD_PORT |= (1 << LCD_DB4);*/
  LCD_PORT |= (comm & 0xF0); // this variant is faster, but ignores bits definition (depends on schematic)
  lcd_enable();

  lcd_busy();
  LCD_PORT_NULL;
/*  if (comm & 0x08)
   LCD_PORT |= (1 << LCD_DB7);
  if (comm & 0x04)
   LCD_PORT |= (1 << LCD_DB6);
  if (comm & 0x02)
   LCD_PORT |= (1 << LCD_DB5);
  if (comm & 0x01)
   LCD_PORT |= (1 << LCD_DB4);*/
  LCD_PORT |= (comm & 0x0F) << 4;
  lcd_enable();
}

/***************************************************
 *  Display initialization
 ***************************************************/

void lcd_init(void)
{
// Make the LCD port an output
  DDRD |= (1 << LCD_RS) | (1 << LCD_ENABLE) | (1 << LCD_DB4) | (1 << LCD_DB5) | (1 << LCD_DB6) | (1 << LCD_DB7);
  _delay_ms(100);	//Allow LCD to power up > 30mS

  CLEAR_RS;

  // LCD Starts up in 8-Bit mode, busy cannot be checked at moment
  // we send these bytes according to the datasheet.
  LCD_PORT_NULL;
  LCD_PORT |= (1 << LCD_DB4) | (1 << LCD_DB5); lcd_enable();  _delay_ms(5);
  LCD_PORT_NULL;
  LCD_PORT |= (1 << LCD_DB4) | (1 << LCD_DB5); lcd_enable();  _delay_ms(1);
  LCD_PORT_NULL;
  LCD_PORT |= (1 << LCD_DB4) | (1 << LCD_DB5); lcd_enable();

  // Now we can check the Busy
  lcd_busy();
  LCD_PORT_NULL;
  LCD_PORT |= (1 << LCD_DB5); lcd_enable();	// This places the LCD in 4-bit mode. //LCD_PORT = 0x20
  
  lcd_comm(0x2C); // N & F
  lcd_comm(0x08); // display off
  lcd_comm(0x01); // display clear
  lcd_comm(0x06); // inc mode, no shift
  
  lcd_comm(0x0C); // display on

//  lcd_cls();	// Clear Screen
  lcd_home();	// Home Cursor
}

/***************************************************
 *  Check if the LCD is Busy
 ***************************************************/
void lcd_busy(void)
{
	//We should check the busy flag properly, but
	//were going to cheat and just use a delay to
	//allow the LCD to not be busy

  _delay_us(100);
}

/***************************************************
 *  Toggle the Enable Pin on the LCD
 ***************************************************/
void lcd_enable()
{
  _delay_us(100);
  SET_E;		//E=1
  _delay_us(1700);
  CLEAR_E;	        //E=0
}

/***************************************************
 *  Clear Display
 ***************************************************/
void lcd_cls()
{
  CLEAR_RS;
  lcd_busy();
  LCD_PORT_NULL; lcd_enable();	//CLEAR SCREEN

  LCD_PORT |= (1 << LCD_DB4); lcd_enable();
  _delay_ms(2);
}

/***************************************************
 *  Go to Home Position (Top Left)
 ***************************************************/
void lcd_home()
{
  CLEAR_RS;
  lcd_comm(0x02);
  _delay_ms(2);
}

/****************************************************
 *  Goto position   (0x00 - 1.row, 1.col)
 *                  (0x40 - 1.row, 2.col)
 ****************************************************/
void lcd_goto(unsigned char pos)
{
  CLEAR_RS;
  lcd_comm(pos | 0x80);
  _delay_us(40);
}

/****************************************************
 *  Put character on LCD
 ****************************************************/
void lcd_putc(char data)
{
  //Send the UPPER nibble first
  SET_RS;
  lcd_comm(data);
  CLEAR_RS;
}

/***************************************************
 *  Display null terminated string
 ***************************************************/
void lcd_puts(char *data)
{
  while(*data)
    {
        lcd_putc(*data);
        data++;
    }
}

void lcd_putsr(char *data)
{
  while(*data)
    {
      if (*data >= 0xC0) // russian font
       lcd_putc(rus_table[*data-0xC0]);
      else
       lcd_putc(*data);
        data++;
    }
}

/****************************************************
 *  Display integer
 ****************************************************/

void lcd_printint(unsigned int x)
{
  char str[7],pos=0;
  if (x == 0) lcd_putc('0');
  while (x) {
    str[pos++] = '0' + x%10;
    x = x/10;
  }
  while(pos--) {
    lcd_putc(str[pos]);
  }
}

void lcd_printlong(unsigned long x)
{
  char str[15],pos=0;
  if (x == 0) lcd_putc('0');
  while (x) {
    str[pos++] = '0' + x%10;
    x = x/10;
  }
  while(pos--) {
    lcd_putc(str[pos]);
  }
}
