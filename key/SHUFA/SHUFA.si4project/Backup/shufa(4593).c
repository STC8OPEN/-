#include "lcd_192.h"
#include "adc.h"
#include "front.h"
#include "pir.h"

#define FOSC        11059200UL
#define BRT         (65536 - FOSC / 115200 / 4)
u8 code clear[]={0x00,0x00,0x00,0x00};
u8 code black[]={0xff,0xff,0xff,0xff};

bit busy;
char wptr;


void UartIsr() interrupt 4
{
    if (TI)
    {
        TI = 0;
        busy = 0;
    }
}
void UartInit()
{
    SCON = 0x50;
    T2L = BRT;
    T2H = BRT >> 8;
    AUXR = 0x15;
    wptr = 0x00;
    busy = 0;
}

void UartSend(char dat)
{
    while (busy);
    busy = 1;
    SBUF = dat;
}

 
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
		u16 data1;
//	P_SW1 = 0x00;                               //RXD/P3.0, TXD/P3.1
//  Init_lcd();
//  ADC_Init();
    PIR_INT();
	UartInit();
//  Displine(clear);
	//	ES = 1;
		//EA = 1;
   while(1)
   {
		//Displine(black);
		//display_left();
		//display_right();
		//M_Delay(400);

			EA = 0;
			data1=PIR_data_get();
		 	EA = 1;
		 	UartSend(data1/256);
		 	UartSend(data1%256);
   }
}