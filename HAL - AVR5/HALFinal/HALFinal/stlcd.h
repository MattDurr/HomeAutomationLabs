
#define CMD_DISPLAY_OFF   0xAE
#define CMD_DISPLAY_ON    0xAF

#define CMD_SET_DISP_START_LINE  0x40
#define CMD_SET_PAGE  0xB0

#define CMD_SET_COLUMN_UPPER  0x10
#define CMD_SET_COLUMN_LOWER  0x00

#define CMD_SET_ADC_NORMAL  0xA0
#define CMD_SET_ADC_REVERSE 0xA1

#define CMD_SET_DISP_NORMAL 0xA6
#define CMD_SET_DISP_REVERSE 0xA7

#define CMD_SET_ALLPTS_NORMAL 0xA4
#define CMD_SET_ALLPTS_ON  0xA5
#define CMD_SET_BIAS_9 0xA2 
#define CMD_SET_BIAS_7 0xA3

#define CMD_RMW  0xE0
#define CMD_RMW_CLEAR 0xEE
#define CMD_INTERNAL_RESET  0xE2
#define CMD_SET_COM_NORMAL  0xC0
#define CMD_SET_COM_REVERSE  0xC8
#define CMD_SET_POWER_CONTROL  0x28
#define CMD_SET_RESISTOR_RATIO  0x20
#define CMD_SET_VOLUME_FIRST  0x81
#define  CMD_SET_VOLUME_SECOND  0
#define CMD_SET_STATIC_OFF  0xAC
#define  CMD_SET_STATIC_ON  0xAD
#define CMD_SET_STATIC_REG  0x0
#define CMD_SET_BOOSTER_FIRST  0xF8
#define CMD_SET_BOOSTER_234  0
#define  CMD_SET_BOOSTER_5  1
#define  CMD_SET_BOOSTER_6  3
#define CMD_NOP  0xE3
#define CMD_TEST  0xF0

#define LCDWIDTH 128
#define LCDHEIGHT 64

#define led_set_red(val) (LED_RED = (val&0xFF)) //macro function to set LED PWM level, masks the input with 255 to prevent overflows
#define led_set_green(val) (LED_GREEN = (val&0xFF)) //macro function to set LED PWM level, masks the input with 255 to prevent overflows
#define led_set_blue(val) (LED_BLUE = (val&0xFF)) //macro function to set LED PWM level, masks the input with 255 to prevent overflows


extern unsigned char lcd_buffer[128*64/8];

#include "SPI.h"
//void spiwrite(uint8_t c);

void setup(void);
void loop(void);

void st7565_init(void);
void st7565_command(unsigned char c);
void st7565_data(unsigned char c);
void st7565_set_brightness(unsigned char val);


void clear_screen(void);
void clear_buffer(unsigned char *buffer);
void write_buffer(unsigned char *buffer);

#define swap(a, b) { unsigned char t = a; a = b; b = t; }

void setpixel(unsigned char *buff, unsigned char x, unsigned char y, unsigned char color);

void invertrect(unsigned char *buff, unsigned char x, unsigned char y, unsigned char w, unsigned char h);
void drawstring(unsigned char *buff, unsigned char x, unsigned char line, unsigned char *c);
void drawstring_P(unsigned char *buff, unsigned char x, unsigned char line, unsigned char *c);
void drawrect(unsigned char *buff, unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char color);
void drawline(unsigned char *buff, unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char color);
void drawchar(unsigned char *buff, unsigned char x, unsigned char line, unsigned char c);
void drawcircle(unsigned char *buff, unsigned char x0, unsigned char y0, unsigned char r, unsigned char color);
void fillrect(unsigned char *buff, unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char color);
