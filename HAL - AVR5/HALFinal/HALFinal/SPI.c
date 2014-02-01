/*
 * CProgram1.c
 *
 * Created: 4/16/2012 10:17:43 AM
 *  Author: mlamoureux
 */ 

#include "SPI.h"
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

inline void spiwrite(uint8_t c) {
  
	//cli();//disable interupts

	SPDR = c;
	waitspi();

	//sei();//enable interupts

}

void spiInit(void){
	cli();//disable interupts
	// initialize SPI interface
	// master mode and Fosc/2 clock:
    SPCR = _BV(SPE)|_BV(MSTR);
    SPSR |= _BV(SPI2X);

	// initialize I/O
    // ss as output:
	SI_DDR  |= _BV(SI) | _BV(SCLK); // mosi, sck output
	SO_DDR &= ~_BV(SO); // MISO is input
    //
    SI_PORT &= ~_BV(SI); // MOSI low
    SCLK_PORT &= ~_BV(SCLK); // SCK low
	sei();//enable interupts

}