#include "pir.h"
#include <intrins.h>
void Delay1us_pir(u8 i)		//@11.0592MHz
{
	while (--i);
}
void PIR_INT(void)
{

	P5M0 = 0x00;
	P5M1 = 0x00;

}
void PIR_data_get(void)
{
	u8 PIR_data_get;

	if(PIR_IO==1)
	{
		Delay1us_pir(30);
		for(PIR_data_get=0;PIR_data_get<19;PIR_data_get++)
		{
			PIR_IO=0;
		   Delay1us_pir(30);
			PIR_IO=1;
			Delay1us_pir(50);
			if(PIR_IO==1)
			{
			}
			else
			{
			}
		}
		Delay1us_pir(30);
	}
	
}
