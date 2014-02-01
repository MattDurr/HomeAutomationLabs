//----USB Serial---
#include "usb_serial.h"

//-----LCD------
#include "stlcd.h"
#include "lcdMenu.h"

//------Gen-------
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "HALFinal.h"
#include <avr/eeprom.h>

//------WEB-------
#include "ip_arp_udp_tcp.h"
#include "enc28j60.h"
#include "avr_compat.h"
#include "net.h"
#include "websrv_help_functions.h"
#include <ctype.h>
#include "webPages.h"

//------Clock/Date-----
#include "timeconversions.h"


//---------ENC Global Vars---------

uint8_t mymac[] = {0x54,0x55,0x58,0x10,0x01,0x29};
uint8_t myip[] = {192,168,160,104};
uint8_t buf[BUFFER_SIZE+1];
char lcd_update_flag = 1;//use this to keep track if the LCD needs to be updated.
uint8_t button_state = 0; //buffer used to track the current state of the buttons
uint8_t button_state_input = 0;
uint8_t drawclock = 0;

char debug;
char butt_debug;

char serialCommandBuffer[50];
//char *serialBufferHead;
char *serialBufferTail = &serialCommandBuffer[0]; //init to first char of buffer
//char *serialBufferIndex = &serialCommandBuffer[0]; //init to first char of buffer

uint8_t first_run_flag = 1;
int timer1 = 0; //interrupt driven, counts up to 500
char flag_500mills = 0;//flag used for refreshing the menu
char flag_250mills = 0;//flag used for refreshing user input


//-----Clock/Date Global Vars----

int clock_mills = 0;
uint32_t clock_unix_time = 0; //used to keep track of time in seconds.  This is used to calculate everything else.
char clock[] = {'0','0',':','0','0',':','0','0','\0'}; //init clock char array
uint8_t newMinute;
char day[] = {'T','h','u',' ','1','9','7','0','-','0','1','-','0','1','\0'}; //init date array
char isLeapYear = 0; //keep track if this year is a leapyear is refreshed in main whenever year is changed
char isDaylightSavings = 0;
char timezone[] = {'E','S','T','\0'};

struct calendarEvent bufferEvent;
struct networkConfigStruct eepromIPConfig;
struct led_struct lcd_led;



int main(void){

	//----INIT AREA-----
	spiInit();
	timer_init();
	lcd_init();
	button_init();
	relay_init();
	io_init();
	usb_init();
	enc28j60Init(mymac);
	enc28j60PhyWrite(PHLCON,0x476);
	init_udp_or_www_server(mymac,myip);
    www_server_port(MYWWWPORT);
	menuInit();
	newMinute = 0;
	serialCommandBuffer[49] = 0; //add null to last one
	gmtime(clock_unix_time, day, clock);
	
	//-------------ENC28J60------------

	uint16_t dat_p;
	sei(); //  Enable global interrupts 


	//-----First run stuff----

	if(first_run_flag==1){

		first_run_flag = 0;
	}
	
// 	extern uint8_t au8FontCourrier8x12;
// 	char bigNum[12];
// 	char x = 0;
// 	for (uint8_t i = 0; i<12; i++ ) {
// 		bigNum[x] = pgm_read_byte((int)au8FontCourrier8x12+(17+i));
// 		x++;
// 	}
// 	drawbitmap(lcd_buffer, (6*11), (8*2), bigNum, 8, 12, 1);
	

	while(1){

		//Clock Stuff

		if(timer1 > 199){
	   		flag_500mills = 1;
			timer1 = 0;
		}

		else if (clock_mills > 999){
			clock_unix_time++;
			clock_mills = 0;
			newMinute++;
		}
	
		else if (newMinute >59){
			gmtime(clock_unix_time, day, clock);
			checkEvents();
			newMinute = 0;
			lcd_update_flag = 1;			
		}
		
		else ;
			

		//------------------------Input Stuff------------------------
		butt_state();
	
		//-------------------------LCD Stuff---------------------
		
		if(lcd_led.update_flag == 1){

			LED_RED = lcd_led.red;
			LED_GREEN = lcd_led.green;
			LED_BLUE = lcd_led.blue;
			st7565_set_brightness(lcd_led.contrast);
			lcd_led.update_flag = 0;

		}
		
		else;

		if (flag_500mills) {
			
			menu_track();
			flag_500mills = 0;
		
		}
		else ;
				
		if (lcd_update_flag){ //check to see if flag is set.

			lcd_update_flag = 0; //reset flag
			cli();
			lcd_refresh(lcd_buffer);
			sei();
		}
				

		//-------------------USB Serial-------------------------

		// wait for the user to run their terminal emulator program
		// which sets DTR to indicate it is ready to receive.
		
		else if(usb_serial_available()){
			*serialBufferTail = usb_serial_getchar();
			if (*serialBufferTail == 10){ //end of command
				commandParse(serialCommandBuffer);
				serialBufferTail = &serialCommandBuffer[0];
			}
			else{
				serialBufferTail++;
				if(serialBufferTail == &serialCommandBuffer[49]){
					//TODO - Error end of buffer
				}
				else;
			}				
			
		}

		//-----------------------ENC28J60-----------------------
					
        // read packet, handle ping and wait for a tcp packet:
        dat_p=packetloop_arp_icmp_tcp(buf,enc28j60PacketReceive(BUFFER_SIZE, buf));

        // dat_p will be unequal to zero if there is a valid  http get
        if(dat_p==0){
                // no http request
                continue;
        }
        // tcp port 80 begin
        if (strncmp("GET ",(char *)&(buf[dat_p]),4)!=0){
			// head, post and other methods:
			dat_p=http200ok();
			dat_p=fill_tcp_data_p(buf,dat_p,PSTR("<h1>200 OK</h1>"));
			goto SENDTCP;
        }
        // just one web page in the "root directory" of the web server
		if (strncmp("/ ",(char *)&(buf[dat_p+4]),2)==0){
			dat_p=landingPageHTML(buf);
			goto SENDTCP;
        }
		
        else if (strncmp("/?",(char *)&(buf[dat_p+4]),2)==0){
			char * urlCommand;
			urlCommand = strstr ((char *)&(buf[dat_p+4]),"?RU");
			
			if(urlCommand){
				urlCommand = strtok (urlCommand+3," &=");
			
				if(strcmp(urlCommand, "RL1") == 0){
					urlCommand = strtok (0, " &=");
					if(strcmp(urlCommand, "ON") == 0) RELAY1_SET();
					else if(strcmp(urlCommand, "TGL") == 0) RELAY1_TOGGLE();
					else if(strcmp(urlCommand, "OFF") == 0) RELAY1_CLEAR();
					else;
					urlCommand = strtok (0, " &=");//move on to next part of command
				}
			
				if(strcmp(urlCommand, "RL2") == 0){
					urlCommand = strtok (0, " &=");
					if(strcmp(urlCommand, "ON") == 0) RELAY2_SET();
					else if(strcmp(urlCommand, "TGL") == 0) RELAY2_TOGGLE();
					else if(strcmp(urlCommand, "OFF") == 0) RELAY2_CLEAR();
					else;
					urlCommand = strtok (0, " &=");//move on to next part of command
				}
			
				if(strcmp(urlCommand, "RL3") == 0){
					urlCommand = strtok (0, " &=");
					if(strcmp(urlCommand, "ON") == 0) RELAY3_SET();
					else if(strcmp(urlCommand, "TGL") == 0) RELAY3_TOGGLE();
					else if(strcmp(urlCommand, "OFF") == 0) RELAY3_CLEAR();
					else;
					urlCommand = strtok (0, " &=");//move on to next part of command
				}
			
				if(strcmp(urlCommand, "RL4") == 0){
					urlCommand = strtok (0, " &=");
					if(strcmp(urlCommand, "ON") == 0) RELAY4_SET();
					else if(strcmp(urlCommand, "TGL") == 0) RELAY4_TOGGLE();
					else if(strcmp(urlCommand, "OFF") == 0) RELAY4_CLEAR();
					else;
					urlCommand = strtok (0, " &=");//move on to next part of command
				}
			}				
			
			dat_p=landingPageHTML(buf);
			goto SENDTCP;
        }
		
		else if (strncmp("/ts",(char *)&(buf[dat_p+4]),3)==0){ // change clock
			
			char * pch;
			char * urlTime;
			pch = strstr ((char *)&(buf[dat_p+4]),"?tv");
			urlTime = strtok (pch," ?=");
			usb_serial_write_p(PSTR("Receiving Time URL...")); 
			urlTime = strtok (0," ?=");
			clock_unix_time = atol(urlTime);
			gmtime(clock_unix_time, day, clock);
			lcd_update_flag = 1;
			dat_p=print_webpage_setclock();
			usb_serial_write_p(PSTR("Done\r\n"));
            goto SENDTCP;

        }
		
		else if (strncmp("/tc ",(char *)&(buf[dat_p+4]),4)==0){
                dat_p=print_webpage_setclock();
                goto SENDTCP;
        }
		
		else if (strncmp("/sc ",(char *)&(buf[dat_p+4]),4)==0){
                dat_p=print_webpage_schedule();
                goto SENDTCP;
        }
		else{
                dat_p=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n<h1>401 Unauthorized</h1>"));
                goto SENDTCP;
        }
SENDTCP:
        www_server_reply(buf,dat_p); // send web page data
        // tcp port 80 end

	}//end while(1)

}//end main()



void lcd_refresh( unsigned char *buffer){

	//Put stuff for LCD in here
	//This refreshes as fast a possible

	clear_buffer(lcd_buffer);

	drawMenu();

	write_buffer(lcd_buffer); //write the boot screen
	
	//debug++;

}//end lcd_refresh

void commandParse(char *commandBuffer){ //look at incoming strings here.
	char *ptr = strstr (commandBuffer,"AT");
	if(ptr){
		char* pch;
		ptr+=2;//Look at what's after the AT command
		usb_serial_write_p(PSTR("AT\r\n"));
		pch = strtok(ptr," []<>;"); //look at first part of command, will be one of: W0, W1, WI, WP, SR, SW, TS, TR, IR, IS, STATUS
		
		if(strcmp(pch, "TR") == 0){ //Time Read
			char timeBuff[20];
			ltoa(clock_unix_time, timeBuff, 10);
			usb_serial_write_p(PSTR("Time: "));
			usb_serial_write(timeBuff, strlen(timeBuff));
			usb_serial_write_p(PSTR("\n\r"));
			return;
		}//END Time Read
		
		else if(strcmp(pch, "TS") == 0){ //Time Set
			pch = strtok (0, " []<>;");
			usb_serial_write_p(PSTR("Setting Time.."));
			clock_unix_time = atol(pch);
			char buff[10];
			extern TIMEZONECHANGE;
			extern DLS;
			pch = strtok (0, " []<>;");
			
			if(strcmp(pch, "TZ") == 0){
				pch = strtok (0, " []<>;");
				TIMEZONECHANGE =  atoi(pch);
				pch = strtok (0, " []<>;");
			}
			
			if(strcmp(pch, "DLS") == 0){
				pch = strtok (0, " []<>;");
				DLS =  atoi(pch);
			}
			gmtime(clock_unix_time, day, clock);
			lcd_update_flag = 1;
			usb_serial_write_p(PSTR("Done\n\r"));
			return;
		}//END Time Set
		
		else if(strcmp(pch, "IR") == 0){ //IO Read
			
			usb_serial_write_p(PSTR("Relay1:"));
			if(RELAY1_READ()) usb_serial_write_p(PSTR("ON\n\r"));
			else usb_serial_write_p(PSTR("OFF\n\r"));
			
			usb_serial_write_p(PSTR("Relay2:"));
			if(RELAY2_READ()) usb_serial_write_p(PSTR("ON\n\r"));
			else usb_serial_write_p(PSTR("OFF\n\r"));
			
			usb_serial_write_p(PSTR("Relay3:"));
			if(RELAY3_READ()) usb_serial_write_p(PSTR("ON\n\r"));
			else usb_serial_write_p(PSTR("OFF\n\r"));
			
			usb_serial_write_p(PSTR("Relay4:"));
			if(RELAY4_READ()) usb_serial_write_p(PSTR("ON\n\r"));
			else usb_serial_write_p(PSTR("OFF\n\r"));
			
			//TODO -- READ OTHER IO LATER
			
			return;
		}//END IO Read
		
		else if(strcmp(pch, "IS") == 0){ //IO Set
			pch = strtok (0, " []<>;");
			usb_serial_write_p(PSTR("Setting IO.."));
			
			if(strcmp(pch, "RELAY1") == 0){
				pch = strtok (0, " []<>;");
				if(strcmp(pch, "ON") == 0) RELAY1_SET();
				else if(strcmp(pch, "TOGGLE") == 0) RELAY1_TOGGLE();
				else if(strcmp(pch, "OFF") == 0) RELAY1_CLEAR();
				else;
				pch = strtok (0, " []<>;");//move on to next part of command
			}
			if(strcmp(pch, "RELAY2") == 0){
				pch = strtok (0, " []<>;");
				if(strcmp(pch, "ON") == 0) RELAY2_SET();
				else if(strcmp(pch, "TOGGLE") == 0) RELAY2_TOGGLE();
				else if(strcmp(pch, "OFF") == 0) RELAY2_CLEAR();
				else;
				pch = strtok (0, " []<>;");//move on to next part of command
			}
			if(strcmp(pch, "RELAY3") == 0){
				pch = strtok (0, " []<>;");
				if(strcmp(pch, "ON") == 0) RELAY3_SET();
				else if(strcmp(pch, "TOGGLE") == 0) RELAY3_TOGGLE();
				else if(strcmp(pch, "OFF") == 0) RELAY3_CLEAR();
				else;
				pch = strtok (0, " []<>;");//move on to next part of command
			}
			if(strcmp(pch, "RELAY4") == 0){
				pch = strtok (0, " []<>;");
				if(strcmp(pch, "ON") == 0) RELAY4_SET();
				else if(strcmp(pch, "TOGGLE") == 0) RELAY4_TOGGLE();
				else if(strcmp(pch, "OFF") == 0) RELAY4_CLEAR();
				else;
				pch = strtok (0, " []<>;");//move on to next part of command
			}
			
			usb_serial_write_p(PSTR("Done\n\r"));
			return;
		}//END IO set
		
		else if(strcmp(pch, "STATUS") == 0){//Echo status
			usb_serial_write_p(PSTR("Link Status: "));
			usb_serial_putchar(enc28j60linkup() + 48);
			usb_serial_write_p(PSTR("\n\r"));
			return;
		}//End Echo status
		
		else if(strcmp(pch, "W0") == 0){//Disable Web
			enc28j60DisableBroadcast();
			usb_serial_write_p(PSTR("Web Disabled\n\r"));
			return;
		}//End Disable Web
		
		else if(strcmp(pch, "W1") == 0){//Enable Web
			enc28j60EnableBroadcast();
			usb_serial_write_p(PSTR("Web Enabled\n\r"));
			return;
		}//End Enable Web
		
		else if(strcmp(pch, "SW") == 0){//Schedule Write
			pch = strtok (0, " []<>;");
			
			if(strcmp(pch, "&U") == 0){//We want to update one
				pch = strtok (0, " []<>;");
				
				disableStructEEPROM(3, atoi(pch));
				
				//This is where I will have some way to identify what one we are updating, probably the type and the start time
			}
			
			else{//Create a new one
				/*
				* Syntax is Day of week, startData, duration, relay info
				*
				*
				* uint8_t DayOfWeek; //MSB/7th = NULL, 6th bit = Sat, 5th = Mon ... 0th = Sun
				* uint16_t StartData; //data broken into: 15th bit == NULL; 14th-11th == month; 10th-0th == minute of day
				* uint16_t Duration; //how long in minutes event lasts
				* uint8_t Relay; //byte is broken up into two bits per relay: bits 7&6 = RL1 .. 1&0 = RL4
				*
				*/
				usb_serial_write_p(PSTR("Creating new event"));
				
				if(pch == 0){ usb_serial_write_p(PSTR("Error:NoDay")); return;}
				else;
				bufferEvent.DayOfWeek = atoi(pch);

				pch = strtok (0, " []<>;");//Go to next part, startData
				
				if(pch == 0){ usb_serial_write_p(PSTR("Error:NoSta")); return;}
				else;
				bufferEvent.startData = atoi(pch); //date is in uint16_t form, so two bytes
				
				pch = strtok (0, " []<>;");//Go to next part, Duration
				
				if(pch == 0){ usb_serial_write_p(PSTR("Error:NoDur")); return;}
				else;
				bufferEvent.duration = atoi(pch); //date is in uint16_t form, so two bytes
				
				pch = strtok (0, " []<>;");//Go to next part, Relay
				
				if(pch == 0){ usb_serial_write_p(PSTR("Error:NoRel")); return;}
				else;
				bufferEvent.relay = atoi(pch);//date is in uint8_t form, so only one byte
				
				usb_serial_write_p(PSTR("Code:"));
				usb_serial_putchar(writeCalanderStructEEPROM(&bufferEvent, 3)+48);	
				usb_serial_write_p(PSTR("\n\r"));		
				
			}				
			
			
		}//End Schedule Write
		
		else if(strcmp(pch, "SR") == 0){//Schedule Read
			pch = strtok (0, " []<>;");
			char tmpArray[10];
			
			usb_serial_write_p(PSTR("Code:"));
			usb_serial_putchar(readCalanderStructEEPROM(&bufferEvent, 3, atoi(pch))+48);
			usb_serial_write_p(PSTR("\n\r"));
			usb_serial_write_p(PSTR("Day:"));
			itoa(bufferEvent.DayOfWeek, tmpArray, 10);
			usb_serial_write(tmpArray, strlen(tmpArray));
			//usb_serial_putchar(bufferEvent.DayOfWeek);
			usb_serial_write_p(PSTR("\n\r"));
			usb_serial_write_p(PSTR("StartData:"));
			itoa(bufferEvent.startData, tmpArray, 10);
			usb_serial_write(tmpArray, strlen(tmpArray));
			//usb_serial_putchar((char)(bufferEvent.startData >> 8));
			//usb_serial_putchar((char)(bufferEvent.startData & 255));
			usb_serial_write_p(PSTR("\n\r"));
			usb_serial_write_p(PSTR("Duration:"));
			itoa(bufferEvent.duration, tmpArray, 10);
			usb_serial_write(tmpArray, strlen(tmpArray));
			//usb_serial_putchar((char)(bufferEvent.duration >> 8));
			//usb_serial_putchar((char)(bufferEvent.duration & 255));
			usb_serial_write_p(PSTR("\n\r"));
			usb_serial_write_p(PSTR("Relay:"));
			itoa(bufferEvent.relay, tmpArray, 10);
			usb_serial_write(tmpArray, strlen(tmpArray));
			//usb_serial_putchar(bufferEvent.relay);
			usb_serial_write_p(PSTR("\n\r"));
			
		}//End Schedule Read
		
		else if(strcmp(pch, "ER") == 0){//Read EEPROM
			pch = strtok (0, " []<>;");
			usb_serial_putchar(eeprom_read_byte(atoi(pch)));
			usb_serial_write_p(PSTR("\n\r"));
			
		}//End Read EEPROM
		
		else if(strcmp(pch, "EW") == 0){//Write EEPROM
			pch = strtok (0, " []<>;");
			
			char add = atoi(pch);
			pch = strtok (0, " []<>;");
			char val = atoi(pch);
			eeprom_write_byte(add, val);
			
			usb_serial_putchar(eeprom_read_byte(add));
			usb_serial_write_p(PSTR("\n\r"));
			
		}//End Read EEPROM		
		
		else if(strcmp(pch, "Hello") == 0){
			usb_serial_write_p(PSTR("Hello Host"));
		}			
		
		else return;
		
	}//end if(ptr)
}//end commandParse()

void butt_state(){

	button_state = ( (RAW_BUTT_UP << 4) | (RAW_BUTT_DOWN << 3) | (RAW_BUTT_LEFT << 2) | (RAW_BUTT_RIGHT << 1) | (RAW_BUTT_SELECT << 0 ) );

	button_state_input = ((PINF >> 7) & 1);

}


	
//------------ IO and RELAYS ---------------

void relay_init(void){
	//will impiment load from eeprom later
	//For now hard-coded
	
	RELAY1_DDR |= _BV(RELAY1);//set relay1 to output
	RELAY2_DDR |= _BV(RELAY2);//set relay2 to output
	RELAY3_DDR |= _BV(RELAY3);//set relay3 to output
	RELAY4_DDR |= _BV(RELAY4);//set relay4 to output
	
	RELAY1_PORT &= ~(_BV(RELAY1));//Set relay1 output low
	RELAY2_PORT &= ~(_BV(RELAY2));//Set relay2 output low
	RELAY3_PORT &= ~(_BV(RELAY3));//Set relay3 output low
	RELAY4_PORT &= ~(_BV(RELAY4));//Set relay4 output low

	PORTD &= ~( _BV(7) | _BV(6) | _BV(4) ); //Set R1, R2, and R3 low
	PORTF &= ~( _BV(6) ); //set R4 low

	
}

void io_init(void){ //allow incoming parameters to set init direction and if pull-up/state
	
	//need to set way of setting to adc or not from code later

	DDRF &= ~( _BV(7) ); //Sens1 on port F7 to input, can use adc
	DDRB &= ~( _BV(6) ); //Sens2 on port B6 to input, can use adc

	DDRD &= ~( _BV(5) ); //IO1 on port D5 to input

}

	//----------------LCD ---------------------

void lcd_init(void){

	DDRC |= (1 << 7) | (1 << 6); //Set LCD LED to output
	DDRD |= (1 << 0); //Set LCD LED to output

	TCCR0A = ( _BV(WGM10) | _BV(WGM00) | _BV(COM0B1) ); //Timer0 ChA Fast PWM setup
	TCCR0B = ( _BV(CS01) ); 

	TCCR3A = ( _BV(COM3A1) | _BV(COM3B1) | _BV(COM3C0) | _BV(WGM30) );//Timer3 ChB Fast PWM setup
	TCCR3B = ( _BV(WGM32) | _BV(CS31)); //prescaler of 8

	TCCR4A = ( _BV(COM4A1) | _BV(PWM4A) );//Timer4 ChA Fast PWM setup
	TCCR4B = ( _BV(CS42) );

	lcd_led.red = 0;
	lcd_led.green = 0;
	lcd_led.blue = 0;
	lcd_led.contrast = 40;
	lcd_led.update_flag = 1;

	setup();
	st7565_set_brightness(40);
	write_buffer(lcd_buffer); //write the boot screen
	_delay_ms(2000); //hold the boot screen for 2s //REPLACE WITH TIMER DELAY!!
	clear_buffer(lcd_buffer);
	clear_screen();
}


	//----------------Buttons--------------

void button_init(void){

	DDRF &= ~( (1 << 0) | (1<<1) | (1<<4) | (1<<5) ); //Set buttons as input
	DDRE &= ~(1 << 6); //Select button as input 

	PORTF |= ( (1 << 0) | (1<<1) | (1<<4) | (1<<5) ); //Enable pull-up resistors for buttons 
	PORTE |= (1 << 6); //Select button 
}

	//------------Clock Timer ---------------

void timer_init(void){

	TCCR1B = ( _BV(CS11) | _BV(CS10) | _BV(WGM12) ); //Timer1 CTC Mode, prescaler of 64
	OCR1AL = 249; //set timer to reset at 250
	TIMSK1 = _BV(OCIE1A); //enable CTC Channel A interrupt

}


//------------Timer Interrupts -----------------

ISR(TIMER1_COMPA_vect)
{
	clock_mills++;
	timer1++;
   	
} 

//-------------EEPROM Functions----------------

uint8_t readCalanderStructEEPROM(struct calendarEvent *bufferEvent, uint8_t typeID, uint8_t number){ //return codes: 0 = success, 1 = 
	//number means the function will return the numberth calender event it finds, outside function will handle telling if it is the correct event
	
	/*	EEPROM structure is :
	* 	1st byte: Table length in 16-bit words
	*	2nd byte: Table ID, used to determine what's in the program; IDs are: 1=Gen Config, 2=Network Config, 3=Schedule etc
	*	3rd byte: Table Checksum
	*	4th byte: First byte of data
	*	Nth byte: Last byte of data
	*/
	
	typeID |= _BV(7); //we only want to read enabled tables

	uint8_t tableAddress = 0; //address for current table we are looking at
	uint16_t tableIndex = 0; //index for how many tables we've read
	uint8_t indexTableType = 0; //index of how many of the correct type of tables we've read
	uint16_t currentTableLength; //length of table we're are reading in bytes
	uint8_t currentTableID = 0; //the typeID of the current table we are reading
	uint8_t currentTableChkSum = 0; //hold checksum of current table
	uint8_t tempChkSum = 0; //hold temp checksum
	
	bufferEvent->DayOfWeek = 0;
	bufferEvent->duration = 0;
	bufferEvent->relay = 0;
	bufferEvent->startData = 0;
	
	while (indexTableType <= number){ //keep going until we find the the numberth one, or stop after that

		currentTableLength = eeprom_read_byte ((uint8_t *) tableAddress); //load the length of the current table we are looking at in bytes

		if(currentTableLength != 0xFF && currentTableLength > 3 ){ //check to see if the table we are reading is valid, must be less than FF and greater than 3, which is the minimum for a table(with no body)
		
			currentTableID = eeprom_read_byte ((uint8_t *) tableAddress+1); //read the typeID of that table

			if(currentTableID == typeID){ //we're looking at the right table type
				
				if(indexTableType == number){ //we are at the table we are looking for
					
					tempChkSum = eeprom_read_byte ((uint8_t *) tableAddress+2);

					eeprom_read_block ((void*)bufferEvent , (const void*) tableAddress+3, sizeof(*bufferEvent) );

					uint8_t *byteOfStruct = bufferEvent;

					for( uint8_t i = 0; i < sizeof(*bufferEvent); i++){
						tempChkSum -= byteOfStruct[i];		
					} 
					if(tempChkSum == 0){ //Correct checksum
						return 1; //success
					}
					else{
						currentTableID &= ~(_BV(7));//mark as disabled by clearing that bit
						eeprom_write_byte(tableAddress+1, currentTableID);
						return 4; //error: found item but failed checksum test				
					}			
				}
				else {//right type but not the table we are looking for, move onto the next one
					tableAddress += (currentTableLength);
					tableIndex++;
					indexTableType++;
				}
			}
			else {//wrong table type, lets try with the next one
				tableAddress += currentTableLength;
				tableIndex++;
			}
		}//end if
		else if (tableIndex > 0) return 2; //There isn't that many tables of that type in eeprom
		else return 3; //eeprom has no usable data in it (or first byte is corrupt)
	}//end loop	
	return 0; //error: went through loop and didn't find error or success
}//End readCalanderStructEEPROM()


uint8_t writeCalanderStructEEPROM(struct calendarEvent *bufferEvent, uint8_t typeID){ //return codes: 

	/*	EEPROM structure is :
	* 	1st byte: Table length in 16-bit words
	*	2nd byte: Table ID, used to determine what's in the program IDs are: 1=Gen Config, 2=Network Config, 3=Schedule etc
	*	3rd byte: Table Checksum
	*	4th byte: First byte of data
	*	Nth byte: Last byte of data
	*/
	
	//typeID |= (1 << 7); //we only want to read enabled tables

	uint8_t tableAddress = 0; //address for current table we are looking at
	uint16_t tableIndex = 0; //index for how many tables we've read
	uint8_t indexTableType = 0; //index of how many of the correct type of tables we've read
	uint16_t currentTableLength; //length of table we're are reading in bytes (actual number is stored in 16-bit words, multiply by two to convert bytes)
	uint8_t currentTableID = 0; //the typeID of the current table we are reading
	uint8_t currentTableChkSum = 0; //hold checksum of current table
	uint8_t tempChkSum = 0; //hold temp checksum
	
	while (1){//keep going until we find an empty spot
		currentTableLength = eeprom_read_byte ((uint8_t *) tableAddress); //load the length of the current table we are looking at in bytes (multiply function result by two to get bytes
		if(currentTableLength != 0xFF && currentTableLength > 3 ){ //check to see if the table we are reading is valid, must be less than FF and greater than 3, which is the minimum for a table(with no body)
			currentTableID = eeprom_read_byte ((uint8_t *) tableAddress+1); //read the typeID of that table
			if(currentTableID == typeID){ //we're looking at the right table type, and it is disabled (we are going to reuse it)
				eeprom_write_byte (tableAddress , sizeof(*bufferEvent)+3); //Writing the first byte that contains the size of the table we are creating. (the plus 3 is for this byte, ID byte, and checksum byte)
				eeprom_write_byte (tableAddress+1 , typeID | _BV(7)); //Add ID byte, mark it active with 7th bit == 1
			
				//Calculate checksum for even we were given
				uint8_t *byteOfStruct = bufferEvent;
				for( uint8_t i = 0; i < sizeof(*bufferEvent); i++){
					tempChkSum += byteOfStruct[i];		
				}
		
				eeprom_write_byte (tableAddress+2 , tempChkSum);//write the checksum to the table
				eeprom_write_block (bufferEvent , tableAddress+3 , sizeof(*bufferEvent));//Write the even to eeprom.
				return 2;//Success, reused old table
			}
			else {//wrong table type, or this one is being used, lets try with the next one
				tableAddress += currentTableLength;
				tableIndex++;
			}
		}//end if
		else{//Either at end of tables or no table exists.  Let's make a new one!
			eeprom_write_byte (tableAddress , sizeof(*bufferEvent)+3); //Writing the first byte that contains the size of the table we are creating. (the plus 3 is for this byte, ID byte, and checksum byte)
			eeprom_write_byte (tableAddress+1 , typeID | _BV(7)); //Add ID byte, mark it active with 7th bit == 1
			
			//Calculate checksum for even we were given
			uint8_t *byteOfStruct = bufferEvent;
			for( uint8_t i = 0; i < sizeof(*bufferEvent); i++){
				tempChkSum += byteOfStruct[i];		
			}
		
			eeprom_write_byte (tableAddress+2 , tempChkSum);//write the checksum to the table
			eeprom_write_block (bufferEvent , tableAddress+3 , sizeof(bufferEvent));//Write the even to eeprom.
			return 1;//Success, new table created
		}//end else
	}//end loop	
	return 0; //error: went through loop and didn't find error or success
}//End writeCalanderStructEEPROM()


uint8_t disableStructEEPROM(uint8_t typeID, uint8_t number){ //return codes: 0 = success, 1 = 
	//number means the function will return the numberth calender event it finds, outside function will handle telling if it is the correct event
	
	/*	EEPROM structure is :
	* 	1st byte: Table length in 16-bit words
	*	2nd byte: Table ID, used to determine what's in the program; IDs are: 1=Gen Config, 2=Network Config, 3=Schedule etc
	*	3rd byte: Table Checksum
	*	4th byte: First byte of data
	*	Nth byte: Last byte of data
	*/
	
	typeID |= _BV(7); //we only want to read enabled tables

	uint8_t tableAddress = 0; //address for current table we are looking at
	uint16_t tableIndex = 0; //index for how many tables we've read
	uint8_t indexTableType = 0; //index of how many of the correct type of tables we've read
	uint16_t currentTableLength; //length of table we're are reading in bytes
	uint8_t currentTableID = 0; //the typeID of the current table we are reading
	uint8_t currentTableChkSum = 0; //hold checksum of current table
	uint8_t tempChkSum = 0; //hold temp checksum
	
	while (indexTableType <= number){ //keep going until we find the the numberth one, or stop after that
		currentTableLength = eeprom_read_byte ((uint8_t *) tableAddress); //load the length of the current table we are looking at in bytes
		if(currentTableLength != 0xFF && currentTableLength > 3 ){ //check to see if the table we are reading is valid, must be less than FF and greater than 3, which is the minimum for a table(with no body)
			currentTableID = eeprom_read_byte ((uint8_t *) tableAddress+1); //read the typeID of that table
			if(currentTableID == typeID){ //we're looking at the right table type
				if(indexTableType == number){ //we are at the table we are looking for	
					currentTableID &= ~(_BV(7));//mark as disabled by clearing that bit
					eeprom_write_byte(tableAddress+1, currentTableID);
					return 4; //error: found item but failed checksum test									
				}
				else {//right type but not the table we are looking for, move onto the next one
					tableAddress += (currentTableLength>>2);
					tableIndex++;
					indexTableType++;
				}
			}
			else {//wrong table type, lets try with the next one
				tableAddress += currentTableLength;
				tableIndex++;
			}
		}//end if
		else if (tableIndex > 0) return 2; //There isn't that many tables of that type in eeprom
		else return 3; //eeprom has no usable data in it (or first byte is corrupt)
	}//end loop	
	return 0; //error: went through loop and didn't find error or success
}//End disableStructEEPROM()

//-------------------End EEprom functions-----------------------


//------------------CheckEvents------------------------

void checkEvents(void){
	char functionReturn = 0;
	char todayMask;
	char monthBuffer[2];
	char timeBuffer[2];
	int	i = 0;
	char stringBuffer[10];
	
	//strncpy(monthBuffer, day+9, 2);
	monthBuffer[0] = day[9];
	monthBuffer[1] = day[10];
	strncpy(timeBuffer, clock, 2);
	
	usb_serial_write_p(PSTR("Before:"));
	usb_serial_write(monthBuffer, 2);
	usb_serial_putchar('-')	;
	
	uint8_t thisMonth = atoi(monthBuffer);
	usb_serial_putchar(thisMonth+48);

	uint16_t thisMinute = atoi(timeBuffer) * 60;
	
	strncpy(timeBuffer, clock+3, 2);
	
	thisMinute += atoi(timeBuffer);
	
	if(strstr (day,"Sun")) todayMask=6;
	else if(strstr (day,"Mon")) todayMask=5;
	else if(strstr (day,"Tue")) todayMask=4;
	else if(strstr (day,"Wen")) todayMask=3;
	else if(strstr (day,"Thu")) todayMask=2;
	else if(strstr (day,"Fri")) todayMask=1;
	else if(strstr (day,"Sat")) todayMask=0;
	else;
	
	while (1){
		functionReturn = readCalanderStructEEPROM(&bufferEvent, 3, i);
		usb_serial_write_p(PSTR("Checking for events:\r\n"));
		usb_serial_putchar(functionReturn+48);
		usb_serial_write_p(PSTR("\r\n"));
		if(functionReturn == 2 || functionReturn == 3) return; //exit if there are no more/are no events to read
		
		itoa((bufferEvent.startData>>11)&0b1111, stringBuffer, 10);
		usb_serial_write_p(PSTR("Month: "));
		usb_serial_write(stringBuffer, strlen(stringBuffer));
		usb_serial_write_p(PSTR("vs"));
		usb_serial_putchar(thisMonth+48);
		usb_serial_write_p(PSTR("\r\n"));
		
		if ((bufferEvent.startData>>11)&0b1111 == thisMonth){//The event is for this month
			
			itoa(bufferEvent.DayOfWeek>>todayMask, stringBuffer, 10);
			usb_serial_write_p(PSTR("Day: "));
			usb_serial_write(stringBuffer, strlen(stringBuffer));
			usb_serial_write_p(PSTR("\r\n"));
		
			if((bufferEvent.DayOfWeek>>todayMask)&1){//The event is for today
				if((bufferEvent.startData&2047)<thisMinute){//did the event start
					if((bufferEvent.duration+(bufferEvent.startData&2047)) < thisMinute){//Event is over
						disableStructEEPROM(3, i);
					}
					else if((bufferEvent.duration+(bufferEvent.startData&0b11111111111)) > thisMinute){//Event going on now
						
						if((bufferEvent.relay >> 6) & 3){//Relay1 has something to do
							switch((bufferEvent.relay >> 6) & 3){
								case 1: RELAY1_SET();
									break;
								case 2: RELAY1_CLEAR();
									break;
								case 3: RELAY1_TOGGLE();
									break;
							}
						}
						
						if((bufferEvent.relay >> 4) & 3){//Relay1 has something to do
							switch((bufferEvent.relay >> 4) & 3){
								case 1: RELAY1_SET();
									break;
								case 2: RELAY1_CLEAR();
									break;
								case 3: RELAY1_TOGGLE();
									break;
							}
						}	
						
						if((bufferEvent.relay >> 2) & 3){//Relay1 has something to do
							switch((bufferEvent.relay >> 2) & 3){
								case 1: RELAY1_SET();
									break;
								case 2: RELAY1_CLEAR();
									break;
								case 3: RELAY1_TOGGLE();
									break;
							}
						}
						
						if((bufferEvent.relay >> 0) & 3){//Relay1 has something to do
							switch((bufferEvent.relay >> 0) & 3){
								case 1: RELAY1_SET();
									break;
								case 2: RELAY1_CLEAR();
									break;
								case 3: RELAY1_TOGGLE();
									break;
							}
						}
					}//End event is now					
				}//End this minute			 
			}//End this day
		}//End this month
		
		i++;
		
	}//end loop
	
}

//---------------End Check Event -------------------

//------------ENC Functions--------------------


uint16_t http200ok(void)
{
        return(fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n")));
}


