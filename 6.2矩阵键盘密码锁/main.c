#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char Keynum=0;
unsigned int Password,count;
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
				if(count<4)
				{	
					Password*=10;
					Password+=Keynum%10;
					count++;
				}	
				LCD_ShowNum(2,1,Password,4);
			}
			if(Keynum==11)//确认键
			{
				if(Password==1314)
				{
					LCD_ShowString(1,11,"True  ");
					count=0;
					Password=0;
					LCD_ShowNum(2,1,Password,4);
				}
				else
				{
					LCD_ShowString(1,11,"Error ");
					count=0;
					Password=0;
					LCD_ShowNum(2,1,Password,4);
				}
			}
			if(Keynum==12)//取消输入
			{
				LCD_ShowString(1,11,"Cancel");
				count=0;
				Password=0;
				LCD_ShowNum(2,1,Password,4);
			}
		}
	}
}