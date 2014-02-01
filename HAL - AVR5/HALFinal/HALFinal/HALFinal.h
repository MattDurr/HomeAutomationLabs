#include <stdint.h>

//USB definitions
#define USB_LED_CONFIG	(DDRE |= (1<<6))
#define USB_LED_ON		(PORTE |= (1<<6))
#define USB_LED_OFF		(PORTE &= ~(1<<6))
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

//Button PIN Definitions
#define RAW_BUTT_UP ((PINF >> 4) & 1)
#define RAW_BUTT_DOWN ((PINF >> 5) & 1)
#define RAW_BUTT_LEFT ((PINE >> 6) & 1)
#define RAW_BUTT_RIGHT ((PINF >> 0) & 1)
#define RAW_BUTT_SELECT ((PINF >> 1) & 1)

extern uint8_t button_state;

//Button variable definitions
#define BUTT_UP ((button_state >> 4) & 1)
#define BUTT_DOWN ((button_state >> 3) & 1)
#define BUTT_LEFT ((button_state >> 2) & 1)
#define BUTT_RIGHT ((button_state >> 1) & 1)
#define BUTT_SELECT ((button_state >> 0) & 1)

//LCD LED Definitions
#define LED_BLUE OCR0B
#define LED_GREEN OCR4A
#define LED_RED OCR3AL

//Relay Definitions
#define RELAY1_DDR DDRD
#define RELAY1_PIN PIND
#define RELAY1_PORT PORTD
#define RELAY1 7

#define RELAY2_DDR DDRD
#define RELAY2_PIN PIND
#define RELAY2_PORT PORTD
#define RELAY2 6

#define RELAY3_DDR DDRD
#define RELAY3_PIN PIND
#define RELAY3_PORT PORTD
#define RELAY3 4

#define RELAY4_DDR DDRF
#define RELAY4_PIN PINF
#define RELAY4_PORT PORTF
#define RELAY4 6

#define RELAY1_SET() (RELAY1_PORT |= _BV(RELAY1))
#define RELAY2_SET() (RELAY2_PORT |= _BV(RELAY2))
#define RELAY3_SET() (RELAY3_PORT |= _BV(RELAY3))
#define RELAY4_SET() (RELAY4_PORT |= _BV(RELAY4))

#define RELAY1_CLEAR() (RELAY1_PORT &= ~(_BV(RELAY1)))
#define RELAY2_CLEAR() (RELAY2_PORT &= ~(_BV(RELAY2)))
#define RELAY3_CLEAR() (RELAY3_PORT &= ~(_BV(RELAY3)))
#define RELAY4_CLEAR() (RELAY4_PORT &= ~(_BV(RELAY4)))

#define RELAY1_READ() ( (RELAY1_PORT >> RELAY1) & 1)
#define RELAY2_READ() ( (RELAY2_PORT >> RELAY2) & 1)
#define RELAY3_READ() ( (RELAY3_PORT >> RELAY3) & 1)
#define RELAY4_READ() ( (RELAY4_PORT >> RELAY4) & 1)

#define RELAY1_TOGGLE() (RELAY1_PORT ^= _BV(RELAY1))
#define RELAY2_TOGGLE() (RELAY2_PORT ^= _BV(RELAY2))
#define RELAY3_TOGGLE() (RELAY3_PORT ^= _BV(RELAY3))
#define RELAY4_TOGGLE() (RELAY4_PORT ^= _BV(RELAY4))

  

//----------Structures-----------

struct led_struct{

	char update_flag;
	char red;
	char green;
	char blue;
	char contrast;

} lcd_led;

struct calendarEvent{

	uint8_t DayOfWeek; //MSB/7th = NULL, 6th bit = Sun, 5th = Mon ... 0th = Sat -- GENIUS
	uint16_t startData; //data broken into: 15th bit == NULL; 14th-11th == month; 10th-0th == minute of day
	uint16_t duration; //how long in minutes event lasts
	uint8_t relay; //byte is broken up into two bits per relay: bits 7&6 = RL1 .. 1&0 = RL4 See truth table below for what their state means -- GENIUS
	//maybe some IO stuff later

	/*
	Relay Truth table
	00 == do nothing
	01 == on
	10 == off
	11 == toggle
	*/
};

struct networkConfigStruct{

	uint8_t mymac[6];
	uint8_t myip[4];
	uint8_t enableDHCP;

};


//function definitions
void lcd_refresh( unsigned char *buffer);
void butt_state( void );
uint16_t http200ok(void);
void deldot(char *s);
void relay_init(void);
void io_init(void);
void lcd_init(void);
#include "SPI.h"
//void spiInit(void);
void button_init(void);
void timer_init(void);
uint8_t readCalanderStructEEPROM(struct calendarEvent *bufferEvent, uint8_t typeID, uint8_t number);
uint8_t writeCalanderStructEEPROM(struct calendarEvent *bufferEvent, uint8_t typeID);
void commandParse(char *commandBuffer);
uint8_t disableStructEEPROM(uint8_t typeID, uint8_t number);


extern uint8_t mymac[6];
extern uint8_t myip[4]; 
extern char password[10];

// listen port for www
#define MYWWWPORT 80
#define MYUDPPORT 1200

#define BUFFER_SIZE 500
extern uint8_t buf[BUFFER_SIZE+1];
//extern char gStrbuf[25];
