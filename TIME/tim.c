#include "tim.h" 

void TIM_Init(void)
{
    TMOD = 0x00;                                //模式0
    TL0 = 0xCD;                                 //65536-12/1000
    TH0 = 0xFF;
    TR0 = 1;                                    //启动定时器
    ET0 = 1;                                    //使能定时器中断
    EA = 1;
}

