#include "tim.h" 

void TIM_Init(void)
{
    TMOD = 0x00;                                //ģʽ0
    TL0 = 0xCD;                                 //65536-12/1000
    TH0 = 0xFF;
    TR0 = 1;                                    //������ʱ��
    ET0 = 1;                                    //ʹ�ܶ�ʱ���ж�
    EA = 1;
}

