#include <REGX52.H>

void Timer0_Init()//1毫秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式：清除原有配置
	TMOD |= 0x01;		//设置定时器模式：模式1的16位定时器
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0默认不计时
}
void Timer0_SetCounter(unsigned int Value)
{
	TH0=Value/256;
	TL0=Value%256;
}
unsigned int Timer0_GetCounter(void)
{
	return (TH0<<8)|TL0;
}
void Timer0_Run(unsigned char Flag)
{
	TR0=Flag;//置1开始计时，置0停止计时
}