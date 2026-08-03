#include <REGX52.H>
#include "Timer1.h"
sbit Motor=P1^0;
unsigned char Counter,Compare;
void Motor_Init(void)
{
	Timer1_Init();
}
void Motor_SetSpeed(unsigned char Speed)
{
	Compare=Speed;
}
void Timer1_Routinue() interrupt 3
{
	unsigned char T1Count;
	TL1=0x9C;
	TH1=0xFF;
	Counter++;
	Counter%=100;
	if(Counter<Compare){Motor=1;}
	else{Motor=0;}
	T1Count++;
	if(T1Count>20)
	{
		T1Count=0;
		Key_Loop();
	}
}