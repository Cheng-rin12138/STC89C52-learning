#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
int result=0;
void main()
{
	LCD_Init();
	/*LCD_ShowString(1,1,"TheBombHasBeenPl");
	LCD_ShowString(2,1,"anted!");
	while(1)
	{
		Delay(1000);
		result++;
		LCD_ShowNum(2,9,result,2);
	}*/
	while(1)
	{
		LCD_ShowString(1,1,"YuanShenNB");
		LCD_ShowString(2,1,"LBWNB");
	
	}
	
}