#include <REGX52.H>
#include "Delay.h"
#include "UART.h"

unsigned char Sec;
void main()
{
	UART_Init();
	while(1)
	{
		UART_SendByte(Sec++);
		Delay(1000);
	}

}
void UART_Routinue() interrupt 4
{
	//P2=0x00;//灯全亮表示进入中断函数
	if(RI==1)//接收完毕
	{
		P2=~SBUF;
		UART_SendByte(SBUF);
		RI=0;//软件复位
	}
}