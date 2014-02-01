/*
 * SPI.h
 *
 * Created: 4/16/2012 10:18:09 AM
 *  Author: mlamoureux
 */ 
#include <stdint.h>

//SPI
#define SI_DDR DDRB
#define SI_PIN PINB
#define SI_PORT PORTB
#define SI 2

#define SO_DDR DDRB
#define SO_PIN PINB
#define SO_PORT PORTB
#define SO 3

#define SCLK_DDR DDRB
#define SCLK_PIN PINB
#define SCLK_PORT PORTB
#define SCLK 1

void spiwrite(uint8_t c);
void spiInit(void);
#define waitspi() while(!(SPSR&(1<<SPIF)))
