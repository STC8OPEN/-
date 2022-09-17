#include "pir.h"
#include <intrins.h>
u16 data_pir;
void Delay1us_pir(u8 i)		//@11.0592MHz
{
	while (--i);
}
void PIR_INT(void)
{

	P0M0 = 0x00;
	P0M1 = 0x00;
	P5M0 = 0x00;
	P5M1 = 0x00;

}
void PIR_data_get(void)
{
	u8 flag=0;
	u8 PIR_data_get;

	if(PIR_IO==1)
	{
		for(PIR_data_get=0;PIR_data_get<19;PIR_data_get++)
		{
			PIR_IO=0;
		  Delay1us_pir(30);
			P5M1 = 0x00;
			PIR_IO=1;
			Delay1us_pir(40);
			P5M1 = 0xff;			
			Delay1us_pir(5);
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
			Delay1us_pir(70);
		}
		Delay1us_pir(30);
	}
	
}
