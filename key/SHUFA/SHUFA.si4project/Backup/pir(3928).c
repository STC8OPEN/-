#include "pir.h"
#include <intrins.h>
void Delay20us_pir(u8 i)		//@11.0592MHz
{
	unsigned char j;

	j = 40;
	while (--j);
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
	for(PIR_data_get=0;PIR_data_get<19;PIR_data_get++)
	{
		PIR_IO=0;
		PIR_IO=1;
		Delay20us_pir(1);
	}
	
}
