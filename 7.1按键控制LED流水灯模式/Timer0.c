#include <REGX52.H>

void Timer0_Init()//1毫秒@12.000MHz
{
	/*TMOD=0x01;//0000 0001
	TF0=0;//
	TR0=1;//打开计数器开关
	TH0=64536/256;
	TL0=64536%256;*/
	//AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
	ET0=1;
	EA=1;
	PT0=1;
}
/*unsigned int T0Count;
void Timer0_Routinue() interrupt 1
{
	
	TL0=0x18;
	TH0=0xFC;
	T0Count++;
	if(T0Count>=2000)
	{
		T0Count=0;
		
	}
}*/