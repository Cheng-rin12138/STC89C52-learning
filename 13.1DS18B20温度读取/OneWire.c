#include <REGX52.H>
sbit OneWire_DQ=P3^7;

unsigned char OneWire_Init(void)
{
	unsigned char i;
	unsigned char AckBit;
	//1.进入初始化，先确保高电平再拉低
	OneWire_DQ=1;
	OneWire_DQ=0;
	//2.延时至少480us后再释放，留出多余一点时间，设为500ms
	i=247;while(--i);//延时500us
	//3.主机释放总线15~60us后，从机拉低60~240us（取70us检测从机拉低电平）
	OneWire_DQ=1;//主机释放
	i=32;while(--i);//延时70us检测
	AckBit=OneWire_DQ;//读取电平
	i=247;while(--i);//延时500ms，需要保证第二个时间片>480us
	return AckBit;
}

void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	//1.主机先拉低60~120us后释放表示发送0；拉低1~15us后释放表示发送1
	OneWire_DQ=0;
	i=4;while(--i);//延时10us（实际14）
	OneWire_DQ=Bit;
	i=24;while(--i);//延时50us（实际54）
	OneWire_DQ=1;//主机释放
	//如果Bit=0则14us后为低电平，Bit为1则14us后释放为高电平
}

unsigned char OneWire_ReceiveBit(void)
{
	unsigned char i;
	unsigned char Bit;
	//主机先拉低1~15us释放并在15us读取高低电平
	OneWire_DQ=0;
	i=2;while(--i);//延时5us
	OneWire_DQ=1;
	i=2;while(--i);//延时5us
	Bit=OneWire_DQ;//采样
	i=24;while(--i);//延时50us
	return Bit;
}
//发送1个字节
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		OneWire_SendBit(Byte&(0x01<<i));
	}
}
//接收1个字节
unsigned char OneWire_ReceiveByte(void)
{
	unsigned char i;
	unsigned char Byte=0x00;
	for(i=0;i<8;i++)
	{
		if(OneWire_ReceiveBit()){Byte|=(0x01<<i);}
	}
	return Byte;
}
