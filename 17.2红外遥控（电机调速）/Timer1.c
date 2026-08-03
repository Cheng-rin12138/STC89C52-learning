#include <REGX52.H>

void Timer1_Init()//1毫秒@12.000MHz
{
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x66;		//设置定时初值
	TH1 = 0xFC;		//设置定时初值
	TF1 = 0;		//清除TF0标志
	TR1 = 1;		//定时器0开始计时
	
	ET1=1;
	EA=1;
	PT1=1;
}
/*unsigned int T1Count;
void Timer1_Routinue() interrupt 3
{
	
	TL1=0x66;
	TH1=0xFC;
	T1Count++;
	if(T1Count>=2000)
	{
		T1Count=0;
		
	}
}*/