#include	"stm32f10x.h"
#include	"Timer.h"

static TIMER_TASK global_task;

void TIM2_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{

		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);

		global_task();
	}
}


void TIMER_cfg()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_DeInit(TIM2);

	TIM_InternalClockConfig(TIM2);

	TIM_TimeBaseStructure.TIM_Prescaler = 36000 - 1;

	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseStructure.TIM_Period = 10000 - 1;

	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update); 

	TIM_ARRPreloadConfig(TIM2, DISABLE);

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
}
void NVIC_cfg()
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;

	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
}

int Start_Timer(TIMER_TASK task, int second)
{
	global_task = task;
	TIMER_cfg();
	NVIC_cfg();
	TIM_Cmd(TIM2,ENABLE);
	return 0;
}

void Stop_Timer()
{
	TIM_Cmd(TIM2,DISABLE);
}


