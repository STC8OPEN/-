#include "key.h"


void KEY_Init(void)
{
		P3M1=0x7F;
		P3M0=0X00;

}
void key_get(void)
{

	if(P37==0)
	{
		key_return.key_down++;
		key_return.key_up=0;
	}
	else
	{
		key_return.key_up++;
		if((key_return.key_down>=10)&&(key_return.key_up>=20))
		{
			key_return.key_flag_cl=1;
			key_return.key_down=0;
			key_return.key1++;
			if(key_return.key1==3)
				key_return.key1=1;
			
		}
	}

}


