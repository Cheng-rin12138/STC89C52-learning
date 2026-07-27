#include <REGX52.H>
sbit DS1302_SCLK=P3^6;
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;

#define DS1302_SECOND 0x80
#define DS1302_MINUTE 0x82
#define DS1302_HOUR 0x84
#define DS1302_DATE 0x86
#define DS1302_MONTH 0x88
#define DS1302_DAY 0x8A
#define DS1302_YEAR 0x8C
#define DS1302_WP 0x8E
unsigned char DS1302_Time[]={26,7,27,11,33,20,6};

void DS1302_Init(void)
{
	//由时序图知，CE和SCLK读写前默认低电平，即先置0
	DS1302_CE=0;
	DS1302_SCLK=0;
}
void DS1302_WriteByte(unsigned char Command,Data)
{
	unsigned char i;
	//1.CE先置1
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		//2.先把命令字放在IO口上，先读取最0位,依次移位
		DS1302_IO=Command&(0x01<<i);
		//3.上升沿，锁存该位数据
		DS1302_SCLK=1;
		//4.时钟复位准备下一位
		DS1302_SCLK=0;//如果过快需要延时，稳定一段高电平
	}
	for(i=0;i<8;i++)
	{
		DS1302_IO=Data&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	DS1302_CE=0;
}
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i,Data=0x00;//局部变量默认初始化值不一定为0
	Command|=0x01;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=0;//先0后1作周期
		DS1302_SCLK=1;
	}	
	
	for(i=0;i<8;i++)
	{
		DS1302_SCLK=1;
		DS1302_SCLK=0;//补1上升沿让D0被推到IO线上，才能继续采集
		if(DS1302_IO)//赋值时单片机输出，不赋值if时由DS1302控制,IO值和读取到的bit值相同
			{Data|=(0x01<<i);}//只对最后一位操作，读取到最低位为1则更新并移位，最低位为0则不更新数据而直接左移1位
	}
	DS1302_CE=0;
	DS1302_IO=0;
	return Data;
}
void DS1302_SetTime(void)
{
	DS1302_WriteByte(DS1302_WP,0x00);//关闭写保护
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16+DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);//打开写保护
}
void DS1302_ReadTime(void)
{
	unsigned char Temp;
	Temp=DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6]=Temp/16*10+Temp%16;
}