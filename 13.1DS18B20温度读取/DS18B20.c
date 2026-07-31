#include <REGX52.H>
#include "OneWire.h"
#define DS18B20_SKIP_ROM         0xCC
#define DS18B20_CONVERT_T        0x44
#define DS18B20_READ_SCRATCHPAD  0xBE
void DS18B20_ConvertT(void)
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_CONVERT_T);
}
float DS18B20_ReadT(void)
{
	unsigned char TLSB,TMSB;
	int Temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	TLSB=OneWire_ReceiveByte();
	TMSB=OneWire_ReceiveByte();
	Temp=(TMSB<<8)|TLSB;//无符号转为有符号时内容不变
	//二进制左移1位相当于x2，由于BIT4相当于实际最低位，需要向右移4位，但精度不损失
	T=Temp/16.0;
	return T;
}