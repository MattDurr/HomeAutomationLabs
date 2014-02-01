/*
$Id:$

ST7565 LCD library!

Copyright (C) 2010 Limor Fried, Adafruit Industries

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

 // some of this code was written by <cstone@pobox.com> originally; it is in the public domain.
*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "stlcd.h"
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <string.h> 

#define SID_DDR DDRB
#define SID_PIN PINB
#define SID_PORT PORTB
#define SID 2

#define SCLK_DDR DDRB
#define SCLK_PIN PINB
#define SCLK_PORT PORTB
#define SCLK 1

#define A0_DDR DDRB
#define A0_PIN PINB
#define A0_PORT PORTB
#define A0 4

#define RST_DDR DDRB
#define RST_PIN PINB
#define RST_PORT PORTB
#define RST 7

//CS pin stuff
#define LCD_CONTROL_PORT   PORTB
#define LCD_CONTROL_DDR    DDRB
#define LCD_CONTROL_CS     0
// set CS to 0 = active
#define CSACTIVE LCD_CONTROL_PORT&=~(1<<LCD_CONTROL_CS)
// set CS to 1 = passive
#define CSPASSIVE LCD_CONTROL_PORT|=(1<<LCD_CONTROL_CS)

#define waitspi() while(!(SPSR&(1<<SPIF)))

extern uint8_t PROGMEM font[];

uint8_t is_reversed = 0;

int pagemap[] = { 3, 2, 1, 0, 7, 6, 5, 4 };

unsigned char lcd_buffer[] = { //array that holds the screen buffer, by default it holds the boot screen

 
	0xff, 0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
	0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
	0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
	0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, //1
	0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
	0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
	0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
	0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff, 0xff, 

	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
	0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x1f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 

	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 
	0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf8, 
	0xf8, 0xf8, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 

	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
	0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x01, 0x0f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 
	0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x0f, 0x01, 0x00, 0x00, 
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 
	0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
		
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 
	0x00, 0x00, 0x30, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xc0, 0xc0, 0xc0, 
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x30, 0x00, 
	0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 
	0xf0, 0xf0, 0xf0, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
		
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x01, 0x01, 0x01, 0x01, 0x0f, 
	0x0f, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 
	0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x0f, 0x0e, 0x0f, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x07, 
	0x07, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 
	0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x07, 0x07, 
	0x01, 0x01, 0x0d, 0x0d, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 

	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0x80, 0x80, 0x80, 0x80, 0xf8, 
	0xf8, 0x00, 0xf0, 0xf8, 0x98, 0x98, 0xf8, 0xf0, 0x00, 0xf8, 0xf8, 0x80, 0x80, 0xf8, 0xf8, 0x80, 
	0x80, 0xf8, 0xf8, 0x00, 0xf0, 0xf8, 0x48, 0x48, 0xc8, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
	0xf8, 0xf0, 0x30, 0xf0, 0xf8, 0x18, 0x00, 0xf0, 0xf8, 0x18, 0x10, 0xf8, 0xf8, 0x00, 0x80, 0xf8, 
	0xf8, 0x98, 0x98, 0xf0, 0xf8, 0x98, 0x98, 0xf8, 0xf0, 0x00, 0xf8, 0xf8, 0x80, 0x80, 0xf8, 0xf8, 
	0x80, 0x80, 0xf8, 0xf8, 0x00, 0xf0, 0xf8, 0x98, 0x98, 0x90, 0xf8, 0xf8, 0x00, 0x80, 0xf8, 0xf8, 
	0x98, 0x98, 0xf8, 0xf8, 0x00, 0xf0, 0xf8, 0x98, 0x98, 0xf8, 0xf0, 0x00, 0xf8, 0xf8, 0x80, 0x80, 
	0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 

	0xff, 0xff, 0xff, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,  //8
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xff, 0xff, 0xff, 

};

void setup(void) {

    st7565_init();
    st7565_command(CMD_DISPLAY_ON);
    st7565_command(CMD_SET_ALLPTS_NORMAL);
    clear_screen();
}

void clear_screen(void) {
  uint8_t p, c;
  
  for(p = 0; p < 8; p++) {

    st7565_command(CMD_SET_PAGE | p);
    for(c = 0; c < 129; c++) {
      st7565_command(CMD_SET_COLUMN_LOWER | (c & 0xf));
      st7565_command(CMD_SET_COLUMN_UPPER | ((c >> 4) & 0xf));
      st7565_data(0x0);
    }     
  }
}


void st7565_init(void) {
	// set pin directions
	A0_DDR |= _BV(A0);
	RST_DDR |= _BV(RST);
	LCD_CONTROL_DDR |= _BV(LCD_CONTROL_CS);

	// toggle RST low to reset; CS low so it'll listen to us
	CSACTIVE;
	RST_PORT &= ~_BV(RST);
	_delay_ms(500);
	RST_PORT |= _BV(RST);

	// LCD bias select
	st7565_command(CMD_SET_BIAS_7);
	// ADC select
	st7565_command(CMD_SET_ADC_NORMAL);
	// SHL select
	st7565_command(CMD_SET_COM_NORMAL);
	// Initial display line
	st7565_command(CMD_SET_DISP_START_LINE);

	// turn on voltage converter (VC=1, VR=0, VF=0)
	st7565_command(CMD_SET_POWER_CONTROL | 0x4);
	// wait for 50% rising
	_delay_ms(50);

	// turn on voltage regulator (VC=1, VR=1, VF=0)
	st7565_command(CMD_SET_POWER_CONTROL | 0x6);
	// wait >=50ms
	_delay_ms(50);

	// turn on voltage follower (VC=1, VR=1, VF=1)
	st7565_command(CMD_SET_POWER_CONTROL | 0x7);
	// wait
	_delay_ms(10);

	// set lcd operating voltage (regulator resistor, ref voltage resistor)
	st7565_command(CMD_SET_RESISTOR_RATIO | 0x6);

	//Turn off CS pin
	CSPASSIVE;

	// initial display line
	// set page address
	// set column address
	// write display data
}

/* Now in SPI.c
inline void spiwrite(uint8_t c) {
  
	//cli();//disable interupts

	CSACTIVE;

	SPDR = c;
	waitspi();

	CSPASSIVE;

	//sei();//enable interupts

}
*/

void st7565_command(uint8_t c) {
	A0_PORT &= ~_BV(A0);
	CSACTIVE;
	spiwrite(c);
	CSPASSIVE;
}

void st7565_data(uint8_t c) {
	A0_PORT |= _BV(A0);
	CSACTIVE;
	spiwrite(c);
	CSPASSIVE;

}


void st7565_set_brightness(uint8_t val) {//0 to 63

    st7565_command(CMD_SET_VOLUME_FIRST);
    st7565_command(CMD_SET_VOLUME_SECOND | (val & 0x3f));
}


void write_buffer(uint8_t *buffer) {
  uint8_t c, p;

  for(p = 0; p < 8; p++) {

    st7565_command(CMD_SET_PAGE | pagemap[p]);
    st7565_command(CMD_SET_COLUMN_LOWER | (0x0 & 0xf));
    st7565_command(CMD_SET_COLUMN_UPPER | ((0x0 >> 4) & 0xf));
    st7565_command(CMD_RMW);
    st7565_data(0xff);
    
    for(c = 0; c < 128; c++) {
      st7565_data(buffer[(128*p)+c]);
    }

  }

}

// the most basic function, set a single pixel
void setpixel(unsigned char *buff, unsigned char x, unsigned char y, unsigned char color) {
  if ((x >= LCDWIDTH) || (y >= LCDHEIGHT))
    return;

  // x is which column
  if (color) 
    buff[x+ (y/8)*128] |= _BV(7-(y%8));  
  else
    buff[x+ (y/8)*128] &= ~_BV(7-(y%8)); 
}

void drawbitmap(unsigned char *buff, unsigned char x, unsigned char y, const unsigned char bitmap, unsigned char w, unsigned char h, unsigned char color) 
{
  for (uint8_t j=0; j<h; j++) {
    for (uint8_t i=0; i<w; i++ ) {
      if (pgm_read_byte(bitmap + i + (j/8)*w) & _BV(j%8)) {
	setpixel(buff, x+i, y+j, color);
      }
    }
  }
}

void drawstring(unsigned char *buff, unsigned char x, unsigned char line, unsigned char *c) {
  while (c[0] != 0) {
    //uart0_putchar(c[0]);
    drawchar(buff, x, line, c[0]);
    c++;
    x += 6; // 6 pixels wide
    if (x + 6 >= LCDWIDTH) {
      x = 0;    // ran out of this line
      line++;
    }
    if (line >= (LCDHEIGHT/8))
      return;        // ran out of space :(
  }

}


void drawchar(unsigned char *buff, unsigned char x, uint8_t line, unsigned char c) {
  for (uint8_t i = 0; i<5; i++ ) {
    buff[x + (line*128) ] = pgm_read_byte(font+(c*5)+i);
    x++;
  }
}

// the most basic function, clear a single pixel
void clearpixel(unsigned char *buff, unsigned char x, unsigned char y) {
  // x is which column
  buff[x+ (y/8)*128] &= ~_BV(7-(y%8));
}

// bresenham's algorithm - thx wikpedia
void drawline(unsigned char *buff, unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char color) {

  uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  uint8_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int8_t err = dx / 2;
  int8_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;}

  for (; x0<x1; x0++) {
    if (steep) {
      setpixel(buff, y0, x0, color);
    } else {
      setpixel(buff, x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

// filled rectangle
void fillrect(unsigned char *buff, unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char color) {

  // stupidest version - just pixels - but fast with internal buffer!
  for (uint8_t i=x; i<x+w; i++) {
    for (uint8_t j=y; j<y+h; j++) {
      setpixel(buff, i, j, color);
    }
  }
}

// invert rectangle
void invertrect(unsigned char *buff, unsigned char x, unsigned char y, unsigned char w, unsigned char h) {

	// stupidest version - just pixels - but fast with internal buffer!
	for (uint8_t i=x; i<x+w; i++) {
		for (uint8_t j=y; j<y+h; j++) {
		
			buff[i+ (j/8)*128] ^= _BV(7-(j%8)); 
		}
	}
}


// draw a rectangle
void drawrect(unsigned char *buff, unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char color) {
  // stupidest version - just pixels - but fast with internal buffer!
  for (uint8_t i=x; i<x+w; i++) {
    setpixel(buff, i, y, color);
    setpixel(buff, i, y+h-1, color);
  }
  for (uint8_t i=y; i<y+h; i++) {
    setpixel(buff, x, i, color);
    setpixel(buff, x+w-1, i, color);
  } 
}


// draw a circle
void drawcircle(unsigned char *buff, unsigned char x0, unsigned char y0, unsigned char r, unsigned char color) {
  int8_t f = 1 - r;
  int8_t ddF_x = 1;
  int8_t ddF_y = -2 * r;
  int8_t x = 0;
  int8_t y = r;

  setpixel(buff, x0, y0+r, color);
  setpixel(buff, x0, y0-r, color);
  setpixel(buff, x0+r, y0, color);
  setpixel(buff, x0-r, y0, color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    setpixel(buff, x0 + x, y0 + y, color);
    setpixel(buff, x0 - x, y0 + y, color);
    setpixel(buff, x0 + x, y0 - y, color);
    setpixel(buff, x0 - x, y0 - y, color);
    
    setpixel(buff, x0 + y, y0 + x, color);
    setpixel(buff, x0 - y, y0 + x, color);
    setpixel(buff, x0 + y, y0 - x, color);
    setpixel(buff, x0 - y, y0 - x, color);
    
  }
}


// draw a circle
void fillcircle(unsigned char *buff, unsigned char x0, unsigned char y0, unsigned char r, unsigned char color) {
  int8_t f = 1 - r;
  int8_t ddF_x = 1;
  int8_t ddF_y = -2 * r;
  int8_t x = 0;
  int8_t y = r;

  for (uint8_t i=y0-r; i<=y0+r; i++) {
    setpixel(buff, x0, i, color);
  }

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    for (uint8_t i=y0-y; i<=y0+y; i++) {
      setpixel(buff, x0+x, i, color);
      setpixel(buff, x0-x, i, color);
    } 
    for (uint8_t i=y0-x; i<=y0+x; i++) {
      setpixel(buff, x0+y, i, color);
      setpixel(buff, x0-y, i, color);
    }    
  }
}


// clear everything
void clear_buffer(unsigned char *buff) {
  memset(buff, 0, 1024);
}


void drawstring_P(unsigned char *buff, unsigned char x, unsigned char line, unsigned char *c){
	while (pgm_read_byte ( c ) != 0x00) {
		drawchar(buff, x, line, pgm_read_byte ( c ));
		c++;
		x += 6; // 6 pixels wide
		if (x + 6 >= LCDWIDTH) {
		  x = 0;    // ran out of this line
		  line++;
		}
		if (line >= (LCDHEIGHT/8))
		  return;        // ran out of space :(
  }
}