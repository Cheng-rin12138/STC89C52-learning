#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Motor.h"
#include "IR.h"

unsigned char Command,Speed;
void main()
{
	while(1)
	{
		Motor_Init();
		IR_Init();
		if(IR_GetDataFlag())
		{
			Speed++;
			Speed%=4;
			Command=IR_GetDataFlag();
			if(Command==IR_0){Speed=0;}
			if(Command==IR_1){Speed=1;}
			if(Command==IR_2){Speed=2;}
			if(Command==IR_3){Speed=3;}
			if(Speed==0){Motor_SetSpeed(0);}
			if(Speed==1){Motor_SetSpeed(25);}
			if(Speed==2){Motor_SetSpeed(50);}
			if(Speed==3){Motor_SetSpeed(100);}
		}
		Nixie(1,Speed);
	}
}
