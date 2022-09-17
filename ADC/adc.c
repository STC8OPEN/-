#include "adc.h"
#include "intrins.h"


void ADC_Init(void)
{
	ADCTIM=0X3F;
	ADCCFG=0x2f;
	ADC_CONTR=0x8F;
}
u16 ADCRead(void)
{
    u16 res;
    ADC_CONTR |= 0x40;                          //����ADת��
		NOP1();
    while (!(ADC_CONTR & 0x20));                //��ѯADC��ɱ�־
    ADC_CONTR &= ~0x20;                         //����ɱ�־
    res = (ADC_RES << 8) | ADC_RESL;            //��ȡADC���

    return res;
}
u16 Power_volet(void)
{
    float power_v;
		power_v=ADCRead();
		power_v=1024*11.9/power_v*10;
    return (u16)power_v;
}