#include "lcd_192.h"
#include "adc.h"
#include "front.h"
#include "pir.h"
#define FOSC        12000000UL
#define BRT         (65536 - FOSC / 120000 / 4)

u8 code clear[]={0x00,0x00,0x00,0x00};
u8 code black[]={0xff,0xff,0xff,0xff};


//----------------------------------------------------------
void M_Delay(u16 NOs)
 {
   while(NOs)
   {
		NOs--;
		Delay(50);
   }
 }
void display_left()
{
	display_graphic_32x32(1,0,zi6);
	display_graphic_32x32(1,30,zi5); 
	display_graphic_32x32(1,64,zi4); 
	display_graphic_32x32(1,94,zi3); 
	display_graphic_32x32(1,128,zi2); 
	display_graphic_32x32(1,160,zi1); 
}
void display_right()
{
	u16 volt_value=2345;
	volt_value=Power_volet();
	lcd_show_char(5,176,volt_value/100%10);
	lcd_show_char(6,176,'.');
	lcd_show_char(7,176,volt_value/10%10);
	lcd_show_char(8,176,'V');
}
void main()
{
   Init_lcd();
   ADC_Init();
   PIR_INT();
   Displine(clear);
   while(1)
   {
		Displine(black);
		display_left();
		display_right();
		M_Delay(50000);
		PIR_data_get();
   }
}