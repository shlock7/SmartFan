#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "AD.h"

uint8_t KeyNum;
int8_t Speed;

int main(void)
{
	OLED_Init();
	Motor_Init();
	Key_Init();
	AD_Init();
	
	OLED_ShowString(1, 1, "Speed:");
	OLED_ShowString(2, 1, "AD0:");
	OLED_ShowString(3, 1, "AD1:");
	
	while (1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 1)
		{
			Speed += 20;
			if (Speed > 100)
			{
				Speed = 0;
			}
		}
		Motor_SetSpeed(Speed);
		OLED_ShowSignedNum(1, 7, Speed, 3);
		OLED_ShowNum(2, 5, AD_Value[0], 4); // 温度
		OLED_ShowNum(3, 5, AD_Value[1], 4); // 红外
	}
}
