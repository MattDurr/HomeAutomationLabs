/*
 * lcdMenu.c
 *
 * Created: 4/10/2012 10:58:55 AM
 *  Author: mlamoureux
 */
#include "lcdMenu.h"
#include "HALFinal.h"
#include "stlcd.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <string.h>

uint8_t LCDMenuStatus; //what menu should be showing
int8_t LCDMenuIndex; //What item in root menu is selected
int8_t LCDMenuLine; //what line of the menu are we on, used in LCD and Time
uint8_t LCDMenuAction; //What menu operation is being done
extern char lcd_update_flag;
extern uint8_t drawclock;
struct led_struct bufferLEDStruct;
extern char day[];
extern char clock[];

char bufferDay[16];

void menuInit(){
	LCDMenuStatus = LCDMENU_HIDDEN;
	LCDMenuIndex = 0;
	LCDMenuLine = 0;
	LCDMenuAction = 0;
	//drawclock = 1;
}

void menu_track(){ //this function keeps track of key presses in the menu systems
	
	if(LCDMenuStatus == LCDMENU_HIDDEN){//menu is hidden
		if (!BUTT_SELECT){ //select pushed, so open root menu
			LCDMenuStatus = LCDMENU_ROOT;
			LCDMenuIndex = 0;//first item in index
			//drawclock = 0;
			lcd_update_flag = 1;
			return;
		}
		
		else;
	}//end 	LCDMENU_HIDDEN	
	
	//--------------------------------
	
	else if (LCDMenuStatus == LCDMENU_ROOT){//menu is root
	
		if (!BUTT_RIGHT){ //Going right
			LCDMenuIndex++;
		
			if (LCDMenuIndex > MAX_LCDMENUITEM){ //check if we need to loop back to zero
				LCDMenuIndex = 0;
			}
			lcd_update_flag = 1;
			
			return;
		}

		else if (!BUTT_LEFT){ //Going left
			LCDMenuIndex--;
		
			if (LCDMenuIndex < 0){//check if we need to loop back to the max value
				LCDMenuIndex = MAX_LCDMENUITEM;
			}
		
			lcd_update_flag = 1;

			return;
		}

		else if (LCDMenuIndex > 0 && !BUTT_UP){ //Hide menu
			LCDMenuStatus = LCDMENU_HIDDEN;
			drawclock = 1;
			lcd_update_flag = 1;

			return;
		}
	
		else if (!BUTT_SELECT){ //selecting a sub-menu
			LCDMenuStatus = LCDMenuIndex+2;//plus two because thats where the codes start for the menus 
			
			if (LCDMenuStatus == LCDMENU_LCD){
				LCDMenuLine = 2;//start on line 2
				bufferLEDStruct = lcd_led;	//copy current state of LED, will be used to undo changed if not saving.
				LCDMenuIndex = 0;
				lcd_update_flag = 1;
				return;
			}
			else if (LCDMenuStatus == LCDMENU_TIME){
				LCDMenuLine = 2;//start on line 2
				LCDMenuIndex = 0;
				lcd_update_flag = 1;
				bufferDay[15] = 0;
				strncpy (bufferDay,day,1);
				return;
			}
			else;
		}
		
		else; //idle
		
	}//end 	LCDMENU_ROOT
	
	//-----------------------------------	
	
	else if (LCDMenuStatus == LCDMENU_LCD){//in the LCD config menu
	
		if (!BUTT_SELECT){//Select
			
			if(LCDMenuIndex == 0 && LCDMenuLine == 7){ //Save		
				//LCDMenuAction = LCD_SAVE;
				LCDMenuStatus = LCDMENU_ROOT;
				lcd_update_flag = 1;
				return;	
			}
			
			else if (LCDMenuIndex == 1 && LCDMenuLine == 7){//Exit		
				//LCDMenuAction = LCD_EXIT;
				lcd_led = bufferLEDStruct;
				LCDMenuStatus = LCDMENU_ROOT;
				lcd_led.update_flag = 1;
				LCDMenuIndex = 0;
				lcd_update_flag = 1;
				return;
			}
			
			else;
		}
		
		else if (!BUTT_LEFT){
			
			if (LCDMenuLine == 2){ //contrast
					if (lcd_led.contrast>0){
						lcd_led.contrast--;
						lcd_led.update_flag = 1;
						lcd_update_flag = 1;	
						return;
					}	
					else return;
			}
			
			else if (LCDMenuLine == 3){ //RED
				if (lcd_led.red>9){
					lcd_led.red-=10;
					lcd_led.update_flag = 1;
					lcd_update_flag = 1;
					return;
				}
				else return;
					
			}
			
			else if (LCDMenuLine == 4){ //Green
				if (lcd_led.green>9){
					lcd_led.green-=10;
					lcd_led.update_flag = 1;
					lcd_update_flag = 1;
					return;
				}	
				else return;				
			}
			
			else if (LCDMenuLine == 5){ //Blue
				if (lcd_led.blue>9){
					lcd_led.blue-=10;
					lcd_led.update_flag = 1;
					lcd_update_flag = 1;
					return;
				}	
				else return;
			}
			
			else if (LCDMenuLine == 7){ //Left
					LCDMenuIndex = 0;
					lcd_update_flag = 1;
					return;
			}
			
			else;
			
		}
		
		else if (!BUTT_RIGHT){
			
			if (LCDMenuLine == 2){ //contrast
					if (lcd_led.contrast<63){
						lcd_led.contrast++;
						lcd_led.update_flag = 1;
						lcd_update_flag = 1;
						return;
					}
					else return;
			}
			
			else if (LCDMenuLine == 3){ //RED
					if (lcd_led.red<243){
						lcd_led.red+=10;
						lcd_led.update_flag = 1;
						lcd_update_flag = 1;
						return;
					}	
					else return;
			}
			
			else if (LCDMenuLine == 4){ //Green
					if (lcd_led.green<243){
						lcd_led.green+=10;
						lcd_led.update_flag = 1;
						lcd_update_flag = 1;
						return;
					}	
					else return;
			}
			
			else if (LCDMenuLine == 5){ //Blue
					if (lcd_led.blue<243){
						lcd_led.blue+=10;
						lcd_led.update_flag = 1;
						lcd_update_flag = 1;
						return;
					}
					else return;
			}
			
			else if (LCDMenuLine == 7){ //Right
					LCDMenuIndex = 1;
					lcd_update_flag = 1;
					return;	
			}
			
			else;
		}
		
		else if (!BUTT_UP){
			LCDMenuLine--;
			LCDMenuIndex = 0;
			
			if (LCDMenuLine<2){
				LCDMenuLine = 7;
			}	
			else if (LCDMenuLine==6){
				LCDMenuLine--;
			}
			else;
			lcd_update_flag = 1;
			return;
		}
		
		else if (!BUTT_DOWN){
			LCDMenuLine++;
			LCDMenuIndex = 0;
			
			if (LCDMenuLine>7){
				LCDMenuLine = 2;
			}
			
			else if (LCDMenuLine==6){
				LCDMenuLine++;
			}
			
			else;
			lcd_update_flag = 1;
			return;
		}
		
		else;
	}//end LCDMENU_LCD
	
	//------------------------------------
	
	else if(LCDMenuStatus == LCDMENU_TIME){
			
		if (!BUTT_SELECT){//Select
			
			if(LCDMenuIndex == 0 && LCDMenuLine == 7){ //Save		
				LCDMenuStatus = LCDMENU_ROOT;
				lcd_update_flag = 1;
				return;	
			}	
			else if (LCDMenuIndex == 1 && LCDMenuLine == 7){//Exit		
				LCDMenuStatus = LCDMENU_ROOT;
				LCDMenuIndex = 0;
				lcd_update_flag = 1;
				return;
			}
			else;
		}
		
		else if (!BUTT_LEFT){
			
			if(LCDMenuIndex>0){
				LCDMenuIndex--;
			}
			
			else if (LCDMenuLine == 7){ //Left
					LCDMenuIndex = 0;
					lcd_update_flag = 1;
					return;
			}
			
			else;
			
		}
		
		else if (!BUTT_RIGHT){
			if(LCDMenuLine>2 && LCDMenuLine<6);
			
			else if (LCDMenuLine == 7){ //Right
					LCDMenuIndex = 1;
					lcd_update_flag = 1;
					return;	
			}
			
			else;
		}
		
		else if (!BUTT_UP){
			LCDMenuLine--;
			LCDMenuIndex = 0;
			
			if (LCDMenuLine<2){
				LCDMenuLine = 7;
			}	
			else if (LCDMenuLine==6){
				LCDMenuLine--;
			}
			else;
			lcd_update_flag = 1;
			return;
		}
		
		else if (!BUTT_DOWN){
			LCDMenuLine++;
			LCDMenuIndex = 0;
			
			if (LCDMenuLine>7){
				LCDMenuLine = 2;
			}
			
			else if (LCDMenuLine==6){
				LCDMenuLine++;
			}
			
			else;
			lcd_update_flag = 1;
			return;
		}
		
		else;
	}//end LCDMENU_TIME

	else;			
}//end menu_track()


void drawMenu(){
	
	if (LCDMenuStatus == LCDMENU_LCD){
		
		char valueBuffer[4] = {0,0,0,0};
		uint8_t dummy;
		
		drawstring_P(lcd_buffer, (6*4), 0, PSTR("LCD Config"));
		
		drawstring_P(lcd_buffer, (6*2), 2, PSTR("Contrast:"));
		dummy = lcd_led.contrast;
		valueBuffer[0] = (dummy/100) + 48;
		valueBuffer[1] = ((dummy/10)%10) + 48;
		valueBuffer[2] = (dummy%10) + 48;
		drawstring(lcd_buffer, (6*12), 2, valueBuffer);
		
		drawstring_P(lcd_buffer, (6*2), 3, PSTR("Red:"));
		dummy = lcd_led.red;
		valueBuffer[0] = (dummy/100) + 48;
		valueBuffer[1] = ((dummy/10)%10) + 48;
		valueBuffer[2] = (dummy%10) + 48;
		drawstring(lcd_buffer, (6*12), 3, valueBuffer);
		
		drawstring_P(lcd_buffer, (6*2), 4, PSTR("Green:"));
		dummy = lcd_led.green;
		valueBuffer[0] = (dummy/100) + 48;
		valueBuffer[1] = ((dummy/10)%10) + 48;
		valueBuffer[2] = (dummy%10) + 48;
		drawstring(lcd_buffer, (6*12), 4, valueBuffer);
		
		drawstring_P(lcd_buffer, (6*2), 5, PSTR("Blue:"));
		dummy = lcd_led.blue;
		valueBuffer[0] = (dummy/100) + 48;
		valueBuffer[1] = ((dummy/10)%10) + 48;
		valueBuffer[2] = (dummy%10) + 48;
		drawstring(lcd_buffer, (6*12), 5, valueBuffer);		
		
		drawstring_P(lcd_buffer, (6*2), 7, PSTR("SAVE"));
		
		drawstring_P(lcd_buffer, (6*8), 7, PSTR("EXIT"));
		
		drawchar(lcd_buffer, 6*(1+LCDMenuIndex*6), LCDMenuLine, 16);
		
		drawrect(lcd_buffer, 0, 0, 128, 64, 1);
		
		return;
			
	}//end LCDMENU_LCD
	
	else if (LCDMenuStatus == LCDMENU_ROOT){
		
		drawline(lcd_buffer, 0, 9, 128, 9, 1);
		
		drawstring_P(lcd_buffer, (6*1), 0, PSTR("LED|"));
		
		drawstring_P(lcd_buffer, (6*6), 0, PSTR("Time|"));
		
		if (LCDMenuIndex == 0){//highlight LED menu
			invertrect(lcd_buffer, (6*1), 0, (6*3), 8);
		}
		
		else if (LCDMenuIndex == 1){//highlight LED menu
			invertrect(lcd_buffer, (6*6), 0, (6*4), 8);
		}
		
		else;
		
		drawstring_P(lcd_buffer, 0, 3, PSTR("Time:"));
		for(uint8_t i = 0; i < 5 ; i++){
			drawchar(lcd_buffer, 6*(i+5), 3, clock[i]);
		}
		
	}//end LCDMENU_ROOT
	
	else if(LCDMenuStatus == LCDMENU_TIME){
		
		drawstring_P(lcd_buffer, (6*4), 0, PSTR("Time Config"));
		
		drawstring_P(lcd_buffer, (6*2), 2, PSTR("Time:"));
		drawchar(lcd_buffer, (6*15), 2, clock[0]);
		drawchar(lcd_buffer, (6*16), 2, clock[1]);
		drawchar(lcd_buffer, (6*17), 2, clock[2]);
		drawchar(lcd_buffer, (6*18), 2, clock[3]);
		drawchar(lcd_buffer, (6*19), 2, clock[4]);
		
		drawstring_P(lcd_buffer, (6*2), 3, PSTR("DLS:"));
		drawstring_P(lcd_buffer, (6*14), 3, PSTR("ON/OFF"));
		
		drawstring_P(lcd_buffer, (6*2), 4, PSTR("Month/Day:"));
		drawchar(lcd_buffer, (6*15), 4, day[9]);
		drawchar(lcd_buffer, (6*16), 4, day[10]);
		drawchar(lcd_buffer, (6*17), 4, '/');
		drawchar(lcd_buffer, (6*18), 4, day[12]);
		drawchar(lcd_buffer, (6*19), 4, day[13]);
		
		drawstring_P(lcd_buffer, (6*2), 5, PSTR("Year:"));
		drawchar(lcd_buffer, (6*16), 5, day[4]);
		drawchar(lcd_buffer, (6*17), 5, day[5]);
		drawchar(lcd_buffer, (6*18), 5, day[6]);
		drawchar(lcd_buffer, (6*19), 5, day[7]);
		
		drawstring_P(lcd_buffer, (6*5), 7, PSTR("SAVE"));
		
		drawstring_P(lcd_buffer, (6*12), 7, PSTR("EXIT"));
		
		if(LCDMenuIndex < 3){
			if(LCDMenuLine == 7) drawchar(lcd_buffer, 6*(4+LCDMenuIndex*7), LCDMenuLine, 16);
			else drawchar(lcd_buffer, 6*1, LCDMenuLine, 16);
		}			
		
		else if(LCDMenuIndex > 2){ //means we're editing a thing
			drawchar(lcd_buffer, 6*1, LCDMenuLine, 16);
		}
		
		drawrect(lcd_buffer, 0, 0, 128, 64, 1);
		
		return;	
		
	}//end LCDMENU_TIME
	
	else if(LCDMenuStatus == LCDMENU_HIDDEN){ //When we have no active menu and am just idle
		drawstring_P(lcd_buffer, 0, 3, PSTR("Time:"));
		for(uint8_t i = 0; i < 5 ; i++){
			drawchar(lcd_buffer, 6*(i+5), 3, clock[i]);
		}
	}// End LCDMENU_HIDDEN
	
	else;
}//end drawmenu()