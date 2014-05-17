#include <stm32f10x.h>
#include "Buzzer.h"

#define BUZZER_PIN	GPIO_Pin_0

int Buzzer_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void Buzzer_Beep()
{
	GPIO_ResetBits(GPIOB, BUZZER_PIN);
}

void Buzzer_Cancel()
{
	GPIO_SetBits(GPIOB, BUZZER_PIN);
}

