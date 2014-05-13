#include <stm32f10x.h>
#include "LightCounter.h"

void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0);     //清除和挂起中断
}

void Light_Counter_NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Light_Count_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef Exit_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
          
  Exit_InitStructure.EXTI_Line = EXTI_Line0;        
	Exit_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;        
  Exit_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  Exit_InitStructure.EXTI_LineCmd = ENABLE;                     
  EXTI_Init(&Exit_InitStructure);         
	
}

int Light_Counter_Init()
{
	Light_Count_GPIO_Config();
	Light_Counter_NVIC_Config();
	return 0;
}

void Register_Light_Count_CallBack(LIGHT_COUNT_CALLBACK function)
{
	
}

