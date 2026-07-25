#include <REGX52.H>
#include "Delay.h"
#include "MatrixLED.h"

void main()
{
	MatrixLED_Init();
	while(1)
	{
		MatrixLED_ShowColumn(0,0xFF);
		MatrixLED_ShowColumn(1,0x81);
		MatrixLED_ShowColumn(2,0xA3);
		MatrixLED_ShowColumn(3,0x95);
		MatrixLED_ShowColumn(4,0x89);
		MatrixLED_ShowColumn(5,0x95);
		MatrixLED_ShowColumn(6,0xA3);
		MatrixLED_ShowColumn(7,0x81);
	}
}
