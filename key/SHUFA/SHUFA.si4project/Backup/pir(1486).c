#include "pir.h"
#include <intrins.h>
u16 data_pir;


void Delay1us_pir(u8 i)		//@11.0592MHz
{
	while (--i);
}
void PIR_INT(void)
{
	P5M0 = 0x00;
	P5M1 = 0x00;

}
u16 PIR_data_get(void)
{
	u8 flag=0;
	u8 PIR_data_get;

	if(PIR_IO==1)
	{
		for(PIR_data_get=0;PIR_data_get<=19;PIR_data_get++)
		{
			PIR_IO=0;
		  Delay1us_pir(30);
			P5M1 = 0x00;
			PIR_IO=1;
			Delay1us_pir(40);
			P5M1 = 0xff;			
			Delay1us_pir(14);
			if(PIR_IO==1)
			{
				data_pir=data_pir|0x001;
				data_pir=data_pir<<1;
			}
			else
			{
				data_pir=data_pir&0xfffe;
				data_pir=data_pir<<1;
			}
		}	
		Delay1us_pir(100);
	//	if(data_pir>33000)data_pir=65536-data_pir;
		return  data_pir;
	}
}
