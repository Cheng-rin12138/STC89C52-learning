#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char Keynum=0;
void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	while(1)
	{
		Keynum=MatrixKey();
		if(Keynum)
		{
			if(Keynum<=10)
			{
				Keynum=Keynum%10;
			}
			LCD_ShowNum(2,1,Keynum,2);
		}
	}
}