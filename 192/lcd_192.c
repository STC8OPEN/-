#include "lcd_192.h"
#include "oled_front.h"

#define somenop();_nop_();_nop_();_nop_();_nop_();


u8 code IC[]={
	0xe2,//system reset
	0xa0,//set Frame Rate[A0: 76fps, A1b: 95fps, A2b: 132fps, A3b: 168fps(fps: frame-per-second)]  
	0xeb,//set BR 
	0x2f,//set Power Control
	0xc2,//set LCD Mapping Control
	0x81,//set PM
	160, //set PM 110
	0xaf,//display Enable
};
//----------------------------------------------------------
void Delay(u16 times)
  {
   while(times)
   {
    times--;
   }
  }
	
	void WriteData(u8 data1, bit di)
{
       u8 i,temp;
        CS=0;
		CD=di;
		for(i=0;i<8;i++)
		    {
                  SCK=0;
		  temp=data1;
		  SDA=(bit)(temp&0x80);

		  somenop();
	      SCK=1;
          temp=data1<<1;
	      data1=temp;
 		     }
        CS=1;
		CD=~di;
}

//----------------------------------------------------------
void Init_lcd(void)
{
	int i;
	P3M0 = 0xff;
	P3M1 = 0x00;
	RST=0;
	Delay(200);
	RST=1;
	Delay(50000);
	for(i=0;i<8;i++)
	{
		WriteData(IC[i],0);
	}
}
//----------------------------------------------------------
void Displine(u8 array[])
  {
   u16 i,j,k;
   for(i=0;i<9;i++)
   {

    WriteData(0x40,0);  //set scroll line
    WriteData(0xb0|i,0);//set page address
    WriteData(0x10,0);  //column  msb
    WriteData(0x00,0);  //column  lsb
    for(j=0;j<48;j++)
    for(k=0;k<4;k++)
    {
     WriteData(array[k],1);
    }
   }
  }

void lcd_address(u16 page,u16 column)
{
	column=column-0x01;
	WriteData(0xB0+page-1,0); 
	WriteData(0x10+(column>>4&0x0F),0);
	WriteData(column&0x0F,0); 
}

void lcd_show_char(u16 page,u16 column,u8 CHAR_NUM)
{
	u8 i;
	u8 dp=0;
	if((0<=CHAR_NUM)&&(CHAR_NUM<=9))
	{
		CHAR_NUM=CHAR_NUM+16;
		lcd_address(page,column);
		for (i=0;i<16;i++)
		{
			WriteData(USER[CHAR_NUM][dp],1);
			dp++;
		}
	}
	else if((32<=CHAR_NUM)&&(CHAR_NUM<=47))
	{	
		CHAR_NUM=CHAR_NUM-32;
		lcd_address(page,column);
		for (i=0;i<16;i++)
		{
			WriteData(USER[CHAR_NUM][dp],1);
			dp++;
		}
	}
	else if(65<=CHAR_NUM)
	{	
		CHAR_NUM=CHAR_NUM-39;
		lcd_address(page,column);
		for (i=0;i<16;i++)
		{
			WriteData(USER[CHAR_NUM][dp],1);
			dp++;
		}
	}

}

void display_graphic_16x16(u8 page,u8 column,u8 *dp)
{
	u16 i,j;
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<16;i++)
		{
		WriteData(*dp,1);
		dp++;
		}
	}
}  

void display_graphic_32x32(u8  page,u8 column,u8 *dp)
{
	u16 i,j;
	for(j=0;j<4;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<32;i++)
		{
		WriteData(*dp,1); 
		dp++;
		}
	}
}  

void display_graphic_32x64(u8  page,u8 column,u8 *dp)
{
	u16 i,j;
	for(j=0;j<8;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<32;i++)
		{
		WriteData(*dp,1); 
		dp++;
		}
	}
}  
