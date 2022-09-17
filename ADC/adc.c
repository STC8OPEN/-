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
    ADC_CONTR |= 0x40;                          //启动AD转换
		NOP1();
    while (!(ADC_CONTR & 0x20));                //查询ADC完成标志
    ADC_CONTR &= ~0x20;                         //清完成标志
    res = (ADC_RES << 8) | ADC_RESL;            //读取ADC结果

    return res;
}
u16 Power_volet(void)
{
    float power_v;
		power_v=ADCRead();
		power_v=1024*11.9/power_v*10;
    return (u16)power_v;
}