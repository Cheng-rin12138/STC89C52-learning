#include <REGX52.H>
void Int0_Init(void)
{
	IT0=1;//下降沿触发
	IE0=0;//中断标志，置0即可
	EX0=1;//打开该中断
	EA=1;//打开中断总开关
	PX0=1;//高优先级，可打断别的中断进行嵌套
}
//外部中断函数模板
/*void Int0_Routine(void) interrupt 0
{
	
}*/