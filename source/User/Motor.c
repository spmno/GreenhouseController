#include	"stm32f10x.h"
#include	"Motor.h"

#include	"FreeRTOS.h"
#include	"task.h"
#include	"queue.h"
#include	"list.h"
#include	"portable.h"
#include	"freertosconfig.h"

void Motor_GPIO_Init( void )
{
		GPIO_InitTypeDef GPIO_InitStructure;
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	return	;
}

// 置高电平 继电器放开
void SetRelay( void )
{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
}


// 置低电平 继电器吸合
void ReSetRelay( void )
{
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
}

void Motor_Entry( void *pvParameters )
{
//	xQueueHandle			xQueue = (xQueueHandle)pvParameters;
	(void)pvParameters;
	Motor_GPIO_Init();
	
	return	;
}

