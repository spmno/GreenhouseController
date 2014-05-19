#ifndef _GREENHOUSE_ADC_H_
#define _GREENHOUSE_ADC_H_
#include <stm32f10x.h>

int Analog_Digital_Converter_Init();
u16 Get_ADC_Data(u8 channel);

#endif
