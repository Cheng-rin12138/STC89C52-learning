#include <REGX52.H>

void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;
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
	unsigned char k;
	while(1)
	{
	for(k=0;k<8;k++)
	{
		P2=0xFF;
		P2=~(1<<k);
		Delay500ms();
	}
	}
}
