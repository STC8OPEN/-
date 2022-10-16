#include "lcd_192.h"
#include "adc.h"
#include "front.h"
#include "pir.h"
#include "cds.h"
#include "sth30.h"  

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
	static u8 i=0;
	i++;
	if(i%3==0)
	{
		display_graphic_32x32(5,0,zi6);
		display_graphic_32x32(1,0,zi5); 
	}
	else if(i%3==1)
	{
	    display_graphic_32x32(5,0,zi3); 
		display_graphic_32x32(1,0,zi4); 
	}
	else if(i%3==2)
	{
		display_graphic_32x32(1,0,zi1); 
		display_graphic_32x32(5,0,zi2); 
	}
}
void display_right()
{
	u16 volt_value=2345;
	volt_value=Power_volet();
	lcd_show_char(5,176,volt_value/100%10);
	lcd_show_char(6,176,'.');
	lcd_show_char(7,176,volt_value/10%10);
	lcd_show_char(8,176,'V');

	display_graphic_16x32(1,35,temp_get()/10);
	display_graphic_16x32(3,35,temp_get()%10);
	display_graphic_32x32(5,35,zi7);

	display_graphic_16x32(1,70,humi_get()/10);
	display_graphic_16x32(3,70,humi_get()%10);
	display_graphic_32x32(5,70,zi8);
	

	
	read_temp_hum_cmd();
}
void main()
{
	u16 data1;
	//P_SW1 = 0x00;                               //RXD/P3.0, TXD/P3.1
	Init_lcd();
	ADC_Init();
	PIR_INT();
	SHT30_Init();

	CDS_INT();
	Displine(clear);
	ES = 1;
    while(1)
    {
		 if(CDS==0)
		 {
				BLACK_ED=1;
		 }
		 else
		 {
				BLACK_ED=0;
		 }
			Displine(black);
			display_left();
			display_right();
			M_Delay(40000);
	

			//EA = 0;
			//data1=PIR_data_get();
		// 	EA = 1;
		 	//UartSend(data1/256);
		 	//UartSend(data1%256);

    }
}