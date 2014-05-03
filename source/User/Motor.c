#include	"stm32f10x.h"
#include	"Motor.h"

#include	"FreeRTOS.h"
#include	"task.h"
#include	"queue.h"
#include	"list.h"
#include	"portable.h"
#include	"freertosconfig.h"

#define Relay_Delay		(0xEFFFF)

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
void Delay(int nCount)
{
  for(; nCount != 0; nCount--);
}


void SetRelay( void )
{
		
}
void ReSetRelay( void )
{

}


// 继电器A置高电平,继电器断开
void SetRelayA( void )
{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
}


// 继电器B置高电平，继电器断开
void SetRelayB( void )
{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
}

// 继电器A置低电平，继电器吸合
void ReSetRelayA( void )
{
		Delay(Relay_Delay);
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

// 继电器B置低电平，继电器吸合
void ReSetRelayB( void )
{
		Delay(Relay_Delay);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
}

void Motor_Entry( void *pvParameters )
{
//	xQueueHandle			xQueue = (xQueueHandle)pvParameters;
	(void)pvParameters;
	Motor_GPIO_Init();
	
	return	;
}

