/*
 * lcdMenu.h
 *
 * Created: 4/10/2012 10:59:13 AM
 *  Author: mlamoureux
 */ 

void menu_track();
void menuInit();
void drawMenu();


#define MAX_LCDMENUITEM (2)

#define LCDMENU_HIDDEN 0
#define LCDMENU_ROOT 1
#define LCDMENU_LCD 2
#define LCDMENU_TIME 3

#define LCD_EXIT 1
#define LCD_SAVE 2
#define LCD_INCREACE 3
#define LCD_DECREACE 4
