#ifndef __LCD_192_H
#define __LCD_192_H

#include "stc8h.h" 
#include <intrins.h>

sbit CS =P3^7;
sbit RST =P3^5;
sbit CD= P3^6;
sbit SCK =P3^3;
sbit SDA= P3^4;
sbit BLACK_ED =P3^2;



void Init_lcd(void);
void Delay(u16 times);
void Displine(u8 array[]);
void lcd_show_char(u16 page,u16 column,u8 CHAR_NUM);
void display_graphic_16x16(u8 page,u8 column,u8 *dp);
void display_graphic_32x32(u8 page,u8 column,u8 *dp);
void display_graphic_32x64(u8  page,u8 column,u8 *dp);



#endif  