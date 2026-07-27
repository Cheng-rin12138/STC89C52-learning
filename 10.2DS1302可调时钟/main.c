#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"

unsigned char KeyNum,MODE,TimeSetSelect,TimeSetFlashFlag;

void TimeShow(void)
{
		DS1302_ReadTime();
		LCD_ShowNum(1,1,DS1302_Time[0],2);
		LCD_ShowNum(1,4,DS1302_Time[1],2);
		LCD_ShowNum(1,7,DS1302_Time[2],2);
		LCD_ShowNum(2,1,DS1302_Time[3],2);
		LCD_ShowNum(2,4,DS1302_Time[4],2);
		LCD_ShowNum(2,7,DS1302_Time[5],2);
}
void TimeSet(void)
{
	//1.切换选位
	if(KeyNum==2)
	{
		TimeSetSelect++;
		TimeSetSelect%=6;//防止溢出
	}
	//2.时间加减
	if(KeyNum==3)
	{
		DS1302_Time[TimeSetSelect]++;
		//越界判断
		if(DS1302_Time[0]>99){DS1302_Time[0]=0;}//年
		if(DS1302_Time[1]>12){DS1302_Time[1]=1;}//月
		if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||DS1302_Time[1]==7||DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)//大月
		{
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==4||DS1302_Time[1]==6||DS1302_Time[1]==9||DS1302_Time[1]==11)//小月
		{
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==2)//2月
		{
			if(DS1302_Time[0]%4==0)//闰年
			{
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
			}
			else//平年
			{
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}
			}
		}
		if(DS1302_Time[3]>23){DS1302_Time[3]=0;}
		if(DS1302_Time[4]>59){DS1302_Time[4]=0;}
		if(DS1302_Time[5]>59){DS1302_Time[5]=0;}
	}
	if(KeyNum==4)
	{
		DS1302_Time[TimeSetSelect]--;
		//越界判断
		if(DS1302_Time[0]<0){DS1302_Time[0]=99;}//年
		if(DS1302_Time[1]<1){DS1302_Time[1]=12;}//月
		if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||DS1302_Time[1]==7||DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)//大月
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=31;}
		}
		else if(DS1302_Time[1]==4||DS1302_Time[1]==6||DS1302_Time[1]==9||DS1302_Time[1]==11)//小月
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=30;}
			if(DS1302_Time[2]>30){DS1302_Time[2]=30;}
		}
		else if(DS1302_Time[1]==2)//2月
		{
			if(DS1302_Time[0]%4==0)//闰年
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=29;}
				if(DS1302_Time[2]>29){DS1302_Time[2]=29;}
			}
			else//平年
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=28;}
				if(DS1302_Time[2]>28){DS1302_Time[2]=28;}
			}
		}
		if(DS1302_Time[3]<0){DS1302_Time[3]=23;}
		if(DS1302_Time[4]<0){DS1302_Time[4]=59;}
		if(DS1302_Time[5]<0){DS1302_Time[5]=59;}
	}
	//3.更新时间
	if(TimeSetSelect==0 && TimeSetFlashFlag==1){LCD_ShowString(1,1,"  ");}//选中该位闪烁
	else{LCD_ShowNum(1,1,DS1302_Time[0],2);}//同理改其他位闪烁
	if(TimeSetSelect==1 && TimeSetFlashFlag==1){LCD_ShowString(1,4,"  ");}
	else{LCD_ShowNum(1,4,DS1302_Time[1],2);}
	if(TimeSetSelect==2 && TimeSetFlashFlag==1){LCD_ShowString(1,7,"  ");}
	else{LCD_ShowNum(1,7,DS1302_Time[2],2);}
	if(TimeSetSelect==3 && TimeSetFlashFlag==1){LCD_ShowString(2,1,"  ");}
	else{LCD_ShowNum(2,1,DS1302_Time[3],2);}
	if(TimeSetSelect==4 && TimeSetFlashFlag==1){LCD_ShowString(2,4,"  ");}
	else{LCD_ShowNum(2,4,DS1302_Time[4],2);}
	if(TimeSetSelect==5 && TimeSetFlashFlag==1){LCD_ShowString(2,7,"  ");}
	else{LCD_ShowNum(2,7,DS1302_Time[5],2);}
	LCD_ShowString(2,10,"SET");
	LCD_ShowNum(2,13,TimeSetSelect,2);
}
void main()
{
	LCD_Init();
	DS1302_Init();
	Timer0_Init();
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	DS1302_SetTime();
	while(1)
	{
		KeyNum=Key();//读取按键获取值0~4
		if(KeyNum==1)
		{
			if(MODE==0){MODE=1;TimeSetSelect=0;}
			else if(MODE==1){MODE=0;DS1302_SetTime();LCD_ShowString(2,10,"     ");}
		}
		switch(MODE)
		{
			case 0:TimeShow();break;
			case 1:TimeSet();break;
		}
	}
}
void Timer0_Routinue() interrupt 1
{
	static unsigned int T0Count;
	TL0=0x18;
	TH0=0xFC;
	T0Count++;
	if(T0Count>=500)
	{
		T0Count=0;
		TimeSetFlashFlag=!TimeSetFlashFlag;
	}
}
