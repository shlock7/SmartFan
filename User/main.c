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
	OLED_ShowString(2, 1, "Temp:");
	OLED_ShowString(3, 1, "Infr:");
	OLED_ShowString(4, 1, "POWER:");
	uint16_t temperature, infrared;
	uint8_t powerFlag = 0;
	while (1)
	{
//		KeyNum = Key_GetNum();
//		if (KeyNum == 1)
//		{
//			Speed += 20;
//			if (Speed > 60)
//				Speed = 0;
//		}
		//Motor_SetSpeed(Speed);
		

		temperature = AD_Value[0];
		infrared = AD_Value[1];
		
		if (infrared <= 2500)
			powerFlag = 1;
		else if (infrared > 3100)
			powerFlag = 0;
		
		// 1700 -- 1850
		if (temperature >= 1850)
			Speed = 0;
		else if(temperature <= 1700)
			Speed = 60;
		else
			Speed = (1850 - temperature) * 2 / 5;
		if (powerFlag)
			Motor_SetSpeed(Speed);
		else
			Motor_SetSpeed(0);
		
		OLED_ShowSignedNum(1, 7, Speed, 3);
		OLED_ShowNum(2, 6, temperature, 4); // 温度
		OLED_ShowNum(3, 6, infrared, 4);    // 红外
		if (powerFlag)
			OLED_ShowString(4, 7, "ON");
		else
			OLED_ShowString(4, 7, "OF");
		Delay_ms(1000);
	}
}
