#include <REGX52.H>
#include<INTRINS.H>

void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main()
{
	P2=0xFE;//1ºÅµÆÁÁ
	Delay500ms();
	P2=0xFF;//1ºÅµÆÃð
	Delay500ms();
}