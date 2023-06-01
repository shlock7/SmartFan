#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //开启TIM2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//开启GPIO时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    	 //复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			 //开启引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //配置响应速度
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);		//使用内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;          //配置时基单元
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;			//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;	//重复计数器
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;	//定义输出比较结构体
	TIM_OCStructInit(&TIM_OCInitStructure);	//给结构体赋默认值
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //PWM1模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 	  //有效电平为高电平
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //使能
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2, Compare); //设置CCR3的值
}
