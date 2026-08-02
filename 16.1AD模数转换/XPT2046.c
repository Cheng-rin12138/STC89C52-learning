#include <REGX52.H>
#include "Delay.h"
sbit XPT2046_CS=P3^5;
sbit XPT2046_DCLK=P3^6;
sbit XPT2046_DIN=P3^4;
sbit XPT2046_DOUT=P3^7;
unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned int ADValue=0;
	unsigned char i;
	//先初始化
	XPT2046_DCLK=0;//先置0时钟
	XPT2046_CS=0;//开始
	for(i=0;i<8;i++)
	{
		XPT2046_DIN=Command&(0x80>>i);
		XPT2046_DCLK=1;//上升沿采样
		XPT2046_DCLK=0;
	}
	for(i=0;i<16;i++)
	{
		XPT2046_DCLK=1;
		//Delay(1);
		XPT2046_DCLK=0;//下降沿读出
		Delay(10);
		if(XPT2046_DOUT)
		{ADValue|=0x8000>>i;}
	}
	XPT2046_CS=1;//结束
	if(Command&0x08)//倒数第四位决定分辨率
	{
		return ADValue>>8;//2字节共16位低位不足用0填充，需要右移回来得到实际大小
	}
	else
	{
		return ADValue>>14;
	}
}