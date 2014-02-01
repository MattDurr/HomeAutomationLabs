// answer HTTP/1.0 301 Moved Permanently\r\nLocation: .....\r\n\r\n
// to redirect
// type =0  : http://tuxgraphics.org/c.ico    favicon.ico file
// type =1  : /password/
#include "ip_arp_udp_tcp.h"
#include "enc28j60.h"
#include "avr_compat.h"
#include "net.h"
#include "websrv_help_functions.h"
#include <ctype.h>
#include "webPages.h"
#include "HALFinal.h"
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "usb_serial.h"



uint16_t landingPageHTML(uint8_t *buf){

	uint16_t plen;
	extern uint32_t clock_unix_time;
	extern char clock[];
	extern char day[];
	char tempTimeString[20];
	
	plen=http200ok();
	//plen=print_line_mobile_webpage(plen);
    plen=fill_tcp_data_p(buf,plen,PSTR("<a href=/>[home]</a>\n"));
	plen=fill_tcp_data_p(buf,plen,PSTR("<a href=/tc>[Time]</a>\n"));
	plen=fill_tcp_data_p(buf,plen,PSTR("<a href=/sc>[Schedule]</a>\n"));
	plen=fill_tcp_data_p(buf,plen,PSTR("<h3>Welcome to the HAL site</h3>\nCurrent Time:\nUTC: "));
	
	ltoa(clock_unix_time,tempTimeString,10); // convert long to string
    plen=fill_tcp_data(buf,plen,tempTimeString);
	
	plen=fill_tcp_data_p(buf,plen,PSTR("<br>24hr: "));
	strcpy (tempTimeString,clock);
	plen=fill_tcp_data(buf,plen,tempTimeString);
	
	plen=fill_tcp_data_p(buf,plen,PSTR("<br>Date: "));
	strcpy (tempTimeString,day);
	plen=fill_tcp_data(buf,plen,tempTimeString);
	
	plen=fill_tcp_data_p(buf,plen,PSTR("\n\n<h3>Relay States:</h3>\n<ul type=\"disc\"><li>Relay 1: "));
	
	if(RELAY1_READ()) plen=fill_tcp_data_p(buf,plen,PSTR("<font color=#00FF00>ON</font>  <a href=\"/?RU&RL1=TGL\" class=\"button\">Toggle</a>"));
	else plen=fill_tcp_data_p(buf,plen,PSTR("OFF  <a href=\"/?RU&RL1=TGL\">Toggle</a>"));
	
	plen=fill_tcp_data_p(buf,plen,PSTR("</li><li>Relay 2: "));
	
	if(RELAY2_READ()) plen=fill_tcp_data_p(buf,plen,PSTR("<font color=#00FF00>ON</font>&nbsp;<a href=\"/?RU&RL2=TGL\" class=\"button\">Toggle</a>"));
	else plen=fill_tcp_data_p(buf,plen,PSTR("OFF  <a href=\"/?RU&RL2=TGL\">Toggle</a>"));
	
	plen=fill_tcp_data_p(buf,plen,PSTR("</li><li>Relay 3: "));
	
	if(RELAY3_READ()) plen=fill_tcp_data_p(buf,plen,PSTR("<font color=#00FF00>ON</font>  <a href=\"/?RU&RL3=TGL\" class=\"button\">Toggle</a>"));
	else plen=fill_tcp_data_p(buf,plen,PSTR("OFF  <a href=\"/?RU&RL3=TGL\">Toggle</a>"));
	
	plen=fill_tcp_data_p(buf,plen,PSTR("</li><li>Relay 4: "));
	
	if(RELAY4_READ()) plen=fill_tcp_data_p(buf,plen,PSTR("<font color=#00FF00>ON</font>  <a href=\"/?RU&RL4=TGL\" class=\"button\">Toggle</a>"));
	else plen=fill_tcp_data_p(buf,plen,PSTR("OFF  <a href=\"/?RU&RL4=TGL\">Toggle</a>"));
	
	plen=fill_tcp_data_p(buf,plen,PSTR("</li></ul>"));	
	
	return(plen);
}

uint16_t print_webpage_setclock(void)
{
        uint16_t plen;
        plen=http200ok();
        plen=print_line_mobile_webpage(plen);
        plen=fill_tcp_data_p(buf,plen,PSTR("<a href=/>[home]</a>\n"));
        plen=fill_tcp_data_p(buf,plen,PSTR("<h2>Set clock</h2>\n<pre>"));
        plen=fill_tcp_data_p(buf,plen,PSTR("\
<form  action=ts method=get>\n\
time :<input type=text name=tv id=tf size=10>\n\
<input type=submit value=\"set time\">\n\
</form>\n\
<script>\n\
d=new Date();\n\
e=document.getElementById(\"tf\");\n\
e.value=Math.round(new Date().getTime() / 1000) - 14400 ;\n\
</script>\n"));
        plen=fill_tcp_data_p(buf,plen,PSTR("</pre><hr>\n"));
        return(plen);
}

uint16_t print_webpage_schedule(void){
	
	uint16_t plen;
        plen=http200ok();
        plen=print_line_mobile_webpage(plen);
        plen=fill_tcp_data_p(buf,plen,PSTR("<a href=/>[home]</a>\n"));
        plen=fill_tcp_data_p(buf,plen,PSTR("<h2>Schedule</h2>\n<pre>"));
		plen=fill_tcp_data_p(buf,plen,PSTR("Under construction"));

        return(plen);

}

uint16_t print_line_mobile_webpage(uint16_t plen)
{
        //plen=fill_tcp_data_p(buf,plen,PSTR("<meta name=viewport content=\"width=device-width, initial-scale=1.2\">\n"));
        plen=fill_tcp_data_p(buf,plen,PSTR("<meta name=viewport content=\"width=device-width\">\n"));
        //plen=fill_tcp_data_p(buf,plen,PSTR("<meta name=viewport content=\"width=240, initial-scale=1\">\n"));
        return(plen);
}
